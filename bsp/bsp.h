/* Aca van todos los prototipos de funciones 
 */

/* 
 * File:   
 * Author: Amenabar Jonathan
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef _BSP_H
#define _BSP_H

void bsp_init(); //prototipo de inicializador de hardware aca llamo a otras funciones para iniciar hardware

/*Prototipos de funciones para iniciarlizacion de hardware y varias*/
void bsp_hardware_init(void);
void bsp_led_init(void);
void bsp_sw_init(void);
void color_set(unsigned int color);
void delay(int tiempo);
void ANTIREBOTE (void);
void DELAY_FLASH (void);
void apagar(void);
void prueba(void);

unsigned char SENSOR_AR(void);
unsigned char SENSOR_CI(void);

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

/*-------------------------------DEFINO COLORES COMPUESTOS COMO NUMEROS PARA EL SWITCH------------------*/
#define ROJO1       1
#define CYAN1       2
#define AZUL1       3
#define AMARILLO1   4
#define BLANCO1     5
#define BLANCO1OFF  6
#define ROJO3       7
#define CYAN3       8
#define AZUL3       9
#define AMARILLO3  10
#define BLANCO3    11
#define BLANCO3OFF 12
#define ROJO5      13
#define CYAN5      14
#define AZUL5      15
#define AMARILLO5  16
#define BLANCO5    17
#define BLANCO5OFF 18
#define ROJO7      19
#define CYAN7      20
#define AZUL7      21
#define AMARILLO7  22
#define BLANCO7    23
#define BLANCO7OFF 24



/*------------------------DEFINO LOS PULSADORES---------------------------------------------------------*/
//#define SENSOR_AR PORTBbits.RB0 //SENSOR ARBOL DE LEVA
//#define SENSOR_CI PORTBbits.RB5 //SENSOR CIGUE?AL
/*------------------------DEFINO LOS TIEMPOS------------------------------------------------------------*/
//#define ANTIREBOTE  __delay_ms(500)  //ANTI REBOTE, REVISAR SI EL TIEMPO ES MUY LARGO
//#define DELAY_FLASH __delay_ms(80) //establezco un delay para los flash
//#define RETARDO __delay_ms(4)    //ESTABLEZCO UN DELAY DE 100 ms
//#define TIEMPO_PRUEBA __delay_ms(2000) //10 segundos.
/*------------------------DEFINO ESTADOS----------------------------------------------------------------*/
#define ENCENDER 1
#define APAGAR   0



#endif
