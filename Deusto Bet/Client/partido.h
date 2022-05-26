#ifndef PARTIDO_H_
#define PARTIDO_H_

#include "equipo.h"

class Partido
{
    private:
        static int ultimoCodPartido;
        int codPartido;
        int jornada;
        Equipo local;
        Equipo visitante;

    public:
        Partido();
        Partido(int jornada, const Equipo local, const Equipo visitante);
        Partido(const Partido& p);

        int getCodPartido();
        void setCodPartido(int codPartido);
        int getJornada();
        void setJornada(int jornada);
        Equipo getLocal();
        void setLocal(Equipo local);
        Equipo getVisitante();
        void setVisitante(Equipo visitante);
};

#endif /*PARTIDO_H_*/