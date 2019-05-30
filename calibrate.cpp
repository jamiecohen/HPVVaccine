//
// Created by Jamie Cohen on 3/4/19.
//

#include "calibrate.h"

using namespace std;


calibrate::calibrate(int n_sims, int n_params, int n_targs) {

    calib_targs.resize (n_targs);
    calib_targs_SD.resize (n_targs);

    multipliers.resize(n_params);
    for(int i = 0; i < n_params; i++){
        multipliers[i].resize(4);
    }

    calib_params.resize (n_sims);
    for (int i = 0; i < calib_params.size(); i++){
        calib_params[i].resize (n_params);
    }

    saved_output.resize (n_sims);
    for (int i = 0; i < saved_output.size(); i++){
        saved_output[i].resize (n_targs);
    }

    best_params.resize (n_params);
    best_output.resize(n_targs);

    GOF.clear();

    tuned_SD.resize(n_params);

}

calibrate::~calibrate(void) {

}

void calibrate::CalculateGOF(int n_sims) {

    GOF.push_back (WeightedDistance (saved_output[n_sims][0], calib_targs[0], calib_targs_SD[0]));
    for (int i = 1; i < calib_targs.size(); i ++){
        GOF[n_sims] += WeightedDistance (saved_output[n_sims][i], calib_targs[i], calib_targs_SD[i]);
    }


    if (n_sims == 0){
        GOF_min = GOF[0];
        best_params = calib_params[0];
        best_output = saved_output[0];

    } else {

        auto it = std::min_element(std::begin(GOF), std::end(GOF));
        int index = distance(GOF.begin(), it);
        GOF_min_run = GOF[index];
        if (GOF_min_run < GOF_min){
            GOF_min = GOF_min_run;
            best_params = calib_params[index];
            best_output = saved_output[index];
        }
    }
}

std::vector<double> calibrate::loadCalibData(int n_params, int n_sim, int tuning_factor) {

    if(n_sim == 0){

        for (int i = 0; i < n_params; i ++ ){
            calib_params[n_sim][i] = rnormal_trunc (multipliers[i][0], multipliers[i][3], multipliers[i][2], multipliers[i][1]);
        }

    } else {
        tuned_SD = tuningparam (n_sim, n_params, tuning_factor);

        for (int i = 0; i < n_params; i ++ ){
            calib_params[n_sim][i] = rnormal_trunc (best_params[i], tuned_SD[i], multipliers[i][2], multipliers[i][1]);
        }
    }

    return(calib_params[n_sim]);
}

double calibrate::WeightedDistance(double data, double mean, double SD) {
    double distance = pow((data - mean)/(SD * 2),2);
    return distance;
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

vector<double> calibrate::tuningparam(int n_sims, int n_param, int tuning_factor) {
    vector<double> newSD;
    for (int i = 0; i < n_param; i++){
        newSD.push_back (multipliers[i][3]/pow(tuning_factor,n_sims));
    }

    return newSD;
}