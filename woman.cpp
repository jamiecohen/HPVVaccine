//
// Created by Jamie Cohen on 11/14/17.
//
//
//  woman.cpp
//  HPV
//
//

#include "woman.h"
using namespace std;


//Value constructor

Woman::Woman(int Age, int StartYear) {

    CIN16 = 0;
    CIN18 = 0;
    CIN31 = 0;
    CIN33 = 0;
    CIN45 = 0;
    CIN52 = 0;
    CIN58 = 0;
    CINoHR = 0;
    CA16= 0;
    CA18= 0;
    CA31= 0;
    CA33= 0;
    CA45= 0;
    CA52= 0;
    CA58= 0;
    CAoHR= 0;
    age16 = 0;
    age18 = 0;
    age31 = 0;
    age33 = 0;
    age45 = 0;
    age52 = 0;
    age58 = 0;
    ageoHR = 0;
    hpvlo_ageimmunity = 0;
    hpv16_ageimmunity = 0;
    hpv18_ageimmunity = 0;
    hpv31_ageimmunity = 0;
    hpv33_ageimmunity = 0;
    hpv45_ageimmunity = 0;
    hpv52_ageimmunity = 0;
    hpv58_ageimmunity = 0;
    hpvotherHR_ageimmunity = 0;
    hpvlo = false;
    hpv16 = false;
    hpv18 = false;
    hpv31 = false;
    hpv33 = false;
    hpv45 = false;
    hpv52 = false;
    hpv58 = false;
    hpvotherHR = false;
    hpvlo_seropos = false;
    hpv16_seropos = false;
    hpv18_seropos = false;
    hpv31_seropos = false;
    hpv33_seropos = false;
    hpv45_seropos = false;
    hpv52_seropos = false;
    hpv58_seropos = false;
    hpvotherHR_seropos = false;
    wasHPV16flag = false;
    wasHPV18flag = false;
    wasHPV31flag = false;
    wasHPV33flag = false;
    wasHPV45flag = false;
    wasHPV52flag = false;
    wasHPV58flag = false;
    wasHPVloflag = false;
    wasHPVotherHRflag = false;
    immune_deg_LR = 1;
    immune_deg_otherHR = 1;
    immune_deg_16 = 1;
    immune_deg_18 = 1;
    immune_deg_31 = 1;
    immune_deg_33 = 1;
    immune_deg_45 = 1;
    immune_deg_52 = 1;
    immune_deg_58 = 1;
    HPVLatentinfections.clear();
    HPVLatentinfectionTimer.clear();
    HPVinfections.clear();
    HPVinfectionTimer.clear();
    CIN2Lesions.clear();
    CIN3Lesions.clear();
    CIN2LesionTimer.clear();
    CIN3LesionTimer.clear();
    CurrentAge = Age;
    CurrentYear = StartYear;
    Alive = true;
    cancer = false;
    ca1Timer = 0;
    ca2Timer = 0;
    ca3Timer = 0;
    screenstart = false;
    screenage = {0};
    screens = 0;
    screen_first = 0;
    completevaccine = false;
    vaccineage = 9;
    nextscreenage = 0;
    ScreenAccess = false;
    cancerstage = caT::Stage0;
}

Woman::Woman(int Age, int StartYear, helper &help, double ScreenCoverage, int VaccineAge, double vaccinecov) {
    CIN16 = 0;
    CIN18 = 0;
    CIN31 = 0;
    CIN33 = 0;
    CIN45 = 0;
    CIN52 = 0;
    CIN58 = 0;
    CINoHR = 0;
    CA16= 0;
    CA18= 0;
    CA31= 0;
    CA33= 0;
    CA45= 0;
    CA52= 0;
    CA58= 0;
    CAoHR= 0;
    age16 = 0;
    age18 = 0;
    age31 = 0;
    age33 = 0;
    age45 = 0;
    age52 = 0;
    age58 = 0;
    ageoHR = 0;
    hpvlo = false;
    hpv16 = false;
    hpv18 = false;
    hpv31 = false;
    hpv33 = false;
    hpv45 = false;
    hpv52 = false;
    hpv58 = false;
    hpvotherHR = false;
    hpvlo_seropos = false;
    hpv16_seropos = false;
    hpv18_seropos = false;
    hpv31_seropos = false;
    hpv33_seropos = false;
    hpv45_seropos = false;
    hpv52_seropos = false;
    hpv58_seropos = false;
    hpvotherHR_seropos = false;
    wasHPV16flag = false;
    wasHPV18flag = false;
    wasHPV31flag = false;
    wasHPV33flag = false;
    wasHPV45flag = false;
    wasHPV52flag = false;
    wasHPV58flag = false;
    wasHPVloflag = false;
    wasHPVotherHRflag = false;
    immune_deg_LR = 1;
    immune_deg_otherHR = 1;
    immune_deg_16 = 1;
    immune_deg_18 = 1;
    immune_deg_31 = 1;
    immune_deg_33 = 1;
    immune_deg_45 = 1;
    immune_deg_52 = 1;
    immune_deg_58 = 1;
    hpvlo_ageimmunity = 0;
    hpv16_ageimmunity = 0;
    hpv18_ageimmunity = 0;
    hpv31_ageimmunity = 0;
    hpv33_ageimmunity = 0;
    hpv45_ageimmunity = 0;
    hpv52_ageimmunity = 0;
    hpv58_ageimmunity = 0;
    hpvotherHR_ageimmunity = 0;
    HPVLatentinfections.clear();
    HPVLatentinfectionTimer.clear();
    HPVinfections.clear();
    HPVinfectionTimer.clear();
    CIN2Lesions.clear();
    CIN3Lesions.clear();
    CIN2LesionTimer.clear();
    CIN3LesionTimer.clear();
    CurrentAge = Age;
    CurrentYear = StartYear;
    Alive = true;
    cancerstage = caT::Stage0;
    cancer = false;
    ca1Timer = 0;
    ca2Timer = 0;
    ca3Timer = 0;
    screenstart = false;
    screenage = {0};
    screens = 0;
    screen_first = 0;
    nextscreenage = 0;
    rand = help.getrand ();
    ScreenAccess = rand < ScreenCoverage;
    rand = help.getrand ();
    if (rand < vaccinecov){
        completevaccine = true;
        vaccineage = VaccineAge;
    } else {
        completevaccine = false;
    }
}

