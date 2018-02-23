#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include "Gerador.h"

class Individuo
{
    public:
        Individuo(vector<Gerador> geradores);
        virtual ~Individuo();
        void fill(){
            for(Gerador & gerador : geradores){
                int Ppro;
                cin >> Ppro;
                gerador.SetPpro(Ppro);
            }

        }
        void mutar(float sigma,default_random_engine generator, normal_distribution<double> distribution){
            for(Gerador & g : geradores){
                g.mutarPpro(sigma,generator,distribution);
            }
        }

        float sumPmax(){
            float sumPmax=0;
            for(Gerador g : geradores){
                sumPmax += g.GetPmax;
            }
            return sumPmax;
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
};

#endif // INDIVIDUO_H
