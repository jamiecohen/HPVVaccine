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
#include <random>
#include "calibrate.h"
#include <thread>

using namespace std;

Output RunVaccineCohort(string, string, string, string);
void RunCalibration(calibrate &calib, Inputs &tables, int i);

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
        RunsFileName.append("screentest.ini");
        FileName = "test.ini";
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
        if(argc >= 4){
            cout << "Chain number " << argv[3] << endl;
        }
        Inputs tables(OutputFolder, DataFolder);
        tables.loadRFG (RunsFileName, RunType);
        int n_sims = tables.Simulations;
        int n_params = tables.Multipliers.size();
        int n_targs = tables.CalibTargs.size();
        calibrate calib (n_sims, n_params, n_targs);
        calib.multipliers_names = tables.MultipliersNames;
        calib.calib_targs_names = tables.CalibTargsNames;
        for (int i = 0; i < n_targs; i ++){
            calib.calib_targs[i] = tables.CalibTargs[i][0];
            calib.calib_targs_SD[i] = tables.CalibTargs[i][1];
        }
        for (int i = 0; i < n_params; i++){
            for (int j = 0; j < 4; j++){
                calib.multipliers[i][j] = tables.Multipliers[i][j];
            }
        }
        for (int i = 0; i < n_sims; i++){
            RunCalibration (calib, tables, i);
        }
        string OutDir = OutputFolder.append("HPVVaccine_Calib");
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
        int StartYear = tables.StartYear;
        vector<Output> modeloutputs;
        modeloutputs.reserve(numruns);
        vector<string> CurKey;
        CurKey.reserve(numruns);

        for (run = 0; run < RunsFile.GetNumKeys (); run++) {
            cout << "Running Strat " << run << endl;
            CurKey.push_back (RunsFile.GetKeyName (run));
            modeloutputs.push_back(RunVaccineCohort (RunsFileName, CurKey[run], OutputFolder, DataFolder));
        }
        for (int i = 0; i < modeloutputs.size(); i++){
            string OutputDir (OutputFolder);
            OutputDir.append (RunsFile.GetValue (CurKey[i], "OutputDir"));
            const boost::filesystem::path dir (OutputDir);
            boost::filesystem::create_directories (dir);
            modeloutputs[i].writeCohort (&OutputDir, ModelStartAge, ModelStopAge, StartYear, SimulationYears);
            modeloutputs[i].writeDwellTime (&OutputDir);
        }
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
    vector<Woman> women;
    women.reserve (tables.CohortSize);
    helper help;
    double rand;
    for (int j = 0; j < tables.CohortSize; j++) {
        rand = help.getrand();
        Woman newWoman (tables.ModelStartAge, CurrentModelYear, rand);
        women.push_back (newWoman);
    }
    Output trace_burnin (tables, tables.SimulationYears);
    StateMachine Machine;

    for (int y = 0; y < tables.SimulationYears; y++) {
        for (int k = 0; k < tables.CohortSize; k++) {
            Machine.runPopulationYear (women[k], tables, trace_burnin, y, CurrentModelYear, true, help);
        }
        CurrentModelYear++;
    }
    trace_burnin.createInc (tables);
    trace_burnin.createCalibOutput ();
    calib.saved_output[i] = trace_burnin.calib;
    rand = help.getrand ();
    calib.CalculateGOF (i, tables.Tuning_Factor, rand);
    women.clear();
}

Output RunVaccineCohort(string RunsFileName, string CurKey, string OutputFolder, string DataFolder){
    helper help;
    StateMachine Machine;
    Inputs tables(std::move(OutputFolder), std::move(DataFolder));
    tables.loadRFG (RunsFileName, CurKey);
    tables.loadVariables ();
    int CurrentModelYear = tables.StartYear;
    vector<Woman> women;
    women.reserve(tables.CohortSize);
    for (int j = 0; j < tables.CohortSize; j++) {
        Woman newWoman(tables.ModelStartAge, CurrentModelYear, help, tables.ScreenCoverage, tables.VaccineStartAge,
                       tables.ScreenDist, tables.ColpoAvail, tables.VaccineCoverage);
        women.push_back (newWoman);
    }
    Output trace (tables, tables.SimulationYears);
    int SimYear = 0;
    for(int y = 0; y < tables.SimulationYears; y++){
        for (int k = 0; k < tables.CohortSize; k++) {
            Machine.runPopulationYear (women[k], tables, trace, y, CurrentModelYear, false, help);
        }
        CurrentModelYear++;
        trace.discDALY += (trace.YLL[y] + trace.YLD[y])/ pow ((1 + trace.discountrate), static_cast<double>(SimYear));
        trace.discQALY += trace.LE[y]/pow((1+trace.discountrate),static_cast<double>(SimYear));
        trace.TotalCost += trace.cost[y]/pow((1+trace.discountrate),static_cast<double>(SimYear));
        SimYear++;
    }
    trace.createInc (tables);
    trace.createCalibOutput ();
    for (int j = 0; j < tables.CohortSize; j++) {
        trace.calcDwellTime(women[j]);
    }
    women.clear();
    return(trace);
}