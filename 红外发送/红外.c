/***************************
Ӳ��ƽ̨�����ƺ���װ��
�����ܣ����ݾ�����̰��µļ�����NEC����
****************************/
/*---------------------------------------------
���ƺ���װ�ã�P3^3(INT1)ͨ���㴥�����ӵء�P1�ڽӾ������
P0^7ͨ��s9015��TSAL6200���͵�ƽ��ͨ��P3^2��INT0����HS0038B��
P0^6����ɫָʾ�ƣ��͵�ƽ��ͨ��P2^5�Ӻ�ɫָʾ�ƣ��͵�ƽ��ͨ��
---------------------------------------------*/
#include<reg51.h>
#include<intrins.h>
#include"lcd.h"
/*---------------------------------------------
                 �˿ڶ���
---------------------------------------------*/
sbit zaibo=P2^0;   //���ⷢ����������
sbit IRIN=P3^2;	  //�����ⲿ�жϴ���
unsigned char code CDIS1[4]={"For:"};
unsigned char code CDIS2[5]={"Back:"};
unsigned char code CDIS3[2]={"T:"};
unsigned char code CDIS4[3]={"RH:"};
unsigned char code CDIS5[2]={"S:"};
unsigned char IrValue[6]; //�����������
unsigned char Time;	  //����������ݼ�ʱ
bit panduan01;  //panduan01�����ж�nec���Ӧ������λ��0����1
int key=16;		//key�ݴ��ֵ������keyscan����
unsigned int temp;	//tempɨ���н����������keyscan����
unsigned int M0=0,M1=0;//���������Ծ���
unsigned char U8T_data_H=0,U8RH_data_H=0;//��ʪ�ȴ�������������
unsigned char speed=0;
/*---------------------------------------------
 yindao�������������룺9ms�ز�+4.5ms���ز����ز�ռ�ձȣ�1/3
 ---------------------------------------------*/
void yindao()
{
   unsigned int jishu;

   for(jishu=0;jishu<=345;jishu++)             //8.99ms���ز�
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

    for(jishu=0;jishu<=172;jishu++)           //4.49ms���ز�
    {
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();
     _nop_();_nop_();_nop_();_nop_();_nop_();//��for��乲��26��nop����

    }
  

}
/*---------------------------------------------
 emit1�������䡰1��
 ��������1:21.5�����ز����ز����ڣ���65�����ز����ز�����
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
 emit0�������䡰0��:
 21.5�����ز�����21.5�����ز�����P0^7-���ⷢ��˿ڱ���Ϊ�ߵ�ƽ��
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
NEC()����nec������������a��ʾ��ַ����βΣ�b��ʾ��������βΣ�����8λ�������� 
cΪa�ķ��룬dΪb�ķ��룬����˳��Ϊ��acbd,�ȷ�8λ�еĸ�λ����������Ӧ��
---------------------------------------------*/  
void NEC_emit(unsigned char a,unsigned char b)
{
 void emit1();
 void emit0();
 void yindao();

 unsigned char c,d;     //c,d���ڴ�Ŷ�Ӧa��b�ķ���
 c=~a;
 d=~b;

 yindao();              //����������

 panduan01=a&0x01;     //����ַ���Ӧ�����Ƶ�һλ�����λ��Ϊ1����panduan1����1������Ϊ�㡣
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
 else emit0();                   //����a����ַ����ԭ��

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
 else emit0();                   //����a�ķ���c

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
 else emit0();                   //����b(����)��ԭ��

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
 else emit0();                   //����b�ķ���d

 emit0();   

}

