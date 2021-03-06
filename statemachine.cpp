//
// Created by Jamie Cohen on 11/15/17.
//


#include "statemachine.h"

using namespace std;

StateMachine::StateMachine() {
    genotypes = {Woman::Low, Woman::High16, Woman::High18, Woman::High31, Woman::High33, Woman::High45,
                 Woman::High52, Woman::High58, Woman::otherHR};
}

void StateMachine::CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y) {
    if (Data.Alive) {
        StateMachine::GetMortality (Data, Tables);
        rand = help.getrand ();
        if (rand <  mCA) {
            Data.Alive = false;
            Count.totaldeadcancer++;
        } else {
            switch (Data.cancerstage) {
                case Woman::Stage1:
                    rand = help.getrand ();
                    if (rand < Tables.CA1_CA2) {
                        Data.cancerstage = Data.Stage2;
                        Data.ca2Timer++;
                    } else if (rand < (Tables.CA1_CA2 + Tables.CA1_CA1d)) {
                        Data.cancerstage = Data.Stage1d;
                        Count.DwellTime_CA_detected_num += Data.ca1Timer;
                        Count.DwellTime_CA_detected_denom++;
                        StateMachine::CountDetectedCancer (Data, Count, y);
                        Data.ca1Timer++;
                        StateMachine::Colpo (Data, Tables, Count, help, y);
                    } else {
                        Data.ca1Timer++;
                    }
                    break;
                case Woman::Stage2:
                    rand = help.getrand ();
                    if (rand < Tables.CA2_CA3) {
                        Data.cancerstage = Data.Stage3;
                        Data.ca3Timer++;
                    } else if (rand < (Tables.CA2_CA3 + Tables.CA2_CA2d)) {
                        Data.cancerstage = Data.Stage2d;
                        StateMachine::CountDetectedCancer (Data, Count, y);
                        Count.DwellTime_CA_detected_num += Data.ca1Timer + Data.ca2Timer;
                        Count.DwellTime_CA_detected_denom++;
                        Data.ca2Timer++;
                        StateMachine::Colpo (Data, Tables, Count, help, y);
                    } else {
                        Data.ca2Timer++;
                    }
                    break;
                case Woman::Stage3:
                    rand = help.getrand ();
                    if (rand <  Tables.CA3_CA3d) {
                        Data.cancerstage = Data.Stage3d;
                        StateMachine::CountDetectedCancer (Data, Count, y);
                        Count.DwellTime_CA_detected_num += Data.ca1Timer + Data.ca2Timer + Data.ca3Timer;
                        Count.DwellTime_CA_detected_denom++;
                        Data.ca3Timer++;
                        StateMachine::Colpo (Data, Tables, Count, help, y);
                    } else {
                        Data.ca3Timer++;
                    }
                    break;
                case Woman::Stage1d:
                    Data.ca1Timer++;
                    break;
                case Woman::Stage2d:
                    Data.ca2Timer++;
                    break;
                case Woman::Stage3d:
                    Data.ca3Timer++;
                    break;
                default:
                    break;
            }
        }
    }
}

void StateMachine::HPVNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help) {

    if (Data.Alive) {
        for(int i = 0; i < genotypes.size(); i++){
            if(Data.HPVinfectionTimer[i]>0){
                StateMachine::GetLesionRisk (Data, Tables, i);
                StateMachine::GetHPVClearanceRisk (Data, Tables, i);
                rand = help.getrand ();
                if (rand < pHPV_CIN) {
                    Data.HPVinfectionTimer[i]++;
                    StateMachine::CountCIN (Data, i);
                    rand = help.getrand ();
                    if (rand < prop_CIN2){
                        Data.CIN2Lesions.push_back (Data.HPVinfections[i]);
                        Data.CIN2LesionTimer.push_back (1);
                    } else {
                        Data.CIN3Lesions.push_back (Data.HPVinfections[i]);
                        Data.CIN3LesionTimer.push_back (1);
                    }
                } else if (rand < ( pHPV_CIN + pHPV_NL)) {
                    StateMachine::ClearHPV (Data, Tables, help, Data.HPVinfections[i]);
                } else {
                    Data.HPVinfectionTimer[i]++;
                }
            }
        }
    }
}

