//
//  Spectrum.h
//
//
//  Created by Giulio Cordova on 29/11/22.
//
//

#ifndef Spectrum_h
#define Spectrum_h

#include "TTree.h"
#include "TH1D.h"
#include <stdio.h>


TH1D* Spectrum(std::string namefile, std::string nameHist, std::string histTitle,float min, float max){

  //Define Trees
  TTree *t= new TTree("t","t");


  std::string tmp = "../Data/" + namefile + ".dat";
  const char *fname = tmp.c_str();

  t->ReadFile(fname, "x");



  Int_t nbins = t->GetEntries();
  Float_t v_t;

  t->SetBranchAddress("x", &v_t);

  TH1D *h = new TH1D("h",histTitle.c_str(), nbins,0.,nbins);

  for (Int_t i=0;i<nbins;i++){
    t->GetEntry(i);
 
    h->SetBinContent(i,v_t);
  
  }
  h->Rebin(25);
  h->GetXaxis->SetRangeUser(min, max)


  auto *c = new TCanvas("c", "Spettro", 800, 700);
  h->Draw();
  h->DrawClone();

  std::string tmp = "../Plots/Calibrazione/" + nameHist + ".pdf";
  const char *ffile = tmp.c_str();

  c->SaveAs(ffile);

  return h;
}

#endif