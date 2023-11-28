#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <framework/Communication.h>
#include <string>

namespace modular::devices::arduino {

class SerialCommunication : public Communication<std::string> {
    public:
        SerialCommunication();
        void listen();
        void send(std::string value);
};

}

#endif