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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-09-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/09/30  <td>1.0      <td>Shifeng Li  <td>format the code
 * </table>
 */

#include "driver_as5600_register_test.h"
#include "driver_as5600_read_test.h"
#include "driver_as5600_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     as5600 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t as5600(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            as5600_info_t info;
            
            /* print as5600 info */
            as5600_info(&info);
            as5600_interface_debug_print("as5600: chip is %s.\n", info.chip_name);
            as5600_interface_debug_print("as5600: manufacturer is %s.\n", info.manufacturer_name);
            as5600_interface_debug_print("as5600: interface is %s.\n", info.interface);
            as5600_interface_debug_print("as5600: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            as5600_interface_debug_print("as5600: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            as5600_interface_debug_print("as5600: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            as5600_interface_debug_print("as5600: max current is %0.2fmA.\n", info.max_current_ma);
            as5600_interface_debug_print("as5600: max temperature is %0.1fC.\n", info.temperature_max);
            as5600_interface_debug_print("as5600: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            as5600_interface_debug_print("as5600: SCL connected to GPIOB PIN8.\n");
            as5600_interface_debug_print("as5600: SDA connected to GPIOB PIN9.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show as5600 help */
            
            help:
            as5600_interface_debug_print("as5600 -i\n\tshow as5600 chip and driver information.\n");
            as5600_interface_debug_print("as5600 -h\n\tshow as5600 help.\n");
            as5600_interface_debug_print("as5600 -p\n\tshow as5600 pin connections of the current board.\n");
            as5600_interface_debug_print("as5600 -t reg \n\trun as5600 register test.\n");
            as5600_interface_debug_print("as5600 -t read <times>\n\trun as5600 read test.times is test times.\n");
            as5600_interface_debug_print("as5600 -c read <times>\n\trun as5600 read function.times is read times.\n");

            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run reg test */
                if (as5600_register_test() != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                /* run read test */
                if (as5600_read_test(atoi(argv[3])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i;
                uint32_t times;
                
                /* basic init */
                res = as5600_basic_init();
                if (res != 0)
                {
                    return 1;
                }
                
                /* get the times */
                times = atoi(argv[3]);
                
                for (i = 0; i < times; i++)
                {
                    float deg;
                    
                    /* read data */
                    res = as5600_basic_read(&deg);
                    if (res != 0)
                    {
                        (void)as5600_basic_deinit();
                       
                        return 1;
                    }
                    
                    /* output */
                    as5600_interface_debug_print("as5600: %d/%d.\n", i + 1, times);
                    
                    /* output */
                    as5600_interface_debug_print("as5600: angle is %.2f.\n", deg);
                    
                    /* delay 1000ms */
                    as5600_interface_delay_ms(1000);
                }
                
                /* deinit */
                (void)as5600_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register as5600 fuction */
    shell_init();
    shell_register("as5600", as5600);
    uart1_print("as5600: welcome to libdriver as5600.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("as5600: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("as5600: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("as5600: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("as5600: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("as5600: param is invalid.\n");
            }
            else
            {
                uart1_print("as5600: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
