#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include "Gerador.h"
#include "Linha.h"
#include "Carga.h"
#include "Barramento.h"

class Individuo
{
    public:
        Individuo();
        Individuo(vector<Gerador> geradores,vector<Barramento> barramentos,vector<Linha> linhas);
        virtual ~Individuo();
        //gerar valores aleatorios iniciais para as potencias produzidas dos geradores
        void fill(float P,default_random_engine & generator,uniform_real_distribution<float> distribution_){
            float sum = 0;
            int i;
            do{
                for( i = 0; i < geradores.size();i++){
                    geradores[i].SetPpro(0);
                }
                for( i = 0 ; i < geradores.size()-1;i++){
                    geradores[i].SetPpro(distribution_(generator)*(geradores[i].GetPmax()-geradores[i].GetPmin())+geradores[i].GetPmin());
            }
                geradores[i].SetPpro(P-sumPcons());
                pcons = sumPcons();
            }while(geradores[i].GetPpro()>geradores[i].GetPmax()||geradores[i].GetPpro()<geradores[i].GetPmin());

        }
        //mutar matrizes filhos
        void mutar(float sigma,default_random_engine & generator, normal_distribution<double> distribution){
            for(Gerador & g : geradores){
                g.mutarPpro(sigma,generator,distribution);
                g.calcCusto();
            }
        }
        float getCustoTotal(){
            float sum = 0;
            for(Gerador & g : geradores){
                sum += g.Getcusto();
            }

            vector <Gerador> g1;
            vector <Gerador> g2;
            g1.push_back(geradores.at(0));
            g1.push_back(geradores.at(1));
            g2.push_back(geradores.at(2));
            g2.push_back(geradores.at(3));
            barramentos.at(2).Setgerador(g1);
            barramentos.at(3).Setgerador(g2);
            for(Barramento & b: barramentos){
                b.Calcpinj();
            }
            //cout << endl;
            for(Linha l:linhas){
                float soma=0;
                for(int i = 0;i< l.Getsensibilidades().size();i++){
                    soma+= barramentos.at(i).Getpinj() * l.Getsensibilidades().at(i);
                }

                //cout << soma << " " <<l.GetPmax()<< " / ";
                if(soma<0){
                        soma=-soma;
                }
                if(soma>l.GetPmax())sum=sum+10000*(soma-l.GetPmax())*(soma-l.GetPmax());

                //cout <<endl;

            }




            return sum;
            }

        void corrigir(float pcons, float l ){

            for(Gerador & g : geradores){
                g.corrigir(pcons,l);
                g.calcCusto();
            }
        }

        float sumPcons(){
            float sumPpro=0;
            for(Gerador g : geradores){
                sumPpro = sumPpro  + g.GetPpro();
            }
            return sumPpro;
        }

        void avaliar(){
            for(Gerador & g : geradores){
                g.avaliar();
            }
        }

        void printCusto(){
            for(Gerador g : geradores){
                g.printCusto();
            }
            cout<<endl;
        }
        void print(){

            for(Gerador g : geradores){
                g.printPpro();
            }

            cout<< getCustoTotal()<<'|';
            cout<<endl;
        }
        vector<Gerador> Getgeradores() { return geradores; }
        void Setgeradores(vector<Gerador> val) { geradores = val; }

    protected:

    private:
        vector<Gerador> geradores;
        vector <Barramento> barramentos;
        float pcons;
        vector<Linha> linhas;
};

#endif // INDIVIDUO_H
