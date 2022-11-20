/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h"
#include "../pong/pong.h"
#include "../RIT/RIT.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/


extern int AD_current, pause;
unsigned int j, diff, distanzabordo;   
extern paddle paddlePos;
extern ball ballPos;
extern ballMovimento ballMov;


void ADC_IRQHandler(void) {
  
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  AD_current = (AD_current * 239 / 0xFFF);			//proporzione per settere valore in un range tra 0 e 239, ossia la larghezza in pixel dello schermo
	

	if(pause != 1){			//se il gioco non e' in pausa allora muovi il paddle
	if(AD_current < paddlePos.centro-3  |  AD_current > paddlePos.centro+3){			//margine per evitare oscillazioni potenziometro
		
		if(AD_current > paddlePos.centro){								//se si deve spostare verso destra
			diff = AD_current - paddlePos.centro;
			distanzabordo = 239 - AD_current;
			
			if(distanzabordo < 20){													//paddle andr� a contatto con il bordo destro
				if(239-paddlePos.centro!=paddlePos.length/2){
					for(j=0; j<paddlePos.length; j++){
						LCD_DrawLine(paddlePos.estremoDx-j,287,paddlePos.estremoDx-j,278,Black);
						LCD_DrawLine(239-j,287,239-j,278,Green);
					}
					paddlePos.estremoSx = 199;
					paddlePos.estremoDx = 239;
					paddlePos.centro = 219;
				}
			}else if(diff>=40){															//se paddle si sposta di un numero di pixel maggiore della sua lunghezza
				j=0;
				while(j<diff){
					LCD_DrawLine(paddlePos.estremoSx+j,287,paddlePos.estremoSx+j,278,Black);
					LCD_DrawLine(paddlePos.estremoDx+1+j,287,paddlePos.estremoDx+1+j,278,Green);
					j++;
				}
				paddlePos.estremoSx = AD_current-paddlePos.length/2;
				paddlePos.estremoDx = AD_current+paddlePos.length/2;
				paddlePos.centro = AD_current;
			}else if(diff<40){															//se paddle si sposta di un numero di pixel minore della sua lunghezza
				for(j=0; j<diff; j++){
					LCD_DrawLine(paddlePos.estremoSx+j,287,paddlePos.estremoSx+j,278,Black);
					LCD_DrawLine(paddlePos.estremoDx+j,287,paddlePos.estremoDx+j,278,Green);
				}
					paddlePos.estremoSx = AD_current-paddlePos.length/2;
					paddlePos.estremoDx = AD_current+paddlePos.length/2;
					paddlePos.centro = AD_current;
			}	
		}else if(AD_current < paddlePos.centro){						//se si deve spostare verso sinistro
			diff = paddlePos.centro -	AD_current;
			distanzabordo = AD_current;
			
			if(distanzabordo < 20){														//paddle andr� a contatto con il bordo sinistro
				if(paddlePos.centro!=paddlePos.length/2){
					for(j=0; j<paddlePos.length; j++){
						LCD_DrawLine(paddlePos.estremoSx+j,287,paddlePos.estremoSx+j,278,Black);
						LCD_DrawLine(j,287,j,278,Green);
					}
					paddlePos.estremoSx = 0;
					paddlePos.estremoDx = 40;
					paddlePos.centro = 20;
				}
			}else if(diff>=40){																//se paddle si sposta di un numero di pixel maggiore della sua lunghezza
				j=0;
				while(j<diff){
					LCD_DrawLine(paddlePos.estremoDx-j,287,paddlePos.estremoDx-j,278,Black);
					LCD_DrawLine(paddlePos.estremoSx-1-j,287,paddlePos.estremoSx-1-j,278,Green);
					j++;
				}
				paddlePos.estremoSx = AD_current-paddlePos.length/2;
				paddlePos.estremoDx = AD_current+paddlePos.length/2;
				paddlePos.centro = AD_current;			
			}else if(diff<40){																	//se paddle si sposta di un numero di pixel maggiore della sua lunghezza
				for(j=0; j<diff; j++){
					LCD_DrawLine(paddlePos.estremoDx-j,287,paddlePos.estremoDx-j,278,Black);
					LCD_DrawLine(paddlePos.estremoSx-j,287,paddlePos.estremoSx-j,278,Green);
				}
				paddlePos.estremoSx = AD_current-paddlePos.length/2;
				paddlePos.estremoDx = AD_current+paddlePos.length/2;
				paddlePos.centro = AD_current;				
			}	
		}
	}

}	
}
