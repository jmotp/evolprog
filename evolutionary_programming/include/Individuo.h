#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include "Gerador.h"

class Individuo
{
    public:
        Individuo();
        Individuo(vector<Gerador> geradores);
        virtual ~Individuo();
        void fill(){
            for(Gerador & gerador : geradores){
                int Ppro;
                cin >> Ppro;
                gerador.SetPpro(Ppro);
                gerador.calcCusto();
            }
            pcons = sumPcons();

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
