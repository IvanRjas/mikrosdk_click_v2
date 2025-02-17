/*!
 * \file 
 * \brief Accel Click example
 * 
 * # Description
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI/I2C driver and settings data read format,
 * power mode, FIFO control and baud rate( 100Hz default ).
 *
 * ## Application Task
 * Reading X, Y and Z axis and logs on usbuart every 1 second.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel.h"

// ------------------------------------------------------------------ VARIABLES

static accel_t accel;
static log_t logger;

static uint8_t tmp;
static int16_t val_x;
static int16_t val_y;
static int16_t val_z;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    accel_cfg_setup( &cfg );
    ACCEL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel_init( &accel, &cfg );

    accel_generic_read( &accel, ACCEL_REG_DEVID, &tmp, 1 );

    if ( tmp == ACCEL_DEVID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        for ( ; ; );
    }
    accel_default_cfg ( &accel );
}

void application_task ( void )
{
    val_x = accel_read_x_axis( &accel );
    log_printf( &logger, "Axis X : %d\r\n", val_x );

    val_y = accel_read_y_axis( &accel );
    log_printf( &logger, "Axis Y : %d\r\n", val_y );

    val_z = accel_read_z_axis( &accel );
    log_printf( &logger, "Axis Z : %d\r\n", val_z );

    log_printf( &logger, "-------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
