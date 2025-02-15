#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
///////////// Ejercicio 1.1 ////////////////////////////////////////////////////

typedef enum{
    CS = 0xA0,   //Chip Select
    INT1 = 0xA1,
    INT2 = 0xA2,
    INT3 = 0xA3,
    INT4 = 0xA4,
}GPIO;

typedef enum{
    SDO = 0xE0,  //Serial Data Output
    SDI = 0xE1,  //Serial Data Input
    SCK = 0xE2,  //Serial Clock
}SPI; //Serial Peripheral Interface Protocol


////////////////////////////////////////////////////////////////////////////////
///////////// Ejercicio 1.2 ////////////////////////////////////////////////////

#include <stdint.h>

typedef union
{
    uint8_t byte_device_definitions;

    // Bitfield - Register 0xFF - Device Definitions (R)
    struct
    {
        uint8_t gravity_size_definition:2;  // 00=8bytes, 010=10bytes, 10=12bytes, 00=14bytes
        uint8_t extra_interrupts_enable:1;  // 0 means device does not support them, 1 means device can use them.
        uint8_t device_state:1;             // 0 means Powered Off state, 1 means active state
        uint8_t :4;                         // variable opaca, bits always 0
    }; 
    
} Byte_Device_Definitions ;

typedef union
{
    uint8_t byte_gravity_l;

    // Bitfield - Register 0x10 - Gravity_L (R)
    struct
    {
        uint8_t :2;                           //variable opaca, bits always 0
        uint8_t lower_bits_of_measurement:6;  //
    };

} Byte_Gravity_L;

typedef union
{
    uint8_t byte_gravity_h;

    // Bitfield - Register 0x11 - Gravity_H (R)
    struct
    {
        uint8_t tap_enable:1;
        uint8_t gravity_change_enable:1;
        uint8_t inactivity_enable:1;
        uint8_t double_tap_eneable:1;
        uint8_t :4; //variable opaca, bits always 0
    };
    
} Byte_Gravity_H;

typedef union
{
    uint8_t byte_interrupt_configure;

    // Bitfield - Register 0x20 - Interrupt Configure (R/W)
    struct
    {
        uint8_t tap_enable:1;
        uint8_t gravity_change_enable:1;
        uint8_t inactivity_enable:1;
        uint8_t double_tap_eneable:1;
        uint8_t :4; //variable opaca, bits always 0
    };
    
} Byte_Interrupt_Configure;


////////////////////////////////////////////////////////////////////////////////
///////////// Ejercicio 1.3 ////////////////////////////////////////////////////'

typedef enum
{
    TOUCH = 1,          //INT1
    GRAVITY_CHANGE = 2, //INT2
    INACTIVITY = 3,     //INT3
    DOUBLE_TAP = 4,     //INT4
} INTERRUPTIONS;


////////////////////////////////////////////////////////////////////////////////
///////////// Item para cola lineal ////////////////////////////////////////////
/*
    Especifica valor del registro, si se quiere hacer Write or Read, y la data (si es Read). hago un switch 
*/

typedef enum{
    READ  = 0,
    WRITE = 1,
} MODE;

typedef enum{
    DEVICE_DEFINITIONS = 0xFF,  // R
    GRAVITY_L = 0x10,           // R
    GRAVITY_H = 0x11,           // R
    INTERRUPT_CONFIGURE = 0x20, // R/W
} REGISTER;

typedef struct
{
    MODE mode;
    REGISTER register_nr;
    int data;
} Item_R_W;
//     NOTAR: que el item ya estaría empaquetado en su minimo tamaño ya que tanto los elementos tipo MODE
//     como los de REGISTER como data son tipo int y ocupan 4bytes cada uno.



////////////////////////////////////////////////////////////////////////////////
///////////// Item para cola circular ////////////////////////////////////////////
/* 
    Como los Pines GPIO casualmente son 4 y se llaman INT1, INT2, INT3 e INT4 (ejer 1.1) 
    y hay 4 interrupciones, podemos asociar directamente cada una a un pin especifico.

    NOTAR: que el item ya estaría empaquetado en su minimo tamaño ya que tanto los elementos GPIO
    como los de INTERRUPTION son tipo int y ocupan 4bytes cada uno.
*/
typedef struct 
{
    GPIO pin;
    INTERRUPTIONS interruption_type; 
} Item_Interruption;

