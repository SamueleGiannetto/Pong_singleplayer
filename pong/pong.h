																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           pong.h
** Last modified Date:  2021-12-20
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_pong, funct_pong .c files
** Correlated files:    lib_pong.c, funct_pong.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#ifndef __PONG_H
#define __PONG_H

/* lib_pong.c */
extern void startingPitchConf(void);
extern void startingBallConf(void);
extern void startingPaddleConf(void);

/* funct_pong.c */
extern void movimentoPallina(char nord_sud, char ovest_est);
extern void colpitoPaddle(void);
extern void colpitoMuro(void);
extern void punteggioNuovo(void);
extern void pallinaCaduta(void);
#endif /* end __TIMER_H */

typedef struct{
	unsigned int length;										//posizione del paddle
	unsigned int estremoSx;
	unsigned int estremoDx;
	unsigned int centro;
	unsigned int superficie;
}paddle;

typedef struct{
	unsigned int dim;
	unsigned int x;					//coordinate del vertice in basso a sinistra della pallina
	unsigned int y;
	unsigned int centroX;		//coordinata del centro in basso della pallina (punto a contatto con il paddle) 
}ball;

typedef struct{						//angolazione del movimento della pallina e numero di pixel di cui si sposta a ogni RIT
	char nord_sud;
	char ovest_est;
	int angolazioneX;
	int angolazioneY;
}ballMovimento;

typedef struct{
	int record;						
	int score;
}punteggio;
