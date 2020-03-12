//
// Created by Jamie Cohen on 11/29/17.
//

#include "outputs.h"

using namespace std;

const string extension = ".txt";

Output::Output(Inputs &Tables, int y) {

    // 2Dmatrices: [age][simyear]

    DALY.resize (y + 1);
    YLL.resize (y + 1);
    YLD.resize (y + 1);
    cost.resize (y + 1);
    discDALY = 0;
    TotalDALY = 0;
    discountrate = 0.03;
    TotalCost = 0;
    discCost = 0;

    ageoHR = 0;
    age16 = 0;
    age18 = 0;
    age31 = 0;
    age33 = 0;
    age45 = 0;
    age52 = 0;
    age58 = 0;

    trace.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        trace[i].resize(y);
        for (int j = 0; j < y; ++j)
            trace[i][j].resize(7);
    }

    inc.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        inc[i].resize(y);
        for(int j = 0; j < y; j++)
            inc[i][j].resize(5);
    }

    hpvscreens.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        hpvscreens[i].resize (y);
    }
    papscreens.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        papscreens[i].resize (y);
    }
    vaccines.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        vaccines[i].resize (y);
    }

    CaIncStandardized.resize(Tables.ModelStopAge + 1);

    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CaIncStandardized[i].resize (y);
    }

    prev.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        prev[i].resize (y);
    }

    total_alive.resize (Tables.ModelStopAge+1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        total_alive[i].resize (y);
    }
    totaldeadcancer = 0;
    TotalHPV.resize(Tables.ModelStopAge+1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalHPV[i].resize (y);
    }
    totalcancer_mort.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        totalcancer_mort[i].resize (y);
    }
    LE.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        LE[i].resize (y);
    }
    TotalPrevCancer.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalPrevCancer[i].resize (y);
    }
    TotalCancer.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalCancer[i].resize (y);
    }
    TotalDetectedCancer.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalDetectedCancer[i].resize (y);
    }
    TotalDetectedCancer_byyear.resize(y);
    CancerDenom_byyear.resize(y);
    TotalCancer_1618.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalCancer_1618[i].resize (y);
    }
    TotalCancer_nonavalent.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalCancer_nonavalent[i].resize (y);
    }
    TotalCancer_allother.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalCancer_allother[i].resize (y);
    }
    TotalCancerDenom.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        TotalCancerDenom[i].resize (y);
    }
    HPVcount.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        HPVcount[i].resize (y);
    }
    HPV16count.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        HPV16count[i].resize (y);
    }
    HPV18count.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        HPV18count[i].resize (y);
    }
    CIN2count.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CIN2count[i].resize (y);
    }
    CIN3count.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CIN3count[i].resize (y);
    }
    CAcount.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CAcount[i].resize (y);
    }
    DetectedCAcount.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        DetectedCAcount[i].resize (y);
    }
    CAdead.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CAdead[i].resize (y);
    }
    HPVdenom.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        HPVdenom[i].resize (y);
    }
    CINdenom = 0;
    CINnum = 0;

    HPV16denom.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        HPV16denom[i].resize (y);
    }
    HPV18denom.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        HPV18denom[i].resize (y);
    }
    CIN2denom.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CIN2denom[i].resize (y);
    }
    CIN3denom.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CIN3denom[i].resize (y);
    }
    CAdenom.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CAdenom[i].resize (y);
    }
    CIN2HIVneg.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CIN2HIVneg[i].resize (y);
    }
    CIN3HIVneg.resize (Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        CIN3HIVneg[i].resize (y);
    }

    causalHPV16ageMatrix.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        causalHPV16ageMatrix[i].resize (y);
    }
    causalHPV18ageMatrix.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        causalHPV18ageMatrix[i].resize (y);
    }

    causalHPVhi5ageMatrix.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        causalHPVhi5ageMatrix[i].resize (y);
    }
    causalHPVallhrageMatrix.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        causalHPVallhrageMatrix[i].resize (y);
    }

    cancer = 0;
    CA16 = 0;
    CA18 = 0;
    CA31 = 0;
    CA33 = 0;
    CA45 = 0;
    CA52 = 0;
    CA58 = 0;
    CIN316 = 0;
    CIN318 = 0;
    CIN331 = 0;
    CIN333 = 0;
    CIN345 = 0;
    CIN352 = 0;
    CIN358 = 0;
    CIN3LR = 0;
    CIN216 = 0;
    CIN218 = 0;
    CIN231 = 0;
    CIN233 = 0;
    CIN245 = 0;
    CIN252 = 0;
    CIN258 = 0;
    CIN2LR = 0;
    CAotherHR = 0;
    CIN2otherHR = 0;
    CIN3otherHR = 0;
    CIN2total = 0;
    CIN3total = 0;
    DwellTime_HPV_CIN_16_num = 0;
    DwellTime_HPV_CIN_18_num = 0;
    DwellTime_HPV_CIN_hi5_num = 0;
    DwellTime_HPV_CIN_allhr_num = 0;
    DwellTime_CIN_CA_16_num = 0;
    DwellTime_CIN_CA_18_num = 0;
    DwellTime_CIN_CA_hi5_num = 0;
    DwellTime_CIN_CA_allhr_num = 0;
    DwellTime_CA_16_denom = 0;
    DwellTime_CA_18_denom = 0;
    DwellTime_CA_hi5_denom = 0;
    DwellTime_CA_allhr_denom = 0;
    DwellTime_CA_16_latent_denom = 0;
    DwellTime_CA_18_latent_denom = 0;
    DwellTime_CA_hi5_latent_denom = 0;
    DwellTime_CA_allhr_latent_denom = 0;
    DwellTime_CA_detected_denom = 0;
    DwellTime_CA_detected_num = 0;
    Dormancy_HPV_CIN_16_num = 0;
    Dormancy_HPV_CIN_18_num = 0;
    Dormancy_HPV_CIN_hi5_num = 0;
    Dormancy_HPV_CIN_allhr_num = 0;

    Latency_HPV_CIN_16_num = 0;
    Latency_HPV_CIN_18_num = 0;
    Latency_HPV_CIN_hi5_num = 0;
    Latency_HPV_CIN_allhr_num = 0;
    
    causalHPV16age = 0;
    causalHPV18age = 0;
    causalHPVhi5age = 0;
    causalHPVallhrage = 0;
}

