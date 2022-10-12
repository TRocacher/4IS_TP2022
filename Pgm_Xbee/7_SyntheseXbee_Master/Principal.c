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



// Table Correpondance
char TabCorrespondance[4]={0xB0, 0xB1, 0xB2, 0xB3};


void IT_1Sec(void);
void LCD_ClearLine_0(void);
void LCD_ClearLine_1(void);

char * ChaineRecue;
char * Ptr;
char Code[]="Temp";
char ChaineTemp[5];
char Message[50];
int i;

#define XbeeMy (0xAA)
#define XbeeUserPCAddress (0xDD)
#define XbeeChannel (0x1A)
#define XbeePanID (0xFF)

char Reponse[50];

int main (void)
{
CLOCK_Configure();

// test
	Float2Tring(25.6);
	Float2Tring(-15.4);
	

// Affichage bienvenu
lcd_init();
lcd_clear();
set_cursor(0,0); lcd_print("I am the Master !");
set_cursor(0,1); lcd_print("Please wait...");	

Delay_x_ms(1000);		
	
// configuration Xbee	
Xbee_Init(XbeeChannel, XbeePanID, XbeeMy);

// invite 
LCD_ClearLine_1();
set_cursor(0,1); lcd_print("Waiting for Cmd...");	
	
	
Timer_1234_Init(TIM1,10000);
Active_IT_Debordement_Timer( TIM1, 10, IT_1Sec);		
	

	
while(1)
	{
		
		if (Xbee_Is_Str_Received()==1)
		{
			    //Affichage de tout message reçu sur la ligne 1
					ChaineRecue=Xbee_Get_Str();
					LCD_ClearLine_1();
					lcd_print(ChaineRecue);
			
				//Test message Temp xx
				Ptr=ChaineRecue;
			  for (i=0;i<4;i++)
				{
					ChaineTemp[i]=*Ptr;
					Ptr++;
				}
				ChaineTemp[4]=0; // insertion caractère nul
				Xbee_Fix_DestAdress(XbeeUserPCAddress);
				if (strcmp(ChaineTemp, Code)!=0) Xbee_Send_Str("OK");

				else 
				{
					// demande d'une température...
					// récupération n° position 5 de la chaine de caractères
					i=ChaineRecue[5]-0x30; // ça passe !! un pointeur que je traite comme un tableau !
					Xbee_Fix_DestAdress(TabCorrespondance[i]);
					Xbee_Send_Str("Temp?\r");
					ChaineRecue=Xbee_Get_Str();
					// stockage chaine
					i=0;
					while (*ChaineRecue!=0)
					{
						Message[i]=*ChaineRecue;
						i++;
						ChaineRecue++;
						if (i==40) break;
					}
					
					
					// attente réponse
					Xbee_Fix_DestAdress(XbeeUserPCAddress);
					// retour réponse vers user PC
					Xbee_Send_Str(Message);
				}
			
		}

				

			 
	}	
}



void IT_1Sec(void)
{
		
}



void LCD_ClearLine_0 (void)
{
	set_cursor(0,0); lcd_print("                 ");set_cursor(0,0);
}

void LCD_ClearLine_1 (void)
{
	set_cursor(0,1); lcd_print("                 ");set_cursor(0,1);
}


