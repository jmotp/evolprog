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
    Gnuplot gp;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(0,1);
    uniform_real_distribution<float> distribution_(0.0,1.0);
    float sigma =10 ;

    int Pop;
    do{
        cout << "Insira o numero de Individuos da Populacao"<< endl;
        cin >> Pop;
    }while(Pop<=0);
    float P;

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
        Individuo ind = Individuo(geradores_ini);
        //gera valores aleatorios para as cargas dos geradores
        ind.fill(P,generator,distribution_);
        //mete individuo no vetor
        individuos.push_back(ind);
    }
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

    }

    sort(individuos.begin(),individuos.end(),compare);
    cout << "Individuos ordenados por custo:" << endl;
    print(individuos);
    return 0;
}
