//
// Created by Jamie Cohen on 3/4/19.
//

#ifndef HPVVaccine_CALIBRATE_H
#define HPVVaccine_CALIBRATE_H


#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <time.h>


typedef std::vector<std::vector<int> > IntMatrix;
typedef std::vector<std::vector<double> > DoubleMatrix;

class calibrate {

public:

    calibrate(int n_sims, int n_params, int n_targs);
    ~calibrate(void);

    std::vector<double> loadCalibData(int n_params, int n_sim);
    void CalculateGOF(int n_sims, double rand);
    double WeightedDistance(double data, double mean, double N);
    double rnormal_trunc (double mu, double sigma, double upper, double lower);
    double rlognormal (double mu, double sigma);
    int runif (double lower, double upper);
    void GetProbAcceptance(double neighbor, double current, int n_sims);

    double tune_factor;
    enum MultType {prob = 0, RR = 1, Unif = 2};
    std::vector<MultType> multipliers_type;

    std::vector<double> calib_targs;
    std::vector<double> calib_targs_N;
    DoubleMatrix calib_params;
    DoubleMatrix saved_output;
    std::vector<double> best_params;
    std::vector<double> best_output;
    std::vector<double> GOF;
    double GOF_min;
    double GOF_min_run;
    DoubleMatrix multipliers;
    std::string multipliers_names;
    std::string calib_targs_names;
    std::vector<double> tuned_SD;
    double ProbAcceptance;

};


#endif //HPVVaccine_CALIBRATE_H
