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

double helper::rbeta(int alpha, int beta) {

    double randFromUnif = getrand();

    beta_distribution<> distr(alpha,beta);

    double randFromDist = quantile(distr, randFromUnif);

    return(randFromDist);
}

helper::~helper() = default;
