#include <stdio.h>
#include <string.h>

void my_push_back(char *str,char c)
{
	if(c == '\0')
	{
		return ;
	}

	int len = strlen(str);
	str[len] = c;
	str[len + 1] = '\0';
}

int main(void)
{
	char buf[10] = "";

	my_push_back(buf,'1');
	printf("bufの内容：%s\n",buf);

	my_push_back(buf,'2');
	printf("bufの内容：%s\n",buf);

	my_push_back(buf,'3');
	printf("bufの内容：%s\n",buf);

	my_push_back(buf,'\0');
	printf("bufの内容：%s\n",buf);

	return 0;
}
