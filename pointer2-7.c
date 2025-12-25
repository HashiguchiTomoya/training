#include <stdio.h>
#include <string.h>

void my_erase_head(char *str,int n)
{
	int len = strlen(str);

	if(n >= len)
	{
		str[0] = '\0';
	}
	else
	{
		memmove(str,str + n,len -n +1);
	}
}

int main(void)
{
	char v1[] = "abcxyz";
	char v2[] = "abcxyz";
	char v3[] = "abcxyz";
	char v4[] = "abc";
	char v5[] = "";

	my_erase_head(v1,3);
	printf("v1の内容:%s\n",v1);

	my_erase_head(v2,4);
	printf("v2の内容：%s\n",v2);

	my_erase_head(v3,0);
	printf("v3の内容：%s\n",v3);

	my_erase_head(v4,6);
	printf("v4の場合：%s\n",v4);

	my_erase_head(v5,7);
	printf("v5の場合：%s\n",v5);
	
}
