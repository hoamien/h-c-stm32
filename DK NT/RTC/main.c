//*********************************************************************************************************
               //                MACH DONG HO HEN GIO
//	********************************************************************************************************			
#include <stm32f4xx.h>  
#include "tm_stm32f4_rtc.h"
#include "defines.h"
#include "attributes.h"
#include <stdio.h>
#include <stm32f4xx.h>   
#include "lcd.h"
#include "reprintf.h"

TM_RTC_Time_t      datatime;

void GPIO_Config(void);  
void hien_thi(void);
void cai_dat(void);
void Bat_Tat(void);
void xu_ly(void);
void Delay(__IO uint32_t nCount);
void tinh_ngay_am(uint8_t ngay_duong,uint8_t thang_duong,uint8_t nam_duong);
void ADC_Config(void);
void TIM_PWM_Configuration(void);
__IO int8_t dem=1,bam=0,a=10,b=0,c=0,g=0,k=0,d=0,e=0,f=0,h=15,ab=0,ac=0,bc=0,abc=0;
__IO int8_t a1,a2,a3,a4,a5,a6,a7,k1,l1,a8,Y1=0;
__IO uint8_t ngay_am,thang_am,nam_am=15;
__IO int8_t  x,y,z,xyz,l,X=1;
__IO uint16_t ADCValue[1]={0},ND,i;

 unsigned char ALdauthangDL[11][12] = {
	{17,18,16,27,18,19,20,21,23,24,25,26},//2010
	{27,29,27,28,29,30, 1, 2, 4, 5, 6, 7},//2011
	{ 8,10, 9,11,11,12,13,14,16,16,18,18},//2012
	{20,21,20,21,22,23,24,25,26,27,28,29},//2013
	{ 1, 2, 1, 2, 3, 4, 5, 6, 8, 8, 9,10},//2014
	{11,13,11,13,13,15,16,17,19,19,20,20},//2015
	{22,23,23,24,25,26,27,29, 1, 1, 2, 3},//2016
	{ 4, 5, 4, 5, 6, 7, 8,10,11,12,13,14},//2017
	{15,16,14,16,16,18,18,20,22,22,24,25},//2018
	{26,27,25,27,27,28,29, 1, 3, 3, 5, 6},//2019
	{ 7, 8, 8, 9, 9,10,11,12,14,15,16,17},//2020
};

  unsigned char thangALdauthangDL[11][12] = {
	{11,12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},//2010
	{11,12, 1, 2, 3, 4, 6, 7, 8, 9,10,11},//2011
	{12, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9,10},//2012
	{11,12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},//2013
	{12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9,10},//2014
	{11,12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},//2015
	{11,12, 1, 2, 3, 4, 5, 6, 8, 9,10,11},//2016
	{12, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9,10},//2017
	{11,12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},//2018
	{11,12, 1, 2, 3, 4, 5, 7, 8, 9,10,11},//2019
	{12, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9,10},//2020
};

  unsigned char DLdauthangAL[11][12] = {
	{15,14,16, 5,14,12,12,10, 8, 8, 6, 6},//2010
	{ 4, 3, 5, 3, 3, 2,31,29,27,27,25,25},//2011
	{23,22,22,21,21,19,19,17,16,15,14,13},//2012
	{12,10,12,10,10, 8, 8, 7, 5, 5, 3, 3},//2013
	{31,1,31,29,29,27,27,25,24,24,22,22},//2014
	{20,19,20,19,18,16,16,14,13,13,12,11},//2015
	{10, 8, 9, 7, 7, 5, 4, 3, 1,31,29,29},//2016
	{28,26,28,26,26,24,23,22,20,20,18,18},//2017
	{17,16,17,16,15,14,13,11,10, 9, 7, 7},//2018
	{ 6, 5, 6, 5, 5, 3, 3,30,29,28,26,26},//2019
	{25,23,24,23,23,21,21,19,17,17,15,14},//2020
};

  unsigned char thangALdauthangAL[11][12] = {
	{12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},//2010
	{12, 1, 2, 3, 4, 5, 7, 8, 9,10,11,12},//2011
	{ 1, 2, 3, 4, 4, 5, 6, 7, 8, 9,10,11},//2012
	{12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},//2013
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 9,10,11},//2014
	{12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},//2015
	{12, 1, 2, 3, 4, 5, 6, 7, 8,10,11,12},//2016
	{ 1, 2, 3, 4, 5, 6, 6, 7, 8, 9,10,11},//2017
	{12, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},//2018
	{12, 1, 2, 3, 4, 5, 6, 8, 9,10,11,12},//2019
	{ 1, 2, 3, 4, 4, 5, 6, 7, 8, 9,10,11},//2020
};
int main(void)
{

	GPIO_Config();
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
	ADC_Config();
	TIM_PWM_Configuration();
	TIM1->CCR1 = 45; 
  if (!TM_RTC_Init(TM_RTC_ClockSource_Internal)) {}
  lcd_Init();		
  lcd_Clear();
  lcd_Goto(0,4);
	printf("    MACH DIEN: ");
	lcd_Goto(1,0);
	printf(" DONG HO HEN GIO ");
			
  lcd_Clear();						
  while(1)
  {
		for(i=1;i<=100;i++)
   {
    ND=ADCValue[0] + ND;
   }
	  ND=ND/100;
		ND=ND*1.09; // ND=ND*330/256
		TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);
		tinh_ngay_am(datatime.date,datatime.month,datatime.year);
		cai_dat();
		hien_thi();
	  xu_ly();
		Bat_Tat();
  }
 }
