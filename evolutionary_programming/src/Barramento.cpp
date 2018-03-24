#include "Barramento.h"
#include <vector>
#include "Gerador.h"
#include "Carga.h"
Barramento::Barramento(vector<Gerador> G,Carga & C)
{
    Setgerador(G);
    Setcarga(C);
    //ctor
}

Barramento::~Barramento()
{
    //dtor
}
