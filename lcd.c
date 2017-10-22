#include <reg52.h>
#include "LCD1602.h"
#define u8 unsigned char 
#define u16 unsigned int
   
u16 time[20]={2,0,1,7,1,0,2,0,2,3,5,9,3,0,2017,10,20,12,59,30};	

u8 num,miao,fen,shi;		
u16 mypow(u8 m,u8 n)	 //求m^n
{
	u16 result=1;	 
	while(n--)result*=m;    
	return result;
}

void chaifen(u16 temp,u8 len,u8 temp2)
{
	u8 t;
	for(t=0;t<len;t++)	
		time[t+len*temp2]=(temp/mypow(10,len-t-1))%10;
}
void shijianchuli()
{
  	if(num>=20)
	{
	  num=0;
	  time[20]++; 		//秒自加
	  if(time[20]>=60)
	  {
	  	 time[20]=0;
		 time[19]++; 	//分自加
		 if(fen>=60)
		 {
		 	time[19]=0;
			time[18]++;	//时自加
			if(shi>=24)
			{
				time[18]=0;
			}
		 }
	  }
	chaifen(time[18],2,0);
	chaifen(time[19],2,1);
	chaifen(time[20],2,2);
	 }
}

void LCD_Show ()
{
	u8 i;
	LCD_1602(0,0X80+0x44);
	for(i=0;i<6;i++)
	{
		if((i%2==0)&&(i>1))LCD_1602(1,':');
		 LCD_1602(1,time[i]+'0');
	} 

}
void Timer0_init()
{
  TMOD=0X01;
  TH0=(65536-50000)>>8;
  TL0=(65536-50000);
  EA=1;
  ET0=1;
  TR0=1;   
}

void T0_Timer () interrupt 1
{
	TH0=(65536-50000)>>8;
 	TL0=(65536-50000);
	num++;	
}

void main()
{
	LCD_1602_inti();  
	LCD_ShowString(0,0,"Time: 2017-10-20");
	Timer0_init();
	while(1)
	{	  	
	  shijianchuli();
	  LCD_Show ();
 	}
}