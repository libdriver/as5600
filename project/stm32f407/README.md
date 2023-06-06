### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AS5600

#### 3.1 Command Instruction

1. Show as5600 chip and driver information.

   ```shell
   as5600 (-i | --information)
   ```

2. Show as5600 help.

   ```shell
   as5600 (-h | --help)
   ```

3. Show as5600 pin connections of the current board.

   ```shell
   as5600 (-p | --port)
   ```

4. Run as5600 register test. 

   ```shell
   as5600 (-t reg | --test=reg) 
   ```

5. Run as5600 read test, num is test times.

   ```shell
   as5600 (-t read | --test=read) [--times=<num>]
   ```

6. Run as5600 read function, num is the read times.

   ```shell
   as5600 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
as5600 -i

as5600: chip is AMS AS5600.
as5600: manufacturer is AMS.
as5600: interface is IIC.
as5600: driver version is 1.0.
as5600: min supply voltage is 4.5V.
as5600: max supply voltage is 5.5V.
as5600: max current is 100.00mA.
as5600: max temperature is 125.0C.
as5600: min temperature is -40.0C.
```

```shell
as5600 -p

as5600: SCL connected to GPIOB PIN8.
as5600: SDA connected to GPIOB PIN9.
```

```shell
as5600 -t reg

as5600: chip is AMS AS5600.
as5600: manufacturer is AMS.
as5600: interface is IIC.
as5600: driver version is 1.0.
as5600: min supply voltage is 4.5V.
as5600: max supply voltage is 5.5V.
as5600: max current is 100.00mA.
as5600: max temperature is 125.0C.
as5600: min temperature is -40.0C.
as5600: start register test.
as5600: as5600_set_start_position/as5600_get_start_position test.
as5600: set start position 1408.
as5600: check start position ok.
as5600: as5600_set_stop_position/as5600_get_stop_position test.
as5600: set stop position 2622.
as5600: check stop position ok.
as5600: as5600_set_max_angle/as5600_get_max_angle test.
as5600: set max angle 0.
as5600: check max angle ok.
as5600: as5600_set_watch_dog/as5600_get_watch_dog test.
as5600: enable watch dog.
as5600: check watch dog ok.
as5600: disable watch dog.
as5600: check watch dog ok.
as5600: as5600_set_fast_filter_threshold/as5600_get_fast_filter_threshold test.
as5600: set fast filter threshold slow filter only.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 6 lsb.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 7 lsb.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 9 lsb.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 10 lsb.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 18 lsb.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 21 lsb.
as5600: check fast filter threshold ok.
as5600: set fast filter threshold 24 lsb.
as5600: check fast filter threshold ok.
as5600: as5600_set_slow_filter/as5600_get_slow_filter test.
as5600: set slow filter 16X.
as5600: check slow filter ok.
as5600: set slow filter 8X.
as5600: check slow filter ok.
as5600: set slow filter 4X.
as5600: check slow filter ok.
as5600: set slow filter 2X.
as5600: check slow filter ok.
as5600: as5600_set_pwm_frequency/as5600_get_pwm_frequency test.
as5600: set pwm frequency 115Hz.
as5600: check pwm frequency ok.
as5600: set pwm frequency 230Hz.
as5600: check pwm frequency ok.
as5600: set pwm frequency 460Hz.
as5600: check pwm frequency ok.
as5600: set pwm frequency 920Hz.
as5600: check pwm frequency ok.
as5600: as5600_set_output_stage/as5600_get_output_stage test.
as5600: set output stage full range.
as5600: check output stage ok.
as5600: set output stage reduced.
as5600: check output stage ok.
as5600: set output stage digital pwm.
as5600: check output stage ok.
as5600: as5600_set_hysteresis/as5600_get_hysteresis test.
as5600: set hysteresis off.
as5600: check hysteresis ok.
as5600: set hysteresis 1 lsb.
as5600: check hysteresis ok.
as5600: set hysteresis 2 lsb.
as5600: check hysteresis ok.
as5600: set hysteresis 3 lsb.
as5600: check hysteresis ok.
as5600: as5600_set_power_mode/as5600_get_power_mode test.
as5600: set power mode nom.
as5600: check hysteresis ok.
as5600: set power mode lpm1.
as5600: check hysteresis ok.
as5600: set power mode lpm2.
as5600: check hysteresis ok.
as5600: set power mode lpm3.
as5600: check hysteresis ok.
as5600: as5600_get_raw_angle test.
as5600: get raw angle 3405.
as5600: as5600_get_angle test.
as5600: get angle 1998.
as5600: as5600_get_status test.
as5600: get status 0xA7.
as5600: as5600_get_agc test.
as5600: get agc 0xC4.
as5600: as5600_get_magnitude test.
as5600: get magnitude 2064.
as5600: as5600_angle_convert_to_register/as5600_angle_convert_to_data test.
as5600: set angle 1840.90.
as5600: check angle 1840.87.
as5600: finish register test.
```

```shell
as5600 -t read --times=10

as5600: chip is AMS AS5600.
as5600: manufacturer is AMS.
as5600: interface is IIC.
as5600: driver version is 1.0.
as5600: min supply voltage is 4.5V.
as5600: max supply voltage is 5.5V.
as5600: max current is 100.00mA.
as5600: max temperature is 125.0C.
as5600: min temperature is -40.0C.
as5600: start read test.
as5600: angle is 72.33 and raw angle is 823.
as5600: angle is 72.33 and raw angle is 823.
as5600: angle is 57.22 and raw angle is 651.
as5600: angle is 35.33 and raw angle is 402.
as5600: angle is 349.80 and raw angle is 3980.
as5600: angle is 349.80 and raw angle is 3980.
as5600: angle is 327.39 and raw angle is 3725.
as5600: angle is 283.89 and raw angle is 3230.
as5600: angle is 262.27 and raw angle is 2984.
as5600: angle is 227.20 and raw angle is 2585.
as5600: finish read test.
```

```shell
as5600 -e read --times=10

as5600: 1/10.
as5600: angle is 180.18.
as5600: 2/10.
as5600: angle is 151.70.
as5600: 3/10.
as5600: angle is 126.10.
as5600: 4/10.
as5600: angle is 96.83.
as5600: 5/10.
as5600: angle is 25.84.
as5600: 6/10.
as5600: angle is 342.77.
as5600: 7/10.
as5600: angle is 335.39.
as5600: 8/10.
as5600: angle is 312.01.
as5600: 9/10.
as5600: angle is 298.83.
as5600: 10/10.
as5600: angle is 260.91.
```

```shell
as5600 -h

Usage:
  as5600 (-i | --information)
  as5600 (-h | --help)
  as5600 (-p | --port)
  as5600 (-t reg | --test=reg)
  as5600 (-t read | --test=read) [--times=<num>]
  as5600 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>             Run the driver example.
  -h, --help                              Show the help.
  -i, --information                       Show the chip information.
  -p, --port                              Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>    Run the driver test.
      --times=<num>                       Set the running times.([default: 3])

```

