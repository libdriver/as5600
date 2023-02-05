/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      driver_as5600.c
 * @brief     driver as5600 source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-09-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/09/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_as5600.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "AMS AS5600"        /**< chip name */
#define MANUFACTURER_NAME         "AMS"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        4.5f                /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                /**< chip max supply voltage */
#define MAX_CURRENT               100.0f              /**< chip max current */
#define TEMPERATURE_MIN           -40.0f              /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f              /**< chip max operating temperature */
#define DRIVER_VERSION            1000                /**< driver version */

/**
 * @brief chip address definition
 */
#define AS5600_ADDRESS            0x6C        /**< iic device address */

/**
 * @brief chip register definition
 */
#define AS5600_REG_ZMCO               0x00        /**< written times register */
#define AS5600_REG_ZPOS_H             0x01        /**< start position register high */
#define AS5600_REG_ZPOS_L             0x02        /**< start position register low */
#define AS5600_REG_MPOS_H             0x03        /**< stop position register high */
#define AS5600_REG_MPOS_L             0x04        /**< stop position register low */
#define AS5600_REG_MANG_H             0x05        /**< maximum angle register high */
#define AS5600_REG_MANG_L             0x06        /**< maximum angle register low */
#define AS5600_REG_CONF_H             0x07        /**< conf register high */
#define AS5600_REG_CONF_L             0x08        /**< conf register low */
#define AS5600_REG_RAW_ANGLE_H        0x0C        /**< raw angle register high */
#define AS5600_REG_RAW_ANGLE_L        0x0D        /**< raw angle register low */
#define AS5600_REG_ANGLE_H            0x0E        /**< angle register high */
#define AS5600_REG_ANGLE_L            0x0F        /**< angle register low */
#define AS5600_REG_STATUS             0x0B        /**< status register */
#define AS5600_REG_AGC                0x1A        /**< automatic gain control register */
#define AS5600_REG_MAGNITUDE_H        0x1B        /**< magnitude register high */
#define AS5600_REG_MAGNITUDE_L        0x1C        /**< magnitude register low */
#define AS5600_REG_BURN               0xFF        /**< burn register */

/**
 * @brief      read bytes
 * @param[in]  *handle points to an as5600 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_as5600_iic_read(as5600_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read(AS5600_ADDRESS, reg, data, len) != 0)        /* read the register */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_as5600_iic_write(as5600_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(AS5600_ADDRESS, reg, data, len) != 0)       /* write the register */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an as5600 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t as5600_init(as5600_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                    /* check iic_init */
    {
        handle->debug_print("as5600: iic_init is null.\n");          /* iic_init is null */

        return 3;                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                  /* check iic_init */
    {
        handle->debug_print("as5600: iic_deinit is null.\n");        /* iic_deinit is null */

        return 3;                                                    /* return error */
    }
    if (handle->iic_read == NULL)                                    /* check iic_read */
    {
        handle->debug_print("as5600: iic_read is null.\n");          /* iic_read is null */

        return 3;                                                    /* return error */
    }
    if (handle->iic_write == NULL)                                   /* check iic_write */
    {
        handle->debug_print("as5600: iic_write is null.\n");         /* iic_write is null */

        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("as5600: delay_ms is null.\n");          /* delay_ms is null */

        return 3;                                                    /* return error */
    }

    if (handle->iic_init() != 0)                                     /* iic init */
    {
        handle->debug_print("as5600: iic init failed.\n");           /* iic init failed */

        return 1;                                                    /* return error */
    }
    handle->inited = 1;                                              /* flag finish initialization */

    return 0;                                                        /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to an as5600 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_deinit(as5600_handle_t *handle)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }

    if (handle->iic_deinit() != 0)                                  /* iic deinit */
    {
        handle->debug_print("as5600: iic deinit failed.\n");        /* iic deinit failed */

        return 1;                                                   /* return error */
    }
    handle->inited = 0;                                             /* flag close */

    return 0;                                                       /* success return 0 */
}

/**
 * @brief      read the magnetic angle
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *angle_raw points to a raw angle buffer
 * @param[out] *deg points to a converted angle buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_read(as5600_handle_t *handle, uint16_t *angle_raw, float *deg)
{
    uint8_t buf[2];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_RAW_ANGLE_H, buf, 2) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get raw angle failed.\n");                /* get raw angle failed */

        return 1;                                                              /* return error */
    }
    else
    {
        *angle_raw = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];          /* set the raw angle */
        *deg = (float)(*angle_raw ) * (360.0f / 4096.0f);                      /* convert the raw data to the real data */

        return 0;                                                              /* success return 0 */
    }
}

