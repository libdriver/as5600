[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AS5600

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/as5600/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der AS5600 ist ein einfach zu programmierender magnetischer Drehpositionssensor mit einem hochauflösenden 12-Bit-Analog- oder PWM-Ausgang. Dieses berührungslose System misst den absoluten Winkel eines diametral magnetisierten axialen Magneten. Dieser AS5600 wurde für kontaktlose Potentiometer-Anwendungen entwickelt und sein robustes Design eliminiert den Einfluss von homogenen externen magnetischen Streufeldern Bereich von 0 bis 360 Grad. Es ist auch möglich, einen kleineren Bereich für den Ausgang zu definieren, indem Sie einen Nullwinkel (Startposition) und einen maximalen Winkel (Stoppposition) programmieren. Der AS5600 ist auch mit einer intelligenten Energiesparmodusfunktion ausgestattet automatisch den Stromverbrauch reduzieren. Ein Eingangspin (DIR) wählt die Polarität des Ausgangs in Bezug auf die Drehrichtung. Wird DIR mit Masse verbunden, steigt der Ausgangswert bei Rechtsdrehung. Wird DIR mit VDD verbunden, steigt der Ausgangswert bei Linksdrehung.

LibDriver AS5600 ist der voll funktionsfähige AS5600-Treiber, der von LibDriver gestartet wurde. Er bietet das Lesen des Magnetwinkels und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver AS5600-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver AS5600 IIC.

/test enthält den Testcode des LibDriver AS5600-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver AS5600-Beispielcode.

/doc enthält das LibDriver AS5600-Offlinedokument.

/Datenblatt enthält AS5600-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/as5600/index.html](https://www.libdriver.com/docs/as5600/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.