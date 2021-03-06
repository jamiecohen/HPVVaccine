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

Woman::Woman(unsigned int Age, unsigned int StartYear) {

    CIN16 = 0;
    CIN18 = 0;
    CIN31 = 0;
    CIN33 = 0;
    CIN45 = 0;
    CIN52 = 0;
    CIN58 = 0;
    CINoHR = 0;
    CIN_dormant_16 = 0;
    CIN_dormant_18 = 0;
    CIN_dormant_31 = 0;
    CIN_dormant_33 = 0;
    CIN_dormant_45 = 0;
    CIN_dormant_52 = 0;
    CIN_dormant_58 = 0;
    CIN_dormant_oHR = 0;
    CIN_latent_16 = 0;
    CIN_latent_18 = 0;
    CIN_latent_31 = 0;
    CIN_latent_33 = 0;
    CIN_latent_45 = 0;
    CIN_latent_52 = 0;
    CIN_latent_58 = 0;
    CIN_latent_oHR = 0;
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
    HPVLatentinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                           hpvT::High52, hpvT::High58, hpvT::otherHR};
    HPVLatentinfectionTimer.clear();
    for (int i = 0; i < 9; i++){
        HPVLatentinfectionTimer.push_back(0);
    }
    HPVinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                     hpvT::High52, hpvT::High58, hpvT::otherHR};
    HPVinfectionTimer.clear();
    for (int i = 0; i < 9; i++){
        HPVinfectionTimer.push_back(0);
    }
    Dormantinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                         hpvT::High52, hpvT::High58, hpvT::otherHR};
    DormancyTimer.clear();
    for (int i = 0; i < 9; i++){
        DormancyTimer.push_back(0);
    }
    AgeClearedHPV.clear();
    for (int i = 0; i < 9; i++){
        AgeClearedHPV.push_back(0);
    }
    LatentTimer.clear();
    for (int i = 0; i < 9; i++){
        LatentTimer.push_back(0);
    }
    CIN2Lesions.clear();
    CIN3Lesions.clear();
    CIN2LesionTimer.clear();
    CIN3LesionTimer.clear();
    CurrentAge = Age;
    CurrentYear = StartYear;
    CurrentMonthAge = Age*12;
    CurrentMonth = StartYear*12;
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

Woman::Woman(unsigned int Age, unsigned int StartYear, helper &help, double ScreenCoverage) {
    CIN16 = 0;
    CIN18 = 0;
    CIN31 = 0;
    CIN33 = 0;
    CIN45 = 0;
    CIN52 = 0;
    CIN58 = 0;
    CINoHR = 0;
    CIN_dormant_16 = 0;
    CIN_dormant_18 = 0;
    CIN_dormant_31 = 0;
    CIN_dormant_33 = 0;
    CIN_dormant_45 = 0;
    CIN_dormant_52 = 0;
    CIN_dormant_58 = 0;
    CIN_dormant_oHR = 0;

    CIN_latent_16 = 0;
    CIN_latent_18 = 0;
    CIN_latent_31 = 0;
    CIN_latent_33 = 0;
    CIN_latent_45 = 0;
    CIN_latent_52 = 0;
    CIN_latent_58 = 0;
    CIN_latent_oHR = 0;
    
    CA16 = 0;
    CA18 = 0;
    CA31 = 0;
    CA33 = 0;
    CA45 = 0;
    CA52 = 0;
    CA58 = 0;
    CAoHR = 0;
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
    HPVLatentinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                           hpvT::High52, hpvT::High58, hpvT::otherHR};
    HPVLatentinfectionTimer.clear();
    for (int i = 0; i < 9; i++){
        HPVLatentinfectionTimer.push_back(0);
    }
    HPVinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                     hpvT::High52, hpvT::High58, hpvT::otherHR};
    HPVinfectionTimer.clear();
    for (int i = 0; i < 9; i++){
        HPVinfectionTimer.push_back(0);
    }
    Dormantinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                         hpvT::High52, hpvT::High58, hpvT::otherHR};
    DormancyTimer.clear();
    for (int i = 0; i < 9; i++){
        DormancyTimer.push_back(0);
    }
    AgeClearedHPV.clear();
    for (int i = 0; i < 9; i++){
        AgeClearedHPV.push_back(0);
    }
    LatentTimer.clear();
    for (int i = 0; i < 9; i++){
        LatentTimer.push_back(0);
    }
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
    completevaccine = false;
}

void Woman::reset(unsigned int Age, unsigned int StartYear, helper &help, double ScreenCoverage) {
    CIN16 = 0;
    CIN18 = 0;
    CIN31 = 0;
    CIN33 = 0;
    CIN45 = 0;
    CIN52 = 0;
    CIN58 = 0;
    CINoHR = 0;
    CIN_dormant_16 = 0;
    CIN_dormant_18 = 0;
    CIN_dormant_31 = 0;
    CIN_dormant_33 = 0;
    CIN_dormant_45 = 0;
    CIN_dormant_52 = 0;
    CIN_dormant_58 = 0;
    CIN_dormant_oHR = 0;
    CIN_latent_16 = 0;
    CIN_latent_18 = 0;
    CIN_latent_31 = 0;
    CIN_latent_33 = 0;
    CIN_latent_45 = 0;
    CIN_latent_52 = 0;
    CIN_latent_58 = 0;
    CIN_latent_oHR = 0;
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
    year16 = 0;
    year18 = 0;
    year31 = 0;
    year33 = 0;
    year45 = 0;
    year52 = 0;
    year58 = 0;
    yearoHR = 0;
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
    HPVLatentinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                           hpvT::High52, hpvT::High58, hpvT::otherHR};
    HPVLatentinfectionTimer.clear();
    for (int i = 0; i < 9; i++){
        HPVLatentinfectionTimer.push_back(0);
    }
    HPVinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                     hpvT::High52, hpvT::High58, hpvT::otherHR};
    HPVinfectionTimer.clear();
    for (int i = 0; i < 9; i++){
        HPVinfectionTimer.push_back(0);
    }
    Dormantinfections = {hpvT::Low, hpvT::High16, hpvT::High18, hpvT::High31, hpvT::High33, hpvT::High45,
                         hpvT::High52, hpvT::High58, hpvT::otherHR};
    DormancyTimer.clear();
    for (int i = 0; i < 9; i++){
        DormancyTimer.push_back(0);
    }
    AgeClearedHPV.clear();
    for (int i = 0; i < 9; i++){
        AgeClearedHPV.push_back(0);
    }
    LatentTimer.clear();
    for (int i = 0; i < 9; i++){
        LatentTimer.push_back(0);
    }
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
    completevaccine = false;
}

Woman::~Woman()
= default;



