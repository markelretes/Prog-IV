#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 10
#include "usuario.h"

void clearIfNeeded(char *str, int max_line)
{
	// Limpia los caracteres de más introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
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
    clearIfNeeded(linea, MAX_LINE);

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
    clearIfNeeded(strUser, MAX_LINE);
    // Pide la contrasena
    printf("Contrasena: ");
    fflush(stdout);
    fgets(strPass, MAX_LINE, stdin);
    clearIfNeeded(strPass, MAX_LINE);
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

void registroUsuario(Usuario** usuarios, int numUsuarios)
{
    char strUser[MAX_LINE];
    char strPass[MAX_LINE];
    printf("\n\n=========================\n");
    printf("REGISTRO DE ADMINISTRADOR\n");
    printf("=========================\n");
    printf("Nombre de usuario: ");
    // Pide el username
    fflush(stdout);
    fgets(strUser, MAX_LINE, stdin);
    clearIfNeeded(strUser, MAX_LINE);
    // Pide la contrasena
    printf("Contrasena: ");
    fflush(stdout);
    fgets(strPass, MAX_LINE, stdin);
    clearIfNeeded(strPass, MAX_LINE);

    // Creo el administrador
    Usuario u = {strUser, strPass, 0.0, 0, 0, true};

    // Modificar el array de usuarios (reservar memoria para un usuario mas)
    Usuario* copia;
    copia = (Usuario*)malloc(sizeof(Usuario)*numUsuarios); // Creo una copia del array antes de reservar memoria
    copia = *usuarios;

    *usuarios = (Usuario*)malloc(sizeof(Usuario)*(numUsuarios+1)); // Reservo memoria para un usuario mas
    *usuarios = copia;
    (*usuarios)[numUsuarios] = u;

    // Libero memoria del array de copia
    free(copia);
    copia = NULL;
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
    clearIfNeeded(linea, MAX_LINE);

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
    clearIfNeeded(linea, MAX_LINE);

    return linea[0];
}

void modificarUsuario(Usuario **usuarios, int numUsuario)
{
    printf("\n\n=================\n");
    printf("MODIFICAR USUARIO\n");
    printf("=================\n");

    // Mostrar por pantalla los usuarios que no sean admins
    for(int i = 0; i < numUsuario; i++)
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
    char linea[MAX_LINE];
    fgets(linea, MAX_LINE, stdin);
    sscanf(linea, "%i", &index);
    clearIfNeeded(linea, MAX_LINE);

    // Modificar usuario
    printf("\n\n===================\n");
    printf("MODIFICAR %s\n", (*usuarios)[index].username);
    printf("===================\n");
    printf("Nombre de usuario nuevo: ");
    fgets(linea, MAX_LINE, stdin);
    sscanf(linea, "%i", &index);
    clearIfNeeded(linea, MAX_LINE);
    (*usuarios)[index].username = linea;
    printf("Nombre de usuario nuevo: ");
    fgets(linea, MAX_LINE, stdin);
    sscanf(linea, "%i", &index);
    clearIfNeeded(linea, MAX_LINE);
    (*usuarios)[index].contrasena = linea;
    
    printf("Cambios realizados con exito!\n");
}

void eliminarUsuario(Usuario** usuarios, int numUsuario)
{
    // Mostrar solamente los admins
    for(int i = 0; i < numUsuario; i++)
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
    clearIfNeeded(linea, MAX_LINE);

    // Confirmacion
    printf("Va a eliminar a %s ¿Esta seguro? (S/N)", (*usuarios)[index].username);
    fflush(stdout);
    fgets(linea, MAX_LINE, stdin);
    if(linea[0] == 'S')
    {
        Usuario* copia;
        copia = (Usuario*)malloc(sizeof(Usuario)*(numUsuario));
        copia = *usuarios; 
        *usuarios = (Usuario*)malloc(sizeof(Usuario)*(numUsuario-1));
        for(int i = 0; i < numUsuario; i++)
        {
            if(i != index)
            {
                *usuarios[i] = copia[i];
            }
        }

        // Liberar memoria
        free(copia);
        copia = NULL;
    }

}

int main(void)
{
    //cargarDatos();

    // Datos de prueba
    int numUsuarios = 5;
    Usuario *usuarios;
    usuarios = (Usuario*)malloc(sizeof(Usuario)*numUsuarios);
    usuarios[0].username = "juorma"; usuarios[0].contrasena = "juan1234"; usuarios[0].dineroMax = 1500.6; usuarios[0].partidas = 130; usuarios[0].wins = 95; usuarios[0].admin = true;
    usuarios[1].username = "markel"; usuarios[1].contrasena = "markel1234"; usuarios[1].dineroMax = 1500.6; usuarios[1].partidas = 130; usuarios[1].wins = 95; usuarios[1].admin = false;
    usuarios[2].username = "diego1"; usuarios[2].contrasena = "diego1234"; usuarios[2].dineroMax = 1500.6; usuarios[2].partidas = 130; usuarios[2].wins = 95; usuarios[2].admin = true;
    usuarios[3].username = "diego2"; usuarios[3].contrasena = "juan1234"; usuarios[3].dineroMax = 1500.6; usuarios[3].partidas = 130; usuarios[3].wins = 95; usuarios[3].admin = false;
    usuarios[4].username = "andoni"; usuarios[4].contrasena = "andon1234"; usuarios[4].dineroMax = 1500.6; usuarios[4].partidas = 130; usuarios[4].wins = 95; usuarios[4].admin = true;
    
    //  Muestra menu principal
    char opcion1 = menuInicioAdmin();
    char opcion2;
    char opcion3;

    int login;
    //  Switch de opcion
    switch (opcion1)
    {
    case '1':
    // TODO: anyadir do-while
        //login = menuIniciarSesion(usuarios, numUsuarios);
        login = 1;
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
                    modificarUsuario(&usuarios, numUsuarios);
                    break;
                case '2':
                    eliminarUsuario(&usuarios, numUsuarios);
                    numUsuarios--;
                    break;

                default:
                // Volver
                    break;
                }
                break;
            case '2':

                break;
            case '3':

                break;

            default:
            printf("Fin del programa");
                break;
            }
        }
        else if(login == 0)
        {
            printf("Contraseña incorrecta\n");
        } else
        {
            printf("Usuario no existe\n");
        }
        break;
    case '2':
        registroUsuario(&usuarios, numUsuarios);
        numUsuarios++;
    default:
        printf("Fin del programa");
        break;
    }

    return 0;
}