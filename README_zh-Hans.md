[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AS5600

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/as5600/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AS5600是一种易于编程的磁性旋转位置传感器，具有高分辨率12位输出、模拟输出或PWM输出。该非接触系统可以测量轴上径向磁化磁体的绝对角度。AS5600专为无触点电位器应用而设计，其坚固的设计消除了任何均匀外部干扰磁场的影响。行业标准I²C接口支持非易失性参数的简单用户编程，无需专门的程序员。默认情况下，输出表示0到360度的范围。也可以通过编程零角度（开始位置）和最大角度（停止位置）来定义输出的较小范围。AS5600还配备了智能低功耗模式功能，可自动降低功耗。输入引脚（DIR）选择输出相对于旋转方向的极性。如果DIR接地，输出值随顺时针旋转而增加。如果DIR连接到VDD，则输出值随逆时针旋转而增加。

LibDriver AS5600是LibDriver推出的AS5600全功能驱动，该驱动提供磁角度读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver AS5600的源文件。

/interface目录包含了LibDriver AS5600与平台无关的IIC总线模板。

/test目录包含了LibDriver AS5600驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver AS5600编程范例。

/doc目录包含了LibDriver AS5600离线文档。

/datasheet目录包含了AS5600数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_as5600_basic.h"

uint8_t res;
uint32_t i;
uint32_t times;

/* basic init */
res = as5600_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* get the times */
times = 10;

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
    as5600_interface_debug_print("as5600: angle is %.2f.\n", deg);

    /* delay 1000ms */
    as5600_interface_delay_ms(1000);
    
    ...
}

...
    
/* deinit */
(void)as5600_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/as5600/index.html](https://www.libdriver.com/docs/as5600/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。