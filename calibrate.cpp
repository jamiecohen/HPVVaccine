//
// Created by Jamie Cohen on 3/4/19.
//

#include "calibrate.h"

using namespace std;


calibrate::calibrate(int n_sims, int n_params, int n_targs) {

    calib_targs.resize (n_targs);
    calib_targs_N.resize (n_targs);

    multipliers.resize(n_params);
    for (int i = 0; i < n_params; i++) {
        multipliers[i].resize(3);
    }

    multipliers_type.resize(n_params);

    calib_params.resize (n_sims);
    for (auto & calib_param : calib_params){
        calib_param.resize (n_params);
    }

    saved_output.resize (n_sims);
    for (auto & i : saved_output){
        i.resize (n_targs);
    }

    best_params.resize (n_params);
    best_output.resize(n_targs);

    GOF.clear();

    tuned_SD.resize(n_params);

}

calibrate::~calibrate() {

}

void calibrate::CalculateGOF(int n_sims, double rand) {
    GOF.push_back (WeightedDistance (saved_output[n_sims][0], calib_targs[0], calib_targs_N[0]));
    for (int i = 1; i < calib_targs.size(); i ++){
        GOF[n_sims] += WeightedDistance (saved_output[n_sims][i], calib_targs[i], calib_targs_N[i]);
    }
    if (n_sims == 0){
        GOF_min = GOF[0];
        best_params = calib_params[0];
        best_output = saved_output[0];
    } else {
        GOF_min_run = GOF[n_sims];
        if (GOF_min_run <= GOF_min){
            GOF_min = GOF_min_run;
            best_params = calib_params[n_sims];
            best_output = saved_output[n_sims];
        } else {
            calibrate::GetProbAcceptance (GOF_min_run, GOF_min, n_sims);
            if (rand < ProbAcceptance){
                GOF_min = GOF_min_run;
                best_params = calib_params[n_sims];
                best_output = saved_output[n_sims];
            }
        }
    }
}

std::vector<double> calibrate::loadCalibData(int n_params, int n_sim) {

    double logmean;

    if(n_sim == 0){
        for (int i = 0; i < n_params; i++){
            switch(multipliers_type[i]){
                case prob:
                    calib_params[n_sim][i] = rnormal_trunc (multipliers[i][0], multipliers[i][1], 1, 0);
                    break;
                case RR:
                    logmean = log(multipliers[i][0]);
                    calib_params[n_sim][i] = rlognormal (logmean, multipliers[i][1]);
                    break;
                case Unif:
                    calib_params[n_sim][i] = runif (0, 100);
                    break;
            }
        }
    } else {
        for (int i = 0; i < n_params; i++){
            switch(multipliers_type[i]){
                case prob:
                    calib_params[n_sim][i] = rnormal_trunc (best_params[i], multipliers[i][1], 1, 0);
                    break;
                case RR:
                    logmean = log(best_params[i]);
                    calib_params[n_sim][i] = rlognormal (logmean, multipliers[i][1]);
                    break;
                case Unif:
                    calib_params[n_sim][i] = rnormal_trunc (best_params[i], multipliers[i][1], 100, 0);
                    break;
            }
        }
    }

    return(calib_params[n_sim]);
}

double calibrate::WeightedDistance(double data, double mean, double N) {
    double distance = pow((data - mean)/N,2);
    return distance;
}

double calibrate::rlognormal(double mu, double sigma) {
    std::random_device rdev{};
    std::default_random_engine generator{rdev()};
    std::lognormal_distribution<double> distribution(mu, sigma);
    double mult = distribution(generator);
    return(mult);
}

double calibrate::rnormal_trunc(double mu, double sigma, double upper, double lower) {
    std::random_device rdev{};
    std::default_random_engine generator{rdev()};
    std::normal_distribution<double> distribution(mu, sigma);
    double prob = distribution(generator);
    while (prob < lower || prob > upper){
        prob = distribution(generator);
    }
    return(prob);
}

int calibrate::runif(double lower, double upper) {
    std::random_device rdev{};
    std::default_random_engine generator{rdev()};
    std::uniform_int_distribution<int> distribution(lower, upper);
    int mult = distribution(generator);
    return(mult);
}

void calibrate::GetProbAcceptance(double neighbor, double current, int n_sims) {
    double temperature = (-0.0299*n_sims) + 30;
    ProbAcceptance = exp((current - neighbor) / temperature);
}