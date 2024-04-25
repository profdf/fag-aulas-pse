#include "SerialMonitor.h"

void print(HardwareSerial &serial, const char* msg){
    serial.print(msg);
}

void print(HardwareSerial &serial, char character){
    serial.print(character);
}

char read(HardwareSerial &serial){
    
    if(serial.available()){
        return serial.read();
    }

    return '.';
    
}