#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include "TF1.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TPaveText.h"
#include "TAxis.h"
#include "TStyle.h"

TLegend * drawLegend(TGraph * leg_plot1,TF1 * leg_func){
    TLegend * legend = new TLegend(0.15, 0.4, 0.35, 0.57, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);
    legend->AddEntry(leg_plot1, "Data", "EP");
    legend->AddEntry(leg_func, "best-fit", "L");
    legend->Draw();
    return legend;
}

TPaveText * drawInfos(){
    TPaveText * infos = new TPaveText(0.55, 0.75, 0.85, 0.85, "NDC nb");
    infos->SetTextAlign(11);
    infos->SetTextFont(42);
    infos->SetTextSizePixels(22);
    infos->SetFillColorAlpha(0,0.0);
    infos->AddText("E_{in} = 1.173240 MeV");
    //infos->AddText("#theta_{offset} = -1.034 #pm 0.083#circ");
    infos->Draw();
    return infos; 
}

void fancyPlot(TGraphErrors * plt){
    plt->GetXaxis()->SetTitle("#theta [degrees]"); plt->GetXaxis()->SetTitleSize(0.045);
    plt->GetYaxis()->SetTitle("E_{fin} [MeV]"); plt->GetYaxis()->SetTitleSize(0.045);
    plt->GetYaxis()->SetTitleOffset(1.05);
    plt->SetMarkerStyle(20);
    plt->SetMarkerColor(3);
}

Double_t compton(Double_t * x, Double_t * p){
    Double_t E_peak = p[0];
    Double_t m_e = p[1];
    Double_t theta_rad = (x[0] - p[2]) * 3.14159 / 180;
    return E_peak / (1 + (E_peak / m_e) * (1 - TMath::Cos(theta_rad))) + p[3];
}

void FitMassa(){
    gStyle->SetOptStat(1111); gStyle->SetOptFit(1111);
    gStyle->SetStatBorderSize(0.);
    gStyle->SetStatX(.5); gStyle->SetStatY(.35); gStyle->SetFillColorAlpha(0,0.);

    // DATA
    Double_t E_low[] = {0.7, 0.649, 0.625};
    Double_t dE_low[] = {0.0051, 0.0043, 0.0054};
    Double_t dE_lows[] = {0.0173, 0.0195, 0.0165, 0.0149, 0.0172};
    Double_t E_high[] = {1.0451, 0.997, 0.940};
    Double_t dE_high[] = {0.0057, 0.0051, 0.0057};
    Double_t dE_highs[] = {0.0176, 0.0197, 0.0166, 0.0149, 0.0172};
    Double_t th[] = {18,23,28};
    Double_t dth[] = {0.29, 0.29, 0.29, 0.29, 0.29};
    Double_t dth_sist[] = {1.16, 1.16, 1.16, 1.16, 1.16};
    Double_t E_peaklow = 1.173240, E_peakhigh = 1.332508;

    // TGRAPH AND FUNCTION
    TCanvas * c1 = new TCanvas("c1", "c1", 1);
    TGraphErrors * plot = new TGraphErrors(3,th, E_low, dth, dE_low);
    plot->SetTitle("");
    TF1 * func = new TF1("compton", compton, 0, 45, 4); 
    func->SetParNames("E_{peak}", "m_{e}", "#theta_{0}", "k");
    func->FixParameter(0, E_peaklow);
    func->SetParameter(1, 0.511); // m_e
    func->SetParameter(2, -3); // theta_0
    func->FixParameter(3, 0);     // k

    // FIT AND FANCY
    plot->Draw("AP");
    TFitResultPtr r = plot->Fit("compton", "S");
    r->Print();

    TLegend * legend = drawLegend(plot,func);
    TPaveText * infos = drawInfos();
    fancyPlot(plot);
}