#include <iostream>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TStyle.h>



void SistematicoRate()
{
    //first peak (da 17 cm in poi)
    double_t peak1[] = {6056.0, 6014.9, 5987., 5963., 5931.};//[a.u.]
    //sono gli errori dati dal fit, poi andranno considerati i sistematici (scala di enrgia)
    double_t err_peak1[] = {1., 1., 1., 1., 1. };

    //second peak (da 17 cm in poi)
    double_t peak2[] = {6837.7, 6788.7, 6763.2, 6725., 6693.}; //[a.u.]
    double_t err_peak2[] = {0.9, 0.9, 0.9, 1., 1.};

    //conteggi
    double_t counts[] = {364665., 293743., 270329., 238417., 202024.};
    double_t err_counts[] = {604., 542., 520., 488., 449.}; //è la radice del numero dei conteggi


    //defining the size of the array depth
    Int_t size = sizeof(peak1)/sizeof(peak1[0]);

    //defining the TGraph with error bars for the position of peak1
    TGraphErrors *graph1 = new TGraphErrors(size,counts, peak1, err_counts, err_peak1); 

    
    graph1->Fit("pol1");//why option F?
    

    graph1->SetMarkerStyle(8);
    graph1->SetMarkerColor(1);
    graph1->SetMarkerSize(1);
    gStyle->SetOptFit(111);//serve per farsi stampare chi2, p0, p1
    graph1->GetYaxis()->SetRangeUser(0., 8000.);
    graph1->GetXaxis()->SetRangeUser(0.,2.);
    graph1->SetTitle("Variation of the first peak with rate; Counts PMT1 ; E [u.a.]");
    TCanvas *c1 = new TCanvas();
    graph1->Draw("AP");

}
