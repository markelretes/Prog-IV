#ifndef EQUIPO_H_
#define EQUIPO_H_

class Equipo
{
    private:
        static int ultimoCodEquipo;
        int codEquipo;
        char* nombre;

    public:
        Equipo();
        Equipo(char* nombre);
        Equipo(char* nombre, int codEquipo); //Prueba
        Equipo(const Equipo& e);

        int getCodEquipo();
        void setCodEquipo(int codEquipo);
        char* getNombre();
        void setNombre(char* nombre);
};

#endif /*EQUIPO_H_*/