void tinh_ngay_am(uint8_t ngay_duong,uint8_t thang_duong,uint8_t nam_duong)
 {
	uint8_t ngayam_cua_mung1duong,ngayduong_cua_mung1am;
	int8_t hieu;	
	ngayam_cua_mung1duong = ALdauthangDL[((nam_duong) - 10)][(thang_duong - 1)];
	ngayduong_cua_mung1am = DLdauthangAL[((nam_duong) - 10)][(thang_duong - 1)];
	
	hieu = (ngayduong_cua_mung1am - ngay_duong);
	if( thang_duong == 2 && nam_duong == 14)
	{
		ngay_am = ngayam_cua_mung1duong + ngay_duong - 1;
		thang_am = thangALdauthangDL[((nam_duong) - 10)][((thang_duong)-1)];
	}
	else
	{
		if(hieu<=0)
		{
			ngay_am = ngay_duong - ngayduong_cua_mung1am + 1;
			thang_am = thangALdauthangAL[((nam_duong) - 10)][(thang_duong - 1)];
		
		}
		else
		{
			ngay_am = ngayam_cua_mung1duong + ngay_duong - 1;
			thang_am = thangALdauthangDL[((nam_duong) - 10)][(thang_duong - 1)];
		
		}
	}
}
void cai_dat(void)
 {
	if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_8)==1);
		dem++;bam=0;lcd_Clear();	if(dem==26) dem=1;
    }
	 switch(dem)
    {
		case 0:
		{  
			 }break;
	  case 1:  
    {
			X=1;
			if(datatime.day==1)
				{
			lcd_Goto(0,0);
	    printf("THU:CN ");
	    lcd_Goto(0,8);
	    printf("%d:%d:%d      ", datatime.hours,datatime.minutes,datatime.seconds);
			lcd_Goto(1,0);
			printf("nhiet do:%d*C     ",ND);
					}
				else
					{
					lcd_Goto(0,0);
	    printf("THU:%d ",datatime.day);
	    lcd_Goto(0,8);
	    printf("%d:%d:%d      ", datatime.hours,datatime.minutes,datatime.seconds);
			lcd_Goto(1,0);
			printf("nhiet do:%d*C     ",ND);
					}
		}break;     
	  case 2:  
    {
			X=0;
			lcd_Goto(0,0);
	    printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("_%d:%d:%d  BAT ",ab,ac,bc);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    ab++;  
			if(ab<0) ab=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    ab--; 
			if(ab<0) ab=0;
       }
		}break;     
		case 3:  
    {
			X=0;
			k=ab;
			lcd_Goto(0,0);
	    printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:_%d:%d  BAT ",ab,ac,bc);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    ac++;  
			if(ac<0) ac=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    ac--; 
			if(ac<0) ac=0;
       }
		}break;     
		case 4:  
    {
			X=0;
			lcd_Goto(0,0);
	   printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:_%d  BAT ",ab,ac,bc);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    bc++;  
			if(bc<0) bc=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    bc--; 
			if(bc<0) bc=0;
       }
		}break;     
		case 5:  
    {
			X=0;
			abc++;
			if(abc==1)
				{
				lcd_Goto(0,0);
	   printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",ab,ac,bc);
				}
				if(abc==10) abc=2;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
				lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
				ab=k;
		   lcd_Goto(0,0);
	   printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",k,ac,bc);
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
				 lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
				 	ab=24;
				  lcd_Goto(0,0);
		    printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _TAT ",ab,ac,bc);
       }
			 }break;
		case 6:  
    {
			X=0;
			lcd_Goto(0,0);
	    printf("THIET BI 1 TAT:");
			lcd_Goto(1,0);
			printf("_%d:%d:%d  BAT ",x,y,z);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    x++;  
			if(x<0) x=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    x--; 
			if(x<0) x=0;
       }
		}break;     
		case 7:  
    {
			X=0;
			l=x;
			lcd_Goto(0,0);
	   printf("THIET BI 1 TAT:");
			lcd_Goto(1,0);
			printf("%d:_%d:%d  BAT ",x,y,z);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    y++;  
			if(y<0) y=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    y--; 
			if(y<0) y=0;
       }
		}break;     
		case 8:  
    {
			X=0;
			lcd_Goto(0,0);
	    printf("THIET BI 1 TAT:"); 
			lcd_Goto(1,0);
			printf("%d:%d:_%d  BAT ",x,y,z);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    z++;  
			if(z<0) z=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    z--; 
			if(z<0) z=0;
       }
		}break;     
		case 9:  
    {
			X=0;
			xyz++;
			if(xyz==1)
				{
				lcd_Goto(0,0);
	    printf("THIET BI 1 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",x,y,z);
				}
				if(xyz==10) xyz=2;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
				lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
				x=l;
		   lcd_Goto(0,0);
	   printf("THIET BI 1 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",l,y,z);
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
				 lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
				 	x=24;
				  lcd_Goto(0,0);
		     printf("THIET BI 1 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _TAT ",x,y,z);
       }
			 }break;
	  case 10:  
    {
			X=0;
			lcd_Goto(0,0);
	    printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("_%d:%d:%d  BAT ",a1,a2,a3);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    a1++;  
			if(a1<0) a1=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    a1--; 
			if(a1<0) a1=0;
       }
		}break;     
		case 11:  
    {
			X=0;
			k1=a1;
			lcd_Goto(0,0);
	    printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:_%d:%d  BAT ",a1,a2,a3);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    a2++;  
			if(a2<0) a2=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    a2--; 
			if(a2<0) a2=0;
       }
		}break;     
		case 12:  
    {
			X=0;
			lcd_Goto(0,0);
	   printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:_%d  BAT ",a1,a2,a3);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    a3++;  
			if(a3<0) a3=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    a3--; 
			if(a3<0) a3=0;
       }
		}break;     
		case 13:  
    {
			X=0;
			a7++;
			if(a7==1)
				{
				lcd_Goto(0,0);
	   printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",a1,a2,a3);
				}
				if(a7==10) a7=2;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
				lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
				a1=k1;
		   lcd_Goto(0,0);
	   printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",k1,a2,a3);
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
				 lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
				 	a1=24;
				  lcd_Goto(0,0);
		    printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _TAT ",a1,a2,a3);
       }
			 }break;
		case 14:  
    {
			X=0;
			lcd_Goto(0,0);
	    printf("THIET BI 2 TAT:");
			lcd_Goto(1,0);
			printf("_%d:%d:%d  BAT ",a4,a5,a6);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    a4++;  
			if(a4<0) a4=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    a4--; 
			if(a4<0) a4=0;
       }
		}break;     
		case 15:  
    {
			X=0;
			l1=a4;
			lcd_Goto(0,0);
	   printf("THIET BI 2 TAT:");
			lcd_Goto(1,0);
			printf("%d:_%d:%d  BAT ",a4,a5,a6);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    a5++;  
			if(a5<0) a5=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    a5--; 
			if(a5<0) a5=0;
       }
		}break;     
		case 16:  
    {
			X=0;
			lcd_Goto(0,0);
	    printf("THIET BI 2 TAT:"); 
			lcd_Goto(1,0);
			printf("%d:%d:_%d  BAT ",a4,a5,a6);
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    a6++;  
			if(a6<0) a6=0;
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    a6--; 
			if(a6<0) a6=0;
       }
		}break;     
		case 17:  
    {
			X=0;
			a8++;
			if(a8==1)
				{
				lcd_Goto(0,0);
	    printf("THIET BI 2 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",a4,a5,a6);
				}
				if(a8==10) a8=2;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
				lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
				a4=l1;
		   lcd_Goto(0,0);
	   printf("THIET BI 2 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _BAT ",l1,a5,a6);
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
				 lcd_Clear();
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
				 	a4=24;
				  lcd_Goto(0,0);
		     printf("THIET BI 2 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d  _TAT ",a4,a5,a6);
       }
			 }break;
		
		case 18:   
    {
			X=0;
			xyz=0;
			abc=0;
			a7=0;
			a8=0;
		 	a= datatime.hours ;
      b= datatime.minutes ;
      c= datatime.seconds ;
			g= datatime.day;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		    g++;   if(g>7) g=1; 
				datatime.hours=a ;
       datatime.minutes=b;
       datatime.seconds=c ;
			 datatime.day=g;
			 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
      }
		  if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
       {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		    g--;  if(g<1) g=7;
				 datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
       }
			if(datatime.day==1)
				{
			lcd_Goto(0,0);
	    printf("THU:_CN ");
	    lcd_Goto(0,8);
	    printf("%d:%d:%d      ", datatime.hours,datatime.minutes,datatime.seconds);
			lcd_Goto(1,0);
			printf("nhiet do:%d*C     ",ND);
				}
			else
				{
		  lcd_Goto(0,0);
	   printf("THU:_%d  ",datatime.day);
	  lcd_Goto(0,7);
	  printf("%d:%d:%d       ", datatime.hours,datatime.minutes,datatime.seconds);
			 lcd_Goto(1,0);
				printf("nhiet do:%d*C     ",ND);
					}
		}  break;
		case 19:   
    {
			X=0;
			a=datatime.hours ;
       b= datatime.minutes ;
        c= datatime.seconds ;
			   g=datatime.day;
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		a++;   if(a>23) a=0; 
			datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		a--;  if(a<0) a=23;
			datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(datatime.day==1)
				{
			lcd_Goto(0,0);
	    printf("THU:CN ");
	    lcd_Goto(0,8);
	    printf("_%d:%d:%d      ", datatime.hours,datatime.minutes,datatime.seconds);
			lcd_Goto(1,0);
			printf("nhiet do:%d*C     ",ND);
					}
				else
					{
			  lcd_Goto(0,0);
	     	printf("THU:%d ",datatime.day);
	     lcd_Goto(0,7);
	     printf("_%d:%d:%d       ", datatime.hours,datatime.minutes,datatime.seconds);
		lcd_Goto(1,0);
				printf("nhiet do:%d*C     ",ND);
						}
		}  break;
		case 20:   
    {
			X=0;
			 a=datatime.hours ;
       b= datatime.minutes ;
       c= datatime.seconds ;
			 g=datatime.day;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		b++;   if(b>59) b=0; 
			datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		b--;  if(b<0) b=59;
			datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    } 
		if(datatime.day==1)
				{
			lcd_Goto(0,0);
	    printf("THU:CN ");
	    lcd_Goto(0,8);
	    printf("%d:_%d:%d      ", datatime.hours,datatime.minutes,datatime.seconds);
			lcd_Goto(1,0);
			printf("nhiet do:%d*C     ",ND);
					}
				else
					{
			  lcd_Goto(0,0);
	     	printf("THU:%d ",datatime.day);
	     lcd_Goto(0,7);
		 printf("%d:_%d:%d       ", datatime.hours,datatime.minutes,datatime.seconds);
		lcd_Goto(1,0);
		printf("nhiet do:%d*C     ",ND);
						}
		}break;
		case 21:   
    {
			X=0;
			 a=datatime.hours ;
       b= datatime.minutes ;
       c= datatime.seconds ;
			 g=datatime.day;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		c++;   if(c>59) c=0; 
			datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)==1);
		c--;  if(c<0) c=59;
			datatime.hours=a ;
         datatime.minutes=b;
         datatime.seconds=c ;
			   datatime.day=g;
				  TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(datatime.day==1)
				{
			lcd_Goto(0,0);
	    printf("THU:CN ");
	    lcd_Goto(0,8);
	    printf("%d:%d:_%d      ", datatime.hours,datatime.minutes,datatime.seconds);
			lcd_Goto(1,0);
			printf("nhiet do:%d*C     ",ND);
					}
				else
					{
		  lcd_Goto(0,0);
	     	printf("THU:%d ",datatime.day);
	     lcd_Goto(0,7);
	     printf("%d:%d:_%d       ", datatime.hours,datatime.minutes,datatime.seconds);
		lcd_Goto(1,0);
				printf("nhiet do:%d*C     ",ND);
						}
		}  break;
		
		case 22:   
    {
			    X=0;
			 d=datatime.year;
       e =datatime.month;
       f=datatime.date ;
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		f++;    
			datatime.year=d;
       datatime.month=e;
       datatime.date=f;
		 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		f--;  
			datatime.year=d;
       datatime.month=e;
       datatime.date=f;
		 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
	     lcd_Goto(0,0);
		printf("D  _%d:%d:%d           ", datatime.date,datatime.month, datatime.year+2000);
		  lcd_Goto(1,0);
		printf("A  %d:%d:%d           ",  ngay_am,thang_am,nam_am+2000);
		}  break;
		case 23:   
    {
			X=0;
			 d=datatime.year;
       e =datatime.month;
       f=datatime.date ;
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		e++;   if(e>12) e=1; 
			datatime.year=d;
       datatime.month=e;
       datatime.date=f;
		 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		e--;  if(e<1) e=12;
			datatime.year=d;
       datatime.month=e;
       datatime.date=f;
		 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
	     lcd_Goto(0,0);
		printf("D  %d:_%d:%d           ", datatime.date,datatime.month, datatime.year+2000);
		  lcd_Goto(1,0);
		printf("A  %d:%d:%d           ",  ngay_am,thang_am,nam_am+2000);
		}  break;
		case 24:   
    {
			X=0;
			 d=datatime.year;
       e =datatime.month;
       f=datatime.date ;
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
        while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		d++;   
			datatime.year=d;
       datatime.month=e;
       datatime.date=f;
		 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
		if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)==1);
		d--;  if(d<0) d=0;
			datatime.year=d;
       datatime.month=e;
       datatime.date=f;
		 TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
    }
	     lcd_Goto(0,0);
		printf("D  %d:%d:_%d           ", datatime.date,datatime.month, datatime.year+2000);
		  lcd_Goto(1,0);
		printf("A  %d:%d:%d           ",  ngay_am,thang_am,nam_am+2000);
		}  break;
		case 25:   
    {   
			X=0; 
			if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1) 
      {
       while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		h++;   
    }
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		h--;  if(h<0) h=0;
    }
		 nam_am=h;
	     lcd_Goto(0,0);
		printf("D  %d:%d:%d           ", datatime.date,datatime.month, datatime.year+2000);
		  lcd_Goto(1,0);
		printf("A  %d:%d:_%d           ",  ngay_am,thang_am,nam_am+2000);
		}  break;
	}
	   }
