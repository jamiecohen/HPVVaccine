//
// Created by Jamie Cohen on 11/15/17.
//

#include "statemachine.h"

using namespace std;


StateMachine::StateMachine() = default;

void StateMachine::CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {
    if (Data.Alive) {
        switch (Data.cancerstage) {
            case Woman::Stage1:
                rand = help.getrand ();
                if (rand < Tables.CA1_CA2) {
                    Data.cancerstage = Data.Stage2;
                    Data.ca2Timer++;
                } else if (rand < (Tables.CA1_CA2 + Tables.mCA1[Data.ca1Timer])) {
                    Data.Alive = false;
                    Count.totaldeadcancer++;
                } else if (rand < (Tables.CA1_CA2 + Tables.mCA1[Data.ca1Timer] + Tables.pCA1_CA1D)) {
                    Data.cancerstage = Data.Stage1d;
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
                } else if (rand < (Tables.CA2_CA3 + Tables.mCA2[Data.ca2Timer])) {
                    Data.Alive = false;
                    Count.totaldeadcancer++;
                } else if (rand < (Tables.CA2_CA3 + Tables.mCA2[Data.ca2Timer] + Tables.pCA2_CA2D)) {
                    Data.cancerstage = Data.Stage2d;
                    Data.ca2Timer++;
                    StateMachine::Colpo (Data, Tables, Count, y, help);
                } else {
                    Data.ca2Timer++;
                }
                break;

            case Woman::Stage3:

                rand = help.getrand ();
                if (rand < Tables.mCA3[Data.ca3Timer]) {
                    Data.Alive = false;
                    Count.totaldeadcancer++;
                } else if (rand < (Tables.mCA3[Data.ca3Timer] + Tables.pCA3_CA3D)) {
                    Data.cancerstage = Data.Stage3d;
                    Data.ca3Timer++;
                    StateMachine::Colpo (Data, Tables, Count, y, help);
                } else {
                    Data.ca3Timer++;
                }
                break;


            case Woman::Stage1d:
                rand = help.getrand ();
                if (rand < Tables.mCA1d[Data.ca1Timer]) {
                    Count.HIVCAdead[Data.CurrentAge]++;
                    Count.totaldeadcancer++;
                    Data.Alive = false;
                } else {
                    Data.ca1Timer++;
                }
                break;
            case Woman::Stage2d:
                rand = help.getrand ();
                if (rand < Tables.mCA2d[Data.ca2Timer]) {
                    Count.HIVCAdead[Data.CurrentAge]++;
                    Count.totaldeadcancer++;
                    Data.Alive = false;
                } else {
                    Data.ca2Timer++;
                }
                break;
            case Woman::Stage3d:
                rand = help.getrand ();
                if (rand < Tables.mCA3d[Data.ca3Timer]) {
                    Count.HIVCAdead[Data.CurrentAge]++;
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
        for (int i = 0; i < Data.HPVinfections.size (); i++) {
            StateMachine::GetLesionRisk (Data, Tables, i, Data.HPVinfections[i]);
            switch (Data.HPVinfections[i]) {
                case Woman::No: break;
                case Woman::Low:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN2Lesions.push_back (Woman::Low);
                        Data.CIN2LesionTimer.push_back (1);
                        Count.CIN2HIVpostotal++;
                        Count.CIN2LRHIV++;
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::Low);
                        Data.CIN3LesionTimer.push_back (1);
                        Count.CIN3HIVpostotal++;
                        Count.CIN3LRHIV++;
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_LR_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpvlo = false;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::otherHR:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN2HIVpostotal++;
                        Count.CIN2otherHRHIV++;
                        Data.CIN2Lesions.push_back (Woman::otherHR);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN3HIVpostotal++;
                        Count.CIN3otherHRHIV++;
                        Data.CIN3Lesions.push_back (Woman::otherHR);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_otherHR_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpvotherHR = false;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High16:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN2HIVpostotal++;
                        Count.CIN21618HIV++;
                        Data.CIN2Lesions.push_back (Woman::High16);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Count.CIN3HIVpostotal++;
                        Count.CIN31618HIV++;
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::High16);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_1618_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv16 = false;
                        Data.wasHPV16flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High18:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN2HIVpostotal++;
                        Count.CIN21618HIV++;
                        Data.CIN2Lesions.push_back (Woman::High18);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN3HIVpostotal++;
                        Count.CIN31618HIV++;
                        Data.CIN3Lesions.push_back (Woman::High18);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_1618_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv18 = false;
                        Data.wasHPV18flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High31:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN2HIVpostotal++;
                        Count.CIN2high5HIV++;
                        Data.CIN2Lesions.push_back (Woman::High31);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Count.CIN3HIVpostotal++;
                        Count.CIN3high5HIV++;
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::High31);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv31 = false;
                        Data.wasHPV31flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High33:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Count.CIN2HIVpostotal++;
                        Count.CIN2high5HIV++;
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN2Lesions.push_back (Woman::High33);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Count.CIN3HIVpostotal++;
                        Count.CIN3high5HIV++;
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN3Lesions.push_back (Woman::High33);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv33 = false;
                        Data.wasHPV33flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High45:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN2HIVpostotal++;
                        Count.CIN2high5HIV++;
                        Data.CIN2Lesions.push_back (Woman::High45);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN3HIVpostotal++;
                        Count.CIN3high5HIV++;
                        Data.CIN3Lesions.push_back (Woman::High45);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv45 = false;
                        Data.wasHPV45flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High52:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN2HIVpostotal++;
                        Count.CIN2high5HIV++;
                        Data.CIN2Lesions.push_back (Woman::High52);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN3HIVpostotal++;
                        Count.CIN3high5HIV++;
                        Data.CIN3Lesions.push_back (Woman::High52);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv52 = false;
                        Data.wasHPV52flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
                        i--;
                    } else {
                        Data.HPVinfectionTimer[i]++;
                    }
                    break;
                case Woman::High58:
                    rand = help.getrand ();
                    if (rand < pHPV_CIN2) {
                        Count.CIN2HIVpostotal++;
                        Count.CIN2high5HIV++;
                        Data.HPVinfectionTimer[i]++;
                        Data.CIN2Lesions.push_back (Woman::High58);
                        Data.CIN2LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3)) {
                        Data.HPVinfectionTimer[i]++;
                        Count.CIN3HIVpostotal++;
                        Count.CIN3high5HIV++;
                        Data.CIN3Lesions.push_back (Woman::High58);
                        Data.CIN3LesionTimer.push_back (1);
                    } else if (rand < (pHPV_CIN2 + pHPV_CIN3 + Tables.pHPV_high5_NL[Data.HPVinfectionTimer[i]])) {
                        Data.hpv58 = false;
                        Data.wasHPV58flag = true;
                        Data.HPVinfections.erase (Data.HPVinfections.begin () + i);
                        Data.HPVinfectionTimer.erase (Data.HPVinfectionTimer.begin () + i);
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
        if (Data.wasHPVloflag) {
            immune_deg_LR = Tables.ImmuneDegreeLR;
        } else {
            immune_deg_LR = 1.00;
        }
        if (Data.wasHPVotherHRflag) {
            immune_deg_otherHR = Tables.ImmuneDegreeotherHR;
        } else {
            immune_deg_otherHR = 1.00;
        }
        if (Data.wasHPV16flag) {
            immune_deg_16 = Tables.ImmuneDegree16;
        } else {
            immune_deg_16 = 1.00;
        }
        if (Data.wasHPV18flag) {
            immune_deg_18 = Tables.ImmuneDegree18;
        } else {
            immune_deg_18 = 1.00;
        }
        if (Data.wasHPV31flag) {
            immune_deg_31 = Tables.ImmuneDegree31;
        } else {
            immune_deg_31 = 1.00;
        }
        if (Data.wasHPV33flag) {
            immune_deg_33 = Tables.ImmuneDegree33;
        } else {
            immune_deg_33 = 1.00;
        }
        if (Data.wasHPV45flag) {
            immune_deg_45 = Tables.ImmuneDegree45;
        } else {
            immune_deg_45 = 1.00;
        }
        if (Data.wasHPV52flag) {
            immune_deg_52 = Tables.ImmuneDegree52;
        } else {
            immune_deg_52 = 1.00;
        }
        if (Data.wasHPV58flag) {
            immune_deg_58 = Tables.ImmuneDegree58;
        } else {
            immune_deg_58 = 1.00;
        }

        if (Data.vaccinated) {

            vaccine_deg_1618 = 1 - Tables.VE_1618 * Tables.VaccineEfficacy;
            vaccine_deg_high5 = 1 - Tables.VE_high5 * Tables.VaccineEfficacy;

            if (Data.CurrentAge > (Tables.VaccineDuration + Tables.VaccineStartAge)) {

                vaccine_deg_1618 = GetEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                           (Tables.VaccineDuration + Tables.VaccineStartAge),
                                           (1 - Tables.VE_1618 * Tables.VaccineEfficacy));

                vaccine_deg_high5 = GetEff (Tables.VaccineWaneTime, Data.CurrentAge,
                                            (Tables.VaccineDuration + Tables.VaccineStartAge),
                                            (1 - Tables.VE_high5 * Tables.VaccineEfficacy));

            }
        } else {
            vaccine_deg_1618 = 1;
            vaccine_deg_high5 = 1;
        }

        if (Data.cancer) {
            CancerNatHistory (Data, Tables, Count, y, help);
        } else {
            if (!Data.CIN3Lesions.empty ()) {
                StateMachine::StartCIN (Data, Count, Tables, y, help);
            }
            if (!Data.HPVinfections.empty ()) {
                StateMachine::HPVNatHistory (Data, Tables, Count, help);
            }

            StateMachine::AcquireHPV16 (Data, Count, Tables, help);
            StateMachine::AcquireHPV18 (Data, Count, Tables, help);
            StateMachine::AcquireHPV31 (Data, Count, Tables, help);
            StateMachine::AcquireHPV33 (Data, Count, Tables, help);
            StateMachine::AcquireHPV45 (Data, Count, Tables, help);
            StateMachine::AcquireHPV52 (Data, Count, Tables, help);
            StateMachine::AcquireHPV58 (Data, Count, Tables, help);
            StateMachine::AcquireHPVoHR (Data, Count, Tables, help);
            StateMachine::AcquireHPVLow (Data, Count, Tables, help);

        }
    }
}

