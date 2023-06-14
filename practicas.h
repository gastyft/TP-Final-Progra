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
    int idPractica; /// campo �nico y autoincremental
    char nombre[30];
    int costo; /// valores enteros entre 1000 y 10000 como m�nimos y m�ximos respectivamente
    int baja; /// 0 si est� activo - 1 si est� eliminado
} stPracticas;


stPracticas cargaUnaPractica();
stPracticas cargaUnaPractica();

  stPracticas busquedaPractica (char nombreArchivo[]);

void cargaArchivoPracticas(char nombreArchivo[]);
void muestraUnaPractica(stPracticas practica);
void muestraArchivoPracticas(char nombreArchivo[]);
void darBajaPracticas(char nombreArchivo[]);


#endif // PRACTICAS_H_INCLUDED