/*--------------
������ʱ����
---------------*/
void delayms(unsigned int xms)
{
 unsigned int i,j;
 for(i=xms;i>0;i--)
       for(j=110;j>0;j--);
}
/*--------------------
keyscan(),����ɨ���ӳ��򣺼��̵ı��Ϊ0 1 2 3
                                      4 5 6 7
			                          8 9 A B
									  C D E F
P1^0~P1^3�ӵ�1����4��,P1^4~P1^7�Ӵ�������1�������С�
---------------------*/
void keyscan()
{
//��һ��ɨ��
 P1=0xfe;
 temp=P1;											 
	
 temp=temp&0xf0;										
 if(temp!=0xf0)											
  {												 
		
    delayms(10);	//**����**
	if(temp!=0xf0)
	 {
	    temp=P1;
		switch(temp)									 
	//******************************************Learn
		   {										 
			//switch()�����÷�,����temp��һ������
		 case 0xee:									 
		//switch�����Ƕ��֧ѡ�����
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
		     while(temp!=0xf0)		//�ȴ����ͷ�
             {
               temp=P1;
               temp=temp&0xf0;
             }
	 }
  }							           		
//�ڶ���ɨ��
 P1=0xfd;
 temp=P1;
 temp=temp&0xf0;
 if(temp!=0xf0)
  {
    delayms(10);		//����
	if(temp!=0xf0)
	 {
	    temp=P1;
		switch(temp)
		 {
		 case 0xed:
               key=4;
			   break;			//*********Learn�˴�break������������� 
//��switch�ṹ��ִ��switch�µ����

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
//������ɨ��
 P1=0xfb;
 temp=P1;
 temp=temp&0xf0;
 if(temp!=0xf0)
  {
    delayms(10);		//����
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
//ɨ�������
 P1=0xf7;
 temp=P1;
 temp=temp&0xf0;
 if(temp!=0xf0)
  {
    delayms(10);		//����
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
	IT0=1;//�½��ش���
	EX0=0;//�ر��ж�0����
	EA=1;	//�����ж�
	IRIN=1;//��ʼ���˿�
}
/*--------------
������
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
			 LcdWriteData('0' + (M1 / 100)); 	//��λ		 
			 LcdWriteData('0' + (M1 % 100 / 10)); // ʮλ
			 LcdWriteData('0' + (M1 % 10));		  // ��λ 
			 LcdWriteCom(0x80+0x0D);
			 LcdWriteData('0' + (M0 / 100)); 	//��λ		 
			 LcdWriteData('0' + (M0 % 100 / 10)); // ʮλ
			 LcdWriteData('0' + (M0 % 10));		  // ��λ 
			 LcdWriteCom(0xC0+0x02);		 
			 LcdWriteData('0' + (U8T_data_H/10)); // ʮλ
			 LcdWriteData('0' + (U8T_data_H % 10));		  // ��λ 
			 LcdWriteCom(0xC0+0x08);		 
			 LcdWriteData('0' + (U8RH_data_H/10)); // ʮλ
			 LcdWriteData('0' + (U8RH_data_H % 10));		  // ��λ
			 LcdWriteCom(0xC0+0x0D);		 
			 LcdWriteData('0' + (speed/10)); // ʮλ
			 LcdWriteData('0' + (speed% 10));		  // ��λ
		 }
}

void Delay_Ms(unsigned int x)   //0.14ms��� 0us
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

	if(IRIN==0)		//ȷ���Ƿ���Ľ��յ���ȷ���ź�
	{	 
		
		err=1000;				//1000*10us=10ms,����˵�����յ�������ź�
		/*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó�������ʱ
		�������������*/	
		while((IRIN==0)&&(err>0))	//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ  		
		{			
			Delay_Ms(1);
			err--;
		} 
		if(IRIN==1)			//�����ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				Delay_Ms(1);
				err--;
			}
			for(k=0;k<4;k++)		//����4������
			{				
				for(j=0;j<8;j++)	//����һ������
				{

					err=60;		
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
						Delay_Ms(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //����ߵ�ƽ��ʱ�䳤�ȡ�
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
					IrValue[k]>>=1;	 //k��ʾ�ڼ�������
					if(Time>=10)			//����ߵ�ƽ���ִ���565us����ô��1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//����ʱ��Ҫ���¸�ֵ							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}