void Output::createTrace(Woman &Data, int y) {
    // No Cancer, allhr, HPV16, HPV18, HPVhi5, HPVoHR, HPVLR, CIN+
    
    if(!Data.cancer){
        if(Data.CurrentAge >= 15){
            TotalCancerDenom[Data.CurrentAge][y]++;
            CancerDenom_byyear[y]++;
        }
        if(!Data.hpv16){
            HPV16denom[Data.CurrentAge][y]++;
        }
        if(!Data.hpv18){
            HPV18denom[Data.CurrentAge][y]++;
        }

        if(accumulate(Data.HPVinfectionTimer.begin(), Data.HPVinfectionTimer.end(), 0) == 0){
            HPVdenom[Data.CurrentAge][y]++;
        }
        trace[Data.CurrentAge][y][0]++; // no cancer (prev DENOM)
        CAdenom[Data.CurrentAge][y]++;
        if (Data.hpv16 || Data.hpv18 || Data.hpv31 || Data.hpv33 ||Data.hpv45 || Data.hpv52 || Data.hpv58 || Data.hpvotherHR){
            trace[Data.CurrentAge][y][1]++; // all prevalent hr-HPV
            if(Data.hpv16){
                trace[Data.CurrentAge][y][2]++; // all prevalent HPV16
            }
            if(Data.hpv18){
                trace[Data.CurrentAge][y][3]++; // all prevalent HPV18
            }
            if(Data.hpv31 || Data.hpv33 ||Data.hpv45 || Data.hpv52 || Data.hpv58){
                trace[Data.CurrentAge][y][4]++; // all prevalent high-5
            }
            if(Data.hpvotherHR){
                trace[Data.CurrentAge][y][5]++; // all prevalent HPVotherHR
            }
        }

        if(Data.hpvlo){
            trace[Data.CurrentAge][y][6]++; // all prevalent HPVLR
        }

    }
}

