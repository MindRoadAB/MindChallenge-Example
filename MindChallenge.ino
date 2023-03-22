/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Thinary_AHT10.h>
#include <Bounce2.h>
#include <SparkFunLSM6DS3.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

AHT10Class AHT10;

LSM6DS3 myIMU; 


Bounce button1 = Bounce(); 

Bounce button2 = Bounce(); 

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

Wire.begin();
  if(AHT10.begin(eAHT10Address_Low))
    Serial.println("Init AHT10 Sucess.");
  else
    Serial.println("Init AHT10 Failure.");
 myIMU.settings.gyroEnabled = 0;
 myIMU.begin();

  // Setup the first button with an internal pull-up :
  pinMode(4,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  button1.attach(4);
  button1.interval(100); // interval in ms


  // Setup the first button with an internal pull-up :
  pinMode(5,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  button2.attach(5);
  button2.interval(100); // interval in ms

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.display();
}

void writeString(char* text) {
  char* c = text;
  while(*c) { 
    display.write(*c);
    c++;
  }
}

void writeFloatString(float n) {
  char buffer[128];
  dtostrf(n, 4, 2, buffer);
  writeString(buffer);
}

void loop() {

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  int count = 0;

  #define NUMBER_OF_STATES 2
  int state = 0;



  while(1) {

    button1.update();
    button2.update();

    if(button1.fell()) {
      state = state + 1;
      if(state >= NUMBER_OF_STATES)
        state = NUMBER_OF_STATES - 1;          
       Serial.println(state);
      
    }

    if(button2.fell()) {
      state = state - 1; 
      if(state <  0)
         state = 0;
       Serial.println(state);
    }

    if(count == 0) {
      display.clearDisplay();
      display.setCursor(0, 0);
      
            
      switch(state) {
        case 0: {
        float temperature = AHT10.GetTemperature();   
        writeString("TEMPERATURE = ");
        writeFloatString(temperature);

         display.setCursor(0, 12);
        
        float humidity =AHT10.GetHumidity();
        writeString("HUMIDITY = ");
        writeFloatString(humidity);
      };
      break;
      
      case 1: {  
        float x = myIMU.readFloatAccelX();
        writeString("aX = ");
        writeFloatString(x);
        
        display.setCursor(0, 12);
        float y = myIMU.readFloatAccelY();
        writeString("aY = ");
        writeFloatString(y);
        
        display.setCursor(0, 24);
        float z = myIMU.readFloatAccelZ();
        writeString("aZ = ");
        writeFloatString(z);
      };
      break;
      case 2: {  
        float x = myIMU.readFloatGyroX();
        writeString("gX = ");
        writeFloatString(x);
        
        display.setCursor(0, 12);
        float y = myIMU.readFloatGyroY();
        writeString("gY = ");
        writeFloatString(y);
        
        display.setCursor(0, 24);
        float z = myIMU.readFloatGyroZ();
        writeString("gZ = ");
        writeFloatString(z);
      };
      break;
      }
      
      display.display();        
    } 
    count = (count + 1) % 1000;;
    
  }

}
