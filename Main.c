/*
 * File:   Main.c
 * Author: amenabarjonathan
 *
 * Created on 8 de OCTUBRE de 1987, 20:57
 */

#define _XTAL_FREQ 4000000
#include <xc.h>
//#include <pic16f873a.h>

// PIC16F873A Configuration Bit Settings

// 'C' source line config statements



// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT-  oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF     // Power-up Timer Enable bit (PWRT enable)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


//DEFINO LOS NOMBRE PARA QUE SEA MAS FACIL RECORDAR

#define 	SENSOR_AR PORTBbits.RB0 //SENSOR ARBOL DE LEVA
#define 	SENSOR_CI PORTBbits.RB5 //SENSOR CIGUE?AL

//-------------------DEFINO LEDS------------------
//Cilindro 1
#define ROJO1  /*PORTA|=0b000001 //RA0 (HAGO UN OR PARA NO CAMBIAR LOS VALORES ANTES DEFINIDOS*/ PORTAbits.RA0=1;
#define CYAN1  /*PORTA|= 0b000110*/PORTAbits.RA1=1 ; PORTAbits.RA2=1;  //VERDE BIT 4 PUERTO1  (BIT4 Y BIT 2 ON) VERDE+AZUL 
#define AZUL1	/*PORTA|= 0b000100 //RA2*/ PORTAbits.RA2=1;
#define AMARILLO1 /*PORTA|= 0b000011*/ PORTAbits.RA1=1 ; PORTAbits.RA0=1; // VERDE BIT 4 + ROJO BIT 3
#define BLANCO1  PORTA|=0b000111//PORTAbits.RA0=1 ; PORTAbits.RA1=1 ; //PORTAbits.RA2=1 // BIT 3+ BIT 2+BIT 4

//Cilindro 3
#define ROJO3  /*PORTA|=0b001000 //RA3*/ PORTAbits.RA3=1;
#define CYAN3  /*PORTA|=0b110000/*/PORTAbits.RA4=1 ; PORTAbits.RA5=1; //BIT 2  VERDE+AZUL
#define AZUL3	/*PORTA|=0b100000 //RA5*/ PORTAbits.RA5=1;
#define AMARILLO3  /*PORTA|=0b011000//*/PORTAbits.RA4=1 ; PORTAbits.RA3=1; //VERDE + ROJO
#define BLANCO3	 PORTA|=0b111000//PORTAbits.RA3=1 ; PORTAbits.RA4=1 ; PORTAbits.RA5=1;

//cilindro 5
#define ROJO5  PORTC=0b00000001 //RC0*/ PORTCbits.RC0=1;
#define CYAN5  PORTC=0b00000110//*/PORTCbits.RC1=1 ; PORTCbits.RC2=1;// VERDE+AZUL
#define AZUL5	PORTC=0b00000100 //RC2*/ PORTCbits.RC2=1;
#define AMARILLO5 PORTC=0b00000011//PORTCbits.RC1=1 ; PORTCbits.RC0=1;// VERDE + ROJO
#define BLANCO5 PORTC=0b00000111//PORTCbits.RC0=1; PORTCbits.RC1=1 ; PORTCbits.RC2=1;

//cilindro 7
#define ROJO7  PORTB=0b00000010 //RB1*/ PORTBbits.RB1=1;
#define CYAN7  PORTB=0b00010100//*/PORTBbits.RB2=1 ; PORTBbits.RB4=1; // VERDE+AZUL
#define AZUL7	PORTB=0b00010000 //RB4*/ PORTBbits.RB4=1;
#define AMARILLO7 PORTB=0b00000110//*/PORTBbits.RB1=1 ; PORTBbits.RB2=1;// VERDE + ROJO
#define BLANCO7 PORTB=0b00010110//*/PORTBbits.RB1=1 ; PORTBbits.RB2=1 ; PORTBbits.RB4=1;

#define ANTIREBOTE  __delay_ms(500)  //ANTI REBOTE, REVISAR SI EL TIEMPO ES MUY LARGO
#define DELAY_FLASH __delay_ms(100) //establezco un delay para los flash
#define RETARDO __delay_ms(4)    //ESTABLEZCO UN DELAY DE 100 ms
#define TIEMPO_PRUEBA __delay_ms(2000); //2 segundos.


