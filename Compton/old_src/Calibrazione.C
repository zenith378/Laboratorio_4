//
//  Compton.C
//
//
//  Created by Giulio Cordova on 06/12/22.
//
//
#include "TTree.h"
#include <stdio.h>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooBreitWigner.h"
#include "RooAddPdf.h"
#include "RooGlobalFunc.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TH1.h"
#include "RooHist.h"
#include "TRootCanvas.h"
#include "RooDataHist.h"
#include "TStyle.h"
#include "RooFitResult.h"
#include "Spectrum.h"

#include <string.h>

using namespace RooFit;


void Calibrazione()
{

/*
    // Tree creation
    TTree *cesio = new TTree("cesio", "cesio");
    TTree *cobalto = new TTree("cobalto", "cobalto");
    TTree *sodio = new TTree("sodio", "sodio");
    TTree *stronzio = new TTree("stronzio", "stronzio");

    // Data load
    cesio->ReadFile("Data/cesio1dicembre.dat", "x");
    cobalto->ReadFile("Data/cobalto60.dat", "x");
    sodio->ReadFile("Data/sodio22.dat", "x");
    stronzio->ReadFile("Data/stronzio90.dat", "x");

    Int_t nbins = cesio->GetEntries();
    Float_t v_cesio;
    Float_t v_cobalto;
    Float_t v_sodio;
    Float_t v_stronzio;
    cesio->SetBranchAddress("x", &v_cesio);
    cobalto->SetBranchAddress("x", &v_cobalto);
    sodio->SetBranchAddress("x", &v_sodio);
    stronzio->SetBranchAddress("x", &v_stronzio);
    TH1 *h_cesio = new TH1D("h_cesio", "E Cesium Spectrum;Energy;Counts", nbins, 0., nbins);
    TH1 *h_cobalto = new TH1D("h_cobalto", "E Cobalt Spectrum;Energy;Counts", nbins, 0., nbins);
    TH1 *h_sodio = new TH1D("h_sodio", "E Sodium Spectrum;Energy;Counts", nbins, 0., nbins);
    TH1 *h_stronzio = new TH1D("h_stronzio", "E Strontium  Spectrum;Energy;Counts", nbins, 0., nbins);
    for (Int_t i = 0; i < nbins; i++)
    {
        cesio->GetEntry(i);

        h_cesio->SetBinContent(i, v_cesio);

        cobalto->GetEntry(i);

        h_cobalto->SetBinContent(i, v_cobalto);

        sodio->GetEntry(i);

        h_sodio->SetBinContent(i, v_sodio);

        stronzio->GetEntry(i);

        h_stronzio->SetBinContent(i, v_stronzio);
    }
    h_cesio->Rebin(3);
    h_cobalto->Rebin(3);
    h_sodio->Rebin(3);
    h_stronzio->Rebin(3);

*/

    h_cesio=Spectrum("./Data/cesio1dicembre.dat")
    h_cobalto=Spectrum("./Data/cobalto60.dat")
    h_sodio=Spectrum("./Data/sodio22.dat")
    h_stronzio=Spectrum("./Data/stronzio90.dat")
    
  // Set up   component   pdfs
    // ---------------------------------------

    // Declare observable x
    RooRealVar x("x", "Energy [a.u.]", 0, 8500);

    //SODIO

    // Declare histogram from argument one
    RooDataHist rh_sodio("rh_sodio", "rh_sodio", x, Import(*h_sodio));


    // Create Gaussian PDF and its parameters
    RooRealVar mean_sodio("mean1", "mean of gaussians", 2740, 2000, 3500);
    RooRealVar sigma_sodio("sigma1", "width of gaussians", 200, 100, 400);

    RooGaussian* sig_sodio = new RooGaussian("sig1", "Signal component 1", x, mean_sodio, sigma_sodio);


    // Build polynomial pdf
    RooRealVar a0("a0", "a0", 450, 0, 10000);
    RooRealVar a1("a1", "a1", -0.017, -300., 300.);
    RooRealVar a2("a2","a2", 0,0,30 );
    RooPolynomial bkg("bkg", "Background", x, RooArgSet(a0, a1,a2));


    // Define model and fit
    // ---------------------------------------


    // Add signal and background

    RooRealVar fsig1("fsig1", "signal1", 0., 1.);

    RooAddPdf model("model", "model", RooArgList(*sig_sodio,bkg), RooArgList(fsig1), kTRUE);


    // Define "signal" range in x as [-3,3]
    x.setRange("signal", 2300, 3300);
    //  Fit model to data
    //model.fitTo(rh_sodio);

    // Fit pdf only to data in "signal" range
    RooFitResult *r_sig = model.fitTo(rh_sodio, Save(true), Range("signal"));


    // Draw options
    // ---------------------------------------


    // Plot data and PDF overlaid
    RooPlot *xframe = x.frame(Title("Sodium  Spectrum"));

    rh_sodio.plotOn(xframe, Range(""), MarkerStyle(6),MarkerSize(1),LineStyle(kDashed), LineColor(kGreen));


    // Overlay the background component of model with a dashed line
    model.plotOn(xframe, Components(bkg), LineColor(kBlue), LineStyle(kDashed));
    // Overlay the sig1 components of model with a dashed-dotted line
    model.plotOn(xframe, Components(RooArgSet(*sig_sodio)), LineColor(kRed), LineStyle(8));

    // Print structure of composite pdf
    model.Print("t");

    model.plotOn(xframe);

    RooHist *hpull = xframe->pullHist();
    hpull->SetMarkerSize(1);
    hpull->SetMarkerStyle(6);

    // Draw the frame on the canvas
    auto c1 = new TCanvas("Fit", "", 800, 800);

    TPad *pad1 = new TPad("pad1", "The pad 80 of the height",0.0,0.2,1.0,1.0);
    TPad *pad2 = new TPad("pad2", "The pad 20 of the height",0.0,0.05,1.0,0.25);
    pad1->Draw();
    pad2->Draw();
    pad1->cd();

    xframe->GetYaxis()->SetTitleOffset(1.5);
    xframe->GetXaxis()->SetTitleSize(0);
    xframe->GetXaxis()->SetLabelSize(0);
    //xframe->GetXaxis()->SetTitleOffset(999);
    xframe->SetMinimum(0.001);

    xframe->Draw();
    pad2->cd();
    pad2->SetBottomMargin(0.4);
    //auto axis = hpull->GetXaxis();

    //axis->SetLimits(8.5001,11.5);   
    //hpull->GetYaxis()->SetNdivisions(6);
    //hpull->SetMinimum(-9.999);
    hpull->GetXaxis()->SetTitleOffset(1.3);
    hpull->GetYaxis()->SetTitle("Pull");
    hpull->GetXaxis()->SetTitle("Energy [u.a.]");
    hpull->GetXaxis()->SetLabelFont(43);
    hpull->GetXaxis()->SetLabelSize(21); 
    hpull->GetYaxis()->SetLabelFont(43);
    hpull->GetYaxis()->SetLabelSize(21); 
    hpull->GetXaxis()->SetTitleSize(21);
    hpull->GetXaxis()->SetTitleFont(43);
    hpull->GetYaxis()->SetTitleSize(21);
    hpull->GetYaxis()->SetTitleFont(43);
    hpull->SetTitle("");
    //hpull->GetXaxis()->SetTitleOffset(3);


    //gStyle->SetTitleFontSize(14);

    hpull->Draw();
    //gPad->SetLeftMargin(0.3);
    c1->Update();

    //xframe->GetYaxis()->SetTitleOffset(1.4);
    //xframe->Draw();
    c1->SaveAs("RooFit_Sodio.pdf");






    //CESIO

    // Declare histogram from argument one
    RooDataHist rh_cesio("rh_cesio", "rh_cesio", x, Import(*h_cesio));


    // Create Gaussian PDF and its parameters
    RooRealVar mean_cesio("mean1", "mean of gaussians", 3410, 3350, );
    RooRealVar sigma_cesio("sigma1", "width of gaussians", 300, 100, 400);

    RooGaussian* sig_cesio = new RooGaussian("sig1", "Signal component 1", x, mean_cesio, sigma_cesio);


    // Build polynomial pdf
    RooRealVar a0_cesio("a0_cesio", "a0_cesio", 700, 0, 10000);
    RooRealVar a1_cesio("a1_cesio", "a1_cesio", -0.25, -300., 300.);
    RooPolynomial bkg_cesio("bkg", "Background", x, RooArgSet(a0_cesio, a1_cesio));


    // Define model and fit
    // ---------------------------------------


    // Add signal and background

    RooRealVar fsig1_cesio("fsig1", "signal1", 0., 1.);

    RooAddPdf model_cesio("model_cesio", "model_cesio", RooArgList(*sig_sodio,bkg), RooArgList(fsig1_cesio), kTRUE);


    // Define "signal" range in x as [-3,3]
    x.setRange("signal_cesio", 3000, 4000);
    //  Fit model to data
    //model.fitTo(rh_sodio);

    // Fit pdf only to data in "signal" range
    RooFitResult *r_sig_cesio = model.fitTo(rh_cesio, Save(true), Range("signal_cesio"));


    // Draw options
    // ---------------------------------------


    // Plot data and PDF overlaid
    RooPlot *xframe_cesio = x.frame(Title("Cesium  Spectrum"));

    rh_cesio.plotOn(xframe_cesio, Range(""), MarkerStyle(6),MarkerSize(1));


    // Overlay the background component of model with a dashed line
    model_cesio.plotOn(xframe_cesio, Components(bkg), LineColor(kBlue), LineStyle(kDashed));
    // Overlay the sig1 components of model with a dashed-dotted line
    model_cesio.plotOn(xframe_cesio, Components(RooArgSet(*sig_cesio)), LineColor(kRed), LineStyle(8));

    // Print structure of composite pdf
    model_cesio.Print("t");

    model_cesio.plotOn(xframe_cesio);

    RooHist *hpull_cesio = xframe_cesio->pullHist();
    hpull_cesio->SetMarkerSize(1);
    hpull_cesio->SetMarkerStyle(6);

    // Draw the frame on the canvas
    auto c2 = new TCanvas("c2", "Fit Cesio", 800, 800);

    TPad *pad3 = new TPad("pad3", "The pad 80 of the height",0.0,0.2,1.0,1.0);
    TPad *pad4 = new TPad("pad4", "The pad 20 of the height",0.0,0.05,1.0,0.25);
    pad3->Draw();
    pad4->Draw();
    pad3->cd();

    xframe_cesio->GetYaxis()->SetTitleOffset(1.5);
    xframe_cesio->GetXaxis()->SetTitleSize(0);
    //xframe_cesio->GetXaxis()->SetLabelSize(0);
    //xframe->GetXaxis()->SetTitleOffset(999);
    xframe_cesio->SetMinimum(0.001);

    xframe_cesio->Draw();
    pad4->cd();
    pad4->SetBottomMargin(0.4);
    //auto axis = hpull->GetXaxis();

    //axis->SetLimits(8.5001,11.5);   
    //hpull->GetYaxis()->SetNdivisions(6);
    //hpull->SetMinimum(-9.999);
    hpull_cesio->GetXaxis()->SetTitleOffset(1.3);
    hpull_cesio->GetYaxis()->SetTitle("Pull");
    hpull_cesio->GetXaxis()->SetTitle("Energy [u.a.]");
    hpull_cesio->GetXaxis()->SetLabelFont(43);
    hpull_cesio->GetXaxis()->SetLabelSize(21); 
    hpull_cesio->GetYaxis()->SetLabelFont(43);
    hpull_cesio->GetYaxis()->SetLabelSize(21); 
    hpull_cesio->GetXaxis()->SetTitleSize(21);
    hpull_cesio->GetXaxis()->SetTitleFont(43);
    hpull_cesio->GetYaxis()->SetTitleSize(21);
    hpull_cesio->GetYaxis()->SetTitleFont(43);
    hpull_cesio->SetTitle("");
    //hpull->GetXaxis()->SetTitleOffset(3);


    //gStyle->SetTitleFontSize(14);

    hpull_cesio->Draw();
    //gPad->SetLeftMargin(0.3);
    c2->Update();

    //xframe->GetYaxis()->SetTitleOffset(1.4);
    //xframe->Draw();
    c2->SaveAs("RooFit_Cesio.pdf");
}