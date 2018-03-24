#ifndef GERADOR_H
#define GERADOR_H
#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include "Linha.h"
#include "Carga.h"
using namespace std;
class Gerador
{
    public:
        Gerador(int Pmax,int Pmin,float costa,float costb,float costc );
        Gerador();
        virtual ~Gerador();

        /*void fill(){
            int Pmax;
            int Pmin;
            float costa, costb, costc;
            cout <<"Pmax: ";
            cin >> Pmax;
            cout << "Pmin: ";
            cin >> Pmin;
            cout << "costa";
            cin >> costa;
            cin >> costb;
            cin >> costc;
            SetPmax(Pmax);
            SetPmin(Pmin);
            Setcosta(costa);
            Setcostb(costb);
            Setcostc(costc);

        };*/
        void mutarPpro(float sigma,default_random_engine & generator, normal_distribution<double> distribution){

            Ppro = (Ppro + sigma * distribution(generator));
        }
        void corrigir(float pcons, float l){
            Ppro = Ppro * l / pcons;
        }
        void printPpro(){
            cout <<  setw(4) << setprecision(2)<< fixed << Ppro <<" |" ;
        }
        void calcCusto(){
            custo = costa + Ppro* costb + Ppro * Ppro * costc;
        }
        void printCusto(){
            cout << custo <<" " ;
        };
        void avaliar(){
            calcCusto();
            if(Ppro> Pmax){
                custo = custo + 100 * (Ppro-Pmax)*(Ppro-Pmax);
            }
            if(Ppro < Pmin){
                custo = custo + 100 * (-Ppro+Pmin)*(-Ppro+Pmin);
            }

        }


        void print(){
            cout << "Pmax: " << GetPmax();
        };
        int GetPmax() { return Pmax; }
        void SetPmax(int val) { Pmax = val; }
        int GetPmin() { return Pmin; }
        void SetPmin(int val) { Pmin = val; }
        float GetPpro() { return Ppro; }
        void SetPpro(float val) { Ppro = val; }
        float Getcosta() { return costa; }
        void Setcosta(float val) { costa = val; }
        float Getcostb() { return costb; }
        void Setcostb(float val) { costb = val; }
        float Getcostc() { return costc; }
        void Setcostc(float val) { costc = val; }
        float Getcusto() { return custo; }
        void Setcusto(float val) { custo = val; }



    protected:

    private:
        int Pmax;
        int Pmin;
        float Ppro=0;
        float costa;
        float costb;
        float costc;
        float custo = 0;
};

#endif // GERADOR_H
