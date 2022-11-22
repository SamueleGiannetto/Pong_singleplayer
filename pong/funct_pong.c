/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_pong.h
** Last modified Date:  2022-6-1
** Last Version:        V1.00
** Descriptions:        High level pong management functions
** Correlated files:    lib_pong.c, funct_pong.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "pong.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "stdio.h"
#include "string.h"


/*----------------------------------------------------------------------------
  Funzioni che implementato il gioco del pong 
 *----------------------------------------------------------------------------*/


extern paddle paddlePos;
extern ball ballPos;
extern ballMovimento ballMov;
extern punteggio punt;
int contattoPunteggio=0, contattoRecord=0;
char stringaPunteggio[10];  


/*funzione che in base alle struct ballPos e ballMov sposta la pallina da una posizione con un certo movimento
ballPos contiene la posizione della pallina, ballMov dice di quanti pixel spostare pallina orizzontalmente e verticalmente e verso che direzione*/

void movimentoPallina(char nord_sud, char ovest_est){				
	static int i, j;

	if(nord_sud == 's' & ovest_est == 'o'){										//se spostamento verso sud-ovest
	
		for(i=0; i<ballMov.angolazioneX; i++){									//da 1 a 3 cicli in base ad angolazione, sposta da 1 a 3 volte pallina in orizzontale 
			LCD_DrawLine(ballPos.x+ballPos.dim-1-i, ballPos.y-ballPos.dim+1, ballPos.x+ballPos.dim-1-i, ballPos.y,Black);
			LCD_DrawLine(ballPos.x-1-i, ballPos.y-ballPos.dim+1, ballPos.x-1-i, ballPos.y,Green);
			if(ballPos.x-1-i == 5){																//se tocca il muro chiama la funzione colpitoMuro e poi return perchè non si muova più la pallina
					ballPos.x=ballPos.x-1-i;
					ballPos.y=ballPos.y;
					ballPos.centroX=ballPos.x+2;
					colpitoMuro();
					return;
			}
		}
				
		for(j=0; j<ballMov.angolazioneY; j++){									//da 1 a 3 cicli in base ad angolazione, sposta da 1 a 3 volte pallina in verticale
			LCD_DrawLine(ballPos.x-ballMov.angolazioneX, ballPos.y-ballPos.dim+1+j, ballPos.x+ballPos.dim-1-ballMov.angolazioneX, ballPos.y-ballPos.dim+1+j,Black);
			LCD_DrawLine(ballPos.x-ballMov.angolazioneX, ballPos.y+1+j, ballPos.x+ballPos.dim-1-ballMov.angolazioneX, ballPos.y+1+j,Green);
		  if(ballPos.y +j+1 == paddlePos.superficie-1){
					ballPos.x=ballPos.x-ballMov.angolazioneX;
					ballPos.y=ballPos.y+j+1;
					ballPos.centroX=ballPos.x+2;
					colpitoPaddle();
					return;
			}
			if(ballPos.y +j+1 == 305){
					pallinaCaduta();
					return;
			}
		}
		ballPos.x=ballPos.x-i;																		//setto i nuovi valori sulla coordinata del vertice in basso a sinistra della pallina
		ballPos.y=ballPos.y+j;
		ballPos.centroX=ballPos.x+2;
	}
	
	
	if(nord_sud == 's' & ovest_est == 'e'){											//se spostamento verso sud-est
		
		for(i=0; i<ballMov.angolazioneX; i++){
			LCD_DrawLine(ballPos.x+i, ballPos.y-ballPos.dim+1, ballPos.x+i, ballPos.y,Black);
			LCD_DrawLine(ballPos.x+ballPos.dim+i, ballPos.y-ballPos.dim+1, ballPos.x+ballPos.dim+i, ballPos.y,Green);
			if(ballPos.x+ballPos.dim+i == 234){
					ballPos.x=ballPos.x+1+i;
					ballPos.y=ballPos.y;
					ballPos.centroX=ballPos.x+2;
					colpitoMuro();
					return;
			}
		}
				
		for(j=0; j<ballMov.angolazioneY; j++){
			LCD_DrawLine(ballPos.x+ballMov.angolazioneX, ballPos.y-ballPos.dim+1+j, ballPos.x+ballPos.dim-1+ballMov.angolazioneX, ballPos.y-ballPos.dim+1+j,Black);
			LCD_DrawLine(ballPos.x+ballMov.angolazioneX, ballPos.y+1+j, ballPos.x+ballPos.dim-1+ballMov.angolazioneX, ballPos.y+1+j,Green);
		  if(ballPos.y +j+1 == paddlePos.superficie-1){
					ballPos.x=ballPos.x+ballMov.angolazioneX;
					ballPos.y=ballPos.y+j+1;
					ballPos.centroX=ballPos.x+2;
					colpitoPaddle();
					return;
			}
			if(ballPos.y +j+1 == 305){
					pallinaCaduta();
					return;
			}
		}
		ballPos.x=ballPos.x+i;
		ballPos.y=ballPos.y+j;
		ballPos.centroX=ballPos.x+2;
	}
	
	
	
	if(nord_sud == 'n' & ovest_est == 'o'){																//se spostamento verso nord-ovest
		
		for(i=0; i<ballMov.angolazioneX; i++){
			LCD_DrawLine(ballPos.x+ballPos.dim-1-i, ballPos.y-ballPos.dim+1, ballPos.x+ballPos.dim-1-i, ballPos.y,Black);
			LCD_DrawLine(ballPos.x-1-i, ballPos.y-ballPos.dim+1, ballPos.x-1-i, ballPos.y,Green);
			if(ballPos.x-1-i==5){
				ballPos.x=ballPos.x-1-i;
				ballPos.y=ballPos.y;
				ballPos.centroX=ballPos.x+2;
				colpitoMuro();
				return;
			}
		}
				
		for(j=0; j<ballMov.angolazioneY; j++){
			LCD_DrawLine(ballPos.x-ballMov.angolazioneX, ballPos.y-j, ballPos.x+ballPos.dim-1-ballMov.angolazioneX, ballPos.y-j,Black);
			LCD_DrawLine(ballPos.x-ballMov.angolazioneX, ballPos.y-ballPos.dim-j, ballPos.x+ballPos.dim-1-ballMov.angolazioneX, ballPos.y-ballPos.dim-j,Green);
			if(ballPos.y-ballPos.dim-j==5){
					ballPos.x=ballPos.x-ballMov.angolazioneX;
					ballPos.y=ballPos.y-j-1;
					ballPos.centroX=ballPos.x+2;
					colpitoMuro();
					return;
			}
		}
		ballPos.x=ballPos.x-i;
		ballPos.y=ballPos.y-j;
		ballPos.centroX=ballPos.x+2;
	}
	
	
	if(nord_sud == 'n' & ovest_est == 'e'){																	//se spostamento verso nord-est

		for(i=0; i<ballMov.angolazioneX; i++){
			LCD_DrawLine(ballPos.x+i, ballPos.y-ballPos.dim+1, ballPos.x+i, ballPos.y,Black);
			LCD_DrawLine(ballPos.x+ballPos.dim+i, ballPos.y-ballPos.dim+1, ballPos.x+ballPos.dim+i, ballPos.y,Green);
			if(ballPos.x+ballPos.dim+i==234){
				ballPos.x=ballPos.x+i+1;
				ballPos.y=ballPos.y;
				ballPos.centroX=ballPos.x+2;
				colpitoMuro();
				return;
			}
		}
				
		for(j=0; j<ballMov.angolazioneY; j++){
			LCD_DrawLine(ballPos.x+ballMov.angolazioneX, ballPos.y-j, ballPos.x+ballPos.dim-1+ballMov.angolazioneX, ballPos.y-j,Black);
			LCD_DrawLine(ballPos.x+ballMov.angolazioneX, ballPos.y-ballPos.dim-j, ballPos.x+ballPos.dim-1+ballMov.angolazioneX, ballPos.y-ballPos.dim-j,Green);
			if(ballPos.y-ballPos.dim-j==5){
					ballPos.x=ballPos.x+ballMov.angolazioneX;
					ballPos.y=ballPos.y-j-1;
					ballPos.centroX=ballPos.x+2;
					colpitoMuro();
					return;
			}
		}
		ballPos.x=ballPos.x+i;
		ballPos.y=ballPos.y-j;
		ballPos.centroX=ballPos.x+2;
	}
	
	if((ballPos.x<25 & ballPos.y>159 & ballPos.y<175)){				//ristampa punteggio se pallina passandoci sopra l'ha cancellato
			contattoPunteggio=1;
	}else if(contattoPunteggio==1){
			sprintf(stringaPunteggio,"%d",punt.score);
			GUI_Text(10, 160, (uint8_t*) stringaPunteggio, White, Black);
			contattoPunteggio=0;
	}		
	
	if((ballPos.x>180 & ballPos.y<30)){												//ristampa record se pallina passandoci sopra l'ha cancellato
			contattoRecord=1;
	}else if(contattoRecord==1){
			sprintf(stringaPunteggio,"%d",punt.record);
			GUI_Text(190, 10, (uint8_t*) stringaPunteggio, White, Black);
			contattoRecord=0;
	}		
}	


