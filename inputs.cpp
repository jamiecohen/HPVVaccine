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
    string InitialPopulationFileName = "InitialPopulationFile";

    //[NaturalHistory] variable names
    //Natural History related distributions
    //e.g. string TableExampleFileName = "TableExampleFile";
    string ASRMortalityFileName = "ASRMortalityFile";
    string HPVIncidenceFileName = "HPVIncidenceFile";
    string HPVProgressionFileName = "HPVProgressionFile";
    string HPVClearanceFileName = "HPVClearanceFile";
    string CINProgressionFileName = "CINProgressionFile";
    string CINRegressionFileName = "CINRegressionFile";
    string CaMortalityFileName = "CaMortalityFile";
    string SymptomDetectionFileName = "SymptomDetectionFile";

    // Interventions
    string CostsFileName = "CostsFile";
    string DisabilityFileName = "DisabilityFile";
    string LifeExpectancyFileName = "LifeExpectancyFile";
    string ScreenStopAgeName = "ScreenStopAge";
    string ScreenStartAgeName = "ScreenStartAge";
    string ScreenFrequencyName = "ScreenFrequency";
    string ScreenCoverageName = "ScreenCoverage";
    string ScreenComplianceName = "ScreenCompliance";
    string VaccineCoverageName = "VaccineCoverage";
    string MechanismofImmunityName = "MechanismofImmunity";
    string LatencyName = "Latency";
    string WaningImmunityName = "WaningImmunity";
    string ImmuneDurationName = "ImmuneDuration";
    string ImmuneWaneTimeName = "ImmuneWaneTime";
    string VaccineTypeName = "VaccineType";
    string VaccineDoseName = "VaccineDose";
    string VaccineStartAgeName = "VaccineStartAge";
    string VaccineEndAgeName = "VaccineEndAge";
    string VaccineStartYearName = "VaccineStartYear";
    string VaccineEfficacyFileName = "VaccineEfficacyFile";
    string VaccineDurationName = "VaccineDuration";
    string VaccineWaneTimeName = "VaccineWaneTime";
    string CytoSensFileName = "CytoSensFile";
    string ColpoSensFileName = "ColpoSensFile";
    string LLETZSuccessRateCINName = "LLETZSuccessRateCIN";
    string LLETZSuccessRateHPVName = "LLETZSuccessRateHPV";
    string AdequacyLBCName = "AdequacyLBC";
    string ColpoAvailName = "ColpoAvail";
    string dwelltime_outputName = "dwelltime_output";
    string incidence_outputName = "incidence_output";
    string mortality_outputName = "mortality_output";
    string CEA_outputName = "CEA_output";

    //[Multipliers] variable names
    //[NaturalImmunity Multipliers] variable names
    string CIN2_NL_allother_1Name = "CIN2_NL_allother_1";
    string CIN2_NL_allother_2_4Name = "CIN2_NL_allother_2_4";
    string CIN2_NL_allother_5Name = "CIN2_NL_allother_5";
    string CIN2_NL_16_1Name = "CIN2_NL_16_1";
    string CIN2_NL_16_2_4Name = "CIN2_NL_16_2_4";
    string CIN2_NL_16_5Name = "CIN2_NL_16_5";
    string HPV_NL_LR_1Name = "HPV_NL_LR_1";
    string HPV_NL_LR_2_4Name = "HPV_NL_LR_2_4";
    string HPV_NL_LR_5Name = "HPV_NL_LR_5";
    string HPV_NL_otherHR_1Name = "HPV_NL_otherHR_1";
    string HPV_NL_otherHR_2_4Name = "HPV_NL_otherHR_2_4";
    string HPV_NL_otherHR_5Name = "HPV_NL_otherHR_5";
    string HPV_NL_high5_1Name = "HPV_NL_high5_1";
    string HPV_NL_high5_2_4Name = "HPV_NL_high5_2_4";
    string HPV_NL_high5_5Name = "HPV_NL_high5_5";
    string HPV_NL_16_1Name = "HPV_NL_16_1";
    string HPV_NL_16_2_4Name = "HPV_NL_16_2_4";
    string HPV_NL_16_5Name = "HPV_NL_16_5";
    string HPV_NL_18_1Name = "HPV_NL_18_1";
    string HPV_NL_18_2_4Name = "HPV_NL_18_2_4";
    string HPV_NL_18_5Name = "HPV_NL_18_5";
    string HPV_CIN_LR_1Name = "HPV_CIN_LR_1";
    string HPV_CIN_LR_2_4Name = "HPV_CIN_LR_2_4";
    string HPV_CIN_LR_5Name = "HPV_CIN_LR_5";
    string HPV_CIN_otherHR_1Name = "HPV_CIN_otherHR_1";
    string HPV_CIN_otherHR_2_4Name = "HPV_CIN_otherHR_2_4";
    string HPV_CIN_otherHR_5Name = "HPV_CIN_otherHR_5";
    string HPV_CIN_high5_1Name = "HPV_CIN_high5_1";
    string HPV_CIN_high5_2_4Name = "HPV_CIN_high5_2_4";
    string HPV_CIN_high5_5Name = "HPV_CIN_high5_5";
    string HPV_CIN_16_1Name = "HPV_CIN_16_1";
    string HPV_CIN_16_2_4Name = "HPV_CIN_16_2_4";
    string HPV_CIN_16_5Name = "HPV_CIN_16_5";
    string HPV_CIN_18_1Name = "HPV_CIN_18_1";
    string HPV_CIN_18_2_4Name = "HPV_CIN_18_2_4";
    string HPV_CIN_18_5Name = "HPV_CIN_18_5";
    string CIN3_CA_high5_1_5Name = "CIN3_CA_high5_1_5";
    string CIN3_CA_high5_6_10Name = "CIN3_CA_high5_6_10";
    string CIN3_CA_high5_11_20Name = "CIN3_CA_high5_11_20";
    string CIN3_CA_high5_21_30Name = "CIN3_CA_high5_21_30";
    string CIN3_CA_high5_31_40Name = "CIN3_CA_high5_31_40";
    string CIN3_CA_high5_41_50Name = "CIN3_CA_high5_41_50";
    string CIN3_CA_high5_50Name = "CIN3_CA_high5_50";
    string CIN3_CA_16_1_5Name = "CIN3_CA_16_1_5";
    string CIN3_CA_16_6_10Name = "CIN3_CA_16_6_10";
    string CIN3_CA_16_11_20Name = "CIN3_CA_16_11_20";
    string CIN3_CA_16_21_30Name = "CIN3_CA_16_21_30";
    string CIN3_CA_16_31_40Name = "CIN3_CA_16_31_40";
    string CIN3_CA_16_41_50Name = "CIN3_CA_16_41_50";
    string CIN3_CA_16_50Name = "CIN3_CA_16_50";
    string CIN3_CA_18_1_5Name = "CIN3_CA_18_1_5";
    string CIN3_CA_18_6_10Name = "CIN3_CA_18_6_10";
    string CIN3_CA_18_11_20Name = "CIN3_CA_18_11_20";
    string CIN3_CA_18_21_30Name = "CIN3_CA_18_21_30";
    string CIN3_CA_18_31_40Name = "CIN3_CA_18_31_40";
    string CIN3_CA_18_41_50Name = "CIN3_CA_18_41_50";
    string CIN3_CA_18_50Name = "CIN3_CA_18_50";
    string CIN3_CA_otherHR_1_5Name = "CIN3_CA_otherHR_1_5";
    string CIN3_CA_otherHR_6_10Name = "CIN3_CA_otherHR_6_10";
    string CIN3_CA_otherHR_11_20Name = "CIN3_CA_otherHR_11_20";
    string CIN3_CA_otherHR_21_30Name = "CIN3_CA_otherHR_21_30";
    string CIN3_CA_otherHR_31_40Name = "CIN3_CA_otherHR_31_40";
    string CIN3_CA_otherHR_41_50Name = "CIN3_CA_otherHR_41_50";
    string CIN3_CA_otherHR_50Name = "CIN3_CA_otherHR_50";
    string NL_HPV16_17_19Name = "NL_HPV16_17_19";
    string NL_HPV16_20_24Name = "NL_HPV16_20_24";
    string NL_HPV16_25_29Name = "NL_HPV16_25_29";
    string NL_HPV16_30_34Name = "NL_HPV16_30_34";
    string NL_HPV16_35_39Name = "NL_HPV16_35_39";
    string NL_HPV16_40_44Name = "NL_HPV16_40_44";
    string NL_HPV16_45_49Name = "NL_HPV16_45_49";
    string NL_HPV16_50_54Name = "NL_HPV16_50_54";
    string NL_HPV16_55_65Name = "NL_HPV16_55_65";
    string NL_HPV18_17_19Name = "NL_HPV18_17_19";
    string NL_HPV18_20_24Name = "NL_HPV18_20_24";
    string NL_HPV18_25_29Name = "NL_HPV18_25_29";
    string NL_HPV18_30_34Name = "NL_HPV18_30_34";
    string NL_HPV18_35_39Name = "NL_HPV18_35_39";
    string NL_HPV18_40_44Name = "NL_HPV18_40_44";
    string NL_HPV18_45_49Name = "NL_HPV18_45_49";
    string NL_HPV18_50_54Name = "NL_HPV18_50_54";
    string NL_HPV18_55_65Name = "NL_HPV18_55_65";
    string NL_HPVhigh5_17_19Name = "NL_HPVhigh5_17_19";
    string NL_HPVhigh5_20_24Name = "NL_HPVhigh5_20_24";
    string NL_HPVhigh5_25_29Name = "NL_HPVhigh5_25_29";
    string NL_HPVhigh5_30_34Name = "NL_HPVhigh5_30_34";
    string NL_HPVhigh5_35_39Name = "NL_HPVhigh5_35_39";
    string NL_HPVhigh5_40_44Name = "NL_HPVhigh5_40_44";
    string NL_HPVhigh5_45_49Name = "NL_HPVhigh5_45_49";
    string NL_HPVhigh5_50_54Name = "NL_HPVhigh5_50_54";
    string NL_HPVhigh5_55_65Name = "NL_HPVhigh5_55_65";
    string NL_HPVoHR_17_19Name = "NL_HPVoHR_17_19";
    string NL_HPVoHR_20_24Name = "NL_HPVoHR_20_24";
    string NL_HPVoHR_25_29Name = "NL_HPVoHR_25_29";
    string NL_HPVoHR_30_34Name = "NL_HPVoHR_30_34";
    string NL_HPVoHR_35_39Name = "NL_HPVoHR_35_39";
    string NL_HPVoHR_40_44Name = "NL_HPVoHR_40_44";
    string NL_HPVoHR_45_49Name = "NL_HPVoHR_45_49";
    string NL_HPVoHR_50_54Name = "NL_HPVoHR_50_54";
    string NL_HPVoHR_55_65Name = "NL_HPVoHR_55_65";
    string NL_HPVLR_17_19Name = "NL_HPVLR_17_19";
    string NL_HPVLR_20_24Name = "NL_HPVLR_20_24";
    string NL_HPVLR_25_29Name = "NL_HPVLR_25_29";
    string NL_HPVLR_30_34Name = "NL_HPVLR_30_34";
    string NL_HPVLR_35_39Name = "NL_HPVLR_35_39";
    string NL_HPVLR_40_44Name = "NL_HPVLR_40_44";
    string NL_HPVLR_45_49Name = "NL_HPVLR_45_49";
    string NL_HPVLR_50_54Name = "NL_HPVLR_50_54";
    string NL_HPVLR_55_65Name = "NL_HPVLR_55_65";
    string ImmuneDegreeName = "ImmuneDegree";
    string ImmuneDegree16Name = "ImmuneDegree16";
    string pRegresstoHPVName = "pRegresstoHPV";
    string CIN3_NLName = "CIN3_NL";
    string CIN2_CAName = "CIN2_CA";
    string HPV_CIN2_16Name = "HPV_CIN2_16";
    string HPV_CIN2_allotherName = "HPV_CIN2_allother";
    string CA1_CA1dName = "CA1_CA1d";
    string CA2_CA2dName = "CA2_CA2d";
    string CA3_CA3dName = "CA3_CA3d";
    string CA1_CA2Name = "CA1_CA2";
    string CA2_CA3Name = "CA2_CA3";

    string CalibTargsFileName = "CalibTargsFile";
    string CalibTargsNamesFileName = "CalibTargsNamesFile";
    string MultipliersFileName = "MultipliersFile";
    string MultipliersNamesFileName = "MultipliersNamesFile";
    string SimulationsName = "Simulations";

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
    dwelltime_output = RunsFile.GetValueI(CurKey, dwelltime_outputName);
    incidence_output = RunsFile.GetValueI(CurKey, incidence_outputName);
    mortality_output = RunsFile.GetValueI(CurKey, mortality_outputName);
    CEA_output = RunsFile.GetValueI(CurKey, CEA_outputName);

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

    CostsFile.append(DataFolder);
    CostsFile.append(RunsFile.GetValue(CurKey, CostsFileName));
    Infile.open(CostsFile, ios::in);
    if(Infile.fail())
    {
        cerr << "\nError: Unable to open file: " << CostsFile << endl;
        exit(1);
    }

    loadData (Infile, Costs);
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

    //[Interventions]

    ScreenStartAge = RunsFile.GetValueI(CurKey, ScreenStartAgeName);
    ScreenStopAge = RunsFile.GetValueI(CurKey, ScreenStopAgeName);
    ScreenFrequency = RunsFile.GetValueI(CurKey, ScreenFrequencyName);
    ScreenCoverage = RunsFile.GetValueF(CurKey, ScreenCoverageName);
    ScreenCompliance = RunsFile.GetValueF(CurKey, ScreenComplianceName);

    VaccineCoverage = RunsFile.GetValueF(CurKey, VaccineCoverageName);
    VaccineType = RunsFile.GetValue(CurKey, VaccineTypeName);
    VaccineDose = RunsFile.GetValueI(CurKey, VaccineDoseName);
    VaccineStartAge = RunsFile.GetValueI(CurKey, VaccineStartAgeName);
    VaccineEndAge = RunsFile.GetValueI(CurKey, VaccineEndAgeName);
    VaccineStartYear = RunsFile.GetValueI(CurKey, VaccineStartYearName);
    VaccineDuration = RunsFile.GetValueI(CurKey, VaccineDurationName);
    VaccineWaneTime = RunsFile.GetValueI(CurKey, VaccineWaneTimeName);
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
    ImmuneWaneTime = RunsFile.GetValueI(CurKey, ImmuneWaneTimeName);
    ImmuneDuration = RunsFile.GetValueI(CurKey, ImmuneDurationName);
    MechanismofImmunity = RunsFile.GetValue (CurKey, MechanismofImmunityName);
    Latency = RunsFile.GetValueI (CurKey, LatencyName);



    // NEW PARAMETERS

    CIN2_NL_allother_1 = RunsFile.GetValueF(CurKey, CIN2_NL_allother_1Name);
    CIN2_NL_allother_2_4 = RunsFile.GetValueF(CurKey, CIN2_NL_allother_2_4Name);
    CIN2_NL_allother_5 = RunsFile.GetValueF(CurKey, CIN2_NL_allother_5Name);
    CIN2_NL_16_1 = RunsFile.GetValueF(CurKey, CIN2_NL_16_1Name);
    CIN2_NL_16_2_4 = RunsFile.GetValueF(CurKey, CIN2_NL_16_2_4Name);
    CIN2_NL_16_5 = RunsFile.GetValueF(CurKey, CIN2_NL_16_5Name);
    HPV_NL_LR_1 = RunsFile.GetValueF(CurKey, HPV_NL_LR_1Name);
    HPV_NL_LR_2_4 = RunsFile.GetValueF(CurKey, HPV_NL_LR_2_4Name);
    HPV_NL_LR_5 = RunsFile.GetValueF(CurKey, HPV_NL_LR_5Name);
    HPV_NL_otherHR_1 = RunsFile.GetValueF(CurKey, HPV_NL_otherHR_1Name);
    HPV_NL_otherHR_2_4 = RunsFile.GetValueF(CurKey, HPV_NL_otherHR_2_4Name);
    HPV_NL_otherHR_5 = RunsFile.GetValueF(CurKey, HPV_NL_otherHR_5Name);
    HPV_NL_high5_1 = RunsFile.GetValueF(CurKey, HPV_NL_high5_1Name);
    HPV_NL_high5_2_4 = RunsFile.GetValueF(CurKey, HPV_NL_high5_2_4Name);
    HPV_NL_high5_5 = RunsFile.GetValueF(CurKey, HPV_NL_high5_5Name);
    HPV_NL_16_1 = RunsFile.GetValueF(CurKey, HPV_NL_16_1Name);
    HPV_NL_16_2_4 = RunsFile.GetValueF(CurKey, HPV_NL_16_2_4Name);
    HPV_NL_16_5 = RunsFile.GetValueF(CurKey, HPV_NL_16_5Name);
    HPV_NL_18_1 = RunsFile.GetValueF(CurKey, HPV_NL_18_1Name);
    HPV_NL_18_2_4 = RunsFile.GetValueF(CurKey, HPV_NL_18_2_4Name);
    HPV_NL_18_5 = RunsFile.GetValueF(CurKey, HPV_NL_18_5Name);
    HPV_CIN_LR_1 = RunsFile.GetValueF(CurKey, HPV_CIN_LR_1Name);
    HPV_CIN_LR_2_4 = RunsFile.GetValueF(CurKey, HPV_CIN_LR_2_4Name);
    HPV_CIN_LR_5 = RunsFile.GetValueF(CurKey, HPV_CIN_LR_5Name);
    HPV_CIN_otherHR_1 = RunsFile.GetValueF(CurKey, HPV_CIN_otherHR_1Name);
    HPV_CIN_otherHR_2_4 = RunsFile.GetValueF(CurKey, HPV_CIN_otherHR_2_4Name);
    HPV_CIN_otherHR_5 = RunsFile.GetValueF(CurKey, HPV_CIN_otherHR_5Name);
    HPV_CIN_high5_1 = RunsFile.GetValueF(CurKey, HPV_CIN_high5_1Name);
    HPV_CIN_high5_2_4 = RunsFile.GetValueF(CurKey, HPV_CIN_high5_2_4Name);
    HPV_CIN_high5_5 = RunsFile.GetValueF(CurKey, HPV_CIN_high5_5Name);
    HPV_CIN_16_1 = RunsFile.GetValueF(CurKey, HPV_CIN_16_1Name);
    HPV_CIN_16_2_4 = RunsFile.GetValueF(CurKey, HPV_CIN_16_2_4Name);
    HPV_CIN_16_5 = RunsFile.GetValueF(CurKey, HPV_CIN_16_5Name);
    HPV_CIN_18_1 = RunsFile.GetValueF(CurKey, HPV_CIN_18_1Name);
    HPV_CIN_18_2_4 = RunsFile.GetValueF(CurKey, HPV_CIN_18_2_4Name);
    HPV_CIN_18_5 = RunsFile.GetValueF(CurKey, HPV_CIN_18_5Name);
    CIN3_CA_high5_1_5 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_1_5Name);
    CIN3_CA_high5_6_10 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_6_10Name);
    CIN3_CA_high5_11_20 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_11_20Name);
    CIN3_CA_high5_21_30 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_21_30Name);
    CIN3_CA_high5_31_40 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_31_40Name);
    CIN3_CA_high5_41_50 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_41_50Name);
    CIN3_CA_high5_50 = RunsFile.GetValueF(CurKey, CIN3_CA_high5_50Name);
    CIN3_CA_16_1_5 = RunsFile.GetValueF(CurKey, CIN3_CA_16_1_5Name);
    CIN3_CA_16_6_10 = RunsFile.GetValueF(CurKey, CIN3_CA_16_6_10Name);
    CIN3_CA_16_11_20 = RunsFile.GetValueF(CurKey, CIN3_CA_16_11_20Name);
    CIN3_CA_16_21_30 = RunsFile.GetValueF(CurKey, CIN3_CA_16_21_30Name);
    CIN3_CA_16_31_40 = RunsFile.GetValueF(CurKey, CIN3_CA_16_31_40Name);
    CIN3_CA_16_41_50 = RunsFile.GetValueF(CurKey, CIN3_CA_16_41_50Name);
    CIN3_CA_16_50 = RunsFile.GetValueF(CurKey, CIN3_CA_16_50Name);
    CIN3_CA_18_1_5 = RunsFile.GetValueF(CurKey, CIN3_CA_18_1_5Name);
    CIN3_CA_18_6_10 = RunsFile.GetValueF(CurKey, CIN3_CA_18_6_10Name);
    CIN3_CA_18_11_20 = RunsFile.GetValueF(CurKey, CIN3_CA_18_11_20Name);
    CIN3_CA_18_21_30 = RunsFile.GetValueF(CurKey, CIN3_CA_18_21_30Name);
    CIN3_CA_18_31_40 = RunsFile.GetValueF(CurKey, CIN3_CA_18_31_40Name);
    CIN3_CA_18_41_50 = RunsFile.GetValueF(CurKey, CIN3_CA_18_41_50Name);
    CIN3_CA_18_50 = RunsFile.GetValueF(CurKey, CIN3_CA_18_50Name);
    CIN3_CA_otherHR_1_5 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_1_5Name);
    CIN3_CA_otherHR_6_10 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_6_10Name);
    CIN3_CA_otherHR_11_20 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_11_20Name);
    CIN3_CA_otherHR_21_30 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_21_30Name);
    CIN3_CA_otherHR_31_40 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_31_40Name);
    CIN3_CA_otherHR_41_50 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_41_50Name);
    CIN3_CA_otherHR_50 = RunsFile.GetValueF(CurKey, CIN3_CA_otherHR_50Name);
    NL_HPV16_17_19 = RunsFile.GetValueF(CurKey, NL_HPV16_17_19Name);
    NL_HPV16_20_24 = RunsFile.GetValueF(CurKey, NL_HPV16_20_24Name);
    NL_HPV16_25_29 = RunsFile.GetValueF(CurKey, NL_HPV16_25_29Name);
    NL_HPV16_30_34 = RunsFile.GetValueF(CurKey, NL_HPV16_30_34Name);
    NL_HPV16_35_39 = RunsFile.GetValueF(CurKey, NL_HPV16_35_39Name);
    NL_HPV16_40_44 = RunsFile.GetValueF(CurKey, NL_HPV16_40_44Name);
    NL_HPV16_45_49 = RunsFile.GetValueF(CurKey, NL_HPV16_45_49Name);
    NL_HPV16_50_54 = RunsFile.GetValueF(CurKey, NL_HPV16_50_54Name);
    NL_HPV16_55_65 = RunsFile.GetValueF(CurKey, NL_HPV16_55_65Name);
    NL_HPV18_17_19 = RunsFile.GetValueF(CurKey, NL_HPV18_17_19Name);
    NL_HPV18_20_24 = RunsFile.GetValueF(CurKey, NL_HPV18_20_24Name);
    NL_HPV18_25_29 = RunsFile.GetValueF(CurKey, NL_HPV18_25_29Name);
    NL_HPV18_30_34 = RunsFile.GetValueF(CurKey, NL_HPV18_30_34Name);
    NL_HPV18_35_39 = RunsFile.GetValueF(CurKey, NL_HPV18_35_39Name);
    NL_HPV18_40_44 = RunsFile.GetValueF(CurKey, NL_HPV18_40_44Name);
    NL_HPV18_45_49 = RunsFile.GetValueF(CurKey, NL_HPV18_45_49Name);
    NL_HPV18_50_54 = RunsFile.GetValueF(CurKey, NL_HPV18_50_54Name);
    NL_HPV18_55_65 = RunsFile.GetValueF(CurKey, NL_HPV18_55_65Name);
    NL_HPVhigh5_17_19 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_17_19Name);
    NL_HPVhigh5_20_24 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_20_24Name);
    NL_HPVhigh5_25_29 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_25_29Name);
    NL_HPVhigh5_30_34 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_30_34Name);
    NL_HPVhigh5_35_39 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_35_39Name);
    NL_HPVhigh5_40_44 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_40_44Name);
    NL_HPVhigh5_45_49 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_45_49Name);
    NL_HPVhigh5_50_54 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_50_54Name);
    NL_HPVhigh5_55_65 = RunsFile.GetValueF(CurKey, NL_HPVhigh5_55_65Name);
    NL_HPVoHR_17_19 = RunsFile.GetValueF(CurKey, NL_HPVoHR_17_19Name);
    NL_HPVoHR_20_24 = RunsFile.GetValueF(CurKey, NL_HPVoHR_20_24Name);
    NL_HPVoHR_25_29 = RunsFile.GetValueF(CurKey, NL_HPVoHR_25_29Name);
    NL_HPVoHR_30_34 = RunsFile.GetValueF(CurKey, NL_HPVoHR_30_34Name);
    NL_HPVoHR_35_39 = RunsFile.GetValueF(CurKey, NL_HPVoHR_35_39Name);
    NL_HPVoHR_40_44 = RunsFile.GetValueF(CurKey, NL_HPVoHR_40_44Name);
    NL_HPVoHR_45_49 = RunsFile.GetValueF(CurKey, NL_HPVoHR_45_49Name);
    NL_HPVoHR_50_54 = RunsFile.GetValueF(CurKey, NL_HPVoHR_50_54Name);
    NL_HPVoHR_55_65 = RunsFile.GetValueF(CurKey, NL_HPVoHR_55_65Name);
    NL_HPVLR_17_19 = RunsFile.GetValueF(CurKey, NL_HPVLR_17_19Name);
    NL_HPVLR_20_24 = RunsFile.GetValueF(CurKey, NL_HPVLR_20_24Name);
    NL_HPVLR_25_29 = RunsFile.GetValueF(CurKey, NL_HPVLR_25_29Name);
    NL_HPVLR_30_34 = RunsFile.GetValueF(CurKey, NL_HPVLR_30_34Name);
    NL_HPVLR_35_39 = RunsFile.GetValueF(CurKey, NL_HPVLR_35_39Name);
    NL_HPVLR_40_44 = RunsFile.GetValueF(CurKey, NL_HPVLR_40_44Name);
    NL_HPVLR_45_49 = RunsFile.GetValueF(CurKey, NL_HPVLR_45_49Name);
    NL_HPVLR_50_54 = RunsFile.GetValueF(CurKey, NL_HPVLR_50_54Name);
    NL_HPVLR_55_65 = RunsFile.GetValueF(CurKey, NL_HPVLR_55_65Name);
    ImmuneDegree = RunsFile.GetValueF(CurKey, ImmuneDegreeName);
    ImmuneDegree16 = RunsFile.GetValueF(CurKey, ImmuneDegree16Name);
    pRegresstoHPV = RunsFile.GetValueF(CurKey, pRegresstoHPVName);
    CIN3_NL = RunsFile.GetValueF(CurKey, CIN3_NLName);
    CIN2_CA = RunsFile.GetValueF(CurKey, CIN2_CAName);
    HPV_CIN2_16 = RunsFile.GetValueF(CurKey, HPV_CIN2_16Name);
    HPV_CIN2_allother = RunsFile.GetValueF(CurKey, HPV_CIN2_allotherName);
    CA1_CA1d = RunsFile.GetValueF(CurKey, CA1_CA1dName);
    CA2_CA2d = RunsFile.GetValueF(CurKey, CA2_CA2dName);
    CA3_CA3d = RunsFile.GetValueF(CurKey, CA3_CA3dName);
    CA1_CA2 = RunsFile.GetValueF(CurKey, CA1_CA2Name);
    CA2_CA3 = RunsFile.GetValueF(CurKey, CA2_CA3Name);

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

    CIN2_NL = CINRegression[0][0];

    for (int j = 0; j < 99; j ++){
        pHPV_16[j] = HPVInc[j][0];
        pHPV_18[j] = HPVInc[j][1];
        pHPV_31[j] = HPVInc[j][2];
        pHPV_33[j] = HPVInc[j][3];
        pHPV_45[j] = HPVInc[j][4];
        pHPV_52[j] = HPVInc[j][5];
        pHPV_58[j] = HPVInc[j][6];
        pHPV_otherHR[j] = HPVInc[j][7];
        pHPV_LR[j] = HPVInc[j][8];

        if(j < 20){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_17_19);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_17_19);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_17_19);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_17_19);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_17_19);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_17_19);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_17_19);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_17_19);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_17_19);
        } else if (j <25){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_20_24);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_20_24);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_20_24);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_20_24);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_20_24);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_20_24);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_20_24);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_20_24);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_20_24);
        } else if (j < 30){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_25_29);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_25_29);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_25_29);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_25_29);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_25_29);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_25_29);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_25_29);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_25_29);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_25_29);
        } else if (j < 35){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_30_34);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_30_34);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_30_34);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_30_34);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_30_34);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_30_34);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_30_34);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_30_34);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_30_34);
        } else if (j < 40){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_35_39);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_35_39);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_35_39);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_35_39);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_35_39);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_35_39);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_35_39);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_35_39);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_35_39);
        } else if (j < 45){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_40_44);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_40_44);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_40_44);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_40_44);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_40_44);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_40_44);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_40_44);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_40_44);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_40_44);
        } else if (j < 50){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_45_49);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_45_49);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_45_49);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_45_49);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_45_49);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_45_49);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_45_49);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_45_49);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_45_49);
        } else if (j < 55){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_50_54);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_50_54);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_50_54);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_50_54);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_50_54);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_50_54);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_50_54);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_50_54);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_50_54);
        } else if (j < 65){
            pHPV_16[j] = ApplyMult (pHPV_16[j], NL_HPV16_55_65);
            pHPV_18[j] = ApplyMult (pHPV_18[j], NL_HPV18_55_65);
            pHPV_31[j] = ApplyMult (pHPV_31[j], NL_HPVhigh5_55_65);
            pHPV_33[j] = ApplyMult (pHPV_33[j], NL_HPVhigh5_55_65);
            pHPV_45[j] = ApplyMult (pHPV_45[j], NL_HPVhigh5_55_65);
            pHPV_52[j] = ApplyMult (pHPV_52[j], NL_HPVhigh5_55_65);
            pHPV_58[j] = ApplyMult (pHPV_58[j], NL_HPVhigh5_55_65);
            pHPV_otherHR[j] = ApplyMult (pHPV_58[j], NL_HPVoHR_55_65);
            pHPV_LR[j] = ApplyMult (pHPV_LR[j], NL_HPVLR_55_65);
        }
        
        if(j < 6){
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_1_5);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_1_5);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_1_5);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_1_5);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_1_5);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_1_5);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_1_5);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_1_5);
        } else if (j < 11){
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_6_10);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_6_10);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_6_10);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_6_10);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_6_10);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_6_10);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_6_10);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_6_10);
        } else if (j < 21){
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_11_20);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_11_20);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_11_20);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_11_20);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_11_20);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_11_20);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_11_20);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_11_20);
        } else if (j < 31){
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_21_30);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_21_30);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_21_30);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_21_30);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_21_30);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_21_30);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_21_30);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_21_30);
        } else if (j < 41){
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_31_40);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_31_40);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_31_40);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_31_40);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_31_40);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_31_40);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_31_40);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_31_40);
        } else if (j < 51){
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_41_50);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_41_50);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_41_50);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_41_50);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_41_50);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_41_50);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_41_50);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_41_50);
        } else {
            pCIN3_CA1_oHR[j] = ApplyMult (CINProgression[j][0], CIN3_CA_otherHR_50);
            pCIN3_CA1_16[j] = ApplyMult (CINProgression[j][1], CIN3_CA_16_50);
            pCIN3_CA1_18[j] = ApplyMult (CINProgression[j][2], CIN3_CA_18_50);
            pCIN3_CA1_31[j] = ApplyMult (CINProgression[j][3], CIN3_CA_high5_50);
            pCIN3_CA1_33[j] = ApplyMult (CINProgression[j][4], CIN3_CA_high5_50);
            pCIN3_CA1_45[j] = ApplyMult (CINProgression[j][5], CIN3_CA_high5_50);
            pCIN3_CA1_52[j] = ApplyMult (CINProgression[j][6], CIN3_CA_high5_50);
            pCIN3_CA1_58[j] = ApplyMult (CINProgression[j][7], CIN3_CA_high5_50);
        }

        if(j < 1){
            pHPV_LR_NL[j] = ApplyMult(HPVClearance[j][0], HPV_NL_LR_1);
            pHPV_otherHR_NL[j] = ApplyMult(HPVClearance[j][1], HPV_NL_otherHR_1);
            pHPV_16_NL[j] = ApplyMult(HPVClearance[j][2], HPV_NL_16_1);
            pHPV_18_NL[j] = ApplyMult(HPVClearance[j][3], HPV_NL_18_1);
            pHPV_31_NL[j] = ApplyMult(HPVClearance[j][4], HPV_NL_high5_1);
            pHPV_33_NL[j] = ApplyMult(HPVClearance[j][5], HPV_NL_high5_1);
            pHPV_45_NL[j] = ApplyMult(HPVClearance[j][6], HPV_NL_high5_1);
            pHPV_52_NL[j] = ApplyMult(HPVClearance[j][7], HPV_NL_high5_1);
            pHPV_58_NL[j] = ApplyMult(HPVClearance[j][8], HPV_NL_high5_1);
            pHPV_LR_CIN[j] = ApplyMult(HPVProgression[j][0], HPV_CIN_LR_1);
            pHPV_otherHR_CIN[j] = ApplyMult(HPVProgression[j][1], HPV_CIN_otherHR_1);
            pHPV_16_CIN[j] = ApplyMult(HPVProgression[j][2], HPV_CIN_16_1);
            pHPV_18_CIN[j] = ApplyMult(HPVProgression[j][3], HPV_CIN_18_1);
            pHPV_31_CIN[j] = ApplyMult(HPVProgression[j][4], HPV_CIN_high5_1);
            pHPV_33_CIN[j] = ApplyMult(HPVProgression[j][5], HPV_CIN_high5_1);
            pHPV_45_CIN[j] = ApplyMult(HPVProgression[j][6], HPV_CIN_high5_1);
            pHPV_52_CIN[j] = ApplyMult(HPVProgression[j][7], HPV_CIN_high5_1);
            pHPV_58_CIN[j] = ApplyMult(HPVProgression[j][8], HPV_CIN_high5_1);
            pCIN2_NL_16[j] = ApplyMult (CIN2_NL, CIN2_NL_16_1);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN3_NL);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_1);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN3_NL);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_1);
            pCIN3_NL_high5[j] = ApplyMult (pCIN2_NL_high5[j], CIN3_NL);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_1);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN2_NL_oHR[j], CIN3_NL);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_1);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN3_NL);
        } else if (j < 5){
            pHPV_LR_NL[j] = ApplyMult(HPVClearance[j][0], HPV_NL_LR_2_4);
            pHPV_otherHR_NL[j] = ApplyMult(HPVClearance[j][1], HPV_NL_otherHR_2_4);
            pHPV_16_NL[j] = ApplyMult(HPVClearance[j][2], HPV_NL_16_2_4);
            pHPV_18_NL[j] = ApplyMult(HPVClearance[j][3], HPV_NL_18_2_4);
            pHPV_31_NL[j] = ApplyMult(HPVClearance[j][4], HPV_NL_high5_2_4);
            pHPV_33_NL[j] = ApplyMult(HPVClearance[j][5], HPV_NL_high5_2_4);
            pHPV_45_NL[j] = ApplyMult(HPVClearance[j][6], HPV_NL_high5_2_4);
            pHPV_52_NL[j] = ApplyMult(HPVClearance[j][7], HPV_NL_high5_2_4);
            pHPV_58_NL[j] = ApplyMult(HPVClearance[j][8], HPV_NL_high5_2_4);
            pHPV_LR_CIN[j] = ApplyMult(HPVProgression[j][0], HPV_CIN_LR_2_4);
            pHPV_otherHR_CIN[j] = ApplyMult(HPVProgression[j][1], HPV_CIN_otherHR_2_4);
            pHPV_16_CIN[j] = ApplyMult(HPVProgression[j][2], HPV_CIN_16_2_4);
            pHPV_18_CIN[j] = ApplyMult(HPVProgression[j][3], HPV_CIN_18_2_4);
            pHPV_31_CIN[j] = ApplyMult(HPVProgression[j][4], HPV_CIN_high5_2_4);
            pHPV_33_CIN[j] = ApplyMult(HPVProgression[j][5], HPV_CIN_high5_2_4);
            pHPV_45_CIN[j] = ApplyMult(HPVProgression[j][6], HPV_CIN_high5_2_4);
            pHPV_52_CIN[j] = ApplyMult(HPVProgression[j][7], HPV_CIN_high5_2_4);
            pHPV_58_CIN[j] = ApplyMult(HPVProgression[j][8], HPV_CIN_high5_2_4);
            pCIN2_NL_16[j] = ApplyMult (CIN2_NL, CIN2_NL_16_2_4);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN3_NL);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_2_4);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN3_NL);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_2_4);
            pCIN3_NL_high5[j] = ApplyMult (pCIN2_NL_high5[j], CIN3_NL);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_2_4);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN2_NL_oHR[j], CIN3_NL);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_2_4);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN3_NL);
        } else {
            pHPV_LR_NL[j] = ApplyMult(HPVClearance[j][0], HPV_NL_LR_5);
            pHPV_otherHR_NL[j] = ApplyMult(HPVClearance[j][1], HPV_NL_otherHR_5);
            pHPV_16_NL[j] = ApplyMult(HPVClearance[j][2], HPV_NL_16_5);
            pHPV_18_NL[j] = ApplyMult(HPVClearance[j][3], HPV_NL_18_5);
            pHPV_31_NL[j] = ApplyMult(HPVClearance[j][4], HPV_NL_high5_5);
            pHPV_33_NL[j] = ApplyMult(HPVClearance[j][5], HPV_NL_high5_5);
            pHPV_45_NL[j] = ApplyMult(HPVClearance[j][6], HPV_NL_high5_5);
            pHPV_52_NL[j] = ApplyMult(HPVClearance[j][7], HPV_NL_high5_5);
            pHPV_58_NL[j] = ApplyMult(HPVClearance[j][8], HPV_NL_high5_5);
            pHPV_LR_CIN[j] = ApplyMult(HPVProgression[j][0], HPV_CIN_LR_5);
            pHPV_otherHR_CIN[j] = ApplyMult(HPVProgression[j][1], HPV_CIN_otherHR_5);
            pHPV_16_CIN[j] = ApplyMult(HPVProgression[j][2], HPV_CIN_16_5);
            pHPV_18_CIN[j] = ApplyMult(HPVProgression[j][3], HPV_CIN_18_5);
            pHPV_31_CIN[j] = ApplyMult(HPVProgression[j][4], HPV_CIN_high5_5);
            pHPV_33_CIN[j] = ApplyMult(HPVProgression[j][5], HPV_CIN_high5_5);
            pHPV_45_CIN[j] = ApplyMult(HPVProgression[j][6], HPV_CIN_high5_5);
            pHPV_52_CIN[j] = ApplyMult(HPVProgression[j][7], HPV_CIN_high5_5);
            pHPV_58_CIN[j] = ApplyMult(HPVProgression[j][8], HPV_CIN_high5_5);
            pCIN2_NL_16[j] = ApplyMult (CIN2_NL, CIN2_NL_16_5);
            pCIN3_NL_16[j] = ApplyMult (pCIN2_NL_16[j], CIN3_NL);
            pCIN2_NL_18[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_5);
            pCIN3_NL_18[j] = ApplyMult (pCIN2_NL_18[j], CIN3_NL);
            pCIN2_NL_high5[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_5);
            pCIN3_NL_high5[j] = ApplyMult (pCIN2_NL_high5[j], CIN3_NL);
            pCIN2_NL_oHR[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_5);
            pCIN3_NL_oHR[j] = ApplyMult (pCIN2_NL_oHR[j], CIN3_NL);
            pCIN2_NL_LR[j] = ApplyMult (CIN2_NL, CIN2_NL_allother_5);
            pCIN3_NL_LR[j] = ApplyMult (pCIN3_NL_LR[j], CIN3_NL);
        }

        pCIN2_CA1_oHR[j] = ApplyMult(pCIN3_CA1_oHR[j], CIN2_CA);
        pCIN2_CA1_16[j] = ApplyMult (pCIN3_CA1_16[j], CIN2_CA);
        pCIN2_CA1_18[j] = ApplyMult (pCIN3_CA1_18[j], CIN2_CA);
        pCIN2_CA1_31[j] = ApplyMult(pCIN3_CA1_31[j], CIN2_CA);
        pCIN2_CA1_33[j] = ApplyMult(pCIN3_CA1_33[j], CIN2_CA);
        pCIN2_CA1_45[j] = ApplyMult(pCIN3_CA1_45[j], CIN2_CA);
        pCIN2_CA1_52[j] = ApplyMult(pCIN3_CA1_52[j], CIN2_CA);
        pCIN2_CA1_58[j] = ApplyMult(pCIN3_CA1_58[j], CIN2_CA);
        mCA1[j] = CaMortality[j][0];
        mCA2[j] = CaMortality[j][1];
        mCA3[j] = CaMortality[j][2];
        mCA1d[j] = CaMortality[j][3];
        mCA2d[j] = CaMortality[j][4];
        mCA3d[j] = CaMortality[j][5];
    }

    cytosens_NL = cytosens[1][0];
    cytosens_CIN = cytosens[1][1];
    cytosens_Ca = cytosens[1][3];

    if(VaccineType == "Bivalent"){
        vaccinetype = VxType::Bivalent;
        VE_1618 = vaccineefficacy[0][0];
        VE_high5 = vaccineefficacy[1][0];
        cHPVVaccine = Costs[12][0];
    } else if(VaccineType == "Nonavalent"){
        vaccinetype = VxType::Nonavalent;
        VE_1618 = vaccineefficacy[0][1];
        VE_high5 = vaccineefficacy[1][1];
        cHPVVaccine = Costs[13][0];
    }


    if(MechanismofImmunity == "Degree"){
        ImmuneMechanism = Immunity::Degree;
    } else if(MechanismofImmunity == "Factor"){
        ImmuneMechanism = Immunity::Factor;
    } else if(MechanismofImmunity == "None"){
        ImmuneMechanism = Immunity::None;
    }


    cPtTime = Costs[0][0];
    cPaptest = Costs[1][0];
    cReturnForResult = Costs[2][0];
    cColpoTime = Costs[3][0];
    cColpoProc = Costs[4][0];
    cCryoVisit = Costs[5][0];
    cCryoHPV = Costs[6][0];
    cCryoCIN23 = Costs[7][0];
    cCryoCA = Costs[8][0];
    cStage1Ca = Costs[9][0];
    cStage2Ca = Costs[10][0];
    cStage3Ca = Costs[11][0];

    disabilityCA1 = Disability[0][0];
    disabilityCA2 = Disability[1][0];
    disabilityCA3 = Disability[2][0];


}

