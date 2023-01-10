#include <iostream>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TStyle.h>
#include <TMultiGraph.h>



void CalibrazioniTemperatura()
{
    //--------------------MANCANO I DATI DELLA CALIBRAZIONE DELLE 18---------------------

    //---COBALTO

    //posizione del primo picco per la sorgente di Co-60, per temperature decrescenti
    double_t peak1_Co[] = {5977., 5911., 5862.};//[a.u.]
    //sono gli errori dati dal fit
    double_t err_peak1_Co[] = {2., 2., 2.};

    double_t peak2_Co[] = {6752., 6676., 6625.};
    double_t err_peak2_Co[] = {2., 2., 2.};

    //----CESIO
    double_t peak_Ce[]={3472.6, 3433.6, 3406.5};
    double_t err_peak_Ce[]={0.5, 0.6, 0.3};

    //----SODIO
    double_t peak_Na[]={2670., 2636., 2622.};
    double_t err_peak_Na[]={1., 1., 2.};

    //----TEMPERATURA
    double_t temperatura[]= {19.8, 20.4, 20.9};//in °C
    double_t err_temperatura [] = {0.1, 0.1, 0.1}; //è di quanto ballava la temperatura letta 

    
    //defining the size of the array depth
    Int_t size = sizeof(peak1_Co)/sizeof(peak1_Co[0]);

    //TMultiGraph *mg = new TMultiGraph();
    //mg->SetTitle("Exclusion graphs");

    
    TGraphErrors *graph_Co_1 = new TGraphErrors(size,temperatura, peak1_Co, err_temperatura, err_peak1_Co); 
    TGraphErrors *graph_Co_2 = new TGraphErrors(size,temperatura, peak2_Co, err_temperatura, err_peak2_Co);
    TGraphErrors *graph_Ce = new TGraphErrors(size,temperatura, peak_Ce, err_temperatura, err_peak_Ce);  
    TGraphErrors *graph_Na = new TGraphErrors(size,temperatura, peak_Na, err_temperatura, err_peak_Na);  
    

    TF1* fitfunction_Co = new TF1 ("fitfunction_Co", "[0] + [1]*x + [2]*x*x");
    fitfunction_Co->SetParameter(0, 19000. );
    fitfunction_Co->SetParameter(1, -1180.);
    fitfunction_Co->SetParameter(2, 26);

    graph_Co_2->Fit("fitfunction_Co");
    graph_Co_1->Fit("fitfunction_Co");

    TF1* fitfunction_Ce = new TF1 ("fitfunction_Ce", "[0] + [1]*x+ [2]*x*x");
    fitfunction_Ce->SetParameter(0, 8726. );
    fitfunction_Ce->SetParameter(1, -459.);
    fitfunction_Ce->SetParameter(2, 10.);
    
    graph_Ce->Fit("fitfunction_Ce");

    TF1* fitfunction_Na = new TF1 ("fitfunction_Na", "[0] + [1]*x +[2]*x*x");
    fitfunction_Na->SetParameter(0, 14000. );
    fitfunction_Na->SetParameter(1, -1100.);
    fitfunction_Na->SetParameter(2, 26.);
    
    graph_Na->Fit("fitfunction_Na");

   

    graph_Co_1->SetMarkerStyle(8);
    graph_Co_1->SetMarkerColor(1);
    graph_Co_1->SetMarkerSize(1);
    graph_Co_1->SetTitle("Posizione del primo picco del Co-60 al variare  della temperatura; Temperatura [$'°C'$] ; E [u.a.]");

    graph_Co_2->SetMarkerStyle(8);
    graph_Co_2->SetMarkerColor(4);
    graph_Co_2->SetMarkerSize(1);
    graph_Co_2->SetTitle("Posizione del secondo picco del Co-60 al variare  della temperatura; Temperatura [$'°C'$] ; E [u.a.]");

    graph_Ce->SetMarkerStyle(8);
    graph_Ce->SetMarkerColor(5);
    graph_Ce->SetMarkerSize(1);
    graph_Ce->SetTitle("Posizione del picco del Cesio-137 al variare  della temperatura; Temperatura [$'°C'$] ; E [u.a.]");

    graph_Na->SetMarkerStyle(8);
    graph_Na->SetMarkerColor(5);
    graph_Na->SetMarkerSize(1);
    graph_Na->SetTitle("Posizione del picco del Sodio-22  al variare  della temperatura; Temperatura [$'°C'$] ; E [u.a.]");


    gStyle->SetOptFit(111);//serve per farsi stampare chi2, p0, p1
    
    //graph_Ce->GetYaxis()->SetRangeUser(0., 10000.);
    //graph_Na->GetYaxis()->SetRangeUser(0., 10000.);
    //graph_Co_2->GetYaxis()->SetRangeUser(0., 10000.);
    //graph_Co_1->GetYaxis()->SetRangeUser(0., 10000.);

    //graph_Co_1->GetXaxis()->SetLimits(0., 50.);
    //graph_Co_2->GetXaxis()->SetLimits(0., 50.);
    //graph_Ce->GetXaxis()->SetLimits(0., 50.);
    //graph_Na->GetXaxis()->SetLimits(0., 50.);
    
    
    //mg->Add(graph_Ce);
    //mg->Add(graph_Co_1);
    //mg->Add(graph_Co_2);
    //mg->GetYaxis()->SetLimits(0., 6700.);


    //drawing graphs
    TCanvas *c1 = new TCanvas();
    graph_Ce->Draw("AP");

    TCanvas *c2 = new TCanvas();
    graph_Co_1->Draw("AP");

    TCanvas *c3 = new TCanvas();
    graph_Co_2->Draw("AP");

    TCanvas *c4 = new TCanvas();
    graph_Na->Draw("AP");


}
