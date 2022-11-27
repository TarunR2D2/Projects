#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
int sensorValue1;
int sensorValue2;
int RED = 7;
int GRN = 6;
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000); // wait for initializing
  oled.setCursor(0, 0);
}


void loop(){
  sensorValue1 = analogRead(3);
  sensorValue2 = analogRead(1);
//  sensorValue1 = digitalRead(0);
//  sensorValue2 = digitalRead(2);
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextSize(2);
  oled.setCursor(0, 0);
  oled.println("CO2 in PPM");
  oled.setCursor(5, 20);
  oled.println("In : ");
  oled.setCursor(55, 20);
  oled.print(sensorValue1, DEC);
  oled.setCursor(5, 40);
  oled.println("Out: ");
  oled.setCursor(55, 40);
  oled.print(sensorValue2, DEC);
  oled.display();
  delay(2000);  
  
  if (abs(sensorValue1 - sensorValue2) <= 25){
    digitalWrite(RED, HIGH);
    digitalWrite(GRN, LOW);
    
//    oled.setCursor(0, 0);
//    oled.setTextColor(SSD1306_WHITE);
//    oled.println("ATTENTION! CARTRIDGE FULL");
    
  }
  else {
    digitalWrite(GRN, HIGH);
    digitalWrite(RED, LOW);
       }
}
