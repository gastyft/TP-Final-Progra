#include "pacientes.h"


stPaciente cargaUnPaciente()
{
    stPaciente paciente;

    printf("\nIngrese los datos del paciente:\n");
    printf("\n Nombre: ");
    fflush(stdin);
    gets(paciente.nombre);

    printf("\n Apellido: ");
    fflush(stdin);
    gets(paciente.apellido);

    printf("\n DNI: ");
    fflush(stdin);
    gets(paciente.dni);

    printf("\n Telefono: ");
    fflush(stdin);
    gets(paciente.movil);

    paciente.eliminado=0;

    return paciente;
}

///FUNCION MUESTRA UN PACIENTE:
void muestraUnPaciente(stPaciente paciente)
{
    if(paciente.eliminado==0){
        printf("\n PACIENTE ACTIVO ");
    }
    else{
        printf("\n PACIENTE INACTIVO ");
    }
    printf("\n ID: %d", paciente.idPaciente);
    printf("\n Nombre: %s", paciente.nombre);
    printf("\n Apellido: %s", paciente.apellido);
    printf("\n DNI: %s", paciente.dni);
    printf("\n Telefono: %s", paciente.movil);
    printf("\n =====================================");

}



///FUNCION CARGA UN ARCHIVO DE PACIENTES
void cargaArchivoPacientes(char nombreArchivo[])
{
    stPaciente paciente;
    char opcion=0;
     int cant=0;
     int flag=1;
    FILE *archi = fopen(nombreArchivo, "ab");
    if(archi)
    {
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(paciente);
        do
        {
            cant++;
            paciente = cargaUnPaciente();
            paciente.idPaciente=cant;

            paciente= validaciones(nombreArchivo,paciente,&flag);
            paciente.eliminado=0;
            if (flag==0){
                printf("No se cargara el paciente.\n");
            }
            else{
                 fwrite(&paciente, sizeof(stPaciente), 1, archi);
            }

            printf("\nESC para salir o cualquier tecla para continuar con una nueva carga");
            opcion = getch();
        }
        while(opcion != ESC);
        fclose(archi);
    }
}


void muestraArchivoPacientes(char nombreArchivo[]) ///MUESTRA ARCHIVO PACIENTES
{
    stPaciente paciente;
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&paciente, sizeof(stPaciente), 1, archi) > 0)
        {
            muestraUnPaciente(paciente);
        }
        fclose(archi);
    }
}



void darBajaPacientes(char nombreArchivo[]) ///DAR DE BAJA PACIENTES
{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    stPaciente paciente;
    int flag=1;
    char dni[30];
    if(archivo != NULL)
    {
    printf("Ingrese dni \n");
    fflush(stdin);
    gets(dni);


     while(flag && fread(&paciente,sizeof(stPaciente),1,archivo)){
            if(strcmpi(paciente.dni, dni)==0){
        if(paciente.eliminado == -1)
                {
            printf("Ya esta dado de baja el DNI %s \n",paciente.dni);
                flag=0;
                }
                else
                {



                     fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);
                    paciente.eliminado=-1;
                    fwrite(&paciente,sizeof(stPaciente),1,archivo);
                    flag=0;
                    printf("Baja exitosa \n");
                }
            }
        }
        if(flag)
        {
            printf("No se encontro practica con ese nombre. Intente nuevamente \n");


        }

    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
    fclose(archivo);
}

void opcionBuscaPacienteDNI (char nombreArchivo[]) ///BUSCAR PACIENTE DNI
{
    char dniABuscar[30];

   FILE * archivo= fopen(nombreArchivo, "rb");
    if (archivo!=NULL)
        {
        printf("Ingrese el DNI a buscar: ");
        fflush(stdin);
        gets(dniABuscar);
 system("cls");
        stPaciente paciente = buscarPacientePorDNI(nombreArchivo,dniABuscar);

        if (atoi(paciente.dni) != -1)
            {
            fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);
            muestraUnPaciente(paciente);
            }
        else
            {
            printf(" El paciente con el DNI %s NO EXISTE \n", dniABuscar);
            }

        }
    else
        {
        printf("FALLO AL ABRIR EL ARCHIVO\n");
        }
        fclose(archivo);
}


