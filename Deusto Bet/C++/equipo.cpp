#include "equipo.h"
#include <string.h>

    int Equipo::ultimoCodEquipo = 0;

    Equipo::Equipo()
    {
        this->codEquipo = ultimoCodEquipo;
        Equipo::ultimoCodEquipo++;
        this->nombre = new char[1];
    }
    Equipo::Equipo(char* nombre)
    {
        this->codEquipo = ultimoCodEquipo;
        Equipo::ultimoCodEquipo++;
        this->nombre = new char[strlen(nombre)+1];
        strcpy(this->nombre, nombre);
    }
    Equipo::Equipo(const Equipo& e)
    {
        this->codEquipo = e.codEquipo;
        this->nombre = new char[strlen(e.nombre)+1];
        strcpy(this->nombre, e.nombre);
    }

    int Equipo::getCodEquipo()
    {
        return this->codEquipo;
    }
    void Equipo::setCodEquipo(int codEquipo)
    {
        this->codEquipo = codEquipo;
    }
    char* Equipo::getNombre()
    {
        return this->nombre;
    }
    void Equipo::setNombre(char* nombre)
    {
        this->nombre = new char[strlen(nombre)+1];
        strcpy(this->nombre, nombre);
    }