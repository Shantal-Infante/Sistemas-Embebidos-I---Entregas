#include "static_stack.h"
// los demás include serán agregados al importar la libreria "static_stack.h"

int procesarInterrupciones(Item *items, size_t N);

int main() {
    // Creamos la pila estática
    Static_Stack pila = crear();

    // creamos items de prueba
    Item item1;
    item1.Pin_entrada = 0x00;
    item1.tiempo = 0x01;
    item1.referencia = 0x02;

    Item item2;
    item2.Pin_entrada = 0x01;
    item2.tiempo = 0x02;
    item2.referencia = 0x03;

    Item item3;
    item3.Pin_entrada = 0x02;
    item3.tiempo = 0x03;
    item3.referencia = 0x04;

    Item item4;
    item4.Pin_entrada = 0x03;
    item4.tiempo = 0x04;
    item4.referencia = 0x05;

    Item item5;
    item5.Pin_entrada = 0x05;
    item5.tiempo = 0x05;
    item5.referencia = 0x06;

    // cargamos a la pila los itemas de prueba
    push(&pila, item1);
    push(&pila, item2);
    push(&pila, item3);
    push(&pila, item4);
    push(&pila, item5); 

    // creamos el arreglo de items popped
    Item items[MAX_ELEMENTOS];
    int N;
    for (int i = 0; i < MAX_ELEMENTOS; i++) {
        items[i] = pop(&pila);
        N = i; // cuantos items se tendrán
    }

    // Llamamos la función para procesar las interrupciones
    procesar_interrupcion(items, N);

    return 0;
}

// Definición de la función de interrupciones
int procesar_interrupcion(Item *items, size_t N) 
{
    int pin1 = 0;
    size_t contador = 0;
    for (int i = 0; i < N; i++) 
    {
        switch (items[i].Pin_entrada) {
            case 0x00: // Hacer Toggle de una variable booleana para el Pin 1
                pin1 = !pin1;
                break;
            case 0x01: // Imprimir el valor del pin 1
                printf("Pin 1: %d\n", pin1);
                break;
            case 0x02: // Aumentar un contador de tipo size_t
                contador++;
                break;
            case 0x03: // Imprimir el contador
                printf("Contador size_t: %zu \n", contador);
                break;
            case 0x05: // Verificar el número de items que hay en la Pila
                printf("Nro de items en la Pila: %d\n", N);
                break;
            case 0x06: // Si la Pila está llena finaliza la ejecución del programa
                printf("La pila se lleno, finalizando el programa.\n");
                exit(0);
                break;
            default:
                printf("Instrucción no reconocida!");
                break;
        }
    }
    return 0;
}


