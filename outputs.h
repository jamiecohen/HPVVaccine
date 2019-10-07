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


class Output {
public:

    IntMatrix costs;
    double discountrate;
    IntMatrix trace;
    DoubleMatrix inc;
    vector<double> prev;
    vector<int> TotalPrevCancer;
    vector<int> TotalCancer;
    vector<int> TotalDetectedCancer;
    vector<int> TotalCancer_1618;
    vector<int> TotalCancer_nonavalent;
    vector<int> TotalCancer_allother;
    vector<int> TotalCancerDenom;
    int totaldeadcancer;
    vector<int> TotalHPV;
    vector<int> total_alive;
    vector<double> LE;
    vector<double> cost;
    vector<double> DALY;
    vector<double> YLL;
    vector<double> YLD;
    vector<double> calib;
    vector<double> CaIncStandardized;
    DoubleMatrix totalcancer_mort;
    vector<int> HPV16count;
    vector<int> HPV18count;
    vector<int> HPVcount;
    vector<int> HPV16denom;
    vector<int> HPV18denom;
    vector<int> HPVdenom;

    vector<int> CAdead;
    vector<int> count;
    vector<int> CIN2count;
    vector<int> CIN3count;
    vector<int> CAcount;
    vector<int> DetectedCAcount;
    vector<int> denom;
    vector<int> CIN2denom;
    vector<int> CIN3denom;
    vector<int> CAdenom;
    vector<int> CIN2HIVneg;
    vector<int> CIN3HIVneg;
    unsigned int cancerHIVneg;
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
    unsigned int CIN216;
    unsigned int CIN218;
    unsigned int CIN231;
    unsigned int CIN233;
    unsigned int CIN245;
    unsigned int CIN252;
    unsigned int CIN258;
    unsigned int CIN2otherHR;
    unsigned int CIN2total;
    unsigned int CIN3total;
    vector<int> hpvscreens;
    vector<int> papscreens;
    vector<unsigned int> vaccines;
    int DwellTime_HPV_CIN_16_num;
    int DwellTime_HPV_CIN_18_num;
    int DwellTime_HPV_CIN_31_num;
    int DwellTime_HPV_CIN_33_num;
    int DwellTime_HPV_CIN_45_num;
    int DwellTime_HPV_CIN_52_num;
    int DwellTime_HPV_CIN_58_num;
    int DwellTime_HPV_CIN_oHR_num;
    int DwellTime_CIN_CA_16_num;
    int DwellTime_CIN_CA_18_num;
    int DwellTime_CIN_CA_31_num;
    int DwellTime_CIN_CA_33_num;
    int DwellTime_CIN_CA_45_num;
    int DwellTime_CIN_CA_52_num;
    int DwellTime_CIN_CA_58_num;
    int DwellTime_CIN_CA_oHR_num;
    int DwellTime_CA_16_denom;
    int DwellTime_CA_18_denom;
    int DwellTime_CA_31_denom;
    int DwellTime_CA_33_denom;
    int DwellTime_CA_45_denom;
    int DwellTime_CA_52_denom;
    int DwellTime_CA_58_denom;
    int DwellTime_CA_oHR_denom;
    int DwellTime_CA_detected_denom;
    int DwellTime_CA_detected_num;
    int causalHPV16age;
    int causalHPV18age;
    int causalHPV31age;
    int causalHPV33age;
    int causalHPV45age;
    int causalHPV52age;
    int causalHPV58age;
    int causalHPVoHRage;
    double QALY;
    double discQALY;
    double TotalCost;
    double discDALY;

    Output(Inputs &Tables, int y);
    ~Output(void);

    void createTrace(Woman &Datath);
    void createInc(Inputs &Tables);
    void writeCohort(std::string *Outdir, int ModelStartAge, int ModelStopAge, int SimStartYear, int SimYears);
    void calcLE(Woman &Data, Inputs &Tables, int y);
    void createCalibOutput();
    void calcDwellTime(Woman &Data);
    void writeDwellTime(std::string *Outdir);
    void writeCalibOutput(std::string *Outdir);

};


#endif //HPV_OUTPUTS_H
