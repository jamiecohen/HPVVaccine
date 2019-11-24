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
    enum Immunity {Degree, Factor, Seropositivity};
    Immunity ImmuneMechanism;

    double CIN2_NL;

    double CIN2_NL_allother_1;
    double CIN2_NL_allother_2_4;
    double CIN2_NL_allother_5;
    double CIN2_NL_16_1;
    double CIN2_NL_16_2_4;
    double CIN2_NL_16_5;
    double HPV_NL_LR_1;
    double HPV_NL_LR_2_4;
    double HPV_NL_LR_5;
    double HPV_NL_otherHR_1;
    double HPV_NL_otherHR_2_4;
    double HPV_NL_otherHR_5;
    double HPV_NL_high5_1;
    double HPV_NL_high5_2_4;
    double HPV_NL_high5_5;
    double HPV_NL_16_1;
    double HPV_NL_16_2_4;
    double HPV_NL_16_5;
    double HPV_NL_18_1;
    double HPV_NL_18_2_4;
    double HPV_NL_18_5;
    double HPV_CIN_LR_1;
    double HPV_CIN_LR_2_4;
    double HPV_CIN_LR_5;
    double HPV_CIN_otherHR_1;
    double HPV_CIN_otherHR_2_4;
    double HPV_CIN_otherHR_5;
    double HPV_CIN_high5_1;
    double HPV_CIN_high5_2_4;
    double HPV_CIN_high5_5;
    double HPV_CIN_16_1;
    double HPV_CIN_16_2_4;
    double HPV_CIN_16_5;
    double HPV_CIN_18_1;
    double HPV_CIN_18_2_4;
    double HPV_CIN_18_5;
    double CIN3_CA_high5_1_5;
    double CIN3_CA_high5_6_10;
    double CIN3_CA_high5_11_20;
    double CIN3_CA_high5_21_30;
    double CIN3_CA_high5_31_40;
    double CIN3_CA_high5_41_50;
    double CIN3_CA_high5_50;
    double CIN3_CA_16_1_5;
    double CIN3_CA_16_6_10;
    double CIN3_CA_16_11_20;
    double CIN3_CA_16_21_30;
    double CIN3_CA_16_31_40;
    double CIN3_CA_16_41_50;
    double CIN3_CA_16_50;
    double CIN3_CA_18_1_5;
    double CIN3_CA_18_6_10;
    double CIN3_CA_18_11_20;
    double CIN3_CA_18_21_30;
    double CIN3_CA_18_31_40;
    double CIN3_CA_18_41_50;
    double CIN3_CA_18_50;
    double CIN3_CA_otherHR_1_5;
    double CIN3_CA_otherHR_6_10;
    double CIN3_CA_otherHR_11_20;
    double CIN3_CA_otherHR_21_30;
    double CIN3_CA_otherHR_31_40;
    double CIN3_CA_otherHR_41_50;
    double CIN3_CA_otherHR_50;
    double NL_HPV16_17_19;
    double NL_HPV16_20_24;
    double NL_HPV16_25_29;
    double NL_HPV16_30_34;
    double NL_HPV16_35_39;
    double NL_HPV16_40_44;
    double NL_HPV16_45_49;
    double NL_HPV16_50_54;
    double NL_HPV16_55_65;
    double NL_HPV18_17_19;
    double NL_HPV18_20_24;
    double NL_HPV18_25_29;
    double NL_HPV18_30_34;
    double NL_HPV18_35_39;
    double NL_HPV18_40_44;
    double NL_HPV18_45_49;
    double NL_HPV18_50_54;
    double NL_HPV18_55_65;
    double NL_HPVhigh5_17_19;
    double NL_HPVhigh5_20_24;
    double NL_HPVhigh5_25_29;
    double NL_HPVhigh5_30_34;
    double NL_HPVhigh5_35_39;
    double NL_HPVhigh5_40_44;
    double NL_HPVhigh5_45_49;
    double NL_HPVhigh5_50_54;
    double NL_HPVhigh5_55_65;
    double NL_HPVoHR_17_19;
    double NL_HPVoHR_20_24;
    double NL_HPVoHR_25_29;
    double NL_HPVoHR_30_34;
    double NL_HPVoHR_35_39;
    double NL_HPVoHR_40_44;
    double NL_HPVoHR_45_49;
    double NL_HPVoHR_50_54;
    double NL_HPVoHR_55_65;
    double NL_HPVLR_17_19;
    double NL_HPVLR_20_24;
    double NL_HPVLR_25_29;
    double NL_HPVLR_30_34;
    double NL_HPVLR_35_39;
    double NL_HPVLR_40_44;
    double NL_HPVLR_45_49;
    double NL_HPVLR_50_54;
    double NL_HPVLR_55_65;
    double ImmuneDegree;
    double ImmuneDegree16;
    double pRegresstoHPV;
    double CIN3_NL;
    double CIN2_CA;
    double HPV_CIN2_16;
    double HPV_CIN2_allother;
    double CA1_CA1d;
    double CA2_CA2d;
    double CA3_CA3d;
    double CA1_CA2;
    double CA2_CA3;

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
    void loadData(ifstream &Infile, vector< vector<double> > &VariableName);
    void loadStringData(ifstream &Infile, std::string &VariableName);
    void loadRFG(std::string& RunsFileName, std::string& CurKey);
    void loadVariables();
    double ApplyMult(double, double);
    void loadCalibParams(vector<double> calib_params);

};

#endif //HPVVaccine_INPUTS_H
