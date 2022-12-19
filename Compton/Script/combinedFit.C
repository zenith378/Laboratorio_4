//+ Combined (simultaneous) fit of two histogram with separate functions 
//  and some common parameters
//
// See http://root.cern.ch/phpBB3//viewtopic.php?f=3&t=11740#p50908
// for a modified version working with Fumili or GSLMultiFit 
//
// N.B. this macro must be compiled with ACliC 
//
//Author: L. Moneta - Dec 2010

#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "Fit/Chi2FCN.h"
#include "TH1.h"
#include "TF1.h"
#include "TList.h"
#include "Math/WrappedMultiTF1.h"
#include "HFitInterface.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TGraph.h"
#include "TRandom.h"

// definition of shared parameter
// background function 
int iparB1[4] = { 0,      // initial energy
                    1,
                 2,    // mass common parameter
                3      // theta init common
                };

// signal + background function 
int iparB2[4] = {0, 1, // initial energy
                  2, // mass common parameter
                3   // theta init common
};

struct GlobalChi2 { 
   GlobalChi2(  ROOT::Math::IMultiGenFunction & f1,  
                ROOT::Math::IMultiGenFunction & f2) : 
      fChi2_1(&f1), fChi2_2(&f2) {}

   // parameter vector is first background (in common 1 and 2) 
   // and then is signal (only in 2)
   double operator() (const double *par) const {
      double p1[4];
      for (int i = 0; i < 4; ++i) p1[i] = par[iparB1[i] ];

      double p2[4]; 
      for (int i = 0; i < 4; ++i) p2[i] = par[iparB2[i] ];

      return (*fChi2_1)(p1) + (*fChi2_2)(p2);
   } 

   const  ROOT::Math::IMultiGenFunction * fChi2_1;
   const  ROOT::Math::IMultiGenFunction * fChi2_2;
};

Double_t compton_low(Double_t * x, Double_t * par){
    Double_t E_peak = par[0];
    Double_t m_e = par[2];
    Double_t theta_rad = (x[0]-par[3]) * 3.14159 / 180;
    return E_peak / (1 + (E_peak / m_e) * (1 - TMath::Cos(theta_rad)));
}

Double_t compton_high(Double_t * x, Double_t * par){
    Double_t E_peak = par[1];
    Double_t m_e = par[2];
    Double_t theta_rad = (x[0]-par[3]) * 3.14159 / 180;
    return E_peak / (1 + (E_peak / m_e) * (1 - TMath::Cos(theta_rad)));
}

Double_t compton_low_1(Double_t * x, Double_t * par){
    Double_t E_peak = par[0];
    Double_t m_e = par[2];
    Double_t theta_rad = (x[0]-par[3]) * 3.14159 / 180;
    return E_peak / (1 + (E_peak / m_e) * (1 - TMath::Cos(theta_rad)));
}

Double_t compton_high_1(Double_t * x, Double_t * par){
    Double_t E_peak = par[1];
    Double_t m_e = par[2];
    Double_t theta_rad = (x[0]-par[3]) * 3.14159 / 180;
    return E_peak / (1 + (E_peak / m_e) * (1 - TMath::Cos(theta_rad)));
}

void combinedFit(){ 
    Double_t E_low[] = {0.7, 0.649, 0.625};
    Double_t dE_low[] = {0.0051, 0.0043, 0.0054};
    Double_t E_high[] = {1.0451, 0.997, 0.940};
    Double_t dE_high[] = {0.0057, 0.0051, 0.0057};
    Double_t th[] = {15,20,25};
    Double_t dth[] = {2, 2, 2};
    Double_t E_peaklow = 1.173240, E_peakhigh = 1.332508;

  
  //TH1D * hB1 = new TH1D("hB1","histo B1",100,0,100);
  //TH1D * hB2 = new TH1D("hB2","histo B2",100, 0,100);

  TF1 * fB1 = new TF1("fB1",compton_low,0,45);
  TF1 * fB2 = new TF1("fB2",compton_high,0,45);
    fB1->SetParNames("E_{in1}","E_{in2}", "m_{e}","#theta_{0}");
    fB2->SetParNames("E_{in1}","E_{in2}", "m_{e}","#theta_{0}");

  fB1->SetParameters(E_peaklow,E_peakhigh,0.5,3);
  fB2->SetParameters(E_peaklow,E_peakhigh,0.5,3);
  
  //hB1->FillRandom("fB1",2000);
  //hB2->FillRandom("fB1",2000);
  TGraphErrors * gb1 = new TGraphErrors(3,th, E_low,dth, dE_low);
  TGraphErrors * gb2 = new TGraphErrors(3,th, E_high,dth, dE_high);
    
    TF1 * ffitB1 = new TF1("ffitB1",compton_low_1,0,45,1);
  TF1 * ffitB2 = new TF1("ffitB2",compton_high_1,0,45,1); 
  
  ROOT::Math::WrappedMultiTF1 wfB1(*ffitB1,3);
  ROOT::Math::WrappedMultiTF1 wfB2(*ffitB2,3);

  ROOT::Fit::DataOptions opt; 
  ROOT::Fit::DataRange rangeB1; 
  ROOT::Fit::DataRange rangeB2; 
 
  // set the data range
  rangeB1.SetRange(0,45);
  rangeB2.SetRange(0,45);
 
  ROOT::Fit::BinData dataB1(opt,rangeB1); 
  ROOT::Fit::BinData dataB2(opt,rangeB2); 
 
  ROOT::Fit::FillData(dataB1, gb1);
  ROOT::Fit::FillData(dataB2, gb2);

 
  ROOT::Fit::Chi2Function chi2_B1(dataB1, wfB1);
  ROOT::Fit::Chi2Function chi2_B2(dataB2, wfB2);

  GlobalChi2 globalChi2(chi2_B1, chi2_B2);

  ROOT::Fit::Fitter fitter;

  const int Npar = 4; 
  double par0[Npar] = {E_peaklow,E_peakhigh,0.5,3};

  // create before the parameter settings in order to fix or set range on them
  fitter.Config().SetParamsSettings(4,par0);
  // fix parameter  
  fitter.Config().ParSettings(0).Fix();
  fitter.Config().ParSettings(1).Fix();
  // set limits
  fitter.Config().ParSettings(2).SetLimits(0.4,0.8);
  fitter.Config().ParSettings(3).SetLimits(-10,10);

  fitter.Config().MinimizerOptions().SetPrintLevel(0);
  fitter.Config().SetMinimizer("Minuit","Minimize"); 

  // fit FCN function directly 
  // (specify optionally data size and flag to indicate that is a chi2 fit)
  fitter.FitFCN(4,globalChi2,0,dataB1.Size()+dataB2.Size(),true);
  ROOT::Fit::FitResult result = fitter.Result();
  result.Print(std::cout);

  TCanvas * c1 = new TCanvas("Simfit","Simultaneous fit of two graphs",
                             10,10,700,700);
  c1->Divide(1,2);
  c1->cd(1);
  gStyle->SetOptFit(1111);

  ffitB1->SetFitResult(result, iparB1);
  //fB1->SetRange(rangeB1().first, rangeB1().second);   
  ffitB1->SetLineColor(kBlue);
  gb1->GetListOfFunctions()->Add(ffitB1);
  gb1->Draw("alp"); 
// 
  c1->cd(2);
  fB2->SetFitResult( result, iparB2);
  //fB2->SetRange(rangeB2().first, rangeB2().second);   
  ffitB2->SetLineColor(kRed);
  gb2->GetListOfFunctions()->Add(ffitB2);
  gb2->Draw("alp"); 

}