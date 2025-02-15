#include<stdio.h>
#include<stdint.h>

 // si se incluye una cola comentar la otra
#include "queue_linear.h" 
//#include "queue_circular.h"

int main(){

    /*Items de R/W - prueba (cola lineal):*/
    Queue_Linear queue;
    Item_R_W item[5]; 
    item[0].register_nr = DEVICE_DEFINITIONS;
    item[1].register_nr = GRAVITY_L;
    item[2].register_nr = GRAVITY_H;
    item[3].register_nr = INTERRUPT_CONFIGURE;
    item[3].mode = WRITE;
    item[4].register_nr = INTERRUPT_CONFIGURE;
    item[4].mode = READ;

    /*Items de interrupciones - prueba (cola circular):
    Queue_Circular queue;
    Item_Interruption item[5]; 
    item[0].pin = INT1;
    item[1].pin = INT2;
    item[2].pin = INT3;
    item[3].pin = INT4;
    item[4].pin = INT1; 
    */
    

    make(&queue);

    for(int i=0; i < 5; i++)
    {   push(&queue, item[i]);
    }
    
    show_R_W(&queue);             //Si es cola lineal
    //show_interruption(&queue); //Si es cola circular

    return 0;
}