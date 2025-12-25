#include <stdio.h>
#include <string.h>

char my_pop_front(char *str)
{
	int len = strlen(str);

	if(len == 0)
	{
		return '\0';
	}

	char first_char = str[0];
	memmove(str,str + 1,len);

	return first_char;
}

int main(void)
{
	char buf[] = "abcd";

	char popped = my_pop_front(buf);
	printf("削除された文字：'%c',bufの内容：%s\n",popped,buf);

	popped = my_pop_front(buf);
	printf("削除された文字：'%c',bufの内容：%s\n",popped,buf);

	popped = my_pop_front(buf);
	printf("削除された文字：'%c',bufの内容：%s\n",popped,buf);

	popped = my_pop_front(buf);
	printf("削除された文字：'%c',bufの内容：%s\n",popped,buf);

	popped = my_pop_front(buf);
	printf("削除された文字：'%c',bufの内容：%s\n",popped,buf);

	return 0;
}
