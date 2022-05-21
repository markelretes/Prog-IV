#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "usuario.h"

class Partida
{
    private:
        static int ultimoCodPartida;
        int codPartida;
        float dinero;
        Usuario user;

    public:
        Partida();
        Partida(float dinero, Usuario user);
        Partida(const Partida& p);

        int getCodigoPartida();
        void setCodigoPartida(int codigoPartida);
        float getDinero();
        void setDinero(float dinero);
        Usuario getUser();
        void setUser(Usuario u);
};

#endif /*PARTIDA_H_*/