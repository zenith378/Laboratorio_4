
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

void FitSpettro()
{
    std::string folder ="25 gradi";
    std::string namefile = "15dicembre25gradi";
    std::string nameHist = "25_gradi_spettro";
    std::string histTitle = "Spettro 25 gradi";
    float min = 2000;
    float max = 8192;
    // Define Trees
    TTree *t = new TTree("t", "t");

    std::string tmp = "../"+folder+"/Data/" + namefile + ".dat";
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
    h->Rebin(25);
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

    std::string tmp_name = "../"+folder+"/Plots/" + nameHist + ".pdf";
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


    //15 gradi: 3200, 3400, 4000
    //25 gradi: 3200
    //17 cm: 5400, 5300, 6000
    //22 cm: 5400, 5300, 6000
    //27 cm: 5400, 5300, 6000
    //32 cm: 4400, 4300, 5000
    //37 cm: 4400, 4600, 5000
    RooRealVar mean1("mean1", "mean of gaussians", 5400,5300 , 6000);

    //15 gradi: 1300, 800, 2000
    //25 gradi: 1028
    //17 cm: 1500, 800, 2000
    //22 cm: ""
    //27 cm:""
    //32 cm: ""
    //37 cm: ""
    RooRealVar sigma1("sigma1", "width of gaussians",1500 , 800, 2000);
    
    //15 gradi: 5000, 4900,5250
    //25 gradi: 4821
    //17 cm; 6050, 5900, 6200
    //22 cm: 6015, 5900, 6200
    //27 cm; 5990,5800 , 6200
    //32 cm: 5960,5800 , 6100
    //37 cm: 5930, 5800, 6100
    RooRealVar mean2("mean2", "mean of gaussians", 5990,5800 , 6200);

    //15 gradi: 100,100,800
    //25 gradi: 348
    RooRealVar sigma2("sigma2", "width of gaussians", 100, 100, 800);
    
    //15 gradi: 5600, 5400, 6000
    //25 gradi: 5489
    //17 cm: 6830, 6600, 7000
    //22 cm: 6780, 6600, 7000
    //27 cm: ""
    //32 cm: 6750,6600 , 7000
    //37 cm: 6670, 6500, 6900
    RooRealVar mean3("mean3", "mean of gaussians", 6780,6600 , 7000);


    //25 gradi: 225
    RooRealVar sigma3("sigma3", "width of gaussians", 100, 100, 800);
    
    RooRealVar alpha_up("alpha_up","alpha_up",1,0,10);
    RooRealVar n_up("n_up","n_up",1,0,10);
    
    RooRealVar fsig1("fsig1", "signal1", 0.74, 0., 1.);
    RooRealVar fsig2("fsig2", "signal1", 0.79, 0., 1.);
    RooRealVar fsig3("fsig3", "signal1", 0.5, 0., 1.);

    RooGaussian spalla("spalla", "Spalla Compton", x, mean1, sigma1);
    RooGaussian peak1("peak1", "Primo Picco", x, mean2, sigma2);
    RooGaussian peak2("peak2", "Secondo Picco", x, mean3, sigma3);

    //15 gradi: 3200-6500
    //17 cm: 5400-7500
    //22 cm: ""
    //27 cm: ""
    //32 cm: 5400-7500
    //37 cm: 5500-7500
    x.setRange("signal_gaus", 5400, 7500);
    
    RooAddPdf model("model", "Gaussian model", RooArgList(spalla,peak1,peak2), RooArgList(fsig1,fsig2),kTRUE);
    
    //RooAddPdf model("model_cb", "Crystal Ball model", RooArgList(sig_cb, bkg), RooArgList(fsig1),kTRUE);

    RooFitResult *fitResult = model.fitTo(rh, Range("signal_gaus"),RecoverFromUndefinedRegions(1), Verbose(false), Warnings(false), Save(), PrintEvalErrors(-1), PrintLevel(-1));
    
    fitResult->Print("v");



    std::string tmp_fit = histTitle + " Fit";
    const char *ffit = tmp_fit.c_str();

    RooPlot *xframe = x.frame(Title(ffit));

    // Plot data and PDF overlaid
    rh.plotOn(xframe, MarkerStyle(6), MarkerSize(1));

    // Overlay the background component of model with a dashed line
    model.plotOn(xframe, Components(spalla),Range("signal_gaus"), LineColor(41), LineStyle(kDashed));
    // Overlay the sig1 components of model with a dashed-dotted line
    model.plotOn(xframe, Components(peak1),Range("signal_gaus"), LineColor(46), LineStyle(8));
    model.plotOn(xframe, Components(peak2),Range("signal_gaus"), LineColor(30), LineStyle(9));

    model.plotOn(xframe, LineWidth(2),Range("signal_gaus"), LineColor(kRed));

    double chi2 = xframe->chiSquare(); 
    TString chi2Line = TString::Format("Chi^2 = %f ",chi2); //  

    RooArgSet display(mean1,sigma1,mean2,sigma2,mean3,sigma3);
    model.paramOn(xframe,
            Parameters(display),
            Layout(0.25, 0.2, 0.58),
            Format("NE", AutoPrecision(1)),
            Label(chi2Line)
            );

    // Define model and fit
    // ---------------------------------------
    xframe->getAttText()->SetTextSize(0.031);
    xframe->getAttText()->SetTextFont(42);

    RooHist *hpull = xframe->pullHist();
    // hpull->SetMarkerSize(1);
    hpull->SetMarkerStyle(6);
    hpull->SetLineWidth(0);

    // Draw the frame on the canvas
    auto c1 = new TCanvas("Fit", ffit , 950, 800);
    
    TPad *pad1 = new TPad("pad1", "The pad 80 of the height", 0.0, 0.2, 1.0, 1.0);
    TPad *pad2 = new TPad("pad2", "The pad 20 of the height", 0.167, 0.05, 0.985, 0.25);
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


    std::string tmp_fitplot = "../"+folder+"/picchiVSrate/Plot/" + nameHist + "_Fit" + ".pdf";
    const char *ffit_plot = tmp_fitplot.c_str();

    c1->SaveAs(ffit_plot);
    return;
}