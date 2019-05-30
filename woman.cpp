//
// Created by Jamie Cohen on 11/14/17.
//

//
//  woman.cpp
//  HIVHPV
//
//

#include "woman.h"
using namespace std;



//Value constructor

Woman::Woman(int Age, int StartYear) {

    hpvlo = false;
    hpv16 = false;
    hpv18 = false;
    hpv31 = false;
    hpv33 = false;
    hpv45 = false;
    hpv52 = false;
    hpv58 = false;
    hpvotherHR = false;

    wasHPV16flag = false;
    wasHPV18flag = false;
    wasHPV31flag = false;
    wasHPV33flag = false;
    wasHPV45flag = false;
    wasHPV52flag = false;
    wasHPV58flag = false;
    wasHPVloflag = false;
    wasHPVotherHRflag = false;

    HPVinfections.clear();
    HPVinfectionTimer.clear();
    CIN2Lesions.clear();
    CIN3Lesions.clear();
    CIN2LesionTimer.clear();
    CIN3LesionTimer.clear();

    CurrentAge = Age;
    CurrentYear = StartYear;
    CurrentMonthAge = Age*12;
    CurrentMonth = StartYear*12;
    Alive = true;
    cancerstage = caT::Stage0;
    hpv = false;

    cancer = false;
    ca1Timer = 0;
    ca2Timer = 0;
    ca3Timer = 0;
    hpvstart = false;
    hpvcolpostart = false;
    hpvage = {0};
    hpvcolpoage = {0};
    hpvtest = 0;
    hpvcolpotest = 0;
    hpv_first_hiv = 0;
    hpvcolpo_first_hiv = 0;
    vaccinated = true;
    completevaccine = true;
    vaccineage = {9};
    nextscreenage = 0;
}

Woman::~Woman()
= default;



