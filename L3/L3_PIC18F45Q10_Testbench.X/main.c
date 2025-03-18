 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

//Máquina de estados
typedef enum{
    INIT_STATE,
    RUNNING_STATE,
    INTERRUPT_STATE           
}STATE_MACHINE;

//Variable para saber el estado de la máquina
STATE_MACHINE state = INIT_STATE; //La Inicalizo en estado 0

//Definimos el Callback Handler del timer
void timer_callback(void)
{  
    state = INTERRUPT_STATE; //En callback cambiamos el estado a interrupcion
}

int main(void)
{
    SYSTEM_Initialize(); // No usamos TMR4_Initialize(void) porque SYSTEM_Initialize() ya inicializa todo

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts X
    INTERRUPT_PeripheralInterruptEnable(); 
    
    while(1)
    {
        switch(state){
            case INIT_STATE:
                //Ejecutamos acá la rutina de inicialización
                TMR2_PeriodMatchCallbackRegister(timer_callback);
                TMR2_Start();
                
                state = RUNNING_STATE; //pasamos al siguiente estado
                break;
                
            case RUNNING_STATE:
                //No toca hacer nada acá
                break;
                
            case INTERRUPT_STATE:
                LED_Toggle();
                state = RUNNING_STATE;
                break;
        }
    }    
}