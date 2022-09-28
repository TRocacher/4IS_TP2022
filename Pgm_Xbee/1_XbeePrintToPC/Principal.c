
#include "clock.h"
#include "API_ADC.h"
#include "Timer_1234.h"
#include "USART_rev2018.h"

#include "FctDiverses.h"
#include "API_Xbee_ModeAT.h"
#include "LCD.h"

void EnvoieMessg(void);




int main (void)
{
CLOCK_Configure();
Xbee_Init(0x1A, 0xFF, 0xAA);
Xbee_Fix_DestAdress(0xBB);	
	
	
	
Timer_1234_Init(TIM1,1e6);
Active_IT_Debordement_Timer( TIM1, 10, EnvoieMessg);	


	

while(1)
	{
		


			 
	}	
}



void EnvoieMessg(void)
{
			Xbee_Send_Str( "coucou \r\n");
}



