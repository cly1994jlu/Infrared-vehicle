#include<reg52.h>
#include<intrins.h>
sbit zaibo=P0^7;
sbit lvdeng=P0^6;
/*---------------------------------------------
                 ȫ�ֱ�������
---------------------------------------------*/
bit panduan01;  //panduan01�����ж�nec���Ӧ������λ��0����1
int key=16;		//key�ݴ��ֵ������keyscan����
unsigned int temp;	//tempɨ���н����������keyscan����
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
{bit panduan01;  //panduan01�����ж�nec���Ӧ������λ��0����1
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
