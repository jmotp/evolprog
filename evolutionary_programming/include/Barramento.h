#ifndef BARRAMENTO_H
#define BARRAMENTO_H
#include <vector>
#include "Gerador.h"
#include "Carga.h"

class Barramento
{
    public:
        Barramento(vector<Gerador>  G,Carga & C);
        virtual ~Barramento();

        vector<Gerador> & Getgerador() { return  gerador; }
        void Setgerador(vector<Gerador> val) { gerador = val; }
        Carga Getcarga() { return carga; }
        void Setcarga(Carga val) { carga = val; }
        float Getpinj(){return pinj;}
        void Calcpinj(){
            pinj = 0;
            for(Gerador gerador_: gerador ){
                pinj+=gerador_.GetPpro();
            }
            pinj -= carga.GetPcons();
        }
    protected:

    private:
        vector<Gerador> gerador;
        Carga carga;
        float pinj;
};

#endif // BARRAMENTO_H
