/***************************
硬件平台：自制红外装置
程序功能：根据矩阵键盘按下的键发射NEC编码
****************************/
/*---------------------------------------------
自制红外装置：P3^3(INT1)通过点触按键接地。P1口接矩阵键盘
P0^7通过s9015接TSAL6200，低电平导通。P3^2（INT0）接HS0038B。
P0^6接绿色指示灯，低电平导通。P2^5接红色指示灯，低电平导通。
---------------------------------------------*/
#include<reg51.h>
#include<intrins.h>
#include"lcd.h"
/*---------------------------------------------
                 端口定义
---------------------------------------------*/
sbit zaibo=P2^0;   //红外发送数据引脚
sbit IRIN=P3^2;	  //红外外部中断触发
unsigned char code CDIS1[4]={"For:"};
unsigned char code CDIS2[5]={"Back:"};
unsigned char code CDIS3[2]={"T:"};
unsigned char code CDIS4[3]={"RH:"};
unsigned char code CDIS5[2]={"S:"};
unsigned char IrValue[6]; //红外接收数据
unsigned char Time;	  //红外接收数据计时
bit panduan01;  //panduan01用于判断nec码对应二进制位是0还是1
int key=16;		//key暂存键值，用于keyscan（）
unsigned int temp;	//temp扫描中介变量，用于keyscan（）
unsigned int M0=0,M1=0;//超声波测试距离
unsigned char U8T_data_H=0,U8RH_data_H=0;//温湿度传感器接收数据
unsigned char speed=0;
/*---------------------------------------------
 yindao（）产生引导码：9ms载波+4.5ms无载波，载波占空比：1/3
 ---------------------------------------------*/
void yindao()
{
   unsigned int jishu;

   for(jishu=0;jishu<=345;jishu++)             //8.99ms有载波
     {
     zaibo=0;
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();
      zaibo=1;
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
    }   
    
    zaibo=1;

    for(jishu=0;jishu<=172;jishu++)           //4.49ms无载波
    {
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();//此for语句共有26个nop（）

    }
  

}
/*---------------------------------------------
 emit1（）发射“1”
 若发数字1:21.5个有载波的载波周期，加65个无载波的载波周期
 ---------------------------------------------*/
void emit1()
{
    
    unsigned char a;
    
    for(a=0;a<=20;a++)
        {
         zaibo=0;
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();
      zaibo=1;
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
        }
    
    zaibo=1;
    for(a=0;a<=64;a++)
        {
         _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
        }
}
/*---------------------------------------------
 emit0（）发射“0”:
 21.5个有载波，加21.5个无载波（即P0^7-红外发射端口保持为高电平）
 ---------------------------------------------*/
 void emit0()
 {

   unsigned char a;
   
   for(a=0;a<=20;a++)
   {
     zaibo=0;
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();
      zaibo=1;
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
   }
   
   zaibo=1;
   for(a=0;a<=20;a++)
   {
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
   }
 }
/*---------------------------------------------
NEC()发射nec脉冲链，其中a表示地址码的形参，b表示命令码的形参，都是8位二进制数 
c为a的反码，d为b的反码，发射顺序为：acbd,先发8位中的高位（这与解码对应）
---------------------------------------------*/  
void NEC_emit(unsigned char a,unsigned char b)
{
 void emit1();
 void emit0();
 void yindao();

 unsigned char c,d;     //c,d用于存放对应a，b的反码
 c=~a;
 d=~b;

 yindao();              //发射引导码

 panduan01=a&0x01;     //若地址码对应二进制第一位（最低位）为1，则panduan1等于1，否则为零。
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x02;
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x04;
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x08;
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x10;
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x20;
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x40;
 if(panduan01)emit1();
 else emit0();
 panduan01=a&0x80;
 if(panduan01)emit1();
 else emit0();                   //发射a（地址）的原码

  panduan01=c&0x01;     
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x02;
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x04;
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x08;
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x10;
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x20;
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x40;
 if(panduan01)emit1();
 else emit0();
 panduan01=c&0x80;
 if(panduan01)emit1();
 else emit0();                   //发射a的反码c

 panduan01=b&0x01;     
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x02;
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x04;
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x08;
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x10;
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x20;
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x40;
 if(panduan01)emit1();
 else emit0();
 panduan01=b&0x80;
 if(panduan01)emit1();
 else emit0();                   //发射b(命令)的原码

 panduan01=d&0x01;     
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x02;
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x04;
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x08;
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x10;
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x20;
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x40;
 if(panduan01)emit1();
 else emit0();
 panduan01=d&0x80;
 if(panduan01)emit1();
 else emit0();                   //发射b的反码d

 emit0();   

}

