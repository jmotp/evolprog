#ifndef LINHA_H
#define LINHA_H
#include <vector>

using namespace std;
class Linha
{
    public:
        Linha(int No1,int No2,float Pmax,vector<float> sensibilidades);
        virtual ~Linha();

        int GetNo1() { return No1; }
        int GetNo2() { return No2; }

        void SetNo(int no1,int no2)
        {
            No1=no1;
            No2=no2;

        }
        float GetPmax() { return Pmax; }
        void SetPmax(float val) { Pmax = val; }
        vector<float> Getsensibilidades(){
            return sensibilidades;
        }

    protected:

    private:
        int No1;
        int No2;
        float Pmax;
        vector<float> sensibilidades;
};

#endif // LINHA_H
