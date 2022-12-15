
#include "TTree.h"
#include "TH1D.h"
#include <stdio.h>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TH1.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooHist.h"
#include "TRootCanvas.h"
#include "TStyle.h"
#include <string.h>
#include <filesystem>

using namespace RooFit;

void FitCalibrazione()
{

    std::string namefile = "13dicembre16cesio";
    std::string nameHist = "Cesio_13_dicembre_H16";
    std::string histTitle = "Cesio 13 dicembre H16";
    float min = 2800;
    float max = 4000;
    // Define Trees
    TTree *t = new TTree("t", "t");

    std::string tmp = "../20 gradi/Data/Calibrazioni/" + namefile + ".dat";
    const char *fname = tmp.c_str();

    t->ReadFile(fname, "x");

    Int_t nbins = t->GetEntries();
    Float_t v_t;

    t->SetBranchAddress("x", &v_t);

    TH1D *h = new TH1D("h", histTitle.c_str(), nbins, 0., nbins);

    for (Int_t i = 0; i < nbins; i++)
    {
        t->GetEntry(i);

        h->SetBinContent(i, v_t);
    }
    h->Rebin(15);
    h->GetXaxis()->SetRangeUser(min, max);

    auto *c = new TCanvas("c", "Spettro", 800, 700);
    h->Draw();
    h->DrawClone();

    std::string tmp_name = "../20 gradi/Plots/Calibrazione/Cesio/" + nameHist + ".pdf";
    const char *ffile = tmp_name.c_str();

    c->SaveAs(ffile);

    RooRealVar x("x", "Energy [a.u.]", min, max);
    RooDataHist rh("rh", "rh", x, Import(*h));

    Int_t nb = h->GetNbinsX();
    Double_t x1 = h->GetBinCenter(1);
    Double_t x9 = h->GetBinCenter(nb);
    Int_t i1 = h->FindBin(x1);
    Int_t i9 = h->FindBin(x9);
    Double_t n1 = h->GetBinContent(i1);
    Double_t n9 = h->GetBinContent(i9);
    Double_t slp = (n9-n1)/(x9-x1);
    Double_t bg = n1 - slp*x1; 

    RooRealVar a0("a0", "a0", bg, 0., 2000.);
    RooRealVar a1("a1", "a1", slp, -10., 0.);
    //RooRealVar a2("a2", "a2", 0, -30., 30.);
    RooPolynomial bkg("bkg", "Background", x, RooArgSet(a0, a1));

    RooRealVar mean("mean", "mean of gaussians", 3530,3500 , 3550);
    RooRealVar sigma("sigma", "width of gaussians", 350, 100, 600);
    RooRealVar alpha_up("alpha_up","alpha_up",1,0,10);
    RooRealVar n_up("n_up","n_up",1,0,10);
    
    RooRealVar fsig1("fsig1", "signal1", 0.8, 0.01, 1.);

    RooGaussian sig_gaus("sig1", "Gaussian signal component", x, mean, sigma);
    RooCBShape sig_cb("upsilon","crystal ball PDF",x,mean,sigma,alpha_up,n_up);

    x.setRange("signal_gaus", 2800., 4000.);
    
    //RooAddPdf model("model_gaus", "Gaussian model", RooArgList(sig_gaus, bkg), RooArgList(fsig1), kTRUE);
    
    RooAddPdf model("model_cb", "Crystal Ball model", RooArgList(sig_cb, bkg), RooArgList(fsig1),kTRUE);

    RooFitResult *fitResult = model.fitTo(rh, Range("signal_gaus"),RecoverFromUndefinedRegions(1), Verbose(false), Warnings(false), Save(), PrintEvalErrors(-1), PrintLevel(-1));
    
    fitResult->Print("v");



    std::string tmp_fit = histTitle + " Fit";
    const char *ffit = tmp_fit.c_str();

    RooPlot *xframe = x.frame(Title(ffit));

    // Plot data and PDF overlaid
    rh.plotOn(xframe, MarkerStyle(6), MarkerSize(1));

    // Overlay the background component of model with a dashed line
    model.plotOn(xframe, Components(bkg),Range("signal_gaus"), LineColor(41), LineStyle(kDashed));
    // Overlay the sig1 components of model with a dashed-dotted line
    model.plotOn(xframe, Components(sig_cb),Range("signal_gaus"), LineColor(46), LineStyle(8));

    model.plotOn(xframe, LineWidth(2),Range("signal_gaus"), LineColor(kRed));

    model.paramOn(xframe,
            Layout(0.15, 0.4, 0.9),
            Format("NEU", AutoPrecision(1)));

    // Define model and fit
    // ---------------------------------------

    RooHist *hpull = xframe->pullHist();
    // hpull->SetMarkerSize(1);
    hpull->SetMarkerStyle(6);
    hpull->SetLineWidth(0);

    // Draw the frame on the canvas
    auto c1 = new TCanvas("Fit", ffit , 950, 800);
    
    TPad *pad1 = new TPad("pad1", "The pad 80 of the height", 0.0, 0.2, 1.0, 1.0);
    TPad *pad2 = new TPad("pad2", "The pad 20 of the height", 0.0, 0.05, 1.0, 0.25);
    pad1->Draw();
    pad2->Draw();
    pad1->cd();

    xframe->GetYaxis()->SetTitleOffset(1.5);
    xframe->GetXaxis()->SetTitleSize(0);
    // xframe->GetXaxis()->SetLabelSize(0);
    //  xframe->GetXaxis()->SetTitleOffset(999);
    xframe->SetMinimum(0.001);
    xframe->Draw();

    pad2->cd();
    pad2->SetBottomMargin(0.4);

    hpull->GetYaxis()->SetNdivisions(6);
    hpull->GetXaxis()->SetTitleOffset(1.3);
    hpull->GetYaxis()->SetTitle("Pull");
    hpull->GetXaxis()->SetTitle("Energy [a.u.]");
    hpull->GetXaxis()->SetLabelFont(43);
    hpull->GetXaxis()->SetRangeUser(min, max);
    hpull->GetXaxis()->SetLabelSize(21);
    hpull->GetYaxis()->SetLabelFont(43);
    hpull->GetYaxis()->SetLabelSize(21);
    hpull->GetXaxis()->SetTitleSize(21);
    hpull->GetXaxis()->SetTitleFont(43);
    hpull->GetYaxis()->SetTitleSize(21);
    hpull->GetYaxis()->SetTitleFont(43);
    hpull->SetTitle("");
    hpull->Draw();
    c1->Update();


    std::string tmp_fitplot = "../20 gradi/Plots/Calibrazione/Cesio/" + nameHist + "_Fit" + ".pdf";
    const char *ffit_plot = tmp_fitplot.c_str();

    c1->SaveAs(ffit_plot);
    return;
}