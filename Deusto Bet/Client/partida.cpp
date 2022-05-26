#include "partida.h"

    int Partida::ultimoCodPartida = 0;

    Partida::Partida()
    {
        this->codPartida = ultimoCodPartida;
        Partida::ultimoCodPartida++;
        this->dinero = 0.0;
        this->user = Usuario();
    }
    Partida::Partida(float dinero, Usuario user)
    {
        this->codPartida = ultimoCodPartida;
        Partida::ultimoCodPartida++;
        this->dinero = dinero;
        this->user = user;
    }
    Partida::Partida(const Partida& p)
    {
        this->codPartida = p.codPartida;
        this->dinero = p.dinero;
        this->user = p.user;
    }

    int Partida::getCodigoPartida()
    {
        return this->codPartida;
    }
    void Partida::setCodigoPartida(int codigoPartida)
    {
        this->codPartida = codigoPartida;
    }
    float Partida::getDinero()
    {
        return this->dinero;
    }
    void Partida::setDinero(float dinero)
    {
        this->dinero = dinero;
    }
    Usuario Partida::getUser()
    {
        return this->user;
    }
    void Partida::setUser(Usuario u)
    {
        this->user = u;
    }