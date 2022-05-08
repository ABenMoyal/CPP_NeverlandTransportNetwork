//
// Created by adirr on 04/05/2022.
//

#ifndef HW2_UTILSFUNCTIONS_H
#define HW2_UTILSFUNCTIONS_H

#include "algorithm"

template<class C, typename T>
bool contains(C& c, T t) {
    return std::find(std::begin(c), std::end(c), t) != std::end(c);
};

#endif //HW2_UTILSFUNCTIONS_H
