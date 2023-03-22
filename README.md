# MindChallenge-Example
This example code is for the MindChallenge arduino board created by MindRoad and Wolfram Mathcore. It utelizes a Arduino Nano (ATMega328P, old bootloader) as main controll card with a Adafruit SSD1306 OLED, AHT10 Temperature and air humidity sensor and a BMI160 Gyro and accelerometer, all connected via I2C. In additon the card also sports two momentary buttons.

## Setup and necessary downloads

1. Open Aruino IDE

2. Download libraries (Tools -> Manage Libraries)
    - Adafruit Graphics Library: Adafruit GFX Library by Adafruit
    - Display driver: Adafruit SSD1306
    - Temp and humidity sensor driver: Thinary_AHT10 (Not in the library index. Zip file from here: <a href="https://github.com/Thinary/AHT10">https://github.com/Thinary/AHT10</a> You can link this library by going to Sketch -> Include Library -> Add .ZIP Library)
    - Button debouncing: Bounce2 by Thomas O Fredericks
    - Gyro and accelerometer driver: SparkFunLSM6DS3 (Not in the library index. Zip file from here: <a href="https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library">https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library</a> You can link this library by going to Sketch -> Include Library -> Add .ZIP Library)

3. Open the MindChallenge.ino file in the Arduino IDE

4. Check if the Board, Processor and Port are selected correctly in Tools menu.
	- Board: Arduino Nano
	- Processor:ATmega328P (Old Bootloader)
	- Select the port which says Ardunio Nano

5. Upload the file to Arduino Nano

6. If everything went well, the OLED should display Temperature and humidity data.

7. Press the buttons to move between showing different sensor output (displayed in OLED)
