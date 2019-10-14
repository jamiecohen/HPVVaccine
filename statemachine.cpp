//
// Created by Jamie Cohen on 11/15/17.
//

#include "statemachine.h"

using namespace std;

StateMachine::StateMachine() = default;

void StateMachine::CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {
    if (Data.Alive) {
        StateMachine::GetMortality (Data, Tables);
        switch (Data.cancerstage) {
            case Woman::Stage1:
                rand = help.getrand ();
                if (rand < Tables.CA1_CA2) {
                    Data.cancerstage = Data.Stage2;
                    Data.ca2Timer++;
                } else if (rand < (Tables.CA1_CA2 + mCA)) {
                    Data.Alive = false;
                    Count.totaldeadcancer++;
                } else if (rand < (Tables.CA1_CA2 + mCA + Tables.pCA1_CA1D)) {
                    Data.cancerstage = Data.Stage1d;
                    Count.DwellTime_CA_detected_num += Data.ca1Timer;
                    Count.DwellTime_CA_detected_denom++;
                    StateMachine::CountDetectedCancer (Data, Count);
                    Data.ca1Timer++;
                    StateMachine::Colpo (Data, Tables, Count, y, help);
                } else {
                    Data.ca1Timer++;
                }
                break;
            case Woman::Stage2:
                rand = help.getrand ();
                if (rand < Tables.CA2_CA3) {
                    Data.cancerstage = Data.Stage3;
                    Data.ca3Timer++;
                } else if (rand < (Tables.CA2_CA3 + mCA)) {
                    Data.Alive = false;
                    Count.totaldeadcancer++;
                } else if (rand < (Tables.CA2_CA3 + mCA + Tables.pCA2_CA2D)) {
                    Data.cancerstage = Data.Stage2d;
                    StateMachine::CountDetectedCancer (Data, Count);
                    Count.DwellTime_CA_detected_num += Data.ca1Timer + Data.ca2Timer;
                    Count.DwellTime_CA_detected_denom++;
                    Data.ca2Timer++;
                    StateMachine::Colpo (Data, Tables, Count, y, help);
                } else {
                    Data.ca2Timer++;
                }
                break;
            case Woman::Stage3:
                rand = help.getrand ();
                if (rand < mCA) {
                    Data.Alive = false;
                    Count.totaldeadcancer++;
                } else if (rand < (mCA + Tables.pCA3_CA3D)) {
                    Data.cancerstage = Data.Stage3d;
                    StateMachine::CountDetectedCancer (Data, Count);
                    Count.DwellTime_CA_detected_num += Data.ca1Timer + Data.ca2Timer + Data.ca3Timer;
                    Count.DwellTime_CA_detected_denom++;
                    Data.ca3Timer++;
                    StateMachine::Colpo (Data, Tables, Count, y, help);
                } else {
                    Data.ca3Timer++;
                }
                break;
            case Woman::Stage1d:
                rand = help.getrand ();
                if (rand < mCA) {
                    Count.CAdead[Data.CurrentAge]++;
                    Count.totaldeadcancer++;
                    Data.Alive = false;
                } else {
                    Data.ca1Timer++;
                }
                break;
            case Woman::Stage2d:
                rand = help.getrand ();
                if (rand < mCA) {
                    Count.CAdead[Data.CurrentAge]++;
                    Count.totaldeadcancer++;
                    Data.Alive = false;
                } else {
                    Data.ca2Timer++;
                }
                break;
            case Woman::Stage3d:
                rand = help.getrand ();
                if (rand < mCA) {
                    Count.CAdead[Data.CurrentAge]++;
                    Count.totaldeadcancer++;
                    Data.Alive = false;
                } else {
                    Data.ca3Timer++;
                }
                break;
            default:
                break;
        }
    }
}

void StateMachine::HPVNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help) {

    if (Data.Alive) {
        StateMachine::CheckSeropositivity (Data, Tables, help);
        for (int i = 0; i < Data.HPVinfections.size (); i++) {
            StateMachine::GetLesionRisk (Data, Tables, i, Data.HPVinfections[i]);
            StateMachine::GetHPVClearanceRisk (Data, Tables, i, Data.HPVinfections[i]);
            switch (Data.HPVinfections[i]) {
                case Woman::No:
                    break;
                case Woman::Low:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN2Lesions.push_back (Woman::Low);
                        Data.CIN2LesionTimer.push_back (1);
                        StateMachine::CountCIN2 (Data, Count);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::Low);
                        Data.CIN3LesionTimer.push_back (1);
                        StateMachine::CountCIN3 (Data, Count);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 +
                                        pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::otherHR:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CINoHR = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN2 (Data, Count);
                        Data.CIN2Lesions.push_back (Woman::otherHR);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CINoHR = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN3 (Data, Count);
                        Data.CIN3Lesions.push_back (Woman::otherHR);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High16:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CIN16 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN2 (Data, Count);
                        Data.CIN2Lesions.push_back (Woman::High16);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN16 = Data.HPVinfectionTimer[i];
                        StateMachine::CountCIN3 (Data, Count);
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::High16);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High18:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.CIN18 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN2 (Data, Count);
                        Data.CIN2Lesions.push_back (Woman::High18);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN18 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN3 (Data, Count);
                        Data.CIN3Lesions.push_back (Woman::High18);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 +pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High31:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CIN31 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN2 (Data, Count);
                        Data.CIN2Lesions.push_back (Woman::High31);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN31 = Data.HPVinfectionTimer[i];
                        StateMachine::CountCIN3 (Data, Count);
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::High31);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High33:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CIN33 = Data.HPVinfectionTimer[i];
                        StateMachine::CountCIN2 (Data, Count);
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN2Lesions.push_back (Woman::High33);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN33 = Data.HPVinfectionTimer[i];
                        StateMachine::CountCIN3 (Data, Count);
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::High33);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High45:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CIN45 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN2 (Data, Count);
                        Data.CIN2Lesions.push_back (Woman::High45);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN45 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN3 (Data, Count);
                        Data.CIN3Lesions.push_back (Woman::High45);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High52:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CIN52 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN2 (Data, Count);
                        Data.CIN2Lesions.push_back (Woman::High52);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN52 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN3 (Data, Count);
                        Data.CIN3Lesions.push_back (Woman::High52);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High58:
                    rand = help.getrand ();
                    if (rand <  pHPV_CIN2) {
                        Data.CIN58 = Data.HPVinfectionTimer[i];
                        StateMachine::CountCIN2 (Data, Count);
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN2Lesions.push_back (Woman::High58);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3)) {
                        Data.CIN58 = Data.HPVinfectionTimer[i];
                        Data.HPVinfectionTimer[i]++;
                        StateMachine::CountCIN3 (Data, Count);
                        Data.CIN3Lesions.push_back (Woman::High58);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < ( pHPV_CIN2 + pHPV_CIN3 + pHPV_NL)) {
                        StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
            }
        }
    }
}

