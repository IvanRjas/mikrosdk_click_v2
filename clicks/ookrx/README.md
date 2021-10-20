\mainpage Main Page
 
---
# OOK RX click

OOK RX click is a wireless receiver that operates at the frequency of 433MHz (sub-GHz). This device allows realization of a simple, low-speed wireless ad hoc communication network between a receiver and compatible transmitter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ookrx_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ook-rx-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

We provide a library for the OOKRX Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OOKRX Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ookrx_cfg_setup ( ookrx_cfg_t *cfg ); 
 
- Initialization function.
> OOKRX_RETVAL ookrx_init ( ookrx_t *ctx, ookrx_cfg_t *cfg );

- Click Default Configuration function.
> void ookrx_default_cfg ( ookrx_t *ctx );


#### Example key functions :

- This function receives data in the OOK communication.
> uint8_t ookrx_receive_data ( ookrx_t *ctx, uint16_t start_package, 
                               uint8_t *receive_buffer, uint8_t bytes_num );
 
- This function reads the od pin digital input.
> uint8_t ookrx_read_do_pin ( ookrx_t *ctx );

- This function reads the rsi pin digital input.
> uint8_t ookrx_read_rsi_pin ( ookrx_t *ctx );

## Examples Description

> This example showcases how to initialize and use the OOK RX click. The click decrypts information
  embedded in a 433 MHz frequency radio signal. In order for the OOK communication to work a receiver
  click needs to be used. OOK TX plays that role - it encrypts, embeds and sends the data.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    ookrx_cfg_t cfg;

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
    log_info(&logger, "Application Init");

    //  Click initialization.

    ookrx_cfg_setup( &cfg );
    OOKRX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ookrx_init( &ookrx, &cfg );
    Delay_ms( 100 );
    
#ifdef BYTE_RECEIVE
    log_info(&logger, "Application Task\r\n BYTE TRANSMIT DEMO");
#endif
    
#ifdef DATA_RECEIVE
    log_info(&logger, "Application Task\r\n DATA TRANSMIT DEMO");
#endif
}
  
```

### Application Task

> This application consists 2 types:
>  - BYTE_RECEIVE: Receiving one by one byte of data
>  - DATA_RECEIVE: Receiving package of data ( 6 bytes in this example )

```c

void application_task ( )
{
#ifdef BYTE_RECEIVE
    uint8_t received_byte;

    if ( ! ( ookrx_receive_data( &ookrx, PREABLE_WORD, &received_byte, 1 ) ) )
    {
        log_printf( &logger, "%c", received_byte );
    }
#endif
#ifdef DATA_RECEIVE
    uint8_t received_package[ 10 ] = { 0 };

    if ( ! ( ookrx_receive_data( &ookrx, PREABLE_WORD, received_package, 6 ) ) )
    {
        log_printf( &logger, " * Received packet: %s\r\n", received_package );
    }
#endif
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OOKRX

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
