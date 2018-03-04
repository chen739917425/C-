#ifndef elevator_H_
#define elevator_H_

#include<iostream>
#include<fstream>
using namespace std;
ofstream fout;
ifstream fin;
bool file_open()
{
	fin.open("./input.txt");
	if (!fin.fail())
	{
		fout.open("./output.txt");
		return true;
	}
	else
	  return false;  
} 
//�˿���
class passenger
{
	friend class console;
	public:
		passenger(int t=0,int s=0,int g=0,int ss=0):ask_time(t),start(s),goal(g),status(ss) //���캯�� 
		{} 
	    void set(int t,int s,int g) //��ʼ������         
	    {
	    	ask_time=t;
			start=s;
			goal=g; 
			return;
		}      
		int get_atime() const
		{
			return ask_time; 
		}
		int get_start() const
		{
			return start;
		}
		int get_goal() const
		{
			return goal;
		}
		int get_status() const
		{
			return status;
		}
		int get_wtime(int now_time) const //���㲢���س˿͵ȴ�ʱ�� 
		{
			return now_time-ask_time;
		}	   
		void change_status()
		{
			if (status<2)
			  ++status;
			return;
		}                                                       
	private:	
	    int ask_time,start,goal,status; //����ʱ�䣬��ʼ¥�㣬Ŀ��¥�㣬����״̬��0�ȴ���1�����ڣ�2��� 
};
//������ 
class elevator
{
	friend class console;
	public:
		elevator(int f=1,int d=0):floor(f),direction(d) {} //���캯�� 	 
		void change_direction() //���ݱ��� 
		{
			if (direction==1)
			  direction=2;
			else if (direction==2)
			  direction=1;  
			return;  
		}
		void change_direction(int d) //���ݶ��� 
		{
			direction=d;
			return;
	    }
		void floor_updata() //¥����� 
		{
			if (direction==1)
	        {
		       if (floor>1)
		        --floor;
	        }
	        else if (direction==2)
	        {
		       if (floor<10)
		        ++floor;
         	} 
		}	    
		int get_floor() const //���ص�ǰ����¥����
		{
		    return floor;
	    }
	private:
	    int floor,direction; //��������¥�㣬�����˶�״̬(0ͣ��1�£�2��)
}; 
//���������� 
class console 
{
	public:
		console(int t=0):time(t) //���캯��
		{
			for (int i=0;i<=10;++i)
			{
				plan[i]=0;
			}
		} 
		int get_time() //���ص�ǰʱ�� 
		{
			return time;
		} 
		void time_updata(int t=1) //ʱ����� 
		{
			time+=t;
		}
		void show(int f) //ͣ����Ϣ��� 
        {
	        fout<<time<<"ʱ��ͣ����"<<f<<"¥\n"; 
        }	
		bool ask_in(int N,passenger* psg);//��ȡ���󼰷Ƿ�������			
		bool pick(int N,passenger* p,elevator& ele); //�ж��Ƿ���Ҫ���� 
		int drop(int N,passenger* p,elevator& ele); //�ж��Ƿ���Ҫ���ˣ���������γ����ݵĳ˿͵ĵȴ���ʱ�� 
        int stop(int N,passenger* psg,elevator& ele); //����Ƿ���Ҫͣ�½��˻����,�ǵĻ�ִ�в����طų��˿͵ĵȴ���ʱ�� 
		void ask_solve(int N,const passenger* psg,elevator& ele); //����������
		void plan_check(elevator& ele); //�����ݵ�������¥����Ƿ���Ҫ���� 
		void plan_clear(int a,int b,int excp1,int excp2); //���¼ƻ� 
		bool is_end(int N,passenger* psg);//�ж��Ƿ����г˿Ͷ�����Ŀ��¥�� 
	private:
	    int time; //ʱ��
	    int plan[11]; //���������ÿһ��¥�����мƻ� 
		              //(0����ԭ״̬��1����,2ͣס,3ͣס�������ݣ�4ͣס�½�����,5�����������ݣ�6�����½�����)
}; 
bool console::ask_in(int N,passenger* psg)
{
	int t,s,g;
	while (N--)
	{
		fin>>t>>s>>g;
		if (t<0||s<1||s>10||g<1&&g>10||s==g)
		{
			cout<<"���Ϸ�����!";
			fout<<"���Ϸ�����!";
			fin.close();
			fout.close();
			return false; 
		}
		psg->set(t,s,g);
		psg++;
	}		
	return true;
}
bool console::pick(int N,passenger* p,elevator& ele)
{
	bool flag=false;
	for (int i=0;i<N;++i)
	{
		if (time>=p->get_atime()&&ele.get_floor()==p->get_start()&&p->status==0)
		{
			p->change_status();
			flag=true;
		}   
		p++;   
	}
	return flag;
} 
int console::drop(int N,passenger* p,elevator& ele)
{
	int wtime=0;
	for (int i=0;i<N;++i)
	{
		if (ele.get_floor()==p->get_goal()&&p->status==1)
		{
			p->change_status();
			wtime+=p->get_wtime(time);
		}   
		p++;   
	}
	return wtime;
}
int console::stop(int N,passenger* psg,elevator& ele)
{
    int temp;
    temp=drop(N,psg,ele); //t����ʱ����,��ŷų��˿͵ȴ���ʱ�� 
    if(pick(N,psg,ele)||temp)
    {
        show(ele.get_floor());
        time_updata();
        ask_solve(N,psg,ele);
    }
    return temp;	
}  
void console::ask_solve(int N,const passenger* psg,elevator& ele)
{
	int i,j,k;
	for (i=0;i<N;++i)
	{
		if (time==psg->get_atime())
		{
			if (psg->get_start()>=ele.get_floor()) //���˿�����¥����ڵ��ڵ�������¥��ʱ
			{
				if (ele.direction==0) //������û������ 
				{
					ele.direction=2; //��������׼������ 
				}   
				else if (ele.direction==1) //���������½� 
				{
				    //�½���ͣס¥���������� 
					for (j=1;j<ele.get_floor();++j) 
					{
						if (plan[j]==2||plan[j]==4)
						{
							plan[j]=1;
							break;
						}
					} 	
				}					
				if (psg->get_start()>psg->get_goal()) //���˿�Ҫ��¥
				{
					//���¸���� 
					for (j=10;j>1;--j)
					{
						if (plan[j]!=0&&plan[j]!=4&&plan[j]!=6)
						  break;
					}
					if (j<psg->get_start())
					{
						plan_clear(1,psg->get_start(),4,6); //���֮ǰ�ĸ����ͣס�ƻ�	
						plan[psg->get_start()]=1;
					} 
					else 
					{
						plan[j]=1;
					}
					//����ͣ���� 
					for (j=1;j<psg->get_start();++j)
					{
						if (plan[j]!=0&&plan[j]!=3&&plan[j]!=5)
						  break;
					}
					if (j>psg->get_goal())
					{
						if ((plan[j]==1||plan[j]==6)&&j!=psg->get_start())
						{
							plan_clear(psg->get_goal(),psg->get_start(),3,5); //���֮ǰ�ĸ����ͣ���ƻ� 	 
							plan[psg->get_goal()]=6;								
						}
                        else 
						{
						    plan_clear(psg->get_goal(),psg->get_start(),3,5); //���֮ǰ�ĸ����ͣ���ƻ� 	 
							plan[psg->get_goal()]=4;						
						}		                               
					}
				} 
				else //���˿�Ҫ��¥ 
				{
					//����ͣ���� 
					for (j=10;j>ele.get_floor();--j)
					{
						if (plan[j]!=0&&plan[j]!=4&&plan[j]!=6)
						  break;
					} 
					if (j<psg->get_goal())
					{
						if (plan[j]==1||plan[j]==5)
						{
							plan_clear(ele.get_floor(),psg->get_goal(),4,6);
							plan[psg->get_goal()]=1;								
						}
	                    else
	                    {
	                    	plan_clear(ele.get_floor(),psg->get_goal(),4,6);
	                    	plan[psg->get_goal()]=2;
						}
					}
				}    					
			} 
			else if (psg->get_start()<ele.get_floor()) //���˿�����¥����ڵ�������¥��ʱ
			{
				if (ele.direction==0) //������û������ 
				{
					ele.direction=1; //��������׼���½�
				} 				
				else if (ele.direction==2) //������������ 
				{
				    //������ͣס¥���������� 
					for (j=10;j>ele.get_floor();--j) 
					{
						if (plan[j]==2||plan[j]==3)
						{
							plan[j]=1;
							break;
						}
					} 	
				} 
				if (psg->get_start()<psg->get_goal()) //���˿�Ҫ��¥
				{
					//���¸���� 
					for (j=1;j<10;++j)
					{
						if (plan[j]!=0&&plan[j]!=3&&plan[j]!=5)
						  break;
					}
					if (j>psg->get_start())
					{
						plan_clear(psg->get_start(),10,3,5); //���֮ǰ�ĸ����ͣס�ƻ� 
						plan[psg->get_start()]=1;	
					} 
					else 
					{
						plan[j]=1;
					}
					//����ͣ���� 
					for (j=10;j>psg->get_start();--j)
					{
						if (plan[j]!=0&&plan[j]!=4&&plan[j]!=6)
						  break;
					}
					if (j<psg->get_goal())
					{
						if ((plan[j]==1||plan[j]==5)&&j!=psg->get_start())
						{
							plan_clear(psg->get_start(),psg->get_goal(),4,6); //���֮ǰ�ĸ����ͣ���ƻ� 	 
							plan[psg->get_goal()]=5;								
						}
                        else 
						{
						    plan_clear(psg->get_start(),psg->get_goal(),4,6); //���֮ǰ�ĸ����ͣ���ƻ� 	 
							plan[psg->get_goal()]=3;						
						}		                               
					}
				}
				else //���˿�Ҫ��¥ 
				{
					//����ͣ���� 
					for (j=1;j<ele.get_floor();++j)
					{
						if (plan[j]!=0&&plan[j]!=3&&plan[j]!=5)
						  break;
					} 
					if (j>psg->get_goal())
					{
						if (plan[j]==1)
						{
							plan_clear(psg->get_goal(),ele.get_floor(),3,5);
							plan[psg->get_goal()]=1;								
						}
                        else
                        {
                        	plan_clear(psg->get_goal(),ele.get_floor(),3,5);
                        	plan[psg->get_goal()]=2;
						}
					}						
				} 					
		    }
	    }
		psg++;
	}
	return;
}   
void console::plan_check(elevator& ele)
{
	switch(plan[ele.get_floor()])
	{
		case 1: ele.change_direction();
		        plan[ele.get_floor()]=0;
				break;
		case 2: ele.change_direction(0);
		        plan[ele.get_floor()]=0;
				break;
		case 3: if (ele.direction==2) 
		        {
		        	ele.change_direction(0); 
		        	plan[ele.get_floor()]=0;
				}  
				break;
		case 4: if (ele.direction==1) 
		        {
		        	ele.change_direction(0);
		        	plan[ele.get_floor()]=0;
				}				
				break;
		case 5: if (ele.direction==2)
		        {
			        ele.change_direction();
			        plan[ele.get_floor()]=0;  		        	
				}
		        break;  
		case 6: if (ele.direction==1)
		        {
				  	ele.change_direction();
					plan[ele.get_floor()]=0;				        	
				}
			  	break;  
		default: break;
	}
	return;
} 
void console::plan_clear(int a,int b,int excp1,int excp2)
{
	int i;
	for (i=a+1;i<b;++i)
	{
		if (plan[i]!=0&&plan[i]!=excp1&&plan[i]!=excp2)
		  plan[i]=0;
	}
	return;
} 
bool console::is_end(int N,passenger* psg)
{
	for (int i=0;i<N;++i)
	{
		if (psg->get_status()!=2)
		  return false;
		psg++;  
	}
	return true;
}  

#endif
