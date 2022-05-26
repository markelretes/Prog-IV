#include "partido.h"
#include "equipo.h"

    int Partido::ultimoCodPartido = 0;

    Partido::Partido()
    {
        this->codPartido = ultimoCodPartido;
        Partido::ultimoCodPartido++;
        this->jornada = 0;
        this->local = Equipo();
        this->visitante = Equipo();
    }
    Partido::Partido(int jornada, Equipo local, Equipo visitante)
    {
        this->codPartido = ultimoCodPartido;
        Partido::ultimoCodPartido++;
        this->jornada = jornada;
        this->local = local;
        this->visitante = visitante;
    }
    Partido::Partido(const Partido& p)
    {
        this->codPartido = p.codPartido;
        this->jornada = p.jornada;
        this->local = p.local;
        this->visitante = p.visitante;
    }

    int Partido::getCodPartido()
    {
        return this->codPartido;
    }
    void Partido::setCodPartido(int codPartido)
    {
        this->codPartido = codPartido;
    }
    int Partido::getJornada()
    {
        return this->jornada;
    }
    void Partido::setJornada(int jornada)
    {
        this->jornada = jornada;
    }
    Equipo Partido::getLocal()
    {
        return this->local;
    }
    void Partido::setLocal(Equipo local)
    {
        this->local = local;
    }
    Equipo Partido::getVisitante()
    {
        return visitante;
    }
    void Partido::setVisitante(Equipo visitante)
    {
        this->visitante = visitante;
    }