#include "fichero.h"
#include "equipo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** cargarEquipos(){
    FILE* f;
    char** equipos;
    equipos = (char**)malloc(sizeof(char*)*10);
    for(int i = 0; i < 10; i++){
        equipos[i] = (char*)malloc(sizeof(char)*15);
    }

    char c;
	int linea = 0;
    int char_index = 0;
	//abrir fichero para lectura
	f = fopen("Equipos.txt", "rt");
       
	//leer mientras no se llegue al final del fichero EOF
	while ((c = fgetc(f)) != EOF)
	{
		if (c == '\n'){
			linea++;  
            char_index = 0;
        } else{
            equipos[linea][char_index] = c;
            char_index++;
        }
	}
	//cerrar fichero
	fclose(f);
	return equipos;
}
float* cargarProbabilidades(){
    FILE* f;
    char** probabilidades;
    probabilidades = (char**)malloc(sizeof(char*)*10);
    for(int i = 0; i < 10; i++){
        probabilidades[i] = (char*)malloc(sizeof(char)*4);
    }

    char c;
	int linea = 0;
    int char_index = 0;
	//abrir fichero para lectura
	f = fopen("Probabilidades.txt", "rt");
       
	//leer mientras no se llegue al final del fichero EOF
	while ((c = fgetc(f)) != EOF)
	{
		if (c == '\n'){
			linea++;  
            char_index = 0;
        } else{
            probabilidades[linea][char_index] = c;
            char_index++;
        }
	}

    float* prob;
    float numero;
    prob = (float*)malloc(sizeof(float)*10);
    for(int i = 0; i < 10; i++){
        numero = atof(probabilidades[i]);
        prob[i] = numero;
    }

	//cerrar fichero
	fclose(f);
	return prob;

}