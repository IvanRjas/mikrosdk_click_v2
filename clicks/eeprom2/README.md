\mainpage Main Page
 
 

---
# EEPROM 2 click

EEPROM2 click provides 2 Mbit (2,097,152 bits) of Electrically Erasable and Programmable Read Only Memory, organized in bytes. 
In other words, this Click board™ is an EEPROM memory medium with the capacity of 256 KB. 
The used EEPROM module has an impressive endurance of 4,000,000 write cycles and data retention period of over 200 years.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Eeprom2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eeprom2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void eeprom2_cfg_setup ( eeprom2_cfg_t *cfg ); 
 
- Initialization function.
> EEPROM2_RETVAL eeprom2_init ( eeprom2_t *ctx, eeprom2_cfg_t *cfg );

- Click Default Configuration function.
> void eeprom2_default_cfg ( eeprom2_t *ctx );


#### Example key functions :

- This function writes a single byte of data to the given memory address.
> void eeprom2_write ( eeprom2_t *ctx, uint32_t memory_address, uint8_t value );

 
- This function writes bytes of data to the given memory address.
> void eeprom2_write_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count );

- This function reads a single byte from the given memory address.
> uint8_t eeprom2_read( eeprom2_t *ctx, uint32_t memory_address );


- This function reads bytes from the given memory address.
> void eeprom2_read_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count );


- This function enables EEPROM memory.
> void eeprom2_memory_enable ( eeprom2_t *ctx );


- This function disables EEPROM memory.
> void eeprom2_memory_disable ( eeprom2_t *ctx );

## Examples Description

> This example demonstrates the process of writing and
> reading of data from EEPROM.

**The demo application is composed of two sections :**

### Application Init 

> Initializes EEPROM 2 driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eeprom2_cfg_setup( &cfg );
    EEPROM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom2_init( &eeprom2, &cfg );
}
  
```

### Application Task

> Writing data to EEPROM and then reading that data and writing it via UART.
 

```c

void application_task ( void )
{
    eeprom2_write_bytes ( &eeprom2, 0x01, text, 6 );
    log_printf ( &logger, "Writing Mikroe to EEPROM 2 click\r\n" );
    Delay_ms( 1000 );
    eeprom2_read_bytes ( &eeprom2, 0x01 , mem_value, 6);
    log_printf ( &logger, "Data read: %s\r\n", mem_value );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
