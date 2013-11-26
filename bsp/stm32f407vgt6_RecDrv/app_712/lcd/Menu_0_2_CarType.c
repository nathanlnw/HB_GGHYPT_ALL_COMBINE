#include  <string.h>
#include "Menu_Include.h"


struct IMG_DEF test_scr_CarType={12,12,test_00};



unsigned char CarType_Type_SEL=0;
unsigned char CarType_Type_Screen=0;
void CarType(unsigned char type_Sle) 
{
lcd_fill(0);
lcd_text12(20, 3,"货运车  客运车",14,LCD_MODE_SET);
lcd_text12(20,18,"旅游车  危品车",14,LCD_MODE_SET);
switch(type_Sle)
	{
	case 1:
	    lcd_text12(20, 3,"货运车",6,LCD_MODE_INVERT);
		break;
	case 2:
		lcd_text12(68, 3,"客运车",6,LCD_MODE_INVERT);
		break;
	case 3:
		lcd_text12(20,18,"旅游车",6,LCD_MODE_INVERT);
		break;
    case 4:
		lcd_text12(68,18,"危品车",6,LCD_MODE_INVERT);
		break;
	}
lcd_update_all();
}

static void msg( void *p)
{

}
static void show(void)
{
CounterBack=0;

CarType_Type_Screen=1;
CarType_Type_SEL=1;
CarType(CarType_Type_SEL);
}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:
			
			pMenuItem=&Menu_0_loggingin;
			pMenuItem->show();
			CarType_Type_SEL=0;
			CarType_Type_Screen=0;
			break;
		case KeyValueOk:
            if(CarType_Type_Screen==1)
				{
				CarType_Type_Screen=2;
				if(CarType_Type_SEL==1)
					{
					Vechicle_Info.Vech_Type_Mark=2;
					memcpy(Menu_VechileType,"货运车",6);
					}
				else if((CarType_Type_SEL==2)||(CarType_Type_SEL==3)||(CarType_Type_SEL==4))
					{
					Vechicle_Info.Vech_Type_Mark=1;
					if(CarType_Type_SEL==2)
						memcpy(Menu_VechileType,"客运车",6); 
					if(CarType_Type_SEL==3)
						memcpy(Menu_VechileType,"旅游车",6); 
					if(CarType_Type_SEL==4)
						memcpy(Menu_VechileType,"危品车",6); 
					}
				if(MENU_set_carinfor_flag==1)
					{
					if(CarType_Type_SEL==1)
						{
						dnsr_main("jt1.gghypt.net");
						port_main("7008");
						idip("clear"); //--------    清除鉴权码 -------------------
						}
					else if((CarType_Type_SEL==2)||(CarType_Type_SEL==3)||(CarType_Type_SEL==4))
						{
						dnsr_main("up.gps960.com");
						port_main("8201");
						idip("clear");	//--------    清除鉴权码 -------------------
						}
					rt_kprintf("\r\n车辆类型设置完成，按菜单键返回，%s",Menu_VechileType);		
					memset(Vechicle_Info.Vech_Type,0,sizeof(Vechicle_Info.Vech_Type));
					memcpy(Vechicle_Info.Vech_Type,Menu_VechileType,10);
					DF_WriteFlashSector(DF_Vehicle_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
					WatchDog_Feed();
				    DF_WriteFlashSector(DF_VehicleBAK_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
					WatchDog_Feed();
				    DF_WriteFlashSector(DF_VehicleBAK2_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));
					}
				
				lcd_fill(0);
				lcd_text12(12,3,"车辆类型选择完毕",16,LCD_MODE_SET);
				lcd_text12(6,18,"按确认键设置下一项",18,LCD_MODE_SET);
				lcd_update_all();
				}
			else if(CarType_Type_Screen==2)
				{
				CarType_Type_Screen=0;
				
				CarSet_0_counter=3;//设置第3项
				pMenuItem=&Menu_0_loggingin;
				pMenuItem->show();

				CarType_Type_SEL=0;
				CarType_Type_Screen=0;
				}
				
			break;
		case KeyValueUP:
			if(	CarType_Type_Screen==1)
				{
				if(CarType_Type_SEL==1)
					CarType_Type_SEL=4;
				else
					CarType_Type_SEL--;
				CarType(CarType_Type_SEL);
				}
			break;
		case KeyValueDown:
			if(	CarType_Type_Screen==1)
				{
				if(CarType_Type_SEL>=4)
					CarType_Type_SEL=1;
				else
					CarType_Type_SEL++;
				CarType(CarType_Type_SEL);
				}
			break;
		}
	KeyValue=0;
}


static void timetick(unsigned int systick)
{

}


MENUITEM	Menu_0_2_CarType=
{
    "车辆类型设置",
	12,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};


