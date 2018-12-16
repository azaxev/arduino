// from http://terryking.us/arduino-testing.htm
/* YourDuino Arduino Board TEST 
 Tests all Arduino I/O and Analog pins for Source and Sink ability
 Tests Analog Read on A0..A5
 terry@yourduino.com 
azaxev@gmail.com
 
 
 This test assumes that pins 0 (RX Data) and 1 (TX Data) are OK
 if programs can be loaded, and that pin 13 is OK if it's attached LED
 can be blinked. Pin 13 is not tested for current sink ability.
 
 This test works with a "Test Shield" that is plugged on top
 of the Arduino under test. This shield has a common isolated 
 connection point. The Common Point has 17 220 ohm resistors 
 connected to every digital pin from 2 to 12, and to every analog
 pin from 0 to 5. It also has two 100,000 ohm resistors which 
 connect it to Ground and +5.0 volts, forming a voltage divider
 that sets the common point to 2.50 volts when all pins are in
 the reset high-impedance input condition. This is read by A0 to
 initially test if any of the pins are "stuck" or "leaking", which 
 will pull the common point away from 2.50 volts
 
 Next, pins 3 thru A5 are tested by setting them High or Low against
 an opposite load presented by pin 2. Each pin must be able to
 source and sink at least 10 ma to bring the common point near 2.50 volts.
 If pin 2 fails, all other pins will fail. 
 
 Next, A0 thru A5 are tested individually with voltages near 1.66, 2.50, 3.33volts
 and possibly others, using the resistors connected to the digital pins to
 make various voltage dividers. 
 
 This design and software is licensed under a Creative Commons 
 Attribution-Noncommercial-Share Alike 3.0 License:
 http://creativecommons.org/licenses/by-nc-sa/3
 */

/*-----( Declare Constants )-----*/

const  int    A2D_Delay    =  1; //ms delay for A-D to settle

const  word LowStuckResultOK     =  2400; 
const  word HighStuckResultOK    =  2600;   
const  word LowVoltResultOK      =  2300;    
const  word HighVoltResultOK     =  2700;   

/*-----( Declare Variables )-----*/

byte gTestPin;
word gMiliVolts;      // Result of AnalogRead 0..1023
int gFailCount;          // Count failures that occur
byte FailArray[20];    // Save Pass-Fail during a test
int FailArrayPtr;

void setup()   /****** SETUP: RUNS ONCE ******/
{
//  delay(500);
  Serial.begin(115200);
//  delay(500);
  Serial.println("Arduino Board Test");
//  Serial.println("YourDuino.com terry@yourduino.com");
//  delay(500);
//  LED13.blink(300, 4);  // "HI" in Morse code
//  delay(500);  
//  LED13.blink(300, 2);  

}//--(end setup )---

word analogReadMV(byte pin)
{
	return (word)(analogRead(pin)) * 49 / 10;
}

void printVolt()
{
//	Serial.print(gMiliVolts/1000);
//	Serial.print('.');
//	Serial.print(gMiliVolts%1000/10);
	Serial.print(gMiliVolts);
}

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  gFailCount = 0;
  Serial.println();  
  Serial.println("--- TEST START ---");
  
//-------------( TEST 1 )---------------------------------------------
  Serial.println("TEST 001 - Any stuck pins??");
//  delay(500);
  gMiliVolts = analogReadMV(A0);
  Serial.print("VoltsRead = ");
  printVolt();

  if (gMiliVolts > LowStuckResultOK
    &&  gMiliVolts < HighStuckResultOK)
  {
    Serial.println("  -- OK!");
  }
  else
  {
    gFailCount ++;
    Serial.println("  ** STUCK OR LEAKY PIN FAIL ** ");    
  }

