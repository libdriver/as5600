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
 * @file      driver_as5600_register_test.c
 * @brief     driver as5600 register test source file
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
 
#include "driver_as5600_register_test.h"
#include <stdlib.h>

static as5600_handle_t gs_handle;        /**< as5600 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t as5600_register_test(void)
{
    uint8_t res;
    uint8_t status;
    uint8_t agc;
    uint16_t magnitude;
    uint16_t pos;
    uint16_t pos_check;
    uint16_t ang;
    uint16_t ang_check;
    uint16_t reg;
    float deg;
    float deg_check;
    as5600_info_t info;
    as5600_bool_t enable;
    as5600_power_mode_t mode;
    as5600_slow_filter_t filter;
    as5600_pwm_frequency_t freq;
    as5600_output_stage_t stage;
    as5600_hysteresis_t hysteresis;
    as5600_fast_filter_threshold_t threshold;
    
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
    
    /* start register test */
    as5600_interface_debug_print("as5600: start register test.\n");
    
    /* as5600_set_start_position/as5600_get_start_position test */
    as5600_interface_debug_print("as5600: as5600_set_start_position/as5600_get_start_position test.\n");
    
    pos = rand() % 0xFFF;
    res = as5600_set_start_position(&gs_handle, pos);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set start position failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set start position %d.\n", pos);
    res = as5600_get_start_position(&gs_handle, &pos_check);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get start position failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check start position %s.\n", (pos_check == pos) ? "ok" : "error");
    
    /* as5600_set_stop_position/as5600_get_stop_position test */
    as5600_interface_debug_print("as5600: as5600_set_stop_position/as5600_get_stop_position test.\n");
    
    pos = rand() % 0xFFF;
    res = as5600_set_stop_position(&gs_handle, pos);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set stop position failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set stop position %d.\n", pos);
    res = as5600_get_stop_position(&gs_handle, &pos_check);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get stop position failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check stop position %s.\n", (pos_check == pos) ? "ok" : "error");
    
    /* as5600_set_max_angle/as5600_get_max_angle test */
    as5600_interface_debug_print("as5600: as5600_set_max_angle/as5600_get_max_angle test.\n");
    
    ang = 0;
    res = as5600_set_max_angle(&gs_handle, ang);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set max angle failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set max angle %d.\n", ang);
    res = as5600_get_max_angle(&gs_handle, &ang_check);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get max angle failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check max angle %s.\n", (ang_check == ang) ? "ok" : "error");
    
    /* as5600_set_watch_dog/as5600_get_watch_dog test */
    as5600_interface_debug_print("as5600: as5600_set_watch_dog/as5600_get_watch_dog test.\n");
    
    /* enable watch dog */
    res = as5600_set_watch_dog(&gs_handle, AS5600_BOOL_TRUE);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set watch dog failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: enable watch dog.\n");
    res = as5600_get_watch_dog(&gs_handle, &enable);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get watch dog failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check watch dog %s.\n", (enable == AS5600_BOOL_TRUE) ? "ok" : "error");
    
    /* disable watch dog */
    res = as5600_set_watch_dog(&gs_handle, AS5600_BOOL_FALSE);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set watch dog failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: disable watch dog.\n");
    res = as5600_get_watch_dog(&gs_handle, &enable);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get watch dog failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check watch dog %s.\n", (enable == AS5600_BOOL_FALSE) ? "ok" : "error");
    
    /* as5600_set_fast_filter_threshold/as5600_get_fast_filter_threshold test */
    as5600_interface_debug_print("as5600: as5600_set_fast_filter_threshold/as5600_get_fast_filter_threshold test.\n");
    
    /* slow filter only */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_SLOW_FILTER_ONLY);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold slow filter only.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_SLOW_FILTER_ONLY) ? "ok" : "error");
    
    /* 6 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_6LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 6 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_6LSB) ? "ok" : "error");
    
    /* 7 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_7LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 7 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_7LSB) ? "ok" : "error");
    
    /* 9 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_9LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 9 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_9LSB) ? "ok" : "error");
    
    /* 10 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_10LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 10 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_10LSB) ? "ok" : "error");
    
    /* 18 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_18LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 18 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_18LSB) ? "ok" : "error");
    
    /* 21 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_21LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 21 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_21LSB) ? "ok" : "error");
    
    /* 24 lsb */
    res = as5600_set_fast_filter_threshold(&gs_handle, AS5600_FAST_FILTER_THRESHOLD_24LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set fast filter threshold 24 lsb.\n");
    res = as5600_get_fast_filter_threshold(&gs_handle, &threshold);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get fast filter threshold failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check fast filter threshold %s.\n", (threshold == AS5600_FAST_FILTER_THRESHOLD_24LSB) ? "ok" : "error");
    
    /* as5600_set_slow_filter/as5600_get_slow_filter test */
    as5600_interface_debug_print("as5600: as5600_set_slow_filter/as5600_get_slow_filter test.\n");
    
    /* 16X */
    res = as5600_set_slow_filter(&gs_handle, AS5600_SLOW_FILTER_16X);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set slow filter 16X.\n");
    res = as5600_get_slow_filter(&gs_handle, &filter);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check slow filter %s.\n", (filter == AS5600_SLOW_FILTER_16X) ? "ok" : "error");
    
    /* 8X */
    res = as5600_set_slow_filter(&gs_handle, AS5600_SLOW_FILTER_8X);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set slow filter 8X.\n");
    res = as5600_get_slow_filter(&gs_handle, &filter);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check slow filter %s.\n", (filter == AS5600_SLOW_FILTER_8X) ? "ok" : "error");
    
    /* 4X */
    res = as5600_set_slow_filter(&gs_handle, AS5600_SLOW_FILTER_4X);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set slow filter 4X.\n");
    res = as5600_get_slow_filter(&gs_handle, &filter);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check slow filter %s.\n", (filter == AS5600_SLOW_FILTER_4X) ? "ok" : "error");
    
    /* 2X */
    res = as5600_set_slow_filter(&gs_handle, AS5600_SLOW_FILTER_2X);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set slow filter 2X.\n");
    res = as5600_get_slow_filter(&gs_handle, &filter);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get slow filter failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check slow filter %s.\n", (filter == AS5600_SLOW_FILTER_2X) ? "ok" : "error");
    
    /* as5600_set_pwm_frequency/as5600_get_pwm_frequency test */
    as5600_interface_debug_print("as5600: as5600_set_pwm_frequency/as5600_get_pwm_frequency test.\n");
    
    /* 115Hz */
    res = as5600_set_pwm_frequency(&gs_handle, AS5600_PWM_FREQUENCY_115HZ);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set pwm frequency 115Hz.\n");
    res = as5600_get_pwm_frequency(&gs_handle, &freq);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check pwm frequency %s.\n", (freq == AS5600_PWM_FREQUENCY_115HZ) ? "ok" : "error");
    
    /* 230Hz */
    res = as5600_set_pwm_frequency(&gs_handle, AS5600_PWM_FREQUENCY_230HZ);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set pwm frequency 230Hz.\n");
    res = as5600_get_pwm_frequency(&gs_handle, &freq);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check pwm frequency %s.\n", (freq == AS5600_PWM_FREQUENCY_230HZ) ? "ok" : "error");
    
    /* 460Hz */
    res = as5600_set_pwm_frequency(&gs_handle, AS5600_PWM_FREQUENCY_460HZ);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set pwm frequency 460Hz.\n");
    res = as5600_get_pwm_frequency(&gs_handle, &freq);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check pwm frequency %s.\n", (freq == AS5600_PWM_FREQUENCY_460HZ) ? "ok" : "error");
    
    /* 920Hz */
    res = as5600_set_pwm_frequency(&gs_handle, AS5600_PWM_FREQUENCY_920HZ);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set pwm frequency 920Hz.\n");
    res = as5600_get_pwm_frequency(&gs_handle, &freq);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get pwm frequency failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check pwm frequency %s.\n", (freq == AS5600_PWM_FREQUENCY_920HZ) ? "ok" : "error");
    
    /* as5600_set_output_stage/as5600_get_output_stage test */
    as5600_interface_debug_print("as5600: as5600_set_output_stage/as5600_get_output_stage test.\n");
    
    /* full range */
    res = as5600_set_output_stage(&gs_handle, AS5600_OUTPUT_STAGE_ANALOG_FULL);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set output stage failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set output stage full range.\n");
    res = as5600_get_output_stage(&gs_handle, &stage);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get output stage failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check output stage %s.\n", (stage == AS5600_OUTPUT_STAGE_ANALOG_FULL) ? "ok" : "error");
    
    /* reduced */
    res = as5600_set_output_stage(&gs_handle, AS5600_OUTPUT_STAGE_ANALOG_REDUCED);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set output stage failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set output stage reduced.\n");
    res = as5600_get_output_stage(&gs_handle, &stage);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get output stage failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check output stage %s.\n", (stage == AS5600_OUTPUT_STAGE_ANALOG_REDUCED) ? "ok" : "error");
    
    /* digital pwm */
    res = as5600_set_output_stage(&gs_handle, AS5600_OUTPUT_STAGE_PWM);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set output stage failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set output stage digital pwm.\n");
    res = as5600_get_output_stage(&gs_handle, &stage);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get output stage failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check output stage %s.\n", (stage == AS5600_OUTPUT_STAGE_PWM) ? "ok" : "error");
    
    /* as5600_set_hysteresis/as5600_get_hysteresis test */
    as5600_interface_debug_print("as5600: as5600_set_hysteresis/as5600_get_hysteresis test.\n");
    
    /* hysteresis off */
    res = as5600_set_hysteresis(&gs_handle, AS5600_HYSTERESIS_OFF);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set hysteresis off.\n");
    res = as5600_get_hysteresis(&gs_handle, &hysteresis);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (hysteresis == AS5600_HYSTERESIS_OFF) ? "ok" : "error");
    
    /* hysteresis 1 lsb */
    res = as5600_set_hysteresis(&gs_handle, AS5600_HYSTERESIS_1LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set hysteresis 1 lsb.\n");
    res = as5600_get_hysteresis(&gs_handle, &hysteresis);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (hysteresis == AS5600_HYSTERESIS_1LSB) ? "ok" : "error");
    
    /* hysteresis 2 lsb */
    res = as5600_set_hysteresis(&gs_handle, AS5600_HYSTERESIS_2LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set hysteresis 2 lsb.\n");
    res = as5600_get_hysteresis(&gs_handle, &hysteresis);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (hysteresis == AS5600_HYSTERESIS_2LSB) ? "ok" : "error");
    
    /* hysteresis 3 lsb */
    res = as5600_set_hysteresis(&gs_handle, AS5600_HYSTERESIS_3LSB);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set hysteresis 3 lsb.\n");
    res = as5600_get_hysteresis(&gs_handle, &hysteresis);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get hysteresis failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (hysteresis == AS5600_HYSTERESIS_3LSB) ? "ok" : "error");
    
    /* as5600_set_power_mode/as5600_get_power_mode test */
    as5600_interface_debug_print("as5600: as5600_set_power_mode/as5600_get_power_mode test.\n");
    
    /* nom */
    res = as5600_set_power_mode(&gs_handle, AS5600_POWER_MODE_NOM);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set power mode nom.\n");
    res = as5600_get_power_mode(&gs_handle, &mode);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (mode == AS5600_POWER_MODE_NOM) ? "ok" : "error");
    
    /* lpm1 */
    res = as5600_set_power_mode(&gs_handle, AS5600_POWER_MODE_LPM1);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set power mode lpm1.\n");
    res = as5600_get_power_mode(&gs_handle, &mode);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (mode == AS5600_POWER_MODE_LPM1) ? "ok" : "error");
    
    /* lpm2 */
    res = as5600_set_power_mode(&gs_handle, AS5600_POWER_MODE_LPM2);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set power mode lpm2.\n");
    res = as5600_get_power_mode(&gs_handle, &mode);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (mode == AS5600_POWER_MODE_LPM2) ? "ok" : "error");
    
    /* lpm3 */
    res = as5600_set_power_mode(&gs_handle, AS5600_POWER_MODE_LPM3);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: set power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: set power mode lpm3.\n");
    res = as5600_get_power_mode(&gs_handle, &mode);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get power mode failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check hysteresis %s.\n", (mode == AS5600_POWER_MODE_LPM3) ? "ok" : "error");
    
    /* as5600_get_raw_angle test */
    as5600_interface_debug_print("as5600: as5600_get_raw_angle test.\n");
    
    /* get raw angle */
    res = as5600_get_raw_angle(&gs_handle, &ang);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get raw angle failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: get raw angle %d.\n", ang);
    
    /* as5600_get_angle test */
    as5600_interface_debug_print("as5600: as5600_get_angle test.\n");
    
    /* get angle */
    res = as5600_get_angle(&gs_handle, &ang);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get angle failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: get angle %d.\n", ang);
    
    /* as5600_get_status test */
    as5600_interface_debug_print("as5600: as5600_get_status test.\n");
    
    /* get status */
    res = as5600_get_status(&gs_handle, &status);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get status failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: get status 0x%02X.\n", status);
    
    /* as5600_get_agc test */
    as5600_interface_debug_print("as5600: as5600_get_agc test.\n");
    
    /* get agc */
    res = as5600_get_agc(&gs_handle, &agc);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get agc failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: get agc 0x%02X.\n", agc);
    
    /* as5600_get_magnitude test */
    as5600_interface_debug_print("as5600: as5600_get_magnitude test.\n");
    
    /* get magnitude */
    res = as5600_get_magnitude(&gs_handle, &magnitude);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: get magnitude failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: get magnitude %d.\n", magnitude);
    
    /* as5600_angle_convert_to_data test */
    as5600_interface_debug_print("as5600: as5600_angle_convert_to_register/as5600_angle_convert_to_data test.\n");
    
    /* set the deg */
    deg = (float)(rand() % 36000) / 10.0f;
    
    /* convert to register */
    res = as5600_angle_convert_to_register(&gs_handle, deg, &reg);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: angle convert to register failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    as5600_interface_debug_print("as5600: set angle %0.2f.\n", deg);
    
    /* convert to data */
    res = as5600_angle_convert_to_data(&gs_handle, reg, &deg_check);
    if (res != 0)
    {
        as5600_interface_debug_print("as5600: angle convert to data failed.\n");
        (void)as5600_deinit(&gs_handle);
       
        return 1;
    }
    as5600_interface_debug_print("as5600: check angle %0.2f.\n", deg_check);
    
    /* finish register test */
    as5600_interface_debug_print("as5600: finish register test.\n");
    (void)as5600_deinit(&gs_handle);
    
    return 0;
}
