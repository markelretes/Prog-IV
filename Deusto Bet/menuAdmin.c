#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LINE 10
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

int menuInicioAdmin()
{
    printf("\n====================================\n");
    printf(".:: ADMINISTRACION DE DEUSTO BET ::.\n");
    printf("====================================\n");
    printf("\n1. Iniciar sesion\n2. Registrar administrador\n3. Salir\n");
    printf("\nElija una opcion: ");
    fflush(stdout);
    char linea[MAX_LINE];
    int resultado;
    fgets(linea, MAX_LINE, stdin);
    limpiarString(linea);
    sscanf(linea, "%i", &resultado);

    return resultado;
}

int menuIniciarSesion(Usuario* usuarios, int numUsuarios)
{
    char strUser[15];
    char strPass[15];
    printf("\n\n================\n");
    printf("INICIO DE SESION\n");
    printf("================\n");
    printf("Nombre de usuario: ");
    // Pide el username
    fflush(stdout);
    fgets(strUser, 15, stdin);
    limpiarString(strUser);

    // Pide la contrasena
    printf("Contrasena: ");
    fflush(stdout);
    fgets(strPass, 15, stdin);
    limpiarString(strPass);

    // Comparar username y contrasena
    for(int i = 0; i < numUsuarios; i++)
    {
        if(strcmp(strUser, usuarios[i].username) == 0 && usuarios[i].admin)
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

int menuRegistroAdmin(Usuario* usuarios, int numUsuarios, sqlite3 *db)
{
    int result;
    char strUser[MAX_LINE];
    char strPass[MAX_LINE];
    printf("\n\n=========================\n");
    printf("REGISTRO DE ADMINISTRADOR\n");
    printf("=========================\n");
    printf("Nombre de usuario: ");

    // Pide el username
    fflush(stdout);
    fflush(stdin);
    fgets(strUser, 10, stdin);
    limpiarString(strUser);

    // Pide la contrasena
    printf("Contrasena: ");
    fflush(stdout);
    fflush(stdin);
    fgets(strPass, 10, stdin);
    limpiarString(strPass);

    // Comprobar que el nombre de usuario no este en uso
    bool existe = false;
    for(int i = 0; i < numUsuarios; i++)
    {
        if(strcmp(usuarios[i].username, strUser) == 0)
        {
            existe = true;
            return 2;
        }
    }

    if(!existe)
    {
        Usuario u = {strUser, strPass, 0.0, 0, 0, true};
        result = guardarUsuario(db, u); // Inserta en BD
        if(result != SQLITE_OK)
        {
            printf("Error al registar adminstrador");
            result = SQLITE_ERROR;
        }
    }
    return result;
}

int menuPrincipalAdmin()
{
    printf("\n\n==============\n");
    printf("MENU PRINCIPAL\n");
    printf("==============\n");
    printf("\n1. Gestionar usuarios\n2. Visualizar usuarios\n3. Visualizar clasificacion de usuarios\n4. Cerrar sesion\n");
    printf("\nElija una opcion: ");
    fflush(stdout);
    char linea[MAX_LINE];
    int resultado;
    fgets(linea, MAX_LINE, stdin);
    limpiarString(linea);
    sscanf(linea, "%i", &resultado);

    return resultado;
}

int menuGestionUsuarios()
{
    printf("\n\n===================\n");
    printf("GESTION DE USUARIOS\n");
    printf("===================\n");
    printf("\n1. Modificar usuario\n2. Eliminar usuario\n3. Volver\n");
    printf("\nElija una opcion: ");
    fflush(stdout);
    char linea[MAX_LINE];
    int resultado;
    fgets(linea, MAX_LINE, stdin);
    limpiarString(linea);
    sscanf(linea, "%i", &resultado);

    return resultado;
}

void menuModificarUsuario(Usuario **usuarios, int numUsuarios, sqlite3 *db)
{
    printf("\n\n=================\n");
    printf("MODIFICAR USUARIO\n");
    printf("=================\n");

    // Mostrar por pantalla los usuarios que no sean admins e impedir elegir admins
    int contadorAdmin = 0;
    for(int i = 0; i < numUsuarios; i++){
        if(!(*usuarios)[i].admin)
        {
            contadorAdmin++;
        }
    }
    int posicionesAdmin[contadorAdmin];
    int posicionArray = 0;
    for(int i = 0; i < numUsuarios; i++)
    {
        if(!(*usuarios)[i].admin)
        {
            printf("%i. %s\n", i, (*usuarios)[i].username);
            posicionesAdmin[posicionArray] = i;
            posicionArray++;
        }
    }
    char linea[MAX_LINE];
    int index;
    bool contiene = false;
    do{
        // Elegir usuario
        printf("\nElija el usuario que quiera modificar: ");
        fflush(stdout);
        fgets(linea, MAX_LINE, stdin);
        limpiarString(linea);
        sscanf(linea, "%i", &index);
        for(int i = 0; i < contadorAdmin; i++)
        {
            if(index == posicionesAdmin[i])
            {
               contiene = true;
            }
        }
        if(contiene == false){
            printf("\nElija uno de los valores mostrados\n");
        }
    } while(contiene == false);

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

    modificarUsuario(db, (*usuarios)[index], strUser, strPass);

    printf("\nCambios realizados con exito!\n");
    printf("--------------------------\n");

    printf("Pulse ENTER para continuar");
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);
}

void menuEliminarUsuario(Usuario** usuarios, int numUsuarios, sqlite3 *db)
{
    printf("\n\n==============\n");
    printf("ELIMINAR USUARIO\n");
    printf("==============\n");
    // Mostrar solamente los admins e impedir que se elija un usuario que sea admin
    int contadorAdmin = 0;
    for(int i = 0; i < numUsuarios; i++){
        if(!(*usuarios)[i].admin)
        {
            contadorAdmin++;
        }
    }
    int posicionesAdmin[contadorAdmin];
    int posicionArray = 0;
    for(int i = 0; i < numUsuarios; i++)
    {
        if(!(*usuarios)[i].admin)
        {
            printf("%i. %s\n", i, (*usuarios)[i].username);
            posicionesAdmin[posicionArray] = i;
            posicionArray++;
        }
    }
    char linea[MAX_LINE];
    int index;
    bool contiene = false;
    do{
        // Elegir usuario
        printf("\nElija el usuario que quiera eliminar: ");
        fflush(stdout);
        fgets(linea, MAX_LINE, stdin);
        limpiarString(linea);
        sscanf(linea, "%i", &index);
        for(int i = 0; i < contadorAdmin; i++)
        {
            if(index == posicionesAdmin[i])
            {
               contiene = true;
            }
        }
        if(contiene == false){
            printf("\nElija uno de los valores mostrados\n");
        }
    } while(contiene == false);

    // Confirmacion
    printf("Se va a eliminar a %s ¿Esta seguro? (S/N) ", (*usuarios)[index].username);
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);
    if(linea[0] == 'S')
    {
        eliminarUsuario(db, (*usuarios)[index]);

        printf("\nUsuario eliminado con exito!\n");
    } else{
        printf("\nNingun cambio efectuado\n");
    }
    printf("--------------------------\n");

    printf("Pulse ENTER para continuar");
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);
    
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

    printf("Pulse ENTER para continuar");
    char linea[MAX_LINE];
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);

}