void StateMachine::NatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y, bool burnin) {
    if (Data.Alive) {
        if (Data.cancer) {
            CancerNatHistory (Data, Tables, Count, help, y);
        } else {
            if(Tables.WaningImmunity){
                CheckWaningImmunity (Data, Tables);
            }
            StateMachine::GetVaccineEff (Data, Tables, burnin);
            if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
                StateMachine::StartCIN (Data, Count, Tables, help, y);
            }
            if (!Data.cancer) {
                StateMachine::HPVNatHistory (Data, Tables, Count, help);
                StateMachine::AcquireHPV (Data, Count, Tables, help, y);
            }
        }
    }
}

void StateMachine::CytoScreen(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y) {
    if (Data.ScreenAccess) {
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
                Count.cost[y] += Tables.cPaptest;
                Count.cost[y] += Tables.cReturnForResult;
                Count.cost[y] += Tables.cPtTime;
                rand = help.getrand ();
                if (rand < Adequacy) {
                    Data.screens++;
                    Data.screenage.push_back (Data.CurrentAge);
                }
                if (Data.cancer) {
                    rand = help.getrand ();
                    if (rand < Tables.cytosens_Ca) {
                        rand = help.getrand ();
                        if (rand < Tables.ScreenCompliance) {
                            StateMachine::Colpo (Data, Tables, Count, help, y);
                        }
                    }
                } else {
                    if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
                        rand = help.getrand ();
                        if (rand < Tables.cytosens_CIN) {
                            rand = help.getrand ();
                            if (rand < Tables.ScreenCompliance) {
                                StateMachine::Colpo (Data, Tables, Count, help, y);
                            }
                        }
                    } else {
                        rand = help.getrand ();
                        if (rand < Tables.cytosens_NL) {
                            rand = help.getrand ();
                            if (rand < Tables.ScreenCompliance) {
                                StateMachine::Colpo (Data, Tables, Count, help, y);
                            }
                        }
                    }
                }
            }
        }
    }
}