/**
 * @brief      convert the angle to the register raw data
 * @param[in]  *handle points to an as5600 handle structure
 * @param[in]  deg is the angle
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_angle_convert_to_register(as5600_handle_t *handle, float deg, uint16_t *reg)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }

    *reg = (uint16_t)(deg / (360.0f / 4096.0f));         /* convert real data to register data */

    return 0;                                            /* success return 0 */
}

/**
 * @brief      convert the register raw data to the angle
 * @param[in]  *handle points to an as5600 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *deg points to an angle buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_angle_convert_to_data(as5600_handle_t *handle, uint16_t reg, float *deg)
{
    if (handle == NULL)                              /* check handle */
    {
        return 2;                                    /* return error */
    }
    if (handle->inited != 1)                         /* check handle initialization */
    {
        return 3;                                    /* return error */
    }

    *deg = (float)(reg) * (360.0f / 4096.0f);        /* convert raw data to real data */

    return 0;                                        /* success return 0 */
}

/**
 * @brief     set the start position
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] pos is the start position
 * @return    status code
 *            - 0 success
 *            - 1 set start position failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 pos is over 0xFFF
 * @note      none
 */
uint8_t as5600_set_start_position(as5600_handle_t *handle, uint16_t pos)
{
    uint8_t buf[2];

    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (pos > 0xFFF)                                                        /* check the pos */
    {
        handle->debug_print("as5600: pos is over 0xFFF.\n");                /* pos is over 0xFFF */

        return 4;                                                           /* return error */
    }

    buf[0] = (pos >> 8) & 0x0F;                                             /* set high part */
    buf[1] = (pos >> 0) & 0xFF;                                             /* set low part */
    if (a_as5600_iic_write(handle, AS5600_REG_ZPOS_H, buf, 2) != 0)         /* write conf */
    {
        handle->debug_print("as5600: set start position failed.\n");        /* set start position failed */

        return 1;                                                           /* return error */
    }
    else
    {
        return 0;                                                           /* success return 0 */
    }
}

/**
 * @brief      get the start position
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *pos points to a start position buffer
 * @return     status code
 *             - 0 success
 *             - 1 get start position failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_start_position(as5600_handle_t *handle, uint16_t *pos)
{
    uint8_t buf[2];

    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_ZPOS_H, buf, 2) != 0)          /* read conf */
    {
        handle->debug_print("as5600: get start position failed.\n");        /* get start position failed */

        return 1;                                                           /* return error */
    }
    else
    {
        *pos = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];             /* set the position */

        return 0;                                                           /* success return 0 */
    }
}

/**
 * @brief     set the stop position
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] pos is the stop position
 * @return    status code
 *            - 0 success
 *            - 1 set stop position failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 pos is over 0xFFF
 * @note      none
 */
uint8_t as5600_set_stop_position(as5600_handle_t *handle, uint16_t pos)
{
    uint8_t buf[2];

    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (pos > 0xFFF)                                                        /* check the pos */
    {
        handle->debug_print("as5600: pos is over 0xFFF.\n");                /* pos is over 0xFFF */

        return 4;                                                           /* return error */
    }

    buf[0] = (pos >> 8) & 0x0F;                                             /* set high part */
    buf[1] = (pos >> 0) & 0xFF;                                             /* set low part */
    if (a_as5600_iic_write(handle, AS5600_REG_MPOS_H, buf, 2) != 0)         /* write conf */
    {
        handle->debug_print("as5600: set stop position failed.\n");         /* set stop position failed */

        return 1;                                                           /* return error */
    }
    else
    {
        return 0;                                                           /* success return 0 */
    }
}

/**
 * @brief      get the stop position
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *pos points to a stop position buffer
 * @return     status code
 *             - 0 success
 *             - 1 get stop position failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_stop_position(as5600_handle_t *handle, uint16_t *pos)
{
    uint8_t buf[2];

    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_MPOS_H, buf, 2) != 0)          /* read conf */
    {
        handle->debug_print("as5600: get stop position failed.\n");         /* get stop position failed */

        return 1;                                                           /* return error */
    }
    else
    {
        *pos = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];             /* set the position */

        return 0;                                                           /* success return 0 */
    }
}

/**
 * @brief     set the max angle
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] ang is the max angle
 * @return    status code
 *            - 0 success
 *            - 1 set max angle failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 ang is over 0xFFF
 * @note      none
 */
uint8_t as5600_set_max_angle(as5600_handle_t *handle, uint16_t ang)
{
    uint8_t buf[2];

    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (ang > 0xFFF)                                                        /* check the ang */
    {
        handle->debug_print("as5600: ang is over 0xFFF.\n");                /* ang is over 0xFFF */

        return 4;                                                           /* return error */
    }

    buf[0] = (ang >> 8) & 0x0F;                                             /* set high part */
    buf[1] = (ang >> 0) & 0xFF;                                             /* set low part */
    if (a_as5600_iic_write(handle, AS5600_REG_MANG_H, buf, 2) != 0)         /* write conf */
    {
        handle->debug_print("as5600: set max angle failed.\n");             /* set max angle failed */

        return 1;                                                           /* return error */
    }
    else
    {
        return 0;                                                           /* success return 0 */
    }
}

