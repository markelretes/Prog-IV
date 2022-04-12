#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 10
#define INT_LINE 1
#include "usuario.h"
#include "menuAdmin.h"
#include "sqlite3.h"

void limpiarString(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '\n')
        {
            str[i] = '\0';
        }
    }
}

char menuInicioAdmin()
{
    printf("====================================\n");
    printf(".:: ADMINISTRACION DE DEUSTO BET ::.\n");
    printf("====================================\n");
    printf("\n1. Iniciar sesion\n2. Registrar administrador\n3. Salir\n");
    printf("\nElija una opcion: ");
    fflush(stdout);
    char linea[MAX_LINE];
    fgets(linea, MAX_LINE, stdin);

    return linea[0]; // Solo interesa un digito
}

int menuIniciarSesion(Usuario* usuarios, int numUsuarios)
{
    char strUser[MAX_LINE];
    char strPass[MAX_LINE];
    printf("\n\n================\n");
    printf("INICIO DE SESION\n");
    printf("================\n");
    printf("Nombre de usuario: ");
    // Pide el username
    fflush(stdout);
    fgets(strUser, MAX_LINE, stdin);
    limpiarString(strUser);
    // Pide la contrasena
    printf("Contrasena: ");
    fflush(stdout);
    fgets(strPass, MAX_LINE, stdin);
    limpiarString(strPass);
    // Comparar username y contrasena
    for(int i = 0; i < numUsuarios; i++)
    {
        if(strcmp(strUser, usuarios[i].username) == 0)
        {
            if(strcmp(strPass, usuarios[i].contrasena) == 0)
            {
                return 1;
            }
            return 0;
        }
    }
    return -1;
}

void registroAdmin(Usuario** usuarios, int numUsuarios, sqlite3 *db)
{
    char strUser[MAX_LINE];
    char strPass[MAX_LINE];
    printf("\n\n=========================\n");
    printf("REGISTRO DE ADMINISTRADOR\n");
    printf("=========================\n");
    printf("Nombre de usuario: ");
    // Pide el username
    fflush(stdout);
    fflush(stdin);
    fgets(strUser, MAX_LINE, stdin);
    limpiarString(strUser);
    // Pide la contrasena
    printf("Contrasena: ");
    fflush(stdout);
    fflush(stdin);
    fgets(strPass, MAX_LINE, stdin);
    limpiarString(strPass);

    Usuario u = {strUser, strPass, 0.0, 0, 0, true};
    registrarAdmin(u, usuarios, numUsuarios);
    guardarUsuario(db, u); // Inserta en BD
}

char menuPrincipalAdmin()
{
    printf("\n\n==============\n");
    printf("MENU PRINCIPAL\n");
    printf("==============\n");
    printf("\n1. Gestionar usuarios\n2. Visualizar usuarios\n3. Visualizar clasificacion de usuarios\n4. Salir\n");
    printf("\nElija una opcion: ");
    fflush(stdout);
    char linea[MAX_LINE];
    fgets(linea, MAX_LINE, stdin);

    return linea[0]; // Solo interesa un digito
}

char gestionUsuarios()
{
    printf("\n\n===================\n");
    printf("GESTION DE USUARIOS\n");
    printf("===================\n");
    printf("\n1. Modificar usuario\n2. Eliminar usuario\n3. Volver\n");
    printf("\nElija una opcion: ");
    fflush(stdout);
    char linea[MAX_LINE];
    fgets(linea, MAX_LINE, stdin);

    return linea[0];
}

void menuModificarUsuario(Usuario **usuarios, int numUsuarios)
{
    printf("\n\n=================\n");
    printf("MODIFICAR USUARIO\n");
    printf("=================\n");

    // Mostrar por pantalla los usuarios que no sean admins
    for(int i = 0; i < numUsuarios; i++)
    {
        if(!(*usuarios)[i].admin)
        {
            printf("%i. %s\n", i, (*usuarios)[i].username);
        }
    }

    // Elegir usuario
    printf("\nElija el usuario que quiera modificar: ");
    fflush(stdout);
    int index;
    char strIndex[MAX_LINE];
    fgets(strIndex, MAX_LINE, stdin);
    sscanf(strIndex, "%i", &index);

    // Modificar usuario
    printf("\n\n===================\n");
    printf("MODIFICAR %s\n", (*usuarios)[index].username);
    printf("===================\n");
    printf("Nombre de usuario nuevo: ");
    char strUser[MAX_LINE];
    fflush(stdout);
    fgets(strUser, MAX_LINE, stdin);
    limpiarString(strUser);

    printf("Contrasena de usuario nuevo: ");
    char strPass[MAX_LINE];
    fflush(stdout);
    fgets(strPass, MAX_LINE, stdin);
    limpiarString(strPass);

    modificarUsuario(strUser, strPass, usuarios, index);

    printf("Cambios realizados con exito!\n");
}