void hien_thi(void)
 {
	   if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_10)==1) 
    {
    while(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_10)==1);
		bam++;  dem=0;lcd_Clear();	if(bam==7) bam=1;
    }
	 switch(bam)
    {  
			   case 0:
			 {
	        
			 }break;
		case 1:   
    {
			xyz=0;
			abc=0;
			dem=1;
			a7=0;
			a8=0;
		}
		break;
		case 2:   
    {
		lcd_Goto(0,0);
		printf("D  %d:%d:%d           ", datatime.date,datatime.month, datatime.year+2000);
		lcd_Goto(1,0);
		printf("A  %d:%d:%d           ",  ngay_am,thang_am,nam_am+2000);
		}  break;
		case 3:   
    {
		if(ab==24)
			{
			 lcd_Goto(0,0);
		     printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d   TAT ",ab,ac,bc);
			}
		else 
			{
			 lcd_Goto(0,0);
		     printf("THIET BI 1 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d   BAT ",ab,ac,bc);
			}
		}  break;
		case 4:   
    {
		if(x==24)
			{
			 lcd_Goto(0,0);
		   printf("THIET BI 1 TAT:");
			 lcd_Goto(1,0);
			 printf("%d:%d:%d   TAT ",x,y,z);
			}
		else 
			{
			 lcd_Goto(0,0);
		  printf("THIET BI 1 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d   BAT ",x,y,z);
			}
		}  break;
		case 5:   
    {
		if(a1==24)
			{
			 lcd_Goto(0,0);
		    printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d   TAT ",a1,a2,a3);
			}
		else 
			{
			 lcd_Goto(0,0);
		     printf("THIET BI 2 BAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d   BAT ",a1,a2,a3);
			}
		}  break;
		case 6:   
    {
		if(a4==24)
			{
			 lcd_Goto(0,0);
		   printf("THIET BI 2 TAT:");
			 lcd_Goto(1,0);
			 printf("%d:%d:%d   TAT ",a4,a5,a6);
			}
		else 
			{
			 lcd_Goto(0,0);
		  printf("THIET BI 2 TAT:");
			lcd_Goto(1,0);
			printf("%d:%d:%d   BAT ",a4,a5,a6);
			}
		}  break;
	}
		}
