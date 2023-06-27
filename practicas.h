#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ESC 27

typedef struct
{
    int idPractica; /// campo único y autoincremental
    char nombre[30];
    int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
    int baja; /// 0 si está activo - 1 si está eliminado
} stPracticas;


void cargaArchivoPracticas(char nombreArchivo[]);
void darAltaInactivo(char nombreArchivo[]);
void muestraPracticasInactivas(stPracticas practica);
void muestraTodasLasPracticas(stPracticas practica); ///ACTIVAS E INACTIVAS
void muestraPracticasActivas(stPracticas practica);
void muestraArchivoPracticas(char nombreArchivo[]);
void darBajaPracticas(char nombreArchivo[]);
void validacionesPracticaId(char nombreArchivo[]);
void busquedaPractica (char nombreArchivo[]);
void menuAltasPracticas(char nombreArchivo[]);

stPracticas validacionCosto(stPracticas valPracticas);
stPracticas validacionesPractica(char nombreArchivo[],stPracticas practica);
stPracticas cargaUnaPractica();


#endif // PRACTICAS_H_INCLUDED
