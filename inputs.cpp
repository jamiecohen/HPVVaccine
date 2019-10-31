#include <utility>

//
// Created by Jamie Cohen on 12/4/17.
//

#include "inputs.h"

using namespace std;

Inputs::Inputs(string Output, string Data){
    OutputFolder = std::move(Output);
    DataFolder = std::move(Data);
}

void Inputs::loadData(ifstream &Infile, vector< vector<double> > &VariableName) {

    string line;
    while(getline(Infile, line, '\r')){
        string tab_delim;
        vector<double> v1;
        stringstream row(line);

        while(getline(row, tab_delim))
        {
            stringstream ss(tab_delim);
            double value;
            while(ss>>value){

                v1.push_back(value);
            }
        }
        VariableName.push_back(v1);
    }
}

void Inputs::loadRFG(string &RunsFileName, string &CurKey) {

    //GLOBAL CONSTANTS
    //[ModelSpecifications] variable names
    string OutputDirName = "OutputDir";
    string CohortSizeName = "CohortSize";
    string ModelStartAgeName = "ModelStartAge";
    string ModelStopAgeName = "ModelStopAge";
    string StartYearName = "StartYear";
    string SimulationYearsName = "SimulationYears";
    string BurnInYearsName = "BurnInYears";
    string TuningFactorName = "TuningFactor";
    string InitialPopulationFileName = "InitialPopulationFile";

    //[NaturalHistory] variable names
    //Natural History related distributions
    //e.g. string TableExampleFileName = "TableExampleFile";
    string StartHealthName = "StartHealth";
    string ASRMortalityFileName = "ASRMortalityFile";
    string HPVIncidenceFileName = "HPVIncidenceFile";
    string HPVProgressionFileName = "HPVProgressionFile";
    string HPVClearanceFileName = "HPVClearanceFile";
    string CINProgressionFileName = "CINProgressionFile";
    string CINRegressionFileName = "CINRegressionFile";
    string CaMortalityFileName = "CaMortalityFile";
    string SymptomDetectionFileName = "SymptomDetectionFile";

    // Interventions
    string ScreenStopAgeName = "ScreenStopAge";
    string ScreenStartAgeName = "ScreenStartAge";
    string ScreenFrequencyName = "ScreenFrequency";
    string ScreenCoverageName = "ScreenCoverage";
    string ScreenComplianceName = "ScreenCompliance";
    string VaccineCoverageName = "VaccineCoverage";
    string MechanismofImmunityName = "MechanismofImmunity";
    string LatencyTimeName = "LatencyTime";
    string WaningImmunityName = "WaningImmunity";
    string ImmuneDurationName = "ImmuneDuration";
    string ImmuneWaneTimeName = "ImmuneWaneTime";
    string VaccineTypeName = "VaccineType";
    string VaccineDoseName = "VaccineDose";
    string VaccineStartAgeName = "VaccineStartAge";
    string VaccineEfficacyFileName = "VaccineEfficacyFile";
    string VaccineDurationName = "VaccineDuration";
    string VaccineWaneTimeName = "VaccineWaneTime";
    string CytoSensFileName = "CytoSensFile";
    string ColpoSensFileName = "ColpoSensFile";
    string LLETZSuccessRateCINName = "LLETZSuccessRateCIN";
    string LLETZSuccessRateHPVName = "LLETZSuccessRateHPV";
    string AdequacyLBCName = "AdequacyLBC";
    string ColpoAvailName = "ColpoAvail";

    //[Multipliers] variable names
    //[NaturalImmunity Multipliers] variable names
    string ImmuneDegreeName = "ImmuneDegree";
    string ImmuneDegree16Name = "ImmuneDegree16";
    string CIN2_NL_LRName = "CIN2_NL_LR";
    string CIN2_NL_high5Name = "CIN2_NL_high5";
    string CIN2_NL_16Name = "CIN2_NL_16";
    string CIN2_NL_18Name = "CIN2_NL_18";
    string CIN2_NL_otherHRName = "CIN2_NL_otherHR";
    string HPV_NL_LRName = "HPV_NL_LR";
    string HPV_NL_16Name = "HPV_NL_16";
    string HPV_NL_18Name = "HPV_NL_18";
    string HPV_NL_high5Name = "HPV_NL_high5";
    string HPV_NL_otherHRName = "HPV_NL_otherHR";
    string HPV_CIN_LRName = "HPV_CIN_LR";
    string HPV_CIN_high5Name = "HPV_CIN_high5";
    string HPV_CIN_otherHRName = "HPV_CIN_otherHR";
    string HPV_CIN_16Name = "HPV_CIN_16";
    string HPV_CIN_18Name = "HPV_CIN_18";
    string CIN3_CA_16Name = "CIN3_CA_16";
    string CIN3_CA_18Name = "CIN3_CA_18";
    string CIN3_CA_otherHRName = "CIN3_CA_otherHR";
    string CIN3_CA_high5Name = "CIN3_CA_high5";
    string NL_HPV_16_21Name = "NL_HPV_16_21";
    string NL_HPV_16_21_25Name = "NL_HPV_16_21_25";
    string NL_HPV_16_25_29Name = "NL_HPV_16_25_29";
    string NL_HPV_18_21Name = "NL_HPV_18_21";
    string NL_HPV_18_21_25Name = "NL_HPV_18_21_25";
    string NL_HPV_18_25_29Name = "NL_HPV_18_25_29";
    string NL_HPV_31_21Name = "NL_HPV_31_21";
    string NL_HPV_31_21_25Name = "NL_HPV_31_21_25";
    string NL_HPV_31_25_29Name = "NL_HPV_31_25_29";
    string NL_HPV_33_21Name = "NL_HPV_33_21";
    string NL_HPV_33_21_25Name = "NL_HPV_33_21_25";
    string NL_HPV_33_25_29Name = "NL_HPV_33_25_29";
    string NL_HPV_45_21Name = "NL_HPV_45_21";
    string NL_HPV_45_21_25Name = "NL_HPV_45_21_25";
    string NL_HPV_45_25_29Name = "NL_HPV_45_25_29";
    string NL_HPV_52_21Name = "NL_HPV_52_21";
    string NL_HPV_52_21_25Name = "NL_HPV_52_21_25";
    string NL_HPV_52_25_29Name = "NL_HPV_52_25_29";
    string NL_HPV_58_21Name = "NL_HPV_58_21";
    string NL_HPV_58_21_25Name = "NL_HPV_58_21_25";
    string NL_HPV_58_25_29Name = "NL_HPV_58_25_29";
    string CA1_CA2Name = "CA1_CA2";
    string CA2_CA3Name = "CA2_CA3";

    string CalibTargsFileName = "CalibTargsFile";
    string CalibTargsNamesFileName = "CalibTargsNamesFile";
    string MultipliersFileName = "MultipliersFile";
    string MultipliersNamesFileName = "MultipliersNamesFile";
    string SimulationsName = "Simulations";
    string SeroConversionFileName = "SeroConversionFile";

    //READ IN DATA FROM INPUT FILE HERE FIRST

    //create cinifile object and read it
    CIniFile RunsFile(RunsFileName);
    if (!RunsFile.ReadFile()) {
        std::cerr << "\nError: Could not read Runs File: " << RunsFileName << endl;
        exit(1);
    }

    //SET RUN VARIABLES AND MODEL SPECIFICATIONS

    //a file stream
    ifstream Infile;

    //variable names

    //e.g. StringExample.append(RunsFile.GetValue(CurKey, StringExampleName));
    //e.g. IntExample = RunsFile.GetValueI(CurKey, IntExampleName);
    //e.g. DoubleExample = RunsFile.GetValueF(CurKey, DoubleExampleName);

    OutputDir = OutputFolder.append(RunsFile.GetValue(CurKey, OutputDirName));
    CohortSize = RunsFile.GetValueI(CurKey, CohortSizeName);
    ModelStartAge = RunsFile.GetValueI(CurKey, ModelStartAgeName);
    ModelStopAge = RunsFile.GetValueI(CurKey, ModelStopAgeName);
    StartYear = RunsFile.GetValueI(CurKey, StartYearName);
    SimulationYears = RunsFile.GetValueI (CurKey, SimulationYearsName);
    BurnInYears = RunsFile.GetValueI (CurKey, BurnInYearsName);
    Tuning_Factor = RunsFile.GetValueI (CurKey, TuningFactorName);

    InitialPopulationFile.append(DataFolder);
    InitialPopulationFile.append(RunsFile.GetValue(CurKey, InitialPopulationFileName));
    Infile.open(InitialPopulationFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << InitialPopulationFile << endl;
        exit(1);
    }

    loadData (Infile, InitialPopulation);
    Infile.close();
    Infile.clear();

    CalibTargsFile.append(DataFolder);
    CalibTargsFile.append(RunsFile.GetValue(CurKey, CalibTargsFileName));
    Infile.open(CalibTargsFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CalibTargsFile << endl;
        exit(1);
    }

    loadData (Infile, CalibTargs);
    Infile.close();
    Infile.clear();

    MultipliersFile.append(DataFolder);
    MultipliersFile.append(RunsFile.GetValue(CurKey, MultipliersFileName));
    Infile.open(MultipliersFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << MultipliersFile << endl;
        exit(1);
    }

    loadData (Infile, Multipliers);
    Infile.close();
    Infile.clear();

    MultipliersNamesFile.append(DataFolder);
    MultipliersNamesFile.append(RunsFile.GetValue(CurKey, MultipliersNamesFileName));
    Infile.open(MultipliersNamesFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << MultipliersNamesFile << endl;
        exit(1);
    }

    loadStringData (Infile, MultipliersNames);
    Infile.close();
    Infile.clear();

    CalibTargsNamesFile.append(DataFolder);
    CalibTargsNamesFile.append(RunsFile.GetValue(CurKey, CalibTargsNamesFileName));
    Infile.open(CalibTargsNamesFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CalibTargsNamesFile << endl;
        exit(1);
    }

    loadStringData (Infile, CalibTargsNames);
    Infile.close();
    Infile.clear();

    Simulations = RunsFile.GetValueI (CurKey, SimulationsName);

    HPVIncidenceFile.append(DataFolder);
    HPVIncidenceFile.append(RunsFile.GetValue(CurKey, HPVIncidenceFileName));
    Infile.open(HPVIncidenceFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << HPVIncidenceFile << endl;
        exit(1);
    }

    loadData (Infile, HPVInc);
    Infile.close();
    Infile.clear();

    HPVProgressionFile.append(DataFolder);
    HPVProgressionFile.append(RunsFile.GetValue(CurKey, HPVProgressionFileName));
    Infile.open(HPVProgressionFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << HPVProgressionFile << endl;
        exit(1);
    }

    loadData (Infile, HPVProgression);
    Infile.close();
    Infile.clear();

    HPVClearanceFile.append(DataFolder);
    HPVClearanceFile.append(RunsFile.GetValue(CurKey, HPVClearanceFileName));
    Infile.open(HPVClearanceFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << HPVClearanceFile << endl;
        exit(1);
    }

    loadData (Infile, HPVClearance);
    Infile.close();
    Infile.clear();

    CINProgressionFile.append(DataFolder);
    CINProgressionFile.append(RunsFile.GetValue(CurKey, CINProgressionFileName));
    Infile.open(CINProgressionFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CINProgressionFile << endl;
        exit(1);
    }

    loadData (Infile, CINProgression);
    Infile.close();
    Infile.clear();

    CINRegressionFile.append(DataFolder);
    CINRegressionFile.append(RunsFile.GetValue(CurKey, CINRegressionFileName));
    Infile.open(CINRegressionFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CINRegressionFile << endl;
        exit(1);
    }

    loadData (Infile, CINRegression);
    Infile.close();
    Infile.clear();

    ASRMortalityFile.append(DataFolder);
    ASRMortalityFile.append(RunsFile.GetValue(CurKey, ASRMortalityFileName));
    Infile.open(ASRMortalityFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << ASRMortalityFile << endl;
        exit(1);
    }

    loadData (Infile, ASRMortality);
    Infile.close();
    Infile.clear();

    CaMortalityFile.append(DataFolder);
    CaMortalityFile.append(RunsFile.GetValue(CurKey, CaMortalityFileName));
    Infile.open(CaMortalityFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CaMortalityFile << endl;
        exit(1);
    }

    loadData (Infile, CaMortality);
    Infile.close();
    Infile.clear();

    SymptomDetectionFile.append(DataFolder);
    SymptomDetectionFile.append(RunsFile.GetValue(CurKey, SymptomDetectionFileName));
    Infile.open(SymptomDetectionFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << SymptomDetectionFile << endl;
        exit(1);
    }

    loadData (Infile, sympdet);
    Infile.close();
    Infile.clear();

    //[Interventions]

    SeroConversionFile.append(DataFolder);
    SeroConversionFile.append(RunsFile.GetValue(CurKey, SeroConversionFileName));
    Infile.open(SeroConversionFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << SeroConversionFile << endl;
        exit(1);
    }

    loadData (Infile, SeroConversion);
    Infile.close();
    Infile.clear();

    ScreenStartAge = RunsFile.GetValueI(CurKey, ScreenStartAgeName);
    ScreenStopAge = RunsFile.GetValueI(CurKey, ScreenStopAgeName);
    ScreenFrequency = RunsFile.GetValueI(CurKey, ScreenFrequencyName);
    ScreenCoverage = RunsFile.GetValueF(CurKey, ScreenCoverageName);
    ScreenCompliance = RunsFile.GetValueF(CurKey, ScreenComplianceName);

    VaccineCoverage = RunsFile.GetValueF(CurKey, VaccineCoverageName);
    VaccineType = RunsFile.GetValue(CurKey, VaccineTypeName);
    VaccineDose = RunsFile.GetValueI(CurKey, VaccineDoseName);
    VaccineStartAge = RunsFile.GetValueI(CurKey, VaccineStartAgeName);
    VaccineDuration = RunsFile.GetValueI(CurKey, VaccineDurationName);
    VaccineWaneTime = RunsFile.GetValueF(CurKey, VaccineWaneTimeName);
    WaningImmunity = RunsFile.GetValueI(CurKey, WaningImmunityName);

    VaccineEfficacyFile.append(DataFolder);
    VaccineEfficacyFile.append(RunsFile.GetValue(CurKey, VaccineEfficacyFileName));
    Infile.open(VaccineEfficacyFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << VaccineEfficacyFile << endl;
        exit(1);
    }

    loadData (Infile, vaccineefficacy);
    Infile.close();
    Infile.clear();

    CytoSensFile.append(DataFolder);
    CytoSensFile.append(RunsFile.GetValue(CurKey, CytoSensFileName));
    Infile.open(CytoSensFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CytoSensFile << endl;
        exit(1);
    }

    loadData (Infile, cytosens);
    Infile.close();
    Infile.clear();
    
    ColpoSensFile.append(DataFolder);
    ColpoSensFile.append(RunsFile.GetValue(CurKey, ColpoSensFileName));
    Infile.open(ColpoSensFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << ColpoSensFile << endl;
        exit(1);
    }

    loadData (Infile, colposens);
    Infile.close();
    Infile.clear();

    LLETZSuccessRateCIN = RunsFile.GetValueF(CurKey, LLETZSuccessRateCINName);
    LLETZSuccessRateHPV = RunsFile.GetValueF(CurKey, LLETZSuccessRateHPVName);
    AdequacyLBC = RunsFile.GetValueF (CurKey, AdequacyLBCName);
    ColpoAvail = RunsFile.GetValueF (CurKey, ColpoAvailName);
    ImmuneDegree = RunsFile.GetValueF(CurKey, ImmuneDegreeName);
    ImmuneDegree16 = RunsFile.GetValueF(CurKey, ImmuneDegree16Name);
    ImmuneWaneTime = RunsFile.GetValueI(CurKey, ImmuneWaneTimeName);
    ImmuneDuration = RunsFile.GetValueI(CurKey, ImmuneDurationName);
    MechanismofImmunity = RunsFile.GetValue (CurKey, MechanismofImmunityName);
    LatencyTime = RunsFile.GetValueI (CurKey, LatencyTimeName);
    CA1_CA2 = RunsFile.GetValueF(CurKey, CA1_CA2Name);
    CA2_CA3 = RunsFile.GetValueF(CurKey, CA2_CA3Name);

    // NEW PARAMETERS

    CIN2_NL_LR = RunsFile.GetValueF(CurKey, CIN2_NL_LRName);
    CIN2_NL_high5 = RunsFile.GetValueF(CurKey, CIN2_NL_high5Name);
    CIN2_NL_16 = RunsFile.GetValueF(CurKey, CIN2_NL_16Name);
    CIN2_NL_18 = RunsFile.GetValueF(CurKey, CIN2_NL_18Name);
    CIN2_NL_otherHR = RunsFile.GetValueF(CurKey, CIN2_NL_otherHRName);
    HPV_NL_LR = RunsFile.GetValueF(CurKey, HPV_NL_LRName);
    HPV_NL_16 = RunsFile.GetValueF(CurKey, HPV_NL_16Name);
    HPV_NL_18 = RunsFile.GetValueF(CurKey, HPV_NL_18Name);
    HPV_NL_high5 = RunsFile.GetValueF(CurKey, HPV_NL_high5Name);
    HPV_NL_otherHR = RunsFile.GetValueF(CurKey, HPV_NL_otherHRName);
    HPV_CIN_LR = RunsFile.GetValueF(CurKey, HPV_CIN_LRName);
    HPV_CIN_high5 = RunsFile.GetValueF(CurKey, HPV_CIN_high5Name);
    HPV_CIN_otherHR = RunsFile.GetValueF(CurKey, HPV_CIN_otherHRName);
    HPV_CIN_16 = RunsFile.GetValueF(CurKey, HPV_CIN_16Name);
    HPV_CIN_18 = RunsFile.GetValueF(CurKey, HPV_CIN_18Name);
    CIN3_CA_16 = RunsFile.GetValueF(CurKey, CIN3_CA_16Name);
    CIN3_CA_18 = RunsFile.GetValueF(CurKey, CIN3_CA_18Name);
    CIN3_CA_otherHR = RunsFile.GetValueF(CurKey, CIN3_CA_otherHRName);
    CIN3_CA_high5 = RunsFile.GetValueF(CurKey, CIN3_CA_high5Name);
    NL_HPV_16_21 = RunsFile.GetValueF(CurKey, NL_HPV_16_21Name);
    NL_HPV_16_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_16_21_25Name);
    NL_HPV_16_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_16_25_29Name);
    NL_HPV_18_21 = RunsFile.GetValueF(CurKey, NL_HPV_18_21Name);
    NL_HPV_18_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_18_21_25Name);
    NL_HPV_18_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_18_25_29Name);
    NL_HPV_31_21 = RunsFile.GetValueF(CurKey, NL_HPV_31_21Name);
    NL_HPV_31_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_31_21_25Name);
    NL_HPV_31_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_31_25_29Name);
    NL_HPV_33_21 = RunsFile.GetValueF(CurKey, NL_HPV_33_21Name);
    NL_HPV_33_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_33_21_25Name);
    NL_HPV_33_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_33_25_29Name);
    NL_HPV_45_21 = RunsFile.GetValueF(CurKey, NL_HPV_45_21Name);
    NL_HPV_45_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_45_21_25Name);
    NL_HPV_45_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_45_25_29Name);
    NL_HPV_52_21 = RunsFile.GetValueF(CurKey, NL_HPV_52_21Name);
    NL_HPV_52_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_52_21_25Name);
    NL_HPV_52_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_52_25_29Name);
    NL_HPV_58_21 = RunsFile.GetValueF(CurKey, NL_HPV_58_21Name);
    NL_HPV_58_21_25 = RunsFile.GetValueF(CurKey, NL_HPV_58_21_25Name);
    NL_HPV_58_25_29 = RunsFile.GetValueF(CurKey, NL_HPV_58_25_29Name);

    burnin.clear();
    for(int i = 0; i < ModelStopAge; i++){
        if(i < ModelStartAge){
            burnin.push_back(0);
        } else {
            burnin.push_back (CohortSize*InitialPopulation[i][0]);
        }
    }
}

