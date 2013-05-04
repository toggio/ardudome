/*

ArduDome 0.9
Domotic with Arduino + RaspberryPI + PHP + JSON + jQuery
Platform and browser-independent web based Arduino bidirectional remote control & sensors
by Luca Soltoggio
15/03/2013
http://arduinoelettronica.wordpress.com/

THIS IS JUST THE ARDUINO PART

Don't forget to connect a 10μF capacitor between the RESET and GND lines!!!
This sketch get a command from serial port and actvite/deactvate output or send value back.
The command has to be 7 chars long and begin with "*CMD" and end with "/".
Between "*CMD" and "/", you have to put the pin number (02, 03, 04, ..., A5, A6) followed by the action:
V = value (read) - get the raw value for analog input
S = status (read) - is the output status of digital pins
H = high (write) - just for digital pins
L = low (write) - just for digital pins
T = toggle (write) - just for digital pins
For example the following command:
*CMDA3V/
print on the serial port the raw value of analog pin A3, while:
*CMD12H/
set the output of the digital pin 12 to high, while:
*CMD02S/
get the logical status of digital output 3.
Pins "0" and "1" are excluded because used for serial communication
This sketch is designed to work with his PHP script, but it could be integrated 
in other prjects using the syntax above.
If used with his original PHP script, it will automatically get the right command
from web page modules.

*/


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
byte i=0;                        // generic counter
byte numPin=0;                   // PIN number
boolean dpin[14];                // array containing logical status of digital outputs
char action;                        // char containing the last char of the command

void setup() {
  // initialize serial:
  Serial.begin(38400);
  initializePins();
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  
  if (stringComplete) {
    // verify that this is a command (8 chars beginning with "*CMD")
    if ((inputString.length()==8) && (inputString.startsWith("*CMD"))) {   
      numPin=getPin();
      // verifiy that the PIN specified in the command is valid
      if (numPin!=99) {
        action=inputString.charAt(6);
        // verifiy last char of command and do the associated functions
        if (action=='V') {          
          Serial.println(readStatus(numPin));
        } else
        if ((numPin<=13) && (numPin>=2)) switch (action) {
          case 'S':      
            Serial.println(readStatus(numPin));
            break;            
          case 'H':
            writeStatus(numPin,HIGH);
            break;
          case 'L':
            writeStatus(numPin,LOW);
            break;
          case 'T':      
            writeStatus(numPin,!readStatus(numPin));
            break;
         }
        // Serial.println(inputString);        
        // Serial.println(getPin()); // Debug
        // Serial.println(cmd);
      }
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

}