void StateMachine::HPVScreen(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {

    if (Tables.screenstrat == Inputs::HPV) {
        int ScreenFrequency;
        Data.hpv_first_hiv = Tables.ScreenStartAge;
        ScreenFrequency = Tables.ScreenFrequency;

        if (Data.Alive) {
            if (Data.CurrentAge >= Data.hpv_first_hiv && Data.CurrentAge <= Tables.ScreenStopAge) {
                if (!Data.hpvstart) {
                    Data.hpvtest++;
                    Data.nextscreenage = Data.CurrentAge + ScreenFrequency;
                    Data.hpv_first_hiv = Data.CurrentAge;
                    Data.hpvage.push_back (Data.CurrentAge);
                    Data.hpvstart = true;
                    Count.cost[y] += Tables.cHPVTest;
                    Count.cost[y] += Tables.cReturnforResult;
                    Count.cost[y] += Tables.cPtTime;

                    if (Data.cancer) {
                        switch (Data.cancerstage) {
                            case Woman::Stage0:
                                break;
                            case Woman::Stage1:
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    Data.cancerstage = Data.Stage1d;
                                    rand = help.getrand ();
                                    if (rand < Tables.cryoelig_Ca) {
                                        StateMachine::Cryo (Data, Tables, Count, y, help);
                                    } else {
                                        StateMachine::Colpo (Data, Tables, Count, y, help);
                                    }
                                }
                                break;
                            case Woman::Stage2:
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    Data.cancerstage = Data.Stage2d;
                                    rand = help.getrand ();
                                    if (rand < Tables.cryoelig_Ca) {
                                        StateMachine::Cryo (Data, Tables, Count, y, help);
                                    } else {
                                        StateMachine::Colpo (Data, Tables, Count, y, help);
                                    }
                                }
                                break;
                            case Woman::Stage3:
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    Data.cancerstage = Data.Stage3d;
                                    rand = help.getrand ();
                                    if (rand < Tables.cryoelig_Ca) {
                                        StateMachine::Cryo (Data, Tables, Count, y, help);
                                    } else {
                                        StateMachine::Colpo (Data, Tables, Count, y, help);
                                    }
                                }
                                break;
                            case Woman::Stage1d:break;
                            case Woman::Stage2d:break;
                            case Woman::Stage3d:break;
                        }
                    } else {
                        if (!Data.HPVinfections.empty ()) {
                            if (Data.hpv16 || Data.hpv18 || Data.hpv31 || Data.hpv33 || Data.hpv45 ||
                                Data.hpv52 || Data.hpv58 || Data.otherHR) {
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    rand = help.getrand ();
                                    if (!Data.CIN3Lesions.empty ()) {
                                        if (rand < Tables.cryoelig_CIN3) {
                                            StateMachine::Cryo (Data, Tables, Count, y, help);
                                        } else {
                                            StateMachine::Colpo (Data, Tables, Count, y, help);
                                        }
                                    } else {
                                        if (!Data.CIN2Lesions.empty ()) {
                                            if (rand < Tables.cryoelig_CIN2) {
                                                StateMachine::Cryo (Data, Tables, Count, y, help);
                                            } else {
                                                StateMachine::Colpo (Data, Tables, Count, y, help);
                                            }
                                        } else {
                                            if (rand < Tables.cryoelig_NL) {
                                                StateMachine::Cryo (Data, Tables, Count, y, help);
                                            } else {
                                                StateMachine::Colpo (Data, Tables, Count, y, help);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (Data.CurrentAge >= Data.nextscreenage && Data.CurrentAge <= Tables.ScreenStopAge) {
                    Data.hpvtest++;
                    Data.hpvage.push_back (Data.CurrentAge);
                    Count.cost[y] += Tables.cHPVTest;
                    Count.cost[y] += Tables.cReturnforResult;
                    Count.cost[y] += Tables.cPtTime;
                    Data.nextscreenage = Data.CurrentAge + ScreenFrequency;

                    if (Data.cancer) {
                        switch (Data.cancerstage) {
                            case Woman::Stage0:
                                break;
                            case Woman::Stage1:
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    Data.cancerstage = Data.Stage1d;
                                    rand = help.getrand ();
                                    if (rand < Tables.cryoelig_Ca) {
                                        StateMachine::Cryo (Data, Tables, Count, y, help);
                                    } else {
                                        StateMachine::Colpo (Data, Tables, Count, y, help);
                                    }
                                }
                                break;
                            case Woman::Stage2:
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    Data.cancerstage = Data.Stage2d;
                                    rand = help.getrand ();
                                    if (rand < Tables.cryoelig_Ca) {
                                        StateMachine::Cryo (Data, Tables, Count, y, help);
                                    } else {
                                        StateMachine::Colpo (Data, Tables, Count, y, help);
                                    }
                                }
                                break;
                            case Woman::Stage3:
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    Data.cancerstage = Data.Stage3d;
                                    rand = help.getrand ();
                                    if (rand < Tables.cryoelig_Ca) {
                                        StateMachine::Cryo (Data, Tables, Count, y, help);
                                    } else {
                                        StateMachine::Colpo (Data, Tables, Count, y, help);
                                    }
                                }
                                break;
                            case Woman::Stage1d:break;
                            case Woman::Stage2d:break;
                            case Woman::Stage3d:break;
                        }
                    } else {
                        if (!Data.HPVinfections.empty ()) {
                            if (Data.hpv16 || Data.hpv18 || Data.hpv31 || Data.hpv33 || Data.hpv45
                                || Data.hpv52 || Data.hpv58 || Data.otherHR) {
                                rand = help.getrand ();
                                if (rand < Tables.hpvsens_CIN) {
                                    rand = help.getrand ();
                                    if (!Data.CIN3Lesions.empty ()) {
                                        if (rand < Tables.cryoelig_CIN3) {
                                            StateMachine::Cryo (Data, Tables, Count, y, help);
                                        } else {
                                            StateMachine::Colpo (Data, Tables, Count, y, help);
                                        }
                                    } else {
                                        if (!Data.CIN2Lesions.empty ()) {
                                            if (rand < Tables.cryoelig_CIN2) {
                                                StateMachine::Cryo (Data, Tables, Count, y, help);
                                            } else {
                                                StateMachine::Colpo (Data, Tables, Count, y, help);
                                            }
                                        } else {
                                            if (rand < Tables.cryoelig_NL) {
                                                StateMachine::Cryo (Data, Tables, Count, y, help);
                                            } else {
                                                StateMachine::Colpo (Data, Tables, Count, y, help);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void StateMachine::ClearHPV(Woman &Data, Woman::hpvT genotype) {

    int i = 0;
    while (i < Data.HPVinfections.size ()) {
        if (Data.HPVinfections[i] == genotype) {
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
            Data.hpv = false;
            Data.hpvlo = 0;
            break;
        case Woman::otherHR:
            Data.wasHPVotherHRflag = true;
            Data.hpv = false;
            Data.hpvotherHR = false;
            break;
        case Woman::High16:
            Data.wasHPV16flag = true;
            Data.hpv = false;
            Data.hpv16 = false;
            break;
        case Woman::High18:
            Data.wasHPV18flag = true;
            Data.hpv = false;
            Data.hpv18 = false;
            break;
        case Woman::High31:
            Data.wasHPV31flag = true;
            Data.hpv = false;
            Data.hpv31 = false;
            break;
        case Woman::High33:
            Data.wasHPV33flag = true;
            Data.hpv = false;
            Data.hpv33 = false;
            break;
        case Woman::High45:
            Data.wasHPV45flag = true;
            Data.hpv = false;
            Data.hpv45 = false;
            break;
        case Woman::High52:
            Data.wasHPV52flag = true;
            Data.hpv = false;
            Data.hpv52 = false;
            break;
        case Woman::High58:
            Data.wasHPV58flag = true;
            Data.hpv = false;
            Data.hpv58 = false;
            break;
    }
}

void StateMachine::StartCIN(Woman &Data, Output &Count, Inputs &Tables, int y, helper &help) {

    for (int i = 0; i < Data.CIN3Lesions.size (); i++) {
        switch (Data.CIN3Lesions[i]) {
            case Woman::No:
                break;
            case Woman::Low:
                rand = help.getrand ();
                if (rand < (Tables.pCIN3_NL_LR[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::Low);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::otherHR:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_oHR[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_allother[y]++;
                    Count.cancerHIVpos++;
                    Count.CAotherHRHIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_oHR[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_oHR[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::otherHR);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High16:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_1618[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_1618[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CA1618HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_1618[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_1618[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High16);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High18:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_1618[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_1618[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CA1618HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_1618[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_1618[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High18);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High31:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CAhigh5HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High31);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High33:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CAhigh5HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High33);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High45:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CAhigh5HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High45);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High52:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CAhigh5HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High52);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
            case Woman::High58:
                rand = help.getrand ();
                if (rand < Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]]) {
                    Data.cancer = true;
                    Data.cancerstage = Data.Stage1;
                    Data.ca1Timer++;
                    Count.HIVCAcount[Data.CurrentAge]++;
                    Count.TotalCancer[y]++;
                    Count.TotalCancer_nonavalent[y]++;
                    Count.cancerHIVpos++;
                    Count.CAhigh5HIV++;
                    Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                    Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                    i--;
                    break;
                } else if (rand < (Tables.pCIN3_CA1_high5[Data.CIN3LesionTimer[i]] +
                                   Tables.pCIN3_NL_high5[Data.CIN3LesionTimer[i]])) {
                    rand = help.getrand ();
                    if (rand < Tables.pRegressToHPV) {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                    } else {
                        Data.CIN3Lesions.erase (Data.CIN3Lesions.begin () + i);
                        Data.CIN3LesionTimer.erase (Data.CIN3LesionTimer.begin () + i);
                        i--;
                        StateMachine::ClearHPV (Data, Woman::High58);
                    }
                } else {
                    Data.CIN3LesionTimer[i]++;
                }
                break;
        }
    }



    if(Tables.lesion_progression){
        for (int i = 0; i < Data.CIN2Lesions.size (); i++) {
            switch (Data.CIN2Lesions[i]) {
                case Woman::High16:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_1618[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_1618[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CA1618HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_1618[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_1618[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High16);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::No:
                    break;
                case Woman::Low:
                    rand = help.getrand ();
                    if (rand < (Tables.pCIN2_NL_LR[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            StateMachine::ClearHPV (Data, Woman::Low);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::Low);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::otherHR:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_oHR[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_allother[y]++;
                        Count.cancerHIVpos++;
                        Count.CAotherHRHIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_oHR[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_oHR[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::otherHR);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High18:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_1618[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_1618[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CA1618HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_1618[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_1618[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High18);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High31:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CAhigh5HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High31);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High33:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CAhigh5HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High33);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High45:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CAhigh5HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High45);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High52:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CAhigh5HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High52);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High58:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]]) {
                        Data.cancer = true;
                        Data.cancerstage = Data.Stage1;
                        Data.ca1Timer++;
                        Count.HIVCAcount[Data.CurrentAge]++;
                        Count.TotalCancer[y]++;
                        Count.TotalCancer_nonavalent[y]++;
                        Count.cancerHIVpos++;
                        Count.CAhigh5HIV++;
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CA1_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High58);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
            }
        }
    } else {
        for (int i = 0; i < Data.CIN2Lesions.size (); i++) {
            switch (Data.CIN2Lesions[i]) {
                case Woman::High16:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_1618[Data.CIN2LesionTimer[i]]) {
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        Data.CIN3Lesions.push_back(Woman::High16);
                        Data.CIN3LesionTimer.push_back(1);
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_1618[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_1618[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High16);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::No:
                    break;
                case Woman::Low:
                    rand = help.getrand ();
                    if (rand < (Tables.pCIN2_NL_LR[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            StateMachine::ClearHPV (Data, Woman::Low);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::Low);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::otherHR:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_oHR[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::otherHR);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_oHR[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_oHR[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::otherHR);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High18:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_1618[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::High18);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_1618[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_1618[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High18);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High31:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::High31);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High31);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High33:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::High33);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High33);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High45:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::High45);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High45);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High52:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::High52);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High52);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
                case Woman::High58:
                    rand = help.getrand ();
                    if (rand < Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]]) {
                        Data.CIN3Lesions.push_back(Woman::High58);
                        Data.CIN3LesionTimer.push_back(1);
                        Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                        Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                        i--;
                        break;
                    } else if (rand < (Tables.pCIN2_CIN3_high5[Data.CIN2LesionTimer[i]] +
                                       Tables.pCIN2_NL_high5[Data.CIN2LesionTimer[i]])) {
                        rand = help.getrand ();
                        if (rand < Tables.pRegressToHPV) {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                        } else {
                            Data.CIN2Lesions.erase (Data.CIN2Lesions.begin () + i);
                            Data.CIN2LesionTimer.erase (Data.CIN2LesionTimer.begin () + i);
                            i--;
                            StateMachine::ClearHPV (Data, Woman::High58);
                        }
                    } else {
                        Data.CIN2LesionTimer[i]++;
                    }
                    break;
            }
        }
    }
}

void StateMachine::runPopulationYear(Woman &Data, Inputs &Tables, Output &Count, int y, int CurrentModelYear, bool burnin, helper &help) {

    if (Data.Alive) {

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

        rand = help.getrand ();

        if (rand < mASR) {
            Data.Alive = false;
        } else {
            if (!burnin) {
                if (Data.ScreenAccess) {
                    StateMachine::HPVScreen (Data, Tables, Count, y, help);
                }
            }
            StateMachine::NatHistory (Data, Tables, Count, y, help);
        }

        Count.createTrace (Data, y);
        if (!burnin) {
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

    //todo-JAMIE consider allowing some HPV to persist after cryotherapy

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
            if (rand < Tables.CryoSuccessRateCIN) {
                Data.CIN3Lesions.clear ();
                Data.CIN2Lesions.clear ();
                Data.CIN3LesionTimer.clear();
                Data.CIN2LesionTimer.clear();

                rand = help.getrand ();
                if (rand < Tables.CryoSuccessRateHPV) {
                    if (Data.hpv16) {
                        StateMachine::ClearHPV (Data, Woman::High16);
                    }
                    if (Data.hpv18) {
                        StateMachine::ClearHPV (Data, Woman::High18);
                    }
                    if (Data.hpv31) {
                        StateMachine::ClearHPV (Data, Woman::High31);
                    }
                    if (Data.hpv33) {
                        StateMachine::ClearHPV (Data, Woman::High33);
                    }
                    if (Data.hpv45) {
                        StateMachine::ClearHPV (Data, Woman::High45);
                    }
                    if (Data.hpv52) {
                        StateMachine::ClearHPV (Data, Woman::High52);
                    }
                    if (Data.hpv58) {
                        StateMachine::ClearHPV (Data, Woman::High58);
                    }
                    if (Data.hpvotherHR) {
                        StateMachine::ClearHPV (Data, Woman::otherHR);
                    }
                    if (Data.hpvlo) {
                        StateMachine::ClearHPV (Data, Woman::Low);
                    }
                }
            }
        } else if (!Data.HPVinfections.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.CryoSuccessRateHPV) {
                if (Data.hpv16) {
                    StateMachine::ClearHPV (Data, Woman::High16);
                }
                if (Data.hpv18) {
                    StateMachine::ClearHPV (Data, Woman::High18);
                }
                if (Data.hpv31) {
                    StateMachine::ClearHPV (Data, Woman::High31);
                }
                if (Data.hpv33) {
                    StateMachine::ClearHPV (Data, Woman::High33);
                }
                if (Data.hpv45) {
                    StateMachine::ClearHPV (Data, Woman::High45);
                }
                if (Data.hpv52) {
                    StateMachine::ClearHPV (Data, Woman::High52);
                }
                if (Data.hpv58) {
                    StateMachine::ClearHPV (Data, Woman::High58);
                }
                if (Data.hpvotherHR) {
                    StateMachine::ClearHPV (Data, Woman::otherHR);
                }
                if (Data.hpvlo) {
                    StateMachine::ClearHPV (Data, Woman::Low);
                }
            }
        }
    }
}

void StateMachine::Colpo(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help) {

    Count.cost[y] += Tables.cPtTime;
    Count.cost[y] += Tables.cColpoProc;
    Count.cost[y] += Tables.cColpoTime;

    if (Data.cancer) {
        rand = help.getrand ();
        if(rand < Tables.cryoelig_Ca){
            StateMachine::Cryo (Data, Tables, Count, y, help);
        } else {
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
        }
    } else {
        if (!Data.CIN3Lesions.empty () || !Data.CIN2Lesions.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.colposens[1][1]) {
                StateMachine::Cryo (Data, Tables, Count, y, help);
            }
        } else if (!Data.HPVinfections.empty ()) {
            rand = help.getrand ();
            if (rand < Tables.colposens[1][0]) {
                StateMachine::Cryo (Data, Tables, Count, y, help);
            }
        } else {
            rand = help.getrand ();
            if (rand < Tables.colposens[1][0]) {
                StateMachine::Cryo (Data, Tables, Count, y, help);
            }
        }
    }
}

double StateMachine::GetEff(double wanetime, int age, int waneage, double starteff) {

    double slope = -starteff / wanetime;
    double efficacy = (slope * (age - waneage)) + starteff;

    if (efficacy < 0) {
        efficacy = 0;
    }
    return (efficacy);
}

void StateMachine::AcquireHPV16(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_1618[Data.CurrentAge] * immune_deg_16 * vaccine_deg_1618) {
                Data.hpv = true;
                Data.hpv16 = true;
                Data.HPVinfections.push_back (Woman::High16);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv16) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_1618[Data.CurrentAge] * immune_deg_16 * vaccine_deg_1618) {
                Data.hpv = true;
                Data.hpv16 = true;
                Data.HPVinfections.push_back (Woman::High16);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }
}

void StateMachine::AcquireHPV18(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_1618[Data.CurrentAge] * immune_deg_18 * vaccine_deg_1618) {
                Data.hpv = true;
                Data.hpv18 = true;
                Data.HPVinfections.push_back (Woman::High18);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv18) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_1618[Data.CurrentAge] * immune_deg_18 * vaccine_deg_1618) {
                Data.hpv = true;
                Data.hpv18 = true;
                Data.HPVinfections.push_back (Woman::High18);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }

}

void StateMachine::AcquireHPV31(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_31 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv31 = true;
                Data.HPVinfections.push_back (Woman::High31);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv31) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_31 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv31 = true;
                Data.HPVinfections.push_back (Woman::High31);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }

}

void StateMachine::AcquireHPV33(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_33 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv33 = true;
                Data.HPVinfections.push_back (Woman::High33);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv33) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_33 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv33 = true;
                Data.HPVinfections.push_back (Woman::High33);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }

}

void StateMachine::AcquireHPV45(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_45 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv45 = true;
                Data.HPVinfections.push_back (Woman::High45);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv45) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_45 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv45 = true;
                Data.HPVinfections.push_back (Woman::High45);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }

}

void StateMachine::AcquireHPV52(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_52 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv52 = true;
                Data.HPVinfections.push_back (Woman::High52);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv52) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_52 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv52 = true;
                Data.HPVinfections.push_back (Woman::High52);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }
}

void StateMachine::AcquireHPV58(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_58 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv58 = true;
                Data.HPVinfections.push_back (Woman::High58);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpv58) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_high5[Data.CurrentAge] * immune_deg_58 * vaccine_deg_high5) {
                Data.hpv = true;
                Data.hpv58 = true;
                Data.HPVinfections.push_back (Woman::High58);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }

}

void StateMachine::AcquireHPVoHR(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_otherHR[Data.CurrentAge] * immune_deg_otherHR) {
                Data.hpv = true;
                Data.hpvotherHR = true;
                Data.HPVinfections.push_back (Woman::otherHR);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpvotherHR) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_otherHR[Data.CurrentAge] * immune_deg_otherHR) {
                Data.hpv = true;
                Data.hpvotherHR = true;
                Data.HPVinfections.push_back (Woman::otherHR);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }
}