void Inputs::loadVariables() {

    for(int j = 0; j < 5; j++) {
        pSeroConvert_16[j] = SeroConversion[j][0];
        pSeroConvert_18[j] = SeroConversion[j][1];
        pSeroConvert_high5[j] = SeroConversion[j][2];
    }

    CIN2_NL = CINRegression[0][0];
    pCIN2_NL_16 = ApplyMult (CIN2_NL, CIN2_NL_16);
    pCIN3_NL_16 = ApplyMult (pCIN2_NL_16, CIN3_NL);
    pCIN2_NL_18 = ApplyMult (CIN2_NL, CIN2_NL_18);
    pCIN3_NL_18 = ApplyMult (pCIN2_NL_18, CIN3_NL);
    pCIN2_NL_high5 = ApplyMult (CIN2_NL, CIN2_NL_high5);
    pCIN3_NL_high5 = ApplyMult (pCIN3_NL_high5, CIN3_NL);
    pCIN2_NL_oHR = ApplyMult (CIN2_NL, CIN2_NL_otherHR);
    pCIN3_NL_oHR = ApplyMult (pCIN3_NL_oHR, CIN3_NL);
    pCIN2_NL_LR = ApplyMult (CIN2_NL, CIN2_NL_LR);
    pCIN3_NL_LR = ApplyMult (pCIN3_NL_LR, CIN3_NL);
    pRegresstoHPV = 0.5;
    pCA1_CA1D = sympdet[0][0];
    pCA2_CA2D = sympdet[1][0];
    pCA3_CA3D = sympdet[2][0];

    for (int j = 0; j < 99; j ++){
        pHPV_16[j] = HPVInc[j][0];
        pHPV_18[j] = HPVInc[j][1];
        pHPV_31[j] = HPVInc[j][2];
        pHPV_33[j] = HPVInc[j][3];
        pHPV_45[j] = HPVInc[j][4];
        pHPV_52[j] = HPVInc[j][5];
        pHPV_58[j] = HPVInc[j][6];

        if(j < 21){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV_16_21);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV_18_21);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPV_31_21);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPV_33_21);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPV_45_21);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPV_52_21);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPV_58_21);
        } else if (j <25){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV_16_21_25);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV_18_21_25);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPV_31_21_25);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPV_33_21_25);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPV_45_21_25);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPV_52_21_25);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPV_58_21_25);
        } else if (j < 30){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV_16_25_29);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV_18_25_29);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPV_31_25_29);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPV_33_25_29);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPV_45_25_29);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPV_52_25_29);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPV_58_25_29);
        }

        pHPV_otherHR[j] = HPVInc[j][7];
        pHPV_LR[j] = HPVInc[j][8];
        pHPV_LR_NL[j] = ApplyMult(HPVClearance[j][0], HPV_NL_LR);
        pHPV_otherHR_NL[j] = ApplyMult(HPVClearance[j][1], HPV_NL_otherHR);
        pHPV_16_NL[j] = ApplyMult(HPVClearance[j][2], HPV_NL_16);
        pHPV_18_NL[j] = ApplyMult(HPVClearance[j][3], HPV_NL_18);
        pHPV_31_NL[j] = ApplyMult(HPVClearance[j][4], HPV_NL_high5);
        pHPV_33_NL[j] = ApplyMult(HPVClearance[j][5], HPV_NL_high5);
        pHPV_45_NL[j] = ApplyMult(HPVClearance[j][6], HPV_NL_high5);
        pHPV_52_NL[j] = ApplyMult(HPVClearance[j][7], HPV_NL_high5);
        pHPV_58_NL[j] = ApplyMult(HPVClearance[j][8], HPV_NL_high5);
        pHPV_LR_CIN[j] = ApplyMult(HPVProgression[j][0], HPV_CIN_LR);
        pHPV_otherHR_CIN[j] = ApplyMult(HPVProgression[j][1], HPV_CIN_otherHR);
        pHPV_16_CIN[j] = ApplyMult(HPVProgression[j][2], HPV_CIN_16);
        pHPV_18_CIN[j] = ApplyMult(HPVProgression[j][3], HPV_CIN_18);
        pHPV_31_CIN[j] = ApplyMult(HPVProgression[j][4], HPV_CIN_high5);
        pHPV_33_CIN[j] = ApplyMult(HPVProgression[j][5], HPV_CIN_high5);
        pHPV_45_CIN[j] = ApplyMult(HPVProgression[j][6], HPV_CIN_high5);
        pHPV_52_CIN[j] = ApplyMult(HPVProgression[j][7], HPV_CIN_high5);
        pHPV_58_CIN[j] = ApplyMult(HPVProgression[j][8], HPV_CIN_high5);
        pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR);
        pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16);
        pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18);
        pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5);
        pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5);
        pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5);
        pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5);
        pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5);
        pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN2_CA);
        pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN2_CA);
        pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN2_CA);
        pCIN2_CA1_31[j] = ApplyMult(pCIN3_CA1_31[j], CIN2_CA);
        pCIN2_CA1_33[j] = ApplyMult(pCIN3_CA1_33[j], CIN2_CA);
        pCIN2_CA1_45[j] = ApplyMult(pCIN3_CA1_45[j], CIN2_CA);
        pCIN2_CA1_52[j] = ApplyMult(pCIN3_CA1_52[j], CIN2_CA);
        pCIN2_CA1_58[j] = ApplyMult(pCIN3_CA1_58[j], CIN2_CA);
        mCA1[j] = CaMortality[j][1];
        mCA2[j] = CaMortality[j][2];
        mCA3[j] = CaMortality[j][3];
        mCA1d[j] = CaMortality[j][5];
        mCA2d[j] = CaMortality[j][6];
        mCA3d[j] = CaMortality[j][7];
    }

    cytosens_NL = cytosens[1][0];
    cytosens_CIN = cytosens[1][1];
    cytosens_Ca = cytosens[1][3];

    if(VaccineType == "Bivalent"){
        vaccinetype = VxType::Bivalent;
        VE_1618 = vaccineefficacy[0][0];
        VE_high5 = vaccineefficacy[1][0];

    } else if(VaccineType == "Nonavalent"){
        vaccinetype = VxType::Nonavalent;
        VE_1618 = vaccineefficacy[0][1];
        VE_high5 = vaccineefficacy[1][1];
    }

    if(MechanismofImmunity == "Degree"){
        ImmuneMechanism = Immunity::Degree;
    } else if(MechanismofImmunity == "Factor"){
        ImmuneMechanism = Immunity::Factor;
    } else if(MechanismofImmunity == "Seropositivity"){
        ImmuneMechanism = Immunity::Seropositivity;
    }
}

