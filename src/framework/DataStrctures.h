/* This must be replaced by reusable Filter classes */

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

namespace modular {

template <typename TMMA>
 
struct MinMaxAvg {
    TMMA min {0};
    TMMA max {0};
    TMMA avg {0};
};

}

#endif