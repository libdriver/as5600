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
 * @file      driver_as5600.h
 * @brief     driver as5600 header file
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

#ifndef DRIVER_AS5600_H
#define DRIVER_AS5600_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup as5600_driver as5600 driver function
 * @brief    as5600 driver modules
 * @{
 */

/**
 * @addtogroup as5600_base_driver
 * @{
 */

/**
 * @brief as5600 bool enumeration definition
 */
typedef enum
{
    AS5600_BOOL_FALSE = 0x00,        /**< disable */
    AS5600_BOOL_TRUE  = 0x01,        /**< enable */
} as5600_bool_t;

/**
 * @brief as5600 power mode enumeration definition
 */
typedef enum
{
    AS5600_POWER_MODE_NOM  = 0x00,        /**< normal */
    AS5600_POWER_MODE_LPM1 = 0x01,        /**< low power 1 */
    AS5600_POWER_MODE_LPM2 = 0x02,        /**< low power 2 */
    AS5600_POWER_MODE_LPM3 = 0x03,        /**< low power 3 */
} as5600_power_mode_t;

/**
 * @brief as5600 hysteresis enumeration definition
 */
typedef enum
{
    AS5600_HYSTERESIS_OFF  = 0x00,        /**< off */
    AS5600_HYSTERESIS_1LSB = 0x01,        /**< 1 lsb */
    AS5600_HYSTERESIS_2LSB = 0x02,        /**< 2 lsb */
    AS5600_HYSTERESIS_3LSB = 0x03,        /**< 3 lsb */
} as5600_hysteresis_t;

/**
 * @brief as5600 output stage enumeration definition
 */
typedef enum
{
    AS5600_OUTPUT_STAGE_ANALOG_FULL    = 0x00,        /**< full range from 0% to 100% between gnd and vdd */
    AS5600_OUTPUT_STAGE_ANALOG_REDUCED = 0x01,        /**< reduced range from 10% to 90% between gnd and vdd */
    AS5600_OUTPUT_STAGE_PWM            = 0x02,        /**< digital pwm */
} as5600_output_stage_t;

/**
 * @brief as5600 pwm frequency enumeration definition
 */
typedef enum
{
    AS5600_PWM_FREQUENCY_115HZ = 0x00,        /**< 115Hz */
    AS5600_PWM_FREQUENCY_230HZ = 0x01,        /**< 230Hz */
    AS5600_PWM_FREQUENCY_460HZ = 0x02,        /**< 460Hz */
    AS5600_PWM_FREQUENCY_920HZ = 0x03,        /**< 920Hz */
} as5600_pwm_frequency_t;

/**
 * @brief as5600 slow filter enumeration definition
 */
typedef enum
{
    AS5600_SLOW_FILTER_16X = 0x00,        /**< 16x */
    AS5600_SLOW_FILTER_8X  = 0x01,        /**< 8x */
    AS5600_SLOW_FILTER_4X  = 0x02,        /**< 4x */
    AS5600_SLOW_FILTER_2X  = 0x03,        /**< 2x */
} as5600_slow_filter_t;

/**
 * @brief as5600 fast filter threshold enumeration definition
 */
typedef enum
{
    AS5600_FAST_FILTER_THRESHOLD_SLOW_FILTER_ONLY = 0x00,        /**< slow filter only */
    AS5600_FAST_FILTER_THRESHOLD_6LSB             = 0x01,        /**< 6 lsb */
    AS5600_FAST_FILTER_THRESHOLD_7LSB             = 0x02,        /**< 7 lsb */
    AS5600_FAST_FILTER_THRESHOLD_9LSB             = 0x03,        /**< 9 lsb */
    AS5600_FAST_FILTER_THRESHOLD_10LSB            = 0x07,        /**< 10 lsb */
    AS5600_FAST_FILTER_THRESHOLD_18LSB            = 0x04,        /**< 18 lsb */
    AS5600_FAST_FILTER_THRESHOLD_21LSB            = 0x05,        /**< 21 lsb */
    AS5600_FAST_FILTER_THRESHOLD_24LSB            = 0x06,        /**< 24 lsb */
} as5600_fast_filter_threshold_t;

/**
 * @brief as5600 status enumeration definition
 */
typedef enum
{
    AS5600_STATUS_MD = (1 << 5),        /**< agc minimum gain overflow, magnet too strong */
    AS5600_STATUS_ML = (1 << 4),        /**< agc maximum gain overflow, magnet too weak */
    AS5600_STATUS_MH = (1 << 3),        /**< magnet was detected */
} as5600_status_t;

/**
 * @brief as5600 burn enumeration definition
 */
typedef enum
{
    AS5600_BURN_CMD1    = 0x01,        /**< load the actual otp content command 1 */
    AS5600_BURN_CMD2    = 0x11,        /**< load the actual otp content command 2 */
    AS5600_BURN_CMD3    = 0x10,        /**< load the actual otp content command 3 */
    AS5600_BURN_ANGLE   = 0x80,        /**< angle */
    AS5600_BURN_SETTING = 0x40,        /**< setting */
} as5600_burn_t;

/**
 * @brief as5600 handle structure definition
 */
typedef struct as5600_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} as5600_handle_t;

