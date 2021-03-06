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
#include <thread>
#include <future>
#include "helper.h"

class StateMachine {
public:

    vector<Woman::hpvT> genotypes;
    double pHPV;
    double mCA;
    double pHPV_NL;
    double pHPV_CIN;
    double prop_CIN2;
    double pCIN3_HPV;
    double pCIN2_HPV;
    double pCIN3_CA;
    double pCIN2_CA;
    double mASR;
    double rand;
    double vaccine_deg_16;
    double vaccine_deg_18;
    double vaccine_deg_31;
    double vaccine_deg_33;
    double vaccine_deg_45;
    double vaccine_deg_52;
    double vaccine_deg_58;
    double vaccine_eff_16;
    double vaccine_eff_18;
    double vaccine_eff_31;
    double vaccine_eff_33;
    double vaccine_eff_45;
    double vaccine_eff_52;
    double vaccine_eff_58;
    int ScreenFrequency;
    double Adequacy;

    StateMachine();
    ~StateMachine();

    void NatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y, bool burnin);
    void HPVNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
    void runPopulationYear(Woman &Data, Inputs &Tables, Output &Count, bool burnin, helper &help, int y);
    void CytoScreen(Woman &Data, Inputs &Tables,  Output &Count, helper &help, int y);
    void ClearHPV(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype);
    void StartCIN(Woman &Data, Output &Count, Inputs &Tables, helper &help, int y);
    void GetHPVRisk(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    static void GetImmuneDeg(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    void GetImmuneFactor(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype);
    static void CheckWaningImmunity(Woman &Data, Inputs &Tables);
    void CheckLatency(Woman &Data, Inputs &Tables, int i);
    void AcquireHPV(Woman &Data, Output &Count, Inputs &Tables, helper &help, int y);
    void Colpo(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
    void LLETZ(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
    void SendforTreatment(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
    void GetVaccineEff(Woman &Data, Inputs &Tables, bool burnin);
    static double CalcEff(double wanetime, int age, int waneage, double starteff);
    void GetLesionRisk(Woman &Data, Inputs &Tables, int i);
    void GetHPVClearanceRisk(Woman &Data, Inputs &Tables, int i);
    void GetCIN2Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetCIN3Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    static void CountCancer(Woman &Data, Output &Count, Woman::hpvT genotype, int i, int y);
    static void CountCIN(Woman &Data, int i);
    static void CountDormancyTime(Woman &Data, int i);
    static void CountDetectedCancer(Woman &Data, Output &Count, int y);
    void GetMortality(Woman &Data, Inputs &Tables);
    void GetBackgroundMortality(Woman &Data, Inputs &Tables, helper &help);
    void Vaccinate(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
};

#endif //HPVVaccine_STATEMACHINE_H