void StateMachine::ClearHPV(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype) {

    for(int i = 0; i < genotypes.size(); i++){
        if(genotypes[i] == genotype){
            Data.HPVLatentinfectionTimer[i] = Data.HPVinfectionTimer[i];
            Data.HPVinfectionTimer[i] = 0;
            Data.AgeClearedHPV[i] = Data.CurrentAge;
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
        case Inputs::None:
            break;
    }

}

void StateMachine::StartCIN(Woman &Data, Output &Count, Inputs &Tables, helper &help, int y) {

    if(!Data.CIN3Lesions.empty()){
        for (int i = 0; i < Data.CIN3Lesions.size (); i++) {
            StateMachine::GetCIN3Risk (Data, Tables, i, Data.CIN3Lesions[i]);
            rand = help.getrand ();
            if (rand < pCIN3_CA) {
                Data.cancer = true;
                Data.cancerstage = Data.Stage1;
                Data.ca1Timer++;
                StateMachine::CountCancer (Data, Count, Data.CIN3Lesions[i], Data.CIN3LesionTimer[i], y);
                Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                break;
            } else if (rand < (pCIN3_CA + pCIN3_HPV)) {
                rand = help.getrand ();
                if (rand > Tables.pRegresstoHPV) {
                    StateMachine::ClearHPV (Data, Tables, help, Data.CIN3Lesions[i]);
                }
                Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                i--;
            } else {
                Data.CIN3LesionTimer[i]++;
            }
        }
    }

    if(!Data.cancer){
        if(!Data.CIN2Lesions.empty()){
            for (int i = 0; i < Data.CIN2Lesions.size (); i++) {
                StateMachine::GetCIN2Risk (Data, Tables, i, Data.CIN2Lesions[i]);
                rand = help.getrand ();
                if (rand < pCIN2_CA) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    StateMachine::CountCancer (Data, Count, Data.CIN2Lesions[i], Data.CIN2LesionTimer[i], y);
                    Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                    Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
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
            }
        }
    }
}

void StateMachine::runPopulationYear(Woman &Data, Inputs &Tables, Output &Count, bool calib, helper &help, int y) {

    StateMachine::GetBackgroundMortality (Data, Tables, help);
    rand = help.getrand ();
    if (rand < mASR) {
        Data.Alive = false;
    } else {
        if (!calib) {
            StateMachine::Vaccinate (Data, Tables, Count, help, y);
            StateMachine::CytoScreen (Data, Tables, Count, help, y);
        }
        StateMachine::NatHistory (Data, Tables, Count, help, y, calib);
    }
    Count.createTrace (Data, y);
    if (!calib) {
        Count.calcLE (Data, Tables, y);
    }

    if (Data.Alive) {
        Count.total_alive[Data.CurrentAge][y]++;
        Data.CurrentAge++;
        Data.CurrentYear++;
        Data.Cycle++;
    }
}

void StateMachine::LLETZ(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y) {

    Count.cost[y] += Tables.cPtTime;
    Count.cost[y] += Tables.cCryoVisit;
    Count.cost[y] += Tables.cCryoCIN23;

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

void StateMachine::Colpo(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y) {

    rand = help.getrand ();
    if(rand < Tables.ScreenCompliance){
        Count.cost[y] += Tables.cPtTime;
        Count.cost[y] += Tables.cColpoProc;
        Count.cost[y] += Tables.cColpoTime;
        if (Data.cancer) {
            StateMachine::SendforTreatment (Data, Tables, Count, help, y);
        } else {
            if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
                rand = help.getrand ();
                if (rand < Tables.colposens[1][1]) {
                    rand = help.getrand ();
                    if(rand < Tables.ScreenCompliance){
                        StateMachine::SendforTreatment (Data, Tables, Count,help, y);
                    }
                }
            } else if (!Data.HPVinfections.empty ()) {
                rand = help.getrand ();
                if (rand < Tables.colposens[1][0]) {
                    rand = help.getrand ();
                    if(rand < Tables.ScreenCompliance){
                        StateMachine::SendforTreatment (Data, Tables, Count, help, y);
                    }
                }
            } else {
                rand = help.getrand ();
                if (rand < Tables.colposens[1][0]) {
                    rand = help.getrand ();
                    if(rand < Tables.ScreenCompliance){
                        StateMachine::SendforTreatment (Data, Tables, Count, help, y);
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

void StateMachine::GetVaccineEff(Woman &Data, Inputs &Tables, bool burnin) {
    if(burnin){
        vaccine_eff_16 = 0;
        vaccine_eff_18 = 0;
        vaccine_eff_31 = 0;
        vaccine_eff_33 = 0;
        vaccine_eff_45 = 0;
        vaccine_eff_52 = 0;
        vaccine_eff_58 = 0;
        vaccine_deg_16 = 1 - vaccine_eff_16;
        vaccine_deg_18 = 1 - vaccine_eff_18;
        vaccine_deg_31 = 1 - vaccine_eff_31;
        vaccine_deg_33 = 1 - vaccine_eff_33;
        vaccine_deg_45 = 1 - vaccine_eff_45;
        vaccine_deg_52 = 1 - vaccine_eff_52;
        vaccine_deg_58 = 1 - vaccine_eff_58;

    } else {
        if (Data.completevaccine) {
            vaccine_eff_16 = Tables.VE_1618;
            vaccine_eff_18 = Tables.VE_1618;
            vaccine_eff_31 = Tables.VE_high5;
            vaccine_eff_33 = Tables.VE_high5;
            vaccine_eff_45 = Tables.VE_high5;
            vaccine_eff_52 = Tables.VE_high5;
            vaccine_eff_58 = Tables.VE_high5;
            if (Data.CurrentAge > (Tables.VaccineDuration + Tables.VaccineStartAge)) {
                vaccine_eff_16 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                            (Tables.VaccineDuration + Data.vaccineage),
                                            vaccine_eff_16);
                vaccine_eff_18 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                          (Tables.VaccineDuration + Data.vaccineage),
                                          vaccine_eff_18);
                vaccine_eff_31 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                             (Tables.VaccineDuration + Data.vaccineage),
                                             vaccine_eff_31);
                vaccine_eff_33 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                          (Tables.VaccineDuration + Data.vaccineage),
                                          vaccine_eff_33);
                vaccine_eff_45 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                          (Tables.VaccineDuration + Data.vaccineage),
                                          vaccine_eff_45);
                vaccine_eff_52 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                          (Tables.VaccineDuration + Data.vaccineage),
                                          vaccine_eff_52);
                vaccine_eff_58 = CalcEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                          (Tables.VaccineDuration + Data.vaccineage),
                                          vaccine_eff_58);
            }
        } else {
            vaccine_eff_16 = 0;
            vaccine_eff_18 = 0;
            vaccine_eff_31 = 0;
            vaccine_eff_33 = 0;
            vaccine_eff_45 = 0;
            vaccine_eff_52 = 0;
            vaccine_eff_58 = 0;
        }

        if(Data.HPVLatentinfectionTimer[1] > 0){
            vaccine_eff_16 = vaccine_eff_16*Tables.VaccineEfficacyPrior;
        }
        if(Data.HPVLatentinfectionTimer[2] > 0){
            vaccine_eff_18 = vaccine_eff_18*Tables.VaccineEfficacyPrior;
        }
        if(Data.HPVLatentinfectionTimer[3] > 0){
            vaccine_eff_31 = vaccine_eff_31*Tables.VaccineEfficacyPrior;
        }
        if(Data.HPVLatentinfectionTimer[4] > 0){
            vaccine_eff_33 = vaccine_eff_33*Tables.VaccineEfficacyPrior;
        }
        if(Data.HPVLatentinfectionTimer[5] > 0){
            vaccine_eff_45 = vaccine_eff_45*Tables.VaccineEfficacyPrior;
        }
        if(Data.HPVLatentinfectionTimer[6] > 0){
            vaccine_eff_52 = vaccine_eff_52*Tables.VaccineEfficacyPrior;
        }
        if(Data.HPVLatentinfectionTimer[7] > 0){
            vaccine_eff_58 = vaccine_eff_58*Tables.VaccineEfficacyPrior;
        }

        vaccine_deg_16 = 1 - vaccine_eff_16;
        vaccine_deg_18 = 1 - vaccine_eff_18;
        vaccine_deg_31 = 1 - vaccine_eff_31;
        vaccine_deg_33 = 1 - vaccine_eff_33;
        vaccine_deg_45 = 1 - vaccine_eff_45;
        vaccine_deg_52 = 1 - vaccine_eff_52;
        vaccine_deg_58 = 1 - vaccine_eff_58;
    }
}

