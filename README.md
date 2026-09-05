# ImageProcessor

24비트 BMP 이미지에 여러 필터를 적용하는 CLI 프로그램입니다. C++ STL만 사용하여 제작되었습니다.

## 개발 환경
- C++17
- Visual Studio 2022
- Windows 11

## 구현 항목

| 기능 | 필터 형식 | 설명 |
| --- | --- | --- |
| 그레이스케일 | `grayscale` | RGB 채널을 밝기값으로 변환합니다. |
| 밝기 조정 | `brightness:<offset>` | 각 채널에 밝기 변화량을 더하고 0~255 범위로 제한합니다. |
| 대비 조정 | `contrast:<amount>` | 중간값을 기준으로 채널의 대비를 조정합니다. |
| 이진화 | `threshold:<value>` | 밝기값을 임계값과 비교하여 흑백으로 변환합니다. |
| 흐림 | `blur` | 3×3 Blur 커널로 합성곱 연산을 수행합니다. |
| 선명화 | `sharpen` | 3×3 Sharpen 커널로 합성곱 연산을 수행합니다. |
| 히스토그램 | `histogram` | RGB·밝기 히스토그램 표와 분포 그래프를 콘솔에 출력합니다. |
| 자르기 | `crop:<x>:<y>:<width>:<height>` | 지정한 시작 좌표와 크기에 맞게 이미지를 자릅니다. |
| 좌우 반전 | `flip:horizontal` | 이미지의 좌우를 반전합니다. |
| 상하 반전 | `flip:vertical` | 이미지의 상하를 반전합니다. |
| 크기 변경 | `resize:<width>:<height>` | 픽셀 중심 기준의 양선형 보간으로 크기를 변경합니다. |
| 파이프라인 | `--pipeline "<filter1>,<filter2>,..."` | 여러 필터를 작성한 순서대로 적용합니다. |
| 멀티스레드 처리 | `--thread <count>` | 이미지의 행 범위를 나누어 지정한 수의 작업 스레드로 병렬 처리합니다. 기본값은 1입니다. |
| 로그 파일 출력 | `--log <path>` | 필터명, 마이크로초 단위 처리 시간과 성공 또는 실패 여부를 파일에 추가 기록합니다. |

## 기본 사용법

모든 명령은 저장소 루트에서 실행하며, 실행 파일은 `x64/Release`에 있습니다.

```powershell
.\x64\Release\ImageProcessor.exe --input <입력 BMP> --output <출력 BMP> (--filter <필터> | --pipeline <필터 목록>) [--thread <개수>] [--log <로그 경로>]
```

| 옵션 | 단축 옵션 | 필수 여부 | 설명 |
| --- | --- | --- | --- |
| `--input <path>` | `-i` | 필수 | 입력 BMP 경로입니다. |
| `--output <path>` | `-o` | 필수 | 출력 BMP 경로입니다. |
| `--filter <filter>` | `-f` | 조건부 필수 | 단일 필터를 지정합니다. |
| `--pipeline <filters>` | `-p` | 조건부 필수 | 쉼표로 구분한 필터 목록을 지정합니다. |
| `--thread <count>` | `-t` | 선택 | 작업 스레드 수입니다. 기본값은 1입니다. |
| `--log <path>` | `-l` | 선택 | 처리 결과를 추가 기록할 로그 파일입니다. |
| `--help` | `-h` | 선택 | 사용법을 출력합니다. |


## 실행 명령어

출력 파일의 부모 디렉터리는 미리 생성되어 있어야 합니다. 존재하지 않는 디렉터리를 출력 경로로 지정하면 오류가 발생하며 프로그램이 종료됩니다.

### 그레이스케일

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\output\astronaut_grayscale.bmp --filter grayscale
```

### 밝기 조정

밝기 변화량 `50`을 각 채널에 적용합니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\output\coffee_brightness.bmp --filter brightness:50
```

### 대비 조정

대비 변화량 `50`을 적용합니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\output\cat_contrast.bmp --filter contrast:50
```

### 이진화

밝기 임계값 `128`을 적용합니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\output\astronaut_threshold.bmp --filter threshold:128
```

### 흐림

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\4_text_page.bmp --output .\output\text_blur.bmp --filter blur
```

### 선명화

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\4_text_page.bmp --output .\output\text_sharpen.bmp --filter sharpen
```

### 히스토그램 분석

RGB·밝기별 원시 히스토그램 표와 공통 축척을 적용한 분포 그래프가 콘솔에 출력됩니다. 필터가 픽셀을 변경하지 않으므로 출력 BMP는 입력 이미지와 같습니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\5_checkerboard.bmp --output .\output\checkerboard_histogram.bmp --filter histogram
```

### 이미지 자르기

`(10, 20)`을 시작점으로 너비 200, 높이 150인 영역을 자릅니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\output\astronaut_crop.bmp --filter crop:10:20:200:150
```

### 좌우 반전

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\output\cat_flip_horizontal.bmp --filter flip:horizontal
```

### 상하 반전

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\output\cat_flip_vertical.bmp --filter flip:vertical
```

### 이미지 크기 변경

출력 이미지의 크기를 160×120으로 변경합니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\4_text_page.bmp --output .\output\text_resize.bmp --filter resize:160:120
```

### 필터 파이프라인

필터 이름 사이에 공백을 넣지 않습니다. 다음 명령은 그레이스케일, 흐림, 이진화를 순서대로 적용합니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\4_text_page.bmp --output .\output\text_pipeline.bmp --pipeline "grayscale,blur,threshold:128"
```

### 멀티스레드 처리

`--thread 4`로 작업 스레드 수를 4개로 지정합니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\4_text_page.bmp --output .\output\text_blur_thread4.bmp --filter blur --thread 4
```

### 로그 파일 출력

로그 파일에는 필터 문자열, 마이크로초 단위 처리 시간과 `SUCCESS` 또는 `FAILURE` 상태가 기록됩니다.

```powershell
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\output\astronaut_logged.bmp --filter grayscale --log .\output\processing.log
```
