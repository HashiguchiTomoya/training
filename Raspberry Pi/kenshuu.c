# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <linux/i2c-dev.h>
# include <iconv.h>

# define QUEUELIMIT 5						//キューの最大サイズを5に制限
# define REG_ADDR_GPIO_LENGTH 128			//GPIOのベースアドレスを定義
# define REG_ADDR_GPIO_BASE  0xFE200000		//GPIOのベースアドレスを定義
# define GPFSEL1 (0x04/4)					//GPIOのピン設定
# define GPFSEL2 (0x08/4)					//GPIOのピン設定
# define GPSET0 (0x1c/4)					//GPIOのピンをセット
# define GPCLR0 (0x28/4)					//GPIOのピンのクリア
# define LCD_ADDR 0x27						//LCDのI2Cアドレスを定義
# define I2C_DEVICE "/dev/i2c-1"			//通信デバイスを指定
# define MAX_BUF 1024						//バッファサイズを最大1024バイトを確保

// LCDに表示する関数
void Lcd_Send_Command(int I2cd, uint8_t Command)
{
	uint8_t Data[] = {Command | 0x08}; // バックライトON
	write(I2cd, Data, sizeof(Data));
}

void Lcd_Send_Data(int I2cd, uint8_t Data)
{
	printf("Sending to LCD: 0x%02X\n", Data);

    uint8_t Upper = (Data & 0xF0) | 0x0D; // 上位4ビット + RS=1, RW=0, E=1
	uint8_t Lower = ((Data << 4) & 0xF0) | 0x0D; // 下位4ビット + RS=1, RW=0, E=1

    // 上位4ビット送信
    write(I2cd, &Upper, 1);
    Upper &= ~0x04; // Eビットをクリア
    write(I2cd, &Upper, 1);

    // 下位4ビット送信
	write(I2cd, &Lower, 1);
    Lower &= ~0x04; // Eビットをクリア
    write(I2cd, &Lower, 1);
}

//LCD初期設定
void Lcd_Initialize(int I2cd)
{
	// LCD初期化データ
    uint8_t Lcd_Init_Config[][4] = 
	{
        {0x3C, 0x38, 0x3C, 0x38}, // 2行/5x8フォント設定
        {0x3C, 0x38, 0x2C, 0x28}, // 4ビットモード
        {0x2C, 0x28, 0x8C, 0x88}, // 画面表示ON/OFF
        {0x0C, 0x08, 0xCC, 0x08}, // カーソルの移動やクリア処理
        {0x0C, 0x08, 0x1C, 0x18}, // カーソルと画面のシフト設定
        {0x8C, 0x88, 0x0C, 0x08}  // 1行目のアドレス
    };

    // LCD初期化コマンド
    for (size_t i = 0; i < sizeof(Lcd_Init_Config) / sizeof(Lcd_Init_Config[0]); i++)
	{
        write(I2cd, Lcd_Init_Config[i], sizeof(Lcd_Init_Config[i]));
    }
}

// 受信した文字列をLCDに表示する
void Lcd_Display_String(int I2cd, const char *str)
{
	//クリアコマンド
	Lcd_Send_Command(I2cd, 0x01);
	
	size_t Len = strlen(str);
	
    for (size_t i = 0; i < Len; i++)
    {
		
        Lcd_Send_Data(I2cd, str[i]);

        if (15 == i)
        {
            uint8_t Extra_Data[] = {0xCC, 0xC8, 0x0C, 0x08};
            write(I2cd, Extra_Data, sizeof(Extra_Data));
        }
    }

	sleep(5);
	Lcd_Initialize(I2cd);
}

//カタカナ表示
void Convert_Utf8_To_Sjis(const char *utf8, char *sjis, size_t Buf_Size)
{
    iconv_t ic = iconv_open("SJIS", "UTF-8");
    char *in = (char *)utf8;
    char *out = sjis;
    size_t In_Size = strlen(utf8);
    size_t Out_Size = Buf_Size;

    if (iconv(ic, &in, &In_Size, &out, &Out_Size) == (size_t)-1)
	{
        perror("iconv failed");
    }
    iconv_close(ic);
}

