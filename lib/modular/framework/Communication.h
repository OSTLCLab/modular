 #pragma once

namespace modular {

    template <typename V>

    class Communication {
        public:
            virtual void send(V value) {};
            virtual void listen() {};  
    };

}