void StateMachine::NatHistory(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {
    if (Data.Alive) {
        if(Tables.WaningImmunity){
            CheckWaningImmunity (Data, Tables);
        }
        for(int i = 0; i < Data.HPVLatentinfections.size (); i ++) {
            Data.HPVLatentinfectionTimer[i]++;
        }
        StateMachine::GetVaccineEff (Data, Tables);
        if (Data.cancer) {
            CancerNatHistory (Data, Tables, Count, y, help);
        } else {
            if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
                StateMachine::StartCIN (Data, Count, Tables, help);
            }
            if (!Data.HPVinfections.empty ()) {
                StateMachine::HPVNatHistory (Data, Tables, Count, help);
            }
            StateMachine::AcquireHPVLow (Data, Count, Tables, help);
        }
    }
}

void StateMachine::HPVScreen(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {
    Data.screen_first = Tables.ScreenStartAge;
    ScreenFrequency = Tables.ScreenFrequency;
    if (!Data.screenstart) {
        Data.nextscreenage = Data.screen_first;
    }
    if (Data.Alive) {
        if (Data.CurrentAge >= Data.nextscreenage && Data.CurrentAge <= Tables.ScreenStopAge) {
            Data.screenstart = true;
            Data.screens++;
            Data.screenage.push_back (Data.CurrentAge);
            Data.nextscreenage = Data.CurrentAge + ScreenFrequency;
            Count.cost[y] += Tables.cHPVTest;
            Count.cost[y] += Tables.cReturnforResult;
            Count.cost[y] += Tables.cPtTime;
            Count.costs[y][4]++;
            Count.costs[y][1]++;
            Count.costs[y][5]++;
            if (Data.hpv16 || Data.hpv18 || Data.hpv31 || Data.hpv33 || Data.hpv45 ||
                Data.hpv52 || Data.hpv58 || Data.hpvotherHR) {
                StateMachine::Colpo (Data, Tables, Count, y, help);
            }
        }
    }
}

void StateMachine::CytoScreen(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {
    cPap = Tables.cPapLBCTest;
    Adequacy = Tables.AdequacyLBC;
    Data.screen_first = Tables.ScreenStartAge;
    ScreenFrequency = Tables.ScreenFrequency;
    if (!Data.screenstart) {
        Data.nextscreenage = Data.screen_first;
    }
    if (Data.Alive) {
        if (Data.CurrentAge >= Data.nextscreenage && Data.CurrentAge <= Tables.ScreenStopAge) {
            Data.nextscreenage = Data.CurrentAge + ScreenFrequency;
            Data.screens++;
            Data.nextscreenage = Data.CurrentAge + ScreenFrequency;
            Data.screen_first = Data.CurrentAge;
            Data.screenage.push_back (Data.CurrentAge);
            Count.cost[y] += cPap;
            Count.cost[y] += Tables.cReturnforResult;
            Count.cost[y] += Tables.cPtTime;
            Count.costs[y][4]++;
            Count.costs[y][1]++;
            Count.costs[y][5]++;
            rand = help.getrand ();
            if (rand < Adequacy) {
                Data.screens++;
                Data.screenage.push_back (Data.CurrentAge);
                Count.cost[y] += cPap;
                Count.cost[y] += Tables.cPtTime;
                Count.costs[y][4]++;
                Count.costs[y][1]++;
            }
            if (Data.cancer) {
                rand = help.getrand ();
                if (rand < Tables.cytosens_Ca) {
                    rand = help.getrand ();
                    if (rand < Tables.ScreenCompliance) {
                        StateMachine::Colpo (Data, Tables, Count, y, help);
                    }
                }
            } else {
                if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
                    rand = help.getrand ();
                    if (rand < Tables.cytosens_CIN) {
                        rand = help.getrand ();
                        if (rand < Tables.ScreenCompliance) {
                            StateMachine::Colpo (Data, Tables, Count, y, help);
                        }
                    }
                } else {
                    rand = help.getrand ();
                    if (rand < Tables.cytosens_NL) {
                        rand = help.getrand ();
                        if (rand < Tables.ScreenCompliance) {
                            StateMachine::Colpo (Data, Tables, Count, y, help);
                        }
                    }
                }
            }
        }
    }
}

void StateMachine::ClearHPV(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype) {
    int i = 0;
    while (i < Data.HPVinfections.size ()) {
        if (Data.HPVinfections[i] == genotype) {
            Data.HPVLatentinfections.push_back(genotype);
            Data.HPVLatentinfectionTimer.push_back(Data.HPVinfectionTimer[i]);
            Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
            Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
            i = Data.HPVinfections.size ();
        } else {
            i++;
        }
    }
    switch (genotype) {
        case Woman::No:
            break;
        case Woman::Low:
            Data.wasHPVloflag = true;
            Data.hpvlo = false;
            break;
        case Woman::otherHR:
            Data.wasHPVotherHRflag = true;
            Data.hpvotherHR = false;
            break;
        case Woman::High16:
            Data.wasHPV16flag = true;
            Data.hpv16 = false;
            break;
        case Woman::High18:
            Data.wasHPV18flag = true;
            Data.hpv18 = false;
            break;
        case Woman::High31:
            Data.wasHPV31flag = true;
            Data.hpv31 = false;
            break;
        case Woman::High33:
            Data.wasHPV33flag = true;
            Data.hpv33 = false;
            break;
        case Woman::High45:
            Data.wasHPV45flag = true;
            Data.hpv45 = false;
            break;
        case Woman::High52:
            Data.wasHPV52flag = true;
            Data.hpv52 = false;
            break;
        case Woman::High58:
            Data.wasHPV58flag = true;
            Data.hpv58 = false;
            break;
    }

    switch(Tables.ImmuneMechanism){
        case Inputs::Degree:
            StateMachine::GetImmuneDeg (Data, Tables, genotype);
            break;
        case Inputs::Factor:
            StateMachine::GetImmuneFactor (Data, Tables, help, genotype);
            break;
        case Inputs::Seropositivity:
            StateMachine::GetSeropositivity (Data, Tables, genotype);
            break;
    }

}

void StateMachine::StartCIN(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Data.cancer){
        for (int i = 0; i < Data.CIN3Lesions.size (); i++) {
            StateMachine::GetCIN3Risk (Data, Tables, i, Data.CIN3Lesions[i]);
            switch (Data.CIN3Lesions[i]) {
                case Woman::No:
                    break;
                case Woman::Low:
                    rand = help.getrand ();
                    if (rand < (pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::otherHR:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CAoHR = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High16:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA16 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High18:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA18 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High31:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA31 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High33:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA33 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High45:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA45 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High52:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA52 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
                case Woman::High58:
                    rand = help.getrand ();
                    if (rand < pCIN3_CA) {
                        Data.CA58 = Data.CIN3LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i]);
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                        }
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3LesionTimer[i]++;
                    }
                    break;
            }
        }
    }
    if(!Data.cancer){
        for (int i = 0; i < Data.CIN2Lesions.size (); i++) {
            StateMachine::GetCIN2Risk (Data, Tables, i, Data.CIN2Lesions[i]);
            switch (Data.CIN2Lesions[i]) {
                case Woman::High16:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA16 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::No:
                    break;
                case Woman::Low:
                    rand = help.getrand ();
                    if (rand < (pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::otherHR:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CAoHR = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High18:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA18 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High31:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA31 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High33:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA33 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High45:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA45 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High52:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA52 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High58:
                    rand = help.getrand ();
                    if (rand < pCIN2_CA) {
                        Data.CA58 = Data.CIN2LesionTimer[i];
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i]);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (pCIN2_CA + pCIN2_HPV)) {
                        rand = help.getrand ();
                        if (rand > Tables.pRegresstoHPV){
                            StateMachine::ClearHPV (Data, Tables, help, Data.CIN2Lesions[i]);
                        }
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
            }
        }
    }
}

