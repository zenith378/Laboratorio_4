#include "Spectrum.h"
#include "fitg.h"
#include "fitg_stronzio.h"

int prova(){
    Spectrum();
    fitg("h_cesio",2900,4200);
    //c1->SaveAs("fit_Cesio.pdf");

    //fitg("h_cobalto",2900,4200);
    //c1->SaveAs("fit_Cobalto.pdf");

    fitg("h_sodio",2400,3000);
    //c1->SaveAs("fit_sodio.pdf");

    fitg_stronzio("h_stronzio",100,3000);
    //c1->SaveAs("fit_stronzio.pdf");

    return 0;
}