void xu_ly(void)
 {
      if((ab==datatime.hours)&&(ac==datatime.minutes)&&(bc==datatime.seconds))	
			{
					GPIO_ResetBits(GPIOE, GPIO_Pin_1);
					Y1=1;
			}	
			if((x==datatime.hours)&&(y==datatime.minutes)&&(z==datatime.seconds))	
			{
				  GPIO_SetBits(GPIOE, GPIO_Pin_1);
					Y1=0;
			}	
			if((a1==datatime.hours)&&(a2==datatime.minutes)&&(a3==datatime.seconds))	
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_5);	
					Y1=1;
			}	
			if((a4==datatime.hours)&&(a5==datatime.minutes)&&(a6==datatime.seconds))	
			{
				 GPIO_SetBits(GPIOE, GPIO_Pin_5);
					Y1=0;
			}	
		}
void Bat_Tat(void) 
 {
	if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1&&X==1)
	{
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_6)==1);
		     Y1++;
				if(Y1%2!=0)     					GPIO_ResetBits(GPIOE, GPIO_Pin_1);
				else                    GPIO_SetBits(GPIOE, GPIO_Pin_1);
	}
	if(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1&&X==1)
	{
    while(GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_8)==1);
		     Y1++;
				if(Y1%2!=0)     GPIO_ResetBits(GPIOE, GPIO_Pin_5);
				else           GPIO_SetBits(GPIOE, GPIO_Pin_5);
	}
}
void ADC_Config(void)
 {
	DMA_InitTypeDef            DMA_InitStructure;
ADC_InitTypeDef            ADC_InitStructure;
ADC_CommonInitTypeDef      ADC_CommonInitStructure;
GPIO_InitTypeDef           GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;                     
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  DMA_InitStructure.DMA_Channel = DMA_Channel_0;   //  ho tro kenh 0
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCValue;  // bien DMA_Memory0BaseAddr se chua dia chi bien adc
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); //gan dia chi thanh ghi chua gia tri chuyen doi adc vao bien  DMA_PeripheralBaseAddr
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; //chon huong du lieu tu ngoai vi den bo nho
  DMA_InitStructure.DMA_BufferSize = 2;  
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // neu bat thi dia chi ngoai vi se tang dan (khong quan tr )nguy hiemkhi khong nam ro dk dia chi tiep theo
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//vì có 3 ph?n tu nên nó co tác dung tang dia chi ô nho
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//chon kich thuoc thanh ghi chua du lieu ngoai vi  HalfWord(16bit)
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;// chon kich thuoc mang ADCValue là HalfWord
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;      //che do chuyen doi lien tuc
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;// thiet lap che do yeu tien cao 
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);

  /* DMA2_Stream0 enable */
  DMA_Cmd(DMA2_Stream0, ENABLE);
  
  
  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;  // mode don co ban không su dung chuc nang dac biet
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2; // bo chia 2 lay mau o tan so cao nhat
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles; // thoi gian tre giua 2 lan lay mau lien tiep
  ADC_CommonInit(&ADC_CommonInitStructure);
   
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b; // che do 8 bit
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // khong su dung convert  bang tin hieu ngoai
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // canh le ben phai do thanh ghi 16 bit nhung do phan dai 12bit
  ADC_InitStructure.ADC_NbrOfConversion = 2; //so kenh chuyen doi 
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channels configuration */ 
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_84Cycles); 
 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_84Cycles); //  ADC_SampleTime_3Cycles thoi gian lay maucang lon thì tg lay mau cang lau
  
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
       
  /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConv(ADC1);
}
void GPIO_Config(void)
 {
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOA, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       //CHE DO OUT
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    // CHE DO pushpull THUONG DK DUNG IO NHAT 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //chon clock thuong de toc do max
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    //KHONG CO DIEN TRO KEO LEN MUC CAO VA MUC THAP
  GPIO_Init(GPIOE, &GPIO_InitStructure);   
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8;        //CHON PIN e
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    // CHE DO pushpull THUONG DK DUNG IO NHAT 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;     // CHE DO DAU VAO 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);       // truyen 2 doi  so nay de thiet lap cho phan cung
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;        //CHON PIN e
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    // CHE DO pushpull THUONG DK DUNG IO NHAT 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;     // CHE DO DAU VAO 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);       // truyen 2 doi  so nay de thiet lap cho phan cung
}
void TIM_PWM_Configuration(void)
 { 
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  TIM_OCInitTypeDef          TIM_OCInitStructure;
  GPIO_InitTypeDef           GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
  

  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/100000)-1;
  TIM_TimeBaseStructure.TIM_Period = 100-1;                          
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;
  //TIM_OCStructInit(&TIM_OCInitStructure);
  
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);      // cai dat pwm1
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);   // bat chuc nag preloat
	
	 TIM_OC2Init(TIM1, &TIM_OCInitStructure);   // pwm2
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	 TIM_OC3Init(TIM1, &TIM_OCInitStructure);   // pwm3
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM1, ENABLE);

  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE); // chi co timer 1 va timer 8
}
void Delay(__IO uint32_t nCount)            //Ham delay
 {
  while(nCount--)
  {
  }
}
#ifdef  USE_FULL_ASSERT                                             // DOAN CHUONG TRINH ST THEM VAO DE KIEM TRA LOI
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

