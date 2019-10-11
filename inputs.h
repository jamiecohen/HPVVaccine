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
    int CohortSize;
    int ModelStartAge;
    int ModelStopAge;
    int SimulationYears;
    int StartYear;
    int Simulations;
    int Tuning_Factor;

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

    std::string CostsFile;
    std::vector< std::vector<double> > costs;

    std::string UtilitiesFile;
    std::vector< std::vector<double> > utilities;

    std::string VaccineEfficacyFile;
    std::vector< std::vector<double> > vaccineefficacy;

    int ScreenStartAge;
    int ScreenStopAge;
    int ScreenFrequency;
    double ScreenCoverage;
    double ScreenCompliance;
    double AdequacyLBC;
    double AdequacyCC;
    double ColpoAvail;
    double CryoAvail;
    double VaccineCoverage;
    int VaccineDuration;
    int VaccineStartAge;
    double VaccineEfficacyPerinatalHIV;
    double VaccineEfficacySexualHIV;
    double VaccineWaneTime;
    int VaccineDose;
    bool ImmuneAfterClearance;
    bool WaningImmunity;
    int ImmuneDuration;
    int ImmuneWaneTime;

    double pSeroConvert_16[5];
    double pSeroConvert_18[5];
    double pSeroConvert_high5[5];

    std::string SeroConversionFile;
    std::vector< std::vector<double> > SeroConversion;

    std::string ScreenDistFile;
    std::vector< std::vector<double> > ScreenDist;

    std::string CytoSensFile;
    std::vector< std::vector<double> > cytosens;

    std::string CytoSensHIVFile;
    std::vector< std::vector<double> > cytosens_HIV;

    std::string CalibTargsFile;
    std::vector< std::vector<double> > CalibTargs;

    std::string MultipliersFile;
    std::vector< std::vector<double> > Multipliers;

    std::string MultipliersNamesFile;
    std::string MultipliersNames;

    std::string CalibTargsNamesFile;
    std::string CalibTargsNames;

    std::string ColpoSensFile;
    std::vector< std::vector<double> > colposens;

    std::string CryoEligibilityFile;
    std::vector< std::vector<double> > cryoelig;

    double CryoSuccessRateCIN;
    double CryoSuccessRateHPV;
    double LLETZSuccessRateCIN;
    double LLETZSuccessRateHPV;

    std::string VaccineType;

    enum VxType { Bivalent = 0, Nonavalent = 1
    };
    VxType vaccinetype;

    double VE_1618;
    double VE_high5;

    std::string HPVSensFile;
    std::vector< std::vector<double> > hpvsens;

    //[Multipliers] variable names
    //[NaturalImmunity Multipliers] variable names
    double ImmuneDegree;

    // new parameters

    double CIN2_NL_1_5;
    double CIN2_NL_6_10;
    double CIN2_NL_11_20;
    double CIN2_NL_21_29;
    double CIN2_NL_30_39;
    double CIN2_NL_40_49;
    double CIN2_NL_50;
    double CIN2_NL_LR;
    double CIN2_NL_high5;
    double CIN2_NL_16;
    double CIN2_NL_18;
    double CIN2_NL_otherHR;
    double HPV_NL_0_1;
    double HPV_NL_1_2;
    double HPV_NL_2_5;
    double HPV_NL_5;
    double HPV_NL_LR;
    double HPV_NL_16;
    double HPV_NL_18;
    double HPV_NL_high5;
    double HPV_NL_otherHR;
    double HPV_CIN2_0_1;
    double HPV_CIN2_1_2;
    double HPV_CIN2_2_5;
    double HPV_CIN2_5;
    double HPV_CIN2_LR;
    double HPV_CIN2_high5;
    double HPV_CIN2_otherHR;
    double HPV_CIN2_16;
    double HPV_CIN2_18;
    double CIN3_CA_1_5;
    double CIN3_CA_6_10;
    double CIN3_CA_11_20;
    double CIN3_CA_21_29;
    double CIN3_CA_30_39;
    double CIN3_CA_40_49;
    double CIN3_CA_50;
    double CIN3_CA_16;
    double CIN3_CA_18;
    double CIN3_CA_otherHR;
    double CIN3_CA_high5;
    double CA1_CA2;
    double CA2_CA3;
    double CIN3_CA_mult;
    double CIN2_NL_mult;
    double HPV_CIN2_mult;

    double cryoelig_NL;
    double cryoelig_CIN2;
    double cryoelig_CIN3;
    double cryoelig_Ca;
    double cPapTest;
    double cPapLBCTest;
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
    double cCryoCIN23;
    double cLLETZ;

    double utilityHealthy;
    double utilityHPV;
    double utilityCIN2;
    double utilityCIN3;
    double utilityCA1;
    double utilityCA2;
    double utilityCA3;


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

    // HPV  incidence


    double pHPV_LR[100];
    double pHPV_otherHR[100];
    double pHPV_16[100];
    double pHPV_18[100];
    double pHPV_31[100];
    double pHPV_33[100];
    double pHPV_45[100];
    double pHPV_52[100];
    double pHPV_58[100];

    // CIN/Ca progression

    double pCIN2_CA1_16[100];
    double pCIN3_CA1_16[100];
    double pCIN2_CA1_18[100];
    double pCIN3_CA1_18[100];
    double pCIN2_CA1_oHR[100];
    double pCIN3_CA1_oHR[100];
    double pCIN2_CA1_high5[100];
    double pCIN3_CA1_high5[100];

    // HPV progression

    double pHPV_LR_CIN2[100];
    double pHPV_otherHR_CIN2[100];
    double pHPV_16_CIN2[100];
    double pHPV_18_CIN2[100];
    double pHPV_high5_CIN2[100];
    double pHPV_LR_CIN3[100];
    double pHPV_otherHR_CIN3[100];
    double pHPV_16_CIN3[100];
    double pHPV_18_CIN3[100];
    double pHPV_high5_CIN3[100];

    // regression

    double pCIN3_NL_16[100];
    double pCIN3_NL_18[100];
    double pCIN3_NL_LR[100];
    double pCIN3_NL_oHR[100];
    double pCIN3_NL_high5[100];

    double pCIN2_NL_16[100];
    double pCIN2_NL_18[100];
    double pCIN2_NL_LR[100];
    double pCIN2_NL_oHR[100];
    double pCIN2_NL_high5[100];

    double pHPV_LR_NL[100];
    double pHPV_otherHR_NL[100];
    double pHPV_16_NL[100];
    double pHPV_18_NL[100];
    double pHPV_high5_NL[100];



    double mCA1[100];
    double mCA2[100];
    double mCA3[100];
    double mCA1d[100];
    double mCA2d[100];
    double mCA3d[100];
    double mCA1dsc[100];
    double mCA2dsc[100];
    double mCA3dsc[100];

    double hpvsens_NL;
    double hpvsens_CIN;
    double hpvsens_Ca;
    double cytosens_NL;
    double cytosens_CIN;
    double cytosens_Ca;
    double pRegresstoHPV;


};

#endif //HPVVaccine_INPUTS_H
