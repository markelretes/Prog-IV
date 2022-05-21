#include "usuario.h"
#include <string.h>

    Usuario::Usuario()
    {
        this->username = new char[1];
        this->contrasena = new char[1];
        this->dineroMax = 0.0;
        this->partidas = 0;
        this->wins = 0;
        this->admin = false;
    }
    Usuario::Usuario(char* username, char* contrasena)
    {
        this->username = new char[strlen(username)+1];
        strcpy(this->username, username);
        this->contrasena = new char[strlen(contrasena)+1];
        strcpy(this->contrasena, contrasena);
        this->dineroMax = 0.0;
        this->partidas = 0;
        this->wins = 0;
        this->admin = false;
    }
    Usuario::Usuario(const Usuario& u)
    {
        this->username = new char[strlen(u.username)+1];
        strcpy(this->username, u.username);
        this->contrasena = new char[strlen(u.contrasena)+1];
        strcpy(this->contrasena, u.contrasena);
        this->dineroMax = u.dineroMax;
        this->partidas = u.partidas;
        this->wins = u.wins;
        this->admin = u.admin;
    }
    char* Usuario::getUsername()
    {
        return this->username;
    }
    void Usuario::setUsername(char* username)
    {
        this->username = new char[strlen(username)+1];
        strcpy(this->username, username);
    }
    char* Usuario::getContrasena()
    {
        return this->contrasena;
    }
    void Usuario::setContrasena(char* contrasena)
    {
        this->contrasena = new char[strlen(contrasena)+1];
        strcpy(this->contrasena, contrasena);
    }
    float Usuario::getDineroMax()
    {
        return this->dineroMax;
    }
    void Usuario::setDineroMax(float dineroMax)
    {
        this->dineroMax = dineroMax;
    }
    int Usuario::getPartidas()
    {
        return this->partidas;
    }
    void Usuario::setPartidas(int numPartidas)
    {
        this->partidas = numPartidas;
    }
    int Usuario::getWins()
    {
        return this->wins;
    }
    void Usuario::setWins(int numWins)
    {
        this->wins = numWins;
    }
    bool Usuario::isAdmin()
    {
        return this->admin;
    }
    void Usuario::setAdmin(bool admin)
    {
        this->admin = admin;
    }