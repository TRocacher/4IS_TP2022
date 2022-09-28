
#include "clock.h"
#include "API_ADC.h"
#include "Timer_1234.h"
#include "USART_rev2018.h"

#include "FctDiverses.h"
#include "API_Xbee_ModeAT.h"
#include "LCD.h"

void EnvoieMessg(void);
void LCD_ClearLine_0(void);
void LCD_ClearLine_1(void);

char * ChaineRecue;

int main (void)
{
CLOCK_Configure();
Xbee_Init(0xD, 0xFF, 0xA1);
Xbee_Fix_DestAdress(0xB2);	
lcd_init();
lcd_clear();
set_cursor(0,0); lcd_print("Hello");
set_cursor(0,1); lcd_print("Ready ...");	

Delay_x_ms(1000);	
	
	
	
Timer_1234_Init(TIM1,1e6);
Active_IT_Debordement_Timer( TIM1, 10, EnvoieMessg);	


	

while(1)
	{
		
		ChaineRecue=Xbee_Get_Str();
		LCD_ClearLine_0();
		lcd_print(ChaineRecue);
		

			 
	}	
}



void EnvoieMessg(void)
{
			Xbee_Send_Str( "coucou \r\n");
}


void LCD_ClearLine_0 (void)
{
	set_cursor(0,0); lcd_print("                 ");set_cursor(0,0);
}

void LCD_ClearLine_1 (void)
{
	set_cursor(0,1); lcd_print("                 ");set_cursor(0,1);
}
