// queue linear

#include <stdio.h>
#include <stdlib.h>
#include "L1_items_ejercicios_apartado1.h"  ////////////////////// ??????????? /////////////////////////////

#define MAX_ITEMS 5

typedef struct
{
    int head;  
    int tail; 
    int number_items;   
    int max_items;
    Item_Interruption items[MAX_ITEMS]; 
} Queue_Circular;


// Funciones de la cola
Queue_Circular make(Queue_Circular *queue);
int is_full(Queue_Circular queue);
int is_empty(Queue_Circular queue);
int push(Queue_Circular *queue, Item_Interruption new_item);
Item_Interruption pop(Queue_Circular *queue);
Item_Interruption peek_item(Queue_Circular queue);
void show_interruption(Queue_Circular *queue);

Queue_Circular make(Queue_Circular *queue) 
{ 
    queue->head = 0; 
    queue->tail = 0; 
    queue->number_items = 0;
    queue->max_items = MAX_ITEMS;
    return *queue;
}

int push(Queue_Circular *queue, Item_Interruption new_item)
{
    if(is_full(*queue))
    {             
        printf("\nOverflow: Cola llena, no se pueden agregar mas elementos\n");
        return -1;         
    }
    else 
    {   
        queue->tail = (queue->head + queue->number_items)%queue->max_items;                               
        queue->items[queue->tail] = new_item; 
        queue->number_items++; 
        return 1;// elemento agregado exitosamente 
    }
}

Item_Interruption pop(Queue_Circular *queue)
{   
    // inicializo variables contenedoras temporales
    Item_Interruption popped_item; 

    if(is_empty(*queue)) 
    {  
        printf("\nUnderflow: Cola vacia, no se pueden retirar mas elementos\n");
        exit(1); // fallo hacer pop 
    }
    else
    {   
        // alojo el elemento a eliminar en las variables temporales
        popped_item = queue->items[queue->head];

        // actualizo el valor del indice head y el nro de elementos restantes
        queue->head = (queue->head + 1)%queue->max_items;
        queue->number_items--;
        return popped_item;
    }
}

int is_empty(Queue_Circular queue)
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

int is_full(Queue_Circular queue)
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

Item_Interruption peek_item(Queue_Circular queue) // Para saber que item esta a la cabeza
{  // No se pasó queue como puntero ya que solo quiero ver el elemento no modificarlo
    return queue.items[queue.head];
}

void show_interruption(Queue_Circular *queue)
{
    int n = queue->number_items;
    for(int i=0; i < n; i++)
    {
        Item_Interruption temp = pop(queue);
        switch (temp.pin)
        {
        case INT1:
            temp.interruption_type = TOUCH;
            printf("\nInterrupccion %d: TOUCH\n",i);
            break;

        case INT2:
            temp.interruption_type = GRAVITY_CHANGE;
            printf("\nInterrupccion %d: GRAVITY CHANGE\n",i);
            break;
        
        case INT3:
            temp.interruption_type = INACTIVITY;
            printf("\nInterrupccion %d: INACTIVITY\n",i);
            break;
        
        case INT4:
            temp.interruption_type = DOUBLE_TAP;
            printf("\nInterrupccion %d: DOUBLE TAP\n",i);
            break;
        
        default:
            printf("\nInterrupccion %d: ERROR - NO DEF\n",i);
            break;
        }
    }
}

