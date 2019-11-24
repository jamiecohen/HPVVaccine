//
// Created by Jamie Cohen on 2019-03-25.
//

#include "helper.h"

using namespace boost::math;

helper::helper() {
}


double helper::getrand() {

    return dist(engine);
}

double helper::ratetoprob(double rate) {
    return(1 - exp(-rate));
}



helper::~helper() = default;
