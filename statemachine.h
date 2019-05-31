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

    double mASR;
    double rand;
    double immune_deg_LR;
    double immune_deg_otherHR;
    double immune_deg_16;
    double immune_deg_18;
    double immune_deg_31;
    double immune_deg_33;
    double immune_deg_45;
    double immune_deg_52;
    double immune_deg_58;
    double vaccine_deg_1618;
    double vaccine_deg_high5;
    double pHPV_CIN2;
    double pHPV_CIN3;

    StateMachine();
    ~StateMachine();

    void NatHistory(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help);
    void HPVNatHistory(Woman &Data, Inputs &Tables, Output &Count, helper &help);
    void CancerNatHistory(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help);
    void runPopulationYear(Woman &Data, Inputs &Tables, Output &Count,  int y, int CurrentModelYear, bool burnin, helper &help);
    void HPVScreen(Woman &Data, Inputs &Tables,  Output &Count, int y, helper &help);
    void ClearHPV(Woman &Data, Woman::hpvT genotype);
    void StartCIN(Woman &Data, Output &Count, Inputs &Tables, int y, helper &help);
    void AcquireHPV16(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV18(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV31(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV33(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV45(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV52(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPV58(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPVoHR(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void AcquireHPVLow(Woman &Data, Output &Count, Inputs &Tables, helper &help);
    void Colpo(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help);
    void Cryo(Woman &Data, Inputs &Tables, Output &Count, int y, helper &help);
    double GetEff(double wanetime, int age, int waneage, double intercept);
    double GetLesionRisk(Woman &Data, Inputs &Tables, int i, Woman::hpvT genotype);

};

#endif //HIVHPVVaccine_STATEMACHINE_H