double Inputs::ApplyMult(double prob, double mult){
    double rate;
    rate = -log (1 - prob) * mult;
    prob = 1 - exp(-rate);
    return(prob);
}

void Inputs::loadCalibParams(vector<double> calib_params) {

    CIN2_NL_LR = calib_params[0];
    CIN2_NL_high5 = calib_params[1];
    CIN2_NL_16 = calib_params[2];
    CIN2_NL_18 = calib_params[3];
    CIN2_NL_otherHR = calib_params[4];
    HPV_NL_LR = calib_params[5];
    HPV_NL_16 = calib_params[6];
    HPV_NL_18 = calib_params[7];
    HPV_NL_high5 = calib_params[8];
    HPV_NL_otherHR = calib_params[9];
    HPV_CIN_LR = calib_params[10];
    HPV_CIN_high5 = calib_params[11];
    HPV_CIN_otherHR = calib_params[12];
    HPV_CIN_16 = calib_params[13];
    HPV_CIN_18 = calib_params[14];
    CIN3_CA_16 = calib_params[15];
    CIN3_CA_18 = calib_params[16];
    CIN3_CA_otherHR = calib_params[17];
    CIN3_CA_high5 = calib_params[18];

}

void Inputs::loadStringData(ifstream &Infile, string &VariableName) {
    getline(Infile, VariableName);
}

