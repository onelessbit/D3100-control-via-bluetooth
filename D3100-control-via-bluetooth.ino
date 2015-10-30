/*
A simple program for rometely controlling your DSLR
Choose the appropriate cord: http://www.doc-diy.net/photo/remote_pinout/
I am using 2 buttons: one for single/burst mode and one for Bulb mode
Also, I made a small Android app to control via bluetooth - in progress - 29/10/15

From the 
Single photo:	200
Manual (Bulb):	####ms
*/

int BTread;			// store the string from the bluetooth
int SbtnState = 0;		// store the single shot mode button status
int BbtnPin = 0;		// store the Bulb mode button status
int btnPin = 3;			// which pin is the button attached to
int focusPin = 5;		// which pin is the focus command attached to
int shutterPin = 6;		// which pin is the shutter command attached to


// takePicture fucntion
void takePicture(int time){
	digitalWrite(focusPin, HIGH);	// focus (doesn't do anything if you have your camera in manual mode)
		delay(1000);						// wait for focus
		
		digitalWrite(shutterPin, HIGH);	// take the picture!
		delay(time);
		
		digitalWrite(shutterPin, LOW);
		digitalWrite(focusPin, LOW);
		
	}
}

void setup()
{	
	// initialize the serial communication
	Serial.begin(9600);
	
	// initialize the pins
	pinMode(btnPin, INPUT);		
	pinMode(focusPin, OUTPUT);
	pinMode(shutterPin, OUTPUT);
}

void loop()
{
	// read from buttons
	singleButtonState = digitalRead(SbtnPin);
	bulbButtonState = digitalRead(BbtnPin);
	
	// do the button work
	if (singleButtonState == HIGH){
		takePicture(200);
	}
	
	if (bulbButtonState == HIGH){
		takePicture(1050);
	}
	
/*******************************************************************************/

	// read from bluetooth
	if (Serial.available() > 0) {					// if there is data on BT serial
		BTread = Serial.read();						// store the data
		println("Received: %d", BTread);
	
		takePicture(BTread);						// call the takePicture function
		
		// reset the parameter/flush the serial
		BTread = 0;
		Serial.flush();
	}
}










