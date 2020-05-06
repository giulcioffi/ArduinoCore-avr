// Wire Master Test

// It simulates a Wire Master
// It tries 10 reads from an I2C/TWI slave device
// It tries 10 writes to an I2C/TWI slave device

#include <Wire.h>

unsigned long elapsed_time;
int num_bytes;
int i;
byte x = 0;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  num_bytes = 1;
  Wire.setWireTimeoutUs(25000);
  
  for (i=0; i<10; i++) {
    tryRead();
    num_bytes++;
  }

  for (i=0; i<10; i++) {
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
  Serial.println();

  Serial.print("Master completed the read @ time: ");
  elapsed_time = millis();
  Serial.println(elapsed_time);
  Serial.println();

  delay(3000);
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
  delay(3000);
}

void loop() {
  
}
