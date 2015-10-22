/*
 * File:   Main.c
 * Author: amenabarjonathan
 *
 * Created on 8 de OCTUBRE de 1987, 20:57
 */


#include <xc.h>
#include <pic16f873a.h>

// PIC16F873A Configuration Bit Settings

// 'C' source line config statements



// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000
//DEFINO LOS NOMBRE PARA QUE SEA MAS FACIL RECORDAR

#define 	SENSOR_AR PORTBbits.RB0 //SENSOR ARBOL DE LEVA
#define 	SENSOR_CI PORTBbits.RB5 //SENSOR CIGUE?AL

//-------------------DEFINO LEDS------------------
//Cilindro 1
#define ROJO1  PORTAbits.RA0=1
#define CYAN1 PORTAbits.RA1=1 & PORTAbits.RA2=1  //VERDE BIT 4 PUERTO1  (BIT4 Y BIT 2 ON) VERDE+AZUL
#define AZUL1	PORTAbits.RA2=1
#define AMARILLO1 PORTAbits.RA1=1 & PORTAbits.RA0 // VERDE BIT 4 + ROJO BIT 3
#define BLANCO1  PORTAbits.RA0=1 & (PORTAbits.RA1=1 & PORTAbits.RA2=1) // BIT 3+ BIT 2+BIT 4

//Cilindro 3
#define ROJO3  PORTAbits.RA3=1
#define CYAN3  PORTAbits.RA4=1 & PORTAbits.RA5=1 //BIT 2
#define AZUL3	PORTAbits.RA5=1
#define AMARILLO3  PORTAbits.RA4=1 & PORTAbits.RA3=1
#define BLANCO3	 PORTAbits.RA3=1 & (PORTAbits.RA4=1 & PORTAbits.RA5=1)

//cilindro 5
#define ROJO5  PORTCbits.RC0=1
#define CYAN5  PORTCbits.RC1=1 & PORTCbits.RC2=1
#define AZUL5	PORTCbits.RC2=1
#define AMARILLO5 PORTCbits.RC1=1 & PORTCbits.RC0=1
#define BLANCO5 PORTCbits.RC0=1 & (PORTCbits.RC1=1 & PORTCbits.RC2)

//cilindro 7
#define ROJO7  PORTBbits.RB1=1
#define CYAN7  PORTBbits.RB2=1 & PORTBbits.RB4=1
#define AZUL7	PORTBbits.RB4=1
#define AMARILLO7 PORTBbits.RB1=1 & PORTBbits.RB2=1
#define BLANCO7 PORTBbits.RB1=1 & (PORTBbits.RB2=1 & PORTBbits.RB4)

void main(void) {

    //ANSELA=0;
    

    PEIE = 0;
    GIE = 0;
    //ANSELA = 0; //desconfiguramos los canales AD del PORTA (RA0-RA7)


    int const SI = 1;
    int const NO = 0;


    //----------DEFINO VARIABLES--------------------
    int contador = 4;
    int inicio = 0;

    //*********Configuracion de los pines**********
    //PINES DE ENTRADA DE DATOS
    TRISBbits.TRISB0 = 1; //SENSOR ARBOL DE LEVA RB0
    TRISBbits.TRISB5 = 1; //SENSOR CIGUE—AL RB5

    //CONFIGURO LOS PINES DE SALIDA (PARA LUCES DE MOTOR) P1DIR |= BIT0;
    TRISAbits.TRISA2 = 0; //CILINDRO 1 AZUL
    TRISAbits.TRISA0 = 0; //CILINDRO 1 ROJO
    TRISAbits.TRISA1 = 0; //CILINDRO 1 VERDE

    TRISAbits.TRISA5 = 0; //CILINDRO 3 AZUL
    TRISAbits.TRISA3 = 0; //CILINDRO 3 ROJO
    TRISAbits.TRISA4 = 0; //CILINDRO 3 VERDE

    TRISCbits.TRISC2 = 0; //CILINDRO 5 AZUL
    TRISCbits.TRISC0 = 0; //CILINDRO 5 ROJO
    TRISCbits.TRISC1 = 0; //CILINDRO 5 VERDE

    TRISBbits.TRISB1 = 0; //CILINDRO 7 ROJO
    TRISBbits.TRISB2 = 0; //CILINDRO 7 VERDE
    TRISBbits.TRISB4 = 0; //CILINDRO 7 AZUL

    //************************************ secuencia de encendido de luces motor CILINDRO 1**************************************************************************************
    /*El cilindro 1 le corresponen los tiempos junto al contador como sigue>
     contador :  0-explosi€n
     2-escape
     4-admision
     6-compresi€n

     */
    while (1) {

        do {
            if (SENSOR_AR == SI)
                inicio = SI;
        } while (inicio == 0);

        if (SENSOR_AR == SI) {
            contador = 0;
        }

        if (SENSOR_CI == SI)
            contador++;

        switch (contador) {
            case 0:
                BLANCO1;
                AMARILLO1;
                AZUL3;
                ROJO5;
                ROJO7;
                break;
            case 1:
                AMARILLO1;
                CYAN3;
                AZUL5;
                ROJO7;
                break;
            case 2:
                ROJO1;
                CYAN3;
                AZUL5;
                AZUL7;
                break;
            case 3:
                ROJO1;
                BLANCO3;
                AMARILLO3;
                CYAN5;
                AZUL7;
                break;
            case 4:
                AZUL1;
                AMARILLO3;
                CYAN5;
                CYAN7;
                break;
            case 5:
                AZUL1;
                ROJO3;
                BLANCO5;
                AMARILLO5;
                CYAN7;
                break;
            case 6:
                CYAN1;
                ROJO3;
                AMARILLO5;
                BLANCO7;
                AMARILLO7;
                break;
            case 7:
                CYAN1;
                AZUL3;
                ROJO5;
                AMARILLO7;
                break;
            case 8:
                CYAN1;
                AZUL3;
                ROJO5;
                AMARILLO7;
                break;
            default:
                break;
        }

    }



    return;
}
