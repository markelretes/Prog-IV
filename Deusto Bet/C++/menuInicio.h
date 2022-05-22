#include "usuario.h"
extern "C"
{
    #include "../C/baseDeDatos.h"
}

int menuInicio();
int menuLogin(Usuario* usuarios, int numUsuarios);
int menuRegistroUsuario(Usuario** usuarios, int numUsuarios);