/**
 * @brief as5600 information structure definition
 */
typedef struct as5600_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} as5600_info_t;

/**
 * @}
 */

/**
 * @defgroup as5600_link_driver as5600 link driver function
 * @brief    as5600 link driver modules
 * @ingroup  as5600_driver
 * @{
 */

/**
 * @brief     initialize as5600_handle_t structure
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] STRUCTURE is as5600_handle_t
 * @note      none
 */
#define DRIVER_AS5600_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_AS5600_LINK_IIC_INIT(HANDLE, FUC)             (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_AS5600_LINK_IIC_DEINIT(HANDLE, FUC)           (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_AS5600_LINK_IIC_READ(HANDLE, FUC)             (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_AS5600_LINK_IIC_WRITE(HANDLE, FUC)            (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_AS5600_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an as5600 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_AS5600_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup as5600_base_driver as5600 base driver function
 * @brief    as5600 base driver modules
 * @ingroup  as5600_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an as5600 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t as5600_info(as5600_info_t *info);

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
uint8_t as5600_init(as5600_handle_t *handle);

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
uint8_t as5600_deinit(as5600_handle_t *handle);

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
uint8_t as5600_read(as5600_handle_t *handle, uint16_t *angle_raw, float *deg);

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
uint8_t as5600_angle_convert_to_register(as5600_handle_t *handle, float deg, uint16_t *reg);

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
uint8_t as5600_angle_convert_to_data(as5600_handle_t *handle, uint16_t reg, float *deg);

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
uint8_t as5600_set_start_position(as5600_handle_t *handle, uint16_t pos);

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
uint8_t as5600_get_start_position(as5600_handle_t *handle, uint16_t *pos);

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
uint8_t as5600_set_stop_position(as5600_handle_t *handle, uint16_t pos);

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
uint8_t as5600_get_stop_position(as5600_handle_t *handle, uint16_t *pos);

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
uint8_t as5600_set_max_angle(as5600_handle_t *handle, uint16_t ang);

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
uint8_t as5600_get_max_angle(as5600_handle_t *handle, uint16_t *ang);

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
uint8_t as5600_set_watch_dog(as5600_handle_t *handle, as5600_bool_t enable);

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
uint8_t as5600_get_watch_dog(as5600_handle_t *handle, as5600_bool_t *enable);

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
uint8_t as5600_set_fast_filter_threshold(as5600_handle_t *handle, as5600_fast_filter_threshold_t threshold);

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
uint8_t as5600_get_fast_filter_threshold(as5600_handle_t *handle, as5600_fast_filter_threshold_t *threshold);

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
uint8_t as5600_set_slow_filter(as5600_handle_t *handle, as5600_slow_filter_t filter);

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
uint8_t as5600_get_slow_filter(as5600_handle_t *handle, as5600_slow_filter_t *filter);

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
uint8_t as5600_set_pwm_frequency(as5600_handle_t *handle, as5600_pwm_frequency_t freq);

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
uint8_t as5600_get_pwm_frequency(as5600_handle_t *handle, as5600_pwm_frequency_t *freq);

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
uint8_t as5600_set_output_stage(as5600_handle_t *handle, as5600_output_stage_t stage);

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
uint8_t as5600_get_output_stage(as5600_handle_t *handle, as5600_output_stage_t *stage);

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
uint8_t as5600_set_hysteresis(as5600_handle_t *handle, as5600_hysteresis_t hysteresis);

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
uint8_t as5600_get_hysteresis(as5600_handle_t *handle, as5600_hysteresis_t *hysteresis);

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
uint8_t as5600_set_power_mode(as5600_handle_t *handle, as5600_power_mode_t mode);

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
uint8_t as5600_get_power_mode(as5600_handle_t *handle, as5600_power_mode_t *mode);

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
uint8_t as5600_get_raw_angle(as5600_handle_t *handle, uint16_t *ang);

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
uint8_t as5600_get_angle(as5600_handle_t *handle, uint16_t *ang);

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
uint8_t as5600_get_status(as5600_handle_t *handle, uint8_t *status);

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
uint8_t as5600_get_agc(as5600_handle_t *handle, uint8_t *agc);

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
uint8_t as5600_get_magnitude(as5600_handle_t *handle, uint16_t *magnitude);

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
uint8_t as5600_set_burn(as5600_handle_t *handle, as5600_burn_t burn);

/**
 * @}
 */

/**
 * @defgroup as5600_extend_driver as5600 extend driver function
 * @brief    as5600 extend driver modules
 * @ingroup  as5600_driver
 * @{
 */

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
uint8_t as5600_set_reg(as5600_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

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
uint8_t as5600_get_reg(as5600_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
