// Pila estática

#include <stdlib.h>
#include "item.h"

#define MAX_ELEMENTOS 100

typedef struct
{
    int tamano; //nro de elementos en la pila actualmente
    int cima;   
    Item elementos[MAX_ELEMENTOS]; // usamos un arreglo de tamaño fijo
}Static_Stack;

// Funciones de la pila

Static_Stack crear(Static_Stack *pila, int nro_elementos) 
{ 
    /* Nota: en realidad el int nro_elementos no se uso pero se agrego para que 
       esta funcion sea igual a la forma en que se define en dinamic_stack.h
       y reutilizar codigo en la funcion main*/
    pila->cima = 0;
    pila->tamano = 0;
    return *pila;
}

int esta_vacia(Static_Stack pila)
{
    
    if(pila.tamano == 0)
    {
        return 1; // si esta vacia
    }
    else    
    {
        return 0; // contiene elementos
    }
}

int esta_llena(Static_Stack pila)
{
    if(pila.tamano == MAX_ELEMENTOS)
    { 
        return 1; // está llena
    }
    else
    {
        return 0; // aun hay espacio
    }
}

int push(Static_Stack *pila, Item nuevo_elemento)
{
    if(pila->tamano < MAX_ELEMENTOS) 
    {
        pila->elementos[pila->cima] = nuevo_elemento;
        pila->cima++;
        pila->tamano++;
        return 1; // elemento agregado exitosamente
    }
    else 
    {   
        printf("Overflow");
        exit(1);
    }
}

Item pop(Static_Stack *pila)
{
    Item elemento_retirado;
    elemento_retirado.Pin_entrada = 0;
    elemento_retirado.tiempo = 0;
    elemento_retirado.referencia = 0;

    if(pila->tamano > 0) 
    {
        elemento_retirado.Pin_entrada = pila->elementos[(pila->cima)-1].Pin_entrada;
        elemento_retirado.tiempo = pila->elementos[(pila->cima)-1].tiempo;
        elemento_retirado.referencia = pila->elementos[(pila->cima)-1].referencia;
        pila->cima--;
        pila->tamano--;
        return elemento_retirado;
    }
    else
    {
        return elemento_retirado; // fallo hacer pop 
    }
}

int conteo(Static_Stack pila)
{
    return pila.tamano;
}

