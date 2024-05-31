#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>

#include <stdio.h>
#include "GUI.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    parcare prc;
    file_parcare prc2;
    service srv{ prc, prc2 };
    srv.adauga_srv("BC06DSK", "Ducati", "Panigale_V4", "Sport");
    srv.adauga_srv("CJ90CBV", "BMW", "S1000RR", "SporT");
    srv.adauga_srv("CJ98JHV", "BMW", "A1000R", "Sport");
    srv.adauga_srv("BC12KJF", "Ducati", "AA", "Naked");
    srv.adauga_srv("SV12ASF", "Honda", "FireBlade", "Sport");
    srv.adauga_srv("VS23DAF", "Toyota", "Corola", "Sedan");
    srv.adauga_srv("VS23UYD", "Dacia", "MCV", "Break");
    srv.adauga_srv("CT23AZD", "Dacia", "Logan", "Br");
    srv.adauga_srv("CT12ASD", "Dacia", "Logan", "ABC");
    srv.adauga_srv("BN12ASD", "Dacia", "Logan GPL", "Patrick");
    parcare_gui gui{ srv };
    gui.show();

    return a.exec();

}