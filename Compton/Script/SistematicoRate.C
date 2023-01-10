#include <iostream>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TStyle.h>



void SistematicoRate()
{
    //first peak (da 17 cm in poi). I valori dal sesto compreso in poi sono relativi alla sorgente di calibrazione di Co-60, mentre i primi 5 sono stati presi con la sorgente "grande"
    
    //double_t peak1[] = {6056.0, 6014.9, 5987., 5963., 5931., 5891., 5875., 5870., 5879., 5868., 5869., 5856., 5856., 5857.0, 5852., 5856., 5843., 5843.};//[a.u.]
    //sono gli errori dati dal fit, poi andranno considerati i sistematici (scala di enrgia)
    //double_t err_peak1[] = {1., 1., 1., 1., 1., 2., 2., 2., 2., 1., 2., 3. , 3., 3., 3., 4., 5., 5.};
    double_t peak1[] = {5844., 5842., 5857.,5853., 5856., 5867.,5859.,5868.,5868., 5881., 5876., 5871., 5892., 6046.9, 6006., 5982., 5951., 5920.,};
    double_t err_peak1[] = {6., 9.,4.,4., 3., 5., 3.,3., 2.,2.,3.,2., 2., 0.8, 1., 1., 1., 1.};

    double_t peak2[] = {};
    double_t err_peak2[] = {};
    //second peak (da 17 cm in poi)
    //double_t peak2[] = {6837.7, 6788.7, 6763.2, 6725., 6693., 6659., 6641., 6832., 6643., 6630., 6626., 6624., 6615., 6622., 6610., 6608., 6613., 6615.}; //[a.u.]
    //double_t err_peak2[] = {0.9, 0.9, 0.9, 1., 1., 2., 3., 2., 2., 4., 3., 3., 3., 3., 4., 4., 6., 7.};

    //conteggi letti dal contatore (non va bene poichè ci servono solo i conteggi sotto la curva di segnale)
    //double_t counts[] = {3646.65, 2937.43, 2703.29, 2384.17, 2020.24, 875.,530., 434., 381., 307., 276., 239., 213., 193., 167.57, 119.00, 91.59, 74.21};//Hz
    
    //conteggi di solo segnale (area sotto la curva del segnale)
    double_t counts1[]={9.3, 11.7, 17.6, 30.5, 33.2 , 37.,42., 50., 59.,74., 84.,108.,172., 820., 664., 543., 476., 408.};
    
    //gli errori sui rate devono essere divisi per sqrt(100000), dove 100000 sono i conteggi totali
    //double_t err_counts[] = {6.04, 5.42, 5.20, 4.88, 4.49, 2.96, 2.30, 2.08, 1.95, 1.75, 1.66, 1.55, 1.46, 1.39, 1.29, 1.10, 0.96, 0.86}; //è la radice del numero dei conteggi
    double_t err_counts1[]= {0.7, 1.2, 0.9, 1.1, 1.1, 1., 1.,2., 2., 2.,2., 4.,5. , 8., 12., 4., 4., 6.};//Hz

    //defining the size of the array depth
    Int_t size = sizeof(peak1)/sizeof(peak1[0]);

    //defining the TGraph with error bars for the position of peak1
    TGraphErrors *graph1 = new TGraphErrors(size,counts1, peak1, err_counts1, err_peak1); 

    
    //graph1->Fit("pol3");//why option F?
    

    graph1->SetMarkerStyle(8);
    graph1->SetMarkerColor(1);
    graph1->SetMarkerSize(1);
    gStyle->SetOptFit(111);//serve per farsi stampare chi2, p0, p1
    //graph1->GetYaxis()->SetRangeUser(5800., 6000.);
    //graph1->GetXaxis()->SetRangeUser(0.,2.);
    graph1->SetTitle("Variation of the first peak with rate; Rate PMT1 [Hz] ; E [u.a.]");
    TCanvas *c1 = new TCanvas();
    graph1->Draw("AP");

}
