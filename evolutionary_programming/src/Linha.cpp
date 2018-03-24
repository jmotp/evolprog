#include "Linha.h"

Linha::Linha(int No1,int No2,float Pmax,vector<float> sensibilidades)
{
    SetNo(No1,No2);
    this->Pmax = Pmax;
    this->sensibilidades=sensibilidades;
}

Linha::~Linha()
{
    //dtor
}
