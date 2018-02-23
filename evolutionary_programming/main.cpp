#include <iostream>
#include "Gerador.h"
#include "Individuo.h"
#include <chrono>
#include <random>
using namespace std;


void print(vector<Individuo> individuos){
    cout << "  G1 G2 G3 G4"<<endl;
    for(auto & i : individuos){

        i.print();
    }
}

void mutar(vector<Individuo> & individuos,float sigma,default_random_engine generator, normal_distribution<double> distribution){
    for(auto & i : individuos){

        i.mutar(sigma,generator,distribution);
    }
}

int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(0,1);
    float sigma =5;
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
        ind.fill();
        individuos.push_back(ind);
    }
    print(individuos);
    vector <Individuo> clone;
    clone = individuos;
    cout << "Matriz pais"<< endl;
    print(individuos);
    cout << "Matriz filhos" << endl;
    print (clone);
    mutar(clone,sigma,generator,distribution);
    cout << "Matriz pais"<< endl;
    print(individuos);
    cout << "Matriz filhos" << endl;
    print (clone);

    return 0;
}
