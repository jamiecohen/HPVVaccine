//
// Created by Jamie Cohen on 2019-03-25.
//

#ifndef HPVVaccine_HELPER_H
#define HPVVaccine_HELPER_H

#include <random>
#include <boost/math/distributions.hpp>

class helper {

public:


// Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine{1234};

// "Filter" MT engine's output to generate pseudo-random double values,
// **uniformly distributed** on the closed interval [0, 1].
// (Note that the range is [inclusive, inclusive].)
    std::uniform_real_distribution<double> dist{0.0, 1.0};

// Generate pseudo-random number.

    double getrand();
    double ratetoprob(double rate);

    helper();
    ~helper();

};


#endif //HIVHPVVaccine_HELPER_H
