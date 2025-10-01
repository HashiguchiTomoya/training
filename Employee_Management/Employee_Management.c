#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//社員名簿の構造体
struct employee
{
	int id; 	//社員番号
	char name[20];	//名前
	int age;	//年齢
	int joinday;	//入社日
	struct employee *next; //次の社員のポインタ
};

//リストを追加するための関数
int addList(struct employee **list, struct employee *sp)
{
	//現リストのループ用
	struct employee* roop_list;
	//追加リスト
	struct employee* add_list;

	//追加リストがなかったら何もしない
	if(sp == NULL)
	{
		return 0;
	}

	//追加リストの領域確保
	add_list = (struct employee *)malloc(sizeof(struct employee));

	//追加リストの領域が確保できなかったら何もしない
	if(add_list == NULL)
	{
		return 0;
	}
	else
	{
		//追加リストのデータをコピー
		add_list -> id = sp ->id;
		strcpy(add_list -> name, sp -> name);
		add_list -> age = sp -> age;
		add_list -> joinday = sp -> joinday;
		add_list -> next = NULL;

		if(*list == NULL)
		{
			*list = add_list;
		}
		else
		{
			//追加リストを一番最後に追加
			roop_list = *list;
			while(roop_list -> next != NULL)
			{
				roop_list = roop_list -> next;
			}

			roop_list -> next = add_list;
		}
	}

	return 1;
}

//指定リストを削除する関数
void deleteList(struct employee **list, int pos)
{
	if(*list == NULL)
	{
		return;
	}

	struct employee *current = *list;
	struct employee *prev = NULL;

	for(int i = 0; current != NULL; i++)
	{
		if(i == pos)
		{
			if(prev == NULL)
			{
				*list = current -> next;
			}
			else
			{
				prev -> next = current -> next;
			}

			free(current);
			return;
		}

		prev = current;
		current = current -> next;
	}
}

//リストをすべて削除する場合
void deleteListAll(struct employee **list)
{
	struct employee *current = *list;
	while(current != NULL)
	{
		struct employee *next = current -> next;
		free(current);
		current = next;
	}
	*list = NULL;
}

//起動時にテキストファイルを読み込む
void loadList(struct employee **list)
{
	FILE *fp = fopen("Employee_Management.txt", "r");
	if(fp == NULL)
	{
		printf("ファイルが見つかりませんでした。\n");
		return;
	}
	
	struct employee tmp;
	while(fscanf(fp, "[%*d]社員番号：%d\n", &tmp.id) == 1)
	{
		fscanf(fp, "名前：%s\n", tmp.name);
		fscanf(fp, "年齢：%d\n", &tmp.age);
		fscanf(fp, "入社日：%d\n\n", &tmp.joinday);
		addList(list, &tmp);
	}

	fclose(fp);

}

int main(void)
{
	//社員リスト情報
	struct employee *data;
	//退避用
	struct employee *tmp;
	//追加社員情報
	struct employee add_data;
	//削除する生徒のリスト番号
	int del_pos;
	//操作選択
	int select;

	data = NULL;
	loadList(&data);

	//操作選択
	while(1)
	{
		printf("操作を選んでください\n");
		printf("１：表示\n");
		printf("２：登録\n");
		printf("３：修正\n");
		printf("４：削除\n");
		printf("５：終了\n");
		scanf("%d", &select);

		switch(select)
		{
			//表示
			case 1:
				tmp = data;
				int index = 0;
				while(tmp != NULL)
				{
					printf("\n[%d]社員番号：%d\n", index, tmp -> id);
					printf("名前：%s\n", tmp -> name);
					printf("年齢：%d\n", tmp -> age);
					printf("入社日：%d\n", tmp -> joinday);
					tmp = tmp -> next;
					index ++;
				}
				break;
			//登録
			case 2:
				printf("社員番号：");
				scanf("%d", &add_data.id);
				printf("名前：");
				scanf("%s", add_data.name);
				printf("年齢：");
				scanf("%d", &add_data.age);
				printf("入社日：");
				scanf("%d", &add_data.joinday);
				addList(&data, &add_data);
				break;

			//修正
			case 3:
				printf("修正するリスト番号");
				scanf("%d", &del_pos);

				struct employee *current = data;
				index = 0;

				while(current != NULL)
				{
					if(index == del_pos)
					{
						printf("新しい社員番号(現在：%d)：", current -> id);
						scanf("%d", &current -> id);
						printf("新しい名前(現在：%s)：", current -> name);
						scanf("%s", current -> name);
						printf("新しい年齢(現在：%d)：", current -> age);
						scanf("%d", &current -> age);
						printf("新しい入社日(現在%d：)：", current -> joinday);
						scanf("%d", &current -> joinday);

						printf("編集が完了しました\n");
						break;
					}

					current = current -> next;
					index++;
				}
				if(current == NULL)
				{
					printf("指定された番号は見つかりませんでした\n");
				}
				break;
			
			//削除
			case 4:
				printf("削除するリスト番号：");
				scanf("%d", &del_pos);
				deleteList(&data, del_pos);
				break;

			//ファイル保存、終了
			case 5:
				FILE *fp = fopen("Employee_Management.txt", "w");
				if(fp == NULL)
				{
					printf("ファイルの出力に失敗しました。");
				}
				else
				{
					struct employee *current = data;
					index = 0;
					while(current != NULL)
					{
						fprintf(fp, "[%d]社員番号：%d\n", index, current -> id);
						fprintf(fp, "名前：%s\n", current -> name);
						fprintf(fp, "年齢：%d\n", current -> age);
						fprintf(fp, "入社日：%d\n\n", current -> joinday);
						current = current -> next;
						index++;
					}
					fclose(fp);
					printf("社員情報を保存しました。\n");
				}
				deleteListAll(&data);
				printf("終了します\n");
				exit(0);
			
			//無効な値
			default:
				printf("無効な選択です\n");
				break;
		}
	}
}