double Inputs::ApplyMult(double prob, double mult){
    double rate;
    rate = -log (1 - prob) * mult;
    prob = 1 - exp(-rate);
    return(prob);
}

void Inputs::loadCalibParams(vector<double> calib_params) {

    CIN2_NL_allother_1 = calib_params[0];
    CIN2_NL_allother_2_4 = calib_params[1];
    CIN2_NL_allother_5 = calib_params[2];
    CIN2_NL_16_1 = calib_params[3];
    CIN2_NL_16_2_4 = calib_params[4];
    CIN2_NL_16_5 = calib_params[5];
    HPV_NL_LR_1 = calib_params[6];
    HPV_NL_LR_2_4 = calib_params[7];
    HPV_NL_LR_5 = calib_params[8];
    HPV_NL_otherHR_1 = calib_params[9];
    HPV_NL_otherHR_2_4 = calib_params[10];
    HPV_NL_otherHR_5 = calib_params[11];
    HPV_NL_high5_1 = calib_params[12];
    HPV_NL_high5_2_4 = calib_params[13];
    HPV_NL_high5_5 = calib_params[14];
    HPV_NL_16_1 = calib_params[15];
    HPV_NL_16_2_4 = calib_params[16];
    HPV_NL_16_5 = calib_params[17];
    HPV_NL_18_1 = calib_params[18];
    HPV_NL_18_2_4 = calib_params[19];
    HPV_NL_18_5 = calib_params[20];
    HPV_CIN_LR_1 = calib_params[21];
    HPV_CIN_LR_2_4 = calib_params[22];
    HPV_CIN_LR_5 = calib_params[23];
    HPV_CIN_otherHR_1 = calib_params[24];
    HPV_CIN_otherHR_2_4 = calib_params[25];
    HPV_CIN_otherHR_5 = calib_params[26];
    HPV_CIN_high5_1 = calib_params[27];
    HPV_CIN_high5_2_4 = calib_params[28];
    HPV_CIN_high5_5 = calib_params[29];
    HPV_CIN_16_1 = calib_params[30];
    HPV_CIN_16_2_4 = calib_params[31];
    HPV_CIN_16_5 = calib_params[32];
    HPV_CIN_18_1 = calib_params[33];
    HPV_CIN_18_2_4 = calib_params[34];
    HPV_CIN_18_5 = calib_params[35];
    CIN3_CA_high5_1_5 = calib_params[36];
    CIN3_CA_high5_6_10 = calib_params[37];
    CIN3_CA_high5_11_20 = calib_params[38];
    CIN3_CA_high5_21_30 = calib_params[39];
    CIN3_CA_high5_31_40 = calib_params[40];
    CIN3_CA_high5_41_50 = calib_params[41];
    CIN3_CA_high5_50 = calib_params[42];
    CIN3_CA_16_1_5 = calib_params[43];
    CIN3_CA_16_6_10 = calib_params[44];
    CIN3_CA_16_11_20 = calib_params[45];
    CIN3_CA_16_21_30 = calib_params[46];
    CIN3_CA_16_31_40 = calib_params[47];
    CIN3_CA_16_41_50 = calib_params[48];
    CIN3_CA_16_50 = calib_params[49];
    CIN3_CA_18_1_5 = calib_params[50];
    CIN3_CA_18_6_10 = calib_params[51];
    CIN3_CA_18_11_20 = calib_params[52];
    CIN3_CA_18_21_30 = calib_params[53];
    CIN3_CA_18_31_40 = calib_params[54];
    CIN3_CA_18_41_50 = calib_params[55];
    CIN3_CA_18_50 = calib_params[56];
    CIN3_CA_otherHR_1_5 = calib_params[57];
    CIN3_CA_otherHR_6_10 = calib_params[58];
    CIN3_CA_otherHR_11_20 = calib_params[59];
    CIN3_CA_otherHR_21_30 = calib_params[60];
    CIN3_CA_otherHR_31_40 = calib_params[61];
    CIN3_CA_otherHR_41_50 = calib_params[62];
    CIN3_CA_otherHR_50 = calib_params[63];
    NL_HPV16_17_19 = calib_params[64];
    NL_HPV16_20_24 = calib_params[65];
    NL_HPV16_25_29 = calib_params[66];
    NL_HPV16_30_34 = calib_params[67];
    NL_HPV16_35_39 = calib_params[68];
    NL_HPV16_40_44 = calib_params[69];
    NL_HPV16_45_49 = calib_params[70];
    NL_HPV16_50_54 = calib_params[71];
    NL_HPV16_55_65 = calib_params[72];
    NL_HPV18_17_19 = calib_params[73];
    NL_HPV18_20_24 = calib_params[74];
    NL_HPV18_25_29 = calib_params[75];
    NL_HPV18_30_34 = calib_params[76];
    NL_HPV18_35_39 = calib_params[77];
    NL_HPV18_40_44 = calib_params[78];
    NL_HPV18_45_49 = calib_params[79];
    NL_HPV18_50_54 = calib_params[80];
    NL_HPV18_55_65 = calib_params[81];
    NL_HPVhigh5_17_19 = calib_params[82];
    NL_HPVhigh5_20_24 = calib_params[83];
    NL_HPVhigh5_25_29 = calib_params[84];
    NL_HPVhigh5_30_34 = calib_params[85];
    NL_HPVhigh5_35_39 = calib_params[86];
    NL_HPVhigh5_40_44 = calib_params[87];
    NL_HPVhigh5_45_49 = calib_params[88];
    NL_HPVhigh5_50_54 = calib_params[89];
    NL_HPVhigh5_55_65 = calib_params[90];
    NL_HPVoHR_17_19 = calib_params[91];
    NL_HPVoHR_20_24 = calib_params[92];
    NL_HPVoHR_25_29 = calib_params[93];
    NL_HPVoHR_30_34 = calib_params[94];
    NL_HPVoHR_35_39 = calib_params[95];
    NL_HPVoHR_40_44 = calib_params[96];
    NL_HPVoHR_45_49 = calib_params[97];
    NL_HPVoHR_50_54 = calib_params[98];
    NL_HPVoHR_55_65 = calib_params[99];
    NL_HPVLR_17_19 = calib_params[100];
    NL_HPVLR_20_24 = calib_params[101];
    NL_HPVLR_25_29 = calib_params[102];
    NL_HPVLR_30_34 = calib_params[103];
    NL_HPVLR_35_39 = calib_params[104];
    NL_HPVLR_40_44 = calib_params[105];
    NL_HPVLR_45_49 = calib_params[106];
    NL_HPVLR_50_54 = calib_params[107];
    NL_HPVLR_55_65 = calib_params[108];
    ImmuneDegree = calib_params[109];
    ImmuneDegree16 = calib_params[110];
    pRegresstoHPV = calib_params[111];
    CIN3_NL = calib_params[112];
    CIN2_CA = calib_params[113];
    HPV_CIN2_16 = calib_params[114];
    HPV_CIN2_allother = calib_params[115];
    CA1_CA1d = calib_params[116];
    CA2_CA2d = calib_params[117];
    CA3_CA3d = calib_params[118];
    CA1_CA2 = calib_params[119];
    CA2_CA3 = calib_params[120];
    ImmuneDuration = calib_params[121];
    ImmuneWaneTime = calib_params[122];
}

void Inputs::loadStringData(ifstream &Infile, string &VariableName) {
    getline(Infile, VariableName);
}