void Output::createTypeDist(Woman &Data) {
    if (!Data.CIN2Lesions.empty()){
        CIN2total++;
        if(Data.hpv16){
            CIN216++;
        }
        if(Data.hpv18){
            CIN218++;
        }
        if(Data.hpv31){
            CIN231++;
        }
        if(Data.hpv33){
            CIN233++;
        }
        if(Data.hpv45){
            CIN245++;
        }
        if(Data.hpv52){
            CIN252++;
        }
        if(Data.hpv58){
            CIN258++;
        }
        if(Data.hpvotherHR){
            CIN2otherHR++;
        }
        if(Data.hpvlo){
            CIN2LR++;
        }
    }
    if (!Data.CIN3Lesions.empty()){
        CIN3total++;
        if(Data.hpv16){
            CIN316++;
        }
        if(Data.hpv18){
            CIN318++;
        }
        if(Data.hpv31){
            CIN331++;
        }
        if(Data.hpv33){
            CIN333++;
        }
        if(Data.hpv45){
            CIN345++;
        }
        if(Data.hpv52){
            CIN352++;
        }
        if(Data.hpv58){
            CIN358++;
        }
        if(Data.hpvotherHR){
            CIN3otherHR++;
        }
        if(Data.hpvlo){
            CIN3LR++;
        }
    }
    
}

