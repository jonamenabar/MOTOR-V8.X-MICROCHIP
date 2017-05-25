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
    int const SI = 1;
    int const NO = 0;


    //----------DEFINO VARIABLES--------------------
    int contador = 4;
    int inicio = 0;
    int UNAVEZ = 0; //Variable usada para que el flash solo se de 1 vez por vuelta
    

    prueba(); /*CON ESTO PRUEBO LOS LEDS QUE TODOS LOS COLORES DE CADA UNO FUNCIONE CORRECTAMENTE */

    while (1) {

        do {
            if (SENSOR_AR() == SI) {

                inicio = SI;
                ANTIREBOTE();
            }
        } while (inicio == 0);

        if (SENSOR_AR() == SI) { //Nota: Deberias meterlo en una interrupcion!.

            contador = 4; //ARRANCA EN EL CILINRO 7
            ANTIREBOTE();
            apagar();
            
        }

        if (SENSOR_CI() == SI) { //Nota: Deberias meterlo en una interrupcion!.

            contador++;
            UNAVEZ = 1;
            ANTIREBOTE();
            if(contador>=9)
                contador=0;
        }
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


