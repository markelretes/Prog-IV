#ifndef USUARIO_H_
#define USUARIO_H_

#include <stdbool.h>

class Usuario
{
    private:
        char* username;
        char* contrasena;
        float dineroMax;
        int partidas;
        int wins;
        bool admin;

    public:
        Usuario();
        Usuario(char* username, char* contrasena);
        Usuario(char* username, char* contrasena, float dineroMax, int partidas, int wins);
        Usuario(const Usuario& u);
        char* getUsername();
        void setUsername(char* username);
        char* getContrasena();
        void setContrasena(char* contrasena);
        float getDineroMax();
        void setDineroMax(float dineroMax);
        int getPartidas();
        void setPartidas(int numPartidas);
        int getWins();
        void setWins(int numWins);
        bool isAdmin();
        void setAdmin(bool admin);
};

#endif /*USUARIO_H_*/