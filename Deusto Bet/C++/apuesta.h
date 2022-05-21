#ifndef APUESTA_H_
#define APUESTA_H_

#include <stdbool.h>
#include "partida.h"
#include "partido.h"
class Apuesta
{
    private:
        static int ultimoCodApuesta;
        int codApuesta;
        float importe;
        bool ganaLocal;
        bool ganaVisitante;
        bool empate;
        Partida partida;
        Partido partido;

    public:
        Apuesta();
        Apuesta(float importe, bool ganaLocal, bool ganaVisitante, bool empate);
        Apuesta(const Apuesta& a);

        int getCodApuesta();
        void setCodApuesta(int codApuesta);
        float getImporte();
        void setImporte(float importe);
        bool isGanaLocal();
        void setGanaLocal(bool ganaLocal);
        bool isGanaVisitante();
        void setGanaVisitante(bool ganaVisitante);
        bool isEmpate();
        void setEmpate(bool empate);
        Partida getPartida();
        void setPartida(Partida p);
        Partido getPartido();
        void setPartido(Partido p);

};

#endif /*APUESTA_H_*/