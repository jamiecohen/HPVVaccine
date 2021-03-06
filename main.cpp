//
//  main.cpp
//  HPVVaccine
//
//  Created by Jamie Cohen on 11/4/17.
//  Copyright © 2019 Jamie Cohen. All rights reserved.
//

#include <iostream>
#include <vector>
#include "statemachine.h"
#include <boost/filesystem.hpp>
#include "calibrate.h"
#include <thread>


using namespace std;

Output RunBirthCohort(string, string, string, string);
Output RunPopulation(string, string, string, string);
void RunCalibration(calibrate &calib, Inputs &tables, int i);
void RunValidation(Inputs &tables, Output &trace);

int main(int argc, char* argv[]) {
    string DataFolder;
    string OutputFolder;
    if(argc == 1 || argc == 2){
        DataFolder = "/Users/jamiecohen/Dropbox (Personal)/GSAS/HIV-HPV Research/Model Code/HPVVaccine/Data/";
        OutputFolder = "/Users/jamiecohen/Dropbox (Personal)/GSAS/HIV-HPV Research/Model Code/HPVVaccine/Model Output/";
    } else {
        DataFolder = "../Data/";
        OutputFolder = "/n/scratch2/jac66/Output/";
    }
    unsigned int run;
    string RunType;
    string RunsFileName(DataFolder);
    string FileName;
    if(argc == 1){
        RunsFileName.append("Valid_NoImmunity.ini");
        FileName = "Valid_NoImmunity.ini";
    }
    else if(argc > 1){
        RunsFileName.append(argv[1]);
        FileName = argv[1];
    }
    CIniFile RunsFile(RunsFileName);
    if (!RunsFile.ReadFile()) {
        cout << "Could not read Runs File: " << RunsFileName << endl;
        exit(1);
    }
    RunType = RunsFile.GetKeyName (0);
    if (RunsFile.GetValue(RunType, "RunType") == "Calibration"){
        Inputs tables(OutputFolder, DataFolder);
        tables.loadRFG (RunsFileName, RunType);
        string ModelStruct = "Calib";
        if(tables.Latency){
            ModelStruct.append("_Latency");
        } else{
            ModelStruct.append("_NoLatency");
        }
        switch(tables.ImmuneMechanism){
            case Inputs::Degree:
                ModelStruct.append("_Degree");
                break;
            case Inputs::Factor:
                ModelStruct.append("_Factor");
                break;
            case Inputs::None:
                ModelStruct.append("_NoImmunity");
                break;
        }
        if(argc >= 4){
            cout << ModelStruct << ": Chain number " << argv[3] << endl;
        }
        int n_sims = tables.Simulations;
        int n_params = tables.Multipliers.size();
        int n_targs = tables.CalibTargs.size();
        calibrate calib (n_sims, n_params, n_targs);
        calib.multipliers_names = tables.MultipliersNames;
        calib.calib_targs_names = tables.CalibTargsNames;
        for (int i = 0; i < n_targs; i ++){
            calib.calib_targs[i] = tables.CalibTargs[i][0];
            calib.calib_targs_N[i] = tables.CalibTargs[i][1];
        }
        for (int i = 0; i < n_params; i++){
            for (int j = 0; j < 3; j++){
                calib.multipliers[i][j] = tables.Multipliers[i][j];
            }
        }
        for (int i = 0; i < n_params; i++){
            if(calib.multipliers[i][2] == 0){
                calib.multipliers_type[i] = calib.RR;
            } else if(calib.multipliers[i][2] == 1){
                calib.multipliers_type[i] = calib.prob;
            } else if(calib.multipliers[i][2] == 2){
                calib.multipliers_type[i] = calib.Unif;
            }
        }

        for (int i = 0; i < n_sims; i++){
            RunCalibration (calib, tables, i);
        }
        string OutDir = OutputFolder.append("HPVVaccine_Calib");
        if(tables.Latency){
            OutDir.append("_Latency");
        } else{
            OutDir.append("_NoLatency");
        }
        switch(tables.ImmuneMechanism){
            case Inputs::Degree:
                OutDir.append("_Degree");
                break;
            case Inputs::Factor:
                OutDir.append("_Factor");
                break;
            case Inputs::None:
                OutDir.append("_NoImmunity");
                break;
        }

        if(argc == 4){
            OutDir.append("/");
            OutDir.append(argv[3]);
        }
        const boost::filesystem::path dir (OutDir);
        boost::filesystem::create_directories (dir);
        ofstream output;
        string OutputFileName;
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("best_GOF.txt");
        output.open(OutputFileName.c_str (), ios::out);
        if(output) {
            output << "GOF" << endl;
            output << calib.GOF_min << endl;
            output << endl;
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("all_GOF.txt");
        output.open(OutputFileName.c_str (), ios::out);
        if(output) {
            for(int i = 0; i < n_sims; i++){
                output << "Sim" << i << '\t';
                output << calib.GOF[i] << endl;
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("best_params.txt");
        output.open(OutputFileName.c_str (), ios::out);
        if(output) {
            output << calib.multipliers_names << endl;
            for(double best_param : calib.best_params){
                output<< best_param << '\t';
            }
            output << endl;
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();
        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("best_output.txt");
        output.open(OutputFileName.c_str (), ios::out);
        if(output) {
            output << calib.calib_targs_names << endl;
            for(double best_output : calib.best_output){
                output<< best_output << '\t';
            }
            output << endl;
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

    } else if (RunsFile.GetValue(RunType, "RunType") == "Cohort") {

        cout << "Running " << FileName << endl;
        int numruns = 0;
        for (run = 0; run < RunsFile.GetNumKeys (); run++) {
            numruns++;
        }
        Inputs tables(OutputFolder, DataFolder);
        tables.loadRFG (RunsFileName, RunType);
        int ModelStartAge = tables.ModelStartAge;
        int ModelStopAge = tables.ModelStopAge;
        int SimulationYears = tables.SimulationYears;
        vector<Output> modeloutputs;
        modeloutputs.reserve(numruns);
        vector<string> CurKey;
        CurKey.reserve(numruns);

        for (run = 0; run < RunsFile.GetNumKeys (); run++) {
            cout << "Running Strat " << run << endl;
            CurKey.push_back (RunsFile.GetKeyName (run));
            modeloutputs.push_back(RunBirthCohort (RunsFileName, CurKey[run], OutputFolder, DataFolder));
        }
        for (int i = 0; i < modeloutputs.size(); i++){
            string OutputDir (OutputFolder);
            OutputDir.append (RunsFile.GetValue (CurKey[i], "OutputDir"));
            const boost::filesystem::path dir (OutputDir);
            boost::filesystem::create_directories (dir);
            if(tables.incidence_output){
                modeloutputs[i].writeInc (&OutputDir, ModelStartAge, ModelStopAge, SimulationYears);
            }
            if(tables.mortality_output){
                modeloutputs[i].writeMort (&OutputDir, ModelStopAge, SimulationYears);
            }
            if(tables.dwelltime_output){
                modeloutputs[i].writeDwellTime (&OutputDir, SimulationYears);
            }
            if(tables.CEA_output){
                modeloutputs[i].writeCEA (&OutputDir, ModelStopAge, SimulationYears);
            }
        }
    } else if (RunsFile.GetValue(RunType, "RunType") == "Population") {

        cout << "Running " << FileName << endl;
        unsigned int numruns = RunsFile.GetNumKeys ();
        Inputs tables(OutputFolder, DataFolder);
        tables.loadRFG (RunsFileName, RunType);
        int ModelStartAge = tables.ModelStartAge;
        int ModelStopAge = tables.ModelStopAge;
        int TotalSimYears = tables.BurnInYears + tables.SimulationYears;
        vector<Output> modeloutputs;
        modeloutputs.reserve(numruns);
        vector<string> CurKey;
        CurKey.reserve(numruns);

        for (run = 0; run < RunsFile.GetNumKeys (); run++) {
            cout << "Running Strat " << run << endl;
            CurKey.push_back (RunsFile.GetKeyName (run));
            modeloutputs.push_back(RunPopulation (RunsFileName, CurKey[run], OutputFolder, DataFolder));
        }

        for (int i = 0; i < modeloutputs.size(); i++){
            string OutputDir (OutputFolder);
            OutputDir.append (RunsFile.GetValue (CurKey[i], "OutputDir"));
            const boost::filesystem::path dir (OutputDir);
            boost::filesystem::create_directories (dir);
            if(tables.incidence_output){
                modeloutputs[i].writeInc (&OutputDir, ModelStartAge, ModelStopAge, TotalSimYears);
            }
            if(tables.mortality_output){
                modeloutputs[i].writeMort (&OutputDir, ModelStopAge, TotalSimYears);
            }
            if(tables.dwelltime_output){
                modeloutputs[i].writeDwellTime (&OutputDir, TotalSimYears);
            }
            if(tables.CEA_output){
                modeloutputs[i].writeCEA (&OutputDir, ModelStopAge, TotalSimYears);
            }
        }
    } else if (RunsFile.GetValue(RunType, "RunType") == "Validation") {

        cout << "Running " << FileName << endl;
        Inputs tables(OutputFolder, DataFolder);
        tables.loadRFG (RunsFileName, RunType);

        string ModelStruct = "Validation";
        if(tables.Latency){
            ModelStruct.append("_Latency");
        } else{
            ModelStruct.append("_NoLatency");
        }
        switch(tables.ImmuneMechanism){
            case Inputs::Degree:
                ModelStruct.append("_Degree");
                break;
            case Inputs::Factor:
                ModelStruct.append("_Factor");
                break;
            case Inputs::None:
                ModelStruct.append("_NoImmunity");
                break;
        }

        int TotalSimYears = tables.BurnInYears;
        Output modeloutput(tables, TotalSimYears);
        RunValidation(tables, modeloutput);

        string OutDir = OutputFolder.append("HPVVaccine_Validation");
        if(tables.Latency){
            OutDir.append("_Latency");
        } else{
            OutDir.append("_NoLatency");
        }
        switch(tables.ImmuneMechanism){
            case Inputs::Degree:
                OutDir.append("_Degree");
                break;
            case Inputs::Factor:
                OutDir.append("_Factor");
                break;
            case Inputs::None:
                OutDir.append("_NoImmunity");
                break;
        }
        if(argc == 4){
            OutDir.append("/");
            OutDir.append(argv[3]);
        }

        const boost::filesystem::path dir (OutDir);
        boost::filesystem::create_directories (dir);
        modeloutput.writeValidation(&OutDir);

    }

    return(0);
}

void RunCalibration(calibrate &calib, Inputs &tables, int i){
    cout << "Running Sim " << i << endl;
    int n_params = tables.Multipliers.size ();
    vector<double> calib_params (n_params);
    calib_params = calib.loadCalibData (n_params, i);
    tables.loadCalibParams (calib_params);
    tables.loadVariables ();
    int CurrentModelYear = tables.StartYear;
    int ModelStartAge = tables.ModelStartAge;
    int ModelStopAge = tables.ModelStopAge;
    int SimulationYears = tables.BurnInYears;
    vector<Woman> women;
    women.reserve (tables.CohortSize);
    helper help;

    for (int j = ModelStartAge; j < ModelStopAge; j++) {
        for (int k = 0; k < tables.burnin[j]; k++) {
            Woman newWoman(j, CurrentModelYear, help, tables.ScreenCoverage);
            women.push_back(newWoman);
        }
    }

    Output trace_burnin (tables, SimulationYears);
    StateMachine Machine;

    for(int y = 0; y < SimulationYears; y++){
        for (auto & k : women) {
            Machine.runPopulationYear (k, tables, trace_burnin, true, help, y);
            if (!k.Alive) {
                k.reset(ModelStartAge, CurrentModelYear + 1, help, tables.ScreenCoverage);
            }
        }
        CurrentModelYear++;
    }

    for (auto & k : women) {
        trace_burnin.createTypeDist (k);
    }
    trace_burnin.createCalibOutput (SimulationYears-1);
    calib.saved_output[i] = trace_burnin.calib;
    double rand;
    rand = help.getrand ();
    calib.CalculateGOF (i, rand);
    women.clear();
}

Output RunBirthCohort(string RunsFileName, string CurKey, string OutputFolder, string DataFolder){
    helper help;
    StateMachine Machine;
    Inputs tables(std::move(OutputFolder), std::move(DataFolder));
    tables.loadRFG (RunsFileName, CurKey);
    tables.loadVariables ();
    int BurnInModelYear = tables.StartYear - tables.BurnInYears;
    int TotalSimYears = tables.BurnInYears + tables.SimulationYears;
    int ModelStartAge = tables.ModelStartAge;
    int ModelStopAge = tables.ModelStopAge;
    vector<Woman> women;
    women.reserve(tables.CohortSize);

    for (int j = ModelStartAge; j < ModelStopAge; j++) {
        for (int k = 0; k < tables.burnin[j]; k++) {
            Woman newWoman(j, BurnInModelYear, help, tables.ScreenCoverage);
            women.push_back(newWoman);
        }
    }
    Output trace (tables, TotalSimYears);

    // Start running burn-in period
    for(int y = 0; y < tables.BurnInYears; y++){
        for (auto & k : women) {
            Machine.runPopulationYear (k, tables, trace, true, help, y);
            if (!k.Alive) {
                k.reset(ModelStartAge, BurnInModelYear + 1, help, tables.ScreenCoverage);
            }
        }
        BurnInModelYear++;
    }

    // Now start running simulation from time 0
    int SimYear = 0;
    int CurrentModelYear = tables.StartYear;
    for (int y = tables.BurnInYears; y < TotalSimYears; y++) {
        for (auto &k : women) {
            if (k.Alive) {
                Machine.runPopulationYear (k, tables, trace, false, help, y);
            }
        }
        CurrentModelYear++;
        trace.discDALY += (trace.YLL[y] + trace.YLD[y])/ pow ((1 + trace.discountrate), static_cast<double>(SimYear));
        trace.TotalDALY += trace.YLL[y] + trace.YLD[y];
        trace.TotalCost += trace.cost[y];
        trace.discCost += trace.cost[y]/pow((1+trace.discountrate),static_cast<double>(SimYear));
        SimYear++;
    }


    for (auto & j : women) {
        trace.calcDwellTime(j);
    }
    women.clear();
    return(trace);
}

Output RunPopulation(string RunsFileName, string CurKey, string OutputFolder, string DataFolder){
    helper help;
    StateMachine Machine;
    Inputs tables(std::move(OutputFolder), std::move(DataFolder));
    tables.loadRFG (RunsFileName, CurKey);
    tables.loadVariables ();
    int BurnInModelYear = tables.StartYear - tables.BurnInYears;
    int TotalSimYears = tables.BurnInYears + tables.SimulationYears;
    int ModelStartAge = tables.ModelStartAge;
    int ModelStopAge = tables.ModelStopAge;
    vector<Woman> women;
    women.reserve(tables.CohortSize);

    for (int j = ModelStartAge; j < ModelStopAge; j++) {
        for (int k = 0; k < tables.burnin[j]; k++) {
            Woman newWoman(j, BurnInModelYear, help, tables.ScreenCoverage);
            women.push_back(newWoman);
        }
    }
    Output trace (tables, TotalSimYears);

    // Start running burn-in period
    for(int y = 0; y < tables.BurnInYears; y++){
        for (auto & k : women) {
            Machine.runPopulationYear (k, tables, trace, true, help, y);
            if (!k.Alive) {
                k.reset(ModelStartAge, BurnInModelYear + 1, help, tables.ScreenCoverage);
            }
        }
        BurnInModelYear++;
    }

    // Now start running simulation from time 0
    int SimYear = 0;
    int CurrentModelYear = tables.StartYear;
    for (int y = tables.BurnInYears; y < TotalSimYears; y++) {
        for (auto &k : women) {
            Machine.runPopulationYear (k, tables, trace, false, help, y);
            if (!k.Alive) {
                k.reset(ModelStartAge, CurrentModelYear + 1, help, tables.ScreenCoverage);
            }
        }
        CurrentModelYear++;
        trace.discDALY += (trace.YLL[y] + trace.YLD[y])/ pow ((1 + trace.discountrate), static_cast<double>(SimYear));
        trace.TotalDALY += trace.YLL[y] + trace.YLD[y];
        trace.TotalCost += trace.cost[y];
        trace.discCost += trace.cost[y]/pow((1+trace.discountrate),static_cast<double>(SimYear));
        SimYear++;
    }

    for (auto & j : women) {
        trace.calcDwellTime(j);
    }

    women.clear();
    return(trace);
}

void RunValidation(Inputs &tables, Output &trace){
    helper help;
    StateMachine Machine;
    tables.loadVariables ();
    int BurnInModelYear = tables.StartYear - tables.BurnInYears;
    int ModelStartAge = tables.ModelStartAge;
    int ModelStopAge = tables.ModelStopAge;
    vector<Woman> women;
    women.reserve(tables.CohortSize);
    for (int j = ModelStartAge; j < ModelStopAge; j++) {
        for (int k = 0; k < tables.burnin[j]; k++) {
            Woman newWoman(j, BurnInModelYear, help, tables.ScreenCoverage);
            women.push_back(newWoman);
        }
    }

    for(int y = 0; y < tables.BurnInYears; y++){
        for (auto & k : women) {
            Machine.runPopulationYear (k, tables, trace, true, help, y);
            if (!k.Alive) {
                k.reset(ModelStartAge, BurnInModelYear + 1, help, tables.ScreenCoverage);
            }
        }
        BurnInModelYear++;
    }
    for (auto & k : women) {
        if(k.CurrentAge >= 15 && k.CurrentAge <= 65){
            if(!k.cancer){
                if((accumulate(k.CIN2LesionTimer.begin(), k.CIN2LesionTimer.end(), 0) +
                    accumulate(k.CIN3LesionTimer.begin(), k.CIN3LesionTimer.end(), 0)) == 0){
                    trace.calcValidation (k);
                }
            }
        }
    }
    women.clear();
}