//LEDの共通処理
volatile unsigned int* Map_Memory(off_t base_addr, size_t length, int *fd)
{
    volatile unsigned int* address = NULL;

    *fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (0 > *fd)
    {
        perror("open");
        return NULL;
    }

    address = (volatile unsigned int*)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, base_addr);
    if (address == (volatile unsigned int*)MAP_FAILED)
    {
        perror("mmap");
        close(*fd);
        return NULL;
    }

    return address;
}

//GPIO共通処理
void Configure_GPIO_Output(volatile unsigned int* address, int Fsel_Index, int Bit_Shift, int Pin_Number, unsigned int* Duplicate_Out, char Control_Value)
{
    unsigned int Clear_Mask = 7 << Bit_Shift;
    unsigned int Set_Mask   = 1 << Bit_Shift;
    unsigned int Output_Mask = 1 << Pin_Number;

    address[Fsel_Index] &= ~Clear_Mask;
    address[Fsel_Index] |= Set_Mask;
    address[GPSET0] = Output_Mask;

	if('3'>= Control_Value)
	{
		sleep(5);

		if (Duplicate_Out != NULL)
    	{
        	*Duplicate_Out = Output_Mask;
    	}
	}
	else if ('3' <= Control_Value)
    {
    	for (int i = 0; i < 5; i++)
    	{
        	address[GPSET0] = Output_Mask;  // LED ON
        	sleep(1);
        	address[GPCLR0] = Output_Mask;  // LED OFF
        	sleep(1);
    	}

    	if (Duplicate_Out != NULL)
    	{
        	*Duplicate_Out = Output_Mask;
    	}
	}
}

