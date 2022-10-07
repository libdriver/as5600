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
 * @file      driver_as5600_basic.c
 * @brief     driver as5600 basic source file
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

#include "driver_as5600_basic.h"

static as5600_handle_t gs_handle;        /**< as5600 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t as5600_basic_init(void)
{
    uint8_t res;
    
     /* link interface function */
    DRIVER_AS5600_LINK_INIT(&gs_handle, as5600_handle_t);
    DRIVER_AS5600_LINK_IIC_INIT(&gs_handle, as5600_interface_iic_init);
    DRIVER_AS5600_LINK_IIC_DEINIT(&gs_handle, as5600_interface_iic_deinit);
    DRIVER_AS5600_LINK_IIC_READ(&gs_handle, as5600_interface_iic_read);
    DRIVER_AS5600_LINK_IIC_WRITE(&gs_handle, as5600_interface_iic_write);
    DRIVER_AS5600_LINK_DELAY_MS(&gs_handle, as5600_interface_delay_ms);
    DRIVER_AS5600_LINK_DEBUG_PRINT(&gs_handle, as5600_interface_debug_print);
    
    /* as5600 init */
    res = as5600_init(&gs_handle);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: init failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *angle points to an angle buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t as5600_basic_read(float *angle)
{
    uint8_t res;
    uint16_t angle_raw;
    
    /* read data */
    res = as5600_read(&gs_handle, &angle_raw, angle);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: read failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t as5600_basic_deinit(void)
{
    /* close as5600 */
    if (as5600_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
