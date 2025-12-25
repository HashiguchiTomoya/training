#include<stdio.h>
#include<string.h>

void my_erase_tall(char *str,int n)
{
	int len = strlen(str);

	if(n >= len)
	{
		str[0] = '\0';
	}
	else
	{
		str[len - n] = '\0';
	}
}

int main(void)
{
	char v1[] = "abcxyz";
	char v2[] = "abcxyz";
	char v3[] = "abcxyz";
	char v4[] = "abc";
	char v5[] = "";

	my_erase_tall(v1,3);
	printf("v1の内容：%s\n",v1);

	my_erase_tall(v2,4);
	printf("v2の内容：%s\n",v2);

	my_erase_tall(v3,0);
	printf("v3の内容：%s\n",v3);

	my_erase_tall(v4,6);
	printf("v4の内容：%s\n",v4);

	my_erase_tall(v5,3);
	printf("v5の内容：%s\n",v5);

	return 0;
}
