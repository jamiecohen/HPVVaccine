//
// Created by Jamie Cohen on 11/29/17.
//

#include "outputs.h"

using namespace std;

const string extension = ".txt";

Output::Output(Inputs &Tables, int y) {

    hpvscreens.resize(y + 1);
    papscreens.resize(y + 1);
    vaccines.resize(y+1);
    CaIncStandardized.resize(Tables.ModelStopAge + 1);
    trace.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        trace[i].resize(6);
    }
    prev.resize(Tables.ModelStopAge + 1);
    inc.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        inc[i].resize(5);
    }
    total_alive.resize (Tables.ModelStopAge+1);
    totaldeadcancer = 0;
    TotalHPV.resize(y+1);
    totalcancer_mort.resize (Tables.ModelStopAge + 1);
    LE.resize (y + 1);
    TotalPrevCancer.resize(Tables.ModelStopAge + 1);
    TotalCancer.resize(Tables.ModelStopAge + 1);
    TotalDetectedCancer.resize(Tables.ModelStopAge + 1);
    TotalCancer_1618.resize(Tables.ModelStopAge + 1);
    TotalCancer_nonavalent.resize (Tables.ModelStopAge + 1);
    TotalCancer_allother.resize(Tables.ModelStopAge + 1);
    TotalCancerDenom.resize(Tables.ModelStopAge + 1);
    HPVcount.resize (Tables.ModelStopAge + 1);
    HPV16count.resize (Tables.ModelStopAge + 1);
    HPV18count.resize (Tables.ModelStopAge + 1);
    CIN2count.resize (Tables.ModelStopAge + 1);
    CIN3count.resize (Tables.ModelStopAge + 1);
    CAcount.resize (Tables.ModelStopAge + 1);
    DetectedCAcount.resize (Tables.ModelStopAge + 1);
    CAdead.resize (Tables.ModelStopAge + 1);
    HPVdenom.resize (Tables.ModelStopAge + 1);
    HPV16denom.resize (Tables.ModelStopAge + 1);
    HPV18denom.resize (Tables.ModelStopAge + 1);
    CIN2denom.resize (Tables.ModelStopAge + 1);
    CIN3denom.resize (Tables.ModelStopAge + 1);
    CAdenom.resize (Tables.ModelStopAge + 1);
    CIN2HIVneg.resize (Tables.ModelStopAge + 1);
    CIN3HIVneg.resize (Tables.ModelStopAge + 1);
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
    CIN216 = 0;
    CIN218 = 0;
    CIN231 = 0;
    CIN233 = 0;
    CIN245 = 0;
    CIN252 = 0;
    CIN258 = 0;
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

void Output::createTrace(Woman &Data) {
    
    if(!Data.cancer){
        if(Data.CurrentAge >= 15){
            TotalCancerDenom[Data.CurrentAge]++;
        }
        if(!Data.hpv16){
            HPV16denom[Data.CurrentAge]++;
        }
        if(!Data.hpv18){
            HPV18denom[Data.CurrentAge]++;
        }
        if(Data.HPVinfections.empty()){
            HPVdenom[Data.CurrentAge]++;
        }
        trace[Data.CurrentAge][3]++; // HIVneg, no cancer (prev DENOM)
        CAdenom[Data.CurrentAge]++;
        if (Data.hpv16 || Data.hpv18 || Data.hpv31 || Data.hpv33 || Data.hpv45 || Data.hpv52 || Data.hpv58 || Data.hpvotherHR) {
            trace[Data.CurrentAge][4]++; // all prevalent HIVpos hr-HPV
            if(!Data.CIN2Lesions.empty () || !Data.CIN3Lesions.empty ()){
                trace[Data.CurrentAge][5]++; // all prevalent CIN2+
            }
        }
    }
}

