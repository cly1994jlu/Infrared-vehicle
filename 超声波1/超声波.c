#include<reg51.h>
#include<intrins.h>
sbit bit11=P2^0;  //温湿度传感器数据传输
sbit Tx0=P3^1;//前向超声波产生脉冲引脚，延时 20us
sbit Rx0=P3^3;//回波引脚，进入外部中断 1
sbit Tx1=P3^4;//后向超声波产生脉冲引脚，延时 20us
sbit Rx1=P3^5;//回波引脚，进入外部中断 1
bit b;			  //超声波定时器计数标志位
long Th0,Tl0;	  //定时器0计数数值
unsigned long time0=0,time2=0; //定时器0计数数值之和
unsigned int Del20us=0;//延时变量，在超声波脉冲引脚中产生 20us 的方波
unsigned int M0=0,M1=0;//超声波测试距离
unsigned char U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;//温湿度传感器接收数据

void DelayMs(unsigned int x)   //延时函数，0.14ms误差 0us
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++)
		{}
	}
}
void Delay_us(unsigned char n) //N us 延时函数精度±4us
{
  n=n/2;
  while(--n);
}
void Measure0() //前向测距
	{
		b=1;				 //初始化中断溢出值
		TR0=0;				//关定时器 0
		TH0=0;				//赋定时器初始值高 8 位为 0
		TL0=0;				//赋定时器初始值低 8 位为 0
		Tx0=1;				//拉高超声波脉冲引脚电位
		for(Del20us=20;Del20us>0;Del20us--);  		//延时 20us
		Tx0=0;        				//拉低超声波脉冲引脚电位，使之产生 20us 的方波信号，使超声波模块开始工作。
		while(Rx0==0);     				//等待回波引脚变 1接受脉冲；
		TR0=1;				//开定时器0，开始计数
		while(Rx0==1);				  	//等待回波引脚变 0接受脉冲；
			Th0=TH0;					//读取时间
			Tl0=TL0;				   
			while(!b);				  //等待中断溢出
			time0=Th0*256+Tl0; 
			M0=(17*time0)/1100;		//测量的结果单位为 cm
	}

void Measure1() //后向测距
	{
		b=1;				 //初始化中断溢出值
		TR0=0;				//关定时器 0
		TH0=0;				//赋定时器初始值高 8 位为 0
		TL0=0;				//赋定时器初始值低 8 位为 0
		Tx1=1;				//拉高超声波脉冲引脚电位
		for(Del20us=20;Del20us>0;Del20us--);  		//延时 20us
		Tx1=0;        				//拉低超声波脉冲引脚电位，使之产生 20us 的方波信号，使超声波模块开始工作。
		while(Rx1==0);     				//等待回波引脚变 1接受脉冲；
		TR1=1;				//开定时器0，开始计数
		while(Rx1==1);				  	//等待回波引脚变 0接受脉冲；
			Th0=TH0;					//读取时间
			Tl0=TL0;				   
			while(!b);				  //等待中断溢出
			time2=Th0*256+Tl0; 
			M1=(17*time2)/1100;		//测量的结果单位为 cm
}

unsigned char COM(void)	 //用于读取8位温湿度数据
{
  unsigned char i,U8temp,U8comdata;
  for(i=0;i<8;i++)
  {
   while(!bit11); //表示读取的高电位延时大于20 多us 则读取的是1 否则读取的是0
   Delay_us(35); //通过U8FLAG 可判断bit11 显示数据的脉长
   U8temp=0;
   if(bit11)U8temp=1;
   while(bit11);
   U8comdata<<=1;
   U8comdata|=U8temp; //0
   }//rof
   return U8comdata;
}

void getDHT11(void)	   //最终读取的温湿度数据
{
GO1: bit11=0;
     DelayMs(180);	//主机拉低18ms
     bit11=1;
     Delay_us(60); //总线由上拉电阻拉高主机延时20us
//主机设为输入判断从机响应信号
// bit11=1;
//判断从机是否有低电平响应信号如不响应则跳出，响应则向下运行
     if(!bit11) //T !
     {
     while(!bit11); //wait DHT goto high
     while(bit11);//数据接收状态
     U8RH_data_H=COM();	//8bit湿度整数数据
     U8RH_data_L=COM();	//8bit湿度小数数据
     U8T_data_H=COM();	//8bit温度整数数据
     U8T_data_L=COM();	//8bit温度小数数据
     U8checkdata=COM();	//8bit数据校验和
     bit11=1;
     if((U8T_data_H+U8T_data_L+U8RH_data_H+U8RH_data_L)!=U8checkdata)     //数据校验
     goto GO1;//若出错则重新读取数据
     }
}


void INIT_timer0()//初始化定时器0
{
	TMOD=0x01;//定时器工作方式 1：16 位，初值不能重装
	Th0=0;//初始化变量值
	Tl0=0;//初始化变量值
	EA=1;//开总中断
	ET0=1;//开定时器 0 中断
}
									 
 void main()
{
	INIT_timer0();
	while(1)
	{   Measure0(); 
	 	Measure1();
		getDHT11();
		
		}
}
void T0_time() interrupt 1	 //	  定时器0中断，超声波检测
{
	  b=1;
}
