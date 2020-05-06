// Wire Slave Test

// It simulates a Wire slave that compomise the communication with the Master
// It sends data as an I2C/TWI slave device
// It introduces misfunctionalities to test if Master is able to not get stuck
// Refer to the "Master Test" example for use with this

uint8_t len;
int num_bytes;
const int nMOS2 = 2;

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  // Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);           // start serial for output
  num_bytes = 1;
  
  Wire.onRequest(replyToReadReq);

  Wire.onReceive(receiveEvent);
}



// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void replyToReadReq() {
  
    switch (num_bytes) {
    case 1:
      Wire.write("h"); // respond with message of 1 bytes
      pinMode(nMOS2, OUTPUT);
      digitalWrite(nMOS2, LOW);
      num_bytes++;
      break;
    case 2:
      Wire.write("he"); // respond with message of 2 bytes
      num_bytes++;
      break;
    case 3:
      Wire.write("hel"); // respond with message of 3 bytes
      delay(3000);
      num_bytes ++;
      break;
    case 4:
      pinMode(nMOS2, OUTPUT);
      digitalWrite(nMOS2, HIGH);
      delay(7000);
      num_bytes ++;
      break;
    case 8:
      Wire.write("helloWor"); // respond with message of 8 bytes
      num_bytes++;
      break;
    case 9:
      Wire.write("helloWorl"); // respond with message of 9 bytes
      num_bytes++;
      break;
    case 10:
      Wire.write("helloWorld"); // respond with message of 10 bytes
      num_bytes = 1;
      break;
    default:
      pinMode(nMOS2, OUTPUT);
      digitalWrite(nMOS2, LOW);
      break;
    }
  
}


void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  num_bytes++;
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void loop() {
  if (num_bytes>=5 && num_bytes<= 7) {
    pinMode(nMOS2, OUTPUT);
    digitalWrite(nMOS2, HIGH);
    delay(10000);
    if (num_bytes =! 7){
      num_bytes++;
    }
    else num_bytes = 8;
  }
  else {
    pinMode(nMOS2, OUTPUT);
    digitalWrite(nMOS2, LOW);
  }
}
