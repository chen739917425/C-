#ifndef elevator_H_
#define elevator_H_
 
//�˿���
class passenger
{
	public:
		passenger(int t=0,int s=0,int g=0):ask_time(t),start(s),goal(g) //���캯�� 
		{} 
	    void set(int t,int s,int g) //��ʼ������         
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
		int w_time(int now_time) //���㲢���س˿͵ȴ�ʱ�� 
		{
			return now_time-ask_time;
		}	                                                          
	private:	
	    int ask_time,start,goal; //����ʱ�䣬��ʼ¥�㣬Ŀ��¥��
};
//������ 
class elevator
{
	public:
		elevator(int f=1,int u=0,int d=0,int e=0):floor(f),up_num(u),down_num(d),enter_num(e) //���캯�� 
		{} 
		void updata(bool,int,int,int);  //����״̬���º��� 
		bool is_empty()             //�жϵ����Ƿ�Ϊ�� 
		{
			if (up_num==0&&down_num==0)
			  return true;
			else
			  return false;  
		}
		bool is_accomplished(int n) //�жϵ����Ƿ��ѽӹ�n���� 
		{
			if (enter_num==n)
			  return true;
			else
			  return false;  
		} 
	private:
	    int floor,up_num,down_num,enter_num; //��������¥�㣬��������10F����������������1F����������������ݵ����� 
}; 
void elevator::updata(bool drt,int up_change,int down_change,int enter_change)
{
	if (drt)
	{
		if (floor>1)
		  --floor;
	}
	else
	  ++floor; //��������¥�� 
	up_num+=up_change; //���µ�����Ҫ��10F������
	down_num+=down_change; //���µ�����Ҫ��1F������    
	enter_num+=enter_change; //���½�������ݵ�����
}

#endif
