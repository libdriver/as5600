[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AS5600

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/as5600/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AS5600是一種易於程式設計的磁性旋轉位置感測器，具有高解析度12比特輸出、類比輸出或PWM輸出。 該非接觸系統可以量測軸上徑向磁化磁體的絕對角度。 AS5600專為無觸點電位器應用而設計，其堅固的設計消除了任何均勻外部干擾磁場的影響。 行業標準I²C介面支持非易失性參數的簡單用戶程式設計，無需專門的程式師。 默認情况下，輸出表示0到360度的範圍。 也可以通過程式設計零角度（開始位置）和最大角度（停止位置）來定義輸出的較小範圍。 AS5600還配備了智慧低功耗模式功能，可自動降低功耗。 輸入引脚（DIR）選擇輸出相對於旋轉方向的極性。 如果DIR接地，輸出值隨順時針旋轉而新增。 如果DIR連接到VDD，則輸出值隨逆時針旋轉而新增。

LibDriver AS5600是LibDriver推出的AS5600全功能驅動，該驅動提供磁角度讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver AS5600的源文件。

/interface目錄包含了LibDriver AS5600與平台無關的IIC總線模板。

/test目錄包含了LibDriver AS5600驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver AS5600編程範例。

/doc目錄包含了LibDriver AS5600離線文檔。

/datasheet目錄包含了AS5600數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/as5600/index.html](https://www.libdriver.com/docs/as5600/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。