#include "TTree.h"
#include "TH1D.h"
#include <stdio.h>
#include "TCanvas.h"
#include "TAxis.h"
#include "TStyle.h"
#include <string.h>
#include <filesystem>

void Spettro()
{

    std::string namefile = "13dicembre20gradi";
    std::string nameHist = "20_gradi_spettro";
    std::string histTitle = "Spettro 20 gradi";
    float min = 2000;
    float max = 6500;
    // Define Trees
    TTree *t = new TTree("t", "t");

    std::string tmp = "../20 gradi/Data/" + namefile + ".dat";
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

    auto *c = new TCanvas("c", "Spettro", 800, 700);
    h->Draw();
    h->DrawClone();

    std::string tmp_name = "../20 gradi/Plots/Spettro/" + nameHist + ".pdf";
    const char *ffile = tmp_name.c_str();

    c->SaveAs(ffile);
}