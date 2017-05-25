/*
 * File:   Main.c
 * Author: Amenabar Jonathan
 *
 * Created on 8 de OCTUBRE de 1987, 20:57
 */
//#include <xc.h>
#include "bsp/bsp.h"
//#include "bsp.c"



void main(void) {

   bsp_hardware_init();
   unsigned int const SI = 1;
   unsigned int const NO = 0;


   //----------DEFINO VARIABLES--------------------
   unsigned int contador = 4;
   unsigned int inicio = 0;
   unsigned int UNAVEZ = 0;      //Variable usada para que el flash solo se de 1 vez por vuelta
   unsigned int ACTUAL_AR = 0;   //Variables necesarias para poder crear un evento y reaccionar ante este, antes era por estado.
   unsigned int ANTERIOR_AR = 0; 
   unsigned int ACTUAL_CI = 0;
   unsigned int ANTERIOR_CI = 0;

    prueba(); /*CON ESTO PRUEBO LOS LEDS QUE TODOS LOS COLORES DE CADA UNO FUNCIONE CORRECTAMENTE */

    while (1) {
    
        ACTUAL_AR = SENSOR_AR();     //***REVISAR COMO MEJORAR ESTO
        ACTUAL_CI = SENSOR_CI();
        
        do {
            ACTUAL_AR = SENSOR_AR(); //***REVISAR COMO MEJORAR ESTO
            
            if (ACTUAL_AR == SI && ANTERIOR_AR == NO){

                inicio = SI;
                
            }
            
            
        } while (inicio == NO);      //Es para que quede dentro de este while hasta que el arbol de leva de el arranque inicial del motor

        if (ACTUAL_AR == SI && ANTERIOR_AR == NO) { //Nota: Deberias meterlo en una interrupcion!.

            contador = 4;            //ARRANCA EN EL CILINRO 7
            apagar();
            
        }
            ANTERIOR_AR = ACTUAL_AR;
            
        if (ACTUAL_CI == SI && ANTERIOR_CI == NO) {     //Nota: Deberias meterlo en una interrupcion!.

            contador++;
            UNAVEZ = 1;
            if(contador>=9)
                contador=0;
        }
            ANTERIOR_CI = ACTUAL_CI;
            
        switch (contador) {
            
            case 0:
                apagar();
                color_set(AMARILLO1);
                color_set(AZUL3);
                color_set(ROJO5);
                color_set(ROJO7);
                if (UNAVEZ == 1) { //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    color_set(BLANCO1);
                    DELAY_FLASH();
                    color_set(BLANCO1OFF);
                    DELAY_FLASH();
                    color_set(BLANCO1);
                    DELAY_FLASH();
                }
                UNAVEZ = 0;
                break;
            
            case 1:
                apagar();
                color_set(AMARILLO1);
                color_set(CYAN3);
                color_set(AZUL5);
                color_set(ROJO7);
                break;
            
            case 2:
                apagar();
                color_set(ROJO1);
                color_set(CYAN3);
                color_set(AZUL5);
                color_set(AZUL7);
                break;
            
            case 3:
                apagar();
                color_set(ROJO1);
                color_set(AMARILLO3);
                color_set(CYAN5);
                color_set(AZUL7);
                if (UNAVEZ == 1) {
                    color_set(BLANCO3); //BLANCO3 //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    DELAY_FLASH();
                    color_set(BLANCO3OFF); //apago solo BLANCO3, dejo prendido el rojo1
                    DELAY_FLASH();
                    color_set(BLANCO3); //BLANCO3
                    DELAY_FLASH();
                }
                UNAVEZ = 0;
                break;
            
            case 4:
                apagar();
                color_set(AMARILLO1);
                color_set(CYAN3);
                color_set(AZUL5);
                color_set(ROJO7);
                break;
            
            case 5:
                apagar();
                color_set(AZUL1);
                color_set(ROJO3);
                color_set(AMARILLO5);
                color_set(CYAN7);
                if (UNAVEZ == 1) {     //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    color_set(BLANCO5);
                    DELAY_FLASH();
                    color_set(BLANCO5OFF); //APAGO EL BLANCO 5
                    DELAY_FLASH();
                    color_set(BLANCO5);
                    DELAY_FLASH();
                }
                UNAVEZ = 0;
                break;
            
            case 6:
                apagar();
                color_set(CYAN1);
                color_set(ROJO3);
                color_set(AMARILLO5);
                color_set(AMARILLO7);
                if (UNAVEZ == 1) {     //ESTO ES PARA GENERAR UN DOBLE DESTELLO
                    color_set(BLANCO7);
                    DELAY_FLASH();
                    color_set(BLANCO7OFF);
                    DELAY_FLASH();
                    color_set(BLANCO7);
                    DELAY_FLASH();    
                }
                UNAVEZ = 0;
                break;
            
            case 7:
                apagar();
                color_set(CYAN1);
                color_set(AZUL3);
                color_set(ROJO5);
                color_set(AMARILLO7);
                break;
            
            case 8: //creo q no hay caso 8
                contador = 0;//revisar si es correcto
                break;
            default:
                contador = 4; //vuelvo a comenzar (es x si el contador tuvo un valor erroneo)
                break;
        }

    }



    return;
}