void StateMachine::runPopulationYear(Woman &Data, Inputs &Tables, Output &Count, int y, int CurrentModelYear, bool calib, helper &help) {

    if (Data.Alive) {
        StateMachine::GetBackgroundMortality (Data, Tables, CurrentModelYear);
        rand = help.getrand ();
        if (rand < mASR) {
            Data.Alive = false;
        } else {
            if (!calib) {
                if (Data.ScreenAccess) {
                    StateMachine::HPVScreen (Data, Tables, Count, y, help);
                    StateMachine::CytoScreen (Data, Tables, Count, y, help);
                }
            }
            StateMachine::NatHistory (Data, Tables, Count, y, help);
        }

        Count.createTrace (Data);
        if (!calib) {
            Count.calcLE (Data, Tables, y);
        }

        if (Data.Alive) {
            Count.total_alive[Data.CurrentAge]++;
            Data.CurrentAge++;
            Data.CurrentYear++;
            Data.Cycle++;
        }
    }
}

void StateMachine::Cryo(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {

    Count.cost[y] += Tables.cPtTime;
    Count.cost[y] += Tables.cCryoVisit;
    Count.costs[y][1]++;
    Count.costs[y][8]++;
    Count.cost[y] += Tables.cCryoCIN23;
    Count.costs[y][9]++;

    if (Data.cancer) {
        switch (Data.cancerstage) {
            case Woman::Stage0:break;
            case Woman::Stage1:
                Data.cancerstage = Data.Stage1d;
                break;
            case Woman::Stage2:
                Data.cancerstage = Data.Stage2d;
                break;
            case Woman::Stage3:
                Data.cancerstage = Data.Stage3d;
                break;
            case Woman::Stage1d:break;
            case Woman::Stage2d:break;
            case Woman::Stage3d:break;
        }
    } else {
        if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.CryoSuccessRateCIN) {
                Data.CIN3Lesions.clear ();
                Data.CIN2Lesions.clear ();
                Data.CIN3LesionTimer.clear();
                Data.CIN2LesionTimer.clear();
                rand = help.getrand ();
                if (rand < Tables.CryoSuccessRateHPV) {
                    if (Data.hpv16) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High16);
                    }
                    if (Data.hpv18) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High18);
                    }
                    if (Data.hpv31) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High31);
                    }
                    if (Data.hpv33) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High33);
                    }
                    if (Data.hpv45) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High45);
                    }
                    if (Data.hpv52) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High52);
                    }
                    if (Data.hpv58) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High58);
                    }
                    if (Data.hpvotherHR) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::otherHR);
                    }
                    if (Data.hpvlo) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::Low);
                    }
                }
            }
        } else if (!Data.HPVinfections.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.CryoSuccessRateHPV) {
                if (Data.hpv16) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High16);
                }
                if (Data.hpv18) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High18);
                }
                if (Data.hpv31) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High31);
                }
                if (Data.hpv33) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High33);
                }
                if (Data.hpv45) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High45);
                }
                if (Data.hpv52) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High52);
                }
                if (Data.hpv58) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High58);
                }
                if (Data.hpvotherHR) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::otherHR);
                }
                if (Data.hpvlo) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::Low);
                }
            }
        }
    }
}

