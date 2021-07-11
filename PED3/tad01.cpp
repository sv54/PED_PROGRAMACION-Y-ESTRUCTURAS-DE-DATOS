
#include <iostream>
#include "tavlcalendario.h"
#include "tlistacalendario.h"
#include "tabbcalendario.h"
#include "tvectorcalendario.h"
#include "tcalendario.h"


using namespace std;

int
main()
{
    TABBCalendario arb1, arb2;
    TVectorCalendario vec, vec2;
    TListaCalendario l1;

    TCalendario c1(20, 1, 2011, (char*)"");
    TCalendario c2(10, 1, 2011, (char*)"");
    TCalendario c3(30, 1, 2011, (char*)"");
    TCalendario c4(5, 1, 2011, (char*)"");
    TCalendario c5(15, 1, 2011, (char*)"");
    TCalendario c6(22, 1, 2011, (char*)"");
    TCalendario c7(25, 1, 2011, (char*)"");
    TCalendario c8(24, 1, 2011, (char*)"");
    TCalendario c9(26, 1, 2011, (char*)"");
    TCalendario c10(3, 1, 2011, (char*)"");

    TCalendario cal1(21, 1, 2011, (char*)"");
    TCalendario cal2(22, 1, 2011, (char*)"");
    TCalendario cal3(31, 1, 2011, (char*)"");

    arb1.Insertar(c1);
    arb1.Insertar(c2);
    arb1.Insertar(c3);
    arb1.Insertar(c4);
    arb1.Insertar(c5);
    arb1.Insertar(c6);
    arb1.Insertar(c7);
    arb1.Insertar(c8);
    arb1.Insertar(c9);
    arb1.Insertar(c10);

    //cout << arb1.Niveles()<<endl;


    l1.Insertar(cal1);
    l1.Insertar(cal2);
    l1.Insertar(cal3);

    vec=arb1.ABBCamino(l1);
    //cout << arb1.Niveles() << endl;
    //cout << l1<<endl;
    cout << vec << endl;


    return 0;
}
