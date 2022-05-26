#include "fichero.h"
#include "equipo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** cargarEquipos(char** equipos){
    FILE* f;
    equipos = (char**)malloc(sizeof(char*)*10);
    for(int i = 0; i < 10; i++){
        equipos[i] = (char*)malloc(sizeof(char)*20);
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
float* cargarProbabilidades(float* probabilidades){
    FILE* f;
    char** prob;
    prob = (char**)malloc(sizeof(char*)*10);
    for(int i = 0; i < 10; i++){
        prob[i] = (char*)malloc(sizeof(char)*4);
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
            prob[linea][char_index] = c;
            char_index++;
        }
	}

    float numero;
    probabilidades = (float*)malloc(sizeof(float)*10);
    for(int i = 0; i < 10; i++){
        numero = atof(prob[i]);
        probabilidades[i] = numero;
    }

	//cerrar fichero
	fclose(f);
	return probabilidades;

}