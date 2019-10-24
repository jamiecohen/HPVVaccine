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

    vector<Woman::hpvT> genotypes;
    double pHPV;
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
    double Adequacy;

    StateMachine();
    ~StateMachine();

    void NatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y, bool burnin);
    void HPVNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
    void CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help, int y);
    void runPopulationYear(Woman &Data, Inputs &Tables, Output &Count, bool burnin, helper &help, int y);
    void CytoScreen(Woman &Data, Inputs &Tables,  Output &Count, helper &help);
    void ClearHPV(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype);
    void StartCIN(Woman &Data, Output &Count, Inputs &Tables, helper &help, int y);
    void GetHPVRisk(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    static void GetImmuneDeg(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    void GetImmuneFactor(Woman &Data, Inputs &Tables, helper &help, Woman::hpvT genotype);
    static void GetSeropositivity(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    static void CheckWaningImmunity(Woman &Data, Inputs &Tables);
    static void CheckLatency(Woman &Data, Inputs &Tables, Woman::hpvT genotype);
    void CheckSeropositivity(Woman &Data, Inputs &Tables, helper &help);
    void AcquireHPV(Woman &Data, Output &Count, Inputs &Tables, helper &help, int y);
    void Colpo(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void LLETZ(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void SendforTreatment(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void GetVaccineEff(Woman &Data, Inputs &Tables, bool burnin);
    static double CalcEff(double wanetime, int age, int waneage, double starteff);
    void GetLesionRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetHPVClearanceRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetCIN2Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    void GetCIN3Risk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);
    static void CountCancer(Woman &Data, Output &Count, Woman::hpvT genotype, int i, int y);
    static void CountDetectedCancer(Woman &Data, Output &Count, int y);
    void GetMortality(Woman &Data, Inputs &Tables);
    static void CountCIN2(Woman &Data, Output &Count);
    static void CountCIN3(Woman &Data, Output &Count);
    void GetBackgroundMortality(Woman &Data, Inputs &Tables, helper &help, int y);
};

#endif //HPVVaccine_STATEMACHINE_H