#include "SerialCommunication.h"
#include <Arduino.h>

namespace modular::devices::arduino {

SerialCommunication::SerialCommunication() {

};

void SerialCommunication::listen() {
    
};

void SerialCommunication::send(std::string value) {
    Serial.println(value.c_str());
}

}