void menuClasificacion(Usuario *usuarios, int numUsuarios){
    printf("\n\n========================\n");
    printf("CLASIFICACION DEUSTO BET\n");
    printf("========================\n");

    // Creo un usuario con dineroMax a 0 para comparar desde el 0
    Usuario u = {"comparar", "comparar", 0.0, 0, 0, 0};

    Usuario top1 = u;
    Usuario top2 = u;
    Usuario top3 = u;
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i].dineroMax > top1.dineroMax){
            top1 = usuarios[i];
        }
    }
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i].dineroMax >= top2.dineroMax && usuarios[i].username != top1.username){
            top2 = usuarios[i];
        }
    }
    for(int i = 0; i < numUsuarios; i++ ){
        if(usuarios[i].dineroMax >= top3.dineroMax && usuarios[i].username != top1.username && usuarios[i].username != top2.username){
            top3 = usuarios[i];
        }
    }


    printf("1. %s - %.2f\n", top1.username, top1.dineroMax);
    printf("2. %s - %.2f\n", top2.username, top2.dineroMax);
    printf("3. %s - %.2f\n", top3.username, top3.dineroMax);
    printf("--------------------------\n");

    printf("Pulse ENTER para continuar");
    char linea[MAX_LINE];
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);

}

void mainAdmin(Usuario *usuarios, int numUsuarios, sqlite3 *db){
    int opcion;
    int login;
    int opcion2;
    int opcion3;
    int resultSQL;
    do{
        do{
            opcion = menuInicioAdmin();
        } while(opcion != 1 && opcion != 2 && opcion != 3);
        
        switch (opcion)
        {
        case 1:
            login = menuIniciarSesion(usuarios, numUsuarios);
            if(login == 1)
            {
                //MENU PRINCIPAL
                do{
                    do{
                        opcion2 = menuPrincipalAdmin();
                    } while(opcion2 != 1 && opcion2 != 2 && opcion2 != 3 && opcion2 != 4);
                    switch (opcion2)
                    {
                    case 1:
                        do{
                            do{
                                opcion3 = menuGestionUsuarios();
                            } while(opcion3 != 1 && opcion3 != 2 && opcion3 != 3);
                            switch (opcion3)
                            {
                            case 1:
                                menuModificarUsuario(&usuarios, numUsuarios, db);
                                resultSQL = cargarUsuarios(db, &usuarios, &numUsuarios);
                                if(resultSQL != SQLITE_OK)
                                {
                                    printf("Error al reimportar los usuarios tras modificar los datos");
                                }
                                    
                                break;
                            case 2:
                                menuEliminarUsuario(&usuarios, numUsuarios, db);
                                numUsuarios--;
                                resultSQL = cargarUsuarios(db, &usuarios, &numUsuarios);
                                if(resultSQL != SQLITE_OK)
                                {
                                    printf("Error al reimportar los usuarios tras eliminar el usuario");
                                }
                                break;

                            default:
                                break;
                            }
                        } while(opcion3 != 3);
                        break;
                    case 2:
                        menuVisualizarUsuarios(usuarios, numUsuarios);
                        break;
                    case 3:
                        menuClasificacion(usuarios, numUsuarios);
                        break;

                    default:
                        break;
                    }  
                }while(opcion2 != 4);

            }else if(login == 0)
            {
                printf("\nContrasena incorrecta\n");
                printf("--------------------------\n");
                char linea[MAX_LINE];
                printf("Pulse ENTER para continuar\n");

                do{
                    fflush(stdout);
                    fgets(linea, MAX_LINE, stdin);
                }while(linea[0] != '\n');
            }else
            {
                printf("\nNo existe un administrador con esos credenciales de inicio de sesion\n");
                printf("--------------------------\n");
                char linea[MAX_LINE];
                printf("Pulse ENTER para continuar\n");

                do{ 
                    fflush(stdout);
                    fgets(linea, MAX_LINE, stdin);
                }while(linea[0] != '\n');
            }
            break;
        case 2:
            resultSQL = menuRegistroAdmin(usuarios, numUsuarios, db);
            if(resultSQL == 2)
            {
                printf("\nNombre de usuario ya en uso\n");
            } else if(resultSQL == SQLITE_OK)
            {
                printf("\nAdministrador registrado correctamente\n");
            }
            numUsuarios++;
            resultSQL = cargarUsuarios(db, &usuarios, &numUsuarios);
            if(resultSQL != SQLITE_OK)
            {
                printf("Error al reimportar los usuarios tras el registro");
            }
            break;
        default:
            break;
        }
    }while(opcion != 3);
}