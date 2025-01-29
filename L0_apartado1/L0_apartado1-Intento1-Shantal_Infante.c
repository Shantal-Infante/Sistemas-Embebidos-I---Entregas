#include <stdio.h>  // Libreria standard 
#include <stdint.h> // Es donde estan los tipos de datos uint8_t, int16_t, uint32_t, int32_t que usaremos

// Defino mi tipo de dato segun la informacion que quiero obtener del sensor
// Se pide usar struct, enum o union, pero ya que es el 1er intento se usaré un struct
typedef struct
{
    uint8_t  bateria;        // [byte posicion 0] (sin signo)    
    int16_t  temperatura;    // [bytes posiciones 1-2] (con signo)
    int32_t  reserva_agua;   // [bytes posiciones 3-4-5] (con signo)
    uint32_t agua_principal; // [bytes posiciones 6-7-8-9] (sin signo)
    uint16_t checksum;       // [bytes posiciones 10-11] (sin signo)
} Mediciones;

// Prototipo de la Funcion a implementar
Mediciones ordenar_mediciones(uint8_t data_a_ordenar[]);
int leer_entrada(uint8_t entrada[]);

int main(void) 
{
    uint8_t data[12];

    printf("\n Holis \n");

    while (1) {
        // Solicitud array de entrada:
        printf("\n Data Sensor (12 bytes): ");

        if (leer_entrada(data)) 
        {
            // Llamo a mi funcion
            Mediciones data_ordenada = ordenar_mediciones(data);

            // Imprimo los campos de la variable tipo struct que me devolvió la función
            printf("    Nivel de Bateria     : %u \n", data_ordenada.bateria);
            printf("    Temperatura Ambiental: %d \n", data_ordenada.temperatura);
            printf("    Reserva de Agua      : %d \n", data_ordenada.reserva_agua);
            printf("    Agua Principal       : %u \n", data_ordenada.agua_principal);
            printf("    Checksum             : %u \n", data_ordenada.checksum);
            break; // Salimos del bucle si se leen correctamente los bytes de entrada
        } else
        {
            printf("\n Error en la entrada de bytes. Intente de nuevo.\n");
            while (getchar() != '\n'); // Limpia el buffer de entrada
        }
    }
    return 0;
}

// Funcion para registrar los bytes de entrada
int leer_entrada(uint8_t entrada[])
{
    for (int i = 0; i < 12; i++) 
    {
        unsigned int n;
        if (scanf("%x", &n) != 1 || n > 0xFF) 
        {
            // Verifica si scanf falla o si el valor leido no es un byte valido
            return 0; // Retorna 0 si hay un error
        }
        entrada[i] = (uint8_t)n;
    }
    return 1; // Retorna 1 si todo es correcto
}

// Desarrollo de la funcion
// la funcion devolverá el tipo de dato definido 
Mediciones ordenar_mediciones(uint8_t data_a_ordenar[]) 
{
    Mediciones mediciones_ordenadas; // Creo una variable del tipo de dato que definí

    // Se asignan las partes del array con la data a los campos respectivos
    mediciones_ordenadas.bateria        = data_a_ordenar[0];
    mediciones_ordenadas.temperatura    = (int16_t)((data_a_ordenar[1] << 8) | data_a_ordenar[2]);
    mediciones_ordenadas.reserva_agua   = (int32_t)((data_a_ordenar[3] << 16) | (data_a_ordenar[4] << 8) | data_a_ordenar[5]);
    mediciones_ordenadas.agua_principal = (uint32_t)((data_a_ordenar[6] << 24) | (data_a_ordenar[7] << 16) | (data_a_ordenar[8] << 8) | data_a_ordenar[9]);
    mediciones_ordenadas.checksum       = (uint16_t)((data_a_ordenar[10] << 8) | data_a_ordenar[11]);

    return mediciones_ordenadas; // Se devuelve la variable con el tipo de dato definido con la data ya organizada
}
 