stPaciente buscarPacientePorDNI (char nombreArchivo[], char dni[])  /// BUSCAR PACIENTE POR DNI
{
    int flag=0;
    //  char o=0;
    stPaciente paciente;
FILE*    archivo=fopen(nombreArchivo,"r+b");
    if(archivo!=NULL)
    {
        while(flag==0 && fread(&paciente,sizeof(stPaciente),1,archivo)>0  )
        {
            if (strcmpi(paciente.dni,dni)==0)
            {
                flag=1;
            }

        }

    }

    if (!flag)
        {
        strcpy(paciente.dni, "-1");
        }

    return paciente;
}



stPaciente buscarPacientePorApellido (char nombreArchivo[], char apellido[]) /// BUSCAR PACIENTE POR APELLIDO
{
    int flag=0;
    //  char o=0;
    stPaciente paciente;
    FILE *archivo=fopen(nombreArchivo,"r+b");
    if(archivo!=NULL)
    {
        while(flag==0 && fread(&paciente,sizeof(stPaciente),1,archivo)>0)
        {
            if (strcmpi(paciente.apellido,apellido)==0)
            {
                flag=1;
            }

        }


    }

    if (!flag)
        {
        strcpy(paciente.apellido, "-1");
        }
fclose(archivo);
    return paciente;
}

void opcion_busca_paciente_apellido (char nombreArchivo[]) ///BUSCA PACIENTE POR APELLIDO
{
    char apellidoABuscar[30];

    FILE *archivo= fopen(nombreArchivo, "rb");
    if (archivo!=NULL)
        {
        printf("Ingrese el apellido a buscar: ");
        fflush(stdin);

        gets(apellidoABuscar);
 system("cls");
        stPaciente paciente = buscarPacientePorApellido(nombreArchivo,apellidoABuscar);

        if (atoi(paciente.apellido) != -1)
            {

            fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);
            muestraUnPaciente(paciente);
            }
        else
            {
            printf("El paciente con el apellido %s NO EXISTE \n", apellidoABuscar);
            }
        fclose(archivo);
        }
    else
        {
        printf("FALLO AL ABRIR EL ARCHIVO");
        }
}





/**
Validación en el ingreso de los Datos: dni del paciente
(que no se repita) y nombre de la práctica de
laboratorio (que no se repita).
*/
///VER VALIDACIONES PARA MODIFICAR Y LAS VALIDACIONES DE LABORATORIO

stPaciente validaciones(char nombreArchivo[],stPaciente paciente,int *flag) /// VALIDACIONES DE PACIENTE POR DNI
{
///dni,nombre,apellido vienen como parametros de la funcion alta y modificacion
    stPaciente pacienteValido;
char o=0;

   FILE *archivo=fopen(nombreArchivo,"r+b");
    rewind(archivo);

    while( *flag && fread(&pacienteValido,sizeof(stPaciente),1,archivo)>0 )
    {

        if(strcmpi(paciente.dni,pacienteValido.dni)==0){


            printf("El dni ya existe,presione cualquier tecla para cargar un nuevo DNI o ESCAPE para salir\n");

            fflush(stdin);
            o=getch();
            if(o==ESC){
                *flag=0;

            }
            else{
                    system("cls");
            printf("Ingrese nuevo DNI\n");
            fflush(stdin);
            gets(paciente.dni);
            rewind(archivo);

            }
         system("cls");
            }
        }
 system("cls");

    fclose(archivo);

    return paciente;
}



stPaciente busquedaPaciente (char nombreArchivo[]) ///SUB MENU DE BUSQUEDA POR DNI O APELLIDO
{
 char o=0;
    stPaciente paciente;
    while(o!=ESC)
    {
        printf("1)Buscar por DNI \n");
        printf("2)Buscar por  apellido\n");
        printf("Si desea volver a menu pacientes pulse ESC \n");
        fflush(stdin);
        o=getch();
        system("cls");

        switch(o)
        {
        case '1':
   opcionBuscaPacienteDNI(nombreArchivo);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '2':
            opcion_busca_paciente_apellido(nombreArchivo);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 27:

            break;
        }
    }
    return paciente;
}




