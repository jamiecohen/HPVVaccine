//
// Created by Jamie Cohen on 11/29/17.
//

#ifndef HPVVaccine_OUTPUTS_H
#define HPVVaccine_OUTPUTS_H

#include "woman.h"
#include "inputs.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

typedef vector<vector<int> > IntMatrix;
typedef vector<vector<double> > DoubleMatrix;

typedef vector<vector<vector<int> > > Int3DMatrix;
typedef vector<vector<vector<double> > > Double3DMatrix;


class Output {
public:

    Int3DMatrix trace;
    Double3DMatrix inc;
    DoubleMatrix prev;
    IntMatrix TotalPrevCancer;
    IntMatrix TotalCancer;
    IntMatrix TotalDetectedCancer;
    IntMatrix TotalCancer_1618;
    IntMatrix TotalCancer_nonavalent;
    IntMatrix TotalCancer_allother;
    IntMatrix TotalCancerDenom;
    vector<int> TotalDetectedCancer_byyear;
    vector<int> CancerDenom_byyear;
    int totaldeadcancer;
    IntMatrix TotalHPV;
    IntMatrix total_alive;
    DoubleMatrix LE;
    vector<double > calib;
    DoubleMatrix CaIncStandardized;
    DoubleMatrix totalcancer_mort;
    IntMatrix HPV16count;
    IntMatrix HPV18count;
    IntMatrix HPVcount;
    IntMatrix HPV16denom;
    IntMatrix HPV18denom;
    IntMatrix HPVdenom;
    int CINdenom;
    int CINnum;

    IntMatrix CAdead;
    IntMatrix count;
    IntMatrix CIN2count;
    IntMatrix CIN3count;
    IntMatrix CAcount;
    IntMatrix DetectedCAcount;
    IntMatrix denom;
    IntMatrix CIN2denom;
    IntMatrix CIN3denom;
    IntMatrix CAdenom;
    IntMatrix CIN2HIVneg;
    IntMatrix CIN3HIVneg;
    unsigned int cancer;
    unsigned int CAotherHR;
    unsigned int CA16;
    unsigned int CA18;
    unsigned int CA31;
    unsigned int CA33;
    unsigned int CA45;
    unsigned int CA52;
    unsigned int CA58;
    unsigned int CIN316;
    unsigned int CIN318;
    unsigned int CIN331;
    unsigned int CIN333;
    unsigned int CIN345;
    unsigned int CIN352;
    unsigned int CIN358;
    unsigned int CIN3otherHR;
    unsigned int CIN3LR;
    unsigned int CIN216;
    unsigned int CIN218;
    unsigned int CIN231;
    unsigned int CIN233;
    unsigned int CIN245;
    unsigned int CIN252;
    unsigned int CIN258;
    unsigned int CIN2otherHR;
    unsigned int CIN2LR;
    unsigned int CIN2total;
    unsigned int CIN3total;
    IntMatrix hpvscreens;
    IntMatrix papscreens;
    IntMatrix vaccines;
    int DwellTime_HPV_CIN_16_num;
    int DwellTime_HPV_CIN_18_num;
    int DwellTime_HPV_CIN_hi5_num;
    int DwellTime_HPV_CIN_allhr_num;
    int Dormancy_HPV_CIN_16_num;
    int Dormancy_HPV_CIN_18_num;
    int Dormancy_HPV_CIN_hi5_num;
    int Dormancy_HPV_CIN_allhr_num;
    int Latency_HPV_CIN_16_num;
    int Latency_HPV_CIN_18_num;
    int Latency_HPV_CIN_hi5_num;
    int Latency_HPV_CIN_allhr_num;
    int DwellTime_CIN_CA_16_num;
    int DwellTime_CIN_CA_18_num;
    int DwellTime_CIN_CA_hi5_num;
    int DwellTime_CIN_CA_allhr_num;
    int DwellTime_CA_16_denom;
    int DwellTime_CA_18_denom;
    int DwellTime_CA_hi5_denom;
    int DwellTime_CA_allhr_denom;
    int DwellTime_CA_16_latent_denom;
    int DwellTime_CA_18_latent_denom;
    int DwellTime_CA_hi5_latent_denom;
    int DwellTime_CA_allhr_latent_denom;
    int DwellTime_CA_detected_denom;
    int DwellTime_CA_detected_num;
    int causalHPV16age;
    int causalHPV18age;
    int causalHPVhi5age;
    int causalHPVallhrage;
    int ageoHR;
    int age16;
    int age18;
    int age31;
    int age33;
    int age45;
    int age52;
    int age58;
    IntMatrix causalHPV16ageMatrix;
    IntMatrix causalHPV18ageMatrix;
    IntMatrix causalHPVhi5ageMatrix;
    IntMatrix causalHPVallhrageMatrix;

    vector<double> cost;
    vector<double> DALY;
    vector<double> YLL;
    vector<double> YLD;
    double TotalCost;
    double discDALY;
    double TotalDALY;
    double discCost;
    double discountrate;

    Output(Inputs &Tables, int y);
    ~Output(void);

    void createTrace(Woman &Data, int y);
    void writeInc(std::string *Outdir, int ModelStartAge, int ModelStopAge, int TotalSimYears);
    void writeCEA(std::string *Outdir, int ModelStopAge, int TotalSimYears);
    void writeMort(std::string *Outdir, int ModelStopAge, int TotalSimYears);
    void createTypeDist(Woman &Data);
    void createCalibOutput(int y);
    void calcDwellTime(Woman &Data);
    void writeDwellTime(std::string *Outdir, int TotalSimYears);
    void calcValidation(Woman &Data);
    void writeValidation(std::string *Outdir);
    void writeCalibOutput(std::string *Outdir, std::string calib_targs_names);
    void calcLE(Woman &Data, Inputs &Tables, int y);

};


#endif //HPV_OUTPUTS_H
