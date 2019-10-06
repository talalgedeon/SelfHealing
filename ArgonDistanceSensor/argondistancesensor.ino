// This #include statement was automatically added by the Particle IDE.
#include <Grove_ChainableLED.h>

// This #include statement was automatically added by the Particle IDE.
#include <Grove_4Digit_Display.h>

// This #include statement was automatically added by the Particle IDE.
#include <Grove-Ultrasonic-Ranger.h>

#define CLK D4
#define DIO D5
// This #include statement was automatically added by the Particle IDE.
Ultrasonic ultrasonic(D2);
TM1637 disp(CLK,DIO);
ChainableLED leds(A4, A5, 1);


int lastRange = 0;

void toggleLed(const char *event, const char *data) {
    leds.setColorHSB(0, 0.0, 1.0, 0.5);
    
    delay(500);
    
    leds.setColorHSB(0, 0.0, 1.0, 1.0);
    
    delay(500);
    
    leds.setColorHSB(0,0.0,1.0,1.5);
    
    delay(500);
    
    leds.setColorHSB(0,0.0,3.0,1.5);
    
    delay(500);
    
    leds.setColorHSB(0,0.0,1,2.5);
    
    delay(500);
    
    leds.setColorHSB(0,0.0,4.0,0.5);
    
    delay(500);
    
    leds.setColorHSB(0,0.0,0,0);
    
}

void setup()
{
  Serial.begin(9600);
  
  disp.init();
  
  disp.set(BRIGHT_TYPICAL);
  
  leds.init();
  
  leds.setColorHSB(0, 0.0, 0.0, 0.0);
  
  Mesh.subscribe("toggle-led", toggleLed);

//Options are: BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void loop()
{
	int range;
	int digit;
	int pos = 3;

	Serial.println("Obstacle found at:");

	range = ultrasonic.MeasureInCentimeters();
	Serial.print(range); //0~400cm
	Serial.println(" cm");
	delay(250);
	if (range != lastRange) {
	lastRange = range;

	// Fill display with zeros
	for (int i = 0; i < 4; i++) {
		disp.display(i, 0);
	}

	// Extract each digit from the range and write it to the display
	while (range >= 1) {
		// Get the current digit by performing modulo (%) division on the range
		digit  = range % 10;
		// Remove the trailing digit by whole-number division
		range /= 10;

		disp.display(pos, digit);
		pos--;
	}
}
}