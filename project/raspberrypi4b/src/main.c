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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     as5600 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t as5600(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }

            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
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
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (as5600_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* basic init */
        res = as5600_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
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
    else if (strcmp("h", type) == 0)
    {
        help:
        as5600_interface_debug_print("Usage:\n");
        as5600_interface_debug_print("  as5600 (-i | --information)\n");
        as5600_interface_debug_print("  as5600 (-h | --help)\n");
        as5600_interface_debug_print("  as5600 (-p | --port)\n");
        as5600_interface_debug_print("  as5600 (-t reg | --test=reg)\n");
        as5600_interface_debug_print("  as5600 (-t read | --test=read) [--times=<num>]\n");
        as5600_interface_debug_print("  as5600 (-e read | --example=read) [--times=<num>]\n");
        as5600_interface_debug_print("\n");
        as5600_interface_debug_print("Options:\n");
        as5600_interface_debug_print("  -e <read>, --example=<read>             Run the driver example.\n");
        as5600_interface_debug_print("  -h, --help                              Show the help.\n");
        as5600_interface_debug_print("  -i, --information                       Show the chip information.\n");
        as5600_interface_debug_print("  -p, --port                              Display the pin connections of the current board.\n");
        as5600_interface_debug_print("  -t <reg | read>, --test=<reg | read>    Run the driver test.\n");
        as5600_interface_debug_print("      --times=<num>                       Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        as5600_interface_debug_print("as5600: SCL connected to GPIO3(BCM).\n");
        as5600_interface_debug_print("as5600: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = as5600(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        as5600_interface_debug_print("as5600: run failed.\n");
    }
    else if (res == 5)
    {
        as5600_interface_debug_print("as5600: param is invalid.\n");
    }
    else
    {
        as5600_interface_debug_print("as5600: unknown status code.\n");
    }

    return 0;
}
