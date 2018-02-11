#include<iostream>
#include<cstdio>
#include<climits>
#include"elevator.h"
using namespace std;
//建立5个乘客对象 
const int N=5; 
passenger psg[N+1];
//建立电梯对象
elevator ele; 
//决策算法函数 
int solve(const int* plan,int n)
{
	
	
}
//生成h到n-1的全排列，枚举各种接客的顺序 
bool used[N+5];
int perm[N+5];
void permutation(int pos,int h,int n,int (*fun)(const int*,int))
{
	if (pos==n-h)
	{
		fun(perm,n-h);
		return;
	}
	for (int i=h;i<n;++i)
	{
		if (!used[i])
		{
			perm[pos]=i;
			used[i]=true;
			permutation(pos+1,h,n,fun);
			used[i]=false;
		}
	}
} 
//为贴近现实，先为乘客按请求时间顺序排序 
void insert_sort(passenger* p)
{
	passenger temp;
	int t,i,j;
	for (i=1;i<N;++i)
	{
		temp=psg[i];
		t=psg[i].a_time();
		j=i-1;
		while (j>=0&&psg[j].a_time()>t)
		{
			psg[j+1]=psg[j];
			--j;
		}
		psg[j+1]=temp;
	} 
	return;
} 
int main()
{
	int i,count,time=0,wait_time=0,drt=1,t,s,g;
	//请求输入及非法输入处理 
	for (i=0;i<N;++i)
	{
		cin>>t>>s>>g;
		while (t<0||s<1||s>10||g!=0&&g!=1)
		{
			cout<<"不合法请求，请重新输入：\n" ;
			cin>>t>>s>>g; 
		}
		psg[i].set(t,s,g);
	}
	insert_sort(psg); //排序 
	i=0; 
	while (!(ele.is_empty()&&ele.is_accomplished(N))) //电梯要运行到电梯内没人且已经接过5个人 
	{
		//计算该时刻有多少条请求
		count=0; 
		while (i<N&&psg[i].a_time()==time)
	    {
	    	++i;
	    	++count;
		}   
		//分类做对应状态更新 
		if (count==0)
		{
			ele.updata(drt,0,0,0);
			++time;
		}  
		else
		{
			permutation(0,i-count,i,solve); //枚举当前时刻接客的所有顺序 
	        ele.updata(); 
			++time;
		}  
	}
	return 0;
}