void Output::createCalibOutput(int y) {

    int HPVcalibnum;
    int HPVcalibdenom;

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 17; i < 20; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 20; i < 25; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 25; i < 30; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 30; i < 35; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 35; i < 40; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 40; i < 45; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 45; i < 50; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 50; i < 55; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 55; i < 65; i++){
        HPVcalibnum += trace[i][y][1];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 16; i < 23; i++){
        HPVcalibnum += trace[i][y][2];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 16; i < 23; i++){
        HPVcalibnum += trace[i][y][3];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 16; i < 23; i++){
        HPVcalibnum += trace[i][y][4];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 16; i < 23; i++){
        HPVcalibnum += trace[i][y][5];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    HPVcalibnum = 0;
    HPVcalibdenom = 0;
    for(int i = 16; i < 23; i++){
        HPVcalibnum += trace[i][y][6];
        HPVcalibdenom += trace[i][y][0];
    }
    calib.push_back (static_cast<double>(HPVcalibnum)/HPVcalibdenom);

    calib.push_back(static_cast<double>(CIN216) / CIN2total );
    calib.push_back(static_cast<double>(CIN218) / CIN2total );
    calib.push_back(static_cast<double>(CIN231 + CIN233 + CIN245 + CIN252 + CIN258) / CIN2total);
    calib.push_back(static_cast<double>(CIN2LR) / CIN2total );
    calib.push_back(static_cast<double>(CIN316) / CIN3total );
    calib.push_back(static_cast<double>(CIN318) / CIN3total );
    calib.push_back(static_cast<double>(CIN331 + CIN333 + CIN345 + CIN352 + CIN358) / CIN3total);
    calib.push_back(static_cast<double>(CIN3LR) / CIN3total );
    calib.push_back(static_cast<double>(CA16) / cancer );
    calib.push_back(static_cast<double>(CA18) / cancer );
    calib.push_back(static_cast<double>(CA31 + CA33 + CA45 + CA52 + CA58) / cancer );

    int CAnew;
    int CAdenom;

    CAnew = 0;
    CAdenom = 0;
    for(int i = 15; i < 20; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 20; i < 25; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 25; i < 30; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 30; i < 35; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 35; i < 40; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 40; i < 45; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 45; i < 50; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 50; i < 55; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 55; i < 60; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 60; i < 65; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 65; i < 70; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for(int i = 70; i < 75; i++){
        CAnew += DetectedCAcount[i][y];
        CAdenom += TotalCancerDenom[i][y];
    }
    calib.push_back (100000*static_cast<double>(CAnew)/CAdenom);

}

void Output::writeCalibOutput(std::string *Outdir, std::string calib_targs_names) {

    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_calib");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output) {
        output << calib_targs_names << endl;
        for (int k = 0; k < calib.size(); k ++){
            output << calib[k] << '\t';
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

void Output::writeCEA(std::string *Outdir, int ModelStopAge, int TotalSimYears) {
    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_costbenefit");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << " \tCost\tDALYs" << endl;
        output << "Undiscounted" << '\t';
        output << TotalCost << '\t';
        output << TotalDALY << endl;
        output << "Discounted" << '\t';
        output << discCost << '\t';
        output << discDALY << endl;
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_totalalive");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 0; j < ModelStopAge; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 0; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 0; j < ModelStopAge; j++) {
                output << total_alive[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();
}

void Output::writeInc(std::string *Outdir, int ModelStartAge, int ModelStopAge, int TotalSimYears) {
    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_CAInc");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 15; j < ModelStopAge; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 100; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 15; j < ModelStopAge; j++) {
                output << 100000*static_cast<double>(TotalDetectedCancer[j][i])/TotalCancerDenom[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_CAInc_byyear");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        for(int j = 100; j < TotalSimYears; j++) {
            output << "SimYear" << j << '\t';
            output << 100000*static_cast<double>(TotalDetectedCancer_byyear[j])/CancerDenom_byyear[j] << '\t';
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_HPVInc");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = ModelStartAge; j < ModelStopAge; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 100; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 15; j < ModelStopAge; j++) {
                output << static_cast<double>(HPVcount[j][i])/HPVdenom[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
}

void Output::writeMort(std::string *Outdir, int ModelStopAge, int TotalSimYears) {

    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Mort");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 15; j < ModelStopAge; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 100; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 15; j < ModelStopAge; j++) {
                output << 100000 * static_cast<double>(CAdead[j][i]) / total_alive[j][i] << '\t';
            }
            output << endl;
        }

    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

void Output::calcDwellTime(Woman &Data) {

    if(Data.CA16 > 0){
        DwellTime_HPV_CIN_16_num += Data.CIN16;
        DwellTime_CIN_CA_16_num += Data.CA16;
        Dormancy_HPV_CIN_16_num += Data.CIN_dormant_16;
        Latency_HPV_CIN_16_num += Data.CIN_latent_16;
        age16 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High16] + Data.DormancyTimer[Woman::High16] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);

        causalHPV16age += age16;
        causalHPV16ageMatrix[age16][Data.year16]++;
        if(Data.CIN_latent_16 > 0){
            DwellTime_CA_16_latent_denom++;
        }
        DwellTime_CA_16_denom++;

        Latency_HPV_CIN_allhr_num += Data.CIN_latent_16;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_16;
        DwellTime_HPV_CIN_allhr_num += Data.CIN16;
        DwellTime_CIN_CA_allhr_num += Data.CA16;
        causalHPVallhrage += age16;
        causalHPVallhrageMatrix[age16][Data.year16]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_16 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CA18 > 0){
        DwellTime_HPV_CIN_18_num += Data.CIN18;
        DwellTime_CIN_CA_18_num += Data.CA18;
        Dormancy_HPV_CIN_18_num += Data.CIN_dormant_18;
        Latency_HPV_CIN_18_num += Data.CIN_latent_18;
        age18 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High18] + Data.DormancyTimer[Woman::High18] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);

        causalHPV18age += age18;
        causalHPV18ageMatrix[age18][Data.year18]++;
        DwellTime_CA_18_denom++;
        if(Data.CIN_latent_18 > 0){
            DwellTime_CA_18_latent_denom++;
        }

        Latency_HPV_CIN_allhr_num += Data.CIN_latent_18;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_18;
        DwellTime_HPV_CIN_allhr_num += Data.CIN18;
        DwellTime_CIN_CA_allhr_num += Data.CA18;
        causalHPVallhrage += age18;
        causalHPVallhrageMatrix[age18][Data.year18]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_18 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CA31 > 0){
        DwellTime_HPV_CIN_hi5_num += Data.CIN31;
        DwellTime_CIN_CA_hi5_num += Data.CA31;
        Dormancy_HPV_CIN_hi5_num += Data.CIN_dormant_31;
        Latency_HPV_CIN_hi5_num += Data.CIN_latent_31;
        age31 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High31] + Data.DormancyTimer[Woman::High31] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);

        causalHPVhi5age += age31;
        causalHPVhi5ageMatrix[age31][Data.year31]++;
        DwellTime_CA_hi5_denom++;
        if(Data.CIN_latent_31 > 0){
            DwellTime_CA_hi5_latent_denom++;
        }

        Latency_HPV_CIN_allhr_num += Data.CIN_latent_31;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_31;
        DwellTime_HPV_CIN_allhr_num += Data.CIN31;
        DwellTime_CIN_CA_allhr_num += Data.CA31;
        causalHPVallhrage += age31;
        causalHPVallhrageMatrix[age31][Data.year31]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_31 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CA33 > 0){
        DwellTime_HPV_CIN_hi5_num += Data.CIN33;
        DwellTime_CIN_CA_hi5_num += Data.CA33;
        Dormancy_HPV_CIN_hi5_num += Data.CIN_dormant_33;
        Latency_HPV_CIN_hi5_num += Data.CIN_latent_33;
        age33 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High33] + Data.DormancyTimer[Woman::High33] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);

        causalHPVhi5age += age33;
        causalHPVhi5ageMatrix[age33][Data.year33]++;
        DwellTime_CA_hi5_denom++;
        if(Data.CIN_latent_33 > 0){
            DwellTime_CA_hi5_latent_denom++;
        }

        Latency_HPV_CIN_allhr_num += Data.CIN_latent_33;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_33;
        DwellTime_HPV_CIN_allhr_num += Data.CIN33;
        DwellTime_CIN_CA_allhr_num += Data.CA33;
        causalHPVallhrage += age33;
        causalHPVallhrageMatrix[age33][Data.year33]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_33 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CA45 > 0){
        DwellTime_HPV_CIN_hi5_num += Data.CIN45;
        DwellTime_CIN_CA_hi5_num += Data.CA45;
        Latency_HPV_CIN_hi5_num += Data.CIN_latent_45;
        Dormancy_HPV_CIN_hi5_num += Data.CIN_dormant_45;
        age45 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High45] + Data.DormancyTimer[Woman::High45] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);

        causalHPVhi5age += age45;
        causalHPVhi5ageMatrix[age45][Data.year45]++;
        DwellTime_CA_hi5_denom++;
        if(Data.CIN_latent_45 > 0){
            DwellTime_CA_hi5_latent_denom++;
        }

        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_45;
        Latency_HPV_CIN_allhr_num += Data.CIN_latent_45;
        DwellTime_HPV_CIN_allhr_num += Data.CIN45;
        DwellTime_CIN_CA_allhr_num += Data.CA45;
        causalHPVallhrage += age45;
        causalHPVallhrageMatrix[age45][Data.year45]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_45 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CA52 > 0){
        DwellTime_HPV_CIN_hi5_num += Data.CIN52;
        DwellTime_CIN_CA_hi5_num += Data.CA52;
        Latency_HPV_CIN_hi5_num += Data.CIN_latent_52;
        Dormancy_HPV_CIN_hi5_num += Data.CIN_dormant_52;
        age52 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High52] + Data.DormancyTimer[Woman::High52] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);

        causalHPVhi5age += age52;
        causalHPVhi5ageMatrix[age52][Data.year52]++;
        DwellTime_CA_hi5_denom++;
        if(Data.CIN_latent_52 > 0){
            DwellTime_CA_hi5_latent_denom++;
        }

        Latency_HPV_CIN_allhr_num += Data.CIN_latent_52;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_52;
        DwellTime_HPV_CIN_allhr_num += Data.CIN52;
        DwellTime_CIN_CA_allhr_num += Data.CA52;
        causalHPVallhrage += age52;
        causalHPVallhrageMatrix[age52][Data.year52]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_52 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CA58 > 0){
        DwellTime_HPV_CIN_hi5_num += Data.CIN58;
        DwellTime_CIN_CA_hi5_num += Data.CA58;
        Latency_HPV_CIN_hi5_num += Data.CIN_latent_58;
        Dormancy_HPV_CIN_hi5_num += Data.CIN_dormant_58;
        age58 = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::High58] + Data.DormancyTimer[Woman::High58] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);
        causalHPVhi5age += age58;
        causalHPVhi5ageMatrix[age58][Data.year58]++;
        DwellTime_CA_hi5_denom++;
        if(Data.CIN_latent_58 > 0){
            DwellTime_CA_hi5_latent_denom++;
        }

        DwellTime_HPV_CIN_allhr_num += Data.CIN58;
        Latency_HPV_CIN_allhr_num += Data.CIN_latent_58;
        DwellTime_CIN_CA_allhr_num += Data.CA58;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_58;
        causalHPVallhrage += age58;
        causalHPVallhrageMatrix[age58][Data.year58]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_58 > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }

    if(Data.CAoHR > 0){
        DwellTime_HPV_CIN_allhr_num += Data.CINoHR;
        Latency_HPV_CIN_allhr_num += Data.CIN_latent_oHR;
        DwellTime_CIN_CA_allhr_num += Data.CAoHR;
        Dormancy_HPV_CIN_allhr_num += Data.CIN_dormant_oHR;
        ageoHR = Data.CurrentAge - (Data.HPVinfectionTimer[Woman::otherHR] + Data.DormancyTimer[Woman::otherHR] +
                Data.ca1Timer + Data.ca2Timer + Data.ca3Timer);
        causalHPVallhrage += ageoHR;
        causalHPVallhrageMatrix[ageoHR][Data.yearoHR]++;
        DwellTime_CA_allhr_denom++;
        if(Data.CIN_latent_oHR > 0){
            DwellTime_CA_allhr_latent_denom++;
        }
    }
}

