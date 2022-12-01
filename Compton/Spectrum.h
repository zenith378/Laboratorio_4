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


void Spectrum(){
  TTree *cesio = new TTree("cesio","cesio");
  TTree *cobalto = new TTree("cobalto","cobalto");
  TTree *sodio = new TTree("sodio","sodio");
  TTree *stronzio = new TTree("stronzio","stronzio");

  cesio->ReadFile("Data/cesio137.dat", "x");
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
  TH1D *h_cesio = new TH1D("h_cesio","E Cesium Spectrum;Energy;Counts", nbins,0.,nbins);
  TH1D *h_cobalto = new TH1D("h_cobalto","E Cobalt Spectrum;Energy;Counts", nbins,0.,nbins);
  TH1D *h_sodio = new TH1D("h_sodio","E Sodium Spectrum;Energy;Counts", nbins,0.,nbins);
  TH1D *h_stronzio = new TH1D("h_stronzio","E Strontium  Spectrum;Energy;Counts", nbins,0.,nbins);
  for (Int_t i=0;i<nbins;i++){
    cesio->GetEntry(i);
 
    h_cesio->SetBinContent(i,v_cesio);
    
    cobalto->GetEntry(i);

    h_cobalto->SetBinContent(i,v_cobalto);
    
    sodio->GetEntry(i);

    h_sodio->SetBinContent(i,v_sodio);

    stronzio->GetEntry(i);

    h_stronzio->SetBinContent(i,v_stronzio);

  }
  h_cesio->Rebin(3);
  h_cobalto->Rebin(3);
  h_sodio->Rebin(3);
  //h_stronzio->Rebin(3);
  auto *c_cesio = new TCanvas("c_cesio", "", 800, 700);
  h_cesio->Draw();
  c_cesio->SaveAs("Plots/spettro_Cesio.pdf");

  auto *c_cobalto = new TCanvas("c_cobalto", "", 800, 700);
  h_cobalto->Draw();
  c_cobalto->SaveAs("Plots/spettro_cobalto.pdf");

  auto *c_sodio = new TCanvas("c_sodio", "", 800, 700);
  h_sodio->Draw();
  c_sodio->SaveAs("Plots/spettro_sodio.pdf");

  auto *c_stronzio = new TCanvas("c_stronzio", "", 800, 700);
  h_stronzio->Draw();
  c_stronzio->SaveAs("Plots/spettro_stronzio.pdf");

}

#endif