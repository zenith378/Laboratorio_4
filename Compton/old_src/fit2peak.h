//
//  fit2peak.h
//
//
//  Created by Giulio Cordova on 29/11/22.
//
//

#ifndef fit2peak_h
#define fit2peak_h

#include "TDirectory.h"
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
//#include "TLegend.h"
//#include "TCanvas.h"
#include "TStyle.h"
#include "TFitResult.h"
#include "TMatrixD.h"


Double_t lorentzianPeak(Double_t *x, Double_t *par) {
    /*Definitin of the lorentzian function:
     par[0] is the area
     par[1] is FWHWM
     par[2] is the mean*/
    return (0.5*par[0]*par[1]/TMath::Pi()) / TMath::Max(1.e-10,(x[0]-par[2])*(x[0]-par[2])+ .25*par[1]*par[1]);
}

Double_t gaussianPeak(Double_t *x, Double_t *par) {
    /*Definitin of the gaussian function:
     par[0] is the area
     par[1] is the mean
     par[2] is the FWHM*/
    return par[0]*exp(-0.5* ((x[0]-par[1])/par[2]) * ((x[0]-par[1])/par[2])); //(par[2] *TMath::Sqrt(2*TMath::Pi()));
}

// quadratic background function
Double_t background(Double_t *x, Double_t *par) {
    /*Definitin of a p2 function:
     par[0] is theheight at the origin
     par[1] is the slope
     par[2] is the curv */
    return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

// Sum of background and two peaks function
Double_t fitfunction(Double_t *x, Double_t *par) {
    return background(x,par)+ gaussianPeak(x,&par[3]) + gaussianPeak(x, &par[6]);
    
}

//----------------------------------------------------------------------
TFitResultPtr fit2peak( string hs, double x1=1, double x9=0 )
{
    TH1 *h = (TH1*)gDirectory->Get( hs.c_str() ); // perché quaggiù non passiamo fare direttamente l'istogramma anziché la stringa?

    if( h == NULL ){
        cout << hs << " does not exist\n";
        return nullptr;
    }
    
    //Style histogramm
    h->SetMarkerStyle(21);
    h->SetMarkerSize(0.2);
    h->SetStats(1);
    
    //Style legend
    gStyle->SetOptFit(101);
    gStyle->SetStatX(0.95); // right edge
    gStyle->SetStatY(0.95); // top edge
    gStyle->SetStatW(0.15); // width
    gStyle->SetStatH(0.15); // height

    //gROOT->ForceStyle();

    //inizializzazione parametri
    //bin's width
    double bwt2 = h->GetBinWidth(1);
    //bins' number
    int nb = h->GetNbinsX();
    //if you don't give the extreme of the fit the fit will be done on all the width of the histogram
    if( x9 < x1 ) {
        x1 = h->GetBinCenter(1);
        x9 = h->GetBinCenter(nb);
    }
    //index of the bins who set the range
    int i1 = h->FindBin(x1);
    int i9 = h->FindBin(x9);
    //occurencies at the border of the range
    double n1 = h->GetBinContent(i1);
    double n9 = h->GetBinContent(i9);
    //mean between the occurencies at the border -->we have to find a better implementatio (we are far away from the y axis)
    double bg = 0.5*(n1+n9);
    double slp = (n9-n1)/(x9-x1);

    // find peak in boundaries:

    double npk = bg;
    double xpk = 0.5*(x1+x9);

    double xhwhm = x1;

    for( int ii = i1; ii <= i9; ++ii ) {
        if( h->GetBinContent(ii) > npk ) {
            npk = h->GetBinContent(ii);
            xpk = h->GetBinCenter(ii);
        }
        if( h->GetBinContent(ii)-bg > 0.5*(npk-bg) )
        xhwhm = h->GetBinCenter(ii); // overwritten until right flank

    }


    double sm = 2*(xhwhm-xpk);
    double aa = 2.5 * ( npk - bg ) * sm / bwt2;

    cout << hs << ": " << x1 << " - " << x9 << endl;

    cout << hs << ": xpk=" << xpk << ", xhwhm=" << xhwhm << ", sm=" << sm << endl;

    cout << hs << ": bwt2=" << bwt2 << ", npk=" << npk << ", aa=" << aa << endl;

    // create a TF1 with the range from x1 to x9 and 9 parameters

    TF1 *lp2Fcn = new TF1( "lp2Fcn", fitfunction, x1, x9, 9 );

    lp2Fcn->SetParName( 0, "BG" );
    lp2Fcn->SetParName( 1, "slope" );
    lp2Fcn->SetParName( 2, "curv" );
    lp2Fcn->SetParName( 3, "norm1");
    lp2Fcn->SetParName( 4, "mean1" );
    lp2Fcn->SetParName( 5, "sigma1" );
    lp2Fcn->SetParName( 6, "norm2");
    lp2Fcn->SetParName( 7, "mean2" );
    lp2Fcn->SetParName( 8, "sigma2" );

    
    double nm1=500;
    double nm2=400;
    double me1=6200;
    double me2=7150;
    double sig1=300;
    double sig2=200;
    
    // set start values for some parameters:
    lp2Fcn->SetParameter( 0, bg );
    lp2Fcn->SetParameter( 1, slp );
    lp2Fcn->SetParameter( 2, 0 );
    lp2Fcn->SetParameter( 3, nm1 );//area 5e6 //norm
    lp2Fcn->SetParameter( 4,me1 );//FWHM // mean
    lp2Fcn->SetParameter( 5, sig1 );//mean // sigma
    lp2Fcn->SetParameter( 6, nm2 );
    lp2Fcn->SetParameter( 7, me2 );
    lp2Fcn->SetParameter( 8, sig2 );


    lp2Fcn->SetLineWidth(4);
    lp2Fcn->SetNpx(500);
    lp2Fcn->SetLineColor(kMagenta);
    lp2Fcn->Draw("same");
    
    lp2Fcn->SetLineColor(kBlue);
    TFitResultPtr r = h->Fit("lp2Fcn", "RS", "ep" );
    
    // h->Fit("tp2Fcn","V+","ep");

    cout << "Ndata = " << lp2Fcn->GetNumberFitPoints() << endl;
    cout << "Npar  = " << lp2Fcn->GetNumberFreeParameters() << endl;
    cout << "NDoF  = " << lp2Fcn->GetNDF() << endl;
    cout << "chisq = " << lp2Fcn->GetChisquare() << endl;
    cout << "prob  = " << lp2Fcn->GetProb() << endl;

    ///*
    auto c1 = new TCanvas("c", "", 800, 700);
    //c1->SetLogx();
    //c1->SetLogy();//*/
    
    // data points on top:
    h->Draw("histpesame");
    
    //TMatrixD cor = r->GetCorrelationMatrix();
    //TMatrixD cov = r->GetCovarianceMatrix();
    //cov.Print();
    //cor.Print();
    
    lp2Fcn->Draw("same");
    c1->SaveAs("fit_Cobalto.pdf");
    return r;

}

//TFitResultPtr fitlp2( string hs, double x1=1, double x9=0 );//esecuzione fit

#endif /* fitlp2_h */
