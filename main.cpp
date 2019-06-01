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
#include <future>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


Output RunVaccineCohort(string, string, string, string, bool, double);
void RunCalibration(calibrate &calib, Inputs &tables, int i);
calibrate RunChain(string RunsFileName, string CurKey, string OutputFolder, string DataFolder);
vector<Output> VOI(const string&, string, string, string, int);


int main(int argc, char* argv[]) {

    string DataFolder;
    string OutputFolder;

    if(argc == 1 || argc == 2){
        DataFolder = "/Users/jamiecohen/Dropbox (Personal)/GSAS/HIV-HPV Research/Model Code/HPVVaccine/Data/";
        OutputFolder = "/Users/jamiecohen/Dropbox (Personal)/GSAS/HIV-HPV Research/Model Code/HPVVaccine/Model Output/";
    } else {
        DataFolder = "../Data/";
        OutputFolder = "../Output/";
    }

    unsigned int run;
    string CurKey;
    string RunsFileName(DataFolder);

    if(argc == 1){
        RunsFileName.append("Structure1_test.ini");
    }
    else if(argc > 1){
        RunsFileName.append(argv[1]);
    }

    CIniFile RunsFile(RunsFileName);
    if (!RunsFile.ReadFile()) {
        cout << "Could not read Runs File: " << RunsFileName << endl;
        exit(1);
    }

    CurKey = RunsFile.GetKeyName (0);


    if (RunsFile.GetValue(CurKey, "RunType") == "Calibration"){

        int totaliters = RunsFile.GetValueI(CurKey, "Iterations");
        int n_sims = RunsFile.GetValueI(CurKey, "Simulations");

        vector<future<calibrate>> futures;
        vector<calibrate> modeloutputs;

        for (run = 0; run < totaliters; run++){
            futures.push_back (async(launch::async, RunChain, RunsFileName, CurKey, OutputFolder, DataFolder));
        }

        for (int i = 0; i < futures.size(); i++){
            modeloutputs.push_back (futures[i].get());
        }

        string OutDir = OutputFolder.append("Calibration");
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
        OutputFileName.append("GOF.txt");
        output.open(OutputFileName.c_str (), ios::out);

        if(output) {
            output << "Thread\tIter\tSim\tGOF" << endl;
            for (int i = 0; i < totaliters; i ++){
                for (int j = 0; j < n_sims; j ++){
                    output << argv[3] << '\t';
                    output << i << '\t';
                    output << j << '\t';
                    output << modeloutputs[i].GOF[j] << endl;
                }
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("bestGOF.txt");
        output.open(OutputFileName.c_str (), ios::out);

        if(output) {
            output << "Thread\tIter\tGOF" << endl;
            for (int i = 0; i < totaliters; i ++){
                output << argv[3] << '\t';
                output << i << '\t';
                output << modeloutputs[i].GOF_min << endl;
                output << endl;
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();


        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("params.txt");
        output.open(OutputFileName.c_str (), ios::out);

        if(output) {
            output << "Thread\tIter\tSim\t";
            output << modeloutputs[0].multipliers_names << endl;

            for (int i = 0; i < totaliters; i ++){
                for (int j = 0; j < n_sims; j ++){
                    output << argv[3] << '\t';
                    output << i << '\t';
                    output << j << '\t';
                    for (int k = 0; k < modeloutputs[i].calib_params[j].size(); k ++){
                        output << modeloutputs[i].calib_params[j][k] << '\t';
                    }
                    output << endl;
                }
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
            output << "Thread\tIter\t";
            output << modeloutputs[0].multipliers_names << endl;

            for (int i = 0; i < totaliters; i ++){
                output << argv[3] << '\t';
                output << i << '\t';
                for (int k = 0; k < modeloutputs[i].best_params.size(); k ++){
                    output << modeloutputs[i].best_params[k] << '\t';
                }
                output << endl;
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("output.txt");
        output.open(OutputFileName.c_str (), ios::out);

        if(output) {
            output << "Thread\tIter\tSim\t";
            output << modeloutputs[0].calib_targs_names << endl;
            for (int i = 0; i < totaliters; i ++){
                for (int j = 0; j < n_sims; j ++){
                    output << argv[3] << '\t';
                    output << i << '\t';
                    output << j << '\t';
                    for (int k = 0; k < modeloutputs[i].saved_output[j].size(); k ++){
                        output << modeloutputs[i].saved_output[j][k] << '\t';
                    }
                    output << endl;
                }
            }
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
            output << "Thread\tIter\t";
            output << modeloutputs[0].calib_targs_names << endl;

            for (int i = 0; i < totaliters; i ++){
                output << argv[3] << '\t';
                output << i << '\t';
                for (int k = 0; k < modeloutputs[i].best_output.size(); k ++){
                    output << modeloutputs[i].best_output[k] << '\t';
                }
                output << endl;
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

    }

    else if (RunsFile.GetValue(CurKey, "RunType") == "Cohort") {

        auto tables = new Inputs (OutputFolder, DataFolder);
        tables->loadRFG (RunsFileName, CurKey);
        int ModelStartAge = tables->ModelStartAge;
        int ModelStopAge = tables->ModelStopAge;
        int SimulationYears = tables->SimulationYears;
        delete tables;
        vector<Output> modeloutputs;
        vector<future<Output>> futures;
        vector<string> CurKey;

        for (run = 0; run < RunsFile.GetNumKeys (); run++) {
            CurKey.push_back (RunsFile.GetKeyName (run));
            futures.push_back(async(launch::async, RunVaccineCohort, RunsFileName, CurKey[run], OutputFolder, DataFolder, false, 0));
        }

        for (int i = 0; i < futures.size(); i++){
            modeloutputs.push_back (futures[i].get());
            string OutputDir (OutputFolder);
            OutputDir.append (RunsFile.GetValue (CurKey[i], "OutputDir"));
            const boost::filesystem::path dir (OutputDir);
            boost::filesystem::create_directories (dir);
            modeloutputs[i].writeCohort (&OutputDir, ModelStartAge, ModelStopAge, SimulationYears);
        }
    } else if (RunsFile.GetValue(CurKey, "RunType") == "VOI") {

        vector<vector<Output>> modeloutputs;
        vector<future<vector<Output>>> futures;
        vector<string> CurKey;
        int numruns = 10;

        for (run = 0; run < RunsFile.GetNumKeys (); run++) {
            CurKey.push_back (RunsFile.GetKeyName (run));
            futures.push_back(async(launch::async, VOI, RunsFileName, CurKey[run], OutputFolder, DataFolder, numruns));
        }

        string OutDir (OutputFolder);
        OutDir.append (RunsFile.GetValue (CurKey[0], "OutputDir"));
        const boost::filesystem::path dir (OutDir);
        boost::filesystem::create_directories (dir);

        modeloutputs.reserve(futures.size());
        for (auto & future : futures){
            modeloutputs.push_back (future.get());
        }

        ofstream output;
        string OutputFileName;
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("cost.txt");
        output.open(OutputFileName.c_str (), ios::out);

        if(output) {

            output << "Strategy " << '\t';
            for (int j = 0; j < numruns; j++){
                output << "VOI iter" << j << '\t';
            }

            output << endl;

            for (int i = 0; i < RunsFile.GetNumKeys (); i++){
                output << i << '\t';
                for (int j = 0; j < numruns; j++){
                    output << modeloutputs[i][j].TotalCost;
                    output << '\t';
                }
                output << endl;
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

        OutputFileName.clear();
        OutputFileName.append(OutDir);
        OutputFileName.append("/");
        OutputFileName.append("DALYs.txt");
        output.open(OutputFileName.c_str (), ios::out);

        if(output) {

            output << "Strategy " << '\t';
            for (int j = 0; j < numruns; j++){
                output << "VOI iter" << j << '\t';
            }

            output << endl;

            for (int i = 0; i < RunsFile.GetNumKeys (); i++){
                output << i << '\t';
                for (int j = 0; j < numruns; j++){
                    output << modeloutputs[i][j].discDALY;
                    output << '\t';
                }
                output << endl;
            }
        }
        else
            cerr << "Warning: Unable to open " << OutputFileName << endl;
        output.close();
        output.clear();

    }

    return(0);
}

calibrate RunChain(string RunsFileName, string CurKey, string OutputFolder, string DataFolder) {

    Inputs tables(OutputFolder, DataFolder);
    tables.loadRFG (RunsFileName, CurKey);


    int n_sims = tables.Simulations;
    int n_params = tables.Multipliers.size();
    int n_targs = tables.CalibTargs.size();

    calibrate calib_output (n_sims, n_params, n_targs);

    calib_output.multipliers_names = tables.MultipliersNames;
    calib_output.calib_targs_names = tables.CalibTargsNames;

    for (int i = 0; i < n_targs; i ++){
        calib_output.calib_targs[i] = tables.CalibTargs[i][0];
        calib_output.calib_targs_SD[i] = tables.CalibTargs[i][1];
    }

    for (int i = 0; i < n_params; i++){
        for (int j = 0; j < 4; j++){
            calib_output.multipliers[i][j] = tables.Multipliers[i][j];
        }
    }

    for (int i = 0; i < n_sims; i++){
        RunCalibration(calib_output, tables, i);
    }

    return(calib_output);

}

void RunCalibration(calibrate &calib, Inputs &tables, int i){

    cout << "Running Sim " << i << " on Thread " <<  std::this_thread::get_id() << endl;

    int n_params = tables.Multipliers.size();
    vector<double> calib_params(n_params);
    calib_params = calib.loadCalibData (n_params, i, tables.Tuning_Factor);
    tables.loadCalibParams (calib_params);
    tables.loadVariables ();

    int CurrentModelYear = tables.StartYear;

    std::random_device rdev{};
    std::default_random_engine generator{rdev()};

    uniform_int_distribution<> dis(1, 9);

    vector<Woman> women;
    women.reserve(tables.CohortSize);
    for (int j = 0; j < tables.CohortSize; j++) {
        Woman newWoman(9, CurrentModelYear);
        women.push_back (newWoman);
        women[j].vaccinated = false;
        women[j].completevaccine = false;
        women[j].ScreenAccess = false;
    }

    Output trace_burnin (tables, tables.SimulationYears);

    StateMachine Machine;

    helper help;

    for(int y = 0; y < tables.SimulationYears; y++){

        for (int k = 0; k < tables.CohortSize; k++) {

            Machine.runPopulationYear(women[k], tables, trace_burnin, y, CurrentModelYear, true, help);
        }

        CurrentModelYear++;
    }

    trace_burnin.createInc (tables);

    trace_burnin.createCalibOutput ();

    calib.saved_output[i] = trace_burnin.calib;

    calib.CalculateGOF (i);


    cout << "Finished Sim " << i << " on Thread " <<  std::this_thread::get_id() << endl;

}

Output RunVaccineCohort(string RunsFileName, string CurKey, string OutputFolder, string DataFolder, bool VOI, double VaccineEff){
    helper help;
    StateMachine Machine;
    Inputs tables(std::move(OutputFolder), std::move(DataFolder));
    tables.loadRFG (RunsFileName, CurKey);
    if(VOI){
        tables.VaccineEfficacy = VaccineEff;
    }
    tables.loadVariables ();
    int CurrentModelYear = tables.StartYear;
    vector<Woman> women;
    women.reserve(tables.CohortSize);
    for (int j = 0; j < tables.CohortSize; j++) {
        Woman newWoman(9, CurrentModelYear);
        women.push_back (newWoman);
        double rand = help.getrand();
        women[j].ScreenAccess = rand < tables.ScreenCoverage;
    }
    Output trace (tables, tables.SimulationYears);
    for(int y = 0; y < tables.SimulationYears; y++){
        for (int k = 0; k < tables.CohortSize; k++) {
            Machine.runPopulationYear (women[k], tables, trace, y, CurrentModelYear, false, help);
        }
        CurrentModelYear++;
        trace.discDALY += (trace.YLL[y] + trace.YLD[y])/ pow ((1 + trace.discountrate), static_cast<double>(y));
        trace.discQALY += trace.LE[y]/pow((1+trace.discountrate),static_cast<double>(y));
        trace.TotalCost += trace.cost[y]/pow((1+trace.discountrate),static_cast<double>(y)) ;
    }
    trace.createInc (tables);
    return(trace);
}

vector<Output> VOI(const string& RunsFileName, string CurKey, string OutputFolder, string DataFolder, int runs){
    vector<Output> modeloutputs;

    modeloutputs.reserve(runs);

    helper help;

    double VaccineEff[runs];

    for (int i= 0; i < runs; i++){
        VaccineEff[runs] = help.rbeta (3,1);
        modeloutputs.push_back (RunVaccineCohort (RunsFileName, CurKey, OutputFolder, DataFolder, true, VaccineEff[runs]));
    }

    return(modeloutputs);
}