void StateMachine::LLETZ(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {

    Count.cost[y] += Tables.cPtTime;
    Count.cost[y] += Tables.cCryoVisit;
    Count.costs[y][1]++;
    Count.costs[y][8]++;
    Count.cost[y] += Tables.cLLETZ;
    Count.costs[y][10]++;

    if (Data.cancer) {
        switch (Data.cancerstage) {
            case Woman::Stage0:break;
            case Woman::Stage1:
                Data.cancerstage = Data.Stage1d;
                break;
            case Woman::Stage2:
                Data.cancerstage = Data.Stage2d;
                break;
            case Woman::Stage3:
                Data.cancerstage = Data.Stage3d;
                break;
            case Woman::Stage1d:break;
            case Woman::Stage2d:break;
            case Woman::Stage3d:break;
        }
    } else {
        if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.LLETZSuccessRateCIN) {
                Data.CIN3Lesions.clear ();
                Data.CIN2Lesions.clear ();
                Data.CIN3LesionTimer.clear();
                Data.CIN2LesionTimer.clear();
                rand = help.getrand ();
                if (rand < Tables.LLETZSuccessRateHPV) {
                    if (Data.hpv16) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High16);
                    }
                    if (Data.hpv18) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High18);
                    }
                    if (Data.hpv31) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High31);
                    }
                    if (Data.hpv33) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High33);
                    }
                    if (Data.hpv45) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High45);
                    }
                    if (Data.hpv52) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High52);
                    }
                    if (Data.hpv58) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::High58);
                    }
                    if (Data.hpvotherHR) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::otherHR);
                    }
                    if (Data.hpvlo) {
                        StateMachine::ClearHPV (Data, Tables, help, Woman::Low);
                    }
                }
            }
        } else if (!Data.HPVinfections.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.LLETZSuccessRateHPV) {
                if (Data.hpv16) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High16);
                }
                if (Data.hpv18) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High18);
                }
                if (Data.hpv31) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High31);
                }
                if (Data.hpv33) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High33);
                }
                if (Data.hpv45) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High45);
                }
                if (Data.hpv52) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High52);
                }
                if (Data.hpv58) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::High58);
                }
                if (Data.hpvotherHR) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::otherHR);
                }
                if (Data.hpvlo) {
                    StateMachine::ClearHPV (Data, Tables, help, Woman::Low);
                }
            }
        }
    }
}

void StateMachine::Colpo(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {

    rand = help.getrand ();
    if(rand < Tables.ScreenCompliance){
        Count.cost[y] += Tables.cPtTime;
        Count.cost[y] += Tables.cColpoProc;
        Count.cost[y] += Tables.cColpoTime;
        Count.costs[y][1]++;
        Count.costs[y][6]++;
        Count.costs[y][7]++;
        if (Data.cancer) {
            StateMachine::SendforTreatment (Data, Tables, Count, y, help);
        } else {
            if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
                rand = help.getrand ();
                if (rand < Tables.colposens[1][1]) {
                    rand = help.getrand ();
                    if(rand < Tables.ScreenCompliance){
                        StateMachine::SendforTreatment (Data, Tables, Count, y, help);
                    }
                }
            } else if (!Data.HPVinfections.empty ()) {
                rand = help.getrand ();
                if (rand < Tables.colposens[1][0]) {
                    rand = help.getrand ();
                    if(rand < Tables.ScreenCompliance){
                        StateMachine::SendforTreatment (Data, Tables, Count, y, help);
                    }
                }
            } else {
                rand = help.getrand ();
                if (rand < Tables.colposens[1][0]) {
                    rand = help.getrand ();
                    if(rand < Tables.ScreenCompliance){
                        StateMachine::SendforTreatment (Data, Tables, Count, y, help);
                    }
                }
            }
        }
    }
}

void StateMachine::GetMortality(Woman &Data, Inputs &Tables) {
    switch(Data.cancerstage){
        case Woman::Stage0:break;
        case Woman::Stage1:
            mCA = Tables.mCA1[Data.ca1Timer];
            break;
        case Woman::Stage2:
            mCA = Tables.mCA2[Data.ca2Timer];
            break;
        case Woman::Stage3:
            mCA = Tables.mCA3[Data.ca3Timer];
            break;
        case Woman::Stage1d:
            mCA = Tables.mCA1d[Data.ca1Timer];
            break;
        case Woman::Stage2d:
            mCA = Tables.mCA2d[Data.ca2Timer];
            break;
        case Woman::Stage3d:
            mCA = Tables.mCA3d[Data.ca3Timer];
            break;
    }
}

void StateMachine::GetVaccineEff(Woman &Data, Inputs &Tables) {
    if (Data.completevaccine) {
        vaccine_eff_1618 = Tables.VE_1618;
        vaccine_eff_high5 = Tables.VE_high5;
        if (Data.CurrentAge > (Tables.VaccineDuration + Tables.VaccineStartAge)) {
            vaccine_eff_1618 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                        (Tables.VaccineDuration + Data.vaccineage),
                                        vaccine_eff_1618);
            vaccine_eff_high5 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                         (Tables.VaccineDuration + Data.vaccineage),
                                         vaccine_eff_high5);
        }
    } else {
        vaccine_eff_1618 = 0;
        vaccine_eff_high5 = 0;
    }
    vaccine_deg_1618 = 1 - vaccine_eff_1618;
    vaccine_deg_high5 = 1 - vaccine_eff_high5;
}

