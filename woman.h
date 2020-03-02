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

    int CurrentYear;
    int CurrentAge;
    int CurrentMonth;
    int CurrentMonthAge;
    bool Alive;
    int Cycle;

    enum caT {Stage0, Stage1, Stage2, Stage3, Stage1d, Stage2d, Stage3d};
    enum hpvT {No = 0, Low = 1, otherHR = 2, High16 = 3, High18 = 4, High31 = 5, High33 = 6, High45 = 7, High52 = 8, High58 = 9};
    caT cancerstage;
    std::vector<hpvT> HPVinfections;
    std::vector<int> HPVinfectionTimer;

    std::vector<hpvT> HPVLatentinfections;
    std::vector<int> HPVLatentinfectionTimer;
    std::vector<hpvT> Dormantinfections;
    std::vector<int> DormancyTimer;
    int LatentTimer;

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

    int hpvlo_ageimmunity;
    int hpv16_ageimmunity;
    int hpv18_ageimmunity;
    int hpv31_ageimmunity;
    int hpv33_ageimmunity;
    int hpv45_ageimmunity;
    int hpv52_ageimmunity;
    int hpv58_ageimmunity;
    int hpvotherHR_ageimmunity;

    bool wasHPVloflag;
    bool wasHPVotherHRflag;
    bool wasHPV16flag;
    bool wasHPV18flag;
    bool wasHPV31flag;
    bool wasHPV33flag;
    bool wasHPV45flag;
    bool wasHPV52flag;
    bool wasHPV58flag;

    double immune_deg_LR;
    double immune_deg_otherHR;
    double immune_deg_16;
    double immune_deg_18;
    double immune_deg_31;
    double immune_deg_33;
    double immune_deg_45;
    double immune_deg_52;
    double immune_deg_58;


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

    int CIN_dormant_16;
    int CIN_dormant_18;
    int CIN_dormant_31;
    int CIN_dormant_33;
    int CIN_dormant_45;
    int CIN_dormant_52;
    int CIN_dormant_58;
    int CIN_dormant_oHR;

    int CIN_latent_16;
    int CIN_latent_18;
    int CIN_latent_31;
    int CIN_latent_33;
    int CIN_latent_45;
    int CIN_latent_52;
    int CIN_latent_58;
    int CIN_latent_oHR;

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

    int year16;
    int year18;
    int year31;
    int year33;
    int year45;
    int year52;
    int year58;
    int yearoHR;
    double rand;

    Woman(int Age, int StartYear); // constructor used for calibration
    Woman(int Age, int StartYear, helper &help, double ScreenCoverage); // constructor used for analysis
    void reset(int Age, int StartYear, helper &help, double ScreenCoverage);
    ~Woman();

};

#endif //HPV_WOMAN_H

