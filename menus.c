#include "menus.h"
#include "practicas.h"
#include "pacientes.h"
#include "laboratorios.h"

void muestraTituloMenu(char titulo[])
{
    printf("\n");
    replicaChar('*', 50);

    printf("%s", titulo);

    printf("\n");
    replicaChar('*', 50);
}

void replicaChar(char c, int cant)
{
    for(int i=0; i<cant; i++)
    {
        printf("%c", c);
    }
}

///FUNCION PARA MENU PRINCIPAL:
void menuPrincipal()
{
    char opcion=0;
    do
    {
        muestraTituloMenu("\n\t\tMENU PRINCIPAL\n");
        printf("\n Seleccione una opcion:\n");
        printf("\n 1) Pacientes");
        printf("\n 2) Laboratorio");
        printf("\n 3) Practicas");
        printf("\n\n ESC para salir\n\n");

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
            printf("CODIGO FINALIZADO\n");
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
///FUNCION MENU PACIENTES:
void menuPacientes()
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
        printf("\n\nESC para volver al menu principal\n\n");

        replicaChar('*', 50);

        fflush(stdin);
        opcion=getch();
        system("cls");

        switch(opcion)
        {
        case '1':
            cargaArchivoPacientes("pacientes.dat");
            system("cls");
            break;
        case '2':
            darBajaPacientes("pacientes.dat");
            break;
        case '3':
            ///modificar();
            break;
        case '4':

          busquedaPaciente("pacientes.dat");
            break;
        case '5':
            muestraArchivoPacientes("pacientes.dat");
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

///MENU LABORATORIO:
void menuLaboratorios()
{
    char opcion=0;
    do
    {
        muestraTituloMenu("\n\t\tLABORAORIO\n");
        printf("\n Seleccione una opcion:\n");
        printf("\n 1)Alta");
        printf("\n 2)Baja");
        printf("\n 3)Modificacion");
        printf("\n 4)Consulta");
        printf("\n 5)Listas");
        printf("\n\nESC para volver al menu principal\n\n");

        replicaChar('*', 50);

        fflush(stdin);
        opcion=getch();
        system("cls");

        switch(opcion)
        {
        case '1':
            ///Alta
            break;
        case '2':
            darBajaLaboratorios("laboratorios.dat");
            break;
        case '3':
            ///Modificacion
            break;
        case '4':
            ///Consulta
            break;
        case '5':
            laboratoriosAleatorios("laboratorios.dat");
            muestraLaboratorio("laboratorios.dat");
            system("pause");
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

///MENU PRACTICA:
void menuPracticas()
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
        printf("\n\nESC para volver al menu principal\n\n");

        replicaChar('*', 50);

        fflush(stdin);
        opcion=getch();
        system("cls");

        switch(opcion)
        {
        case '1':
       cargaArchivoPracticas("practicas.dat");

            system("cls");
            break;
        case '2':
           darBajaPracticas("practicas.dat");
            printf("Baja exitosa \n");
            system("pause");
            break;
        case '3':
            ///Modificacion
            break;
        case '4':
           busquedaPractica("practicas.dat");
           system("pause");
           system("cls");
            break;
        case '5':
          muestraArchivoPracticas("practicas.dat");
             system("pause");
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