void StateMachine::CheckLatency(Woman &Data, Inputs &Tables, Woman::hpvT genotype) {
    bool priorlatent = false;
    for (int i = 0; i < Data.HPVLatentinfections.size (); i++) {
        if (Data.HPVLatentinfections[i] == genotype) {
            Data.HPVinfectionTimer.push_back(Data.HPVLatentinfectionTimer[i]);
            Data.HPVLatentinfections.erase (Data.HPVLatentinfections.begin () + i);
            Data.HPVLatentinfectionTimer.erase (Data.HPVLatentinfectionTimer.begin () + i);
            priorlatent = true;
            break;
        }
    }
    if(!priorlatent){
        Data.HPVinfectionTimer.push_back(1);
    }
}

void StateMachine::AcquireHPV16(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High16);
    rand = help.getrand ();
    if (rand < pHPV_16) {
        Data.hpv16 = true;
        Data.age16 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High16);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High16);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
        Count.HPV16count[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPVoHR (Data, Count, Tables, help);
    }
}

void StateMachine::AcquireHPV18(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High18);
    rand = help.getrand ();
    if (rand < pHPV_18) {
        Data.hpv18 = true;
        Data.age18 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High18);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High18);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
        Count.HPV18count[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV31 (Data, Count, Tables, help);
    }
}

void StateMachine::AcquireHPV31(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High31);
    rand = help.getrand ();
    if (rand < pHPV_31) {
        Data.hpv31 = true;
        Data.age31 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High31);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High31);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV33 (Data, Count, Tables, help);
    }
}

void StateMachine::AcquireHPV33(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High33);
    rand = help.getrand ();
    if (rand < pHPV_33) {
        Data.hpv33 = true;
        Data.age33 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High33);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High33);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV45 (Data, Count, Tables, help);
    }

}

void StateMachine::AcquireHPV45(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High45);
    rand = help.getrand ();
    if (rand < pHPV_45) {
        Data.hpv45 = true;
        Data.age45 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High45);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High45);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV52 (Data, Count, Tables, help);
    }

}

void StateMachine::AcquireHPV52(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High52);
    rand = help.getrand ();
    if (rand < pHPV_52) {
        Data.hpv52 = true;
        Data.age52 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High52);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High52);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV58 (Data, Count, Tables, help);
    }
}

void StateMachine::AcquireHPV58(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::High58);
    rand = help.getrand ();
    if (rand < pHPV_58) {
        Data.hpv58 = true;
        Data.age58 = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::High58);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::High58);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    }
}

void StateMachine::AcquireHPVoHR(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::otherHR);
    rand = help.getrand ();
    if (rand < pHPV_oHR) {
        Data.hpvotherHR = true;
        Data.ageoHR = Data.CurrentAge;
        Data.HPVinfections.push_back (Woman::otherHR);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::otherHR);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV18 (Data, Count, Tables, help);
    }
}

void StateMachine::AcquireHPVLow(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    StateMachine::GetHPVRisk (Data, Tables, Woman::Low);
    rand = help.getrand ();
    if (rand < pHPV_LR) {
        Data.hpvlo = true;
        Data.HPVinfections.push_back (Woman::Low);
        if(Tables.LatencyTime){
            StateMachine::CheckLatency (Data, Tables, Woman::Low);
        } else {
            Data.HPVinfectionTimer.push_back (1);
        }
        Count.HPVcount[Data.CurrentAge]++;
    } else {
        StateMachine::AcquireHPV16 (Data, Count, Tables, help);
    }

}

void StateMachine::GetLesionRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype) {

    switch(genotype){
        case Woman::No:break;
        case Woman::Low:
            pHPV_CIN3 = Tables.pHPV_LR_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_LR_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::otherHR:
            pHPV_CIN3 = Tables.pHPV_otherHR_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_otherHR_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High16:
            pHPV_CIN3 = Tables.pHPV_16_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_16_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High18:
            pHPV_CIN3 = Tables.pHPV_18_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_18_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High31:
            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High33:
            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High45:
            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High52:
            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High58:
            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
            pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
            break;
    }

    for (auto & CIN2Lesion : Data.CIN2Lesions){
        if(CIN2Lesion == genotype){
            pHPV_CIN2 = 0;
            pHPV_CIN3 = 0;
            break;
        }
    }

    for (auto & CIN3Lesion : Data.CIN3Lesions){
        if(CIN3Lesion == genotype){
            pHPV_CIN2 = 0;
            pHPV_CIN3 = 0;
            break;
        }
    }
}

void StateMachine::GetHPVClearanceRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype) {

    switch(genotype){
        case Woman::No:break;
        case Woman::Low:
            pHPV_NL = Tables.pHPV_LR_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::otherHR:
            pHPV_NL = Tables.pHPV_otherHR_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High16:
            pHPV_NL = Tables.pHPV_16_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High18:
            pHPV_NL = Tables.pHPV_18_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High31:
            pHPV_NL = Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High33:
            pHPV_NL = Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High45:
            pHPV_NL = Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High52:
            pHPV_NL = Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High58:
            pHPV_NL = Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]];
            break;
    }

    for (auto & CIN2Lesion : Data.CIN2Lesions){
        if(CIN2Lesion == genotype){
            pHPV_NL = 0;
            break;
        }
    }
    for (auto & CIN3Lesion : Data.CIN3Lesions){
        if(CIN3Lesion == genotype){
            pHPV_NL = 0;
            break;
        }
    }
}