/**
 * @brief      get the max angle
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *ang points to a max angle buffer
 * @return     status code
 *             - 0 success
 *             - 1 get max angle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_max_angle(as5600_handle_t *handle, uint16_t *ang)
{
    uint8_t buf[2];

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_MANG_H, buf, 2) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get max angle failed.\n");           /* get max angle failed */

        return 1;                                                         /* return error */
    }
    else
    {
        *ang = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];           /* set the position */

        return 0;                                                         /* success return 0 */
    }
}

/**
 * @brief     enable or disable the watch dog
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set watchdog failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_watch_dog(as5600_handle_t *handle, as5600_bool_t enable)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_H, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(1 << 5);                                                    /* clear the settings */
    prev |= enable << 5;                                                  /* set the bool */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_H, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the watch dog status
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get watchdog failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_watch_dog(as5600_handle_t *handle, as5600_bool_t *enable)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_H, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *enable = (as5600_bool_t)((prev >> 5) & 0x1);                         /* get the bool */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     set the fast filter threshold
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] threshold is the fast filter threshold
 * @return    status code
 *            - 0 success
 *            - 1 set fast filter threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_fast_filter_threshold(as5600_handle_t *handle, as5600_fast_filter_threshold_t threshold)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_H, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(7 << 2);                                                    /* clear the settings */
    prev |= threshold << 2;                                               /* set the threshold */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_H, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the fast filter threshold
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *threshold points to a fast filter threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fast filter threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_fast_filter_threshold(as5600_handle_t *handle, as5600_fast_filter_threshold_t *threshold)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_H, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *threshold = (as5600_fast_filter_threshold_t)((prev >> 2) & 0x7);     /* set the threshold */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     set the slow filter
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] filter is the slow filter
 * @return    status code
 *            - 0 success
 *            - 1 set slow filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_slow_filter(as5600_handle_t *handle, as5600_slow_filter_t filter)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_H, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(3 << 0);                                                    /* clear the settings */
    prev |= filter << 0;                                                  /* set the filter */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_H, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the slow filter
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *filter points to a slow filter buffer
 * @return     status code
 *             - 0 success
 *             - 1 get slow filter failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_slow_filter(as5600_handle_t *handle, as5600_slow_filter_t *filter)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_H, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *filter = (as5600_slow_filter_t)(prev & 0x3);                         /* get the filter */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     set the pwm frequency
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] freq is the pwm frequency
 * @return    status code
 *            - 0 success
 *            - 1 set pwm frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_pwm_frequency(as5600_handle_t *handle, as5600_pwm_frequency_t freq)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(3 << 6);                                                    /* clear the settings */
    prev |= freq << 6;                                                    /* set the freq */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_L, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the pwm frequency
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *freq points to a pwm frequency buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pwm frequency failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_pwm_frequency(as5600_handle_t *handle, as5600_pwm_frequency_t *freq)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *freq = (as5600_pwm_frequency_t)((prev >> 6) & 0x3);                  /* set the frequency */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     set the output stage
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] stage is the output stage
 * @return    status code
 *            - 0 success
 *            - 1 set output stage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_output_stage(as5600_handle_t *handle, as5600_output_stage_t stage)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(3 << 4);                                                    /* clear the settings */
    prev |= stage << 4;                                                   /* set the stage */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_L, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the output stage
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *stage points to an output stage buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output stage failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_output_stage(as5600_handle_t *handle, as5600_output_stage_t *stage)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *stage = (as5600_output_stage_t)((prev >> 4) & 0x3);                  /* get the output stage */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     set the hysteresis
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] hysteresis is the set hysteresis
 * @return    status code
 *            - 0 success
 *            - 1 set hysteresis failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_hysteresis(as5600_handle_t *handle, as5600_hysteresis_t hysteresis)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(3 << 2);                                                    /* clear the settings */
    prev |= hysteresis << 2;                                              /* set the hysteresis */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_L, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the hysteresis
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *hysteresis points to a hysteresis buffer
 * @return     status code
 *             - 0 success
 *             - 1 get hysteresis failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_hysteresis(as5600_handle_t *handle, as5600_hysteresis_t *hysteresis)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *hysteresis = (as5600_hysteresis_t)((prev >> 2) & 0x3);               /* get the hysteresis */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     set the power mode
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] mode is the power mode
 * @return    status code
 *            - 0 success
 *            - 1 set power mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_power_mode(as5600_handle_t *handle, as5600_power_mode_t mode)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    prev &= ~(3 << 0);                                                    /* clear the settings */
    prev |= mode << 0;                                                    /* set the power mode */
    if (a_as5600_iic_write(handle, AS5600_REG_CONF_L, &prev, 1) != 0)     /* write conf */
    {
        handle->debug_print("as5600: set conf failed.\n");                /* set conf failed */

        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the power mode
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *mode points to a power mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get power mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_power_mode(as5600_handle_t *handle, as5600_power_mode_t *mode)
{
    uint8_t prev;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_CONF_L, &prev, 1) != 0)      /* read conf */
    {
        handle->debug_print("as5600: get conf failed.\n");                /* get conf failed */

        return 1;                                                         /* return error */
    }
    *mode = (as5600_power_mode_t)((prev >> 0) & 0x3);                     /* get the power mode */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief      get the raw angle
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *ang points to an ang buffer
 * @return     status code
 *             - 0 success
 *             - 1 get raw angle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_raw_angle(as5600_handle_t *handle, uint16_t *ang)
{
    uint8_t buf[2];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_RAW_ANGLE_H, buf, 2) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get raw angle failed.\n");                /* get raw angle failed */

        return 1;                                                              /* return error */
    }
    else
    {
        *ang = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];                /* set the angle */

        return 0;                                                              /* success return 0 */
    }
}