void menuEliminarUsuario(Usuario** usuarios, int numUsuarios, sqlite3 *db)
{
    printf("\n\n==============\n");
    printf("ELIMINAR USUARIO\n");
    printf("==============\n");
    // Mostrar solamente los admins
    for(int i = 0; i < numUsuarios; i++)
    {
        if(!(*usuarios)[i].admin)
        {
            printf("%i. %s\n", i, (*usuarios)[i].username);
        }
    }

    // Elegir usuario
    printf("\nElija el usuario que quiera eliminar: ");
    fflush(stdout);
    int index;
    char linea[MAX_LINE];
    fgets(linea, MAX_LINE, stdin);
    sscanf(linea, "%i", &index);

    // Confirmacion
    printf("Se va a eliminar a %s ¿Esta seguro? (S/N)", (*usuarios)[index].username);
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);
    if(linea[0] == 'S')
    {
        eliminarUsuarioBD(db, (*usuarios)[index]);
        eliminarUsuario(usuarios, index, numUsuarios);
    }
}
void menuVisualizarUsuarios(Usuario *usuarios, int numUsuarios){
    printf("\n\n=============================\n");
    printf("MOSTRANDO USUARIOS DEUSTO BET\n");
    printf("=============================\n");
    printf("Nombre de usuario || Contrasena || Partidas jugadas || Victorias || Bets maximos por partida\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for(int i = 0; i<numUsuarios; i++){
        imprimirUsuario(usuarios[i]);
    }
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Pulsa cualquier tecla para volver al menu principal\n");
}
void menuClasificacion(Usuario *usuarios, int numUsuarios){
    printf("\n\n========================\n");
    printf("CLASIFICACION DEUSTO BET\n");
    printf("========================\n");
    
    Usuario *top1 = &usuarios[0];
    Usuario *top2 = &usuarios[0];
    Usuario *top3 = &usuarios[0];
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i].dineroMax > top1->dineroMax){
            top1 = &usuarios[i];
        }
    }
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i].dineroMax >= top2->dineroMax && usuarios[i].username != top1->username){
            top2 = &usuarios[i];
        }
    }
    for(int i = 0; i < numUsuarios; i++ ){
        if(usuarios[i].dineroMax >= top3->dineroMax && usuarios[i].username != top1->username && usuarios[i].username != top2->username){
            top3 = &usuarios[i];
        }
    }

    printf("1. %s - %.2f\n", top1->username, top1->dineroMax);
    printf("2. %s - %.2f\n", top2->username, top2->dineroMax);
    printf("3. %s - %.2f\n", top3->username, top3->dineroMax);

}
void mainAdmin(Usuario *usuarios, int numUsuarios, sqlite3 *db){
    char opcion;
    do{
        opcion = menuInicioAdmin();
    } while(opcion != '1' && opcion != '2' && opcion != '3' );
    int login;
    char opcion2;
    char opcion3;
    
    switch (opcion)
    {
    case '1':
    // TODO: anyadir do-while
        login = menuIniciarSesion(usuarios, numUsuarios);
        // login = 1;
        if(login == 1)
        {
            //MENU PRINCIPAL
            opcion2 = menuPrincipalAdmin();
            switch (opcion2)
            {
            case '1':
                opcion3 = gestionUsuarios();
                switch (opcion3)
                {
                case '1':
                    menuModificarUsuario(&usuarios, numUsuarios);
                    break;
                case '2':
                    menuEliminarUsuario(&usuarios, numUsuarios, db);
                    numUsuarios--;
                    break;

                default:
                // Volver
                    break;
                }
                break;
            case '2':
                menuVisualizarUsuarios(usuarios, numUsuarios);

                break;
            case '3':
                menuClasificacion(usuarios, numUsuarios);

                break;

            default:
                break;
            }
        }
        else if(login == 0)
        {
            printf("Contrasena incorrecta\n");
        } else
        {
            printf("Usuario no existe\n");
        }
        break;
    case '2':
        numUsuarios++;
        Usuario u;
        registroAdmin(&usuarios, numUsuarios, db);
        
    default:
        break;
    }
}