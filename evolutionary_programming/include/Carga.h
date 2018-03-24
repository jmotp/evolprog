#ifndef CARGA_H
#define CARGA_H


class Carga
{
    public:
        Carga(int Pcons);
        Carga();
        virtual ~Carga();


        float GetPcons() { return Pcons; }
        void SetPcons(float val) { Pcons = val; }

    protected:

    private:

        float Pcons;
};

#endif // CARGA_H