void Output::writeDwellTime(std::string *Outdir, int TotalSimYears) {
    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Dwelltime");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);
    if(output){
        output << "" << '\t';
        output << "Age Causal Infection" << '\t';
        output << "HPV to CIN" << '\t';
        output << "CIN to CA" << '\t';
        output << "CA to CAd" << '\t';
        output << "Dormancy Time" << '\t';
        output << "Latency Time" << '\t';
        output << "Prop Re-Infect" << endl;
        output << "HPV16" << '\t';
        output << static_cast<double>(causalHPV16age)/DwellTime_CA_16_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_16_num)/DwellTime_CA_16_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_16_num)/DwellTime_CA_16_denom << '\t';
        output << static_cast<double>(DwellTime_CA_detected_num)/DwellTime_CA_detected_denom << '\t';
        output << static_cast<double>(Dormancy_HPV_CIN_16_num)/DwellTime_CA_16_latent_denom << '\t';
        output << static_cast<double>(Latency_HPV_CIN_16_num)/DwellTime_CA_16_latent_denom << '\t';
        output << static_cast<double>(DwellTime_CA_16_latent_denom)/DwellTime_CA_16_denom << endl;
        output << "HPV18" << '\t';
        output << static_cast<double>(causalHPV18age)/DwellTime_CA_18_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_18_num)/DwellTime_CA_18_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_18_num)/DwellTime_CA_18_denom << '\t';
        output << static_cast<double>(DwellTime_CA_detected_num)/DwellTime_CA_detected_denom << '\t';
        output << static_cast<double>(Dormancy_HPV_CIN_18_num)/DwellTime_CA_18_latent_denom << '\t';
        output << static_cast<double>(Latency_HPV_CIN_18_num)/DwellTime_CA_18_latent_denom << '\t';
        output << static_cast<double>(DwellTime_CA_18_latent_denom)/DwellTime_CA_18_denom << endl;
        output << "HPVhi5" << '\t';
        output << static_cast<double>(causalHPVhi5age)/DwellTime_CA_hi5_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_hi5_num)/DwellTime_CA_hi5_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_hi5_num)/DwellTime_CA_hi5_denom << '\t';
        output << static_cast<double>(DwellTime_CA_detected_num)/DwellTime_CA_detected_denom << '\t';
        output << static_cast<double>(Dormancy_HPV_CIN_hi5_num)/DwellTime_CA_hi5_latent_denom << '\t';
        output << static_cast<double>(Latency_HPV_CIN_hi5_num)/DwellTime_CA_hi5_latent_denom << '\t';
        output << static_cast<double>(DwellTime_CA_hi5_latent_denom)/DwellTime_CA_hi5_denom << endl;
        output << "hrHPV" << '\t';
        output << static_cast<double>(causalHPVallhrage)/DwellTime_CA_allhr_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_allhr_num)/DwellTime_CA_allhr_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_allhr_num)/DwellTime_CA_allhr_denom << '\t';
        output << static_cast<double>(DwellTime_CA_detected_num)/DwellTime_CA_detected_denom << '\t';
        output << static_cast<double>(Dormancy_HPV_CIN_allhr_num)/DwellTime_CA_allhr_denom << '\t';
        output << static_cast<double>(Latency_HPV_CIN_allhr_num)/DwellTime_CA_allhr_denom << '\t';
        output << static_cast<double>(DwellTime_CA_allhr_latent_denom)/DwellTime_CA_allhr_denom << endl;

    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Dwelltime_Cum16");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 9; j < 100; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 0; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 9; j < 100; j++) {
                output << causalHPV16ageMatrix[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Dwelltime_Cum18");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 9; j < 100; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 0; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 9; j < 100; j++) {
                output << causalHPV18ageMatrix[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Dwelltime_Cumhi5");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 9; j < 100; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 0; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 9; j < 100; j++) {
                output << causalHPVhi5ageMatrix[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

    OutputFileName.clear();
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Dwelltime_Cumallhr");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 9; j < 100; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 0; i < TotalSimYears; i++) {
            output << "SimYear" << i << '\t';
            for(int j = 9; j < 100; j++) {
                output << causalHPVallhrageMatrix[j][i] << '\t';
            }
            output << endl;
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

void Output::calcLE(Woman &Data, Inputs &Tables, int y) {
    if (Data.Alive) {
        if (Data.cancer) {
            switch(Data.cancerstage){
                case Woman::Stage0:break;
                case Woman::Stage1:
                    YLD[y] += Tables.disabilityCA1;
                    break;
                case Woman::Stage2:
                    YLD[y] += Tables.disabilityCA2;
                    break;
                case Woman::Stage3:
                    YLD[y] += Tables.disabilityCA3;
                    break;
                case Woman::Stage1d:
                    YLD[y] += Tables.disabilityCA1;
                    break;
                case Woman::Stage2d:
                    YLD[y] += Tables.disabilityCA2;
                    break;
                case Woman::Stage3d:
                    YLD[y] += Tables.disabilityCA3;
                    break;
            }
        }
    } else {
        YLL[y] += Tables.LifeExpectancy[Data.CurrentAge][0];
    }
}

void Output::calcValidation(Woman &Data) {
    if((accumulate(Data.CIN2LesionTimer.begin(), Data.CIN2LesionTimer.end(), 0) +
        accumulate(Data.CIN3LesionTimer.begin(), Data.CIN3LesionTimer.end(), 0)) == 0){
        CINdenom++; // no CIN (prev DENOM)
    } else {
        CINnum++; // all prevalent CIN
    }
}

void Output::writeValidation(std::string *Outdir) {

    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Validation");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output) {
        output << static_cast<double>(CINnum) / CINdenom << endl;
    } else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

Output::~Output(void) = default;