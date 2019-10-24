//
// Created by Jamie Cohen on 2019-03-25.
//

#include "helper.h"

using namespace boost::math;

helper::helper() {

}

double helper::getrand() {
    double x = dist(engine);
    return x;
}

double helper::ratetoprob(double rate) {
    double prob;
    prob = 1 - exp(-rate);
    return(prob);
}


helper::~helper() = default;
