#include <stdio.h>
#include <string.h>

void my_push_front(char *str,char c)
{
	if(c == '\0')
	{
		return;
	}

	int len = strlen(str);

	memmove(str + 1,str,len +1);

	str[0] = c;
}

int main(void)
{
	char buf[10] = "";

	my_push_front(buf,'1');
	printf("bufの内容：%s\n",buf);

	my_push_front(buf,'2');
	printf("bufの内容：%s\n",buf);

	my_push_front(buf,'3');
	printf("bufの内容：%s\n",buf);

	my_push_front(buf,'\0');
	printf("bufの内容：%s\n",buf);

	return 0;
}
