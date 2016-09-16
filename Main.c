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
#define ROJO1     RA0=1
#define CYAN1     RA1=1 ; RA2=1  //VERDE BIT 4 PUERTO1  (BIT4 Y BIT 2 ON) VERDE+AZUL 
#define AZUL1	  RA2=1
#define AMARILLO1 RA1=1 ; RA0=1 // VERDE BIT 4 + ROJO BIT 3
#define BLANCO1   RA0=1 ; RA1=1 ; RA2=1//PORTAbits.RA0=1 ; PORTAbits.RA1=1 ; //PORTAbits.RA2=1 // BIT 3+ BIT 2+BIT 4

//Cilindro 3
#define ROJO3     RA3=1
#define CYAN3     RC3=1 ; RA5=1  // VERDE+AZUL
#define AZUL3	  RA5=1
#define AMARILLO3 RC3=1 ; RA3=1 //VERDE + ROJO
#define BLANCO3	  RA3=1 ; RA5=1 ; RC3=1 //PORTAbits.RA3=1 ; PORTCbits.RC3=1 ; PORTAbits.RA5=1;

//cilindro 5
#define ROJO5     RC0=1
#define CYAN5     RC1=1 ; RC2=1// VERDE+AZUL
#define AZUL5	  RC2=1
#define AMARILLO5 RC1=1 ; RC0=1// VERDE + ROJO
#define BLANCO5   RC0=1 ; RC1=1 ; RC2=1

//cilindro 7
#define ROJO7     RB1=1
#define CYAN7     RB2=1 ; RB4=1 // VERDE+AZUL
#define AZUL7	  RB4=1
#define AMARILLO7 RB1=1 ; RB2=1// VERDE + ROJO
#define BLANCO7   RB1=1 ; RB2=1 ; RB4=1

#define ANTIREBOTE  __delay_ms(500)  //ANTI REBOTE, REVISAR SI EL TIEMPO ES MUY LARGO
#define DELAY_FLASH __delay_ms(80) //establezco un delay para los flash
#define RETARDO __delay_ms(4)    //ESTABLEZCO UN DELAY DE 100 ms
#define TIEMPO_PRUEBA __delay_ms(2000); //10 segundos.


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
    TRISB0 = 1; //SENSOR ARBOL DE LEVA RB0
    TRISB5 = 1; //SENSOR CIGUEÑAL RB5

    //CONFIGURO LOS PINES DE SALIDA (PARA LUCES DE MOTOR) P1DIR |= BIT0;
    TRISA2 = 0; //CILINDRO 1 AZUL
    TRISA0 = 0; //CILINDRO 1 ROJO
    TRISA1 = 0; //CILINDRO 1 VERDE

    TRISA5 = 0; //CILINDRO 3 AZUL
    TRISA3 = 0; //CILINDRO 3 ROJO
    TRISC3 = 0; //CILINDRO 3 VERDE

    TRISC2 = 0; //CILINDRO 5 AZUL
    TRISC0 = 0; //CILINDRO 5 ROJO
    TRISC1 = 0; //CILINDRO 5 VERDE

    TRISB1 = 0; //CILINDRO 7 ROJO
    TRISB2 = 0; //CILINDRO 7 VERDE
    TRISB4 = 0; //CILINDRO 7 AZUL

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

        if (SENSOR_AR == SI) { //Nota: Deberias meterlo en una interrupcion!.

            contador = 4; //ARRANCA EN EL PISTON 4
            ANTIREBOTE;
            Apagar();
            
        }

        if (SENSOR_CI == SI) { //Nota: Deberias meterlo en una interrupcion!.

            contador++;
            UNAVEZ = 1;
            ANTIREBOTE;
            if(contador>=9)
                contador=0;
        }
        switch (contador) {
            
            case 0:
                Apagar();
                PORTA = 0b100011; //(AMARILLO1+AZUL3)
                /*
                AMARILLO1;
                AZUL3;*/
                ROJO5;
                ROJO7;
                if (UNAVEZ == 1) { //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    PORTA=0b100111;// BLANCO1, tiene el RA5 en 1 para no apagar el azul 3
                    DELAY_FLASH;
                    PORTA=0b100000;;// apago solamente BLANCO1
                    DELAY_FLASH;
                    PORTA=0b100111;// BLANCO1, tiene el RA5 en 1 para no apagar el azul 3
                    DELAY_FLASH;
                }
                UNAVEZ = 0;
                break;
            
            case 1:
                Apagar();
                PORTA = 0b110011;
                RC3=1;
                /*AMARILLO1;
                CYAN3;*/
                
                AZUL5;
                ROJO7;
                break;
            
            case 2:
                Apagar();
                PORTA = 0b100001;
                RC3=1;
                /*ROJO1;
                CYAN3;*/
                AZUL5;
                AZUL7;
                break;
            
            case 3:
                Apagar();
                PORTA = 0b001001;
                RC3=1;//rojo1+amarillo3)
                /*ROJO1;
                AMARILLO3;*/
                CYAN5;
                AZUL7;
                if (UNAVEZ == 1) {
                    PORTA=0b101001; //BLANCO3 //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    RC3=1;
                    DELAY_FLASH;
                    PORTA=0b000001; //apago solo BLANCO3, dejo prendido el rojo1
                    RC3=0;
                    DELAY_FLASH;
                    PORTA=0b101001; //BLANCO3
                    RC3=1;
                    DELAY_FLASH;
                }
                UNAVEZ = 0;
                break;
            
            case 4:
                Apagar();
                PORTA = 0b001100;
                RC3=1; //(AZUL1+AMARILLO3)

                /*AZUL1;
                AMARILLO3;
                 */
                CYAN5;
                CYAN7;
                break;
            
            case 5:
                Apagar();
                PORTA = 0b001100;
                /*AZUL1;
                ROJO3;*/
                AMARILLO5;
                CYAN7;
                if (UNAVEZ == 1) {     //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    BLANCO5;
                    DELAY_FLASH;
                    RC0=0;RC1=0;RC2=0; //APAGO EL BLANCO 5
                    DELAY_FLASH;
                    BLANCO5;
                    DELAY_FLASH;
                }
                UNAVEZ = 0;
                break;
            
            case 6:
                Apagar();
                PORTA = 0b001110;
                /*CYAN1;
                ROJO3;*/
                AMARILLO5;
                AMARILLO7;
                if (UNAVEZ == 1) {     //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    BLANCO7;
                    DELAY_FLASH;
                    RB0=0;RB2=0;RB4=0;
                    DELAY_FLASH;
                    BLANCO7;
                    DELAY_FLASH;    
                }
                UNAVEZ = 0;
                break;
            
            case 7:
                Apagar();
                PORTA = 0b100110;
                /*CYAN1;
                AZUL3;*/
                ROJO5;
                AMARILLO7;
                break;
            
            case 8: //creo q no hay caso 8
               /* Apagar();
                PORTA = 0b100110;
                /*CYAN1;
                AZUL3;
                ROJO5;
                AMARILLO7;*/
                contador = 0;//revisar si es correcto
                break;
            default:
                contador = 4; //vuelvo a comenzar (es x si el contador tuvo un valor erroneo)
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
//pongo todos los leds en 1
    PORTA=47;
    PORTB=22;
    PORTC=15;
    //TIEMPO_PRUEBA;
}
