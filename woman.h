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

    unsigned int CurrentYear;
    unsigned int CurrentAge;
    unsigned int CurrentMonth;
    unsigned int CurrentMonthAge;
    bool Alive;
    unsigned int Cycle;

    enum caT {Stage0, Stage1, Stage2, Stage3, Stage1d, Stage2d, Stage3d};
    enum hpvT {No = 0, Low = 1, otherHR = 2, High16 = 3, High18 = 4, High31 = 5, High33 = 6, High45 = 7, High52 = 8, High58 = 9};
    caT cancerstage;
    std::vector<hpvT> HPVinfections;
    std::vector<unsigned int> HPVinfectionTimer;

    std::vector<hpvT> HPVLatentinfections;
    std::vector<unsigned int> HPVLatentinfectionTimer;
    std::vector<hpvT> Dormantinfections;
    std::vector<unsigned int> DormancyTimer;
    std::vector<unsigned int> AgeClearedHPV;
    unsigned int LatentTimer;

    std::vector<hpvT> CIN2Lesions;
    std::vector<hpvT> CIN3Lesions;
    std::vector<unsigned int> CIN2LesionTimer;
    std::vector<unsigned int> CIN3LesionTimer;
    bool hpvlo;
    bool hpv16;
    bool hpv18;
    bool hpv31;
    bool hpv33;
    bool hpv45;
    bool hpv52;
    bool hpv58;
    bool hpvotherHR;

    unsigned int hpvlo_ageimmunity;
    unsigned int hpv16_ageimmunity;
    unsigned int hpv18_ageimmunity;
    unsigned int hpv31_ageimmunity;
    unsigned int hpv33_ageimmunity;
    unsigned int hpv45_ageimmunity;
    unsigned int hpv52_ageimmunity;
    unsigned int hpv58_ageimmunity;
    unsigned int hpvotherHR_ageimmunity;

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
    unsigned int ca1Timer;
    unsigned int ca2Timer;
    unsigned int ca3Timer;
    bool screenstart;
    std::vector<unsigned int> screenage;
    unsigned int screens;
    unsigned int screen_first;
    bool ScreenAccess;
    bool completevaccine;
    bool VaccineCoverage;
    unsigned int vaccineage;
    unsigned int vaccinedoses;
    unsigned int nextscreenage;
    unsigned int CIN16;
    unsigned int CIN18;
    unsigned int CIN31;
    unsigned int CIN33;
    unsigned int CIN45;
    unsigned int CIN52;
    unsigned int CIN58;
    unsigned int CINoHR;

    unsigned int CIN_dormant_16;
    unsigned int CIN_dormant_18;
    unsigned int CIN_dormant_31;
    unsigned int CIN_dormant_33;
    unsigned int CIN_dormant_45;
    unsigned int CIN_dormant_52;
    unsigned int CIN_dormant_58;
    unsigned int CIN_dormant_oHR;

    unsigned int CIN_latent_16;
    unsigned int CIN_latent_18;
    unsigned int CIN_latent_31;
    unsigned int CIN_latent_33;
    unsigned int CIN_latent_45;
    unsigned int CIN_latent_52;
    unsigned int CIN_latent_58;
    unsigned int CIN_latent_oHR;

    unsigned int CA16;
    unsigned int CA18;
    unsigned int CA31;
    unsigned int CA33;
    unsigned int CA45;
    unsigned int CA52;
    unsigned int CA58;
    unsigned int CAoHR;
    unsigned int age16;
    unsigned int age18;
    unsigned int age31;
    unsigned int age33;
    unsigned int age45;
    unsigned int age52;
    unsigned int age58;
    unsigned int ageoHR;

    unsigned int year16;
    unsigned int year18;
    unsigned int year31;
    unsigned int year33;
    unsigned int year45;
    unsigned int year52;
    unsigned int year58;
    unsigned int yearoHR;
    double rand;

    Woman(unsigned int Age, unsigned int StartYear); // constructor used for calibration
    Woman(unsigned int Age, unsigned int StartYear, helper &help, double ScreenCoverage); // constructor used for analysis
    void reset(unsigned int Age, unsigned int StartYear, helper &help, double ScreenCoverage);
    ~Woman();

};

#endif //HPV_WOMAN_H

