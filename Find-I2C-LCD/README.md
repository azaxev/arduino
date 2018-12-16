PCF8574/PCF8574A character LCD (SPLC780/HD44780) seeker.

Arduino IDE 1.8.5, Windows 7

Various models of I2C chips have different address and this sketch helps find them. It initializes all known addresses and prints the corresponding address on the LCD.

The LCD keeps continuously refreshing, so this sketch supports hot-swap and can be used as I2C LCD tester.