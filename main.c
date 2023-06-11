#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ESC 27
#include <string.h>
#include <unistd.h>
#include <time.h>

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

typedef struct
{
    int dia;
    int mes;
    int anio;
} stFecha;

///--------MENUS------------
void menuPrincipal();
void menuPacientes();
void menuLaboratorios();
void menuPracticas();
void imprimircabecera(char cabecera[]);
///--------------------------

///---------CRUD-----------
void altaPaciente(FILE *archivo);
void modificar(FILE *archivo);
void mostrarPacientes(FILE *archivo);
///--------------------------------------

///---------LABS ALEATORIOS------------------
void mostrar_laboratorios(FILE *archivo);
void laboratoriosAleatorios(FILE *archiLab);
///-------------------------------------

///------VALIDACIONES--------------
stPaciente  validaciones(FILE *archivo,stPaciente paciente);

int main()
{
    system("COLOR B");
    FILE *bin=NULL;

    altaPaciente(bin);
///menuPrincipal();
   // laboratoriosAleatorios(bin);
   // mostrar_laboratorios(bin);
    mostrarPacientes(bin);
 modificar(bin);
   mostrarPacientes(bin);
    fclose(bin);
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

void imprimircabecera(char cabecera[])
{
    int i;
    printf("%c", 201);
    for (i=0; i<50; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c%32s%19c\n", 186, cabecera,186);
    printf("%c", 200);
    for (i=0; i<50; i++)
    {
        printf( "%c", 205);
    }
    printf("%c",188);
}

void altaPaciente(FILE *archivo)
{


    stPaciente paciente;
    stPaciente pacienteV;
    archivo = fopen("ARCH", "a+b" );
    if ( archivo != NULL)
    {
        do
        {

            printf("Ingrese nombre y apellido \n");
            fflush(stdin);
            gets(paciente.nombre);
            printf("Ingrese apellido \n");
            fflush(stdin);
            gets(paciente.apellido);
            printf("Ingrese DNI\n");
            fflush(stdin);
            gets(paciente.dni);
            printf("Ingrese movil \n");
            fflush(stdin);
            gets(paciente.movil);
    ///Posible lugar donde iria la validacion

           strcpy(pacienteV.movil,paciente.movil);
            pacienteV.eliminado=paciente.eliminado;
            pacienteV.idPaciente=paciente.idPaciente;
           pacienteV= validaciones(archivo,paciente);
            fwrite (&pacienteV, sizeof (stPaciente), 1, archivo);

            printf ( "Presione ESC para terminar \n" );
        }
        while ((getche ()) != ESC );
    }
    else
    {
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

    while ( fread (&paciente, sizeof (stPaciente), 1, archivo) > 0)
    {
        if(strcmp(paciente.dni,aux) == 0)
        {


            printf("Ingrese nombre y apellido a modificar \n");
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
            validaciones(archivo,paciente);
            fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);

            fwrite(&paciente,sizeof(stPaciente),1,archivo);
            break;
        }

    }


    fclose(archivo);
}


/**
Alta de Laboratorios aleatorios anteriores a la fecha
actual. La función deberá agregar 100, eligiendo de
manera aleatoria el paciente, la fecha (del año actual)
y la practica realizada (entre 1 y 10).Pueden haber
más de 1 laboratorio para el mismo paciente en la
misma fecha.
*/

void laboratoriosAleatorios(FILE *archiLab)
{
    archiLab =fopen("ARCHLAB", "a+b");
    stFecha fecha;
    stLaboratorios laboratorio;
    time_t tiempo_actual;
    struct tm *info_tiempo;
    char dia[3];
    char mes[3];
    char anio[5];
    int diaActual,mesActual,anioActual,diasMaximos=0,i=0;

    // Obtenemos el tiempo actual
    tiempo_actual = time(NULL);

    // Convertimos el tiempo a una estructura de tm
    info_tiempo = localtime(&tiempo_actual);

    // Obtenemos el día del mes como cadena
    strftime(dia, sizeof(dia), "%d", info_tiempo);
    strftime(mes, sizeof(mes),"%m",info_tiempo);
    strftime(anio, sizeof(anio),"%Y",info_tiempo);

    // Convertimos la cadena a entero
    diaActual = atoi(dia);
    mesActual = atoi(mes);
    anioActual =atoi(anio);

    if(archiLab!= NULL)
    {
//srand(time(NULL));
        do
        {

            fecha.anio=rand()%(anioActual-2018 +1)+2018;

            if(fecha.anio ==anioActual)
            {
                fecha.mes = rand()%(mesActual-1)+1;
                if(fecha.mes == mesActual)
                {
                    switch (fecha.mes)
                    {
                    case 2:
                        // Verificar si el año es bisiesto para febrero
                        if ((fecha.anio % 4 == 0 && fecha.anio % 100 != 0) || fecha.anio % 400 == 0)
                            diasMaximos = 29;
                        else
                            diasMaximos = 28;
                        break;
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        diasMaximos = 30;
                        break;
                    default:
                        diasMaximos = 31;
                        break;
                    }

                    fecha.dia = 1 + rand() % diaActual;
                }
                else
                {


                    switch (fecha.mes)
                    {
                    case 2:
                        // Verificar si el año es bisiesto para febrero
                        if ((fecha.anio % 4 == 0 && fecha.anio % 100 != 0) || fecha.anio % 400 == 0)
                            diasMaximos = 29;
                        else
                            diasMaximos = 28;
                        break;
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        diasMaximos = 30;
                        break;
                    default:
                        diasMaximos = 31;
                        break;
                    }

                    fecha.dia = 1 + rand() % diasMaximos;


                }


            }
            else
            {
                fecha.mes = rand()%(12-1)+1;
                switch (fecha.mes)
                {
                case 2:
                    // Verificar si el año es bisiesto para febrero
                    if ((fecha.anio % 4 == 0 && fecha.anio % 100 != 0) || fecha.anio % 400 == 0)
                        diasMaximos = 29;
                    else
                        diasMaximos = 28;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    diasMaximos = 30;
                    break;
                default:
                    diasMaximos = 31;
                    break;
                }

                fecha.dia = 1 + rand() % diasMaximos;


            }




            // idLab ///CAMPO AUTOINCREMENTAL VER
            laboratorio.idPaciente=  rand()%10 +1; ///VER SI HAY QUE TRAER LOS PACIENTES ACTUALES O SE EJECUTA CON 10 PACIENTES POR DEFAULT

            laboratorio.anio = fecha.anio;
            laboratorio.mes =fecha.mes;
            laboratorio.dia= fecha.dia;
            laboratorio.PracticaRealizada= 1+ rand() % 10;
            laboratorio.baja =0;

            i++;

        }
        while(i<101 && fwrite(&laboratorio,sizeof(laboratorio),1,archiLab)>0);

    }
    else
    {
        printf("ERROR AL ABRIR O CREAR EL ARCHIVO \n");
    }
    fclose(archiLab);
}

void mostrar_laboratorios(FILE *archivo)
{

    stLaboratorios laboratorio;
    int cant,j=0;
    archivo= fopen("ARCHLAB", "r+b");
    if(archivo != NULL)
    {

        while(!feof(archivo))
        {

            cant=fread(&laboratorio,sizeof(stLaboratorios),1,archivo);

            for(int i=0; i<cant; i++)
            {

                printf("PACIENTE: %d \n",laboratorio.idPaciente);
                printf("DIA MES ANIO: %d/%d/%d \n",laboratorio.dia,laboratorio.mes,laboratorio.anio);
                printf("ACTIVO 0 si 1 no: %d \n",laboratorio.baja);
                printf("PRACTICAS %d \n",laboratorio.PracticaRealizada);
                printf(" CANTIDAD: %d \n",j);
                printf("-----------------\n");
                j++;
            }
        }


        fclose(archivo);
    }
}



/**
Validación en el ingreso de los Datos: dni del paciente
(que no se repita) y nombre de la práctica de
laboratorio (que no se repita).
*/
///VER VALIDACIONES PARA MODIFICAR Y LAS VALIDACIONES DE LABORATORIO

stPaciente validaciones(FILE *archivo,stPaciente paciente)
{
  stPaciente pacienteValido;
  /**  pacienteValido.idPaciente=paciente.idPaciente;
    pacienteValido.movil=paciente.movil;
    pacienteValido.eliminado=paciente.eliminado;  */

    archivo=fopen("ARCH","r+b");
while(fread(&pacienteValido,sizeof(stPaciente),1,archivo)>0)
    {
        while(strcmpi(pacienteValido.nombre,paciente.nombre)==0 && strcmpi(pacienteValido.apellido,paciente.apellido)==0)
        {
            printf("El nombre y apellido ya existe, ingrese otro nombre y apellido \n");

            printf("Ingrese nombre nuevo \n");
            fflush(stdin);
            gets(paciente.nombre);
            printf("Ingrese Apellido nuevo \n");
            fflush(stdin);
            gets(paciente.apellido);
        }
    }
      rewind(archivo);

    while(fread(&pacienteValido,sizeof(stPaciente),1,archivo)>0)
    {
///dni,nombre,apellido vienen como parametros de la funcion alta y modificacion

        while(strcmpi(paciente.dni,pacienteValido.dni)==0)
        {

            printf("El dni ya existe, ingrese otro DNI \n");
            printf("Ingrese DNI nuevo \n");
            gets(paciente.dni);

        }
    }
    fclose(archivo);

    return paciente;
    }

void mostrarPacientes(FILE *archivo){
archivo=fopen("ARCH","r+b");
stPaciente paciente;
while(fread(&paciente,sizeof(stPaciente),1,archivo)>0){


    printf("NOMBRE: %s \n",paciente.nombre);
    printf("APELLIDO  %s\n",paciente.apellido);
    printf("DNI %s\n",paciente.dni);
    printf("movil %s\n",paciente.movil);

printf("----------------------------\n");
}

fclose(archivo);
}

