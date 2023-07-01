#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ESC 27
#include "practicas.h"
#include "laboratorios.h"

///ESTRUCTURA
typedef struct
{
    int idPaciente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char movil[12];
    int eliminado;
} stPaciente;



///PROTOTIPADO
void muestraUnPaciente(stPaciente paciente);
void cargaArchivoPacientes(char nombreArchivo[]);
void muestraArchivoPacientes(char nombreArchivo[]);
void darBajaPacientes(char nombreArchivo[]);
void practicaPaciente(stPaciente paciente);
void menuAltasPacientes(char nombreArchivo[]);
void menuAltasPacientes(char nombreArchivo[]);
void muestraPacientesInactivos(stPaciente paciente);
void modificacion(char nombreArchivo[],stPaciente paciente);
void menuModificacion(char nombreArchivo[]);
int costoTotal(stPaciente paciente);
stPaciente opcion_busca_paciente_apellido (char nombreArchivo[]);
stPaciente opcionBuscaPacienteDNI (char nombreArchivo[]);
stPaciente cargaUnPaciente();
stPaciente buscarPacientePorDNI (char nombreArchivo[], char dni[]);
stPaciente buscarPacientePorApellido (char nombreArchivo[], char apellido[]);
stPaciente busquedaPaciente(char nombreArchivo[]);
stPaciente validaciones(char nombreArchivo[],stPaciente paciente,int *flag);
stPaciente modificaUnPaciente(stPaciente paciente);
#endif // PACIENTES_H_INCLUDED