void Woman::reset(int Age, int StartYear, helper &help, double ScreenCoverage, int VaccineAge, double vaccinecov) {
    CIN16 = 0;
    CIN18 = 0;
    CIN31 = 0;
    CIN33 = 0;
    CIN45 = 0;
    CIN52 = 0;
    CIN58 = 0;
    CINoHR = 0;
    CA16= 0;
    CA18= 0;
    CA31= 0;
    CA33= 0;
    CA45= 0;
    CA52= 0;
    CA58= 0;
    CAoHR= 0;
    age16 = 0;
    age18 = 0;
    age31 = 0;
    age33 = 0;
    age45 = 0;
    age52 = 0;
    age58 = 0;
    ageoHR = 0;
    hpvlo = false;
    hpv16 = false;
    hpv18 = false;
    hpv31 = false;
    hpv33 = false;
    hpv45 = false;
    hpv52 = false;
    hpv58 = false;
    hpvotherHR = false;
    hpvlo_seropos = false;
    hpv16_seropos = false;
    hpv18_seropos = false;
    hpv31_seropos = false;
    hpv33_seropos = false;
    hpv45_seropos = false;
    hpv52_seropos = false;
    hpv58_seropos = false;
    hpvotherHR_seropos = false;
    wasHPV16flag = false;
    wasHPV18flag = false;
    wasHPV31flag = false;
    wasHPV33flag = false;
    wasHPV45flag = false;
    wasHPV52flag = false;
    wasHPV58flag = false;
    wasHPVloflag = false;
    wasHPVotherHRflag = false;
    immune_deg_LR = 1;
    immune_deg_otherHR = 1;
    immune_deg_16 = 1;
    immune_deg_18 = 1;
    immune_deg_31 = 1;
    immune_deg_33 = 1;
    immune_deg_45 = 1;
    immune_deg_52 = 1;
    immune_deg_58 = 1;
    hpvlo_ageimmunity = 0;
    hpv16_ageimmunity = 0;
    hpv18_ageimmunity = 0;
    hpv31_ageimmunity = 0;
    hpv33_ageimmunity = 0;
    hpv45_ageimmunity = 0;
    hpv52_ageimmunity = 0;
    hpv58_ageimmunity = 0;
    hpvotherHR_ageimmunity = 0;
    HPVLatentinfections.clear();
    HPVLatentinfectionTimer.clear();
    HPVinfections.clear();
    HPVinfectionTimer.clear();
    CIN2Lesions.clear();
    CIN3Lesions.clear();
    CIN2LesionTimer.clear();
    CIN3LesionTimer.clear();
    CurrentAge = Age;
    CurrentYear = StartYear;
    Alive = true;
    cancerstage = caT::Stage0;
    cancer = false;
    ca1Timer = 0;
    ca2Timer = 0;
    ca3Timer = 0;
    screenstart = false;
    screenage = {0};
    screens = 0;
    screen_first = 0;
    nextscreenage = 0;
    rand = help.getrand ();
    ScreenAccess = rand < ScreenCoverage;
    rand = help.getrand ();
    if (rand < vaccinecov){
        completevaccine = true;
        vaccineage = VaccineAge;
    } else {
        completevaccine = false;
    }
}

Woman::~Woman()
= default;