/*angolazioni possibili con spostamento di x pixel in orizzontale e y in verticale (x,y): (3,1),(2,1),(1,1),(1,2),(1,3) verso nord-est o verso nord-ovest
5 angolazioni differenti per ciascuna delle 2 direzioni in base a punto in cui il pixel centrale in basso della pallina tocca il paddle 
nella funzione il paddle e' diviso in 10 parti in modo da permette le 10 possibilità di spostamento*/

void colpitoPaddle(void){
	if(ballPos.y == paddlePos.superficie-1){ 	
		if(ballPos.centroX >= paddlePos.estremoSx & ballPos.centroX < paddlePos.estremoSx+3){  //se prende estremo sinistro angolazione ampiamente verso sinistra
			ballMov.nord_sud='n';
			ballMov.ovest_est='o';
			ballMov.angolazioneX=3;
			ballMov.angolazioneY=1;
			punteggioNuovo();
			enable_timer(2);								//al fine di generare il suono
		}
		if(ballPos.centroX >= paddlePos.estremoSx+3 & ballPos.centroX < paddlePos.estremoSx+8){ 
			ballMov.nord_sud='n';
			ballMov.ovest_est='o';
			ballMov.angolazioneX=2;
			ballMov.angolazioneY=1;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+8 & ballPos.centroX < paddlePos.estremoSx+13){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='o';
			ballMov.angolazioneX=1;
			ballMov.angolazioneY=1;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+13 & ballPos.centroX < paddlePos.estremoSx+18){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='o';
			ballMov.angolazioneX=1;
			ballMov.angolazioneY=2;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+18 & ballPos.centroX < paddlePos.estremoSx+20){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='o';
			ballMov.angolazioneX=1;
			ballMov.angolazioneY=3;
			punteggioNuovo();
		}
		if(ballPos.centroX >= paddlePos.estremoSx+20 & ballPos.centroX < paddlePos.estremoSx+23){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='e';
			ballMov.angolazioneX=1;
			ballMov.angolazioneY=3;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+23 & ballPos.centroX < paddlePos.estremoSx+28){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='e';
			ballMov.angolazioneX=1;
			ballMov.angolazioneY=2;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+28 & ballPos.centroX < paddlePos.estremoSx+33){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='e';
			ballMov.angolazioneX=1;
			ballMov.angolazioneY=1;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+33 & ballPos.centroX < paddlePos.estremoSx+38){  
			ballMov.nord_sud='n';
			ballMov.ovest_est='e';
			ballMov.angolazioneX=2;
			ballMov.angolazioneY=1;
			punteggioNuovo();
			enable_timer(2);
		}
		if(ballPos.centroX >= paddlePos.estremoSx+38 & ballPos.centroX < paddlePos.estremoSx+41){ 			//se prende estremo destro angolazione ampiamente verso destra
			ballMov.nord_sud='n';
			ballMov.ovest_est='e';
			ballMov.angolazioneX=3;
			ballMov.angolazioneY=1;
			punteggioNuovo();
			enable_timer(2);
		}
	}
	
}

