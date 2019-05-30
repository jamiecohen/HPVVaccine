//
// Created by Jamie Cohen on 11/14/17.
//

#ifndef HPVVaccine_WOMAN_H
#define HPVVaccine_WOMAN_H



#include <vector>
#include <ctgmath>
#include <cstdlib>
#include <random>


class Woman {
public:

    enum caT {Stage0 = 0, Stage1 = 1, Stage2 = 2, Stage3 = 3, Stage1d = 4, Stage2d = 5, Stage3d = 6};

    enum HealthState {HIV = 1, HIVHPV = 2,
        HIVCIN2 = 3, HIVCIN3 = 4,
        HIVCA1 = 5,  HIVCA2 = 6,
        HIVCA3 = 7,
        HIVCA1d = 8,  HIVCA2d = 9,
        HIVCA3d = 10,
        Dead = 11, DeadCA = 12,
        DeadHIV = 13};

    enum hpvT {No = 0, Low = 1, otherHR = 2, High16, High18, High31, High33, High45, High52, High58};

    std::vector<hpvT> CIN2Lesions;
    std::vector<hpvT> HPVinfections;
    std::vector<int> HPVinfectionTimer;
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

    bool wasHPVloflag;
    bool wasHPVotherHRflag;
    bool wasHPV16flag;
    bool wasHPV18flag;
    bool wasHPV31flag;
    bool wasHPV33flag;
    bool wasHPV45flag;
    bool wasHPV52flag;
    bool wasHPV58flag;

    int CurrentMonthAge;
    int CurrentYear;
    int CurrentMonth;
    int CurrentAge;
    bool    Alive;
    int Cycle;
    bool hpv;

    bool cancer;
    int ca1Timer;
    int ca2Timer;
    int ca3Timer;
    bool hpvstart;
    bool hpvcolpostart;

    std::vector<int> hpvage;
    std::vector<int> hpvcolpoage;
    int hpvtest;
    int hpvcolpotest;
    bool ScreenAccess;
    bool vaccinated;
    bool completevaccine;
    bool VaccineCoverage;
    std::vector<int> vaccineage;
    int hpv_first_hiv;
    int hpvcolpo_first_hiv;
    int nextscreenage;

    caT cancerstage;

    Woman(int Age, int StartYear);
    ~Woman(void);



};

#endif //HIVHPV_WOMAN_H

