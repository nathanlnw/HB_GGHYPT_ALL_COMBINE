#include "Menu_Include.h"
#include "App_moduleConfig.h"

u8 Dis_screen_8_flag=0;


unsigned char noselect_8[]={0x3C,0x7E,0xC3,0xC3,0xC3,0xC3,0x7E,0x3C};//空心
unsigned char select_8[]={0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C};//实心

DECL_BMP(8,8,select_8); DECL_BMP(8,8,noselect_8); 

static unsigned char menu_pos=0;
static PMENUITEM psubmenu[6]=
{
	&Menu_8_1_MainDnsPort,
	&Menu_8_2_AuxDnsPort,
	&Menu_8_3_MainIpPort,
	&Menu_8_4_AuxIpPort,
	&Menu_8_5_ProDnsIp,
	&Menu_8_6_Apn,
};
static void menuswitch(void)
{
unsigned char i=0;
	
lcd_fill(0);
lcd_text12(0,3,"网络",4,LCD_MODE_SET);
lcd_text12(0,17,"设置",4,LCD_MODE_SET);
for(i=0;i<6;i++)
	lcd_bitmap(30+i*11, 5, &BMP_noselect_8, LCD_MODE_SET);
lcd_bitmap(30+menu_pos*11,5,&BMP_select_8,LCD_MODE_SET);
lcd_text12(30,19,(char *)(psubmenu[menu_pos]->caption),psubmenu[menu_pos]->len,LCD_MODE_SET);
lcd_update_all();
}
static void msg( void *p)
{

}
static void show(void)
{
if(Dis_screen_8_flag==0)
	{
    Dis_screen_8_flag=1;
	NET_SET_FLAG=1;//
    lcd_fill(0);
	lcd_text12(0,3,"网络",4,LCD_MODE_SET);
    lcd_text12(0,17,"设置",4,LCD_MODE_SET);
	lcd_text12(42,3,"网络信息设置",12,LCD_MODE_SET);
	lcd_text12(27,17,"请按确认输入密码",16,LCD_MODE_SET);
	lcd_update_all();
	}
else if(NET_SET_FLAG==3)
	{
	//网络设置选择
	menuswitch();
	Dis_screen_8_flag=2;
	}
}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:
			Dis_screen_8_flag=0;
			NET_SET_FLAG=0;
			
			pMenuItem=&Menu_1_Idle;
			pMenuItem->show();
			break;
	case KeyValueOk:
		    if(Dis_screen_8_flag==1)
		    	{
		    	pMenuItem=&Menu_0_0_password;
			    pMenuItem->show();
		    	}
			else
				{
			    pMenuItem=psubmenu[menu_pos];
			    pMenuItem->show();
				}
			break;
	case KeyValueUP:
			if(menu_pos==0) 
				menu_pos=5;
			else
				menu_pos--;
			menuswitch();		
			break;
	case KeyValueDown:
			menu_pos++;
			if(menu_pos>=5)
				menu_pos=0;
			menuswitch();
			break;
		}
	KeyValue=0;	
}

static void timetick(unsigned int systick)  
{
}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_8_SetDNS=
{
"网络信息设置",
	12,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