void StateMachine::GetCIN2Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype) {

    if(!Data.CIN2Lesions.empty()){
        switch(genotype){
            case Woman::No:break;
            case Woman::Low:
                pCIN2_HPV = Tables.pCIN2_NL_LR[Data.CIN2LesionTimer[i]];
                break;
            case Woman::otherHR:
                pCIN2_HPV = Tables.pCIN2_NL_oHR[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_oHR[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High16:
                pCIN2_HPV = Tables.pCIN2_NL_16[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_16[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High18:
                pCIN2_HPV = Tables.pCIN2_NL_18[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_18[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High31:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High33:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High45:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High52:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High58:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]];
                break;
        }
    }
}

void StateMachine::GetCIN3Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype) {

    if(!Data.CIN3Lesions.empty()){
        switch(genotype){
            case Woman::No:break;
            case Woman::Low:
                pCIN3_HPV = Tables.pCIN3_NL_LR[Data.CIN3LesionTimer[i]];
                break;
            case Woman::otherHR:
                pCIN3_HPV = Tables.pCIN3_NL_oHR[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_oHR[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High16:
                pCIN3_HPV = Tables.pCIN3_NL_16[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_16[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High18:
                pCIN3_HPV = Tables.pCIN3_NL_18[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_18[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High31:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High33:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High45:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High52:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High58:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]];
                break;
        }
    }
}

void StateMachine::CountDetectedCancer(Woman &Data, Output &Count) {
    Count.TotalDetectedCancer[Data.CurrentAge]++;
    Count.DetectedCAcount[Data.CurrentAge]++;
}

void StateMachine::CountCancer(Woman &Data, Output &Count, Woman::hpvT genotype) {

    Count.TotalCancer[Data.CurrentAge]++;
    Count.CAcount[Data.CurrentAge]++;
    Count.cancerHIVneg++;
    switch(genotype){
        case Woman::No:break;
        case Woman::Low:break;
        case Woman::otherHR:
            Count.CAotherHR++;
            break;
        case Woman::High16:
            Count.CA16++;
            break;
        case Woman::High18:
            Count.CA18++;
            break;
        case Woman::High31:
            Count.CA31++;
            break;
        case Woman::High33:
            Count.CA33++;
            break;
        case Woman::High45:
            Count.CA45++;
            break;
        case Woman::High52:
            Count.CA52++;
            break;
        case Woman::High58:
            Count.CA58++;
            break;
    }
}

void StateMachine::CountCIN3(Woman &Data, Output &Count) {

    Count.CIN3total++;
    if(Data.hpv16){
        Count.CIN316++;
    }
    if(Data.hpv18){
        Count.CIN318++;
    }
    if(Data.hpv31){
        Count.CIN331++;
    }
    if(Data.hpv33){
        Count.CIN333++;
    }
    if(Data.hpv45){
        Count.CIN345++;
    }
    if(Data.hpv52){
        Count.CIN352++;
    }
    if(Data.hpv58){
        Count.CIN358++;
    }
    if(Data.hpvotherHR){
        Count.CIN3otherHR++;
    }
}

void StateMachine::CountCIN2(Woman &Data, Output &Count) {

    Count.CIN2total++;
    if(Data.hpv16){
        Count.CIN216++;
    }
    if(Data.hpv18){
        Count.CIN218++;
    }
    if(Data.hpv31){
        Count.CIN231++;
    }
    if(Data.hpv33){
        Count.CIN233++;
    }
    if(Data.hpv45){
        Count.CIN245++;
    }
    if(Data.hpv52){
        Count.CIN252++;
    }
    if(Data.hpv58){
        Count.CIN258++;
    }
    if(Data.hpvotherHR){
        Count.CIN2otherHR++;
    }

}

void StateMachine::Vaccinate(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {
    if(Data.CurrentAge >= Tables.VaccineStartAge){
        if (!Data.completevaccine) {
            if(Data.vaccinedoses == 0){
                rand = help.getrand ();
                if (rand < Tables.VaccineCoverage) {
                    /*Count.cost[y] += Tables.cVaccine;*/
                    Data.vaccineage = Data.CurrentAge;
                    Data.vaccinedoses++;
                    /*Count.cost[y] += Tables.cVaccine;*/
                    Data.vaccineage = Data.CurrentAge;
                    Data.vaccinedoses++;
                    if(Data.vaccinedoses >= 2){
                        Data.completevaccine = true;
                    }

                }
            } else {
                /*Count.cost[y] += Tables.cVaccine;*/
                Data.vaccineage = Data.CurrentAge;
                Data.vaccinedoses++;
                if(Data.vaccinedoses >= 2){
                    Data.completevaccine = true;
                }
            }
        }
    }
}

double StateMachine::CalcEff(double wanetime, int age, int waneage, double starteff) {
    double slope = -starteff / wanetime;
    double efficacy = (slope * (age - waneage)) + starteff;

    if (efficacy < 0) {
        efficacy = 0;
    }
    return (efficacy);
}

void StateMachine::GetHPVRisk(Woman &Data, Inputs &Tables, Woman::hpvT genotype) {

    switch(genotype){
        case Woman::No:
            break;
        case Woman::Low:
            if (!Data.hpvlo) {
                pHPV_LR = Tables.pHPV_LR[Data.CurrentAge] * Data.immune_deg_LR;
            } else {
                pHPV_LR = 0;
            }
            break;
        case Woman::otherHR:
            if (!Data.hpvotherHR) {
                pHPV_oHR = Tables.pHPV_otherHR[Data.CurrentAge] * Data.immune_deg_otherHR;
            } else {
                pHPV_oHR = 0;
            }
            break;
        case Woman::High16:
            if (!Data.hpv16) {
                pHPV_16 = Tables.pHPV_16[Data.CurrentAge] * Data.immune_deg_16 * vaccine_deg_1618;
            } else {
                pHPV_16 = 0;
            }
            break;
        case Woman::High18:
            if (!Data.hpv18) {
                pHPV_18 = Tables.pHPV_18[Data.CurrentAge] * Data.immune_deg_18 * vaccine_deg_1618;
            } else {
                pHPV_18 = 0;
            }
            break;
        case Woman::High31:
            if (!Data.hpv31) {
                pHPV_31 = Tables.pHPV_31[Data.CurrentAge] * Data.immune_deg_31 * vaccine_deg_high5;
            } else {
                pHPV_31 = 0;
            }
            break;
        case Woman::High33:
            if (!Data.hpv33) {
                pHPV_33 = Tables.pHPV_33[Data.CurrentAge] * Data.immune_deg_33 * vaccine_deg_high5;
            } else {
                pHPV_33 = 0;
            }
            break;
        case Woman::High45:
            if (!Data.hpv45) {
                pHPV_45 = Tables.pHPV_45[Data.CurrentAge] * Data.immune_deg_45 * vaccine_deg_high5;
            } else {
                pHPV_45 = 0;
            }
            break;
        case Woman::High52:
            if (!Data.hpv52) {
                pHPV_52 = Tables.pHPV_52[Data.CurrentAge] * Data.immune_deg_52 * vaccine_deg_high5;
            } else {
                pHPV_52 = 0;
            }
            break;
        case Woman::High58:
            if (!Data.hpv58) {
                pHPV_58 = Tables.pHPV_58[Data.CurrentAge] * Data.immune_deg_58 * vaccine_deg_high5;
            } else {
                pHPV_58 = 0;
            }
            break;
    }
}

void StateMachine::CheckSeropositivity(Woman &Data, Inputs &Tables, helper &help) {
    for (int i = 0; i < Data.HPVinfections.size (); i++) {
        switch (Data.HPVinfections[i]) {
            case Woman::No:
                break;
            case Woman::Low:
                if(!Data.hpvlo_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpvlo_seropos = true;
                    }
                }
                break;
            case Woman::otherHR:
                if(!Data.hpvotherHR_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpvotherHR_seropos = true;
                    }
                }
                break;
            case Woman::High16:
                if(!Data.hpv16_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_16[Data.HPVinfectionTimer[i]]){
                        Data.hpv16_seropos = true;
                    }
                }
                break;
            case Woman::High18:
                if(!Data.hpv18_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_18[Data.HPVinfectionTimer[i]]){
                        Data.hpv18_seropos = true;
                    }
                }
                break;
            case Woman::High31:
                if(!Data.hpv31_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpv31_seropos = true;
                    }
                }
                break;
            case Woman::High33:
                if(!Data.hpv33_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpv33_seropos = true;
                    }
                }
                break;
            case Woman::High45:
                if(!Data.hpv45_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpv45_seropos = true;
                    }
                }
                break;
            case Woman::High52:
                if(!Data.hpv52_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpv52_seropos = true;
                    }
                }
                break;
            case Woman::High58:
                if(!Data.hpv58_seropos){
                    rand = help.getrand ();
                    if(rand < Tables.pSeroConvert_high5[Data.HPVinfectionTimer[i]]){
                        Data.hpv58_seropos = true;
                    }
                }
                break;
        }
    }
}

