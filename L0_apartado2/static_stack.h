// Pila estática

#include "item.h"

#define MAX_ELEMENTOS 100

typedef struct
{
    int tamano; //nro de elementos en la pila actualmente
    int cima;   
    Item elementos[];
}Static_Stack;

// Funciones de la pila

Static_Stack crear()
{
    Static_Stack pila;
    pila.cima = 0;
    pila.tamano = 0;
    return pila;
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
    else //La pila esta llena, hay que desplazar los items
    {                         
        for(int i = 0; i < (MAX_ELEMENTOS- 1); i++)
        {   
            pila->elementos[i] = pila->elementos[i+1];
        } 
        // agregamos el nuevo elemento en la cima
        pila->elementos[MAX_ELEMENTOS-1] = nuevo_elemento;
        return 1; // elemento agregado exitosamente
        //el índice de la cima y el tamaño no cambian porque la pila sigue llena
    }
}

Item pop(Static_Stack *pila)
{
    Item elemento_retirado;
    elemento_retirado.Pin_entrada = NULL;
    elemento_retirado.tiempo = NULL;
    elemento_retirado.referencia = NULL;

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

