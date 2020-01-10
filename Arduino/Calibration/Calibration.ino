 /* Read Quadrature Encoder
  * Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.
  *
  * Sketch by max wolf / www.meso.net
  * v. 0.1 - very basic functions - mw 20061220
  *
  */  

#include <Servo.h>
#include <Oscillator.h> //Librera ArduSnake de Obijuan, en GitHub
#include <EEPROM.h>

Zowi zowi;

 int val; 
 int encoder0PinA = A2;
 int encoder0PinB = A3;
 int buttonPin = A0;
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;

int homePos[] = {90, 90, 90, 90};
int trims[4];
int tt = 0;
int buttonState = 0;         // current state of the button
int lastButtonState = HIGH;     // previous state of the button

void setup() { 
	memset(trims, sizeof(trims), 0);
 	
	zowi.init(2, 3, 4, 5, false);
 	zowi.setTrims(0,0,0,0);
 	zowi.home();
	zowi._moveServos(500,homePos);
    
    pinMode (encoder0PinA,INPUT);
   	pinMode (encoder0PinB,INPUT);
   	pinMode (buttonPin, INPUT_PULLUP);
   	for (int i=0; i< 3; i++)
   		showTrims(i);
   		
   	Serial.begin (9600);
 } 

void showTrims(int i)
{
   	Serial.print("Trim ");
   	Serial.print(i+1);
  	Serial.print(" is ");
   	Serial.println(trims[i]);
}

 void loop() { 

 	buttonState = digitalRead(buttonPin);
  	if (buttonState != lastButtonState) 
  	{
    	if (buttonState == HIGH) 
    	{
	    	showTrims(tt);
	      	tt++;
			if (tt > 3) tt = 0; 	  	
    	}
        delay(50);
  	}
  	lastButtonState = buttonState;
	
   	n = digitalRead(encoder0PinA);
   	if ((encoder0PinALast == LOW) && (n == HIGH)) {
    	if (digitalRead(encoder0PinB) == LOW) {
       		trims[tt]--;
     	} else {
       		trims[tt]++;
     	}
	
		zowi.setTrims(trims[0],trims[1],trims[2],trims[3]);
		zowi._moveServos(250,homePos);
		
     	Serial.print(tt+1);	
     	Serial.print(": ");
     	Serial.println (trims[tt]);
   	} 
   	encoder0PinALast = n;
 } 
