#include  <string.h>
#include "Menu_Include.h"

u8 DNS_dis_counter=1;

void Disp_DnsIP(u8 counter)
{
u8 apn[20] ={"APN: "};
u8 dns1[20]={"DNS1:jt1.gghypt.net"};
u8 dns2[20]={"DNS2:jt2.gghypt.net"};
u8 dns3[20]={"DNS1:up.gps960.com"};
u8 dns4[20]={"DNS2:up.soo8.com"};
u8 len1=0,len2=0;	

switch(counter)
	{
	case 1:
		len1=strlen(dns1);
		len2=strlen(dns2);
		lcd_fill(0);
		lcd_text12(0, 3,dns1,len1,LCD_MODE_SET);
		lcd_text12(0,18,dns2,len2,LCD_MODE_SET);
		lcd_update_all();
		break;
	case 2:
		len1=strlen(dns3);
		len2=strlen(dns4);
		lcd_fill(0);
		lcd_text12(0, 3,dns3,len1,LCD_MODE_SET);
		lcd_text12(0,18,dns4,len2,LCD_MODE_SET);
		lcd_update_all();
		break;
	case 3:
		if(strncmp((char *)APN_String,"CMNET",5)==0)
			{
			memcpy(apn+5,"CMNET",5);
			len1=5;
			}
		else if(strncmp((char *)APN_String,"UNINET",6)==0)
			{
			memcpy(apn+5,"UNINET",6);
			len1=6;
			}
		lcd_fill(0);
		lcd_text12(0,3,(char *)apn,5+len1,LCD_MODE_SET);
		lcd_update_all();
		break;
	default:
		break;
	}

}
static void msg( void *p)
{
}
static void show(void)
	{
	DNS_dis_counter=1;
    if(Vechicle_Info.Vech_Type_Mark==1)//客运车
		Disp_DnsIP(2);
	else
		Disp_DnsIP(1);
	}
static void keypress(unsigned int key)
{

	switch(KeyValue)
		{
		case KeyValueMenu:
			CounterBack=0;
			
			pMenuItem=&Menu_2_InforCheck;
			pMenuItem->show();
			
			break;
		case KeyValueOk:
			if(Vechicle_Info.Vech_Type_Mark==1)//客运车
				{
				Disp_DnsIP(2);
				}
			else
				{
				Disp_DnsIP(1);
				}
			break;
		case KeyValueUP:
			if(Vechicle_Info.Vech_Type_Mark==1)//客运车
				{
				Disp_DnsIP(2);
				}
			else
				{
				if(DNS_dis_counter==1)
					DNS_dis_counter=3;
				else
					DNS_dis_counter--;
				Disp_DnsIP(DNS_dis_counter);
				}
			break;
		case KeyValueDown:
			if(Vechicle_Info.Vech_Type_Mark==1)//客运车
				{
				Disp_DnsIP(3);
				}
			else
				{
				if(DNS_dis_counter==3)
					DNS_dis_counter=1;
				else
					DNS_dis_counter++;
				Disp_DnsIP(DNS_dis_counter);
				}
			break;
		}
 KeyValue=0;
}


static void timetick(unsigned int systick)
{
	CounterBack++;
	if(CounterBack!=MaxBankIdleTime)
		return;
	CounterBack=0;
	pMenuItem=&Menu_1_Idle;
	pMenuItem->show();

}


MENUITEM	Menu_2_8_DnsIpDisplay=
{
"DNS显示",
	7,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

