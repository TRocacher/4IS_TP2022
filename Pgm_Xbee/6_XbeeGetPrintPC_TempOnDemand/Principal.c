/*
Modif texte peda
Ajouter "après 1 seconde : ligne 0 temp = (ligne 1 ready... ) 
*/


#include "clock.h"
#include "API_ADC.h"
#include "Timer_1234.h"
#include "USART_rev2021.h"
#include "GPIO.h"
#include "FctDiverses_v2.h"
#include "API_Xbee_ModeAT_2022.h"
#include "LCD.h"
#include <string.h>

#include "stdio.h"



// définitions Thermomètre
#define ResADC_to_Volt (5.0/4095.0)
#define m (16.43)
#define p (-26.07)
int CNT_Moy;
float Temperature,TemperatureMoy;
char TempRecu;

void IT_1Sec(void);
void LCD_ClearLine_0(void);
void LCD_ClearLine_1(void);

char * ChaineRecue;
char Code[]="Temp?";

#define XbeeMy (0xB2)
#define XbeeMaster (0xAA)
#define XbeeChannel (0x1A)
#define XbeePanID (0xFF)

char Reponse[50];

int main (void)
{
CLOCK_Configure();

// test
	Float2Tring(25.6);
	Float2Tring(-15.4);
	
// Configuration du thermomètre
ADC_Global_Conf(PB1);
CNT_Moy=0;	
Temperature=0.0;
TemperatureMoy=0.0;	
TempRecu=0;	

// Affichage LCD Ligne 0 : « Hello ! », Ligne 1 : « Ready ...» pendant 1 seconde
lcd_init();
lcd_clear();
set_cursor(0,0); lcd_print("Hello !");
set_cursor(0,1); lcd_print("Please Wait ...");	

Delay_x_ms(1000);		
	
// configuration Xbee	
Xbee_Init(XbeeChannel, XbeePanID, XbeeMy);
Xbee_Fix_DestAdress(XbeeMaster);	

LCD_ClearLine_1();
set_cursor(0,1); lcd_print("Ready ...");		
	
Timer_1234_Init(TIM1,10000);
Active_IT_Debordement_Timer( TIM1, 10, IT_1Sec);		
	

	
while(1)
	{
		if (TempRecu==1)
		{
			TempRecu=0;
			// Affichage de la température de votre thermomètre sur la ligne 0
			LCD_ClearLine_0();
			lcd_print("Temp =");
			lcd_print (Float2Tring(TemperatureMoy));
			lcd_print(" °C");
		}
		if (Xbee_Is_Str_Received()==1)
		{
			    //Affichage de tout message reçu sur la ligne 1
					ChaineRecue=Xbee_Get_Str();
					LCD_ClearLine_1();
					lcd_print(ChaineRecue);
			
				//Accusé de réception «OK» sur tout message reçu différent de «Temp?»
				if (strcmp(ChaineRecue, Code)!=0) Xbee_Send_Str("zut");
		
				//Sur demande «Temp?», le µC renvoie toute la température au demandeur du type : 
				//"B1-Temp : 18.2"     (dans ce exemple B1 est le binôme interrogé)
				else 
				{
					Xbee_Send_Str("B2-Temp :");
					Xbee_Send_Str(Float2Tring(TemperatureMoy));
					Xbee_Send_Str("°C\r");
				}
			
		}

				

			 
	}	
}



void IT_1Sec(void)
{
		Temperature+= m*ResADC_to_Volt*(float)ADC_Get_Value(PB1)+p;
	  CNT_Moy++;
	  if (CNT_Moy==100) 
			{
				CNT_Moy=0;
				TemperatureMoy=Temperature/100.0;
				Temperature=0;
				TempRecu=1;
			}
}



void LCD_ClearLine_0 (void)
{
	set_cursor(0,0); lcd_print("                 ");set_cursor(0,0);
}

void LCD_ClearLine_1 (void)
{
	set_cursor(0,1); lcd_print("                 ");set_cursor(0,1);
}


