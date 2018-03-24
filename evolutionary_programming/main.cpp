#include <iostream>
#include "Gerador.h"
#include "Individuo.h"
#include <chrono>
#include <random>
#include <algorithm>
#include "Linha.h"
#include "Carga.h"
#include "Barramento.h"
#include <fstream>
using namespace std;




void avaliar(vector<Individuo> & individuos){
    for(auto & i : individuos){

        i.avaliar();
    }
}

void print(vector<Individuo> individuos){
    cout << "G1     G2     G3     G4     Custo"<<endl;
    cout<<   "-----------------------------------"<<endl;
    for(auto & i : individuos){

        i.print();
    cout<<   "-----------------------------------"<<endl;
    }
    cout << endl;

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


void corrigir(vector<Individuo> & individuos, vector<Individuo> & clone){
    for( int i = 0 ; i < individuos.size();i++){
        clone.at(i).corrigir(clone.at(i).sumPcons(),individuos.at(i).sumPcons());
    }

}

vector<Individuo> m_elitista(vector<Individuo> & individuos,int Pop){
    vector <Individuo> aux;
    float custo_min = 1e16;
    int pos_min = 0;
    for(int j = 0 ; j < Pop ; j++){
        custo_min = 1e16;
        for(int i = 0; i < individuos.size();i++){
            //cout << individuos[i].getCustoTotal()<<endl;
            if(individuos[i].getCustoTotal()<custo_min){
                custo_min=individuos[i].getCustoTotal();
                pos_min = i;
            }

        }
        /*cout << "I : ";
        individuos[pos_min].print();
        cout << endl <<endl;*/
        aux.push_back(individuos[pos_min]);
        //cout << "E : " << individuos.at(individuos.begin()+pos_min)<< endl <<endl;

        individuos.erase(individuos.begin()+pos_min);
    }
    return aux;

}


vector<Individuo> testocastico(vector<Individuo> & individuos ,int Pop,default_random_engine generator, uniform_real_distribution<float> distribution_){
    vector <Individuo> aux;
    int n1,n2;
    for(int i = 0 ,newPop = Pop*2-1; i < Pop;i++,newPop--){
        do{
            n1 = (distribution_(generator)*newPop);
            n2 = (distribution_(generator)*newPop);
        }while(n1==n2);
        float prob = distribution_(generator);
        if(individuos.at(n1).getCustoTotal()<individuos.at(n2).getCustoTotal()){
            if(prob<0.8){
                aux.push_back(individuos.at(n1));
                individuos.erase(individuos.begin()+n1);
            }else{
                aux.push_back(individuos.at(n2));
                individuos.erase(individuos.begin()+n2);
            }
        }else{
            if(prob<0.8){
                aux.push_back(individuos.at(n2));
                individuos.erase(individuos.begin()+n2);
            }else{
                aux.push_back(individuos.at(n1));
                individuos.erase(individuos.begin()+n1);
            }
        }

    }
    return aux;

}

struct myclass {
  bool operator() (Individuo i,Individuo j) { return (i.getCustoTotal()<j.getCustoTotal());}
} compare;

vector<Individuo> geracao(int Pop,float sigma ,default_random_engine generator, normal_distribution<double> distribution, vector <Individuo> & pais, vector <Individuo> & filhos){
    filhos = pais;
    mutar(filhos,sigma,generator,distribution);
    corrigir(pais,filhos);
    avaliar(filhos);
    //print(filhos);
    for (auto & i: filhos){
        pais.push_back(i);
    }
    return pais;
}


int main()
{
    //Linhas
    vector<float> sensibilidades1 ={0.6495,-0.2062,-0.1031,0,0.3608};
    vector<float> sensibilidades2 ={0.3505,0.2062,0.1031,0,-0.3608};
    vector<float> sensibilidades3 ={0.1856,0.2268,-0.3866,0,0.1031};
    vector<float> sensibilidades4 ={0.4639,0.5670,0.2835,0,0.2577};
    vector<float> sensibilidades5 ={0.1856,0.2268,0.6134,0,0.1031};
    vector<float> sensibilidades6 ={-0.3505,-0.2062,-0.1031,0,-0.6392};


    Linha linha1 = Linha(1,2,48*0.85,sensibilidades1);
    Linha linha2 = Linha(1,5,59*0.85,sensibilidades2);
    Linha linha3 = Linha(2,3,89*0.85,sensibilidades3);
    Linha linha4 = Linha(2,4,94*0.85,sensibilidades4);
    Linha linha5 = Linha(3,4,59*0.85,sensibilidades5);
    Linha linha6 = Linha(4,5,74*0.85,sensibilidades6);
    vector<Linha> linhas;
    linhas.push_back(linha1);
    linhas.push_back(linha2);
    linhas.push_back(linha3);
    linhas.push_back(linha4);
    linhas.push_back(linha5);
    linhas.push_back(linha6);

    //cargas

    Carga carga1 = Carga(50);
    Carga carga2 = Carga(100);
    Carga carga3 = Carga(50);
    Carga carganula = Carga(0);
    vector<Carga> cargas;
    cargas.push_back(carga1);
    cargas.push_back(carga2);
    cargas.push_back(carga3);


    //Inicializacao dos geradores

    vector < Gerador > geradores_ini;
    Gerador G1 = Gerador (80, 40, 1100 , 20 ,0.1);
    Gerador G2 = Gerador (60, 20 , 1200, 25, 0.07);
    Gerador G3 = Gerador (70, 30, 300, 10, 0.2);
    Gerador G4 = Gerador (60, 20, 650, 20, 0.05);
    geradores_ini.push_back(G1);
    geradores_ini.push_back(G2);
    geradores_ini.push_back(G3);
    geradores_ini.push_back(G4);


    //random

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(0,1);
    uniform_real_distribution<float> distribution_(0.0,1.0);
    float sigma =15 ;
    vector<Gerador> g;
    vector<Barramento> barramentos;
    Barramento barramento1 = Barramento(g,carga1);
    Barramento barramento2 = Barramento(g,carga2);
    g.push_back(G1);
    g.push_back(G2);
    Barramento barramento3 = Barramento(g,carganula);
    g.pop_back();
    g.pop_back();
    g.push_back(G3);
    g.push_back(G4);
    Barramento barramento4 = Barramento(g,carganula);
    g.pop_back();
    g.pop_back();
    Barramento barramento5 = Barramento(g,carga3);

    barramentos.push_back(barramento1);
    barramentos.push_back(barramento2);
    barramentos.push_back(barramento3);
    barramentos.push_back(barramento4);
    barramentos.push_back(barramento5);


    //{
    int Pop;
    do{
        cout << "Insira o numero de Individuos da Populacao"<< endl;
        cin >> Pop;
    }while(Pop<=0);
    float P;
    //}
    //Inicializacao dos geradores
    //Inicializacao dos individuos
    vector <Individuo> individuos;
    float sumPmax = 0;
    float sumPmin = 0;
    for(Gerador g:geradores_ini){
        sumPmax = sumPmax + g.GetPmax();
        sumPmin= sumPmin + g.GetPmin();
    }
    while(true){
        cout << "Insira carga a alimentar"<< endl;
        cin >> P;
        if(P<0){
            cout<<"Potencia nao pode ser negativa"<<endl;
        }
        else{
            if(P>240||P<160)cout<<"Potencia entre: " << 160 << " e "<<240 <<endl;
            else break;
        }

    }

    //Adicionar individuos
    for(int i = 0 ; i < Pop; i++){
        //cria individuo com geradores
        Individuo ind = Individuo(geradores_ini,barramentos,linhas);
        //gera valores aleatorios para as cargas dos geradores
        ind.fill(P,generator,distribution_);
        //mete individuo no vetor
        individuos.push_back(ind);
    }

    ofstream ofs ("save.txt" , ofstream::out);
    int Nger;
    avaliar(individuos);
    print(individuos);
    cout << "Numero de Geracoes" <<endl;
    cin >> Nger;
    int method;
    do{
        cout << "Escolha criterio de selecao" << endl << "Metodo elistista(1)" << endl << "Torneio Estocastico(2)" << endl;
        cin >> method;
    }while(method!=1 && method != 2);

    for(int i = 0 ; i < Nger;i++){

        avaliar(individuos);
        vector <Individuo> clone;
        //vetor com geracao nova
        individuos = geracao(Pop,sigma,generator,distribution,individuos,clone);
        //print(individuos);
        //filtra resultados com metodo elitista
        if(method == 2){
                individuos = testocastico(individuos,Pop, generator, distribution_);
        }else if ( method == 1 ){
                individuos = m_elitista(individuos,Pop);
        }


        ofs << min_element(individuos.begin(),individuos.end(),compare)->getCustoTotal() <<endl;
    }
        sort(individuos.begin(),individuos.end(),compare);
    ofs.close();
    cout << "Individuos ordenados por custo:" << endl;
    print(individuos);
    return 0;
}