/*--------------
毫秒延时程序
---------------*/
void delayms(unsigned int xms)
{
 unsigned int i,j;
 for(i=xms;i>0;i--)
       for(j=110;j>0;j--);
}
/*--------------------
keyscan(),矩阵扫描子程序：键盘的编号为0 1 2 3
                                      4 5 6 7
			                          8 9 A B
									  C D E F
P1^0~P1^3接第1到第4行,P1^4~P1^7接从左数第1到第四列。
---------------------*/
void keyscan()
{
//第一行扫描
 P1=0xfe;
 temp=P1;											 
	
 temp=temp&0xf0;										
 if(temp!=0xf0)											
  {												 
		
    delayms(10);	//**消抖**
	if(temp!=0xf0)
	 {
	    temp=P1;
		switch(temp)									 
	//******************************************Learn
		   {										 
			//switch()语句的用法,这里temp是一个变量
		 case 0xee:									 
		//switch（）是多分支选择语句
               key=0;										 
//*******************************************Learn
               break;

          case 0xde:
               key=1;
			   break;

          case 0xbe:
               key=2;
			   break;

          case 0x7e:
               key=3;				   
               break;
		   }
		     while(temp!=0xf0)		//等待键释放
             {
               temp=P1;
               temp=temp&0xf0;
             }
	 }
  }							           		
//第二行扫描
 P1=0xfd;
 temp=P1;
 temp=temp&0xf0;
 if(temp!=0xf0)
  {
    delayms(10);		//消抖
	if(temp!=0xf0)
	 {
	    temp=P1;
		switch(temp)
		 {
		 case 0xed:
               key=4;
			   break;			//*********Learn此处break语句是用来跳出 
//本switch结构，执行switch下的语句

          case 0xdd:
               key=5;
               break;


          case 0xbd:
               key=6;
               break;

          case 0x7d:
               key=7;
			   break;
		  }
		    while(temp!=0xfd)
           {
            temp=P1;
            temp=temp&0xfd;
           }

		 }
		 }							           
//第三行扫描
 P1=0xfb;
 temp=P1;
 temp=temp&0xf0;
 if(temp!=0xf0)
  {
    delayms(10);		//消抖
	if(temp!=0xf0)
	 {
	    temp=P1;
		switch(temp)
		 {
		 case 0xeb:
               key=8;
               break;

          case 0xdb:
               key=9;
               break;

          case 0xbb:
               key=10;
               break;

          case 0x7b:
               key=11;
               break;
		 }
		while(temp!=0xfb)
           {
            temp=P1;
            temp=temp&0xfb;
           }
		 }
		 }							           
//扫描第四行
 P1=0xf7;
 temp=P1;
 temp=temp&0xf0;
 if(temp!=0xf0)
  {
    delayms(10);		//消抖
	if(temp!=0xf0)
	 {
	    temp=P1;
		switch(temp)
		 {
		 case 0xe7:
               key=12;
               break;

          case 0xd7:
               key=13;
               break;

          case 0xb7:
               key=14;
               break;

          case 0x77:
               key=15;
               break;
		 }
		 while(temp!=0xf7)
           {
            temp=P1;
            temp=temp&0xf7;
           }
		 }
		 }							           
}
void IrInit()
{
	IT0=1;//下降沿触发
	EX0=0;//关闭中断0允许
	EA=1;	//打开总中断
	IRIN=1;//初始化端口
}
/*--------------
主函数
---------------*/
void main()
{   unsigned char i;
    void NEC_emit(unsigned char a,unsigned char b);
    void keyscan(); 
    LcdInit();
	IrInit();
	LcdWriteCom(0x80);
	for(i=0;i<4;i++)
	{
		LcdWriteData(CDIS1[i]);	
	}
	LcdWriteCom(0x80+0x08);
	for(i=0;i<5;i++)
	{
		LcdWriteData(CDIS2[i]);	
	}
	LcdWriteCom(0xC0);
	for(i=0;i<2;i++)
	{
		LcdWriteData(CDIS3[i]);	
	}
	LcdWriteCom(0xC0+0x05);
	for(i=0;i<3;i++)
	{
		LcdWriteData(CDIS4[i]);	
	}
	LcdWriteCom(0xC0+0x0B);
	for(i=0;i<2;i++)
	{
		LcdWriteData(CDIS5[i]);	
	}
    while(1)
 		{
   		    keyscan();
		   	switch(key)
		         	{
		     		case 0:NEC_emit(0x22,0x00);key=16;break;
         	 		case 1:NEC_emit(0x22,0x01);key=16;break;
         	 		case 2:NEC_emit(0x22,0x02);key=16;break;
          			case 3:NEC_emit(0x22,0x03);key=16;break;
					case 4:NEC_emit(0x22,0x04);key=16;break;
         	 		case 5:NEC_emit(0x22,0x05);EX0=1;delayms(200);EX0=0;M0=IrValue[2];IrValue[2]=15;key=16;break;
         	 		case 6:NEC_emit(0x22,0x06);EX0=1;delayms(200);EX0=0;M1=IrValue[2];IrValue[2]=25;;key=16;break;
          			case 7:NEC_emit(0x22,0x07);EX0=1;delayms(200);EX0=0;U8T_data_H=IrValue[2];IrValue[2]=18;key=16;break;
					case 10:NEC_emit(0x22,0x08);EX0=1;delayms(200);EX0=0;U8RH_data_H=IrValue[2];IrValue[2]=33;key=16;break;
         	 		case 11:NEC_emit(0x22,0x0a);key=16;break;
          			case 12:NEC_emit(0x22,0x0b);speed=20;key=16;break;
					case 13:NEC_emit(0x22,0x0c);speed=40;key=16;break;
         	 		case 14:NEC_emit(0x22,0x0d);speed=60;key=16;break;
         	 		case 15:NEC_emit(0x22,0x0e);speed=80;key=16;break;
					default:break;
		            }
			 LcdWriteCom(0x80+0x04);
			 LcdWriteData('0' + (M1 / 100)); 	//百位		 
			 LcdWriteData('0' + (M1 % 100 / 10)); // 十位
			 LcdWriteData('0' + (M1 % 10));		  // 个位 
			 LcdWriteCom(0x80+0x0D);
			 LcdWriteData('0' + (M0 / 100)); 	//百位		 
			 LcdWriteData('0' + (M0 % 100 / 10)); // 十位
			 LcdWriteData('0' + (M0 % 10));		  // 个位 
			 LcdWriteCom(0xC0+0x02);		 
			 LcdWriteData('0' + (U8T_data_H/10)); // 十位
			 LcdWriteData('0' + (U8T_data_H % 10));		  // 个位 
			 LcdWriteCom(0xC0+0x08);		 
			 LcdWriteData('0' + (U8RH_data_H/10)); // 十位
			 LcdWriteData('0' + (U8RH_data_H % 10));		  // 个位
			 LcdWriteCom(0xC0+0x0D);		 
			 LcdWriteData('0' + (speed/10)); // 十位
			 LcdWriteData('0' + (speed% 10));		  // 个位
		 }
}

void Delay_Ms(unsigned int x)   //0.14ms误差 0us
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++)
		{}
	}
}

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	Delay_Ms(70);

	if(IRIN==0)		//确认是否真的接收到正确的信号
	{	 
		
		err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
		/*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/	
		while((IRIN==0)&&(err>0))	//等待前面9ms的低电平过去  		
		{			
			Delay_Ms(1);
			err--;
		} 
		if(IRIN==1)			//如果正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				Delay_Ms(1);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
			{				
				for(j=0;j<8;j++)	//接收一组数据
				{

					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						Delay_Ms(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						Delay_Ms(1);//0.14ms
						Time++;
						err--;
						if(Time>30)
						{
							EX0=1;
							return;
						}
					}
					IrValue[k]>>=1;	 //k表示第几组数据
					if(Time>=10)			//如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}
