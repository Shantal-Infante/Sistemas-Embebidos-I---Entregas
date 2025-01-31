// Tipo de dato item (Interrupciones)

#include <stdio.h>
#include <stdint.h>

typedef struct 
{
    uint8_t  Pin_entrada;  // 1 byte  -> especifica la instruccion
    uint32_t tiempo;      // 4 bytes -> tiempo de interrupcion
    uint16_t referencia;  // 2 bytes
} Item; // 7 bytes 