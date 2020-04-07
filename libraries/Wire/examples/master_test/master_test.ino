// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <ATF2.h>

unsigned long elapsed_time;
int num_bytes;
int i;
byte x = 0;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  num_bytes = 4;

  for (i=0; i<20; i++) {
    tryRead();
  }

  for (i=0; i<100; i++) {
    tryWrite();
  }
}


void tryRead() {
  Serial.print("Master wants to start a read @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);

  Wire.requestFrom(8, num_bytes);    // request 6 bytes from slave device #8
  Serial.print("Master started a read @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  Serial.print("Master completed the read @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);
  Serial.println();

  if (num_bytes == 7)
    num_bytes = 4;
  else
    num_bytes++;
  delay(500);
}



void tryWrite() {
  Serial.print("Master wants to start a write @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);

  Wire.beginTransmission(8);
  Serial.print("Master started a write @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);

  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  Serial.print("Master completed the write @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);
  Serial.println();

  x++;
  delay(500);
}

void loop() {
  
}