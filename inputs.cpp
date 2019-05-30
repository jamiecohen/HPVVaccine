//
// Created by Jamie Cohen on 12/4/17.
//

#include "inputs.h"

using namespace std;

Inputs::Inputs(string Output, string Data){
    OutputFolder = Output;
    DataFolder = Data;
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
    string LifeExpectancyFileName = "LifeExpectancyFile";
    string AgeStandardFileName = "AgeStandardFile";
    string InitialPopulationFileName = "InitialPopulationFile";
    string TuningFactorName = "TuningFactor";

    //[NaturalHistory] variable names
    //Natural History related distributions
    //e.g. string TableExampleFileName = "TableExampleFile";
    string StartHealthName = "StartHealth";
    string ASRMortalityFileName = "ASRMortalityFile";
    string HPVIncidenceFileName = "HPVIncidenceFile";
    string CaMortalityFileName = "CaMortalityFile";
    string SymptomDetectionFileName = "SymptomDetectionFile";

    // Interventions
    string CostsFileName = "CostsFile";
    string UtilitiesFileName = "UtilitiesFile";
    string DisabilityFileName = "DisabilityFile";
    string ScreenStrategyName = "ScreenStrategy";
    string ScreenStopAgeName = "ScreenStopAge";
    string ScreenStartAgeName = "ScreenStartAge";
    string ScreenFrequencyName = "ScreenFrequency";
    string ScreenCoverageName = "ScreenCoverage";
    string ScreenComplianceName = "ScreenCompliance";
    string VaccineTypeName = "VaccineType";
    string VaccineStartAgeName = "VaccineStartAge";
    string VaccineEfficacyFileName = "VaccineEfficacyFile";
    string VaccineDurationName = "VaccineDuration";
    string VaccineWaneTimeName = "VaccineWaneTime";
    string HPVSensFileName = "HPVSensFile";
    string ColpoSensFileName = "ColpoSensFile";
    string CryoEligibilityFileName = "CryoEligibilityFile";
    string CryoSuccessRateCINName = "CryoSuccessRateCIN";
    string CryoSuccessRateHPVName = "CryoSuccessRateHPV";

    //[Multipliers] variable names
    //[NaturalImmunity Multipliers] variable names
    string ImmuneDegreeLRName = "ImmuneDegreeLR";
    string ImmuneDegreeotherHRName = "ImmuneDegreeotherHR";
    string ImmuneDegree16Name = "ImmuneDegreeHighRisk16";
    string ImmuneDegree18Name = "ImmuneDegreeHighRisk18";
    string ImmuneDegree31Name = "ImmuneDegreeHighRisk31";
    string ImmuneDegree33Name = "ImmuneDegreeHighRisk33";
    string ImmuneDegree45Name = "ImmuneDegreeHighRisk45";
    string ImmuneDegree52Name = "ImmuneDegreeHighRisk52";
    string ImmuneDegree58Name = "ImmuneDegreeHighRisk58";
    string VaccineEfficacyName = "VE_HIV";

    string CIN2_NL_1_5Name = "CIN2_NL_1_5";
    string CIN2_NL_6_10Name = "CIN2_NL_6_10";
    string CIN2_NL_11_20Name = "CIN2_NL_11_20";
    string CIN2_NL_21_29Name = "CIN2_NL_21_29";
    string CIN2_NL_30_39Name = "CIN2_NL_30_39";
    string CIN2_NL_40_49Name = "CIN2_NL_40_49";
    string CIN2_NL_50Name = "CIN2_NL_50";
    string CIN2_NL_LRName = "CIN2_NL_LR";
    string CIN2_NL_high5Name = "CIN2_NL_high5";
    string CIN2_NL_1618Name = "CIN2_NL_1618";
    string CIN2_NL_otherHRName = "CIN2_NL_otherHR";
    string HPV_NL_0_1Name = "HPV_NL_0_1";
    string HPV_NL_1_2Name = "HPV_NL_1_2";
    string HPV_NL_2_5Name = "HPV_NL_2_5";
    string HPV_NL_5Name = "HPV_NL_5";
    string HPV_NL_LRName = "HPV_NL_LR";
    string HPV_NL_1618Name = "HPV_NL_1618";
    string HPV_NL_high5Name = "HPV_NL_high5";
    string HPV_NL_otherHRName = "HPV_NL_otherHR";
    string HPV_CIN2_0_1Name = "HPV_CIN2_0_1";
    string HPV_CIN2_1_2Name = "HPV_CIN2_1_2";
    string HPV_CIN2_2_5Name = "HPV_CIN2_2_5";
    string HPV_CIN2_5Name = "HPV_CIN2_5";
    string HPV_CIN2_LRName = "HPV_CIN2_LR";
    string HPV_CIN2_high5Name = "HPV_CIN2_high5";
    string HPV_CIN2_otherHRName = "HPV_CIN2_otherHR";
    string HPV_CIN2_1618Name = "HPV_CIN2_1618";
    string CIN3_CA_1_5Name = "CIN3_CA_1_5";
    string CIN3_CA_6_10Name = "CIN3_CA_6_10";
    string CIN3_CA_11_20Name = "CIN3_CA_11_20";
    string CIN3_CA_21_29Name = "CIN3_CA_21_29";
    string CIN3_CA_30_39Name = "CIN3_CA_30_39";
    string CIN3_CA_40_49Name = "CIN3_CA_40_49";
    string CIN3_CA_50Name = "CIN3_CA_50";
    string CIN3_CA_1618Name = "CIN3_CA_1618";
    string CIN3_CA_otherHRName = "CIN3_CA_otherHR";
    string CIN3_CA_high5Name = "CIN3_CA_high5";
    string CA1_CA2Name = "CA1_CA2";
    string CA2_CA3Name = "CA2_CA3";
    string NL_HPV_LRName = "NL_HPV_LR";
    string NL_HPV_oHRName = "NL_HPV_oHR";
    string NL_HPV_1618Name = "NL_HPV_1618";
    string NL_HPV_high5Name = "NL_HPV_high5";
    string pRegressToHPVName = "pRegressToHPV";

    string CalibTargsFileName = "CalibTargsFile";
    string CalibTargsNamesFileName = "CalibTargsNamesFile";
    string MultipliersFileName = "MultipliersFile";
    string MultipliersNamesFileName = "MultipliersNamesFile";
    string SimulationsName = "Simulations";
    string IterationsName = "Iterations";


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
    Tuning_Factor = RunsFile.GetValueF (CurKey, TuningFactorName);

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
    Iterations = RunsFile.GetValueI (CurKey, IterationsName);


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

    LifeExpectancyFile.append(DataFolder);
    LifeExpectancyFile.append(RunsFile.GetValue(CurKey, LifeExpectancyFileName));
    Infile.open(LifeExpectancyFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << LifeExpectancyFile << endl;
        exit(1);
    }

    loadData (Infile, LifeExpectancy);
    Infile.close();
    Infile.clear();

    DisabilityFile.append(DataFolder);
    DisabilityFile.append(RunsFile.GetValue(CurKey, DisabilityFileName));
    Infile.open(DisabilityFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << DisabilityFile << endl;
        exit(1);
    }


    loadData (Infile, Disability);
    Infile.close();
    Infile.clear();

    AgeStandardFile.append(DataFolder);
    AgeStandardFile.append(RunsFile.GetValue(CurKey, AgeStandardFileName));
    Infile.open(AgeStandardFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << AgeStandardFile << endl;
        exit(1);
    }


    loadData (Infile, AgeStandard);
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


    CostsFile.append(DataFolder);
    CostsFile.append(RunsFile.GetValue(CurKey, CostsFileName));
    Infile.open(CostsFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CostsFile << endl;
        exit(1);
    }

    loadData (Infile, costs);
    Infile.close();
    Infile.clear();

    UtilitiesFile.append(DataFolder);
    UtilitiesFile.append(RunsFile.GetValue(CurKey, UtilitiesFileName));
    Infile.open(UtilitiesFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << UtilitiesFile << endl;
        exit(1);
    }

    loadData (Infile, utilities);
    Infile.close();
    Infile.clear();

    ScreenStrategy = RunsFile.GetValue(CurKey, ScreenStrategyName);
    ScreenStartAge = RunsFile.GetValueI(CurKey, ScreenStartAgeName);

    ScreenStopAge = RunsFile.GetValueI(CurKey, ScreenStopAgeName);

    ScreenFrequency = RunsFile.GetValueI(CurKey, ScreenFrequencyName);
    ScreenCoverage = RunsFile.GetValueF(CurKey, ScreenCoverageName);
    ScreenCompliance = RunsFile.GetValueF(CurKey, ScreenComplianceName);
    VaccineType = RunsFile.GetValue(CurKey, VaccineTypeName);
    VaccineStartAge = RunsFile.GetValueI(CurKey, VaccineStartAgeName);
    VaccineDuration = RunsFile.GetValueI(CurKey, VaccineDurationName);
    VaccineEfficacy = RunsFile.GetValueF(CurKey, VaccineEfficacyName);
    VaccineWaneTime = RunsFile.GetValueF(CurKey, VaccineWaneTimeName);
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


    HPVSensFile.append(DataFolder);
    HPVSensFile.append(RunsFile.GetValue(CurKey, HPVSensFileName));
    Infile.open(HPVSensFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << HPVSensFile << endl;
        exit(1);
    }

    loadData (Infile, hpvsens);
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

    CryoEligibilityFile.append(DataFolder);
    CryoEligibilityFile.append(RunsFile.GetValue(CurKey, CryoEligibilityFileName));
    Infile.open(CryoEligibilityFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CryoEligibilityFile << endl;
        exit(1);
    }

    loadData (Infile, cryoelig);
    Infile.close();
    Infile.clear();

    CryoSuccessRateCIN = RunsFile.GetValueF(CurKey, CryoSuccessRateCINName);
    CryoSuccessRateHPV = RunsFile.GetValueF(CurKey, CryoSuccessRateHPVName);

    // todo-Jamie Figure out what cryo success rate for HPV should be? Currently set to 0.5

    ImmuneDegreeLR = RunsFile.GetValueF(CurKey, ImmuneDegreeLRName);
    ImmuneDegreeotherHR = RunsFile.GetValueF(CurKey, ImmuneDegreeotherHRName);
    ImmuneDegree16 = RunsFile.GetValueF(CurKey, ImmuneDegree16Name);
    ImmuneDegree18 = RunsFile.GetValueF(CurKey, ImmuneDegree18Name);
    ImmuneDegree31 = RunsFile.GetValueF(CurKey, ImmuneDegree31Name);
    ImmuneDegree33 = RunsFile.GetValueF(CurKey, ImmuneDegree33Name);
    ImmuneDegree45 = RunsFile.GetValueF(CurKey, ImmuneDegree45Name);
    ImmuneDegree52 = RunsFile.GetValueF(CurKey, ImmuneDegree52Name);
    ImmuneDegree58 = RunsFile.GetValueF(CurKey, ImmuneDegree58Name);

    // NEW PARAMETERS

    CIN2_NL_1_5 = RunsFile.GetValueF(CurKey, CIN2_NL_1_5Name);
    CIN2_NL_6_10 = RunsFile.GetValueF(CurKey, CIN2_NL_6_10Name);
    CIN2_NL_11_20 = RunsFile.GetValueF(CurKey, CIN2_NL_11_20Name);
    CIN2_NL_21_29 = RunsFile.GetValueF(CurKey, CIN2_NL_21_29Name);
    CIN2_NL_30_39 = RunsFile.GetValueF(CurKey, CIN2_NL_30_39Name);
    CIN2_NL_40_49 = RunsFile.GetValueF(CurKey, CIN2_NL_40_49Name);
    CIN2_NL_50 = RunsFile.GetValueF(CurKey, CIN2_NL_50Name);
    CIN2_NL_LR = RunsFile.GetValueF(CurKey, CIN2_NL_LRName);
    CIN2_NL_high5 = RunsFile.GetValueF(CurKey, CIN2_NL_high5Name);
    CIN2_NL_1618 = RunsFile.GetValueF(CurKey, CIN2_NL_1618Name);
    CIN2_NL_otherHR = RunsFile.GetValueF(CurKey, CIN2_NL_otherHRName);
    HPV_NL_0_1 = RunsFile.GetValueF(CurKey, HPV_NL_0_1Name);
    HPV_NL_1_2 = RunsFile.GetValueF(CurKey, HPV_NL_1_2Name);
    HPV_NL_2_5 = RunsFile.GetValueF(CurKey, HPV_NL_2_5Name);
    HPV_NL_5 = RunsFile.GetValueF(CurKey, HPV_NL_5Name);
    HPV_NL_LR = RunsFile.GetValueF(CurKey, HPV_NL_LRName);
    HPV_NL_1618 = RunsFile.GetValueF(CurKey, HPV_NL_1618Name);
    HPV_NL_high5 = RunsFile.GetValueF(CurKey, HPV_NL_high5Name);
    HPV_NL_otherHR = RunsFile.GetValueF(CurKey, HPV_NL_otherHRName);
    HPV_CIN2_0_1 = RunsFile.GetValueF(CurKey, HPV_CIN2_0_1Name);
    HPV_CIN2_1_2 = RunsFile.GetValueF(CurKey, HPV_CIN2_1_2Name);
    HPV_CIN2_2_5 = RunsFile.GetValueF(CurKey, HPV_CIN2_2_5Name);
    HPV_CIN2_5 = RunsFile.GetValueF(CurKey, HPV_CIN2_5Name);
    HPV_CIN2_LR = RunsFile.GetValueF(CurKey, HPV_CIN2_LRName);
    HPV_CIN2_high5 = RunsFile.GetValueF(CurKey, HPV_CIN2_high5Name);
    HPV_CIN2_otherHR = RunsFile.GetValueF(CurKey, HPV_CIN2_otherHRName);
    HPV_CIN2_1618 = RunsFile.GetValueF(CurKey, HPV_CIN2_1618Name);
    CIN3_CA_1_5 = RunsFile.GetValueF(CurKey, CIN3_CA_1_5Name);
    CIN3_CA_6_10 = RunsFile.GetValueF(CurKey, CIN3_CA_6_10Name);
    CIN3_CA_11_20 = RunsFile.GetValueF(CurKey, CIN3_CA_11_20Name);
    CIN3_CA_21_29 = RunsFile.GetValueF(CurKey, CIN3_CA_21_29Name);
    CIN3_CA_30_39 = RunsFile.GetValueF(CurKey, CIN3_CA_30_39Name);
    CIN3_CA_40_49 = RunsFile.GetValueF(CurKey, CIN3_CA_40_49Name);
    CIN3_CA_50 = RunsFile.GetValueF(CurKey, CIN3_CA_50Name);
    CIN3_CA_1618 = RunsFile.GetValueF(CurKey, CIN3_CA_1618Name);
    CIN3_CA_otherHR = RunsFile.GetValueF(CurKey, CIN3_CA_otherHRName);
    CIN3_CA_high5 = RunsFile.GetValueF(CurKey, CIN3_CA_high5Name);
    CA1_CA2 = RunsFile.GetValueF(CurKey, CA1_CA2Name);
    CA2_CA3 = RunsFile.GetValueF(CurKey, CA2_CA3Name);
    NL_HPV_LR = RunsFile.GetValueF(CurKey, NL_HPV_LRName);
    NL_HPV_oHR = RunsFile.GetValueF(CurKey, NL_HPV_oHRName);
    NL_HPV_1618 = RunsFile.GetValueF(CurKey, NL_HPV_1618Name);
    NL_HPV_high5 = RunsFile.GetValueF(CurKey, NL_HPV_high5Name);
    pRegressToHPV = RunsFile.GetValueF(CurKey, pRegressToHPVName);

}

