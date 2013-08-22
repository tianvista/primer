/*************************************************************************
    > File Name: rightshift.c
    > Author: wolf
    > Mail: tiandewei07@163.com 
    > Created Time: Thu 22 Aug 2013 02:27:32 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*将含有N个字符的字符串循环右移K*/
void right_shift(char *arr, int N, int K)
{
	int i;
	int tmp;

	K %= N;
	while(K--)
	{
		tmp = arr[N - 1];
		for(i = N - 1; i > 0; i--)
			arr[i] = arr[i - 1];
		arr[0] = tmp;
	}

}

int main(void)
{
	char array[20] = "abcdef123456";
	int len;
	int shift;

	printf("输入要循环右移的位数(大于0):");
	scanf("%d", &shift);
	if(shift < 0)
	{
		printf("循环右移位数输入错误");
		exit(-1);
	}
	printf("循环右移之前为:%s\n", array);
	right_shift(array, strlen(array), shift);

	printf("循环右移结果为:%s\n", array);

	return 0;

}
