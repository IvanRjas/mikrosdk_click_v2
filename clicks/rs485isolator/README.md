\mainpage Main Page
 
---
# RS485 Isolator click

RS485 Isolator click is an RS485 communication isolator and carries the ADM2682EBRIZ, a 5 kV rms signal and power isolated RS-485 transceiver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs485isolator_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs485-isolator-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs485Isolator Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs485Isolator Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs485isolator_cfg_setup ( rs485isolator_cfg_t *cfg ); 
 
- Initialization function.
> RS485ISOLATOR_RETVAL rs485isolator_init ( rs485isolator_t *ctx, rs485isolator_cfg_t *cfg );

#### Example key functions :

- Set receiver state
> void rs485isolator_set_receiver_mode ( rs485isolator_t *ctx, uint8_t state );
 
- Generic read function.
> int32_t rs485isolator_generic_read ( rs485isolator_t *ctx, char *data_buf, uint16_t max_len );

- Generic write function.
> void rs485isolator_generic_write ( rs485isolator_t *ctx, char *data_buf, uint16_t len );

## Examples Description

> This example reads and processes data from RS485 Isolator clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs485isolator_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs485isolator_cfg_setup( &cfg );
    RS485ISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485isolator_init( &rs485isolator, &cfg );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs485isolator_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator_generic_write( &rs485isolator, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif    
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs485Isolator

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
