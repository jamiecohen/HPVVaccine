//
// Created by Jamie Cohen on 12/4/17.
//

#ifndef HPVVaccine_INPUTS_H
#define HPVVaccine_INPUTS_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <cstdio>
#include <string>
#include <cmath>
#include <ctime>
#include "iniFile.h"


class Inputs{

public:
    Inputs(std::string Output, std::string Data);

    std::string OutputFolder;
    std::string DataFolder;

    std::string OutputDir;
    std::string VOI;
    int CohortSize;
    int ModelStartAge;
    int ModelStopAge;
    int SimulationYears;
    int StartYear;
    int Iterations;
    int Simulations;
    double Tuning_Factor;

    std::string LifeExpectancyFile;
    std::vector<std::vector<double> > LifeExpectancy;

    std::string DisabilityFile;
    std::vector<std::vector<double> > Disability;

    std::string AgeStandardFile;
    std::vector<std::vector<double> > AgeStandard;

    std::string InitialPopulationFile;
    std::vector<std::vector<double> > InitialPopulation;


    //[NaturalHistory] variable names

    std::string ASRMortalityFile;
    std::vector< std::vector<double> > ASRMortality;

    std::string CaMortalityFile;
    std::vector< std::vector<double> > CaMortality;

    std::string HPVIncidenceFile;
    std::vector< std::vector<double> > HPVInc;

    std::string SymptomDetectionFile;
    std::vector< std::vector<double> > sympdet;


    // [Intervention] variable names

    enum Strategy { NoScreen = 0,
        HPV = 1
    };

    std::string CostsFile;
    std::vector< std::vector<double> > costs;

    std::string UtilitiesFile;
    std::vector< std::vector<double> > utilities;

    std::string ScreenStrategy;
    Strategy screenstrat;

    std::string VaccineEfficacyFile;
    std::vector< std::vector<double> > vaccineefficacy;

    int ScreenStartAge;
    int ScreenStopAge;
    int ScreenFrequency;

    double ScreenCoverage;
    double ScreenCompliance;

    int VaccineDuration;
    int VaccineStartAge;
    double VaccineEfficacy;
    double VaccineWaneTime;

    bool multiple_lesions;
    bool multiple_infections;
    bool duration_based_persistence;
    bool lesion_progression;

    std::string CalibTargsFile;
    std::vector< std::vector<double> > CalibTargs;

    std::string MultipliersFile;
    std::vector< std::vector<double> > Multipliers;

    std::string MultipliersNamesFile;
    std::string MultipliersNames;

    std::string CalibTargsNamesFile;
    std::string CalibTargsNames;

    std::string VaccineType;

    enum VxType {
        Bivalent = 0, Nonavalent = 1
    };
    VxType vaccinetype;

    double VE_1618;
    double VE_high5;

    std::string HPVSensFile;
    std::vector< std::vector<double> > hpvsens;

    std::string ColpoSensFile;
    std::vector< std::vector<double> > colposens;

    std::string CryoEligibilityFile;
    std::vector< std::vector<double> > cryoelig;

    double CryoSuccessRateCIN;
    double CryoSuccessRateHPV;

    //[Multipliers] variable names
    //[NaturalImmunity Multipliers] variable names
    double ImmuneDegreeLR;
    double ImmuneDegreeotherHR;
    double ImmuneDegree16;
    double ImmuneDegree18;
    double ImmuneDegree31;
    double ImmuneDegree33;
    double ImmuneDegree45;
    double ImmuneDegree52;
    double ImmuneDegree58;

    // new parameters

    double CIN3_CA_mult;
    double CIN2_NL_mult;
    double HPV_CIN2_mult;