void StateMachine::AcquireHPVLow(Woman &Data, Output &Count, Inputs &Tables, helper &help) {

    if(!Tables.multiple_infections){
        if(Data.HPVinfections.empty()){
            rand = help.getrand ();
            if (rand < Tables.pHPV_LR[Data.CurrentAge] * immune_deg_LR) {
                Data.hpv = true;
                Data.hpvlo = true;
                Data.HPVinfections.push_back (Woman::Low);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    } else {
        if (!Data.hpvlo) {
            rand = help.getrand ();
            if (rand < Tables.pHPV_LR[Data.CurrentAge] * immune_deg_LR) {
                Data.hpv = true;
                Data.hpvlo = true;
                Data.HPVinfections.push_back (Woman::Low);
                Data.HPVinfectionTimer.push_back (1);
                Count.HIVHPVcount[Data.CurrentAge]++;
            }
        }
    }

}

double StateMachine::GetLesionRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype) {
    if(!Tables.multiple_lesions){
        if(Data.CIN2Lesions.empty()){
            switch(genotype){
                case Woman::No:
                    break;
                case Woman::Low:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_LR_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_LR_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::otherHR:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_otherHR_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_otherHR_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High16:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High18:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High31:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High33:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High45:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High52:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                    }
                    break;
                case Woman::High58:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[0]];
                    } else {
                        pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                    }
                    break;
            }
        } else {
            pHPV_CIN2 = 0;
        }

        if(Tables.lesion_progression){
            if(Data.CIN3Lesions.empty()){
                switch(genotype){
                    case Woman::No:
                        break;
                    case Woman::Low:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_LR_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_LR_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::otherHR:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_otherHR_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_otherHR_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High16:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High18:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High31:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High33:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High45:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High52:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                        }
                        break;
                    case Woman::High58:
                        if(Tables.duration_based_persistence){
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[0]];
                        } else {
                            pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                        }
                        break;
                }
            } else {
                pHPV_CIN3 = 0;
            }
        } else {
            pHPV_CIN3 = 0;
        }
    } else {
        if(Tables.lesion_progression){
            switch(genotype){
                case Woman::No:
                    break;
                case Woman::Low:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_LR_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_LR_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::otherHR:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_otherHR_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_otherHR_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High16:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High18:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_1618_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High31:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High33:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High45:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High52:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                    }
                    break;
                case Woman::High58:
                    if(Tables.duration_based_persistence){
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.HPVinfectionTimer[i]];
                    } else {
                        pHPV_CIN3 = Tables.pHPV_high5_CIN3[Data.CurrentAge];
                    }
                    break;
            }
        } else {
            pHPV_CIN3 = 0;
        }
        switch(genotype){
            case Woman::No:
                break;
            case Woman::Low:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_LR_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_LR_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::otherHR:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_otherHR_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_otherHR_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High16:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High18:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_1618_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High31:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High33:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High45:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High52:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                }
                break;
            case Woman::High58:
                if(Tables.duration_based_persistence){
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.HPVinfectionTimer[i]];
                } else {
                    pHPV_CIN2 = Tables.pHPV_high5_CIN2[Data.CurrentAge];
                }
                break;
        }
    }
}


StateMachine::~StateMachine(void) = default;