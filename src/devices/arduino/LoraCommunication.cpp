#include "LoraCommunication.h"
#include <Arduino.h>

namespace modular::devices::arduino {

LoraCommunication::LoraCommunication() {
    // Do Lora Initializaiton here
};

void LoraCommunication::listen() {
    
};

void LoraCommunication::send(std::array<int, 0> value) {
    // auto vec = swatk::cbor::encode(value);
    // std::string str(vec.begin(), vec.end());
    // Fake Lora send
    // translate vector to lora object
    // LoRaSend()
    // Serial.println(str.c_str());
}

}