void Inputs::loadVariables() {

    pResourcesAvail = 1;
    pHPVCIN_ART = 0.67;
    pCINNL_ART = 2.29;

    pCA1_CA1D = sympdet[0][0];
    pCA2_CA2D = sympdet[1][0];
    pCA3_CA3D = sympdet[2][0];

    CIN3_CA_mult = 0.2;
    CIN2_NL_mult = 0.5;
    HPV_CIN2_mult = 1.2;

    for(int j = 0; j < 100; j++) {

        if (j < 6){

            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;

        } else if (j < 11){

            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;

        } else if (j < 21){
            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;


        } else if (j < 30){

            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN3_NL_high5[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;


        } else if (j < 40){

            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;


        } else if (j < 50){

            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;
        } else {

            pCIN3_CA1_1618[j] = ApplyMult (CIN3_CA_50, CIN3_CA_1618);
            pCIN2_CA1_1618[j] = pCIN3_CA1_1618[j] * CIN3_CA_mult;

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_50, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = pCIN3_CA1_high5[j] * CIN3_CA_mult;

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_50, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = pCIN3_CA1_oHR[j] * CIN3_CA_mult;

            pCIN2_NL_1618[j] = ApplyMult (CIN2_NL_50, CIN2_NL_1618);
            pCIN3_NL_1618[j] = pCIN2_NL_1618[j] * CIN2_NL_mult;

            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_50, CIN2_NL_high5);
            pCIN3_NL_high5[j] = pCIN3_NL_high5[j] * CIN2_NL_mult;

            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_50, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = pCIN3_NL_oHR[j] * CIN2_NL_mult;

            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_50, CIN2_NL_LR);
            pCIN3_NL_LR[j] = pCIN3_NL_LR[j] * CIN2_NL_mult;
        }
    }


    for (int j = 0; j < 100; j ++){

        if(j < 1){

            pHPV_LR_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_LR);
            pHPV_1618_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_1618);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_high5);

            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_LR);
            pHPV_1618_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_1618);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_high5);

            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_1618_CIN3[j] = ApplyMult(pHPV_1618_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);



        } else if (j < 2){
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_LR);
            pHPV_1618_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_1618);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_high5);

            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_LR);
            pHPV_1618_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_1618);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_high5);

            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_1618_CIN3[j] = ApplyMult(pHPV_1618_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);


        } else if (j <5){
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_LR);
            pHPV_1618_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_1618);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_high5);

            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_LR);
            pHPV_1618_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_1618);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_high5);

            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_1618_CIN3[j] = ApplyMult(pHPV_1618_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);


        } else {
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_LR);
            pHPV_1618_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_1618);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_high5);

            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_LR);
            pHPV_1618_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_1618);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_high5);

            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_1618_CIN3[j] = ApplyMult(pHPV_1618_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);

        }

        mCA1[j] = CaMortality[j][1];
        mCA2[j] = CaMortality[j][2];
        mCA3[j] = CaMortality[j][3];
        mCA1d[j] = CaMortality[j][5];
        mCA2d[j] = CaMortality[j][6];
        mCA3d[j] = CaMortality[j][7];
        mCA1dsc[j] = CaMortality[j][9];
        mCA2dsc[j] = CaMortality[j][10];
        mCA3dsc[j] = CaMortality[j][11];

        pHPV_LR[j] = ApplyMult(HPVInc[j][0],NL_HPV_LR);
        pHPV_otherHR[j] = ApplyMult(HPVInc[j][0],NL_HPV_oHR);
        pHPV_1618[j] = ApplyMult(HPVInc[j][0],NL_HPV_1618);
        pHPV_high5[j] = ApplyMult(HPVInc[j][0],NL_HPV_high5);

    }

   

    cPtTime = costs[0][0];
    cPapTest = costs[1][0];
    cHPVTest = costs[2][0];
    cReturnforResult = costs[4][0];
    cColpoTime = costs[5][0];
    cColpoProc = costs[6][0];
    cTreatHPV = costs[7][0];
    cTreatCIN23 = costs[8][0];
    cCryoVisit = costs[9][0];
    cCryoHPV = costs[10][0];
    cCryoCIN23 = costs[11][0];
    cCryoCa = costs[12][0];
    cStage1Ca = costs[13][0];
    cStage2Ca = costs[14][0];
    cStage3Ca = costs[15][0];
    cVaccine = costs[22][0];

    cryoelig_NL = cryoelig[0][0];
    cryoelig_CIN2 = cryoelig[1][0];
    cryoelig_CIN3 = cryoelig[2][0];
    cryoelig_Ca = cryoelig[3][0];

    utilityHealthy = utilities[0][0];
    utilityHPV = utilities[1][0];
    utilityCIN2 = utilities[2][0];
    utilityCIN3 = utilities[3][0];
    utilityCA1 = utilities[4][0];
    utilityCA2 = utilities[5][0];
    utilityCA3 = utilities[6][0];
    utilityHIVCD4500 = utilities[8][0];
    utilityHIVCD4200500 = utilities[9][0];
    utilityHIVCD4200 = utilities[10][0];
    utilityHIVCA1 = utilities[11][0];
    utilityHIVCA2 = utilities[12][0];
    utilityHIVCA3 = utilities[13][0];

    disabilityCA34 = Disability[3][0];
    disabilityCA12 = Disability[4][0];


    hpvsens_NL = hpvsens[1][0];
    hpvsens_CIN = hpvsens[1][1];
    hpvsens_Ca = hpvsens[1][1];


    if(ScreenStrategy == "NoScreen"){
        screenstrat = NoScreen;
    }
    else if (ScreenStrategy == "HPV"){
        screenstrat = HPV;
    }

    if(VaccineType == "Bivalent"){
        vaccinetype = VxType::Bivalent;
        VE_1618 = vaccineefficacy[0][0]*VaccineEfficacy;
        VE_high5 = vaccineefficacy[1][0]*VaccineEfficacy;

    } else if(VaccineType == "Nonavalent"){
        vaccinetype = VxType::Nonavalent;
        VE_1618 = vaccineefficacy[0][1]*VaccineEfficacy;
        VE_high5 = vaccineefficacy[1][1]*VaccineEfficacy;
    }


}

