#include "static_stack.c"
//#include "dinamic_stack.c"
// los demás include serán agregados al importar la libreria de la pila estatica
// o la de la dinamica

typedef enum {
    TOGGLE_PIN1 = 0x00,
    IMPRIME_PIN1 = 0x01,
    INCREMENTA_CONTADOR = 0x02,
    IMPRIME_CONTADOR = 0x03,
    NRO_ITEMS = 0x05,
    PILA_LLENA = 0x06,
} Instrucciones;

int procesar_interrupcion(Item *items, int N, int nro_max_de_elementos);

int main() {

    // creamos items de prueba
    Item item1;
    item1.Pin_entrada = 0x06; // salir si la pila esta llena
    item1.tiempo = 0x01;
    item1.referencia = 0x02;

    Item item2;
    item2.Pin_entrada = 0x01; //imprimo valor de pin 1
    item2.tiempo = 0x02;
    item2.referencia = 0x03;

    Item item3;
    item3.Pin_entrada = 0x02; //aumento contador
    item3.tiempo = 0x03;
    item3.referencia = 0x04;

    Item item4;
    item4.Pin_entrada = 0x03; //imprimo contador 
    item4.tiempo = 0x04;
    item4.referencia = 0x05;

    Item item5;
    item5.Pin_entrada = 0x00; // toggle pin 1
    item5.tiempo = 0x05;
    item5.referencia = 0x06;

    Item item6;
    item6.Pin_entrada = 0x05; // verifico nro de items 
    item6.tiempo = 0x05;
    item6.referencia = 0x06;

    // Creamos la pila estática (tiene espacio para maximo 100 items)
    Static_Stack pila;
    // O Creamos la pila dinámica, descomentar 2 lineas siguientes y comentar la de arriba
    //Dinamic_Stack pila;
    crear(&pila, 6); // estatica o dinamica
   // int MAX_ELEMENTOS = pila.tamano_max;

    // cargamos a la pila los items de prueba
    push(&pila, item1);
    push(&pila, item2);
    push(&pila, item3);
    push(&pila, item4);
    push(&pila, item5); 
    push(&pila, item6); 

    // creamos el arreglo de items popped
    int N = conteo(pila);
    Item *items = (Item *)malloc(N*sizeof(Item));
    for (int i = 0; i < N; i++) {
        items[i] = pop(&pila);
    }
    //liberar(&pila); ///////// Comentar linea si es pila estatica ////////////

    // Llamamos la función para procesar las interrupciones
    procesar_interrupcion(items, N, MAX_ELEMENTOS);

    return 0;
}


// Definición de la función de interrupciones
int procesar_interrupcion(Item *items, int N, int nro_max_de_elementos) 
{/////////////// USAR ENUM EN VEZ DEL SWITCH CASE ////////////
    int pin1 = 0;
    size_t j = 0;
    for (int i = 0; i < N; i++) 
    {
        switch ((Instrucciones)items[i].Pin_entrada) {
            case TOGGLE_PIN1: // Hacer Toggle del Pin 1
                printf("\nse hizo Toggle del pin 1 exitosamente");
                pin1 = !pin1;
                break;
            case IMPRIME_PIN1: // Imprimir el valor del pin 1
                printf("\nPin 1: %d", pin1);
                break;
            case INCREMENTA_CONTADOR: // Aumentar un contador de tipo size_t
                printf("\nSe incremento el contador exitosamente");
                j++;
                break;
            case IMPRIME_CONTADOR: // Imprimir el contador
                printf("\nContador: %zu", j);
                break;
            case NRO_ITEMS: // Verificar el número de items que hay en la Pila
                printf("\nNumero de items: %d", N);
                break; 
            case PILA_LLENA: // Si la Pila está llena finaliza la ejecución del programa
                if(N == nro_max_de_elementos)
                {
                    printf("\nLa pila se lleno, finalizando el programa...\n");
                    exit(0);
                    break;
                }
                printf("\nLa pila no se ha llenado.\n");
                break;
            default:
                printf("\nInstrucción no reconocida!\n");
                exit(0);
                break;
        }
    }
    return 0;
}


