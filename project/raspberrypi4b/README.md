### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(as5600 REQUIRED)
```


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
./as5600 -i

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
./as5600 -p

as5600: SCL connected to GPIO3(BCM).
as5600: SDA connected to GPIO2(BCM).
```

```shell
./as5600 -t reg

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
as5600: set start position 3718.
as5600: check start position ok.
as5600: as5600_set_stop_position/as5600_get_stop_position test.
as5600: set stop position 2986.
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
as5600: get raw angle 1992.
as5600: as5600_get_angle test.
as5600: get angle 2370.
as5600: as5600_get_status test.
as5600: get status 0xA7.
as5600: as5600_get_agc test.
as5600: get agc 0xD6.
as5600: as5600_get_magnitude test.
as5600: get magnitude 2059.
as5600: as5600_angle_convert_to_register/as5600_angle_convert_to_data test.
as5600: set angle 2477.70.
as5600: check angle 2477.64.
as5600: finish register test.
```

```shell
./as5600 -t read --times=10

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
as5600: angle is 175.08 and raw angle is 1992.
as5600: angle is 175.08 and raw angle is 1992.
as5600: angle is 137.90 and raw angle is 1569.
as5600: angle is 123.75 and raw angle is 1408.
as5600: angle is 100.02 and raw angle is 1138.
as5600: angle is 79.72 and raw angle is 907.
as5600: angle is 35.24 and raw angle is 401.
as5600: angle is 350.68 and raw angle is 3990.
as5600: angle is 313.42 and raw angle is 3566.
as5600: angle is 276.77 and raw angle is 3149.
as5600: finish read test.
```

```shell
./as5600 -e read --times=10

as5600: 1/10.
as5600: angle is 220.87.
as5600: 2/10.
as5600: angle is 220.78.
as5600: 3/10.
as5600: angle is 179.56.
as5600: 4/10.
as5600: angle is 151.61.
as5600: 5/10.
as5600: angle is 123.66.
as5600: 6/10.
as5600: angle is 109.69.
as5600: 7/10.
as5600: angle is 79.28.
as5600: 8/10.
as5600: angle is 49.83.
as5600: 9/10.
as5600: angle is 20.48.
as5600: 10/10.
as5600: angle is 350.26.
```

```shell
./as5600 -h

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

