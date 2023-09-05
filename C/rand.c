/*
用C语言程序输出指定范围的不重复的随机数
本程序以输出50个范围为1-50的不重复的随机数为例 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int a[26],i=0,j,r;
	srand((int)time(0));   //用当前时间作为随机种子 
	while(i<26)
	{
		r=rand() % 26 + 1;  //生成一个1-26的随机数 
		for(j=i;j>=0;j--)
		{
			if(r==a[j])     //与之前已存的随机数比较 
				break;
		}
		if(j<0)             //没有重复即保存到数组中 
		{
			a[i]=r;
			i++;
		}
	}
	while (i--)            //从数组中输出这26个范围在1-26的不重复的随机数 
	{
		printf(" %d,",a[i]);
		//getchar();	
	}
	
	//system("pause");
	return 0;
}
