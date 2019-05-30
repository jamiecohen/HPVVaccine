//
// Created by Jamie Cohen on 11/29/17.
//

#include "outputs.h"

using namespace std;

const string extension = ".txt";

Output::Output(Inputs &Tables, int y) {

    DALY.resize (y + 1);
    YLL.resize (y + 1);
    YLD.resize (y + 1);

    viascreens.resize(y + 1);
    hpvscreens.resize(y + 1);
    hpvcolposcreens.resize(y + 1);
    papscreens.resize(y + 1);
    vaccines.resize(y+1);
    
    CaIncStandardized = 0;

    trace.resize(Tables.ModelStopAge + 1);
    for (int i = 0; i <= Tables.ModelStopAge; i++) {
        trace[i].resize(3);
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

    cost.resize (y + 1);


    HIVcount.resize (Tables.ModelStopAge + 1);


    HIVHPVcount.resize (Tables.ModelStopAge + 1);


    HIVCIN2count.resize (Tables.ModelStopAge + 1);

    HIVCIN3count.resize (Tables.ModelStopAge + 1);


    HIVCAcount.resize (Tables.ModelStopAge + 1);


    HIVCAdead.resize (Tables.ModelStopAge + 1);



    HIVdenom.resize (Tables.ModelStopAge + 1);


    HIVHPVdenom.resize (Tables.ModelStopAge + 1);


    HIVCIN2denom.resize (Tables.ModelStopAge + 1);


    HIVCIN3denom.resize (Tables.ModelStopAge + 1);


    HIVCAdenom.resize (Tables.ModelStopAge + 1);


    CIN2HIVpos.resize (Tables.ModelStopAge + 1);

    CIN3HIVpos.resize (Tables.ModelStopAge + 1);
    TotalPrevCancer.resize(y);
    TotalCancer.resize(y);
    TotalCancer_1618.resize(y);
    TotalCancer_nonavalent.resize (y);
    TotalCancer_allother.resize(y);
    TotalCancerDenom.resize(y);
    cancerHIVpos = 0;

    CA1618HIV = 0;

    CIN21618HIV = 0;

    CIN31618HIV = 0;

    CAotherHRHIV = 0;

    CAhigh5HIV = 0;

    CIN2otherHRHIV = 0;
    CIN2LRHIV = 0;
    CIN2high5HIV = 0;

    CIN3otherHRHIV = 0;
    CIN3LRHIV = 0;
    CIN3high5HIV = 0;

    CIN2HIVpostotal = 0;

    CIN3HIVpostotal = 0;
    QALY = 0;
    discDALY = 0;
    discountrate = 0.03;
    TotalCost = 0;

}

void Output::createTrace(Woman &Data, int i) {

    if(!Data.cancer){
        trace[Data.CurrentAge][0]++; // HIVpos, no cancer (prev DENOM)

        if(Data.CurrentAge >= 15){
            TotalCancerDenom[i]++;
        }
        HIVCAdenom[Data.CurrentAge]++;

        if(!Data.HPVinfections.empty ()){

            if (Data.hpv16 || Data.hpv18 || Data.hpv31 || Data.hpv33 || Data.hpv45 ||
                Data.hpv52 || Data.hpv58 || Data.otherHR) {
                trace[Data.CurrentAge][1]++; // all prevalent hr-HPV

                if(!Data.CIN2Lesions.empty () || !Data.CIN3Lesions.empty ()){
                    trace[Data.CurrentAge][2]++; // all prevalent CIN2+
                }
            }
        }
    }
}

void Output::createInc(Inputs &Tables) {

    for(int i = 15; i < 78; i++){
        CaIncStandardized +=  Tables.AgeStandard[i][0]*static_cast<double>(HIVCAcount[i])/HIVCAdenom[i];
    }

}

void Output::calcLE(Woman &Data, Inputs &Tables, int y) {
    if (Data.Alive) {
        if(Data.cancer){
            if(Data.cancerstage == Woman::Stage1){
                LE[y] += Tables.utilityCA1;
                YLD[y] += Tables.disabilityCA12;
                TotalPrevCancer[y]++;
            } else if (Data.cancerstage == Woman::Stage2){
                LE[y] += Tables.utilityCA2;
                YLD[y] += Tables.disabilityCA12;
                TotalPrevCancer[y]++;
            } else if (Data.cancerstage == Woman::Stage3){
                LE[y] += Tables.utilityCA3;
                YLD[y] += Tables.disabilityCA34;
                TotalPrevCancer[y]++;
            }
        }
        total_alive[Data.CurrentAge]++;
    } else {

        YLL[y] += Tables.LifeExpectancy[Data.CurrentAge][0];
    }
}

void Output::createCalibOutput() {

    // HPVHIVpos, CIN2HIV+, CIN3HIV+, CAHIV+, Cainc_18_25
    // Cainc_26_35
    // Cainc_36_45
    // Cainc_45
       
    int HPVHIVpos = 0;
    int HIVpos = 0;
    for(int i = 17; i < 25; i++){
        HPVHIVpos += trace[i][1];
        HIVpos += trace[i][0];
    }
    calib.push_back (static_cast<double>(HPVHIVpos)/HIVpos);

    for(int j = 0; j <8; j++){
        HPVHIVpos = 0;
        HIVpos = 0;
        for(int i = 25 + 5*j; i < 30 + 5*j; i++){
            HPVHIVpos += trace[i][1];
            HIVpos += trace[i][0];
        }
        calib.push_back (static_cast<double>(HPVHIVpos)/HIVpos);
    }

    int CINHIVpos = 0;
    int CINHIVpostotal = 0;
    for(int i = 17; i < 25; i++){
        CINHIVpos += trace[i][2];
        CINHIVpostotal += trace[i][0];
    }
    calib.push_back (static_cast<double>(CINHIVpos)/CINHIVpostotal);

    for(int j = 0; j <8; j++){
        CINHIVpos = 0;
        CINHIVpostotal = 0;
        for(int i = 25 + 5*j; i < 30 + 5*j; i++){
            CINHIVpos += trace[i][2];
            CINHIVpostotal += trace[i][0];
        }
        calib.push_back (static_cast<double>(CINHIVpos)/CINHIVpostotal);
    }

    calib.push_back(static_cast<double>(CIN21618HIV) / CIN2HIVpostotal );
    calib.push_back(static_cast<double>(CIN2otherHRHIV) / CIN2HIVpostotal );
    calib.push_back(static_cast<double>(CIN2high5HIV) / CIN2HIVpostotal );

    calib.push_back(static_cast<double>(CIN31618HIV) / CIN3HIVpostotal );
    calib.push_back(static_cast<double>(CIN3otherHRHIV) / CIN3HIVpostotal );
    calib.push_back(static_cast<double>(CIN3high5HIV) / CIN3HIVpostotal );

    calib.push_back(static_cast<double>(CAotherHRHIV) / cancerHIVpos );
    calib.push_back(static_cast<double>(CA1618HIV) / cancerHIVpos );
    calib.push_back(static_cast<double>(CAhigh5HIV) / cancerHIVpos );

    int CAnew = 0;
    int CAdenom = 0;
    for (int j = 18; j < 26; j ++){
        CAnew += HIVCAcount[j];
        CAdenom += HIVCAdenom[j];
    }
    calib.push_back(100000 * static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for (int j = 26; j < 36; j ++){
        CAnew += HIVCAcount[j];
        CAdenom += HIVCAdenom[j];
    }
    calib.push_back(100000 * static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for (int j = 36; j < 46; j ++){
        CAnew += HIVCAcount[j];
        CAdenom += HIVCAdenom[j];
    }
    calib.push_back(100000 * static_cast<double>(CAnew)/CAdenom);

    CAnew = 0;
    CAdenom = 0;
    for (int j = 46; j < 90; j ++){
        CAnew += HIVCAcount[j];
        CAdenom += HIVCAdenom[j];
    }
    calib.push_back(100000 * static_cast<double>(CAnew)/CAdenom);

}

void Output::writeCohort(std::string *Outdir, int ModelStartAge, int ModelStopAge, int SimYears) {

    ofstream output;
    string OutputFileName;
    OutputFileName.append(*Outdir);
    OutputFileName.append("/");
    OutputFileName.append("_Catotalinc");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << "" << '\t';
        for(int j = ModelStartAge; j < ModelStopAge; j++) {
            output << j << '\t';
        }
        output << endl;
        output << "Total" << '\t';
        for(int j = 0; j < (SimYears - ModelStartAge); j++) {
            output << 100000*static_cast<double>(TotalCancer[j])/TotalCancerDenom[j] << '\t';
        }
        output << endl;
        output << "1618" << '\t';
        for(int j = 0; j < (SimYears - ModelStartAge); j++) {
            output << 100000*static_cast<double>(TotalCancer_1618[j])/TotalCancerDenom[j] << '\t';
        }
        output << endl;

        output << "nonavalent" << '\t';
        for(int j = 0; j < (SimYears - ModelStartAge); j++) {
            output << 100000*static_cast<double>(TotalCancer_nonavalent[j])/TotalCancerDenom[j] << '\t';
        }
        output << endl;

        output << "otherHR" << '\t';
        for(int j = 0; j < (SimYears - ModelStartAge); j++) {
            output << 100000*static_cast<double>(TotalCancer_allother[j])/TotalCancerDenom[j] << '\t';
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
    OutputFileName.append("_costbenefit");
    OutputFileName.append(extension);
    output.open(OutputFileName.c_str (), ios::out);

    if(output){
        output << " \tLifetime_Cost\tDiscounted_DALYs" << endl;
        output << "Total" << '\t';
        output << TotalCost << '\t';
        output << discDALY << endl;
    }
    else
        cerr << "Warning: Unable to open " << OutputFileName << endl;
    output.close();
    output.clear();

}

Output::~Output(void) = default;