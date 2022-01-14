/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file ambient18.c
 * @brief Ambient 18 Click Driver.
 */

#include "ambient18.h"

void ambient18_cfg_setup ( ambient18_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->gc1 = HAL_PIN_NC;
    cfg->gc2 = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT18_SET_DEV_ADDR;
    cfg->vref        = AMBIENT18_VREF_3V3;
    cfg->drv_sel     = AMBIENT18_DRV_SEL_I2C;
}

err_t ambient18_init ( ambient18_t *ctx, ambient18_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( AMBIENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
        {
            return ADC_ERROR;
        }
    }

    digital_out_init( &ctx->gc1, cfg->gc1 );
    digital_out_init( &ctx->gc2, cfg->gc2 );

    return AMBIENT18_OK;
}

err_t ambient18_read_raw_adc ( ambient18_t *ctx, uint16_t *raw_adc ) 
{
    if ( AMBIENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ];
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & AMBIENT18_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t ambient18_read_voltage ( ambient18_t *ctx, float *voltage ) 
{
    if ( AMBIENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc;
        err_t err_flag = ambient18_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) AMBIENT18_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t ambient18_set_vref ( ambient18_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( AMBIENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return AMBIENT18_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

void ambient18_set_gain_mode ( ambient18_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case AMBIENT18_MODE_SHUTDOWN:
        {
            digital_out_low ( &ctx->gc1 );
            digital_out_low ( &ctx->gc2 );
            ctx->gain_mode = AMBIENT18_MODE_SHUTDOWN;
            break;
        }
        case AMBIENT18_MODE_H_GAIN:
        {
            digital_out_high ( &ctx->gc1 );
            digital_out_low ( &ctx->gc2 );
            ctx->gain_mode = AMBIENT18_MODE_H_GAIN;
            break;
        }
        case AMBIENT18_MODE_M_GAIN:
        {
            digital_out_low ( &ctx->gc1 );
            digital_out_high ( &ctx->gc2 );
            ctx->gain_mode = AMBIENT18_MODE_M_GAIN;
            break;
        }
        case AMBIENT18_MODE_L_GAIN:
        {
            digital_out_high ( &ctx->gc1 );
            digital_out_high ( &ctx->gc2 );
            ctx->gain_mode = AMBIENT18_MODE_L_GAIN;
            break;
        }
        default:
        {
            break;
        }
    }
    Delay_10ms( );
}

int32_t ambient18_voltage_to_lux ( ambient18_t *ctx, float voltage )
{
    float gain = 0;
    switch ( ctx->gain_mode )
    {
        case AMBIENT18_MODE_H_GAIN:
        {
            gain = AMBIENT18_IOUT_CURRENT_H_GAIN;
            break;
        }
        case AMBIENT18_MODE_M_GAIN:
        {
            gain = AMBIENT18_IOUT_CURRENT_M_GAIN;
            break;
        }
        case AMBIENT18_MODE_L_GAIN:
        {
            gain = AMBIENT18_IOUT_CURRENT_L_GAIN;
            break;
        }
        default:
        {
            return AMBIENT18_ERROR;
        }
    }
    
    return ( int32_t ) ( voltage / ( gain * AMBIENT18_MICROAMPER_TO_AMPER * AMBIENT18_IOUT_RESISTOR ) );
}

// ------------------------------------------------------------------------- END
