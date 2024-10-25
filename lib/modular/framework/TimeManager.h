#pragma once


namespace modular {

    /*
     * Provide an interface to the time manager
     * TIME_TYPE declares the type of the timestamp (e.g. uint32_t)
     */

    template <typename TIME_TYPE>

    class TimeManager {
        public:
            virtual TIME_TYPE getTimeStamp() {
                return TIME_TYPE{0};
            };

    };

}