//-----------------------( TEST 2 )--------------------------------
  Serial.println();    
  Serial.println("TEST 002 - Digital Pins Source Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, LOW);              // Connect Low Load  
  FailArrayPtr    =  0 ;

  //---------( Write the Digital Pin Labels )---------------
  WriteDigitalPinLabels();

  //------( Loop thru pins, testing )-----------  
	for(gTestPin=3; gTestPin<=12; gTestPin++)
	{
		FailArrayPtr ++ ;

		pinMode(gTestPin, OUTPUT);      // Set tested pin to Output mode
		digitalWrite(gTestPin, HIGH);  // Pin Sources current HIGH     
		delay(A2D_Delay);
		gMiliVolts = analogReadMV(A0);
		pinMode(gTestPin, INPUT);      // ReSet tested pin to Input mode   

		printVolt();
		Serial.print("   ");      

		if (gMiliVolts > LowVoltResultOK
		  &&  gMiliVolts < HighVoltResultOK)
		{
		  FailArray[FailArrayPtr]  = 0;      
		}
		else
		{
		  FailArray[FailArrayPtr]  = 1;
		}        

	}//END Loop thru Source Tests

  Serial.println();  
  WriteDigitalPassFail();


//--------------------( TEST 3 )----------------------------------------

  Serial.println("\nTEST 003 - Digital Pins Sink Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, HIGH);              // Connect HIGH Load  
  FailArrayPtr    =  0 ;

  //---------( Write the Digital Pin Labels )------------
  WriteDigitalPinLabels();

  //------( Loop thru pins, testing )-----------  
	for(gTestPin=3; gTestPin<=12; gTestPin++)
	{
		FailArrayPtr ++ ;

		pinMode(gTestPin, OUTPUT);      // Set tested pin to Output mode
		digitalWrite(gTestPin, LOW);  // Pin Sinks current LOW   
		delay(A2D_Delay);
		gMiliVolts = analogReadMV(A0);
		pinMode(gTestPin, INPUT);      // ReSet tested pin to Input mode   

		printVolt();
		Serial.print("   ");      

		if (gMiliVolts > LowVoltResultOK
		  &&  gMiliVolts < HighVoltResultOK)
		{
		  FailArray[FailArrayPtr]  = 0;      
		}
		else
		{
		  FailArray[FailArrayPtr]  = 1;
		}        

	}//END Loop thru Source Tests

  Serial.println();  
  WriteDigitalPassFail();


//-------------------------( TEST 4 )----------------------------------------
  Serial.println();    
  Serial.println("TEST 004 - Analog Pins Source Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, LOW);              // Connect Low Load  

  WriteAnalogPinLabels();

	for(gTestPin=3; gTestPin<=12; gTestPin++)
	{
		FailArrayPtr ++ ;

		pinMode(gTestPin, OUTPUT);      // Set tested pin to Output mode
		digitalWrite(gTestPin, HIGH);  // Pin Sources current HIGH     
		delay(A2D_Delay);
		gMiliVolts = analogReadMV(A0);
		pinMode(gTestPin, INPUT);      // ReSet tested pin to Input mode   
		printVolt();
		Serial.print("   ");   

		if (gMiliVolts > LowVoltResultOK
		  &&  gMiliVolts < HighVoltResultOK)
		{
		  FailArray[FailArrayPtr]  = 0;      
		}
		else
		{
		  FailArray[FailArrayPtr]  = 1;
		}        

	}
  Serial.println();
  WriteAnalogPassFail();

  /*---------( TEST 5 )----------------------*/

  Serial.println("\nTEST 005 - Analog Pins Sink Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, HIGH);              // Connect HIGH Load  

  WriteAnalogPinLabels();

	for(gTestPin=3; gTestPin<=12; gTestPin++)
	{
		FailArrayPtr ++ ;

		pinMode(gTestPin, OUTPUT);      // Set tested pin to Output mode
		digitalWrite(gTestPin, LOW);    // Pin Sinks current LOW   
		delay(A2D_Delay);
		gMiliVolts = analogReadMV(A0);
		pinMode(gTestPin, INPUT);      // ReSet tested pin to Input mode   
		printVolt();
		Serial.print("   ");   

		if (gMiliVolts > LowVoltResultOK
		  &&  gMiliVolts < HighVoltResultOK)
		{
		  FailArray[FailArrayPtr]  = 0;      
		}
		else
		{
		  FailArray[FailArrayPtr]  = 1;
		}        

	}

  Serial.println();
  WriteAnalogPassFail();



  /*---------( TEST 6 )----------------------*/
  Serial.println();
  Serial.println("TEST 006 - Analog Pins A0 to A5: A to D (About 2.50 V)");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, HIGH);              // Connect HIGH Load
  pinMode(3, OUTPUT);      // Set Load pin to Output mode  
  digitalWrite(3, LOW);              // Connect LOW Load  

  WriteAnalogVoltLabels();

  for (  gTestPin = A0; 
         gTestPin <= A5;
         gTestPin ++)
  {// Loop thru Analog Tests
    delay(A2D_Delay);
    gMiliVolts = analogReadMV(gTestPin);
    printVolt();
    FailArray[FailArrayPtr]= (gMiliVolts > 2250 && gMiliVolts < 2750) ? 0 : 1;
    Serial.print("   ");     
  }// END Loop thru Analog Tests  
  Serial.println();
  WriteAnalogPassFail();

  /*---------( TEST 7 )----------------------*/
  Serial.println();
  Serial.println();
  Serial.println("TEST 007 - Analog Pins A0 to A5: A to D (About 3.33 V)");  
  pinMode(4, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(4, HIGH);              // Connect 2nd Resistor

  WriteAnalogVoltLabels();

  for (  gTestPin = A0; 
         gTestPin <= A5;
         gTestPin ++)
  {// Loop thru Analog Tests
    delay(A2D_Delay);
    gMiliVolts = analogReadMV(gTestPin);
    printVolt();
    FailArray[FailArrayPtr]= (gMiliVolts > 2997 && gMiliVolts < 3663) ? 0 : 1;
    Serial.print("   ");     
  }// END Loop thru Analog Tests    
  Serial.println();
  WriteAnalogPassFail();


  /*---------( TEST 8 )----------------------*/
  Serial.println();
  Serial.println();  
  Serial.println("TEST 008 - Analog Pins A0 to A5: A to D (About 1.66 V)");  
  pinMode(4, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(4, LOW);              // Connect 2nd Resistor

  WriteAnalogVoltLabels();

  for (  gTestPin = A0; 
         gTestPin <= A5;
         gTestPin ++)
  {// Loop thru Analog Tests
    delay(A2D_Delay);
    gMiliVolts = analogReadMV(gTestPin);
    printVolt();
    FailArray[FailArrayPtr]= (gMiliVolts > 1494 && gMiliVolts < 1826) ? 0 : 1;
    Serial.print("   ");     
  }// END Loop thru Analog Tests     

  //----------( End Test Digital and Analog Ports: Reset everything)-------
  pinMode(2, INPUT);      // Reset Load pin to Input mode
  pinMode(3, INPUT);      // Reset Load pin to Input mode  
  pinMode(4, INPUT);      // Reset Load pin to Input mode 
  MCUCR |= ( 1 << PUD ); //Disable all Pullups

  /*------------( TEST COMPLETE )----------------*/
  Serial.println();    
  Serial.println("TEST COMPLETE");  
  if (gFailCount > 0)
  {
    Serial.print("!!!!!!!!!!  THERE WERE ");  
    Serial.print(gFailCount, DEC);            
    Serial.print(" FAILURES !!!!!!!!!!");  
  }
  Serial.println();  
  
    pinMode(13, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, HIGH);
    for(;;)
    {
        digitalWrite(10, HIGH);
        digitalWrite(11, gFailCount ? HIGH : LOW);
        digitalWrite(12, gFailCount ? LOW : HIGH);
        delay(500);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        delay(500);
    }    
  //--(end main loop )---
}
//----------------( Declare User-written Functions )--------------------------

void WriteDigitalPinLabels()
{
  //---------( Write the Digital Pin Labels )---------------------
  for (  gTestPin = 3; 
         gTestPin <= 12;
         gTestPin ++)     
  {//Write the label strings  
    Serial.print("PIN-"); 
    Serial.print(gTestPin, DEC);
    Serial.print(gTestPin < 10 ? "  " : " ");         
  }// Write Labels  
  Serial.println();
}

void WriteAnalogPinLabels()
{
  //---------( Write the Analog Pin Labels )---------------------
  for (  gTestPin = A1; 
         gTestPin <= A5;
         gTestPin ++)     
  {//Write the label strings  
    Serial.print("PIN-");                
    Serial.print(gTestPin-14 , DEC);
    Serial.print("  ");         
  }// Write Labels  
  Serial.println();
}


void WriteAnalogVoltLabels()
{
  //---------( Write the Analog Pin Labels )---------------------
  for (  gTestPin = A0; 
         gTestPin <= A5;
         gTestPin ++)     
  {//Write the label strings  
    Serial.print("PIN-");                
    Serial.print(gTestPin -14 , DEC);
    Serial.print("  ");         
  }// Write Labels  
  Serial.println();
}

//--------( Write the Digital Pin PASS-FAIL Strings )----------------------  
void WriteDigitalPassFail()
{
  FailArrayPtr   = 0;
  for (  gTestPin = 3; 
         gTestPin <= 12;
         gTestPin ++)  
  {//Write the PASS-FAIL strings  
    FailArrayPtr ++;  
    if   (FailArray[FailArrayPtr]  == 1)  // Was a Fail
    {
        gFailCount ++;
      Serial.print("FAIL   "); 
    }
    else
    {
      Serial.print("-OK-   ");  
    }       

  }// Write PASS-FAIL
  Serial.println();  
}//End  WriteDigitalPassFail



//--------( Write the Analog Pin PASS-FAIL Strings )----------------------  
void WriteAnalogPassFail()
{
  FailArrayPtr   = 0;
  for (  gTestPin = A0; 
         gTestPin <= A5;
         gTestPin ++)  
  {//Write the PASS-FAIL strings  
    FailArrayPtr ++;  
    if   (FailArray[FailArrayPtr]  == 1)  // Was a Fail
    {
        gFailCount ++;
      Serial.print("FAIL   "); 
    }
    else
    {
      Serial.print("-OK-   ");  
    }       

  }// Write PASS-FAIL
  Serial.println();  
}//End  WriteDigitalPassFail




//*********( THE END )***********