double Inputs::ApplyMult(double prob, double mult){
    double rate;
    rate = -log (1 - prob) * mult;
    prob = 1 - exp(-rate);
    return(prob);
}

void Inputs::loadCalibParams(std::vector<double> calib_params) {

    CIN2_NL_1_5 = calib_params[0];
    CIN2_NL_6_10 = calib_params[1];
    CIN2_NL_11_20 = calib_params[2];
    CIN2_NL_21_29 = calib_params[3];
    CIN2_NL_30_39 = calib_params[4];
    CIN2_NL_40_49 = calib_params[5];
    CIN2_NL_50 = calib_params[6];
    CIN2_NL_LR = calib_params[7];
    CIN2_NL_high5 = calib_params[8];
    CIN2_NL_1618 = calib_params[9];
    CIN2_NL_otherHR = calib_params[10];
    HPV_NL_0_1 = calib_params[11];
    HPV_NL_1_2 = calib_params[12];
    HPV_NL_2_5 = calib_params[13];
    HPV_NL_5 = calib_params[14];
    HPV_NL_LR = calib_params[15];
    HPV_NL_1618 = calib_params[16];
    HPV_NL_high5 = calib_params[17];
    HPV_NL_otherHR = calib_params[18];
    HPV_CIN2_0_1 = calib_params[19];
    HPV_CIN2_1_2 = calib_params[20];
    HPV_CIN2_2_5 = calib_params[21];
    HPV_CIN2_5 = calib_params[22];
    HPV_CIN2_LR = calib_params[23];
    HPV_CIN2_high5 = calib_params[24];
    HPV_CIN2_otherHR = calib_params[25];
    HPV_CIN2_1618 = calib_params[26];
    CIN3_CA_1_5 = calib_params[27];
    CIN3_CA_6_10 = calib_params[28];
    CIN3_CA_11_20 = calib_params[29];
    CIN3_CA_21_29 = calib_params[30];
    CIN3_CA_30_39 = calib_params[31];
    CIN3_CA_40_49 = calib_params[32];
    CIN3_CA_50 = calib_params[33];
    CIN3_CA_1618 = calib_params[34];
    CIN3_CA_otherHR = calib_params[35];
    CIN3_CA_high5 = calib_params[36];
    CA1_CA2 = calib_params[37];
    CA2_CA3 = calib_params[38];
    NL_HPV_LR = calib_params[39];
    NL_HPV_oHR = calib_params[40];
    NL_HPV_1618 = calib_params[41];
    NL_HPV_high5 = calib_params[42];
    pRegressToHPV = calib_params[43];

}

void Inputs::loadStringData(ifstream &Infile, string &VariableName) {


    getline(Infile, VariableName);


}

