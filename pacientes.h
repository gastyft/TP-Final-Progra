#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ESC 27

typedef struct
{
    int idPaciente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char movil[12];
    int eliminado;
} stPaciente;




void muestraUnPaciente(stPaciente paciente);
void cargaArchivoPacientes(char nombreArchivo[]);
void muestraArchivoPacientes(char nombreArchivo[]);
void opcionBuscaPacienteDNI (char nombreArchivo[]);
void darBajaPacientes(char nombreArchivo[]);
void opcion_busca_paciente_apellido (char nombreArchivo[]);
stPaciente cargaUnPaciente();
stPaciente buscarPacientePorDNI (char nombreArchivo[], char dni[]);
stPaciente buscarPacientePorApellido (char nombreArchivo[], char apellido[]);
stPaciente busquedaPaciente(char nombreArchivo[]);


#endif // PACIENTES_H_INCLUDED
