#ifndef LORACOMMUNICATION_H
#define LORACOMMUNICATION_H

#include <framework/Communication.h>
#include <string>
#include <array>
#include <vector>

namespace modular::devices::arduino {

class LoraCommunication : public Communication<std::array<int, 0>> {
    public:
        LoraCommunication();
        void listen();
        void send(std::array<int, 0> value);
};

}

#endif