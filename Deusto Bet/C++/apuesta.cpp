#include <stdbool.h>
#include "apuesta.h"
#include "partida.h"
#include "partido.h"
    
    int Apuesta::ultimoCodApuesta = 0;

    Apuesta::Apuesta()
    {
        this->codApuesta = ultimoCodApuesta;
        Apuesta::ultimoCodApuesta++;
        this->importe = 0.0;
        this->ganaLocal = false;
        this->ganaVisitante = false;
        this->empate = false;
        this->partida = Partida();
        this->partido = Partido();
    }
    Apuesta::Apuesta(float importe, bool ganaLocal, bool ganaVisitante, bool empate)
    {
        this->codApuesta = ultimoCodApuesta;
        Apuesta::ultimoCodApuesta++;
        this->importe = importe;
        this->ganaLocal = ganaLocal;
        this->ganaVisitante = ganaVisitante;
        this->empate = empate;
        this->partida = partida;
        this->partido = partido;
    }
    Apuesta::Apuesta(const Apuesta& a)
    {
        this->codApuesta = a.codApuesta;
        this->importe = a.importe;
        this->ganaLocal = a.ganaLocal;
        this->ganaVisitante = a.ganaVisitante;
        this->empate = a.empate;
        this->partida = a.partida;
        this->partido = a.partido;
    }

    int Apuesta::getCodApuesta()
    {
        return this->codApuesta;
    }
    void Apuesta::setCodApuesta(int codApuesta)
    {
        this->codApuesta = codApuesta;
    }
    float Apuesta::getImporte()
    {
        return this->importe;
    }
    void Apuesta::setImporte(float importe)
    {
        this->importe = importe;
    }
    bool Apuesta::isGanaLocal()
    {
        return this->ganaLocal;
    }
    void Apuesta::setGanaLocal(bool ganaLocal)
    {
        this->ganaLocal = ganaLocal;
    }
    bool Apuesta::isGanaVisitante()
    {
        return this->ganaVisitante;
    }
    void Apuesta::setGanaVisitante(bool ganaVisitante)
    {
        this->ganaVisitante = ganaVisitante;
    }
    bool Apuesta::isEmpate()
    {
        return this->empate;
    }
    void Apuesta::setEmpate(bool empate)
    {
        this->empate = empate;
    }
    Partida Apuesta::getPartida()
    {
        return this->partida;
    }
    void Apuesta::setPartida(Partida p)
    {
        this->partida = p;
    }
    Partido Apuesta::getPartido()
    {
        return this->partido;
    }
    void Apuesta::setPartido(Partido p)
    {
        this->partido = p;
    }