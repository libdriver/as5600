[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AS5600

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/as5600/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AS5600은 고해상도 12비트 아날로그 또는 PWM 출력으로 프로그래밍하기 쉬운 자기 회전 위치 센서입니다. 이 비접촉식 시스템은 직경의 자화된 축상 자석의 절대 각도를 측정합니다. 이 AS5600은 비접촉식 전위차계 애플리케이션을 위해 설계되었으며 견고한 설계로 균질한 외부 표유 자기장의 영향을 제거합니다. 산업 표준 I²C 인터페이스는 전용 프로그래머 없이도 비휘발성 매개변수의 간단한 사용자 프로그래밍을 지원합니다. 기본적으로 출력은 다음을 나타냅니다. 범위는 0 ~ 360도입니다. 0 각도(시작 위치)와 최대 각도(정지 위치)를 프로그래밍하여 출력에 더 작은 범위를 정의할 수도 있습니다. AS5600에는 스마트 저전력 모드 기능도 탑재되어 있어 자동으로 전력 소비를 줄입니다. 입력 핀(DIR)은 회전 방향과 관련하여 출력의 극성을 선택합니다. DIR이 접지에 연결되면 시계 방향으로 회전함에 따라 출력 값이 증가합니다. DIR을 VDD에 연결하면 시계 반대 방향으로 회전하면 출력 값이 증가합니다.

LibDriver AS5600은 LibDriver에서 출시한 AS5600 전체 기능 드라이버입니다. 자기 각도 판독 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver AS5600의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver AS5600용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver AS5600드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver AS5600프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver AS5600오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 AS5600데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/as5600/index.html](https://www.libdriver.com/docs/as5600/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.