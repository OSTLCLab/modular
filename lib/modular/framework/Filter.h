#pragma once

#include <typeinfo> 

namespace modular {

    template <typename FILTER_INPUT, typename FILTER_OUTPUT>

    class Filter
    {
    public:
        virtual void reset(FILTER_OUTPUT &val) {};
        virtual FILTER_OUTPUT filter(FILTER_OUTPUT &val, FILTER_INPUT newValue) = 0;
        const char* getType() {
            return typeid(FILTER_OUTPUT).name();
        };
    private:
    };
}