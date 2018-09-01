#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for #include "SSD1306Wire.h
#include <Adafruit_ADS1015.h> //https://github.com/soligen2010/Adafruit_ADS1X15

Adafruit_ADS1015 ads(0x48); //Connect Address pin to GND to get address 0x48
//Sensor connected to 5 (SDA), 4 (SCL)
float V0 = 0.0;
float V1 = 0.0;
float V2 = 0.0;
float V3 = 0.0;
// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5, 4);


void setup() {
	Serial.begin(115200);
	// Initialising the ADS1015
	ads.begin();
	ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV

	// Initialising the UI will init the display too.
	display.init();
	display.flipScreenVertically();
}

void printVoltage() {
	// create more fonts at http://oleddisplay.squix.ch/
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_16);
	display.drawString(0, 0, "V0: " + String(V0));
	display.drawString(0, 0, "V1: " + String(V1));
	display.drawString(0, 0, "V2: " + String(V2));
	display.drawString(0, 0, "V3: " + String(V3));
}


void loop() {
	display.clear();
	getVoltage();
	printVoltage();
	display.display();
}

void getVoltage() {
	V0 = (ads.readADC_SingleEnded(0) * 3) / 1000.00;
	V1 = (ads.readADC_SingleEnded(1) * 3) / 1000.00;
	V2 = (ads.readADC_SingleEnded(2) * 3) / 1000.00;
	V3 = (ads.readADC_SingleEnded(3) * 3) / 1000.00;
}
