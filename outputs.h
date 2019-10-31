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
    IntMatrix hpvscreens;
    IntMatrix papscreens;
    IntMatrix vaccines;
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

    Output(Inputs &Tables, int y);
    ~Output(void);

    void createTrace(Woman &Data, int y);
    void writeCohort(std::string *Outdir, int ModelStartAge, int ModelStopAge, int TotalSimYears);
    void createCalibOutput(int y);
    void calcDwellTime(Woman &Data);
    void writeDwellTime(std::string *Outdir);
    void writeCalibOutput(std::string *Outdir, std::string calib_targs_names);

};


#endif //HPV_OUTPUTS_H
