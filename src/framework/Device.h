#pragma once

namespace modular {

    class Device {
    public:
        virtual void begin() {};
        virtual void sleep() {};
        virtual void wakeup() {};
        virtual void powerOn() {};
        virtual void powerOff() {};
    };
}