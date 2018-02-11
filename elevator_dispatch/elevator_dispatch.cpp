#include<iostream>
#include<cstdio>
#include<climits>
#include"elevator.h"
using namespace std;
//����5���˿Ͷ��� 
const int N=5; 
passenger psg[N+1];
//�������ݶ���
elevator ele; 
//�����㷨���� 
int solve(const int* plan,int n)
{
	
	
}
//����h��n-1��ȫ���У�ö�ٸ��ֽӿ͵�˳�� 
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
//Ϊ������ʵ����Ϊ�˿Ͱ�����ʱ��˳������ 
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
	//�������뼰�Ƿ����봦�� 
	for (i=0;i<N;++i)
	{
		cin>>t>>s>>g;
		while (t<0||s<1||s>10||g!=0&&g!=1)
		{
			cout<<"���Ϸ��������������룺\n" ;
			cin>>t>>s>>g; 
		}
		psg[i].set(t,s,g);
	}
	insert_sort(psg); //���� 
	i=0; 
	while (!(ele.is_empty()&&ele.is_accomplished(N))) //����Ҫ���е�������û�����Ѿ��ӹ�5���� 
	{
		//�����ʱ���ж���������
		count=0; 
		while (i<N&&psg[i].a_time()==time)
	    {
	    	++i;
	    	++count;
		}   
		//��������Ӧ״̬���� 
		if (count==0)
		{
			ele.updata(drt,0,0,0);
			++time;
		}  
		else
		{
			permutation(0,i-count,i,solve); //ö�ٵ�ǰʱ�̽ӿ͵�����˳�� 
	        ele.updata(); 
			++time;
		}  
	}
	return 0;
}
