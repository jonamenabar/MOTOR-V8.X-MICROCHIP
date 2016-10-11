/* Aca van todos los prototipos de funciones 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _BSP_H
#define _BSP_H

void bsp_init(); //prototipo de inicializador de hardware aca llamo a otras funciones para iniciar hardware

/*-------------------------------DEFINO POSICION DE LEDS EN ARREGLO-------------------------------------*/
//Cilindro 1
#define rojo1  0 //RA0
#define verde1 1 //RA1
#define azul1  2 //RA2
//Cilindro 3
#define rojo3  3 //RA3
#define verde3 4 //RC3
#define azul3  5 //RA5
//cilindro 5
#define rojo5  6 //RC0
#define verde5 7 //RC1
#define azul5  8 //RC2
//cilindro 7
#define rojo7  9  //RB1
#define verde7 10 //RB2
#define azul7  11 //RB4

/*------------------------DEFINO LOS PULSADORES---------------------------------------------------------*/
#define 	SENSOR_AR PORTBbits.RB0 //SENSOR ARBOL DE LEVA
#define 	SENSOR_CI PORTBbits.RB5 //SENSOR CIGUE?AL
/*------------------------DEFINO LOS TIEMPOS------------------------------------------------------------*/
#define ANTIREBOTE  __delay_ms(500)  //ANTI REBOTE, REVISAR SI EL TIEMPO ES MUY LARGO
#define DELAY_FLASH __delay_ms(80) //establezco un delay para los flash
#define RETARDO __delay_ms(4)    //ESTABLEZCO UN DELAY DE 100 ms
#define TIEMPO_PRUEBA __delay_ms(2000); //10 segundos.
/*------------------------DEFINO ESTADOS----------------------------------------------------------------*/
#define ENCENDER 1
#define APAGAR   0
#endif