void StateMachine::GetImmuneFactor(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype) {

    switch(genotype){
        case Woman::No:
            break;
        case Woman::Low:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_LR = 0;
                Data.hpvlo_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_LR = 1.00;
            }
            break;
        case Woman::otherHR:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_otherHR = 0;
                Data.hpvotherHR_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_otherHR = 1.00;
            }
            break;
        case Woman::High16:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_16 = 0;
                Data.hpv16_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_16 = 1.00;
            }
            break;
        case Woman::High18:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_18 = 0;
                Data.hpv18_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_18 = 1.00;
            }
            break;
        case Woman::High31:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_31 = 0;
                Data.hpv31_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_31 = 1.00;
            }
            break;
        case Woman::High33:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
                Data.immune_deg_33 = 0;
                Data.hpv33_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_33 = 1.00;
            }
            break;
        case Woman::High45:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_45 = 0;
                Data.hpv45_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_45 = 1.00;
            }
            break;
        case Woman::High52:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_52 = 0;
                Data.hpv52_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_52 = 1.00;
            }
            break;
        case Woman::High58:
            rand = help.getrand ();
            if (rand < Tables.ImmuneFactor){
                Data.immune_deg_58 = 0;
                Data.hpv58_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_58 = 1.00;
            }
            break;
    }
}

void StateMachine::GetImmuneDeg(Woman &Data, Inputs &Tables, Woman::hpvT genotype) {
    switch(genotype){
        case Woman::No:
            break;
        case Woman::Low:
            Data.immune_deg_LR = Tables.ImmuneDegree;
            Data.hpvlo_ageimmunity = Data.CurrentAge;
            break;
        case Woman::otherHR:
            Data.immune_deg_otherHR = Tables.ImmuneDegree;
            Data.hpvotherHR_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High16:
            Data.immune_deg_16 = Tables.ImmuneDegree;
            Data.hpv16_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High18:
            Data.immune_deg_18 = Tables.ImmuneDegree;
            Data.hpv18_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High31:
            Data.immune_deg_31 = Tables.ImmuneDegree;
            Data.hpv31_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High33:
            Data.immune_deg_33 = Tables.ImmuneDegree;
            Data.hpv33_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High45:
            Data.immune_deg_45 = Tables.ImmuneDegree;
            Data.hpv45_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High52:
            Data.immune_deg_52 = Tables.ImmuneDegree;
            Data.hpv52_ageimmunity = Data.CurrentAge;
            break;
        case Woman::High58:
            Data.immune_deg_58 = Tables.ImmuneDegree;
            Data.hpv58_ageimmunity = Data.CurrentAge;
            break;
    }
}