void StateMachine::CheckLatency(Woman &Data, Inputs &Tables, int i) {
    Data.HPVinfectionTimer[i] = (Data.HPVLatentinfectionTimer[i] + 1);
    if(Data.HPVLatentinfectionTimer[i] > 0){
        Data.DormancyTimer[i] += (Data.CurrentAge - Data.AgeClearedHPV[i]);
        Data.LatentTimer[i] = (Data.HPVLatentinfectionTimer[i] + Data.DormancyTimer[i]);
    }
}

void StateMachine::AcquireHPV(Woman &Data, Output &Count, Inputs &Tables, helper &help, int y) {

    for(int i = 0; i < genotypes.size(); i++){
        StateMachine::GetHPVRisk (Data, Tables, genotypes[i]);
        rand = help.getrand ();
        if (rand < pHPV) {
            if (Tables.Latency) {
                StateMachine::CheckLatency (Data, Tables, i);
                StateMachine::CountDormancyTime(Data, i);
            } else {
                Data.HPVinfectionTimer[i]++;
                Data.LatentTimer[i] = 0;
            }
            Count.HPVcount[Data.CurrentAge][y]++;
            switch (genotypes[i]) {
                case Woman::No:
                    break;
                case Woman::Low:
                    Data.hpvlo = true;
                    break;
                case Woman::otherHR:
                    Data.hpvotherHR = true;
                    Data.yearoHR = Data.Cycle;
                    break;
                case Woman::High16:
                    Data.hpv16 = true;
                    Data.year16 = Data.Cycle;
                    Count.HPV16count[Data.CurrentAge][y]++;
                    break;
                case Woman::High18:
                    Data.hpv18 = true;
                    Data.year18 = Data.Cycle;
                    Count.HPV18count[Data.CurrentAge][y]++;
                    break;
                case Woman::High31:
                    Data.hpv31 = true;
                    Data.year31 = Data.Cycle;
                    break;
                case Woman::High33:
                    Data.hpv33 = true;
                    Data.year33 = Data.Cycle;
                    break;
                case Woman::High45:
                    Data.hpv45 = true;
                    Data.year45 = Data.Cycle;
                    break;
                case Woman::High52:
                    Data.hpv52 = true;
                    Data.year52 = Data.Cycle;
                    break;
                case Woman::High58:
                    Data.hpv58 = true;
                    Data.year58 = Data.Cycle;
                    break;
            }
            break;
        }
    }
}

