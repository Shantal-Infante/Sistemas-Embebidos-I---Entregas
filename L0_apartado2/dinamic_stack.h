// Pila estática

#include <stdlib.h>
#include "item.h"

typedef struct
{
    int tamano; //nro de elementos en la pila actualmente
    int tamano_max; //tamano maximo de la pila para saber si esta llena
    int cima;   
    Item *elementos; // usamos un puntero
}Dinamic_Stack;

// Funciones de la pila

Dinamic_Stack crear(Dinamic_Stack *pila, int nro_elementos) 
{
    // reservamos el bloque de memoria del tamaño adecuado para nuestra pila
    Item *reservado;
    reservado = (Item *)malloc(sizeof(Item)*nro_elementos);
    if(reservado == NULL)
    {
        //verificamos
        printf("\nError al reservar memoria\n");
        exit(1);
    }
    pila->cima = 0;
    pila->tamano = 0;
    pila->tamano_max = nro_elementos;
    return *pila;
}

int esta_vacia(Dinamic_Stack pila)
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

int esta_llena(Dinamic_Stack pila)
{
    if(pila.tamano == pila.tamano_max)
    { 
        return 1; // está llena
    }
    else
    {
        return 0; // aun hay espacio
    }
}

int push(Dinamic_Stack *pila, Item nuevo_elemento)
{
    if(pila->tamano < pila->tamano_max) 
    {
        pila->elementos[pila->cima] = nuevo_elemento;
        pila->cima++;
        pila->tamano++;
        return 1; // elemento agregado exitosamente
    }
    else //La pila esta llena, hay que desplazar los items
    {                         
        for(int i = 0; i < (pila->tamano_max- 1); i++)
        {   
            pila->elementos[i] = pila->elementos[i+1];
        } 
        // agregamos el nuevo elemento en la cima
        pila->elementos[pila->tamano_max-1] = nuevo_elemento;
        return 1; // elemento agregado exitosamente
        //el índice de la cima y el tamaño no cambian porque la pila sigue llena
    }
}

Item pop(Dinamic_Stack *pila)
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

int conteo(Dinamic_Stack pila)
{
    return pila.tamano;
}

