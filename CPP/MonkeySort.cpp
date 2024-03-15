#include <iostream>
#include <random>
 
using namespace std;
 
int n = 0;
bool judgeSort(int *arry,int *randarr,int n)
{
	for (int i = 0; i < n-1; i++)
	{
		if (arry[randarr[i+1]] < arry[randarr[i]])
		{
			return false;
		}
	}
	return true;
	
}
 
 
 
void MonkeySort1(int n,int *arry)
{
 
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, n-1);
 
	int *randarr = new int[n];
	int count = 1;
	bool judge = false;
 
	while (judge == false)
	{
		cout << "第" << count << "遍猴子排序" << endl;
		//生成10个随机数存储在randarr数组里面
		for (int i = 0; i < n; i++)
		{
			randarr[i] = distribution(generator);
 
			for (int j = 0; j < i; j++)
			{
 
				if (randarr[j] == randarr[i])
				{
 
					i--;
					break;
				}
			}
 
		}
 
		
 
		for (int j = 0; j <n; j++)
		{
			cout << arry[randarr[j]] << endl;
		}
 
		judge = judgeSort(arry, randarr,n);
 
		if (judge == false)
		{
			cout << "无序序列" << endl;
		}
		else
		{
			cout << "有序序列" << endl;
 
		}
		count++;
	}
}
 
 
 
 
int main()
{
	cin >> n;
	int *p = new int[n];
 
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}
	MonkeySort1(n,p);
 
	system("pause");
	return 0;
}
