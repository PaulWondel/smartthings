# smartthings
Files for the Minor 'Smart Things'

|   ST7920    | ESP8266 |
|-------------|---------|
|   GND (pin 1) |   Ground (G)  |
|   VCC     |   5V  |
|   RS    |   SS - D8 - GPIO 15   |
|   R/W	|   MOSI - D7 - GPIO 13 |
|   E	    |   SCK -  D5 - GPIO 14 |
|   PSB   |   Ground (to enable SPI MODE)
|   BLA (Backlight Anode) |   3V (consumes 12 mA) or 5V (60 mA)   |
|   BLC (Backlight Cathode)   |   Ground  |

```
U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0,D8);
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* E=*/ 14, /* R/W=*/ 13, /* RS=*/ 15);
```