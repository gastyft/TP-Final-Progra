#ifndef LABORATORIOS_H_INCLUDED
#define LABORATORIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ESC 27
#include "practicas.h"
#include "pacientes.h"

typedef struct
{
    int idLab; /// campo único y autoincremental
    int idPaciente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int PracticaRealizada; /// con códigos entre 1 y 10.
    int baja; /// 0 si está activo - 1 si está eliminado
} stLaboratorios;

typedef struct
{
    int dia;
    int mes;
    int anio;
} stFecha;

void validacionesLabs(char nombreArchivo[]);
void darBajaLaboratorios(char nombreArchivo[]);
void laboratoriosAleatorios(char nombreArchivo[]);
void muestraUnLaboratorio(stLaboratorios laboratorio);
void muestraArchivoLaboratorios(char nombreArchivo[]);
void cargaArchivoLaboratorios(char nombreArchivo[]);
stLaboratorios busquedaLaboratorio(char nombreArchivo[]);
void menuAltasLaboratorios(char nombreArchivo[]);
void muestraLaboratoriosInactivos(stLaboratorios laboratorio);
void muestraLaboratoriosActivos(stLaboratorios laboratorio);
int validacionId();
void modificacionLaboratorio(char nombreArchivo[] );
stLaboratorios modificaUnLaboratorio(stLaboratorios laboratorio);
stLaboratorios cargaUnLaboratorio();
stLaboratorios validacionFecha(stLaboratorios laboratorio);
stLaboratorios validacionPractica(stLaboratorios laboratorio);
#endif // LABORATORIOS_H_INCLUDED
