#include "Gerador.h"



Gerador::Gerador(int Pmax,int Pmin,float costa,float costb,float costc )
{
    SetPmax(Pmax);
    SetPmin(Pmin);
    Setcosta(costa);
    Setcostb(costb);
    Setcostc(costc);
    //ctor
}

Gerador::Gerador(){
};

Gerador::~Gerador()
{
    //dtor
}
