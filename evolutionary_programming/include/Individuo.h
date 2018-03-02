#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include "Gerador.h"
#include <typeinfo>

class Individuo
{
    public:
        Individuo();
        Individuo(vector<Gerador> geradores);
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
            cout<< getCustoTotal();
            cout<<endl;
        }
        vector<Gerador> Getgeradores() { return geradores; }
        void Setgeradores(vector<Gerador> val) { geradores = val; }

    protected:

    private:
        vector<Gerador> geradores;
        float pcons;
};

#endif // INDIVIDUO_H