void Output::createCalibOutput() {

    int HPVHIVneg = 0;
    int HIVneg = 0;
    for(int i = 17; i < 25; i++){
        HPVHIVneg += trace[i][4];
        HIVneg += trace[i][3];
    }
    calib.push_back (static_cast<double>(HPVHIVneg)/HIVneg);

    for(int j = 0; j <8; j++){
        HPVHIVneg = 0;
        HIVneg = 0;
        for(int i = 25 + 5*j; i < 30 + 5*j; i++){
            HPVHIVneg += trace[i][4];
            HIVneg += trace[i][3];
        }
        calib.push_back (static_cast<double>(HPVHIVneg)/HIVneg);
    }

    calib.push_back(static_cast<double>(CIN216) / CIN2total );
    calib.push_back(static_cast<double>(CIN218) / CIN2total );
    calib.push_back(static_cast<double>(CIN231) / CIN2total );
    calib.push_back(static_cast<double>(CIN233) / CIN2total );
    calib.push_back(static_cast<double>(CIN245) / CIN2total );
    calib.push_back(static_cast<double>(CIN252) / CIN2total );
    calib.push_back(static_cast<double>(CIN258) / CIN2total );
    calib.push_back(static_cast<double>(CIN2otherHR) / CIN2total );

    calib.push_back(static_cast<double>(CIN316) / CIN3total );
    calib.push_back(static_cast<double>(CIN318) / CIN3total );
    calib.push_back(static_cast<double>(CIN331) / CIN3total );
    calib.push_back(static_cast<double>(CIN333) / CIN3total );
    calib.push_back(static_cast<double>(CIN345) / CIN3total );
    calib.push_back(static_cast<double>(CIN352) / CIN3total );
    calib.push_back(static_cast<double>(CIN358) / CIN3total );
    calib.push_back(static_cast<double>(CIN3otherHR) / CIN3total );

    calib.push_back(static_cast<double>(CA16) / cancer );
    calib.push_back(static_cast<double>(CA18) / cancer );
    calib.push_back(static_cast<double>(CA31) / cancer );
    calib.push_back(static_cast<double>(CA33) / cancer );
    calib.push_back(static_cast<double>(CA45) / cancer );
    calib.push_back(static_cast<double>(CA52) / cancer );
    calib.push_back(static_cast<double>(CA58) / cancer );
    calib.push_back(static_cast<double>(CAotherHR) / cancer );

    /*for (int j = 0; j < 12; j++){
        int CAinc = 0;
        int CAtotal = 0;
        for (int i = 15 + 5*j; i < 20 + 5*j; i++){
            CAinc += DetectedCAcount[i];
            CAtotal += CAdenom[i];
        }
        calib.push_back (100000* static_cast<double>(CAinc)/CAtotal);
    }*/
}

void Output::writeCalibOutput(std::string *Outdir) {

    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_calib");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output) {
        for (int k = 0; k < calib.size(); k ++){
            output << calib[k] << '\t';
        }
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

void Output::writeCohort(std::string *Outdir, int ModelStartAge, int ModelStopAge, int SimStartYear, int SimYears) {

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
        output << "TotalCA" << '\t';
        for(int j = 15; j < ModelStopAge; j++) {
            output << 100000*static_cast<double>(TotalCancer[j])/TotalCancerDenom[j] << '\t';
        }
        output << endl;
        output << "TotalDetectedCA" << '\t';
        for(int j = 15; j < ModelStopAge; j++) {
            output << 100000*static_cast<double>(TotalDetectedCancer[j])/TotalCancerDenom[j] << '\t';
        }
        output << endl;

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
        output << "TotalCAmort" << '\t';
        for(int j = 15; j < ModelStopAge; j++) {
            output << 100000*static_cast<double>(CAdead[j] )/total_alive[j] << '\t';
        }
        output << endl;
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
        output << "HPV16" << '\t';
        for(int j = ModelStartAge; j < ModelStopAge; j++) {
            output << static_cast<double>(HPV16count[j])/HPV16denom[j] << '\t';
        }
        output << endl;
        output << "HPV18" << '\t';
        for(int j = ModelStartAge; j < ModelStopAge; j++) {
            output << static_cast<double>(HPV18count[j])/HPV18denom[j] << '\t';
        }
        output << endl;
        output << "HPV" << '\t';
        for(int j = ModelStartAge; j < ModelStopAge; j++) {
            output << static_cast<double>(HPVcount[j])/HPVdenom[j] << '\t';
        }
        output << endl;
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