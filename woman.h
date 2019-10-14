//
// Created by Jamie Cohen on 11/14/17.
//

#ifndef HPVVaccine_WOMAN_H
#define HPVVaccine_WOMAN_H




#include <ctgmath>
#include <cstdlib>
#include <random>
#include "helper.h"


class Woman {
public:

    enum caT {Stage0, Stage1, Stage2, Stage3, Stage1d, Stage2d, Stage3d};
    enum hpvT {No, Low, otherHR, High16, High18, High31, High33, High45, High52, High58};
    enum screenmethod {LBC = 0, CC = 1, HPVColpo = 2, HPVsnt = 3};
    screenmethod screenstrat;
    caT cancerstage;
    std::vector<hpvT> HPVinfections;
    std::vector<int> HPVinfectionTimer;
    std::vector<hpvT> CIN2Lesions;
    std::vector<hpvT> CIN3Lesions;
    std::vector<int> CIN2LesionTimer;
    std::vector<int> CIN3LesionTimer;
    bool hpvlo;
    bool hpv16;
    bool hpv18;
    bool hpv31;
    bool hpv33;
    bool hpv45;
    bool hpv52;
    bool hpv58;
    bool hpvotherHR;

    bool hpvlo_seropos;
    bool hpv16_seropos;
    bool hpv18_seropos;
    bool hpv31_seropos;
    bool hpv33_seropos;
    bool hpv45_seropos;
    bool hpv52_seropos;
    bool hpv58_seropos;
    bool hpvotherHR_seropos;

    int hpvlo_ageimmunity;
    int hpv16_ageimmunity;
    int hpv18_ageimmunity;
    int hpv31_ageimmunity;
    int hpv33_ageimmunity;
    int hpv45_ageimmunity;
    int hpv52_ageimmunity;
    int hpv58_ageimmunity;
    int hpvotherHR_ageimmunity;

    int hpvlo_ageseroconvert;
    int hpv16_ageseroconvert;
    int hpv18_ageseroconvert;
    int hpv31_ageseroconvert;
    int hpv33_ageseroconvert;
    int hpv45_ageseroconvert;
    int hpv52_ageseroconvert;
    int hpv58_ageseroconvert;
    int hpvotherHR_ageseroconvert;

    bool wasHPVloflag;
    bool wasHPVotherHRflag;
    bool wasHPV16flag;
    bool wasHPV18flag;
    bool wasHPV31flag;
    bool wasHPV33flag;
    bool wasHPV45flag;
    bool wasHPV52flag;
    bool wasHPV58flag;
    int CurrentYear;
    int CurrentAge;
    bool    Alive;
    int Cycle;
    bool cancer;
    int ca1Timer;
    int ca2Timer;
    int ca3Timer;
    bool screenstart;
    std::vector<int> screenage;
    int screens;
    int screen_first;
    bool ScreenAccess;
    bool completevaccine;
    bool VaccineCoverage;
    int vaccineage;
    int vaccinedoses;
    int nextscreenage;
    int CIN16;
    int CIN18;
    int CIN31;
    int CIN33;
    int CIN45;
    int CIN52;
    int CIN58;
    int CINoHR;
    int CA16;
    int CA18;
    int CA31;
    int CA33;
    int CA45;
    int CA52;
    int CA58;
    int CAoHR;
    int age16;
    int age18;
    int age31;
    int age33;
    int age45;
    int age52;
    int age58;
    int ageoHR;
    double rand;

    Woman(int Age, int StartYear, double rand); // constructor used for calibration
    Woman(int Age, int StartYear, helper &help, double ScreenCoverage, int VaccineAge, std::vector<std::vector<double> > screenstats, double colpocov, double vaccinecov); // constructor used for analysis
    ~Woman();

};

#endif //HPV_WOMAN_H

