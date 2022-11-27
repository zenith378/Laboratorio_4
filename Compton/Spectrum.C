#include "TTree.h"
#include "TH1D.h"
#include <stdio.h>


void Spectrum(){
  TTree *t = new TTree("t","t");
  t->ReadFile("Data/gate30.dat", "x");
  Int_t nbins = t->GetEntries();
  Float_t variable;
  t->SetBranchAddress("x", &variable);
  TH1D *h = new TH1D("h1","E Spectrum;Energy;Counts", nbins,0.,nbins);
  for (Int_t i=0;i<nbins;i++){
    t->GetEntry(i);
    //std::cout<< e <<endl;
    //printf("%f\n", variable);
    h->SetBinContent(i,variable);
  }
  h->Draw();
}