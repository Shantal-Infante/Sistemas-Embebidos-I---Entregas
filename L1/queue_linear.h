// queue linear

#include<stdio.h>
#include <stdlib.h>
#include "L1_items_ejercicios_apartado1.h" 

#define MAX_ITEMS 5

typedef struct
{
    int head;  
    int tail; 
    int number_items;   
    int max_items;
    Item_R_W items[MAX_ITEMS]; 
} Queue_Linear;

// Funciones de la cola
Queue_Linear make(Queue_Linear *queue);
int is_empty(Queue_Linear queue);
int is_full(Queue_Linear queue);
int push(Queue_Linear *queue, Item_R_W new_item);
Item_R_W pop(Queue_Linear *queue);
Item_R_W peek_item(Queue_Linear queue);
void show_R_W(Queue_Linear *queue);


Queue_Linear make(Queue_Linear *queue) 
{ 
    queue->head = -1; // se establecen en -1 para evitar confusion cuando solo haya 1 
    queue->tail = -1; // item en la cola en posicion head=0, porque tail=0 tambien en ese caso
    queue->number_items = 0;
    queue->max_items = MAX_ITEMS;
    return *queue;
}

int push(Queue_Linear *queue, Item_R_W new_item)
{
    if(queue->number_items < MAX_ITEMS) 
    {      
        queue->tail++;                                    
        queue->items[queue->tail] = new_item;                       
        if(queue->head==-1)
        {
            queue->head=0; // porque ahora si hay un item a la cabeza
        }
        queue->number_items++;                
        return 1; // elemento agregado exitosamente
    }
    else 
    {   
        printf("\nOverflow: Cola llena, no se pueden agregar mas elementos\n");
        return -1; // elemento no agregado (Nota, en la pila se usó exit(1) en vez de return)
    }
}

Item_R_W pop(Queue_Linear *queue)
{   
    // inicializo variables contenedoras temporales
    Item_R_W popped_item; 

    if(queue->number_items > 0) 
    {   // alojo el elemento a eliminar en las variables temporales
        popped_item = queue->items[queue->head];

        // actualizo el valor del indice head y el nro de elementos restantes
        queue->head++;
        queue->number_items--;
        return popped_item;
    }
    else
    {   
        //reinicio contadores head y tail a valores iniciales de cola vacia
        queue->head = -1; 
        queue->tail = -1;

        printf("\nUnderflow: Cola vacia, no se pueden retirar mas elementos\n");
        return popped_item; // fallo hacer pop 
    }
}

int is_empty(Queue_Linear queue)
{
    
    if(queue.number_items == 0)
    {
        return 1; // esta vacia
    }
    else    
    {
        return 0; // aun contiene elementos
    }
}

int is_full(Queue_Linear queue)
{
    if(queue.number_items == MAX_ITEMS)
    { 
        return 1; // está llena
    }
    else
    {
        return 0; // aun hay espacio
    }
}

Item_R_W peek_item(Queue_Linear queue) // Para saber que item esta a la cabeza
{
    return queue.items[queue.head];
}

void show_R_W(Queue_Linear *queue)
{
    int n = queue->number_items;
    for (int i = 0; i < n; i++)
    {
        Item_R_W temp = pop(queue);

        switch (temp.register_nr)
        {
        case DEVICE_DEFINITIONS: {
            Byte_Device_Definitions d_d;
            temp.mode = READ; // Only
            temp.data = d_d.byte_device_definitions;
            printf("\nItem %d: Register 0xFF DEVICE DEFINITIONS", i); // Da valores raros porque es una simulacion nada mas
            printf("\nData to READ: %X\n", temp.data);
            break;
        }

        case GRAVITY_L: {
            Byte_Gravity_L g_l;
            temp.mode = READ; // Only
            temp.data = g_l.byte_gravity_l;
            printf("\nItem %d: Register 0x10 GRAVITY L", i); // Da valores raros porque es una simulacion nada mas
            printf("\nData to READ: %X\n", temp.data);
            break;
        }
        
        case GRAVITY_H: {
            Byte_Gravity_H g_h;
            temp.mode = READ; // Only
            temp.data = g_h.byte_gravity_h;
            printf("\nItem %d: Register 0x11 GRAVITY H", i);
            printf("\nData to READ: %X\n", temp.data); // Da valores raros porque es una simulacion nada mas
            break;
        }
        
        case INTERRUPT_CONFIGURE: {
            MODE m = temp.mode; // Read or Write
            printf("\nItem %d: Register 0x20 INTERRUPT CONFIGURE", i);

            if (m == READ) {
                Byte_Interrupt_Configure i_c;
                temp.data = i_c.byte_interrupt_configure;
                printf("\nData to READ: %X\n", temp.data); // Da valores raros porque es una simulacion nada mas
            } else if (m == WRITE) {
                Byte_Interrupt_Configure i_c;
                printf("\nData to WRITE: %X %X %X %X\n", i_c.tap_enable, i_c.gravity_change_enable, i_c.inactivity_enable, i_c.double_tap_eneable); // Da valores raros porque es una simulacion nada mas
            }
            break;
        }
        default:
            printf("\nItem %d: ERROR - INVALID OP\n", i);
            break;
        }
    }
}
