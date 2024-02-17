[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AS5600

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/as5600/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AS5600 は、高解像度の 12 ビット アナログまたは PWM 出力を備えた、プログラムが簡単な磁気回転位置センサーです。この非接触システムは、直径方向に磁化された軸上の磁石の絶対角度を測定します。この AS5600 は、非接触ポテンショメータ アプリケーション用に設計されており、その堅牢な設計により、均一な外部漂遊磁場の影響が排除されます。業界標準の I²C インターフェイスは、専用のプログラマを必要とせずに、不揮発性パラメータの簡単なユーザ プログラミングをサポートします。デフォルトでは、出力はゼロ角度 (開始位置) と最大角度 (停止位置) をプログラミングすることにより、出力の範囲を狭く定義することもできます。AS5600 には、スマートな低電力モード機能も装備されています。入力ピン (DIR) は、回転方向に関して出力の極性を選択します。 DIR がグランドに接続されている場合、出力値は時計回りに増加します。 DIR を VDD に接続すると、反時計回りで出力値が増加します。

LibDriver AS5600 は、LibDriver が起動する AS5600 フル機能ドライバです。磁気角度の読み取りなどの機能を提供します。 LibDriver は MISRA 準拠です。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AS5600のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AS5600用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AS5600ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AS5600プログラミング例が含まれています。

/ docディレクトリには、LibDriver AS5600オフラインドキュメントが含まれています。

/ datasheetディレクトリには、AS5600データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/as5600/index.html](https://www.libdriver.com/docs/as5600/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。