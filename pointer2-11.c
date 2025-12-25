#include<stdio.h>
#include<string.h>

char my_pop_back(char *str)
{
	int len = strlen(str);

	if(len == 0)
	{
		return '\0';
	}

	char lest_char = str[len - 1];
	str[len - 1] = '\0';
	return lest_char;
}

int main(void)
{
	char buf[] = "abcd";

	char popped = my_pop_back(buf);
	printf("削除した文字：'%c',bufの内容:%s\n",popped,buf);

	popped = my_pop_back(buf);
	printf("削除した文字：'%c',bufの内容:%s\n",popped,buf);

	popped = my_pop_back(buf);
	printf("削除した文字：'%c',bufの内容：%s\n",popped,buf);

	popped = my_pop_back(buf);
	printf("削除した文字：'%c',bufの内容：%s\n",popped,buf);

	popped = my_pop_back(buf);
	printf("削除した文字：'%c',bufの内容：%s\n",popped,buf);

	return 0;
}
