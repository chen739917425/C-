#ifndef elevator_H_
#define elevator_H_
 
//乘客类
class passenger
{
	public:
		passenger(int t=0,int s=0,int g=0):ask_time(t),start(s),goal(g) //构造函数 
		{} 
	    void set(int t,int s,int g) //初始化函数         
	    {
	    	ask_time=t;
			start=s;
			goal=g; 
		}      
		int a_time() 
		{
			return ask_time; 
		}
		int s_floor()
		{
			return start;
		}
		int g_floor()
		{
			return goal;
		}
		int w_time(int now_time) //计算并返回乘客等待时间 
		{
			return now_time-ask_time;
		}	                                                          
	private:	
	    int ask_time,start,goal; //请求时间，起始楼层，目标楼层
};
//电梯类 
class elevator
{
	public:
		elevator(int f=1,int u=0,int d=0,int e=0):floor(f),up_num(u),down_num(d),enter_num(e) //构造函数 
		{} 
		void updata(bool,int,int,int);  //电梯状态更新函数 
		bool is_empty()             //判断电梯是否为空 
		{
			if (up_num==0&&down_num==0)
			  return true;
			else
			  return false;  
		}
		bool is_accomplished(int n) //判断电梯是否已接过n个人 
		{
			if (enter_num==n)
			  return true;
			else
			  return false;  
		} 
	private:
	    int floor,up_num,down_num,enter_num; //电梯所在楼层，电梯内上10F的人数，电梯内下1F的人数，进入过电梯的人数 
}; 
void elevator::updata(bool drt,int up_change,int down_change,int enter_change)
{
	if (drt)
	{
		if (floor>1)
		  --floor;
	}
	else
	  ++floor; //更新所在楼层 
	up_num+=up_change; //更新电梯内要上10F的人数
	down_num+=down_change; //更新电梯内要下1F的人数    
	enter_num+=enter_change; //更新进入过电梯的人数
}

#endif