void Apagar(void); //prototipado de la funcion apagar
void prueba(void); //prototipado de la funcion prueba

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
    int UNAVEZ = 0; //Variable usada para que el flash solo se de 1 vez por vuelta

    //*********Configuracion de los pines**********
    //PINES DE ENTRADA DE DATOS
    TRISBbits.TRISB0 = 1; //SENSOR ARBOL DE LEVA RB0
    TRISBbits.TRISB5 = 1; //SENSOR CIGUEÑAL RB5

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
     contador :  0-explosiÛn
     2-escape
     4-admision
     6-compresiÛn

     */
    prueba(); /*CON ESTO PRUEBO LOS LEDS QUE TODOS LOS COLORES DE CADA UNO FUNCIONE CORRECTAMENTE */

    while (1) {

        do {
            if (SENSOR_AR == SI) {

                inicio = SI;
                ANTIREBOTE;
            }
        } while (inicio == 0);

        if (SENSOR_AR == SI) {

            contador = 0;
            ANTIREBOTE;
            Apagar();
            UNAVEZ = 1;
        }

        if (SENSOR_CI == SI) {

            contador++;
            ANTIREBOTE;
            if(contador>=9)
                contador=0;
        }
        switch (contador) {
            case 0:
                if (UNAVEZ == 1) {
                    BLANCO1;
                    DELAY_FLASH;
                }
                PORTA = 0b100011; //(AMARILLO1+AZUL3)
                /*
                AMARILLO1;
                AZUL3;*/
                
                ROJO5;
                ROJO7;
                UNAVEZ = 0;
                break;
            case 1:
                PORTA = 0b110011;
                /*AMARILLO1;
                CYAN3;*/
                
                AZUL5;
                ROJO7;

                break;
            case 2:
                PORTA = 0b110001;
                /*ROJO1;
                CYAN3;*/
                AZUL5;
                AZUL7;

                break;
            case 3:


                if (UNAVEZ == 1) {
                    BLANCO3;
                    DELAY_FLASH;
                }
                PORTA = 0b011001;//rojo1+amarillo3)
                /*ROJO1;
                AMARILLO3;*/
                CYAN5;
                AZUL7;
                UNAVEZ = 0;

                break;
            case 4:
                PORTA = 0b011100; //(AZUL1+AMARILLO3)

                /*AZUL1;
                AMARILLO3;
                 */
                CYAN5;
                CYAN7;

                break;
            case 5:


                if (UNAVEZ == 1) {
                    BLANCO5;
                    DELAY_FLASH;
                }
                PORTA = 0b001100;
                /*AZUL1;
                ROJO3;*/
                AMARILLO5;
                CYAN7;
                UNAVEZ = 0;

                break;
            case 6:

                PORTA = 0b001110;
                /*CYAN1;
                ROJO3;*/
                AMARILLO5;
                if (UNAVEZ == 1) {
                    BLANCO7;
                    DELAY_FLASH;
                }
                AMARILLO7;
                UNAVEZ = 0;

                break;
            case 7:
                PORTA |= 0b100110;
                /*CYAN1;
                AZUL3;*/
                ROJO5;
                AMARILLO7;
                

                break;
            case 8:

                PORTA |= 0b100110;
                /*CYAN1;
                AZUL3;*/
                ROJO5;
                AMARILLO7;
                

                break;
            default:
                break;
        }

    }



    return;
}

void Apagar(void) {
    PORTA = 0; //OJO REVISAR PORQUE NO SE QUE OCURRIRIA AL TRATAR DE ESCRIBIR UN PUERTO DE ENTRADA
    PORTB = 0;
    PORTC = 0;

}

void prueba(void) {

    PORTA|=0b000111;
    TIEMPO_PRUEBA;
    PORTA|=0b111111;
    TIEMPO_PRUEBA;
    BLANCO5;
    TIEMPO_PRUEBA;
    BLANCO7;
    TIEMPO_PRUEBA;
}
