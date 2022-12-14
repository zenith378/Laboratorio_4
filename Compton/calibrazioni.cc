#include <iostream>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TStyle.h>



void calibrazioni()
{
    
    double_t peak_ua[]= {6131., 6917., 3550., 2739.04};//cobalto (2), cesio, sodio 
    double_t sigma_ua [] = {0.2, 5.5 , 1., 0.71};
    double_t peak_MeV[] = {1.173, 1.333, 0.662, 0.545};//cobalto (2), cesio, sodio
    //double_t sigma_MeV [] = {1., 1., 1., 1.};//da cercare (se li metto sulle x non servono per il calcolo del chi2)

    //defining the size of the array depth
    Int_t size = sizeof(peak_ua)/sizeof(peak_ua[0]);

    //defining the TGraph with error bars
    TGraphErrors *graph = new TGraphErrors(size,peak_MeV, peak_ua,nullptr,sigma_ua); 

    //posso definire io una funzione di fit f e usare quella come argomento di Fit(), oppure dargli una funzione già definita
    TF1 *fitfunction = new TF1("fitfunction", "[0]*x/(1 + [1]*x)" );
    graph->Fit("fitfunction");//why option F?
    

    graph->SetMarkerStyle(8);
    graph->SetMarkerColor(1);
    graph->SetMarkerSize(1);
    gStyle->SetOptFit(101);//serve per farsi stampare chi2, p0, p1
    graph->GetYaxis()->SetRangeUser(0., 8000.);
    graph->GetXaxis()->SetRangeUser(0.,2.);
    graph->SetTitle("Calibration curve; E [MeV]; E [u.a.]");
    TCanvas *c1 = new TCanvas();
    graph->Draw("AP");

}