void StateMachine::GetLesionRisk(Woman &Data, Inputs &Tables, int i) {

    switch(genotypes[i]){
        case Woman::No:break;
        case Woman::Low:
            pHPV_CIN = Tables.pHPV_LR_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::otherHR:
            pHPV_CIN = Tables.pHPV_otherHR_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::High16:
            pHPV_CIN = Tables.pHPV_16_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_16;
            break;
        case Woman::High18:
            pHPV_CIN = Tables.pHPV_18_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::High31:
            pHPV_CIN = Tables.pHPV_31_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::High33:
            pHPV_CIN = Tables.pHPV_33_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::High45:
            pHPV_CIN = Tables.pHPV_45_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::High52:
            pHPV_CIN = Tables.pHPV_52_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
        case Woman::High58:
            pHPV_CIN = Tables.pHPV_58_CIN[Data.HPVinfectionTimer[i]];
            prop_CIN2 = Tables.HPV_CIN2_allother;
            break;
    }

    for (auto & CIN2Lesion : Data.CIN2Lesions){
        if(CIN2Lesion == genotypes[i]){
            pHPV_CIN = 0;
            break;
        }
    }

    for (auto & CIN3Lesion : Data.CIN3Lesions){
        if(CIN3Lesion == genotypes[i]){
            pHPV_CIN = 0;
            break;
        }
    }
}

