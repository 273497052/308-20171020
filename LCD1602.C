#include <reg51.h>
#include "LCD1602.H"

#define u8 unsigned char 
#define u16 unsigned int
//LCD引脚定义
sbit RS=P3^0;
sbit RW=P3^1;
sbit EN=P3^2;
#define LCD_DATA  P2

void delay_ms(int x)
{
	 int k,j;
	 for(k=0;k<x;k++)
		for(j=0;j<110;j++);
}

int LCD_1602_Read()	   //LCD 读
{
	 u8 Data_R;
	 RS=0;
	 RW=1;
	 delay_ms(2);
	 EN=0;
	 EN=1;
	 Data_R=LCD_DATA;
	 delay_ms(5);
	 EN=0;
	 delay_ms(5);
	 RW=5;
	 delay_ms(5);
	 return(Data_R&0x80);
}

void LCD_1602(int com,Data)	   //LCD 写
{
	 while(LCD_1602_Read());	   //判断系统是否繁忙
	 RW=0;
	 EN=0;
	 RS=com;
	 delay_ms(5);
	 LCD_DATA=Data;
	 EN=1;
	 delay_ms(5);
	 EN=0;
	 delay_ms(5);
	 RW=1;
}


void LCD_1602_inti()	  //LCD初始化
{
 LCD_1602(0,0X38);
 LCD_1602(0,0X0C);
 LCD_1602(0,0X06);
 LCD_1602(0,0X01);
}

//向LCD写入一串字符串
void LCD_ShowString(u8 x,u8 y,const u8 *p)
{	
    while((*p<='~')&&(*p>=' '))
    {  
		if(y)LCD_1602(0,0X80+x+0X40);
			else LCD_1602(0,0X80+x);
		while(*p)
		{						
			LCD_1602(1,*p++);						
		}			
    } 	
}