/*calcola nuovo punteggio dopo contatto tra pallina e paddle e lo stampa*/
void punteggioNuovo(void){
	if(punt.score>=100)
		punt.score+=5;
	punt.score+=5;
	sprintf(stringaPunteggio,"%d",punt.score);
	GUI_Text(10, 160, (uint8_t*) stringaPunteggio, White, Black);
}	

/*varia la direzione della pallina mantenendo l'angolo di incidenza*/
void colpitoMuro(void){
		
	if(ballPos.x == 5){ 							 //colpito muro di sinistra
		if(ballMov.nord_sud=='n'){
			ballMov.nord_sud='n';
			ballMov.ovest_est='e';				
		}
		else if(ballMov.nord_sud=='s'){
			ballMov.nord_sud='s';
			ballMov.ovest_est='e';			
		}
	}
		
	if(ballPos.y-ballPos.dim+1 == 5){   //colpito muro di sopra
		if(ballMov.ovest_est=='o'){
			ballMov.nord_sud='s';
			ballMov.ovest_est='o';				
		}
		else if(ballMov.ovest_est=='e'){
			ballMov.nord_sud='s';
			ballMov.ovest_est='e';
		}
	}
		
	if(ballPos.x+ballPos.dim-1 == 234){   //colpito muro di destra
		if(ballMov.nord_sud=='n'){
			ballMov.nord_sud='n';
			ballMov.ovest_est='o';
				
		}
		else if(ballMov.nord_sud=='s'){
			ballMov.nord_sud='s';
			ballMov.ovest_est='o';
		}
	}
	enable_timer(3);																	//genera il suono dal contatto con il muro
}
	
	
/*controlla se il punteggio ottenuto nella partita e' un nuovo record, lo stampa, stampa piccolo tutorial e disabilita i timer per suoni e movimento pallina*/
void pallinaCaduta(void){		
		GUI_Text(90, 180, (uint8_t*) "You lose", White, Black);
		if(punt.score>punt.record){
			punt.record=punt.score;
			sprintf(stringaPunteggio,"%d",punt.score);
			GUI_Text(190, 10, (uint8_t*) stringaPunteggio, White, Black);
		}
		punt.score=0;
		GUI_Text(9, 210, (uint8_t*) "Press INT0 to reset the game", White, Black);
			
		disable_timer(1);
		disable_timer(2);
		disable_timer(3);		
}
