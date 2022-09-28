A CONTINUER 
#include "clock.h"
#include "API_ADC.h"
#include "Timer_1234.h"
#include "USART_rev2018.h"

#include "FctDiverses.h"
#include "API_Xbee_ModeAT.h"
#include "LCD.h"
#include <string.h>

#include "stdio.h"


void EnvoieMessg(void);
void LCD_ClearLine_0(void);
void LCD_ClearLine_1(void);

char * ChaineRecue;
int Seconde=0;
char Fr[]="Bonjour";
char Angl[]="Hello";
char Cmde[]="Seconde";
char Reponse[50];

int main (void)
{
CLOCK_Configure();
Xbee_Init(0x1A, 0xFF, 0xAA);
Xbee_Fix_DestAdress(0xBB);	
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
		
		if (strcmp(ChaineRecue, Fr)==0) Xbee_Send_Str("Au revoir ... ");
		else if (strcmp(ChaineRecue, Angl)==0) Xbee_Send_Str("Goodby ...  ");		
		else if (strcmp(ChaineRecue, Cmde)==0) 
		{
			
		}
	
		else 	Xbee_Send_Str("OK");
		

			 
	}	
}



void EnvoieMessg(void)
{
			Seconde++;
}



void LCD_ClearLine_0 (void)
{
	set_cursor(0,0); lcd_print("                 ");set_cursor(0,0);
}

void LCD_ClearLine_1 (void)
{
	set_cursor(0,1); lcd_print("                 ");set_cursor(0,1);
}
