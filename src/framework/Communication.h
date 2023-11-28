#ifndef COMMUNICATION_H
#define COMMUNICATION_H

namespace modular {

template <typename V>

class Communication {
    public:
        virtual void send(V value) {};
        virtual void listen();  
};

}
#endif