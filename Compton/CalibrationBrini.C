#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TRatioPlot.h"

TLegend * drawLegend(TH1D * leg_h1, TF1 * leg_f1){
    TLegend * legend = new TLegend(0.15, 0.7, 0.35, 0.85, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);
    legend->AddEntry(leg_h1, "^{137}Cs", "L");
    legend->AddEntry(leg_f1, "best-fit", "L");
    legend->Draw();
    return legend;
}

// arXiv:1610.09185 [physics.ins-det]
// Safari, Davani, Afarideh
Double_t SDAfunc(Double_t * x, Double_t * p){
    Double_t E = x[0], a = p[0], b = p[1], c = p[2], mu = p[3], s = p[4];
    Double_t alpha = (a * (pow(E,2) + pow(s,2)) + b * E + c) / 2;
    Double_t beta = - s * (a * (E + mu)) / (sqrt(2 * TMath::Pi())) + c;
    Double_t exp = (E - mu) / (sqrt(2) * s);

    return (alpha * TMath::Erfc(exp) + beta * TMath::Exp(-pow(exp,2))) + p[5] * E + p[6];
}


Double_t background(Double_t * x, Double_t * p){
    return p[0] * TMath::Exp(- x[0] / p[1]) + p[2] + p[3] * x[0];
}

Double_t gaus(Double_t * x, Double_t * p){
    return p[0] * TMath::Gaus(x[0], p[1], p[2]);
}

Double_t fitFunc(Double_t * x, Double_t * p){
    return gaus(x, p) + SDAfunc(x, &p[3]);
}

void CalibrationBrini(){
    gStyle->SetOptStat("e"); gStyle->SetOptFit(1111);
    gStyle->SetStatBorderSize(0.);
    gStyle->SetStatX(.92); gStyle->SetStatY(.89);

//Define Trees
    TTree *t= new TTree("cesio","cesio");


  //
    t->ReadFile("./Data/cesio1dicembre.dat", "x");



    Int_t nbins = t->GetEntries();
    Float_t v_t;

    t->SetBranchAddress("x", &v_t);

    TH1D *h = new TH1D("h","E Cesium Spectrum;Energy;Counts", nbins,0.,nbins);

    for (Int_t i=0;i<nbins;i++){
        t->GetEntry(i);
 
        h->SetBinContent(i,v_t);
  
    }
    h->Rebin(25);

    TCanvas * c1 = new TCanvas("c1", "c1", 1);

    TF1 * func = new TF1("fitFunc", fitFunc, 2000, 5000, 10);
    TF1 * fgaus = new TF1("fgaus", gaus, 2000, 5000, 3);
    TF1 * fbg = new TF1("fbg", background, 2000, 5000, 4);
    TF1 * fSDA = new TF1("fSDA", SDAfunc, 2000, 5000, 7);
    func->SetParameters(1200, 3500, 200, 5e-5, 1e-4, 1e-3, 2400, 200, -0.01, 1);
    // func->SetParNames("A_{0}", "#mu", "#sigma", "A_{1}", "#tau");

    // Plot, fit and fancy graph
    func->SetParameters(500, 3500, 200, 2e-5, 1e-4, 1e-3, 2400, 200, -0.01, 1);
    TFitResultPtr r = h->Fit("fitFunc", "", "LIRS", 2200, 4000);
    h->Draw();
    TRatioPlot * r1 = new TRatioPlot(h);
    



    c1->Clear();
    r1->Draw();
    //r1->GetLowerRefGraph()->SetMinimum(-2);
    //r1->GetLowerRefGraph()->SetMaximum(2);
    // Double_t par[7]; func->GetParameters(par); 
    // fgaus->SetParameters(par); fgaus->Draw("SAME"); fgaus->SetLineColor(3);
    // fbg->SetParameters(&par[3]); fbg->Draw("SAME"); fbg->SetLineColor(4);

    TLegend * legend = drawLegend(h, func);
}