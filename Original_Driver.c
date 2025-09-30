#include <stdint.h>
#include <stdbool.h>
#include "iodefine.h"  // RZ/V2H用レジスタ定義

#define EEPROM_ADDR_WRITE 0xA0	//EEPROMnoI2C書き込みアドレス	
#define EEPROM_ADDR_READ 0xA1	//EEPROMのI2C読みだしアドレス
#define EEPROM_MIN_READ 3	//EEPROMから読みだす最小バイト数
#define EEPROM_BUFFER_SIZE 128	//EEPROM読み出し要最大バッファサイズ

//列挙型ステータス管理
typedef enum
{
	RIIC_SUCCESS = 0,	//処理指向を表すステータス、値は０
	RIIC_ERR_NACK,		//NACKを受信した場合のエラー
	RIIC_ERR_TIMEOUT,	//タイムアウトエラー
	RIIC_ERR_INVALID_ARG	//関数に渡された引数が不適切
} riic_status_t;		//列挙型を定義

// RIIC初期化
void riic_init(void)
{
	RIIC0.ICMR1 = 0x00;	//クロックフィルタやノイズ除去設定を初期化
	RIIC0.ICMR2 = 0x00;	//出力制御を初期化
	RIIC0.ICMR3 = 0x01;	//WAITビットを設定（WAIT = 1b）
	RIIC0.ICCR1 = 0x00;	//モジュールリセット解除
	RIIC0.ICCR2 = 0x80;	// RIIC動作開始
}

// START条件発行
riic_status_t riic_issue_start(void)
{
	//START（ICCR2のSTビット７をセット）
	RIIC0.ICCR2 |= (1 << 7);
	//簡易タイムループ
	for (volatile int i = 0; i < 10000; i++)
	{
		//ICSR２のSTSビットを確認
		if (RIIC0.ICSR2 & (1 << 0))
		{
			//成功
			return RIIC_SUCCESS;
		}
	}

	//タイムアウトした場合はエラーを返す
	return RIIC_ERR_TIMEOUT;
}

//再スタート条件発行
riic_status_t riic_issue_restart(void)
{
	//再スタート(ICCR2のSTビット５をリセット)
	RIIC0.ICCR2 |= (1 << 5);
	//簡易ループ
	for(volatile int i = 0; i < 10000; i++)
	{
		//ICSR2のSTSビットを確認
		if(RIIC0.ICSR2 & (1 << 0))
		{
			//成功
			return RIIC_SUCCESS;
		}
	}

	//タイムアウトした場合はエラーを返す
	return RIIC_ERR_TIMEOUT;
}

// STOP条件発行
riic_status_t riic_issue_stop(void)
{
	//STOP（ICSRのSPビット６をセット）
	RIIC0.ICCR2 |= (1 << 6);
	//STOP成立を待つループ
	for (volatile int i = 0; i < 10000; i++)
	{
		//ICSR２のSPSSビット（bit３）を確認
		if (RIIC0.ICSR2 & (1 << 3))
		{
			//成功
			return RIIC_SUCCESS;
		}
}

	//タイムアウトした場合はエラーを返す
	return RIIC_ERR_TIMEOUT;
}

// １バイト送信（ACK確認）
riic_status_t riic_write(uint8_t data)
{
	//送信データレジスタ（ICDRT）に１バイト書き込み
	RIIC0.ICDRT = data;
	//送信完了を待つループ
	for (volatile int i = 0; i < 10000; i++)
	{
		//ICSR2のTENDビット（bit2）を確認
		if (RIIC0.ICSR2 & (1 << 2))
		{
			//NACK検出（NACKFビット）ACKが返ってこなければエラー
			if (RIIC0.ICSR2 & (1 << 4))
			{
				return RIIC_ERR_NACK;
			}

			//ACLが返って吉良田成功
			return RIIC_SUCCESS;
		}
	}

	//タイムアウトした場合はエラーを返す
	return RIIC_ERR_TIMEOUT;
}

// １バイト受信（ACK/NACK制御）
riic_status_t riic_read(uint8_t *data, bool ack)
{
	//NULLポインターチェック
	if (data == NULL)
	{
		return RIIC_ERR_INVALID_ARG;
	}

	//ackを返す設定（ACKBビット＝１）
	if (ack)
	{
		RIIC0.ICMR3 |= (1 << 2);  //NCK
	}
	//NACLを返す設定（ACKBTビット＝０）
	else
	{
		RIIC0.ICMR3 &= ~(1 << 2); // NACK
	}

	//受信完了を待つループ
	for (volatile int i = 0; i < 10000; i++)
	{
		//ICSR2のRDRFビット（bit1）を確認
		if (RIIC0.ICSR2 & (1 << 1))
		{
			//データレジスタ（ICDRR）から１バイトを取得
			*data = RIIC0.ICDRR;
			//成功
			return RIIC_SUCCESS;
		}
	}
	//タイムアウトした場合はエラー
	return RIIC_ERR_TIMEOUT;
}

// EEPROM読み出し（3バイト以上限定）
riic_status_t riic_eeprom_read(uint16_t addr, uint8_t *buffer, uint8_t length)
{
	//最低３バイト以上の読み出しとNULLポインタチェック
	if (length < EEPROM_MIN_READ || buffer == NULL)
	{
		return RIIC_ERR_INVALID_ARG;
	}

	riic_status_t status;

	//START
	status = riic_issue_start();
	if (status != RIIC_SUCCESS)
	{
		return status;
	}

	//EEPROMの書き込みアドレス送信（0XA0）
	status = riic_write(EEPROM_ADDR_WRITE);
	if (status != RIIC_SUCCESS)
	{
		return status;
	}

	//EEPROM内部アドレス（上位バイト）送信
	status = riic_write((addr >> 8) & 0xFF);
	if (status != RIIC_SUCCESS)
	{
		return status;
	}

	//EEPROM内部アドレス（下位バイト）送信
	status = riic_write(addr & 0xFF);
	if (status != RIIC_SUCCESS)
	{
		return status;
	}

	//再スタート
	status = riic_issue_restart();
	if(status != RIIC_SUCCESS)
	{
		return status;
	}

	//EEPROM読み出しアドレス送信（0xA1）
	status = riic_write(EEPROM_ADDR_READ);
	if (status != RIIC_SUCCESS)
	{
		return status;
	}

	//指定バイト数分ループ
	for (uint8_t i = 0; i < length; i++)
	{
		//最後のバイトはNACK、それ以外はACK
		bool ack = (i < length - 1);
		//1バイト受信
		status = riic_read(&buffer[i], ack);
		if (status != RIIC_SUCCESS)
		{
			return status;
		}
	}

	//STOP
	return riic_issue_stop();
}
