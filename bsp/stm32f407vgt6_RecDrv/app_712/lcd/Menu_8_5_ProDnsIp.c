#include "Menu_Include.h"
#include "App_moduleConfig.h"

u8 Screen_flag_8_5=0;
u8 Pro_Dns_Ip=0;

static void msg( void *p)
{

}
static void show(void)
{
if(Screen_flag_8_5==0)
	{
	Screen_flag_8_5=1;
	Pro_Dns_Ip=1;
	lcd_fill(0);
	lcd_text12(0, 3,"1.��������������",16,LCD_MODE_INVERT);
	lcd_text12(0,18,"2.����������IP",14,LCD_MODE_SET);
	lcd_update_all();
	}
}


static void keypress(unsigned int key)
{
  
	switch(KeyValue)
		{
		case KeyValueMenu:
			Pro_Dns_Ip=0;
			Screen_flag_8_5=0;
			
			pMenuItem=&Menu_8_SetDNS;
			pMenuItem->show();
			break;
		case KeyValueOk:
			if(Screen_flag_8_5==1)
				{
				Screen_flag_8_5=2;
				lcd_fill(0);
				if(Pro_Dns_Ip==1)
					lcd_text12(18,3,"��������������",14,LCD_MODE_SET);
				else if(Pro_Dns_Ip==2)
					lcd_text12(18,3,"����������IP",12,LCD_MODE_SET);
				lcd_text12(24,19,"���˵����˳�",12,LCD_MODE_SET);
				lcd_update_all();

				
				//�����Ӧ�Ĺ�������
						
						Vechicle_Info.Link_Frist_Mode=Pro_Dns_Ip-1;  

				        if(Vechicle_Info.Link_Frist_Mode==0)
		        		    rt_kprintf("\r\n �״����ӷ�ʽ: ���� \r\n");     
					    else
							rt_kprintf("\r\n �״����ӷ�ʽ: ��IP \r\n");   
							
					    DF_WriteFlashSector(DF_Vehicle_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));
						
						WatchDog_Feed();
					    DF_WriteFlashSector(DF_VehicleBAK_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
						WatchDog_Feed();
					    DF_WriteFlashSector(DF_VehicleBAK2_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));
						 //--------    �����Ȩ�� -------------------
					    idip("clear");	 	
				//--------------------------------------------------------------------------------		 

				
				}
			break;
		case KeyValueUP:
            if(Screen_flag_8_5==1)
            	{
            	Pro_Dns_Ip=1;
            	lcd_fill(0);
            	lcd_text12(12, 3,"1.��������������",16,LCD_MODE_INVERT);
				lcd_text12(12,18,"2.����������IP",14,LCD_MODE_SET);
				lcd_update_all();
            	}
			break;
		case KeyValueDown:
			 if(Screen_flag_8_5==1)
            	{
            	Pro_Dns_Ip=2;
            	lcd_fill(0);
            	lcd_text12(12, 3,"1.��������������",14,LCD_MODE_SET);
				lcd_text12(12,18,"2.����������IP",12,LCD_MODE_INVERT);
				lcd_update_all();
            	}
			break;
		}
	KeyValue=0;	
}

static void timetick(unsigned int systick)  
{
}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_8_5_ProDnsIp=
{
"����ʹ��ѡ��",
	12,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

