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

    std::vector<int> burnin;

    std::string OutputFolder;
    std::string DataFolder;

    std::string OutputDir;
    int CohortSize;
    int ModelStartAge;
    int ModelStopAge;
    int SimulationYears;
    int BurnInYears;
    int StartYear;
    int Simulations;
    int Tuning_Factor;

    std::string ASRMortalityFile;
    std::vector< std::vector<double> > ASRMortality;

    std::string CaMortalityFile;
    std::vector< std::vector<double> > CaMortality;

    std::string HPVIncidenceFile;
    std::vector< std::vector<double> > HPVInc;

    std::string HPVProgressionFile;
    std::vector< std::vector<double> > HPVProgression;

    std::string HPVClearanceFile;
    std::vector< std::vector<double> > HPVClearance;

    std::string CINProgressionFile;
    std::vector< std::vector<double> > CINProgression;

    std::string CINRegressionFile;
    std::vector< std::vector<double> > CINRegression;

    std::string SymptomDetectionFile;
    std::vector< std::vector<double> > sympdet;

    std::string VaccineEfficacyFile;
    std::vector< std::vector<double> > vaccineefficacy;

    std::string InitialPopulationFile;
    std::vector<std::vector<double> > InitialPopulation;

    int ScreenStartAge;
    int ScreenStopAge;
    int ScreenFrequency;
    double ScreenCoverage;
    double ScreenCompliance;
    double AdequacyLBC;
    double ColpoAvail;
    double VaccineCoverage;
    int VaccineDuration;
    int VaccineStartAge;
    double VaccineWaneTime;
    int VaccineDose;
    std::string MechanismofImmunity;
    bool LatencyTime;
    bool WaningImmunity;
    int ImmuneDuration;
    int ImmuneWaneTime;
    double pSeroConvert_16[5];
    double pSeroConvert_18[5];
    double pSeroConvert_high5[5];

    std::string SeroConversionFile;
    std::vector< std::vector<double> > SeroConversion;

    std::string CytoSensFile;
    std::vector< std::vector<double> > cytosens;

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

    double LLETZSuccessRateCIN;
    double LLETZSuccessRateHPV;

    std::string VaccineType;

    enum VxType { Bivalent = 0, Nonavalent = 1
    };
    VxType vaccinetype;

    double VE_1618;
    double VE_high5;

    double ImmuneDegree;
    double ImmuneDegree16;

    enum Immunity {Degree, Factor, Seropositivity};
    Immunity ImmuneMechanism;

    double CIN2_NL;
    double CIN2_NL_LR;
    double CIN2_NL_high5;
    double CIN2_NL_16;
    double CIN2_NL_18;
    double CIN2_NL_otherHR;
    double HPV_NL_LR;
    double HPV_NL_16;
    double HPV_NL_18;
    double HPV_NL_high5;
    double HPV_NL_otherHR;
    double HPV_CIN_LR;
    double HPV_CIN_high5;
    double HPV_CIN_otherHR;
    double HPV_CIN_16;
    double HPV_CIN_18;
    double CIN3_CA_16;
    double CIN3_CA_18;
    double CIN3_CA_otherHR;
    double CIN3_CA_high5;
    double NL_HPV_16_21;
    double NL_HPV_16_21_25;
    double NL_HPV_16_25_29;
    double NL_HPV_18_21;
    double NL_HPV_18_21_25;
    double NL_HPV_18_25_29;
    double NL_HPV_31_21;
    double NL_HPV_31_21_25;
    double NL_HPV_31_25_29;
    double NL_HPV_33_21;
    double NL_HPV_33_21_25;
    double NL_HPV_33_25_29;
    double NL_HPV_45_21;
    double NL_HPV_45_21_25;
    double NL_HPV_45_25_29;
    double NL_HPV_52_21;
    double NL_HPV_52_21_25;
    double NL_HPV_52_25_29;
    double NL_HPV_58_21;
    double NL_HPV_58_21_25;
    double NL_HPV_58_25_29;
    double CA1_CA2;
    double CA2_CA3;
    double pCA1_CA1D;
    double pCA2_CA2D;
    double pCA3_CA3D;
    double pHPV_LR[100];
    double pHPV_otherHR[100];
    double pHPV_16[100];
    double pHPV_18[100];
    double pHPV_31[100];
    double pHPV_33[100];
    double pHPV_45[100];
    double pHPV_52[100];
    double pHPV_58[100];
    double pCIN2_CA1_16[100];
    double pCIN3_CA1_16[100];
    double pCIN2_CA1_18[100];
    double pCIN3_CA1_18[100];
    double pCIN2_CA1_oHR[100];
    double pCIN3_CA1_oHR[100];
    double pCIN2_CA1_31[100];
    double pCIN3_CA1_31[100];
    double pCIN2_CA1_33[100];
    double pCIN3_CA1_33[100];
    double pCIN2_CA1_45[100];
    double pCIN3_CA1_45[100];
    double pCIN2_CA1_52[100];
    double pCIN3_CA1_52[100];
    double pCIN2_CA1_58[100];
    double pCIN3_CA1_58[100];
    double pHPV_LR_CIN[100];
    double pHPV_otherHR_CIN[100];
    double pHPV_16_CIN[100];
    double pHPV_18_CIN[100];
    double pHPV_31_CIN[100];
    double pHPV_33_CIN[100];
    double pHPV_45_CIN[100];
    double pHPV_52_CIN[100];
    double pHPV_58_CIN[100];
    double pCIN3_NL_16;
    double pCIN3_NL_18;
    double pCIN3_NL_LR;
    double pCIN3_NL_oHR;
    double pCIN3_NL_high5;
    double pCIN2_NL_16;
    double pCIN2_NL_18;
    double pCIN2_NL_LR;
    double pCIN2_NL_oHR;
    double pCIN2_NL_high5;
    double pHPV_LR_NL[100];
    double pHPV_otherHR_NL[100];
    double pHPV_16_NL[100];
    double pHPV_18_NL[100];
    double pHPV_31_NL[100];
    double pHPV_33_NL[100];
    double pHPV_45_NL[100];
    double pHPV_52_NL[100];
    double pHPV_58_NL[100];
    double mCA1[100];
    double mCA2[100];
    double mCA3[100];
    double mCA1d[100];
    double mCA2d[100];
    double mCA3d[100];
    double cytosens_NL;
    double cytosens_CIN;
    double cytosens_Ca;
    double pRegresstoHPV;
    double CIN3_NL = 0.5;
    double CIN2_CA = 0.2;
    double HPV_CIN2_16 = 0.65;
    double HPV_CIN2_allother = 0.8;
    void loadData(ifstream &Infile, vector< vector<double> > &VariableName);
    void loadStringData(ifstream &Infile, std::string &VariableName);
    void loadRFG(std::string& RunsFileName, std::string& CurKey);
    void loadVariables();
    double ApplyMult(double, double);
    void loadCalibParams(vector<double> calib_params);

};

#endif //HPVVaccine_INPUTS_H
