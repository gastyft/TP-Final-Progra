#include "menus.h"
#include "practicas.h"
#include "pacientes.h"
#include "laboratorios.h"

void muestraTituloMenu(char titulo[])
{
    printf("\n");
    replicaChar('*', 50);
    printf("%s", titulo);
    replicaChar('*', 50);
}

void replicaChar(char c, int cant)
{
    for(int i=0; i<cant; i++)
    {
        printf("%c", c);
    }
}
void menuPrincipal() ///FUNCION PARA MENU PRINCIPAL
{
    char opcion=0;
    system("COLOR B");
    printf("Abriendo APP, espere");
    carga_puntos();
    do
    {
        muestraTituloMenu("\n\t\tMENU PRINCIPAL\n");
        printf("\n Seleccione una opcion:\n");
        printf("\n 1) Pacientes");
        printf("\n 2) Laboratorio");
        printf("\n 3) Practicas");
        printf("\n\n ESC para salir\n");
        replicaChar('*', 50);
        fflush(stdin);
        opcion=getch();
        system("cls");
        switch(opcion)
        {
        case '1':
            menuPacientes();
            break;
        case '2':
            menuLaboratorios();
            break;
        case '3':
            menuPracticas();
            break;
        case 27:
           printf("Cerrando APP. Gracias por confiar en nosotros");
           carga_puntos();
           system("cls");
           firma();
            break;
        default:
            printf("\n\tHa seleccionado una opcion invalida.\n\tPor favor, presione cualquier tecla para continuar\n\n");
            fflush(stdin);
            opcion=getch();
            system("cls");
            break;
        }
    }
    while(opcion != ESC);
}

void menuPacientes()///FUNCION MENU PACIENTES
{
    char opcion=0;
    do
    {
        muestraTituloMenu("\n\t\tPACIENTES\n");
        printf("\n Seleccione una opcion:\n");
        printf("\n 1)Alta");
        printf("\n 2)Baja");
        printf("\n 3)Modificacion");
        printf("\n 4)Consulta");
        printf("\n 5)Listas");
        printf("\n\nESC para volver al menu principal\n");
        replicaChar('*', 50);
        fflush(stdin);
        opcion=getch();
        system("cls");
        switch(opcion)
        {
        case '1':
            menuAltasPacientes("pacientes.dat");
            system("cls");
            break;
        case '2':
            darBajaPacientes("pacientes.dat");
            system("pause");
            system("cls");
            break;
        case '3':
          menuModificacion("pacientes.dat");
            break;
        case '4':
            busquedaPaciente("pacientes.dat");
            break;
        case '5':
            muestraArchivoPacientes("pacientes.dat");
            printf(" \n");
            printf(" ");
            system("pause");
            system("cls");
            break;
        case 27:
            break;
        default:
            printf("\n\tHa seleccionado una opcion invalida.\n\tPor favor, presione cualquier tecla para continuar\n\n");
            fflush(stdin);
            opcion=getch();
            system("cls");
            break;
        }
    }
    while(opcion != ESC);
}
void menuLaboratorios() ///MENU LABORATORIO:
{
    char opcion=0;
    do
    {
        muestraTituloMenu("\n\t\tLABORATORIO\n");
        printf("\n Seleccione una opcion:\n");
        printf("\n 1)Alta");
        printf("\n 2)Baja");
        printf("\n 3)Modificacion");
        printf("\n 4)Consulta");
        printf("\n 5)Listas");
        printf("\n 6)Laboratorios aleatorios");
        printf("\n\nESC para volver al menu principal\n");
        replicaChar('*', 50);
        fflush(stdin);
        opcion=getch();
        system("cls");
        switch(opcion)
        {
        case '1':
           menuAltasLaboratorios("laboratorios.dat");
            system("cls");
            break;
        case '2':
            darBajaLaboratorios("laboratorios.dat");
            break;
        case '3':
         modificacionLaboratorio("laboratorios.dat");
            break;
        case '4':
            busquedaLaboratorio ("laboratorios.dat");
            printf("\n");
            system("pause");
                system("cls");
            break;
        case '5':


         muestraArchivoLaboratorios("laboratorios.dat");
         printf("\n");
            system("pause");
            system("cls");
            break;
        case '6':
            laboratoriosAleatorios("laboratorios.dat");
            break;
        case 27:
            break;
        default:
            printf("\n\tHa seleccionado una opcion invalida.\n\tPor favor, presione cualquier tecla para continuar\n\n");
            fflush(stdin);
            opcion=getch();
            system("cls");
            break;
        }
    }
    while(opcion != ESC);
}

void menuPracticas() ///MENU PRACTICA
{
    char opcion=0;
    do
    {
        muestraTituloMenu("\n\t\tPRACTICAS \n");
        printf("\n Seleccione una opcion:\n");
        printf("\n 1)Alta");
        printf("\n 2)Baja");
        printf("\n 3)Modificacion");
        printf("\n 4)Consulta");
        printf("\n 5)Listas");

        printf("\n\nESC para volver al menu principal\n");
        replicaChar('*', 50);
        fflush(stdin);
        opcion=getch();
        system("cls");
        switch(opcion)
        {
        case '1':
            menuAltasPracticas("practicas.dat");
            system("cls");
            break;
        case '2':
            darBajaPracticas("practicas.dat");
            system("pause");
            system("cls");
            break;
        case '3':
            modificacionPractica("practicas.dat");
            break;
        case '4':
            busquedaPractica("practicas.dat");
            system("pause");
            system("cls");
            break;
        case '5':
            muestraArchivoPracticas("practicas.dat");
            printf("\n");
            system("cls");
            break;;
        case 27:
            break;
        default:
            printf("\n\tHa seleccionado una opcion invalida.\n\tPor favor, presione cualquier tecla para continuar\n\n");
            fflush(stdin);
            opcion=getch();
            system("cls");
            break;
        }
    }
    while(opcion != ESC);
}

void carga_puntos()
{
    int i,j;
    int num_puntos = 2;
    for (i = 0; i < 8; i++)
    {
        // Imprimir los puntos con movimiento

        for (j = 0; j < num_puntos; j++)
        {
            printf("..");
            usleep(300000); // Retraso de 300 milisegundos (0.3 segundos)
            printf("\b \b"); // Borrar el punto anterior mediante caracteres de escape
        }
    }
    system("cls");
}







