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
    string HPVSensFileName = "HPVSensFile";
    string ColpoSensFileName = "ColpoSensFile";
    string CryoEligibilityFileName = "CryoEligibilityFile";
    string CryoSuccessRateCINName = "CryoSuccessRateCIN";
    string CryoSuccessRateHPVName = "CryoSuccessRateHPV";
    string LLETZSuccessRateCINName = "LLETZSuccessRateCIN";
    string LLETZSuccessRateHPVName = "LLETZSuccessRateHPV";
    string AdequacyLBCName = "AdequacyLBC";
    string AdequacyCCName = "AdequacyCC";
    string ColpoAvailName = "ColpoAvail";
    string CryoAvailName = "CryoAvail";

    //[Multipliers] variable names
    //[NaturalImmunity Multipliers] variable names
    string ImmuneDegreeName = "ImmuneDegree";
    string ImmuneFactorName = "ImmuneFactor";
    string CIN2_NL_1_5Name = "CIN2_NL_1_5";
    string CIN2_NL_6_10Name = "CIN2_NL_6_10";
    string CIN2_NL_11_20Name = "CIN2_NL_11_20";
    string CIN2_NL_21_29Name = "CIN2_NL_21_29";
    string CIN2_NL_30_39Name = "CIN2_NL_30_39";
    string CIN2_NL_40_49Name = "CIN2_NL_40_49";
    string CIN2_NL_50Name = "CIN2_NL_50";
    string CIN2_NL_LRName = "CIN2_NL_LR";
    string CIN2_NL_high5Name = "CIN2_NL_high5";
    string CIN2_NL_16Name = "CIN2_NL_16";
    string CIN2_NL_18Name = "CIN2_NL_18";
    string CIN2_NL_otherHRName = "CIN2_NL_otherHR";
    string HPV_NL_0_1Name = "HPV_NL_0_1";
    string HPV_NL_1_2Name = "HPV_NL_1_2";
    string HPV_NL_2_5Name = "HPV_NL_2_5";
    string HPV_NL_5Name = "HPV_NL_5";
    string HPV_NL_LRName = "HPV_NL_LR";
    string HPV_NL_16Name = "HPV_NL_16";
    string HPV_NL_18Name = "HPV_NL_18";
    string HPV_NL_high5Name = "HPV_NL_high5";
    string HPV_NL_otherHRName = "HPV_NL_otherHR";
    string HPV_CIN2_0_1Name = "HPV_CIN2_0_1";
    string HPV_CIN2_1_2Name = "HPV_CIN2_1_2";
    string HPV_CIN2_2_5Name = "HPV_CIN2_2_5";
    string HPV_CIN2_5Name = "HPV_CIN2_5";
    string HPV_CIN2_LRName = "HPV_CIN2_LR";
    string HPV_CIN2_high5Name = "HPV_CIN2_high5";
    string HPV_CIN2_otherHRName = "HPV_CIN2_otherHR";
    string HPV_CIN2_16Name = "HPV_CIN2_16";
    string HPV_CIN2_18Name = "HPV_CIN2_18";
    string CIN3_CA_1_5Name = "CIN3_CA_1_5";
    string CIN3_CA_6_10Name = "CIN3_CA_6_10";
    string CIN3_CA_11_20Name = "CIN3_CA_11_20";
    string CIN3_CA_21_29Name = "CIN3_CA_21_29";
    string CIN3_CA_30_39Name = "CIN3_CA_30_39";
    string CIN3_CA_40_49Name = "CIN3_CA_40_49";
    string CIN3_CA_50Name = "CIN3_CA_50";
    string CIN3_CA_16Name = "CIN3_CA_16";
    string CIN3_CA_18Name = "CIN3_CA_18";
    string CIN3_CA_otherHRName = "CIN3_CA_otherHR";
    string CIN3_CA_high5Name = "CIN3_CA_high5";
    string CA1_CA2Name = "CA1_CA2";
    string CA2_CA3Name = "CA2_CA3";
    string CIN3_CA_multName = "CIN3_CA_mult";
    string CIN2_NL_multName = "CIN2_NL_mult";
    string HPV_CIN2_multName = "HPV_CIN2_mult";

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
    LLETZSuccessRateCIN = RunsFile.GetValueF(CurKey, LLETZSuccessRateCINName);
    LLETZSuccessRateHPV = RunsFile.GetValueF(CurKey, LLETZSuccessRateHPVName);
    AdequacyLBC = RunsFile.GetValueF (CurKey, AdequacyLBCName);
    AdequacyCC = RunsFile.GetValueF (CurKey, AdequacyCCName);
    ColpoAvail = RunsFile.GetValueF (CurKey, ColpoAvailName);
    CryoAvail = RunsFile.GetValueF (CurKey, CryoAvailName);

    // todo-Jamie Figure out what cryo success rate for HPV should be? Currently set to 0.5

    ImmuneDegree = RunsFile.GetValueF(CurKey, ImmuneDegreeName);
    ImmuneFactor = RunsFile.GetValueF(CurKey, ImmuneFactorName);
    ImmuneWaneTime = RunsFile.GetValueI(CurKey, ImmuneWaneTimeName);
    ImmuneDuration = RunsFile.GetValueI(CurKey, ImmuneDurationName);
    MechanismofImmunity = RunsFile.GetValue (CurKey, MechanismofImmunityName);
    LatencyTime = RunsFile.GetValueI (CurKey, LatencyTimeName);
    CA1_CA2 = RunsFile.GetValueF(CurKey, CA1_CA2Name);
    CA2_CA3 = RunsFile.GetValueF(CurKey, CA2_CA3Name);
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
    CIN2_NL_16 = RunsFile.GetValueF(CurKey, CIN2_NL_16Name);
    CIN2_NL_18 = RunsFile.GetValueF(CurKey, CIN2_NL_18Name);
    CIN2_NL_otherHR = RunsFile.GetValueF(CurKey, CIN2_NL_otherHRName);

    HPV_NL_0_1 = RunsFile.GetValueF(CurKey, HPV_NL_0_1Name);
    HPV_NL_1_2 = RunsFile.GetValueF(CurKey, HPV_NL_1_2Name);
    HPV_NL_2_5 = RunsFile.GetValueF(CurKey, HPV_NL_2_5Name);
    HPV_NL_5 = RunsFile.GetValueF(CurKey, HPV_NL_5Name);
    HPV_NL_LR = RunsFile.GetValueF(CurKey, HPV_NL_LRName);
    HPV_NL_16 = RunsFile.GetValueF(CurKey, HPV_NL_16Name);
    HPV_NL_18 = RunsFile.GetValueF(CurKey, HPV_NL_18Name);
    HPV_NL_high5 = RunsFile.GetValueF(CurKey, HPV_NL_high5Name);
    HPV_NL_otherHR = RunsFile.GetValueF(CurKey, HPV_NL_otherHRName);

    HPV_CIN2_0_1 = RunsFile.GetValueF(CurKey, HPV_CIN2_0_1Name);
    HPV_CIN2_1_2 = RunsFile.GetValueF(CurKey, HPV_CIN2_1_2Name);
    HPV_CIN2_2_5 = RunsFile.GetValueF(CurKey, HPV_CIN2_2_5Name);
    HPV_CIN2_5 = RunsFile.GetValueF(CurKey, HPV_CIN2_5Name);
    HPV_CIN2_LR = RunsFile.GetValueF(CurKey, HPV_CIN2_LRName);
    HPV_CIN2_high5 = RunsFile.GetValueF(CurKey, HPV_CIN2_high5Name);
    HPV_CIN2_otherHR = RunsFile.GetValueF(CurKey, HPV_CIN2_otherHRName);
    HPV_CIN2_16 = RunsFile.GetValueF(CurKey, HPV_CIN2_16Name);
    HPV_CIN2_18 = RunsFile.GetValueF(CurKey, HPV_CIN2_18Name);

    CIN3_CA_1_5 = RunsFile.GetValueF(CurKey, CIN3_CA_1_5Name);
    CIN3_CA_6_10 = RunsFile.GetValueF(CurKey, CIN3_CA_6_10Name);
    CIN3_CA_11_20 = RunsFile.GetValueF(CurKey, CIN3_CA_11_20Name);
    CIN3_CA_21_29 = RunsFile.GetValueF(CurKey, CIN3_CA_21_29Name);
    CIN3_CA_30_39 = RunsFile.GetValueF(CurKey, CIN3_CA_30_39Name);
    CIN3_CA_40_49 = RunsFile.GetValueF(CurKey, CIN3_CA_40_49Name);
    CIN3_CA_50 = RunsFile.GetValueF(CurKey, CIN3_CA_50Name);
    CIN3_CA_16 = RunsFile.GetValueF(CurKey, CIN3_CA_16Name);
    CIN3_CA_18 = RunsFile.GetValueF(CurKey, CIN3_CA_18Name);
    CIN3_CA_otherHR = RunsFile.GetValueF(CurKey, CIN3_CA_otherHRName);
    CIN3_CA_high5 = RunsFile.GetValueF(CurKey, CIN3_CA_high5Name);
    CIN3_CA_mult = RunsFile.GetValueF(CurKey, CIN3_CA_multName);
    CIN2_NL_mult = RunsFile.GetValueF(CurKey, CIN2_NL_multName);
    HPV_CIN2_mult = RunsFile.GetValueF(CurKey, HPV_CIN2_multName);
}