void StateMachine::GetHPVClearanceRisk(Woman &Data, Inputs &Tables, int i) {

    switch(genotypes[i]){
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
            pHPV_NL = Tables.pHPV_31_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High33:
            pHPV_NL = Tables.pHPV_33_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High45:
            pHPV_NL = Tables.pHPV_45_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High52:
            pHPV_NL = Tables.pHPV_52_NL[Data.HPVinfectionTimer[i]];
            break;
        case Woman::High58:
            pHPV_NL = Tables.pHPV_58_NL[Data.HPVinfectionTimer[i]];
            break;
    }

    for (auto & CIN2Lesion : Data.CIN2Lesions){
        if(CIN2Lesion == genotypes[i]){
            pHPV_NL = 0;
            break;
        }
    }
    for (auto & CIN3Lesion : Data.CIN3Lesions){
        if(CIN3Lesion == genotypes[i]){
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
                pCIN2_CA = 0;
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
                pCIN2_CA = Tables.pCIN2_CA1_31[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High33:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_33[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High45:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_45[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High52:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_52[Data.CIN2LesionTimer[i]];
                break;
            case Woman::High58:
                pCIN2_HPV = Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]];
                pCIN2_CA = Tables.pCIN2_CA1_58[Data.CIN2LesionTimer[i]];
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
                pCIN3_CA = 0;
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
                pCIN3_CA = Tables.pCIN3_CA1_31[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High33:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_33[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High45:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_45[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High52:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_52[Data.CIN3LesionTimer[i]];
                break;
            case Woman::High58:
                pCIN3_HPV = Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]];
                pCIN3_CA = Tables.pCIN3_CA1_58[Data.CIN3LesionTimer[i]];
                break;
        }
    }
}

void StateMachine::CountDetectedCancer(Woman &Data, Output &Count, int y) {
    Count.TotalDetectedCancer[Data.CurrentAge][y]++;
    Count.DetectedCAcount[Data.CurrentAge][y]++;
    Count.TotalDetectedCancer_byyear[y]++;
}

void StateMachine::CountCIN(Woman &Data, int i) {
    switch(Data.HPVinfections[i]){
        case Woman::No:break;
        case Woman::Low:break;
        case Woman::otherHR:
            Data.CINoHR = Data.HPVinfectionTimer[i];
            break;
        case Woman::High16:
            Data.CIN16 = Data.HPVinfectionTimer[i];
            break;
        case Woman::High18:
            Data.CIN18 = Data.HPVinfectionTimer[i];
            break;
        case Woman::High31:
            Data.CIN31 = Data.HPVinfectionTimer[i];
            break;
        case Woman::High33:
            Data.CIN33 = Data.HPVinfectionTimer[i];
            break;
        case Woman::High45:
            Data.CIN45 = Data.HPVinfectionTimer[i];
            break;
        case Woman::High52:
            Data.CIN52 = Data.HPVinfectionTimer[i];
            break;
        case Woman::High58:
            Data.CIN58 = Data.HPVinfectionTimer[i];
            break;
    }
}

void StateMachine::CountDormancyTime(Woman &Data, int i) {
    switch(Data.HPVinfections[i]){
        case Woman::No:break;
        case Woman::Low:break;
        case Woman::otherHR:
            Data.CIN_dormant_oHR = Data.DormancyTimer[i];
            Data.CIN_latent_oHR = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High16:
            Data.CIN_dormant_16 = Data.DormancyTimer[i];
            Data.CIN_latent_16 = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High18:
            Data.CIN_dormant_18 = Data.DormancyTimer[i];
            Data.CIN_latent_18 = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High31:
            Data.CIN_dormant_31 = Data.DormancyTimer[i];
            Data.CIN_latent_31 = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High33:
            Data.CIN_dormant_33 = Data.DormancyTimer[i];
            Data.CIN_latent_33 = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High45:
            Data.CIN_dormant_45 = Data.DormancyTimer[i];
            Data.CIN_latent_45 = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High52:
            Data.CIN_dormant_52 = Data.DormancyTimer[i];
            Data.CIN_latent_52 = Data.HPVLatentinfectionTimer[i];
            break;
        case Woman::High58:
            Data.CIN_dormant_58 = Data.DormancyTimer[i];
            Data.CIN_latent_58 = Data.HPVLatentinfectionTimer[i];
            break;
    }
}

void StateMachine::CountCancer(Woman &Data, Output &Count, Woman::hpvT genotype, int i, int y) {

    Count.TotalCancer[Data.CurrentAge][y]++;
    Count.CAcount[Data.CurrentAge][y]++;
    Count.cancer++;
    switch(genotype){
        case Woman::No:break;
        case Woman::Low:break;
        case Woman::otherHR:
            Count.CAotherHR++;
            Data.CAoHR = i;
            break;
        case Woman::High16:
            Count.CA16++;
            Data.CA16 = i;
            break;
        case Woman::High18:
            Count.CA18++;
            Data.CA18 = i;
            break;
        case Woman::High31:
            Count.CA31++;
            Data.CA31 = i;
            break;
        case Woman::High33:
            Count.CA33++;
            Data.CA33 = i;
            break;
        case Woman::High45:
            Count.CA45++;
            Data.CA45 = i;
            break;
        case Woman::High52:
            Count.CA52++;
            Data.CA52 = i;
            break;
        case Woman::High58:
            Count.CA58++;
            Data.CA58 = i;
            break;
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
                pHPV = Tables.pHPV_LR[Data.CurrentAge] * Data.immune_deg_LR;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::otherHR:
            if (!Data.hpvotherHR) {
                pHPV = Tables.pHPV_otherHR[Data.CurrentAge] * Data.immune_deg_otherHR;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High16:
            if (!Data.hpv16) {
                pHPV = Tables.pHPV_16[Data.CurrentAge] * Data.immune_deg_16 * vaccine_deg_16;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High18:
            if (!Data.hpv18) {
                pHPV = Tables.pHPV_18[Data.CurrentAge] * Data.immune_deg_18 * vaccine_deg_18;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High31:
            if (!Data.hpv31) {
                pHPV = Tables.pHPV_31[Data.CurrentAge] * Data.immune_deg_31 * vaccine_deg_31;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High33:
            if (!Data.hpv33) {
                pHPV = Tables.pHPV_33[Data.CurrentAge] * Data.immune_deg_33 * vaccine_deg_33;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High45:
            if (!Data.hpv45) {
                pHPV = Tables.pHPV_45[Data.CurrentAge] * Data.immune_deg_45 * vaccine_deg_45;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High52:
            if (!Data.hpv52) {
                pHPV = Tables.pHPV_52[Data.CurrentAge] * Data.immune_deg_52 * vaccine_deg_52;
            } else {
                pHPV = 0;
            }
            break;
        case Woman::High58:
            if (!Data.hpv58) {
                pHPV = Tables.pHPV_58[Data.CurrentAge] * Data.immune_deg_58 * vaccine_deg_58;
            } else {
                pHPV = 0;
            }
            break;
    }
}

void StateMachine::GetImmuneFactor(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype) {

    switch(genotype){
        case Woman::No:
            break;
        case Woman::Low:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
                Data.immune_deg_LR = 0;
                Data.hpvlo_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_LR = 1.00;
            }
            break;
        case Woman::otherHR:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
                Data.immune_deg_otherHR = 0;
                Data.hpvotherHR_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_otherHR = 1.00;
            }
            break;
        case Woman::High16:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree16){
                Data.immune_deg_16 = 0;
                Data.hpv16_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_16 = 1.00;
            }
            break;
        case Woman::High18:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
                Data.immune_deg_18 = 0;
                Data.hpv18_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_18 = 1.00;
            }
            break;
        case Woman::High31:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
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
            if (rand < Tables.ImmuneDegree){
                Data.immune_deg_45 = 0;
                Data.hpv45_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_45 = 1.00;
            }
            break;
        case Woman::High52:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
                Data.immune_deg_52 = 0;
                Data.hpv52_ageimmunity = Data.CurrentAge;
            } else {
                Data.immune_deg_52 = 1.00;
            }
            break;
        case Woman::High58:
            rand = help.getrand ();
            if (rand < Tables.ImmuneDegree){
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
            Data.immune_deg_16 = Tables.ImmuneDegree16;
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

void StateMachine::GetBackgroundMortality(Woman &Data, Inputs &Tables, helper &help) {

    if (Data.CurrentAge < Tables.ModelStopAge) {
        mASR = help.ratetoprob(Tables.ASRMortality[Data.CurrentAge][0]);
    } else {
        mASR = 1;
    }
}

void StateMachine::SendforTreatment(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y) {

    if(Data.cancer){
        switch (Data.cancerstage) {
            case Woman::Stage0:
                break;
            case Woman::Stage1:
                Data.cancerstage = Data.Stage1d;
                Count.cost[y] += Tables.cStage1Ca;
                break;
            case Woman::Stage2:
                Data.cancerstage = Data.Stage2d;
                Count.cost[y] += Tables.cStage2Ca;
                break;
            case Woman::Stage3:
                Data.cancerstage = Data.Stage3d;
                Count.cost[y] += Tables.cStage3Ca;
                break;
            case Woman::Stage1d:break;
            case Woman::Stage2d:break;
            case Woman::Stage3d:break;
        }
    } else {
        StateMachine::LLETZ (Data, Tables,  Count, help, y);
    }
}

void StateMachine::Vaccinate(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y) {

    if(Data.CurrentYear >= Tables.VaccineStartYear){
        if(Data.CurrentAge >= Tables.VaccineStartAge && Data.CurrentAge <= Tables.VaccineEndAge){
            if(!Data.completevaccine){
                rand = help.getrand();
                if(rand < Tables.VaccineCoverage){
                    Data.completevaccine = true;
                    Data.vaccineage = Data.CurrentAge;
                    Count.cost[y] += Tables.cHPVVaccine;
                }
            }
        }
    }
}

StateMachine::~StateMachine(void) = default;