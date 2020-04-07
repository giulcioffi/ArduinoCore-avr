// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int num_bytes;
int count;

void setup() {
    Wire.begin(8);                // join i2c bus with address #8
    // Wire.onRequest(requestEvent); // register event
    Serial.begin(9600);           // start serial for output
    num_bytes = 4;
    count = 0;

    Wire.onRequest(replyToReadReq);

    Wire.onReceive(receiveEvent);
}



// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void replyToReadReq() {
    switch (num_bytes) {
        case 4:
            Wire.write("hell"); // respond with message of 4 bytes
            num_bytes++;
            break;
        case 5: 
            Wire.write("hello"); // respond with message of 5 bytes
            num_bytes++;
            break;
        case 6: 
            Wire.write("he"); // respond with message of 2 bytes
            num_bytes++;
            break;
        case 7: // force SDA, SCL low
            digitalWrite(SDA, 0);
            digitalWrite(SCL, 0);
            delay(100);     
            digitalWrite(SDA, 1);
            digitalWrite(SCL, 1);
            num_bytes = 4;
            break;
        default:
            break;
        }
}


void receiveEvent(int howMany) {
    if (count < 10) {
        while (1 < Wire.available()) { // loop through all but the last
            char c = Wire.read(); // receive byte as a character
            Serial.print(c);         // print the character
        }
        int x = Wire.read();    // receive byte as an integer
        Serial.println(x);         // print the integer
    }
    else {
        digitalWrite(SDA, 0);
        digitalWrite(SCL, 0);
    }
}

void loop() {
    
}