//メイン処理
int main(void)
{
	//サーバー側のソケット定義
	int Servsock = 0;
	//クライアント側のソケットを定義
	int Clitsock = 0;
	//サーバーのアドレス情報を格納
	struct sockaddr_in Servsockaddr;
	//クライアントのアドレス情報を格納
	struct sockaddr_in Clitsockaddr;
	//サーバーのポート
	unsigned short Servport = 8080;
	//クライアントのアドレス情報
	unsigned int Clitlen;
	//送受信に使う変数
	int Bytes_Received = 0;
	//データを送受信に使用されるバファ
	char Buffer[MAX_BUF] = {0};

	//ソケットの初期化
	if ((Servsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
	{
		perror("socket() failed.");
		exit(EXIT_FAILURE);
	}

	//構造体の初期化
	memset(&Servsockaddr, 0, sizeof(Servsockaddr));
	//アドレスファミリーを設定
	Servsockaddr.sin_family	= AF_INET;
	//接続要求を受け入れる
	Servsockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//ポートの設定
	Servsockaddr.sin_port = htons(Servport);

	//アプリケーションとの接続
	if (bind(Servsock, (struct sockaddr *) &Servsockaddr, sizeof(Servsockaddr) ) < 0 )
	{
		perror("bind() failed.");
		exit(EXIT_FAILURE);
	}

	//接続待ち
	if (listen(Servsock, QUEUELIMIT) < 0)
	{
		perror("listen() failed.");
		exit(EXIT_FAILURE);
	}

	//LCD
    int I2cd = 0;
    uint8_t Data;
    char Input[256];

    // I2Cデバイスのオープン
    if ((I2cd = open(I2C_DEVICE, O_RDWR)) < 0)
    {
        perror("Failed to open I2C device");
        return -1;
    }

     // I2Cアドレスの設定
    if (ioctl(I2cd, I2C_SLAVE, LCD_ADDR) < 0)
    {
        perror("Failed to set I2C address");
        close(I2cd);
        return -1;
    }
	
	Lcd_Initialize(I2cd);

	Clitlen = sizeof(Clitsockaddr);
	while(1)
	{
		//接続
		if ((Clitsock = accept(Servsock, (struct sockaddr *) &Clitsockaddr, &Clitlen)) < 0)
		{
			perror("accept() failed.");
			exit(EXIT_FAILURE);
		}

		//接続情報を表示
		printf("connected from %s.\n", inet_ntoa(Clitsockaddr.sin_addr));

		//データを受信
		memset(Buffer, 0, MAX_BUF ); //256
        int bytes_received = recv(Clitsock, Buffer,MAX_BUF, 0);//255
        if (bytes_received < 0) 
        {
			perror("recv() failed.");
            exit(EXIT_FAILURE);
        }

		//テスト
		printf("Bytes received: %d\n", bytes_received);		//バイトを表示

		for(int i = 0; i < bytes_received; i++)				//Bufferを表示
		{
    		printf("buffer[%d] = 0x%02X\n", i, Buffer[i]);
		}

		//文字列を格納
		char sjis_buf[MAX_BUF] = {0};
		//文字列をUTF-8からShift_JISに変換
        Convert_Utf8_To_Sjis(Buffer+2 , sjis_buf, sizeof(sjis_buf));

		//GPIOの機能設定用マスク
 		//int GPIO_Function_Select_Mask= 0;
		//GPIOをHIGHにするためのマスク
		//int GPIO_Set_Mask = 0;
		//GPIOをHIGHにするマスク
		int GPIO_Set_Mask_Duplicate= 0; 
        volatile unsigned int*  address;
        int fd = 0; 

		//判定処理
		if('1' == Buffer[0])
		{
			//赤の点灯
			if ('1' == Buffer[2])
			{
				printf("赤：点灯\n");

				address = Map_Memory(REG_ADDR_GPIO_BASE, REG_ADDR_GPIO_LENGTH, &fd);
				if (address == NULL)
				{
    				return -1;
				}
				
				Configure_GPIO_Output(address, GPFSEL2, 18, 26, &GPIO_Set_Mask_Duplicate, Buffer[2]);

			}

			//青の点灯
        	if ('2' == Buffer[2])
         	{
				printf("青：点灯\n");

				address = Map_Memory(REG_ADDR_GPIO_BASE, REG_ADDR_GPIO_LENGTH, &fd);
				if (address == NULL)
				{
    				return -1;
				}

				Configure_GPIO_Output(address, GPFSEL2, 18, 16, &GPIO_Set_Mask_Duplicate, Buffer[2]);
         	}

			//緑の点灯
         	if ('3' == Buffer[2])
         	{
				printf("緑：点灯\n");


				address = Map_Memory(REG_ADDR_GPIO_BASE, REG_ADDR_GPIO_LENGTH, &fd);
				if (address == NULL)
				{
    				return -1;
				}

				Configure_GPIO_Output(address, GPFSEL2, 15, 25, &GPIO_Set_Mask_Duplicate, Buffer[2]);
         	}

			//赤の点滅
         	if ('4' == Buffer[2])
         	{
            	printf("赤：点滅\n");

				address = Map_Memory(REG_ADDR_GPIO_BASE, REG_ADDR_GPIO_LENGTH, &fd);
				if (address == NULL)
				{
    				return -1;
				}

				Configure_GPIO_Output(address, GPFSEL2, 18, 26, &GPIO_Set_Mask_Duplicate, Buffer[2]);

         	}

			//青の点滅
        	if ('5' == Buffer[2])
         	{
             	printf("青：点滅\n");

				address = Map_Memory(REG_ADDR_GPIO_BASE, REG_ADDR_GPIO_LENGTH, &fd);
				if (address == NULL)
				{
    				return -1;
				}

				Configure_GPIO_Output(address, GPFSEL2, 18, 16, &GPIO_Set_Mask_Duplicate, Buffer[2]);
         	}

			//緑の点滅
          	if ('6' == Buffer[2])
          	{
            	printf("緑：点滅\n");
				address = Map_Memory(REG_ADDR_GPIO_BASE, REG_ADDR_GPIO_LENGTH, &fd);
    			if (address == NULL)
				{	
					return -1;
				}

				Configure_GPIO_Output(address, GPFSEL2, 15, 25, &GPIO_Set_Mask_Duplicate, Buffer[2]);				
			}
			
			//リセット
			address[GPCLR0] = GPIO_Set_Mask_Duplicate;
		    printf("Message from client: %s\n", Buffer);
		    //使い終わったリソースを解放する
		    munmap((void*)address, REG_ADDR_GPIO_LENGTH);
			//ソケットを閉じる
		    close(Clitsock);

		}
		//LCDの出力
		else if('2' == Buffer[0])
		{
			// LCDに受信データを表示
			Lcd_Display_String(I2cd, sjis_buf);
			
			close(Clitsock);
    	}
	
	}

	close(I2cd);

	return EXIT_SUCCESS;
}
