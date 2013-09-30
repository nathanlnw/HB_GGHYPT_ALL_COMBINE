#include  <string.h>
#include "Menu_Include.h"

#define  pass_width1  6
#define  ENTER_CODE  "000000"      // 天地通是 000000 以前是 001100

u8 set_car_codetype=0;
u8 password_Code[10];
u8 password_SetFlag=1,password_Counter=0;
u8 password_icon[]={0x0C,0x06,0xFF,0x06,0x0C};

DECL_BMP(8,5,password_icon);


void password_Set(u8 par)
{
	lcd_fill(0);
	lcd_text12(0,3,"请输入6位密码:",14,LCD_MODE_SET);
	if(password_SetFlag>1)
		lcd_text12(84,3,(char *)password_Code,password_SetFlag-1,LCD_MODE_SET);//-1+14
	lcd_bitmap(par*pass_width1, 14, &BMP_password_icon, LCD_MODE_SET);
	lcd_text12(0,19,"0123456789",10,LCD_MODE_SET);
	lcd_text12(68,20,"hb.GGHYPt",9,LCD_MODE_SET);  // 天津公共货运平台     
	lcd_update_all();
}

static void msg( void *p)
{

}
static void show(void)
{
	CounterBack=0;
	password_SetFlag=1;
	password_Counter=0;
	
	memset(password_Code,0,sizeof(password_Code));
	password_Set(password_Counter);
	//rt_kprintf("\r\nshow:password=%s,password_SetFlag=%d,password_Counter=%d\r\n",password_Code,password_SetFlag,password_Counter);

}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:
            if(Password_correctFlag==1)
				{
				if(set_car_codetype==1)
					{
					set_car_codetype=0;
					CarSet_0_counter=1;//设置第1项
					pMenuItem=&Menu_0_loggingin;
					}
				else if((NET_SET_FLAG==1)&&(Exit_to_Idle==1))
					{
					Exit_to_Idle=0;
					pMenuItem=&Menu_1_Idle;
					}
				else if(NET_SET_FLAG==1)
					{
					NET_SET_FLAG=2;
					pMenuItem=&Menu_8_SetDNS;
					}
				else
					pMenuItem=&Menu_1_Idle;
				pMenuItem->show();
				memset(password_Code,0,sizeof(password_Code));
				password_SetFlag=1;
				password_Counter=0;
				}
			else if(CAR_SET_FLAG==1)
				{
				pMenuItem=&Menu_8_SetDNS;
				pMenuItem->show();

				CAR_SET_FLAG=0;
				}
			break;
		case KeyValueOk:
			if((password_SetFlag>=1)&&(password_SetFlag<=6))
				{
				if(password_Counter<=9)
					password_Code[password_SetFlag-1]=password_Counter+'0';
				password_Counter=0;
				password_SetFlag++;	
				password_Set(0);
				//rt_kprintf("\r\nok:password=%s,password_SetFlag=%d,password_Counter=%d\r\n",password_Code,password_SetFlag,password_Counter);
				}		
			else if(password_SetFlag==7)
				{
				if(strncmp((char *)password_Code,ENTER_CODE,6)==0)    
					{
					if(NET_SET_FLAG==1)
						{
						NET_SET_FLAG=2;
						password_SetFlag=0;/////
						
						lcd_fill(0);
						lcd_text12(36,3,"密码正确",8,LCD_MODE_SET);
						lcd_text12(6,19,"按确认设置网络信息",18,LCD_MODE_SET);
						lcd_update_all();
						}
					else
						{
						password_SetFlag=8;	
						Password_correctFlag=1;
						set_car_codetype=1;
						
						lcd_fill(0);
						lcd_text12(36,3,"密码正确",8,LCD_MODE_SET);
						lcd_text12(0,19,"按菜单键进入设置信息",20,LCD_MODE_SET);
						lcd_update_all();
						}
					}
				else
					{
					password_SetFlag=9;
					lcd_fill(0);
					lcd_text12(36,3,"密码错误",8,LCD_MODE_SET);
					lcd_text12(12,19,"按确认键重新设置",16,LCD_MODE_SET);
					lcd_update_all();
					}
				}
			else if(password_SetFlag==9)
				{
				pMenuItem=&Menu_0_0_password;
				pMenuItem->show();
				}
			else if(NET_SET_FLAG==2)
				{
				NET_SET_FLAG=3;
				pMenuItem=&Menu_8_SetDNS;
				pMenuItem->show();
				}
			break;
		case KeyValueUP:
			if((password_SetFlag>=1)&&(password_SetFlag<=6))
				{
				if(password_Counter==0)
					password_Counter=9;
				else if(password_Counter>=1)
					password_Counter--;
				password_Set(password_Counter);
				}
			//rt_kprintf("\r\n  up:password=%s,password_SetFlag=%d,password_Counter=%d\r\n",password_Code,password_SetFlag,password_Counter);
			break;
		case KeyValueDown:
			if((password_SetFlag>=1)&&(password_SetFlag<=6))
				{
				password_Counter++;
				if(password_Counter>9)
					password_Counter=0;
				password_Set(password_Counter);	
				}
			//rt_kprintf("\r\ndown:password=%s,password_SetFlag=%d,password_Counter=%d\r\n",password_Code,password_SetFlag,password_Counter);
			break;
		}
	KeyValue=0;
}


static void timetick(unsigned int systick)
{
	Cent_To_Disp();
	if(Dis_deviceid_flag>=2)
		{
		Dis_deviceid_flag++;
		if(Dis_deviceid_flag>=50)
			{
			Dis_deviceid_flag=0;
			}
		}

	CounterBack++;
	if(CounterBack!=MaxBankIdleTime*5)
		return;
	CounterBack=0;

	if(Password_correctFlag==1)
		{
		pMenuItem=&Menu_1_Idle;
		pMenuItem->show();
		memset(password_Code,0,sizeof(password_Code));
		password_SetFlag=1;
		password_Counter=0;
		}

}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_0_0_password=
{
"密码设置",
	8,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};


