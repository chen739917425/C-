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
//乘客类
class passenger
{
	friend class console;
	public:
		passenger(int t=0,int s=0,int g=0,int ss=0):ask_time(t),start(s),goal(g),status(ss) //构造函数 
		{} 
	    void set(int t,int s,int g) //初始化函数         
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
		int get_wtime(int now_time) const //计算并返回乘客等待时间 
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
	    int ask_time,start,goal,status; //请求时间，起始楼层，目标楼层，所处状态（0等待，1电梯内，2到达） 
};
//电梯类 
class elevator
{
	friend class console;
	public:
		elevator(int f=1,int d=0):floor(f),direction(d) {} //构造函数 	 
		void change_direction() //电梯变向 
		{
			if (direction==1)
			  direction=2;
			else if (direction==2)
			  direction=1;  
			return;  
		}
		void change_direction(int d) //电梯定向 
		{
			direction=d;
			return;
	    }
		void floor_updata() //楼层更新 
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
		int get_floor() const //返回当前所在楼层数
		{
		    return floor;
	    }
	private:
	    int floor,direction; //电梯所在楼层，电梯运动状态(0停，1下，2上)
}; 
//控制中心类 
class console 
{
	public:
		console(int t=0):time(t) //构造函数
		{
			for (int i=0;i<=10;++i)
			{
				plan[i]=0;
			}
		} 
		int get_time() //返回当前时间 
		{
			return time;
		} 
		void time_updata(int t=1) //时间更新 
		{
			time+=t;
		}
		void show(int f) //停靠信息输出 
        {
	        fout<<time<<"时，停靠在"<<f<<"楼\n"; 
        }	
		bool ask_in(int N,passenger* psg);//读取请求及非法请求处理			
		bool pick(int N,passenger* p,elevator& ele); //判断是否需要接人 
		int drop(int N,passenger* p,elevator& ele); //判断是否需要放人，并返回这次出电梯的乘客的等待总时间 
        int stop(int N,passenger* psg,elevator& ele); //检查是否需要停下接人或放人,是的话执行并返回放出乘客的等待总时间 
		void ask_solve(int N,const passenger* psg,elevator& ele); //处理请求函数
		void plan_check(elevator& ele); //检查电梯到达所在楼层后是否需要改向； 
		void plan_clear(int a,int b,int excp1,int excp2); //更新计划 
		bool is_end(int N,passenger* psg);//判断是否所有乘客都到达目的楼层 
	private:
	    int time; //时间
	    int plan[11]; //储存电梯在每一层楼的运行计划 
		              //(0保持原状态，1改向,2停住,3停住上升电梯，4停住下降电梯,5改向上升电梯，6改向下降电梯)
}; 
bool console::ask_in(int N,passenger* psg)
{
	int t,s,g;
	while (N--)
	{
		fin>>t>>s>>g;
		if (t<0||s<1||s>10||g<1&&g>10||s==g)
		{
			cout<<"不合法请求!";
			fout<<"不合法请求!";
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
    temp=drop(N,psg,ele); //t作临时变量,存放放出乘客等待总时间 
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
			if (psg->get_start()>=ele.get_floor()) //若乘客所在楼层高于等于电梯所处楼层时
			{
				if (ele.direction==0) //若电梯没有启动 
				{
					ele.direction=2; //驱动电梯准备上升 
				}   
				else if (ele.direction==1) //若电梯在下降 
				{
				    //下降到停住楼层后改向向上 
					for (j=1;j<ele.get_floor();++j) 
					{
						if (plan[j]==2||plan[j]==4)
						{
							plan[j]=1;
							break;
						}
					} 	
				}					
				if (psg->get_start()>psg->get_goal()) //若乘客要下楼
				{
					//更新改向点 
					for (j=10;j>1;--j)
					{
						if (plan[j]!=0&&plan[j]!=4&&plan[j]!=6)
						  break;
					}
					if (j<psg->get_start())
					{
						plan_clear(1,psg->get_start(),4,6); //清除之前的改向或停住计划	
						plan[psg->get_start()]=1;
					} 
					else 
					{
						plan[j]=1;
					}
					//更新停靠点 
					for (j=1;j<psg->get_start();++j)
					{
						if (plan[j]!=0&&plan[j]!=3&&plan[j]!=5)
						  break;
					}
					if (j>psg->get_goal())
					{
						if ((plan[j]==1||plan[j]==6)&&j!=psg->get_start())
						{
							plan_clear(psg->get_goal(),psg->get_start(),3,5); //清除之前的改向或停靠计划 	 
							plan[psg->get_goal()]=6;								
						}
                        else 
						{
						    plan_clear(psg->get_goal(),psg->get_start(),3,5); //清除之前的改向或停靠计划 	 
							plan[psg->get_goal()]=4;						
						}		                               
					}
				} 
				else //若乘客要上楼 
				{
					//更新停靠点 
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
			else if (psg->get_start()<ele.get_floor()) //若乘客所在楼层低于电梯所处楼层时
			{
				if (ele.direction==0) //若电梯没有启动 
				{
					ele.direction=1; //驱动电梯准备下降
				} 				
				else if (ele.direction==2) //若电梯在上升 
				{
				    //上升到停住楼层后改向向下 
					for (j=10;j>ele.get_floor();--j) 
					{
						if (plan[j]==2||plan[j]==3)
						{
							plan[j]=1;
							break;
						}
					} 	
				} 
				if (psg->get_start()<psg->get_goal()) //若乘客要上楼
				{
					//更新改向点 
					for (j=1;j<10;++j)
					{
						if (plan[j]!=0&&plan[j]!=3&&plan[j]!=5)
						  break;
					}
					if (j>psg->get_start())
					{
						plan_clear(psg->get_start(),10,3,5); //清除之前的改向或停住计划 
						plan[psg->get_start()]=1;	
					} 
					else 
					{
						plan[j]=1;
					}
					//更新停靠点 
					for (j=10;j>psg->get_start();--j)
					{
						if (plan[j]!=0&&plan[j]!=4&&plan[j]!=6)
						  break;
					}
					if (j<psg->get_goal())
					{
						if ((plan[j]==1||plan[j]==5)&&j!=psg->get_start())
						{
							plan_clear(psg->get_start(),psg->get_goal(),4,6); //清除之前的改向或停靠计划 	 
							plan[psg->get_goal()]=5;								
						}
                        else 
						{
						    plan_clear(psg->get_start(),psg->get_goal(),4,6); //清除之前的改向或停靠计划 	 
							plan[psg->get_goal()]=3;						
						}		                               
					}
				}
				else //若乘客要下楼 
				{
					//更新停靠点 
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
