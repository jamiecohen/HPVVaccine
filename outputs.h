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

    double discountrate;
    IntMatrix trace;
    DoubleMatrix inc;
    vector<double> prev;
    vector<int> TotalPrevCancer;
    vector<int> TotalCancer;
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
    double CaIncStandardized;
    DoubleMatrix totalcancer_mort;
    vector<int> HIVCAdead;
    vector<int> HIVcount;
    vector<int> HIVHPVcount;
    vector<int> HIVCIN2count;
    vector<int> HIVCIN3count;
    vector<int> HIVCAcount;
    vector<int> HIVdenom;
    vector<int> HIVHPVdenom;
    vector<int> HIVCIN2denom;
    vector<int> HIVCIN3denom;
    vector<int> HIVCAdenom;
    vector<int> CIN2HIVpos;
    vector<int> CIN3HIVpos;
    unsigned int cancerHIVpos;
    unsigned int CAotherHRHIV;
    unsigned int CA1618HIV;
    unsigned int CAhigh5HIV;
    unsigned int CIN21618HIV;
    unsigned int CIN31618HIV;
    unsigned int CIN2high5HIV;
    unsigned int CIN3high5HIV;
    unsigned int CIN2otherHRHIV;
    unsigned int CIN3otherHRHIV;
    unsigned int CIN2LRHIV;
    unsigned int CIN3LRHIV;
    unsigned int CIN2HIVpostotal;
    unsigned int CIN3HIVpostotal;
    vector<int> hpvscreens;
    vector<int> papscreens;
    vector<int> viascreens;
    vector<int> hpvcolposcreens;
    vector<unsigned int> vaccines;

    double QALY;
    double discQALY;
    double TotalCost;
    double discDALY;

    Output(Inputs &Tables, int y);
    ~Output(void);

    void createTrace(Woman &Data, int i);
    void createInc(Inputs &Tables);
    void writeCohort(std::string *Outdir, int ModelStartAge, int ModelStopAge, int SimYears);
    void calcLE(Woman &Data, Inputs &Tables, int y);
    void createCalibOutput();

};


#endif //HIVHPV_OUTPUTS_H
