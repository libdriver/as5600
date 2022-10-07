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
 * @file      driver_as5600_read_test.c
 * @brief     driver as5600 read test source file
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
 
#include "driver_as5600_read_test.h"

static as5600_handle_t gs_handle;        /**< as5600 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t as5600_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    as5600_info_t info;
    
     /* link interface function */
    DRIVER_AS5600_LINK_INIT(&gs_handle, as5600_handle_t);
    DRIVER_AS5600_LINK_IIC_INIT(&gs_handle, as5600_interface_iic_init);
    DRIVER_AS5600_LINK_IIC_DEINIT(&gs_handle, as5600_interface_iic_deinit);
    DRIVER_AS5600_LINK_IIC_READ(&gs_handle, as5600_interface_iic_read);
    DRIVER_AS5600_LINK_IIC_WRITE(&gs_handle, as5600_interface_iic_write);
    DRIVER_AS5600_LINK_DELAY_MS(&gs_handle, as5600_interface_delay_ms);
    DRIVER_AS5600_LINK_DEBUG_PRINT(&gs_handle, as5600_interface_debug_print);
    
    /* get chip information */
    res = as5600_info(&info);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        as5600_interface_debug_print("as5600: chip is %s.\n", info.chip_name);
        as5600_interface_debug_print("as5600: manufacturer is %s.\n", info.manufacturer_name);
        as5600_interface_debug_print("as5600: interface is %s.\n", info.interface);
        as5600_interface_debug_print("as5600: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        as5600_interface_debug_print("as5600: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        as5600_interface_debug_print("as5600: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        as5600_interface_debug_print("as5600: max current is %0.2fmA.\n", info.max_current_ma);
        as5600_interface_debug_print("as5600: max temperature is %0.1fC.\n", info.temperature_max);
        as5600_interface_debug_print("as5600: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* as5600 init */
    res = as5600_init(&gs_handle);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    as5600_interface_debug_print("as5600: start read test.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t angle_raw;
        float deg;
        
        /* read data */
        res = as5600_read(&gs_handle, &angle_raw, &deg);
        if (res != 0)
        {
            as5600_interface_debug_print("as5600: read failed.\n");
            (void)as5600_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        as5600_interface_debug_print("as5600: angle is %.2f and raw angle is %d.\n", deg, angle_raw);
        
        /* delay 1000ms */
        as5600_interface_delay_ms(1000);
    }
    
    /* finish read test */
    as5600_interface_debug_print("as5600: finish read test.\n");
    (void)as5600_deinit(&gs_handle);
    
    return 0;
}
