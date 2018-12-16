//
// Continuously initialize PCF8574/8574A LCD on all available addresses.
// Should work with TI and NXP parts.
// http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf
//

#include <Wire.h> 
#include "src/LiquidCrystal_I2C1602V1/LiquidCrystal_I2C.h"

word count = 0;
byte addr7 = 0x20; // 7-bit address without R/_W

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println(addr7, HEX);

    LiquidCrystal_I2C lcd(addr7,16,2);
    lcd.init(); // initialize the lcd 
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
    lcd.setCursor(0, 1);
    lcd.print("addr7=0x");
    lcd.setCursor(8, 1);
    lcd.print(addr7, HEX);

    lcd.backlight();
    lcd.setCursor(11, 1);
    lcd.print(count);
    lcd.print("    ");
    delay(20);

    count ++;

    ++ addr7;
    if(addr7 == 0x28)
        addr7 = 0x38;
    if(addr7 == 0x40)
        addr7 = 0x20;   
}