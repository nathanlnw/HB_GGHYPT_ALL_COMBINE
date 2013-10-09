#include "Menu_Include.h"
#include "App_moduleConfig.h"


#define  Apn_width1  6


static u8 Apn_SetFlag=1;
static u8 Apn_SetCounter_0=0,Apn_SetCounter_1=0,Apn_SetCounter_2=0;
static u8 Apn_SetComp=0;//主域名设置完成1
static u8 Apn_AffirmCancel=0;  // 1:确认 2:取消

static u8 Apn_Type_flag=0;//区分组的选择和组内选择
static u8 Apn_Type_Counter=0;//  0: 数字    1:A-M         2:N-Z

unsigned char select_Apn[]={0x0C,0x06,0xFF,0x06,0x0C};
unsigned char ABC_Apn_0_9[13][1]={".",":","#","0","1","2","3","4","5","6","7","8","9"};
unsigned char ABC_Apn_A_M[13][1]={"A","B","C","D","E","F","G","H","I","J","K","L","M"};
unsigned char ABC_Apn_N_Z[13][1]={"N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};


DECL_BMP(8,5,select_Apn);

void Apn_Type_Sel( u8 par)
{
	lcd_fill(0);
	lcd_text12(0,3,(char *)Menu_Apn,Apn_SetFlag-1,LCD_MODE_SET);
	lcd_text12(20,18,".-9  A-M  N-Z",13,LCD_MODE_SET);
	if(par==0)
		lcd_text12(20,18,".-9",3,LCD_MODE_INVERT);
	else if(par==1)
		lcd_text12(20+5*6,18,"A-M",3,LCD_MODE_INVERT);
	else if(par==2)
		lcd_text12(20+10*6,18,"N-Z",3,LCD_MODE_INVERT);
	lcd_update_all();
}

void Apn_Set(u8 par,u8 type1_2)
{
	lcd_fill(0);
	lcd_text12(0,3,(char *)Menu_Apn,Apn_SetFlag-1,LCD_MODE_SET);
	
	if(type1_2==1)
		{
		lcd_bitmap(par*Apn_width1, 14, &BMP_select_Apn, LCD_MODE_SET);
		lcd_text12(0,19,".:#0123456789",13,LCD_MODE_SET);
		}
	else if(type1_2==2)
		{
		lcd_bitmap(par*Apn_width1, 14, &BMP_select_Apn, LCD_MODE_SET);
		lcd_text12(0,19,"ABCDEFGHIJKLM",13,LCD_MODE_SET);
		}
	else if(type1_2==3)
		{
		lcd_bitmap(par*Apn_width1, 14, &BMP_select_Apn, LCD_MODE_SET);
		lcd_text12(0,19,"NOPQRSTUVWXYZ",13,LCD_MODE_SET);
		}
	lcd_update_all();
}

static void msg( void *p)
{

}
static void show(void)
{
CounterBack=0;
Apn_Type_Counter=0;
Apn_Type_Sel(Apn_Type_Counter);
Apn_Type_flag=1;
//rt_kprintf("\r\n选择要输入的类型");

}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:

			Apn_SetFlag=1;
            Apn_SetCounter_0=0;
			Apn_SetCounter_1=0;
			Apn_SetCounter_2=0;
			Apn_SetComp=0;//主域名设置完成1
			Apn_AffirmCancel=0;  // 1:确认 2:取消

			Apn_Type_flag=0;//区分组的选择和组内选择
            Apn_Type_Counter=0;//  0: 数字    1:A-M         2:N-Z

			
			memset(Menu_Apn,0,sizeof(Menu_Apn));
            pMenuItem=&Menu_8_SetDNS;
			pMenuItem->show();
			break;
		case KeyValueOk:
			if((Apn_Type_flag==1)&&(Apn_SetComp==0))
				{
				Apn_Type_flag=2;
				if((Apn_SetFlag>=1)&&(Apn_SetFlag<=20))
					{
					if(Apn_Type_Counter==0)
						Apn_Set(Apn_SetCounter_0,1);
					else if(Apn_Type_Counter==1)
						Apn_Set(Apn_SetCounter_1,2);
					else if(Apn_Type_Counter==2)
						Apn_Set(Apn_SetCounter_2,3);
					//rt_kprintf("\r\n第%d组",Apn_Type_Counter);
					}	
				}
			else if((Apn_Type_flag==2)&&(Apn_SetComp==0))
				{
				Apn_Type_flag=3;
				if((Apn_SetFlag>=1)&&(Apn_SetFlag<=20))
					{
					if(ABC_Apn_0_9[Apn_SetCounter_0][0]==0x23)
						{
						//rt_kprintf("\r\n*********************APN输入完成******************");
						//APN 输入完成
						Menu_Apn[Apn_SetFlag-1]=ABC_Apn_0_9[Apn_SetCounter_0][0];
						Apn_SetComp=1;
						Apn_AffirmCancel=1;
						lcd_fill(0);
						lcd_text12(0,3,(char *)Menu_Apn,Apn_SetFlag,LCD_MODE_SET);
						lcd_text12(24,18,"确认    取消",12,LCD_MODE_SET);
						lcd_text12(24,18,"确认",4,LCD_MODE_INVERT);
						lcd_update_all();
						}
					else
						{
						if(Apn_Type_Counter==0)
							{
							Menu_Apn[Apn_SetFlag-1]=ABC_Apn_0_9[Apn_SetCounter_0][0];
							Apn_SetFlag++;	
							Apn_Set(Apn_SetCounter_0,1);
							//rt_kprintf("\r\n(0_9选择)=%d",Apn_SetCounter_0);
							}
						else if(Apn_Type_Counter==1)
							{
							Menu_Apn[Apn_SetFlag-1]=ABC_Apn_A_M[Apn_SetCounter_1][0];
							Apn_SetFlag++;	
							Apn_Set(Apn_SetCounter_1,2);
							//rt_kprintf("\r\n(A_M选择)=%d",Apn_SetCounter_1);
							}
						else if(Apn_Type_Counter==2)
							{
							Menu_Apn[Apn_SetFlag-1]=ABC_Apn_N_Z[Apn_SetCounter_2][0];
							Apn_SetFlag++;	
							Apn_Set(Apn_SetCounter_2,3);
							//rt_kprintf("\r\n(N_Z选择)=%d",Apn_SetCounter_2);
							}
						if(Apn_Type_flag==3)
							{
							Apn_Type_flag=1;
							Apn_SetCounter_0=0;
							Apn_SetCounter_1=0;
							Apn_SetCounter_2=0;

							Apn_Type_Sel(Apn_Type_Counter);
							//rt_kprintf("\r\n重新选组(1_2_3)=%d",Apn_Type_Counter);
							}
						}
					}
				}
			else if(Apn_SetComp==1)
				{
				if(Apn_AffirmCancel==1)//确认
					{
					/*MainDns_AffirmCancel=3;
					MainDns_SetComp=3;
					
					MainDns_SetFlag=0;
					MainDns_SetComp=0;*/

					Apn_SetFlag=1;
		            Apn_SetCounter_0=0;
					Apn_SetCounter_1=0;
					Apn_SetCounter_2=0;
					Apn_SetComp=0;//主域名设置完成1
					Apn_AffirmCancel=0;  // 1:确认 2:取消

					Apn_Type_flag=0;//区分组的选择和组内选择
                    Apn_Type_Counter=0;//  0: 数字    1:A-M         2:N-Z

			
					lcd_fill(0);
					lcd_text12(27,3,"APN设置完成",11,LCD_MODE_SET);
					lcd_text12(24,18,"按菜单键退出",12,LCD_MODE_SET);
					lcd_update_all();
					//rt_kprintf("\r\nAPN:%s",Menu_Apn);


                    //添加相应的操作，APN 存在Menu_Apn[]中
                    //格式【CMNET#】
                    //#  设置完成结束符


					
					}
				else if(Apn_AffirmCancel==2)//取消
					{
					Apn_SetComp=2;
					Apn_AffirmCancel=4;//重新设置主域名
					lcd_fill(0);
					lcd_text12(12,10,"按确认键重新设置",16,LCD_MODE_SET);
					lcd_update_all();

					}
				}
				
			else if(Apn_SetComp==2)
				{
				//rt_kprintf("\r\n  选择取消 Apn_AffirmCancel=%d",Apn_AffirmCancel);

              
                if(Apn_AffirmCancel==4)
                	{
                	memset(Menu_MainDns,0,sizeof(Menu_MainDns));
					
					//rt_kprintf("\r\n重新设置开始");

					Apn_SetFlag=1;
					Apn_SetCounter_0=0;
					Apn_SetCounter_1=0;
					Apn_SetCounter_2=0;
					Apn_SetComp=0;//主域名设置完成1
					Apn_AffirmCancel=0;  // 1:确认 2:取消

					Apn_Type_flag=0;//区分组的选择和组内选择
                    Apn_Type_Counter=0;//  0: 数字    1:A-M         2:N-Z


					pMenuItem=&Menu_8_SetDNS;
					pMenuItem->show();
                	}
				}
			break;
		case KeyValueUP:
			if(Apn_Type_flag==1)//选择是0-9  A-M  N-Z
				{//
				if(Apn_Type_Counter==0)
					Apn_Type_Counter=2;
				else if(Apn_Type_Counter>=1)
					Apn_Type_Counter--;
				Apn_Type_Sel(Apn_Type_Counter);
				//rt_kprintf("\r\n(  up)Apn_Type_Counter=%d",Apn_Type_Counter);

				}
			else if(Apn_Type_flag==2)//组内选择
				{
				if((Apn_SetFlag>=1)&&(Apn_SetFlag<=20)&&(Apn_SetComp==0))
					{
					if(Apn_Type_Counter==0)
						{
						if(Apn_SetCounter_0==0)
							Apn_SetCounter_0=12;
						else 
							Apn_SetCounter_0--;

						Apn_Set(Apn_SetCounter_0,1);
						}
					else if(Apn_Type_Counter==1)
						{
						if(Apn_SetCounter_1==0)
							Apn_SetCounter_1=12;
						else
							Apn_SetCounter_1--;

						Apn_Set(Apn_SetCounter_1,2);
						}
					else if(Apn_Type_Counter==2)
						{
						if(Apn_SetCounter_2==0)
							Apn_SetCounter_2=12;
						else 
							Apn_SetCounter_2--;

						Apn_Set(Apn_SetCounter_2,3);
						}	
					}
				}
			else if(Apn_SetComp==1)
				{
				Apn_AffirmCancel=1;//确认
				lcd_fill(0);
				lcd_text12(0,3,(char *)Menu_Apn,Apn_SetFlag,LCD_MODE_SET);
				lcd_text12(24,18,"确认    取消",12,LCD_MODE_SET);
				lcd_text12(24,18,"确认",4,LCD_MODE_INVERT);
				lcd_update_all();
				}
			break;
		case KeyValueDown:
			if(Apn_Type_flag==1)//选择是0-9  A-M  N-Z
				{
				Apn_Type_Counter++;
				if(Apn_Type_Counter>2)
					Apn_Type_Counter=0;
				Apn_Type_Sel(Apn_Type_Counter);
				//rt_kprintf("\r\n(down)Apn_Type_Counter=%d",Apn_Type_Counter);
				}
			else if(Apn_Type_flag==2)//组内选择
				{
				if((Apn_SetFlag>=1)&&(Apn_SetFlag<=20)&&(Apn_SetComp==0))
					{
					if(Apn_Type_Counter==0)
						{
						Apn_SetCounter_0++;
						if(Apn_SetCounter_0>12)
							Apn_SetCounter_0=0;

						Apn_Set(Apn_SetCounter_0,1);
						}
					else if(Apn_Type_Counter==1)
						{
						Apn_SetCounter_1++;
						if(Apn_SetCounter_1>12)
							Apn_SetCounter_1=0;

						Apn_Set(Apn_SetCounter_1,2);
						}
					else if(Apn_Type_Counter==2)
						{
						Apn_SetCounter_2++;
						if(Apn_SetCounter_2>12)
							Apn_SetCounter_2=0;

						Apn_Set(Apn_SetCounter_2,3);
						}
					}	
				}

			else if(Apn_SetComp==1)
				{
				Apn_AffirmCancel=2;//取消
				lcd_fill(0);
				lcd_text12(0,3,(char *)Menu_Apn,Apn_SetFlag,LCD_MODE_SET);
				lcd_text12(24,18,"确认    取消",12,LCD_MODE_SET);
				lcd_text12(72,18,"取消",4,LCD_MODE_INVERT);
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
MENUITEM	Menu_8_6_Apn=
{
"APN 设置",
	8,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

