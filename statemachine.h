//
// Created by Jamie Cohen on 11/15/17.
//

#ifndef HPVVaccine_STATEMACHINE_H
#define HPVVaccine_STATEMACHINE_H

#include <vector>
#include "woman.h"
#include "inputs.h"
#include "outputs.h"
#include <stdlib.h>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <thread>
#include <future>
#include "helper.h"

class StateMachine {
public:

    double mCA;
    double pHPV_NL;
    double pHPV_CIN;
    double pCIN3_HPV;
    double pCIN2_HPV;
    double pCIN3_CA;
    double pCIN2_CA;
    double mASR;
    double rand;
    double vaccine_deg_1618;
    double vaccine_deg_high5;
    double vaccine_eff_1618;
    double vaccine_eff_high5;
    int ScreenFrequency;
    double pHPV_16;
    double pHPV_18;
    double pHPV_31;
    double pHPV_33;
    double pHPV_45;
    double pHPV_52;
    double pHPV_58;
    double pHPV_oHR;
    double pHPV_LR;
    double Adequacy;

    StateMachine();
    ~StateMachine();

    void NatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void HPVNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void runPopulationYear(Woman &Data, Inputs &Tables, Output &Count, bool burnin, helper &help);
    void CytoScreen(Woman &Data, Inputs &Tables,  Output &Count, helper &help);
    void ClearHPV(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype);
    void StartCIN(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void GetHPVRisk(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    static void GetImmuneDeg(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    void GetImmuneFactor(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype);
    static void GetSeropositivity(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    static void CheckWaningImmunity(Woman &Data, Inputs &Tables);
    static void CheckLatency(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    void CheckSeropositivity(Woman &Data, Inputs &Tables, helper &help);
    void AcquireHPV16(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV18(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV31(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV33(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV45(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV52(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV58(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPVoHR(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPVLow(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void Colpo(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void LLETZ(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void SendforTreatment(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void GetVaccineEff(Woman &Data, Inputs &Tables);
    static double CalcEff(double wanetime, int age, int waneage, double starteff);
    void GetLesionRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetHPVClearanceRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetCIN2Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetCIN3Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    static void CountCancer(Woman &Data, Output &Count, Woman::hpvT genotype, int i);
    static void CountDetectedCancer(Woman &Data, Output &Count);
    void GetMortality(Woman &Data, Inputs &Tables);
    static void CountCIN2(Woman &Data, Output &Count);
    static void CountCIN3(Woman &Data, Output &Count);
    void GetBackgroundMortality(Woman &Data, Inputs &Tables, helper &help);
};

#endif //HPVVaccine_STATEMACHINE_H