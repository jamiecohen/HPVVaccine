//
// Created by Jamie Cohen on 11/29/17.
//

#include "outputs.h"

using namespace std;

const string extension = ".txt";

Output::Output(Inputs &Tables, int y) {

    // 2Dmatrices: [age][simyear]

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
    DwellTime_HPV_CIN_31_num = 0;
    DwellTime_HPV_CIN_33_num = 0;
    DwellTime_HPV_CIN_45_num = 0;
    DwellTime_HPV_CIN_52_num = 0;
    DwellTime_HPV_CIN_58_num = 0;
    DwellTime_HPV_CIN_oHR_num = 0;
    DwellTime_CIN_CA_16_num = 0;
    DwellTime_CIN_CA_18_num = 0;
    DwellTime_CIN_CA_31_num = 0;
    DwellTime_CIN_CA_33_num = 0;
    DwellTime_CIN_CA_45_num = 0;
    DwellTime_CIN_CA_52_num = 0;
    DwellTime_CIN_CA_58_num = 0;
    DwellTime_CIN_CA_oHR_num = 0;
    DwellTime_CA_16_denom = 0;
    DwellTime_CA_18_denom = 0;
    DwellTime_CA_31_denom = 0;
    DwellTime_CA_33_denom = 0;
    DwellTime_CA_45_denom = 0;
    DwellTime_CA_52_denom = 0;
    DwellTime_CA_58_denom = 0;
    DwellTime_CA_oHR_denom = 0;
    DwellTime_CA_detected_denom = 0;
    DwellTime_CA_detected_num = 0;
    causalHPV16age = 0;
    causalHPV18age = 0;
    causalHPV31age = 0;
    causalHPV33age = 0;
    causalHPV45age = 0;
    causalHPV52age = 0;
    causalHPV58age = 0;
    causalHPVoHRage = 0;
}

void Output::createTrace(Woman &Data, int y) {
    // No Cancer, HPV16, HPV18, HPV31, HPV33, HPV45, HPV52, HPV58
    
    if(!Data.cancer){
        if(Data.CurrentAge >= 15){
            TotalCancerDenom[Data.CurrentAge][y]++;
        }
        if(!Data.hpv16){
            HPV16denom[Data.CurrentAge][y]++;
        }
        if(!Data.hpv18){
            HPV18denom[Data.CurrentAge][y]++;
        }
        if(Data.HPVinfections.empty()){
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

void Output::writeCohort(std::string *Outdir, int ModelStartAge, int ModelStopAge, int TotalSimYears) {

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
        for(int i = 0; i < TotalSimYears; i++) {
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
    OutputFileName.append("_Mort");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = 15; j < ModelStopAge; j++) {
            output << j << '\t';
        }
        output << endl;
        for(int i = 0; i < TotalSimYears; i++) {
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
        for(int i = 0; i < TotalSimYears; i++) {
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

}

void Output::calcDwellTime(Woman &Data) {

    if(Data.CA16 > 0){
        DwellTime_HPV_CIN_16_num += Data.CIN16;
        DwellTime_CIN_CA_16_num += Data.CA16;
        causalHPV16age += Data.age16;
        DwellTime_CA_16_denom++;
    }

    if(Data.CA18 > 0){
        DwellTime_HPV_CIN_18_num += Data.CIN18;
        DwellTime_CIN_CA_18_num += Data.CA18;
        causalHPV18age += Data.age18;
        DwellTime_CA_18_denom++;
    }

    if(Data.CA31 > 0){
        DwellTime_HPV_CIN_31_num += Data.CIN31;
        DwellTime_CIN_CA_31_num += Data.CA31;
        causalHPV31age += Data.age31;
        DwellTime_CA_31_denom++;
    }

    if(Data.CA33 > 0){
        DwellTime_HPV_CIN_33_num += Data.CIN33;
        DwellTime_CIN_CA_33_num += Data.CA33;
        causalHPV33age += Data.age33;
        DwellTime_CA_33_denom++;
    }

    if(Data.CA45 > 0){
        DwellTime_HPV_CIN_45_num += Data.CIN45;
        DwellTime_CIN_CA_45_num += Data.CA45;
        causalHPV45age += Data.age45;
        DwellTime_CA_45_denom++;
    }

    if(Data.CA52 > 0){
        DwellTime_HPV_CIN_52_num += Data.CIN52;
        DwellTime_CIN_CA_52_num += Data.CA52;
        causalHPV52age += Data.age52;
        DwellTime_CA_52_denom++;
    }

    if(Data.CA58 > 0){
        DwellTime_HPV_CIN_58_num += Data.CIN58;
        DwellTime_CIN_CA_58_num += Data.CA58;
        causalHPV58age += Data.age58;
        DwellTime_CA_58_denom++;
    }

    if(Data.CAoHR > 0){
        DwellTime_HPV_CIN_oHR_num += Data.CINoHR;
        DwellTime_CIN_CA_oHR_num += Data.CAoHR;
        causalHPVoHRage += Data.ageoHR;
        DwellTime_CA_oHR_denom++;
    }
}

void Output::writeDwellTime(std::string *Outdir) {
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
        output << "CA to CAd" << endl;
        output << "HPV16" << '\t';
        output << static_cast<double>(causalHPV16age)/DwellTime_CA_16_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_16_num)/DwellTime_CA_16_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_16_num)/DwellTime_CA_16_denom << '\t';
        output << static_cast<double>(DwellTime_CA_detected_num)/DwellTime_CA_detected_denom << endl;
        output << "HPV18" << '\t';
        output << static_cast<double>(causalHPV18age)/DwellTime_CA_18_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_18_num)/DwellTime_CA_18_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_18_num)/DwellTime_CA_18_denom << endl;
        output << "HPV31" << '\t';
        output << static_cast<double>(causalHPV31age)/DwellTime_CA_31_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_31_num)/DwellTime_CA_31_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_31_num)/DwellTime_CA_31_denom << endl;
        output << "HPV33" << '\t';
        output << static_cast<double>(causalHPV33age)/DwellTime_CA_33_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_33_num)/DwellTime_CA_33_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_33_num)/DwellTime_CA_33_denom << endl;
        output << "HPV45" << '\t';
        output << static_cast<double>(causalHPV45age)/DwellTime_CA_45_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_45_num)/DwellTime_CA_45_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_45_num)/DwellTime_CA_45_denom << endl;
        output << "HPV52" << '\t';
        output << static_cast<double>(causalHPV52age)/DwellTime_CA_52_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_52_num)/DwellTime_CA_52_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_52_num)/DwellTime_CA_52_denom << endl;
        output << "HPV58" << '\t';
        output << static_cast<double>(causalHPV58age)/DwellTime_CA_58_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_58_num)/DwellTime_CA_58_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_58_num)/DwellTime_CA_58_denom << endl;
        output << "HPVoHR" << '\t';
        output << static_cast<double>(causalHPVoHRage)/DwellTime_CA_oHR_denom << '\t';
        output << static_cast<double>(DwellTime_HPV_CIN_oHR_num)/DwellTime_CA_oHR_denom << '\t';
        output << static_cast<double>(DwellTime_CIN_CA_oHR_num)/DwellTime_CA_oHR_denom << endl;
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

Output::~Output(void) = default;