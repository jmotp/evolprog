#include "Individuo.h"

Individuo::Individuo(vector<Gerador> geradores,vector<Barramento> barramentos,vector<Linha> linhas)

{
    this->barramentos = barramentos;
    this->linhas = linhas;
    Setgeradores(geradores);
}

Individuo::Individuo()
{

}

Individuo::~Individuo()
{
    //dtor
}
