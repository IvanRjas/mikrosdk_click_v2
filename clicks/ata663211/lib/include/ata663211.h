/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for ATA663211 Click driver.
 *
 * \addtogroup ata663211 ATA663211 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ATA663211_H
#define ATA663211_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define ATA663211_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.inh = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )
 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ATA663211_RETVAL  uint8_t

#define ATA663211_OK           0x00
#define ATA663211_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */ 

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */


/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en;

    // Input pins 

    digital_in_t inh;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} ata663211_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t inh;
    pin_name_t en;


    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits. 

} ata663211_cfg_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void ata663211_cfg_setup ( ata663211_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ata663211 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ATA663211_RETVAL ata663211_init ( ata663211_t *ctx, ata663211_cfg_t *cfg );

/**
 * @brief Generic multi write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer
 * @param len          Number of the bytes in the data buffer
 *
 * @description This function writes data.
 */
void ata663211_generic_multi_write ( ata663211_t *ctx, char *data_buf,  uint8_t len );

/**
 * @brief Generic multi read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 *
 * @description This function reads data.
 */
void ata663211_generic_multi_read ( ata663211_t *ctx, char *data_buf,  uint8_t len );


/**
 * @brief Generic single read function.
 *
 * @param ctx        Click object.
 * @return one byte data
 *
 * @description This function read one byte data.
 */
char ata663211_generic_single_read ( ata663211_t *ctx );

/**
 * @brief Generic single write function.
 *
 * @param ctx          Click object.
 * @param tx_data      Input data 
 *
 * @description This function write one byte data.
 */
void ata663211_generic_single_write ( ata663211_t *ctx, char tx_data );

/**
 * @brief Wake-up device function.
 *
 * @param ctx          Click object.
 *
 * @description This function engages the normal mode.
 */
void ata663211_wake_up_device ( ata663211_t *ctx );

/**
 * @brief Sleep mode function.
 *
 * @param ctx          Click object.
 *
 * @description This function engages the sleep mode.
 */
void ata663211_sleep_mode ( ata663211_t *ctx );

/**
 * @brief Check inhibit pin state function.
 *
 * @param ctx          Click object.
 * 
 * @returns Result  State of the inhibit pin
 *
 * @description This function is used to check the state of inhibit pin.
 */
uint8_t ata663211_check_inh ( ata663211_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ATA663211_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
