#include<reg51.h>
#include<intrins.h>
#include"lcd.h"

//---声明一个全局变量---//
sbit IRIN=P3^2;  //红外接收中断
sbit zaibo=P0^7;  //红外发射载波
int key=16;		//key暂存键值，用于keyscan（）
unsigned char IrValue[6];   //红外接收数据
unsigned char Time;	//红外接收数据计时
unsigned int M0=0,M1=0;//超声波测试距离
unsigned char U8T_data_H=0,U8T_data_L=0,U8RH_data_H=0,U8RH_data_L=0;//温湿度传感器接收数据

void yindao()	 //生成引导码
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

void emit1()  //发射1
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

 void emit0()  //发射0
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
{bit panduan01;
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

void DelayMs(unsigned int x)   //0.14ms误差 0us
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++)
		{}
	}
}

void keyscan()	   //键盘扫描程序
{unsigned int temp;	//temp扫描中介变量，用于keyscan（）
//第一行扫描
 P1=0xfe;
 temp=P1;											 
	
 temp=temp&0xf0;										
 if(temp!=0xf0)											
  {												 
		
    DelayMs(100);	//**消抖**
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
    DelayMs(100);		//消抖
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
    DelayMs(100);		//消抖
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
    DelayMs(100);		//消抖
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
	EX0=1;//打开中断0允许
	EA=1;	//打开总中断
	IRIN=1;//初始化端口
}

void main()
{
	IrInit();
	LcdInit();
	while(1)
	{  	 EA=0;
		 keyscan();
  	     switch(key)
		 {
		  	case 0:NEC_emit(0x22,0x00);break;
         	case 1:NEC_emit(0x22,0x01);break;
         	case 2:NEC_emit(0x22,0x02);break;
          	case 3:NEC_emit(0x22,0x03);break;
			case 4:NEC_emit(0x22,0x04);break;
         	case 5:NEC_emit(0x22,0x05);break;
         	case 6:NEC_emit(0x22,0x06);break;
          	case 7:NEC_emit(0x22,0x07);break;
			case 8:NEC_emit(0x22,0x08);break;	
         	case 9:NEC_emit(0x22,0x09);break;
         	case 10:NEC_emit(0x22,0x0a);break;
          	case 11:NEC_emit(0x22,0x0b);break;
			case 12:NEC_emit(0x22,0x0c);break;
         	case 13:NEC_emit(0x22,0x0d);break;
         	case 14:NEC_emit(0x22,0x0e);break;
          	case 15:NEC_emit(0x22,0x0f);break;
		    }
		  EA=1;		 
		  switch(IrValue[2]&0xF0)
		  {case 0x0F:M0=M0|(IrValue[2]<<4);
		   case 0x1F:M0=M0|(IrValue[2]&0x0F);
		   case 0x2F:M1=M1|(IrValue[2]<<4);
		   case 0x3F:M1=M1|(IrValue[2]&0x0F);
		   case 0x4F:U8RH_data_H=U8RH_data_H|(IrValue[2]<<4);
		   case 0x5F:U8RH_data_H=U8RH_data_H|(IrValue[2]&0x0F);
		   case 0x6F:U8RH_data_L=U8RH_data_L|(IrValue[2]<<4);
		   case 0x7F:U8RH_data_L=U8RH_data_L|(IrValue[2]&0x0F);
		   case 0x8F:U8T_data_H=U8RH_data_H|(IrValue[2]<<4);
		   case 0x9F:U8T_data_H=U8RH_data_H|(IrValue[2]&0x0F);
		   case 0xAF:U8T_data_L=U8RH_data_L|(IrValue[2]<<4);
		   case 0xBF:U8T_data_L=U8RH_data_L|(IrValue[2]&0x0F);
		  }
		  LcdWriteCom(0x80);
		  LcdWriteData('0'+M0/100);
		  LcdWriteData('0'+(M0%100)/10);
		  LcdWriteData('0'+M0%10);
		 }
}

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	DelayMs(70);

	if(IRIN==0)		//确认是否真的接收到正确的信号
	{	 
		
		err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
		/*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/	
		while((IRIN==0)&&(err>0))	//等待前面9ms的低电平过去  		
		{			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)			//如果正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
			{				
				for(j=0;j<8;j++)	//接收一组数据
				{

					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						DelayMs(1);//0.14ms
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


