#ifndef LABORATORIOS_H_INCLUDED
#define LABORATORIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ESC 27

typedef struct
{
    int idLab; /// campo �nico y autoincremental
    int idPaciente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a � dependiendo del mes
    int PracticaRealizada; /// con c�digos entre 1 y 10.
    int baja; /// 0 si est� activo - 1 si est� eliminado
} stLaboratorios;

typedef struct
{
    int dia;
    int mes;
    int anio;
} stFecha;

void darBajaLaboratorios(char nombreArchivo[]);
void muestraLaboratorio (char nombreArchivo[]);
void laboratoriosAleatorios(char nombreArchivo[]);

#endif // LABORATORIOS_H_INCLUDED
