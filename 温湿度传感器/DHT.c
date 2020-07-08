#include<reg51.h>
#include<intrins.h>
#include"lcd.h"
sbit bit11=P2^0;
sbit Tx0=P2^2;//ǰ�����������������ţ���ʱ 20us
sbit Rx0=P2^3;//�ز����ţ������ⲿ�ж� 1
sbit Tx1=P1^4;//�������������������ţ���ʱ 20us
sbit Rx1=P1^5;//�ز����ţ������ⲿ�ж� 1
unsigned char U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
unsigned char F16T,F16RH; //�������ն�ȡ����ʪ������
bit b;			  //��������ʱ��������־λ
long Th0,Tl0;	  //��ʱ��0������ֵ
unsigned long time0=0,time2=0; //��ʱ��0������ֵ֮��
unsigned int Del20us=0;//��ʱ�������ڳ��������������в��� 20us �ķ���
unsigned int M0=0,M1=0;//���������Ծ���
unsigned char U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;//��ʪ�ȴ�������������

void Delay_ms(unsigned int n)//n ������ʱ
{
  unsigned char j;
  while(n--)
  {
    for(j=0;j<125;j++);
   }
}

void Delay_us(unsigned char n) //N us ��ʱ�������ȡ�4us
{
  n=n/2;
  while(--n);
}
void Measure0() //ǰ����
	{
		b=1;				 //��ʼ���ж����ֵ
		TR0=0;				//�ض�ʱ�� 0
		TH0=0;				//����ʱ����ʼֵ�� 8 λΪ 0
		TL0=0;				//����ʱ����ʼֵ�� 8 λΪ 0
		Tx0=1;				//���߳������������ŵ�λ
		for(Del20us=20;Del20us>0;Del20us--);  		//��ʱ 20us
		Tx0=0;        				//���ͳ������������ŵ�λ��ʹ֮���� 20us �ķ����źţ�ʹ������ģ�鿪ʼ������
		while(Rx0==0);     				//�ȴ��ز����ű� 1�������壻
		TR0=1;				//����ʱ��0����ʼ����
		while(Rx0==1);				  	//�ȴ��ز����ű� 0�������壻
			Th0=TH0;					//��ȡʱ��
			Tl0=TL0;				   
			while(!b);				  //�ȴ��ж����
			time0=Th0*256+Tl0; 
			M0=(17*time0)/1100;		//�����Ľ����λΪ cm
	}

void Measure1() //������
	{
		b=1;				 //��ʼ���ж����ֵ
		TR0=0;				//�ض�ʱ�� 0
		TH0=0;				//����ʱ����ʼֵ�� 8 λΪ 0
		TL0=0;				//����ʱ����ʼֵ�� 8 λΪ 0
		Tx1=1;				//���߳������������ŵ�λ
		for(Del20us=20;Del20us>0;Del20us--);  		//��ʱ 20us
		Tx1=0;        				//���ͳ������������ŵ�λ��ʹ֮���� 20us �ķ����źţ�ʹ������ģ�鿪ʼ������
		while(Rx1==0);     				//�ȴ��ز����ű� 1�������壻
		TR0=1;				//����ʱ��0����ʼ����
		while(Rx1==1);				  	//�ȴ��ز����ű� 0�������壻
			Th0=TH0;					//��ȡʱ��
			Tl0=TL0;				   
			while(!b);				  //�ȴ��ж����
			time2=Th0*256+Tl0; 
			M1=(17*time2)/1100;		//�����Ľ����λΪ cm
}
unsigned char COM(void)
{
  unsigned char i,U8temp,U8comdata;
  for(i=0;i<8;i++)
  {
   while(!bit11); //��ʾ��ȡ�ĸߵ�λ��ʱ����20 ��us ���ȡ����1 �����ȡ����0
   Delay_us(35); //ͨ��U8FLAG ���ж�bit11 ��ʾ���ݵ�����
   U8temp=0;
   if(bit11)U8temp=1;
   while(bit11);
   U8comdata<<=1;
   U8comdata|=U8temp; //0
   }//rof
   return U8comdata;
}
//--------------------------------
//-----��ʪ�ȶ�ȡ�ӳ���------------
//--------------------------------
//----���±�����Ϊȫ�ֱ���--------
//----�¶ȸ�8 λ== U8T_data_H------
//----�¶ȵ�8 λ== U8T_data_L------
//----ʪ�ȸ�8 λ== U8RH_data_H-----
//----ʪ�ȵ�8 λ== U8RH_data_L-----
//----У��8 λ== U8checkdata-----
//----��������ӳ�������----------
//---- Delay();, Delay_10us();,COM();
//--------------------------------
void getDHT11(void)
{
GO1: bit11=0;
     Delay_ms(20);	//��������18ms
     bit11=1;
     Delay_us(60); //������������������������ʱ20us
//������Ϊ�����жϴӻ���Ӧ�ź�
// bit11=1;
//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź��粻��Ӧ����������Ӧ����������
     if(!bit11) //T !
     {
     while(!bit11); //wait DHT goto high
     while(bit11);//���ݽ���״̬
     U8RH_data_H=COM();
     U8RH_data_L=COM();
     U8T_data_H=COM();
     U8T_data_L=COM();
     U8checkdata=COM();
     bit11=1;
     if((U8T_data_H+U8T_data_L+U8RH_data_H+U8RH_data_L)!=U8checkdata)     //����У��
     goto GO1;//if check wrong,read again
     }
     F16T=U8T_data_H+(float)U8T_data_L/256; //change integer to float
     F16RH=U8RH_data_H+(float)U8RH_data_L/256;
}
void INIT_timer0()//��ʼ����ʱ��0
{
	TMOD=0x01;//��ʱ��������ʽ 1��16 λ����ֵ������װ
	Th0=0;//��ʼ������ֵ
	Tl0=0;//��ʼ������ֵ
	ET0=1;//����ʱ�� 0 �ж�
	EA=1;
}
void main ()
{
   LcdInit();
   INIT_timer0();
   while(1)
   {  Measure0() ;
	 Measure1() ;
     // getDHT11();
	  LcdWriteCom(0x80); 
      LcdWriteData('0' + (F16T % 100 / 10)); // ʮλ
	  LcdWriteData('0' + (F16T % 10));		  // ��λ
	  LcdWriteCom(0x80+0x08); 
      LcdWriteData('0' + (M0 % 100 / 10)); // ʮλ
	  LcdWriteData('0' + (M0 % 10));		  // ��λ  
	  LcdWriteCom(0xC0); 
	  LcdWriteData('0' + (F16RH % 100 / 10)); // ʮλ
	  LcdWriteData('0' + (F16RH % 10));		  // ��λ 
	  LcdWriteCom(0xC0+0x08); 
      LcdWriteData('0' + (M1 % 100 / 10)); // ʮλ
	  LcdWriteData('0' + (M1 % 10));		  // ��λ  
   }	  
}