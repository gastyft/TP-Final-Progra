#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ESC 27
#include <string.h>



void menuPrincipal();
void menuPacientes();
void menuLaboratorios();
void menuPracticas();
void imprimircabecera(char cabecera[]);
void alta_paciente(FILE *archivo);
void modificar(FILE *archivo);
typedef struct
{
    int idPaciente; /// campo único y autoincremental
    char nombre[30];
    char apellido[30];
    char dni[10];
    char movil[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stPaciente;
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
    int idPractica; /// campo único y autoincremental
    char nombre[30];
    int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
    int baja; /// 0 si está activo - 1 si está eliminado
} stPracticas;
int main()
{
    system("COLOR A");
    FILE *bin=NULL;
alta_paciente(bin);
///menuPrincipal();




    return 0;
}

void menuPrincipal()
{

    char o=0;
    while(o!=ESC)
    {
        imprimircabecera("Menu Principal ");
        printf("\n1)Pacientes \n");
        printf("2)Laboratorio \n");
        printf("3)Practicas \n");
        fflush(stdin);
        o=getch();
        system("cls");
        switch(o)
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

            printf("FIN CODIGO \n");
            break;

        default:
            printf("Selecciono un numero invalido. Presione cualquier tecla para continuar o ESCAPE para finalizar \n");
            fflush(stdin);
            o=getch();
            if(o==ESC)
            {
                printf("Codigo Finalizado \n");
                break;
            }
        }


    }

}
void menuPacientes()
{

    char o=0;
    while(o!=ESC)
    {
        printf("1)Alta \n");
        printf("2)Baja \n");
        printf("3)Modificacion \n");
        printf("4)Consulta \n");
        printf("5)Listas \n");
        printf("Si desea volver al menu principal pulse ESC \n");
        fflush(stdin);
        o=getch();
        system("cls");
        switch(o)
        {
        case '1':
///Alta
            break;
        case '2':
///Baja
            break;


        case '3':
///Modificacion
            break;
        case '4':
            ///Consulta
            break;
        case '5':
            ///Listado Pacientes
            break;

        case 27:

            printf("FIN CODIGO \n");
            break;
        default:
            printf("Selecciono un numero invalido. Presione cualquier tecla para continuar o ESCAPE para volver al menu principal\n");
            fflush(stdin);
            o=getch();
            system("cls");
        }


    }
}

    void menuLaboratorios()
    {

        char o=0;
        while(o!=ESC)
        {
             printf("1)Alta \n");
        printf("2)Baja \n");
        printf("3)Modificacion \n");
        printf("4)Consulta \n");
        printf("5)Listas \n");
     printf("Si desea volver al menu principal pulse ESC \n");
        fflush(stdin);
        o=getch();
        system("cls");

            switch(o)
            {
            case '1':
///Alta
                break;
            case '2':
///Baja
                break;

            case '3':
///Modificacion
                break;
            case '4':
                ///Consulta
                break;
            case '5':
                ///Listado Laboratorios
                break;;
            case 27:

                printf("FIN CODIGO \n");
        break;


            default:
                printf("Selecciono un numero invalido. Presione cualquier tecla para continuar o ESCAPE para volver al menu principal\n");
                fflush(stdin);
                o=getch();
                system("cls");
            }


        }


    }


void menuPracticas()
{

    char o=0;
    while(o!=ESC)
    {
        printf("1)Alta \n");
        printf("2)Baja \n");
        printf("3)Modificacion \n");
        printf("4)Consulta \n");
        printf("5)Listas \n");

     printf("Si desea volver al menu principal pulse ESC \n");
        fflush(stdin);
        o=getch();
        system("cls");

        switch(o)
        {
        case '1':
///Alta
            break;
        case '2':
///Baja
            break;


        case '3':
///Modificacion
            break;
        case '4':
            ///Consulta
            break;
        case '5':
            ///Listado Practicas
            break;


            break;
        case 27:

            printf("FIN CODIGO \n");

        break;
        default:
            printf("Selecciono un numero invalido. Presione cualquier tecla para continuar o ESCAPE para volver al menu principal\n");
            fflush(stdin);
            o=getch();
           system("cls");
        }


    }

}

void imprimircabecera(char cabecera[]){
int i;
printf("%c", 201);
for (i=0;i<50;i++){
    printf("%c", 205);
}
printf("%c\n", 187);
printf("%c%32s%19c\n", 186, cabecera,186);
printf("%c", 200);
for (i=0;i<50;i++){
    printf( "%c", 205);
}
printf("%c",188);
}

void alta_paciente(FILE *archivo){


stPaciente paciente;
    archivo = fopen("ARCH", "a+b" );
if ( archivo != NULL) {
do {

printf("Ingrese nombre y apellido \n");
fflush(stdin);
gets(paciente.nombre);
printf("Ingrese apellido \n");
gets(paciente.apellido);
printf("Ingrese DNI\n");
fflush(stdin);
gets(paciente.dni);
printf("Ingrese movil \n");
gets(paciente.movil);

paciente.eliminado=0;


fwrite (&paciente, sizeof (stPaciente), 1, archivo);

printf ( "Presione ESC para terminar \n" );
} while ((getche ()) != ESC );
}
else{
printf("ERROR de datos");
}
fclose (archivo);

}
void modificar(FILE *archivo)
{

    archivo=fopen("ARCH","r+b");
    stPaciente paciente;
    char aux[30];
    printf("Ingrese el DNI del paciente a modificar \n");
    fflush(stdin);
    gets(aux);
  ///  fseek(archivo,0,SEEK_SET);

 while ( fread (&paciente, sizeof (stPaciente), 1 , archivo) > 0) {
     if(strcmp(paciente.dni,aux) == 0){


printf("Ingrese nombre y apellido \n");
fflush(stdin);
gets(paciente.nombre);
printf("Ingrese apellido \n");
gets(paciente.apellido);
printf("Ingrese DNI\n");
fflush(stdin);
gets(paciente.dni);
printf("Ingrese movil \n");
gets(paciente.movil);

paciente.eliminado=0;

    fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);

    fwrite(&paciente,sizeof(stPaciente),1,archivo);
    break;
     }

 }


    fclose(archivo);
}

