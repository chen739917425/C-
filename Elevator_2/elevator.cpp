#include"elevator.h"
using namespace std;
const int N=5; //һ������5������ 
const int n=5; //����5������ 
int main()
{
	if (file_open())
	{
		for (int i=0;i<n;++i)
		{
			//����5���˿Ͷ��� 
			passenger psg[N];
			//�������ݶ���
			elevator ele; 
			//�����������Ķ���
			console con; 
			int wait_time=0;
			//�������뼰����
			if (con.ask_in(N,psg))
			{
				//�������� 
				while (!con.is_end(N,psg))
				{
					con.plan_check(ele);            //���ݼƻ������Ƿ��������
					con.ask_solve(N,psg,ele);       //�鿴��ǰʱ���������󣬲������ƻ����� 
					wait_time+=con.stop(N,psg,ele); //����ʱ�Ƿ���Ҫͣ����������ų��˿͵ĵȴ���ʱ��
			        ele.floor_updata();             //��������¥����� 
			        con.time_updata();              //��������ʱ����� 
				}
				fout<<"�˿͵ȴ���ʱ��:"<<wait_time<<"s\n\n"; 			
			}
			else 
			  return 0; 
		} 
		fout.close();	
		return 0;	
	}
    else 
    {
		cout<<"�ļ���ȡʧ��";  
		return 0;    	
	}
}
