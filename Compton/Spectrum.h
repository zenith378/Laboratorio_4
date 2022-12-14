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


TH1D* Spectrum(){

  //Define Trees
  TTree *t= new TTree("cesio","cesio");


  //
  t->ReadFile("./Data/cesio1dicembre.dat", "x");



  Int_t nbins = t->GetEntries();
  Float_t v_t;

  t->SetBranchAddress("x", &v_t);

  TH1D *h = new TH1D("h","E Spectrum Compton (22 degree) quat;Energy;Counts", nbins,0.,nbins);

  for (Int_t i=0;i<nbins;i++){
    t->GetEntry(i);
 
    h->SetBinContent(i,v_t);
  
  }
  h->Rebin(25);


  auto *c = new TCanvas("c", "Spettro 30 gradi", 800, 700);
  h->Draw();
  h->DrawClone();
  c->SaveAs("Plots/spettro_22quat.pdf");

  return h;
}

#endif