void StateMachine::GetSeropositivity(Woman &Data, Inputs &Tables, Woman::hpvT genotype) {

    switch(genotype){
        case Woman::No:
            break;
        case Woman::Low:
            if(Data.hpvlo_seropos){
                Data.immune_deg_LR = Tables.ImmuneDegree;
                Data.hpvlo_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::otherHR:
            if(Data.hpvotherHR_seropos){
                Data.immune_deg_otherHR = Tables.ImmuneDegree;
                Data.hpvotherHR_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High16:
            if(Data.hpv16_seropos){
                Data.immune_deg_16 = Tables.ImmuneDegree;
                Data.hpv16_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High18:
            if(Data.hpv18_seropos){
                Data.immune_deg_18 = Tables.ImmuneDegree;
                Data.hpv18_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High31:
            if(Data.hpv31_seropos){
                Data.immune_deg_31 = Tables.ImmuneDegree;
                Data.hpv31_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High33:
            if(Data.hpv33_seropos){
                Data.immune_deg_33 = Tables.ImmuneDegree;
                Data.hpv33_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High45:
            if(Data.hpv45_seropos){
                Data.immune_deg_45 = Tables.ImmuneDegree;
                Data.hpv45_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High52:
            if(Data.hpv52_seropos){
                Data.immune_deg_52 = Tables.ImmuneDegree;
                Data.hpv52_ageimmunity = Data.CurrentAge;
            }
            break;
        case Woman::High58:
            if(Data.hpv58_seropos){
                Data.immune_deg_58 = Tables.ImmuneDegree;
                Data.hpv58_ageimmunity = Data.CurrentAge;
            }
            break;
    }
}

void StateMachine::CheckWaningImmunity(Woman &Data, Inputs &Tables) {
        if(Data.immune_deg_LR < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpvlo_ageimmunity)) {
                Data.immune_deg_LR = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpvlo_ageimmunity), Data.immune_deg_LR);
            }
        }
        if(Data.immune_deg_otherHR < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpvotherHR_ageimmunity)) {
                Data.immune_deg_otherHR = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                                  (Tables.ImmuneDuration + Data.hpvotherHR_ageimmunity), Data.immune_deg_otherHR);
            }
        }
        if(Data.immune_deg_16 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv16_ageimmunity)) {
                Data.immune_deg_16 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv16_ageimmunity), Data.immune_deg_16);
            }
        }
        if(Data.immune_deg_18 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv18_ageimmunity)) {
                Data.immune_deg_18 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv18_ageimmunity), Data.immune_deg_18);
            }
        }
        if(Data.immune_deg_31 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv31_ageimmunity)) {
                Data.immune_deg_31 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv31_ageimmunity), Data.immune_deg_31);
            }
        }
        if(Data.immune_deg_33 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv33_ageimmunity)) {
                Data.immune_deg_33 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv33_ageimmunity), Data.immune_deg_33);
            }
        }
        if(Data.immune_deg_45 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv45_ageimmunity)) {
                Data.immune_deg_45 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv45_ageimmunity), Data.immune_deg_45);
            }
        }
        if(Data.immune_deg_52 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv52_ageimmunity)) {
                Data.immune_deg_52 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv52_ageimmunity), Data.immune_deg_52);
            }
        }
        if(Data.immune_deg_58 < 1){
            if (Data.CurrentAge > (Tables.ImmuneDuration + Data.hpv58_ageimmunity)) {
                Data.immune_deg_58 = 1 - CalcEff (Tables.ImmuneWaneTime, Data.CurrentAge,
                                             (Tables.ImmuneDuration + Data.hpv58_ageimmunity), Data.immune_deg_58);
            }
        }

}

void StateMachine::GetBackgroundMortality(Woman &Data, Inputs &Tables, int CurrentModelYear) {
    int index;
    if (CurrentModelYear < 1950) {
        index = 0;
    } else if (CurrentModelYear < 2085) {
        index = CurrentModelYear - 1950;
    } else {
        index = 134;
    }

    if (Data.CurrentAge < Tables.ModelStopAge) {
        mASR = Tables.ASRMortality[Data.CurrentAge][index];
    } else {
        mASR = 1;
    }
}

void StateMachine::SendforTreatment(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {

    if(Data.cancer){
        switch (Data.cancerstage) {
            case Woman::Stage0:
                break;
            case Woman::Stage1:
                Data.cancerstage = Data.Stage1d;
                Count.cost[y] += Tables.cStage1Ca;
                Count.costs[y][11]++;
                break;
            case Woman::Stage2:
                Data.cancerstage = Data.Stage2d;
                Count.cost[y] += Tables.cStage2Ca;
                Count.costs[y][12]++;
                break;
            case Woman::Stage3:
                Data.cancerstage = Data.Stage3d;
                Count.cost[y] += Tables.cStage3Ca;
                Count.costs[y][13]++;
                break;
            case Woman::Stage1d:break;
            case Woman::Stage2d:break;
            case Woman::Stage3d:break;
        }
    } else {
        if (!Data.CIN3Lesions.empty ()) {
            rand = help.getrand();
            if(rand < Tables.CryoAvail){
                rand = help.getrand();
                if (rand < Tables.cryoelig_CIN3) {
                    StateMachine::Cryo (Data, Tables,  Count, y, help);
                } else {
                    StateMachine::LLETZ (Data, Tables,  Count, y, help);
                }
            } else {
                StateMachine::LLETZ (Data, Tables,  Count, y, help);
            }
        } else if (!Data.CIN2Lesions.empty ()) {
            rand = help.getrand();
            if(rand < Tables.CryoAvail){
                rand = help.getrand();
                if (rand < Tables.cryoelig_CIN2) {
                    StateMachine::Cryo (Data, Tables,  Count, y, help);
                } else {
                    StateMachine::LLETZ (Data, Tables,  Count, y, help);
                }
            } else {
                StateMachine::LLETZ (Data, Tables,  Count, y, help);
            }
        } else {
            rand = help.getrand();
            if(rand < Tables.CryoAvail){
                rand = help.getrand();
                if (rand < Tables.cryoelig_NL) {
                    StateMachine::Cryo (Data, Tables,  Count, y, help);
                } else {
                    StateMachine::LLETZ (Data, Tables,  Count, y, help);
                }
            } else {
                StateMachine::LLETZ (Data, Tables,  Count, y, help);
            }
        }
    }
}

StateMachine::~StateMachine(void) = default;