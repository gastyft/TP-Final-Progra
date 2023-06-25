#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ESC 27

void menuPrincipal();

void menuPacientes();
void menuLaboratorios();
void menuPracticas();
void muestraTituloMenu(char titulo[]);
void replicaChar(char c, int cant);
void carga_puntos();
void firma();
#endif // MENUS_H_INCLUDED
