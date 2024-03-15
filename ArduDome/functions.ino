// inizialize digital pins as OUTPUT with "LOW" value
void initializePins () {
  dpin[0]=dpin[1]=false;
  for (i=2; i<=13; i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
    // Serial.println(i); // Debug
    dpin[i]=false;
  }  
}

// write "HIGH" or "LOW" on specified pin and save status in array dpin[]
boolean writeStatus(int pin, boolean value) {
  digitalWrite(pin, value);
  dpin[pin]=value;
  return value;
}

int readStatus(int pin) {
 if (pin<=13) {
  dpin[pin] = digitalRead(pin);
  return dpin[pin];  
 }else{
  return analogRead(pin);
 }
}

// verify if a char is a number
boolean isNumber(char character) {
  if ((character>=48) && (character<=57)) return true; else return false;
}

// return pin number specified by serial command
// remember the command is in this format: *CMDA2S/ so this function
// takes the 5th and the 6th char and does many checks with ASCII table
// in order to convert values from 02 to A6 to an integer from 2 to 19
// being sure that every single char is a number or the 5th is a "A" 
// followed by a number for analog inputs
byte getPin() {
  if (inputString.charAt(4)==65) { 
    if ((inputString.charAt(5)>=48) && (inputString.charAt(5)<=53)) return (inputString.charAt(5)-34); else return 99;
  } else {
      if ((isNumber(inputString.charAt(4))) && (isNumber(inputString.charAt(5)))) {
        char strtemp[2]={inputString.charAt(4),inputString.charAt(5)};
        if ( (atoi(strtemp))<=19 && (atoi(strtemp))>=2 ) return (atoi(strtemp)); else return 99;
      } else return 99;
    }
}    

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is "/", set a flag
    // so the main loop can do something about it:
    if (inChar == '/') {
      stringComplete = true;
    } 
  }
}
