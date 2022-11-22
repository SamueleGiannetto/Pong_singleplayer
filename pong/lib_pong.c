/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           pong.h
** Last modified Date:  2021-12-20
** Last Version:        V1.00
** Descriptions:        Atomic pong init functions
** Correlated files:    lib_pong.c, funct_pong.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "pong.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h"

/*----------------------------------------------------------------------------
  Functions that initialize pitch 
 *----------------------------------------------------------------------------*/

extern ball ballPos;
extern paddle paddlePos;
extern ballMovimento ballMov;
volatile int superficie;
static int i;

void startingPitchConf(void){
	LCD_Clear(Black);
	GUI_Text(10, 160, (uint8_t*) "0", White, Black);		//punteggio
	
	for(i=0; i<5; i++){												//disegno i muri
		LCD_DrawLine(i,0,i,277,Red);
		LCD_DrawLine(0,i,239,i,Red);
		LCD_DrawLine(239-i,0,239-i,277,Red);
	}
}


void startingBallConf(void){
	ballPos.dim=5;
		for(i=0; i<ballPos.dim; i++){
		//il centro della pallina si trova inizialmente al 160esimo pixel 
		LCD_DrawLine(234-i,157,234-i,161,Green);	
	}
	ballPos.x=230;
	ballPos.y=161;
	ballPos.centroX=232;
	ballMov.nord_sud='s';
	ballMov.ovest_est='o';
	ballMov.angolazioneX=1;				//angolazione iniziale di 45� a partire dalla met� del muro di destra
	ballMov.angolazioneY=1;
}


void startingPaddleConf(void){
	for(i=0; i<10; i++){					//disegno paddle 
		LCD_DrawLine(104,287-i, 143, 287-i, Green);
	}		
	paddlePos.length=41;
	paddlePos.estremoSx=104;
	paddlePos.estremoDx=143;
	paddlePos.centro=(paddlePos.estremoSx+paddlePos.estremoDx)/2;
	paddlePos.superficie=278;					//altezza della superficie su cui palla dovr� rimbalzare
}
