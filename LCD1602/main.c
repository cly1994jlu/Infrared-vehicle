#include<reg51.h>
#include<intrins.h>
#include"lcd.h"

//---����һ��ȫ�ֱ���---//
sbit IRIN=P3^2;  //��������ж�
sbit zaibo=P0^7;  //���ⷢ���ز�
int key=16;		//key�ݴ��ֵ������keyscan����
unsigned char IrValue[6];   //�����������
unsigned char Time;	//����������ݼ�ʱ
unsigned int M0=0,M1=0;//���������Ծ���
unsigned char U8T_data_H=0,U8T_data_L=0,U8RH_data_H=0,U8RH_data_L=0;//��ʪ�ȴ�������������

void yindao()	 //����������
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

void emit1()  //����1
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

 void emit0()  //����0
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
{bit panduan01;
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

void DelayMs(unsigned int x)   //0.14ms��� 0us
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++)
		{}
	}
}

void keyscan()	   //����ɨ�����
{unsigned int temp;	//tempɨ���н����������keyscan����
//��һ��ɨ��
 P1=0xfe;
 temp=P1;											 
	
 temp=temp&0xf0;										
 if(temp!=0xf0)											
  {												 
		
    DelayMs(100);	//**����**
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
    DelayMs(100);		//����
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
    DelayMs(100);		//����
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
    DelayMs(100);		//����
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
	EX0=1;//���ж�0����
	EA=1;	//�����ж�
	IRIN=1;//��ʼ���˿�
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

	if(IRIN==0)		//ȷ���Ƿ���Ľ��յ���ȷ���ź�
	{	 
		
		err=1000;				//1000*10us=10ms,����˵�����յ�������ź�
		/*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó�������ʱ
		�������������*/	
		while((IRIN==0)&&(err>0))	//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ  		
		{			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)			//�����ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)		//����4������
			{				
				for(j=0;j<8;j++)	//����һ������
				{

					err=60;		
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //����ߵ�ƽ��ʱ�䳤�ȡ�
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