/**
 * @brief      get the angle
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *ang points to an ang buffer
 * @return     status code
 *             - 0 success
 *             - 1 get angle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_angle(as5600_handle_t *handle, uint16_t *ang)
{
    uint8_t buf[2];

    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_ANGLE_H, buf, 2) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get angle failed.\n");                /* get angle failed */

        return 1;                                                          /* return error */
    }
    else
    {
        *ang = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];            /* set the angle */

        return 0;                                                          /* success return 0 */
    }
}

/**
 * @brief      get the status
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_status(as5600_handle_t *handle, uint8_t *status)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_STATUS, status, 1) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get status failed.\n");                 /* get status failed */

        return 1;                                                            /* return error */
    }
    else
    {
        return 0;                                                            /* success return 0 */
    }
}

/**
 * @brief      get the automatic gain control
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *agc points to an agc buffer
 * @return     status code
 *             - 0 success
 *             - 1 get agc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_agc(as5600_handle_t *handle, uint8_t *agc)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_AGC, agc, 1) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get agc failed.\n");              /* get agc failed */

        return 1;                                                      /* return error */
    }
    else
    {
        return 0;                                                      /* success return 0 */
    }
}

/**
 * @brief      get the magnitude
 * @param[in]  *handle points to an as5600 handle structure
 * @param[out] *magnitude points to a magnitude buffer
 * @return     status code
 *             - 0 success
 *             - 1 get magnitude failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_magnitude(as5600_handle_t *handle, uint16_t *magnitude)
{
    uint8_t buf[2];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_as5600_iic_read(handle, AS5600_REG_MAGNITUDE_H, buf, 2) != 0)        /* read conf */
    {
        handle->debug_print("as5600: get magnitude failed.\n");                /* get magnitude failed */

        return 1;                                                              /* return error */
    }
    else
    {
        *magnitude = (uint16_t)(((buf[0] >> 0) & 0xF) << 8) | buf[1];          /* set the angle */

        return 0;                                                              /* success return 0 */
    }
}

/**
 * @brief     set the burn
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] burn is the set command
 * @return    status code
 *            - 0 success
 *            - 1 set burn failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_burn(as5600_handle_t *handle, as5600_burn_t burn)
{
    uint8_t prev;

    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }

    prev = burn;                                                           /* set the burn */
    if (a_as5600_iic_write(handle, AS5600_REG_BURN, &prev, 1) != 0)        /* write conf */
    {
        handle->debug_print("as5600: set burn failed.\n");                 /* set burn failed */

        return 1;                                                          /* return error */
    }

    return 0;                                                              /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle points to an as5600 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t as5600_set_reg(as5600_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;

    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }

    res = a_as5600_iic_write(handle, reg, buf, len);                    /* write data */
    if (res != 0)                                                       /* check result */
    {
        handle->debug_print("as5600: write register failed.\n");        /* write register failed */

        return 1;                                                       /* return error */
    }

    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an as5600 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t as5600_get_reg(as5600_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;

    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }

    res = a_as5600_iic_read(handle, reg, buf, len);                    /* read data */
    if (res != 0)                                                      /* check result */
    {
        handle->debug_print("as5600: read register failed.\n");        /* read register failed */

        return 1;                                                      /* return error */
    }

    return 0;                                                          /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an as5600 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t as5600_info(as5600_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(as5600_info_t));                         /* initialize as5600 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