void Inputs::loadVariables() {

    for(int j = 0; j < 5; j++) {
        pSeroConvert_16[j] = SeroConversion[j][0];
        pSeroConvert_18[j] = SeroConversion[j][1];
        pSeroConvert_high5[j] = SeroConversion[j][2];
    }



    pRegresstoHPV = 0.5;
    pCA1_CA1D = sympdet[0][0];
    pCA2_CA2D = sympdet[1][0];
    pCA3_CA3D = sympdet[2][0];
    for(int j = 0; j < 100; j++) {
        if (j < 6){
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_1_5, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_1_5, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);

        } else if (j < 11){
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_6_10, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_6_10, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);
        } else if (j < 21){
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_11_20, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_11_20, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);
        } else if (j < 30){
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_21_29, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_21_29, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);
        } else if (j < 40){
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_30_39, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_30_39, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);
        } else if (j < 50){
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_40_49, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_40_49, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);
        } else {
            pCIN3_CA1_16[j] = ApplyMult (CIN3_CA_50, CIN3_CA_16);
            pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN3_CA_mult);

            pCIN3_CA1_18[j] = ApplyMult (CIN3_CA_50, CIN3_CA_18);
            pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN3_CA_mult);

            pCIN3_CA1_high5[j] = ApplyMult (CIN3_CA_50, CIN3_CA_high5);
            pCIN2_CA1_high5[j] = ApplyMult(pCIN3_CA1_high5[j], CIN3_CA_mult);

            pCIN3_CA1_oHR[j] = ApplyMult (CIN3_CA_50, CIN3_CA_otherHR);
            pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN3_CA_mult);

            pCIN2_NL_16[j] = ApplyMult (CIN2_NL_50, CIN2_NL_16);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN2_NL_mult);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL_50, CIN2_NL_18);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN2_NL_mult);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL_50, CIN2_NL_high5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN3_NL_high5[j], CIN2_NL_mult);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL_50, CIN2_NL_otherHR);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN3_NL_oHR[j], CIN2_NL_mult);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL_50, CIN2_NL_LR);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN2_NL_mult);
        }
    }
    for (int j = 0; j < 100; j ++){
        if(j < 1){
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_LR);
            pHPV_16_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_16);
            pHPV_18_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_18);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_0_1, HPV_NL_high5);
            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_LR);
            pHPV_16_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_16);
            pHPV_18_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_18);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_0_1, HPV_CIN2_high5);
            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_16_CIN3[j] = ApplyMult(pHPV_16_CIN2[j], HPV_CIN2_mult);
            pHPV_18_CIN3[j] = ApplyMult(pHPV_18_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);
        } else if (j < 2){
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_LR);
            pHPV_16_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_16);
            pHPV_18_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_18);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_1_2, HPV_NL_high5);
            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_LR);
            pHPV_16_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_16);
            pHPV_18_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_18);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_1_2, HPV_CIN2_high5);
            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_16_CIN3[j] = ApplyMult(pHPV_16_CIN2[j], HPV_CIN2_mult);
            pHPV_18_CIN3[j] = ApplyMult(pHPV_18_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);
        } else if (j <5){
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_LR);
            pHPV_16_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_16);
            pHPV_18_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_18);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_2_5, HPV_NL_high5);
            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_LR);
            pHPV_16_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_16);
            pHPV_18_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_18);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_2_5, HPV_CIN2_high5);
            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_16_CIN3[j] = ApplyMult(pHPV_16_CIN2[j], HPV_CIN2_mult);
            pHPV_18_CIN3[j] = ApplyMult(pHPV_18_CIN2[j], HPV_CIN2_mult);
            pHPV_otherHR_CIN3[j] = ApplyMult(pHPV_otherHR_CIN2[j], HPV_CIN2_mult);
            pHPV_high5_CIN3[j] = ApplyMult(pHPV_high5_CIN2[j], HPV_CIN2_mult);
        } else {
            pHPV_LR_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_LR);
            pHPV_16_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_16);
            pHPV_18_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_18);
            pHPV_otherHR_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_otherHR);
            pHPV_high5_NL[j] = ApplyMult(HPV_NL_5, HPV_NL_high5);
            pHPV_LR_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_LR);
            pHPV_16_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_16);
            pHPV_18_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_18);
            pHPV_otherHR_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_otherHR);
            pHPV_high5_CIN2[j] = ApplyMult(HPV_CIN2_5, HPV_CIN2_high5);
            pHPV_LR_CIN3[j] = ApplyMult(pHPV_LR_CIN2[j], HPV_CIN2_mult);
            pHPV_16_CIN3[j] = ApplyMult(pHPV_16_CIN2[j], HPV_CIN2_mult);
            pHPV_18_CIN3[j] = ApplyMult(pHPV_18_CIN2[j], HPV_CIN2_mult);
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
        pHPV_16[j] = HPVInc[j][0];
        pHPV_18[j] = HPVInc[j][1];
        pHPV_31[j] = HPVInc[j][2];
        pHPV_33[j] = HPVInc[j][3];
        pHPV_45[j] = HPVInc[j][4];
        pHPV_52[j] = HPVInc[j][5];
        pHPV_58[j] = HPVInc[j][6];
        pHPV_LR[j] = HPVInc[j][7];
        pHPV_otherHR[j] = HPVInc[j][8];

    }

    cPtTime = 8*costs[0][0];
    cPapTest = costs[1][0];
    cPapLBCTest = costs[2][0];
    cHPVTest = costs[3][0];
    cReturnforResult = costs[4][0];
    cColpoTime = costs[5][0];
    cColpoProc = costs[6][0];
    cCryoVisit = costs[7][0];
    cCryoCIN23 = costs[8][0];
    cLLETZ = costs[9][0];
    cStage1Ca = costs[10][0];
    cStage2Ca = costs[11][0];
    cStage3Ca = costs[12][0];
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
    disabilityCA34 = Disability[3][0];
    disabilityCA12 = Disability[4][0];
    hpvsens_CIN = hpvsens[0][0];
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

    CIN2_NL_1_5 = calib_params[0];
    CIN2_NL_6_10 = calib_params[1];
    CIN2_NL_11_20 = calib_params[2];
    CIN2_NL_21_29 = calib_params[3];
    CIN2_NL_30_39 = calib_params[4];
    CIN2_NL_40_49 = calib_params[5];
    CIN2_NL_50 = calib_params[6];
    CIN2_NL_LR = calib_params[7];
    CIN2_NL_high5 = calib_params[8];
    CIN2_NL_16 = calib_params[9];
    CIN2_NL_18 = calib_params[10];
    CIN2_NL_otherHR = calib_params[11];
    HPV_NL_0_1 = calib_params[12];
    HPV_NL_1_2 = calib_params[13];
    HPV_NL_2_5 = calib_params[14];
    HPV_NL_5 = calib_params[15];
    HPV_NL_LR = calib_params[16];
    HPV_NL_16 = calib_params[17];
    HPV_NL_18 = calib_params[18];
    HPV_NL_high5 = calib_params[19];
    HPV_NL_otherHR = calib_params[20];
    HPV_CIN2_0_1 = calib_params[21];
    HPV_CIN2_1_2 = calib_params[22];
    HPV_CIN2_2_5 = calib_params[23];
    HPV_CIN2_5 = calib_params[24];
    HPV_CIN2_LR = calib_params[25];
    HPV_CIN2_high5 = calib_params[26];
    HPV_CIN2_otherHR = calib_params[27];
    HPV_CIN2_16 = calib_params[28];
    HPV_CIN2_18 = calib_params[29];
    CIN3_CA_1_5 = calib_params[30];
    CIN3_CA_6_10 = calib_params[31];
    CIN3_CA_11_20 = calib_params[32];
    CIN3_CA_21_29 = calib_params[33];
    CIN3_CA_30_39 = calib_params[34];
    CIN3_CA_40_49 = calib_params[35];
    CIN3_CA_50 = calib_params[36];
    CIN3_CA_16 = calib_params[37];
    CIN3_CA_18 = calib_params[38];
    CIN3_CA_otherHR = calib_params[39];
    CIN3_CA_high5 = calib_params[40];
    CIN3_CA_mult = calib_params[41];
    CIN2_NL_mult = calib_params[42];
    HPV_CIN2_mult = calib_params[43];

}

void Inputs::loadStringData(ifstream &Infile, string &VariableName) {
    getline(Infile, VariableName);
}

