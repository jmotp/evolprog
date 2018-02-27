#include <iostream>
#include "Gerador.h"
#include "Individuo.h"
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;


void avaliar(vector<Individuo> & individuos){
    for(auto & i : individuos){

        i.avaliar();
    }
}

void print(vector<Individuo> individuos){
    cout << "  G1 G2 G3 G4"<<endl;
    for(auto & i : individuos){

        i.print();
    }
}

void printCusto(vector<Individuo> individuos){
    cout << "  G1 G2 G3 G4"<<endl;
    for(auto & i : individuos){

        i.printCusto();
    }
}

void mutar(vector<Individuo> & individuos,float sigma,default_random_engine generator, normal_distribution<double> distribution){
    for(auto & i : individuos){

        i.mutar(sigma,generator,distribution);
    }
}

vector<Individuo> m_elitista(int Pop,vector<Individuo> & pais){
    vector<Individuo> final;
    for( int i = 0 ; i < Pop; i++){
        float min = 1e16;
        min_element(pais.begin(),pais.end());

    }
}

void corrigir(vector<Individuo> & individuos, vector<Individuo> & clone){
    for( int i = 0 ; i < individuos.size();i++){
        clone.at(i).corrigir(clone.at(i).sumPcons(),individuos.at(i).sumPcons());
    }

}

vector<Individuo> geracao(int Pop,float sigma ,default_random_engine generator, normal_distribution<double> distribution, vector <Individuo> & pais, vector <Individuo> & filhos){
    filhos = pais;
    mutar(filhos,sigma,generator,distribution);
    corrigir(pais,filhos);
    avaliar(filhos);
    print(filhos);
    for (auto & i: filhos){
        pais.push_back(i);
    }
    return pais;
}


int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(0,1);
    float sigma =1;

    int Pop;
    do{
        cout << "Insira o numero de Individuos da Populacao"<< endl;
        cin >> Pop;
    }while(Pop<=0);
    vector < Gerador > geradores_ini;
    Gerador G1 = Gerador (80, 40, 1100 , 20 ,0.1);
    Gerador G2 = Gerador (60, 20 , 1200, 25, 0.07);
    Gerador G3 = Gerador (70, 30, 300, 10, 0.2);
    Gerador G4 = Gerador (60, 20, 650, 20, 0.05);
    geradores_ini.push_back(G1);
    geradores_ini.push_back(G2);
    geradores_ini.push_back(G3);
    geradores_ini.push_back(G4);
    vector <Individuo> individuos;
    for( int i = 0; i < Pop;i++){
        Individuo ind = Individuo(geradores_ini);
        cout << "Insira as potencias de carga do " << i+1 << "º Individuo"<<endl;
        ind.fill();
        individuos.push_back(ind);
    }
    avaliar(individuos);
    print(individuos);
    vector <Individuo> clone;
    print(geracao(Pop,sigma,generator,distribution,individuos,clone));
    return 0;
}
