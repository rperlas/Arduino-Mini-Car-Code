/*
	Ridwaan Safi - Jeffry Lien - Ronald Perlas
	Mr. Wong
	06/12/13
	Arduino Master Program (Grade 12 Engineering ISP) -- This program will allow an intelligent car to travel along either a curve or right-angled maze.
        It reads 3 equally spaced LDRs to travel along a black line on a white background.  
*/

// Pin Variables - H-Bridge
const int  motorOne =  3;	// Controls Forward Motor Direction
const int  motorTwo =  11;	// Controls Reverse Motor Direction
const int  motorA   =  5;       // Controls Second Forward Motor Direction
const int  motorB   =  6;       // Controls Second Forward Motor Direction
const int    enable =  9;	// Controls H-Bridge
const int enableTwo =  7;

// Pin Variables - Light Sensor
const int       led =  13;	// Controls Testing LED
const int 	ldr =  A0;	// Controls The Left Light Sensors
const int    ldrTwo =  A1;      // Controls the Middle LRDR
const int    ldrTri =  A4;      // Controls the Right LDR

// Variable States - LDR Readings
int val        = 0; // Value of the left LDR
int valTwo     = 0; // Value of Middle LDR
int valTri     = 0; // Value of Right LDR

// Variable States - Movements
int black;       //The initial reading of the middle LDR on black
int whiteOne;    // The initial reading of the left LDR on white
int whiteTwo;    // The initial reading of the rtight LDR on white
int check = 0;   // Used to tell the code to read the LDRs

// Pin Initialization
void setup() { 
	pinMode (motorOne, OUTPUT);	// Sets H-Bridge Motor Pins As Outputs
	pinMode (motorTwo, OUTPUT); 
        pinMode (motorA, OUTPUT);
        pinMode (motorB, OUTPUT);
	pinMode (enable, OUTPUT);
	pinMode (led, OUTPUT);		// Sets LED Pin As Output
	digitalWrite (enable, HIGH);	// Sets H-Bridge As HIGH
        digitalWrite (led, HIGH);       // Sets the LEDs As HIGH
        Serial.begin (9600);            // Initializes The Serial Motor
}

// Function Output - Main Program Loop
void loop() {
        
        // Initial LDR Readings - Sets Black And White Ranges
        if (check == 0)
        {
           check = 1;
           delay (1000);
           black = analogRead (ldrTwo) + 15;
           whiteOne = analogRead (ldr) - 30;
           whiteTwo = analogRead (ldrTri) - 30;
        }

	// Toggles Light Sensors - Value Readings     
	val = analogRead (ldr);
        valTwo = analogRead (ldrTwo);
        valTri = analogRead (ldrTri);
        Serial.println (valTri);
        

	// Function Output - Straight Line
        if (valTwo < black && valTri > whiteTwo && val > whiteOne)
        {
	  analogWrite (motorOne, 0);    // Forward Left Motor
          analogWrite (motorTwo, 40);   // Reverse Left Motor
          analogWrite (motorB, 0);      // Forward Right Motor
          analogWrite (motorA, 50);     // Reverse Right Motor
        }      
        // Function Output - Left Turn
        else if (valTwo < black && val < whiteOne)
        {
          delay (1000);
          while (1) {
            valTwo = analogRead (ldrTwo);
            valTri = analogRead (ldrTri);
            val    = analogRead (ldr);
            Serial.println (valTri);
            analogWrite (motorOne, 60);
            analogWrite (motorTwo, 0);
            analogWrite (motorB, 0);     
            analogWrite (motorA, 60);
            if (valTwo < black && valTri > whiteTwo && val > whiteOne)
              break;
          } 
          delay (1000);
        }

        // Function Output - Right Turn
        else if (valTwo < black && val > whiteOne && valTri < whiteTwo)
        {
          delay (1000);
          while (1) {
            valTwo = analogRead (ldrTwo);
            valTri = analogRead (ldrTri);
            val    = analogRead (ldr);
            Serial.println (valTri);
            analogWrite (motorOne, 0);
            analogWrite (motorTwo, 60);
            analogWrite (motorB, 60);     
            analogWrite (motorA, 0);
            if (valTwo < black && valTri > whiteTwo && val > whiteOne)
              break;
          } 
          delay (1000);
        }
        
        // Function Output - Curve Adjustments (Left)
        else if (valTwo > black && valTri < whiteTwo && val > whiteOne)
        {
          delay (100);
          while (1) {
            valTwo = analogRead (ldrTwo);
            valTri = analogRead (ldrTri);
            val    = analogRead (ldr);
            Serial.println (valTri);
            analogWrite (motorOne, 0);
            analogWrite (motorTwo, 40);
            analogWrite (motorB, 40);     
            analogWrite (motorA, 0);
            if (valTwo < black && valTri > whiteTwo && val > whiteOne)
              break;
          } 
          delay (1000);
        }
        
        // Function Output - Curve Adjustments (Right)
        else if (valTwo > black && valTri > whiteTwo && val < whiteOne)
        {
          delay (1000);
          while (1) {
            valTwo = analogRead (ldrTwo);
            valTri = analogRead (ldrTri);
            val    = analogRead (ldr);
            Serial.println (valTri);
            analogWrite (motorOne, 40);
            analogWrite (motorTwo, 0);
            analogWrite (motorB, 0);     
            analogWrite (motorA, 40);
            if (valTwo < black && valTri > whiteTwo && val > whiteOne)
              break;
          } 
          delay (1000);
        }
}
