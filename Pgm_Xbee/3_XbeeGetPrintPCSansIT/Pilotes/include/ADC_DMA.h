//________________________________________________________________________
//
//  COMPATIBLE avec "stm32f10x.h" et "Clock.h" (lors du passage KEIL4.53) 
//________________________________________________________________________
//


#include "stm32f10x.h"

/******************************************************************************
* File Name          : ADC_DMA.h
* Author             : T Rocacher
* Version            : Drivers_STM32F103_107_Juillet_2016_c
* Date               : 4 /11 / 2011, 
* Description        : Module qui configure les ADC 12 bits avec possibilit� de DMA
* MISE A JOUR		 		: + ajout� la calibration dans les dex fcts principales (Sept 2016):
											Init_TimingADC_ActiveADC
											Init_ADC1_DMA_Mult_Chan                    
*******************************************************************************/


#ifndef _ADC_DMA_H__
#define _ADC_DMA_H__

//===========================================================================================================
// Rappel sur les ressources 
//
//  - 2ADC 16 canaux, 12 bits
//  - Les broches :
//		- ADC_In0  PA0
//		- ADC_In1	PA1
//		- ADC_In2	PA2
//		- ADC_In3	PA3
//		- ADC_In4	PA4
//		- ADC_In5 	PA5
//		- ADC_In6	PA6
//		- ADC_In7	PA7
//		- ADC_In8	PB0
//		- ADC_In9	PB1
//		- ADC_In10	PC0
//		- ADC_In11	PC1
//		- ADC_In12	PC2
//		- ADC_In13	PC3
//		- ADC_In14	PC4
//		- ADC_In15	PC5
//
// 	-  ADCck Maxi = 14MHz
//	
//===========================================================================================================


//===========================================================================================================================================
// FONCTION DE CONFIGURATION EN MODE SINGLE
//===========================================================================================================================================
//_______________________________________________________________________________________
//
// CONF : Initialisation de base de l'ADC en single channel
//_______________________________________________________________________________________
float Init_TimingADC_ActiveADC( ADC_TypeDef * ADC, float Duree_Ech_us );

//_______________________________________________________________________________________
//
// CONF : alignement des data, quelque soit le mode
//_______________________________________________________________________________________
#define ALIGN_DROITE_16_0(ADC) ADC->CR2=ADC->CR2&~(ADC_CR2_ALIGN)
#define ALIGN_GAUCHE_1_15(ADC) ADC->CR2=ADC->CR2|(ADC_CR2_ALIGN)

//_______________________________________________________________________________________
//
// USE : choix du canal
//_______________________________________________________________________________________
void Single_Channel_ADC(ADC_TypeDef * ADC, char Voie_ADC);

//_______________________________________________________________________________________
//
// use : lancement conversion single
//_______________________________________________________________________________________ 
#define Start_ADC_Conversion(ADC) ADC->CR2=	(ADC->CR2)|0x01;


//_______________________________________________________________________________________
//
// USE : scrutation ADC single
//_______________________________________________________________________________________
void Wait_On_EOC_ADC ( ADC_TypeDef * ADC);

//_______________________________________________________________________________________
//
// CONF : ADC en IT apr�s chaque conv
//_______________________________________________________________________________________
void Init_IT_ADC_EOC(ADC_TypeDef * ADC, char Prio, void (*IT_function) (void));

//_______________________________________________________________________________________
//
// USE : Lire l'ADC
//_______________________________________________________________________________________
#define Read_ADC(ADC) (ADC->DR)









//===========================================================================================================================================
// FONCTIONS DE CONFIGURATION/UTILISATION ADC AVEC DMA
//===========================================================================================================================================
//_______________________________________________________________________________________
//
// CONF : Association DMA - ADC1 (transferts 16 bits)
//_______________________________________________________________________________________
void Init_ADC1_DMA(char Circ, vu16 *Ptr_Table_DMA, char Nb_Echantillons, char DMA_En);

//_______________________________________________________________________________________
//
// CONF : ADC1 en DMA multi channel mode continu (lancement en boucle)
//_______________________________________________________________________________________

float Init_ADC1_DMA_Mult_Chan_Continuous(char Nb_Canaux, char Seq_Canaux[], float Duree_Ech_us);

//_______________________________________________________________________________________
//
// CONF : ADC1 en DMA multi channel mode scan (un lancement d'une seule DMA multi chan)
//_______________________________________________________________________________________

float Init_ADC1_DMA_Mult_Chan_ScanMode(char Nb_Canaux, char Seq_Canaux[], float Duree_Ech_us);

//_______________________________________________________________________________________
//
// CONF : ADC en IT apr�s chaque DMA
//_______________________________________________________________________________________
void Init_IT_End_Of_DMA1(char Prio, void (*IT_function) (void));

//_______________________________________________________________________________________
//
// USE : lancement DMA avec NB d'�chantillons � sp�cifier
//_______________________________________________________________________________________
void Start_DMA1(u16 NbEchDMA);

//_______________________________________________________________________________________
//
// USE : scrutation DMA
//_______________________________________________________________________________________
void Wait_On_End_Of_DMA1(void);

//_______________________________________________________________________________________
//
// USE : arr�t DMA
//_______________________________________________________________________________________
#define  Stop_DMA1 DMA1_Channel1->CCR =(DMA1_Channel1->CCR) &~0x1;
// Bloque le p�riph DMA. Normalement peu utile. 


//_______________________________________________________________________________________
//
// USE : lecture tableau DMA
//_______________________________________________________________________________________

vu16 ADC_Lire_DMA(int Voie);










//===========================================================================================================================================
//  FONCTIONS DE LANCEMENT MAT�RIEL ADC
//===========================================================================================================================================
//_______________________________________________________________________________________
//
// CONF : Trigger externe
//_______________________________________________________________________________________
void Init_Conversion_On_Trig_Timer(ADC_TypeDef * ADC , char Source, float Freq_KHz);
// l'ADC est lanc� mat�riellement par un timer
// Le timer est lanc� (en PWM 50% interne au uC)
// Les sources de d�clenchement :
#define TIM1_CC1 0
#define TIM1_CC2 1
#define TIM1_CC3 2
#define TIM2_CC2 3
#define TIM4_CC4 5




#endif
