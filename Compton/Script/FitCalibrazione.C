
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

    std::string namefile = "210hertz_cal";
    std::string nameHist = "Energy_vs_rate_210";
    std::string histTitle = "Cobalto 210 Hz";
    std::string tipoFit = "CB + bkg 210";
    float min = 5200;
    float max = 7500;
    // Define Trees
    TTree *t = new TTree("t", "t");

    std::string tmp = "../Preliminari/Data/Rate/" + namefile + ".dat";
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

    
    //Calculate the area under the histogram only in the gaussian region (the option )
    Double_t area_gauss = h->Integral(h->FindFixBin(min), h->FindFixBin(max), "width" );

    std::cout << h->GetBinCenter(h->FindFixBin(min)) << std::endl;
    std::cout << h->GetBinWidth(h->FindFixBin(min)) << std::endl;
    std::cout <<  h->GetBinCenter(h->FindFixBin(max)) << std::endl;
    std::cout << h->GetBinWidth(h->FindFixBin(max)) << std::endl;
    std::cout << "Area under the histogram in the gaussian region:" << area_gauss << std::endl;

    auto *c = new TCanvas("c", "Spettro", 800, 700);
    h->Draw();
    h->DrawClone();

    std::string tmp_name = "../Preliminari/picchiVSrate/Plots/" + nameHist + ".pdf";
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

    RooRealVar a0("a0", "a0", bg, 0., 3000.);
    RooRealVar a1("a1", "a1", slp, -5000., 0.);
    //RooRealVar a2("a2", "a2", 0, -300., 300.);
    RooPolynomial bkg("bkg", "Background", x, RooArgSet(a0, a1));

    RooRealVar mean1("mean1", "mean of gaussians", 5950,5500 , 6500);
    RooRealVar sigma1("sigma1", "width of gaussians", 350, 80, 600);
    RooRealVar alpha_up1("alpha_up1","alpha_up",1,0,10);
    RooRealVar n_up1("n_up1","n_up",1,0,10);
    
    RooRealVar fsig1("fsig1", "signal1", 0.8, 0.01, 1.);

    RooRealVar mean2("mean2", "mean of gaussians", 6650,6400 , 6900);
    RooRealVar sigma2("sigma2", "width of gaussians", 350, 80, 600);
    RooRealVar alpha_up2("alpha_up2","alpha_up",1,0,10);
    RooRealVar n_up2("n_up2","n_up",1,0,10);
    
    RooRealVar fsig2("fsig2", "signal1", 0.8, 0.01, 1.);

    RooGaussian sig_gaus1("sig1", "Gaussian signal component", x, mean1, sigma1);
    RooCBShape sig_cb1("cb1","crystal ball PDF",x,mean1,sigma1,alpha_up1,n_up1);
    RooGaussian sig_gaus2("sig2", "Gaussian signal component", x, mean2, sigma2);
    RooCBShape sig_cb2("cb2","crystal ball PDF",x,mean2,sigma2,alpha_up2,n_up2);

    //x.setRange("signal_gaus", 2600., 3000.);
    
    //RooAddPdf model("model_gaus", "Gaussian model", RooArgList(sig_gaus1, sig_gaus2, bkg), RooArgList(fsig1,fsig2), kTRUE);
    
    RooAddPdf model("model_cb", "Crystal Ball model", RooArgList(sig_cb1,sig_cb2,bkg), RooArgList(fsig1,fsig2),kTRUE);

    RooFitResult *fitResult = model.fitTo(rh,RecoverFromUndefinedRegions(1), Verbose(false), Warnings(false), Save(), PrintEvalErrors(-1), PrintLevel(-1));
    
    fitResult->Print("v");



    std::string tmp_fit = histTitle + " Fit";
    const char *ffit = tmp_fit.c_str();

    RooPlot *xframe = x.frame(Title(ffit));

    // Plot data and PDF overlaid
    rh.plotOn(xframe, MarkerStyle(6), MarkerSize(1));

    // Overlay the background component of model with a dashed line
    model.plotOn(xframe, Components(bkg), LineColor(41), LineStyle(kDashed));
    // Overlay the sig1 components of model with a dashed-dotted line
    model.plotOn(xframe, Components(sig_cb1), LineColor(46), LineStyle(8));
    model.plotOn(xframe, Components(sig_cb2), LineColor(30), LineStyle(9));

    model.plotOn(xframe, LineWidth(2), LineColor(kRed));

    model.paramOn(xframe,
            Layout(0.72, 0.9, 0.9),
            Format("NEU", AutoPrecision(1)));

    // Define model and fit
    // ---------------------------------------
    xframe->getAttText()->SetTextSize(0.028);
    xframe->getAttText()->SetTextFont(42);
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


    std::string tmp_fitplot = "../Preliminari/picchiVSrate/Plots/" + tipoFit + "_Fit" + ".pdf";
    const char *ffit_plot = tmp_fitplot.c_str();

    c1->SaveAs(ffit_plot);
    
    return;
}