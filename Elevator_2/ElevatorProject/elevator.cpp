#include"elevator.h"
using namespace std;
const int N=5; //一组数据5个请求 
const int n=5; //测试5组数据 
int main()
{
	if (file_open())
	{
		for (int i=0;i<n;++i)
		{
			//建立5个乘客对象 
			passenger psg[N];
			//建立电梯对象
			elevator ele; 
			//建立控制中心对象
			console con; 
			int wait_time=0;
			//请求输入及处理
			if (con.ask_in(N,psg))
			{
				//电梯运行 
				while (!con.is_end(N,psg))
				{
					con.plan_check(ele);            //根据计划决定是否改向或待命
					con.ask_solve(N,psg,ele);       //查看当前时刻有无请求，并作出计划调整 
					wait_time+=con.stop(N,psg,ele); //检查此时是否需要停靠，并计算放出乘客的等待总时间
			        ele.floor_updata();             //电梯所在楼层更新 
			        con.time_updata();              //控制中心时间更新 
				}
				fout<<"乘客等待总时间:"<<wait_time<<"s\n\n"; 			
			}
			else 
			  return 0; 
		} 
		fout.close();	
		return 0;	
	}
    else 
    {
		cout<<"文件读取失败";  
		return 0;    	
	}
}