    double CIN2_NL_1_5;
    double CIN2_NL_6_10;
    double CIN2_NL_11_20;
    double CIN2_NL_21_29;
    double CIN2_NL_30_39;
    double CIN2_NL_40_49;
    double CIN2_NL_50;
    double CIN2_NL_LR;
    double CIN2_NL_high5;
    double CIN2_NL_1618;
    double CIN2_NL_otherHR;
    double HPV_NL_0_1;
    double HPV_NL_1_2;
    double HPV_NL_2_5;
    double HPV_NL_5;
    double HPV_NL_LR;
    double HPV_NL_1618;
    double HPV_NL_high5;
    double HPV_NL_otherHR;
    double HPV_CIN2_0_1;
    double HPV_CIN2_1_2;
    double HPV_CIN2_2_5;
    double HPV_CIN2_5;
    double HPV_CIN2_LR;
    double HPV_CIN2_high5;
    double HPV_CIN2_otherHR;
    double HPV_CIN2_1618;
    double CIN3_CA_1_5;
    double CIN3_CA_6_10;
    double CIN3_CA_11_20;
    double CIN3_CA_21_29;
    double CIN3_CA_30_39;
    double CIN3_CA_40_49;
    double CIN3_CA_50;
    double CIN3_CA_1618;
    double CIN3_CA_otherHR;
    double CIN3_CA_high5;
    double CA1_CA2;
    double CA2_CA3;
    double NL_HPV_LR;
    double NL_HPV_oHR;
    double NL_HPV_1618;
    double NL_HPV_high5;
    double pRegressToHPV;

    double cryoelig_NL;
    double cryoelig_CIN2;
    double cryoelig_CIN3;
    double cryoelig_Ca;
    double cHPVTest;
    double cReturnforResult;
    double cColpoTime;
    double cColpoProc;
    double cTreatHPV;
    double cTreatCIN23;
    double cStage1Ca;
    double cStage2Ca;
    double cStage3Ca;
    double cPtTime;
    double cCryoVisit;
    double cCryoHPV;
    double cCryoCIN23;
    double cCryoCa;
    double cVaccine;

    double utilityHealthy;
    double utilityHPV;
    double utilityCIN2;
    double utilityCIN3;
    double utilityCA1;
    double utilityCA2;
    double utilityCA3;
    double utilityHIVCD4500;
    double utilityHIVCD4200500;
    double utilityHIVCD4200;
    double utilityHIVCA1;
    double utilityHIVCA2;
    double utilityHIVCA3;

    double disabilityCA12;
    double disabilityCA34;

    void loadData(ifstream &Infile, vector< vector<double> > &VariableName);
    void loadStringData(ifstream &Infile, std::string &VariableName);
    void loadRFG(std::string& RunsFileName, std::string& CurKey);
    void loadVariables();
    double ApplyMult(double, double);
    void loadCalibParams(vector<double> calib_params);

    //Symptom Detection

    double pCA1_CA1D;
    double pCA2_CA2D;
    double pCA3_CA3D;


    // HPV and HIV incidence
    double pHPV_LR[100];
    double pHPV_otherHR[100];
    double pHPV_1618[100];
    double pHPV_high5[100];

    // CIN/Ca progression

    double pCIN2_CA1_1618[100];
    double pCIN2_CIN3_1618[100];
    double pCIN3_CA1_1618[100];

    double pCIN2_CA1_oHR[100];
    double pCIN2_CIN3_oHR[100];
    double pCIN3_CA1_oHR[100];

    double pCIN2_CA1_high5[100];
    double pCIN2_CIN3_high5[100];
    double pCIN3_CA1_high5[100];

    // HPV progression

    double pHPV_LR_CIN2[100];
    double pHPV_otherHR_CIN2[100];
    double pHPV_1618_CIN2[100];
    double pHPV_high5_CIN2[100];
    double pHPV_LR_CIN3[100];
    double pHPV_otherHR_CIN3[100];
    double pHPV_1618_CIN3[100];
    double pHPV_high5_CIN3[100];
    

    // regression

    // regression with HIV

    double pCIN3_NL_1618[100];
    double pCIN3_NL_LR[100];
    double pCIN3_NL_oHR[100];
    double pCIN3_NL_high5[100];

    double pCIN2_NL_1618[100];
    double pCIN2_NL_LR[100];
    double pCIN2_NL_oHR[100];
    double pCIN2_NL_high5[100];

    double pHPV_LR_NL[100];
    double pHPV_otherHR_NL[100];
    double pHPV_1618_NL[100];
    double pHPV_high5_NL[100];

    // mortality (background, HIV and cancer)
    double mCA1[100];
    double mCA2[100];
    double mCA3[100];
    double mCA1d[100];
    double mCA2d[100];
    double mCA3d[100];
    double mCA1dsc[100];
    double mCA2dsc[100];
    double mCA3dsc[100];

    double pHPVCIN_ART;
    double pCINNL_ART;
    double hpvsens_NL;
    double hpvsens_CIN;
    double hpvsens_Ca;
    double pResourcesAvail;




};

#endif //HIVHPVVaccine_INPUTS_H
