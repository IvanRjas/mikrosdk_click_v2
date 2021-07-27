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
 * \file dcmotor9.h
 *
 * \brief This file contains API for DC Motor 9 Click driver.
 *
 * \addtogroup dcmotor9 DC Motor 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR9_H
#define DCMOTOR9_H

#include "drv_digital_out.h"
#include "drv_pwm.h"
#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macro Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS mapping
 * \{
 */
#define DCMOTOR9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pw1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.pw2 = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup def_set Default settings
 * \{
 */
#define DCMOTOR9_DEF_FREQ  20000
#define DCMOTOR9_DEF_VREF  3.3
/** \} */

/**
 * \defgroup duty_set PWM duty settings
 * \{
 */
#define DCMOTOR9_PWM_DUTY_PERCENT_0   0.0
#define DCMOTOR9_PWM_DUTY_PERCENT_10  0.1
#define DCMOTOR9_PWM_DUTY_PERCENT_20  0.2
#define DCMOTOR9_PWM_DUTY_PERCENT_30  0.3
#define DCMOTOR9_PWM_DUTY_PERCENT_40  0.4
#define DCMOTOR9_PWM_DUTY_PERCENT_50  0.5
#define DCMOTOR9_PWM_DUTY_PERCENT_60  0.6
#define DCMOTOR9_PWM_DUTY_PERCENT_70  0.7
#define DCMOTOR9_PWM_DUTY_PERCENT_80  0.8
#define DCMOTOR9_PWM_DUTY_PERCENT_90  0.9
#define DCMOTOR9_PWM_DUTY_PERCENT_100 1.0
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
    // Digital output pins.

    digital_out_t shd;
    digital_out_t pw2;

    // Modules.

    pwm_t pwm;
    analog_in_t adc;

} dcmotor9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Gpio pins.

    pin_name_t an;                       /**! Analog state pin. */
    pin_name_t shd;                      /**! Shutdown control pin. */
    pin_name_t pw1;                      /**! PWM control pin 1. */
    pin_name_t pw2;                      /**! PWM control pin 2. */

    // Static variables.

    uint32_t pwm_freq;                   /**! PWM default frequency. */
    analog_in_resolution_t resolution;   /**! ADC resolution. */
    float vref;                          /**! ADC reference voltage. */

} dcmotor9_cfg_t;

/** \} */ // End type group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Init Setup function.
 *
 * @param[out] cfg Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param[out] ctx Click object.
 * @param[in] cfg Click configuration structure.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click board.
 */
err_t dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor9_pwm_stop ( dcmotor9_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor9_pwm_start ( dcmotor9_t *ctx );

/**
 * @brief Enable the engine function.
 *
 * @param ctx  Click object.
 * 
 * @description Function enables the engine by setting SHDN ( RST ) pin on DC Motor 9 Click board.
 */
void dcmotor9_enable ( dcmotor9_t *ctx );

/**
 * @brief Disable the engine function.
 *
 * @param ctx  Click object.
 * 
 * @description Function disables the engine by clearing SHDN ( RST ) pin on DC Motor 9 Click board.
 */
void dcmotor9_standby ( dcmotor9_t *ctx );

/**
 * @brief Set the counter clockwise direction of rotation function.
 *
 * @param ctx  Click object.
 * 
 * @description Function sets the counter clockwise direction of rotation
 * by clearing IN1 ( CS ) pin and seting IN2 ( PWM ) pin on DC Motor 9 Click board.
 */
void dcmotor9_counter_clockwise ( dcmotor9_t *ctx );

/**
 * @brief Set the clockwise direction of rotation function.
 *
 * @param ctx  Click object.
 * 
 * @description Function sets the clockwise direction of rotation
 * by setting IN1 ( CS ) pin and claering IN2 ( PWM ) pin on DC Motor 9 Click board.
 */
void dcmotor9_clockwise ( dcmotor9_t *ctx );

/**
 * @brief Brake the engine function.
 *
 * @param ctx  Click object.
 * 
 * @description Function brakes the engine by setting IN1 ( CS ) and IN2 ( PWM ) pins on DC Motor 9 Click board.
 */
void dcmotor9_short_brake ( dcmotor9_t *ctx );

/**
 * @brief Stop the engine function.
 *
 * @param ctx  Click object.
 * 
 * @description Function stops the engine by clearing IN1 ( CS ) and IN2 ( PWM ) pins on DC Motor 9 Click board.
 */
void dcmotor9_stop ( dcmotor9_t *ctx );

/**
 * @brief AN Value Read function.
 *
 * @param[in] ctx Click object.
 * @param[out] data_out AN value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads results of AD conversion on the AN pin.
 */
err_t dcmotor9_read_an_value ( dcmotor9_t *ctx, uint16_t *data_out );

/**
 * @brief AN Voltage Read function.
 *
 * @param[in] ctx Click object.
 * @param[out] data_out AN voltage [V].
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads results of AD conversion on the AN pin and
 * calculates these results to voltage.
 */
err_t dcmotor9_read_an_voltage ( dcmotor9_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif  // DCMOTOR9_H

/** \} */ // End public_function group
/// \}    // End click driver group
/*! @} */
// ------------------------------------------------------------------------- END
