/*
 * File:   bsp.c
 * Author: amenabarjonathan
 *
 * Created on September 17, 2016, 1:52 PM
 */
#include <xc.h>

#include "bsp.h"

/*--------------------------ROJO1, VERDE1,AZUL1, ROJO3, VERDE3,AZUL3, ROJO5, VERDE5,AZUL5, ROJO7, VERDE7,AZUL7*/
unsigned int leds_port[] = {PORTA, PORTA, PORTA, PORTA, PORTC, PORTA, PORTC, PORTC, PORTC, PORTB, PORTB, PORTB};
unsigned char leds[] =     {0x00,  0x01,  0X02,  0x03,  0x03,  0x05,  0x00,  0x01,  0x02,  0x01,  0x02,  0x04};
unsigned char color;
/*----------------------     0      1      2      3      4      5      6      7       8      9     10      11  */

/*Prototipos de funciones de iniciarlizacion de hardware*/
void bsp_hardware_init(void);
void bsp_led_init(void);
void bsp_sw_init(void);
void color_set(char color);
void delay(int tiempo);


/*Funcion principal que inicializa el hardware*/
void bsp_init(void){
   bsp_hardware_init();
   bsp_led_init();
   bsp_sw_init();
}



/*Aca declaro cada funcion, que va a iniciar el hardware*/
void bsp_hardware_init(){
// PIC16F873A Configuration Bit Settings
#define _XTAL_FREQ 4000000
#pragma config FOSC = XT        // Oscillator Selection bits (XT-  oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT enable)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//PEIE = 0;
//GIE = 0;
}

void bsp_led_init(){
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
}

void bsp_sw_init(){
  //PINES DE ENTRADA DE DATOS
    TRISB0 = 1; //SENSOR ARBOL DE LEVA RB0
    TRISB5 = 1; //SENSOR CIGUE�AL RB5
}

void led_set(char led, char estado){
    if(estado)
        leds_port[led] &= leds[led];   //si es 1 lo prende 
    else
        leds_port[led] |= ~leds[led];  //si es 0 lo apaga
    
}

void color_set(char color){
    
    switch (color){
        
        case "ROJO1":
            led_set(rojo1,ENCENDER);
            break;
            
        case "CYAN1":
            led_set(verde1,ENCENDER); //verde1
            led_set(azul1,ENCENDER);  //azul1
            break;
            
        case "AZUL1":
            led_set(azul1,ENCENDER); //azul1
            break;
            
        case "AMARILLO1":
            led_set(verde1,ENCENDER); //verde1
            led_set(rojo1,ENCENDER);  //rojo1
            break;
        
        case "BLANCO1":
            led_set(rojo1,ENCENDER);  //rojo1
            led_set(verde1,ENCENDER); //verde1
            led_set(azul1,ENCENDER);  //azul1
            break;
            
        case "BLANCO1OFF":
            led_set(rojo1,APAGAR);  //rojo1
            led_set(verde1,APAGAR); //verde1
            led_set(azul1,APAGAR);  //azul1
            break;
       
        case "ROJO3":
            led_set(rojo3,ENCENDER);  //rojo3
            break;
            
        case "CYAN3":
            led_set(verde3,ENCENDER); //verde3
            led_set(azul3,ENCENDER);  //azul3
            break;
            
        case "AZUL3":
            led_set(azul5,ENCENDER); //azul3
            break;
            
        case "AMARILLO3":
            led_set(verde3,ENCENDER); //verde3
            led_set(rojo3,ENCENDER);  //rojo3
            break;
        
        case "BLANCO3":
            led_set(rojo3,ENCENDER);  //rojo3
            led_set(verde3,ENCENDER); //verde3
            led_set(azul5,ENCENDER);  //azul3
            break;
            
        case "BLANCO3OFF":
            led_set(rojo3,APAGAR);  //rojo3
            led_set(verde3,APAGAR); //verde3
            led_set(azul5,APAGAR);  //azul3
            break;
            
        case "ROJO5":
            led_set(rojo5,ENCENDER); //rojo5
            break;
            
        case "CYAN5":
            led_set(verde5,ENCENDER); //verde5
            led_set(azul5,ENCENDER);  //azul5
            break;
            
        case "AZUL5":
            led_set(azul5,ENCENDER); //azul5
            break;
            
        case "AMARILLO5":
            led_set(verde5,ENCENDER); //verde5
            led_set(rojo5,ENCENDER);  //rojo5
            break;
        
        case "BLANCO5":
            led_set(rojo5,ENCENDER);  //rojo5
            led_set(verde5,ENCENDER); //verde5
            led_set(azul5,ENCENDER);  //azul5
            break;
            
        case "BLANCO5OFF":
            led_set(rojo5,APAGAR);   //rojo5
            led_set(verde5,APAGAR);  //verde5
            led_set(azul5,APAGAR);   //azul5
            break;
            
        case "ROJO7":
            led_set(rojo7,ENCENDER); //rojo7
            break;
            
        case "CYAN7":
            led_set(verde7,ENCENDER); //verde7
            led_set(azul7,ENCENDER);  //azul7
            break;
            
        case "AZUL7":
            led_set(azul7,ENCENDER); //azul7
            break;
            
        case "AMARILLO7":
            led_set(verde7,ENCENDER); //verde7
            led_set(rojo7,ENCENDER);  //rojo7
            break;
        
        case "BLANCO7":
            led_set(rojo7,ENCENDER);  //rojo7
            led_set(verde7,ENCENDER); //verde7
            led_set(azul7,ENCENDER);  //azul7
            break;
            
        case "BLANCO7OFF":
            led_set(rojo7,APAGAR);  //rojo7
            led_set(verde7,APAGAR); //verde7
            led_set(azul7,APAGAR);  //azul7
            break;
    }
}
void delay(int tiempo){
    __delay_ms(tiempo);
}