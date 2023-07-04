#include "pacientes.h"

///Funcion carga un paciente
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

    if(paciente.eliminado==0)
    {
        printf("\n PACIENTE ACTIVO ");
    }
    else
    {
        printf("\n PACIENTE INACTIVO ");
    }
    printf("\n ID: %d", paciente.idPaciente);
    printf("\n Nombre: %s", paciente.nombre);
    printf("\n Apellido: %s", paciente.apellido);
    printf("\n DNI: %s", paciente.dni);
    printf("\n Telefono: %s", paciente.movil);
    printf("\n Practica/s: ");
    practicaPaciente(paciente);
    printf("\n Costo total de las practicas realizadas: $%d",costoTotal(paciente));
    printf("\n =====================================");
}

void practicaPaciente(stPaciente paciente)
{
    FILE *archivo= fopen("practicas.dat","r+b");
    FILE *archivoLab= fopen("laboratorios.dat","r+b");
    stPracticas practica;
    stLaboratorios laboratorios;
    if(archivo != NULL)
    {

        while(fread(&laboratorios,sizeof(stLaboratorios),1,archivoLab)>0)  ///Reccorre archivo de labs buscando id del paciente con las practicas
        {
            if(paciente.idPaciente == laboratorios.idPaciente)
            {
                rewind(archivo);
                while(fread(&practica,sizeof(stPracticas),1,archivo)>0)
                {
                    if(laboratorios.PracticaRealizada== practica.idPractica)
                    {

                        printf("%s ",practica.nombre);
                    }



                }

            }
        }
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO \n");
    }

    fclose(archivo);
    fclose(archivoLab);

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
            if (flag==0)
            {
                printf("No se cargara el paciente.\n");
            }
            else
            {
                fwrite(&paciente, sizeof(stPaciente), 1, archi);
            }

            printf("\nESC para salir o cualquier tecla para continuar con una nueva carga");
            fflush(stdin);
            opcion = getch();
            system("cls");
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


        while(flag && fread(&paciente,sizeof(stPaciente),1,archivo)>0)
        {
            if(strcmpi(paciente.dni, dni)==0)
            {
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
            printf("No se encontro pacientes con ese DNI. Intente nuevamente. \n");
        }
    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
    fclose(archivo);
}

stPaciente opcionBuscaPacienteDNI (char nombreArchivo[]) ///BUSCAR PACIENTE DNI
{
    char dniABuscar[30];
    stPaciente paciente;
    FILE * archivo= fopen(nombreArchivo, "rb");
    if (archivo!=NULL)
    {
        printf("Ingrese el DNI a buscar: ");
        fflush(stdin);
        gets(dniABuscar);
        system("cls");
        paciente = buscarPacientePorDNI(nombreArchivo,dniABuscar);

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
    return paciente;
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
    if (flag==0)
    {
        char num[30];
        strcpy(num,"-1");
        strcpy(paciente.dni,num);

    }
    return paciente;
}

stPaciente buscarPacientePorApellido (char nombreArchivo[], char apellido[]) /// BUSCAR PACIENTE POR APELLIDO
{
    int flag=0;

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

stPaciente opcion_busca_paciente_apellido (char nombreArchivo[]) ///BUSCA PACIENTE POR APELLIDO
{
    char apellidoABuscar[30];
    stPaciente paciente;
    FILE *archivo= fopen(nombreArchivo, "rb");
    if (archivo!=NULL)
    {
        printf("Ingrese el apellido a buscar: ");
        fflush(stdin);
        gets(apellidoABuscar);
        system("cls");
        paciente = buscarPacientePorApellido(nombreArchivo,apellidoABuscar);
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
    return paciente;
}

stPaciente validaciones(char nombreArchivo[],stPaciente paciente,int *flag) /// VALIDACIONES DE PACIENTE POR DNI (que no exista otro DNI repetido)
{
///dni,nombre,apellido vienen como parametros de la funcion alta y modificacion
    stPaciente pacienteValido;
    char o=0;
    FILE *archivo=fopen(nombreArchivo,"r+b");
    rewind(archivo);
    while( *flag && fread(&pacienteValido,sizeof(stPaciente),1,archivo)>0 )
    {
        if(strcmpi(paciente.dni,pacienteValido.dni)==0)
        {
            printf("El dni ya existe,presione cualquier tecla para cargar un nuevo DNI o ESCAPE para salir\n");
            fflush(stdin);
            o=getch();
            if(o==ESC)
            {
                *flag=0;
            }
            else
            {
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

        switch(o)
        {
        case '1':
            paciente=   opcionBuscaPacienteDNI(nombreArchivo);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '2':
            paciente= opcion_busca_paciente_apellido(nombreArchivo);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 27:
            system("cls");
            break;
        }
    }
    return paciente;
}

int costoTotal(stPaciente paciente)   /// funcion que muestra el costo total por paciente
{
    FILE*archivo= fopen("practicas.dat","r+b");
    FILE *archivoLab=fopen("laboratorios.dat","r+b");
    stPracticas practica;
    stLaboratorios laboratorios;
    int costo=0;
    if(archivo !=NULL && archivoLab!=NULL)
    {
        while(fread(&laboratorios,sizeof(stLaboratorios),1,archivoLab)>0)  ///Reccorre archivo de labs buscando id del paciente con las practicas
        {
            if(paciente.idPaciente == laboratorios.idPaciente)
            {
                rewind(archivo);
                while(fread(&practica,sizeof(stPracticas),1,archivo)>0)
                {
                    if(laboratorios.PracticaRealizada== practica.idPractica)
                    {
                        costo+=practica.costo;
                    }
                }
            }
        }
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
    }
    fclose(archivo);
    fclose(archivoLab);
    return costo;
}


void darAltaInactivoPacientes(char nombreArchivo[]) /// Funcion dar alta pacientes inactivos
{
    FILE*archivo= fopen(nombreArchivo,"r+b");
    int flag=1;
    int flag1 =1;
    char dni[30];


    stPaciente paciente;
    if(archivo)
    {
        while(fread(&paciente,sizeof(stPaciente),1,archivo)>0)
        {
            if(paciente.eliminado==-1)
            {
            muestraPacientesInactivos(paciente);
                flag1=0;
            }
        }
        if(!flag1)
        {
            printf("\nIngrese DNI de paciente a dar de alta\n");
            fflush(stdin);
            gets(dni);

        }
        do
        {

            rewind(archivo);
            while( flag && fread(&paciente,sizeof(stPaciente),1,archivo)>0)
            {
                if(strcmpi(paciente.dni,dni)==0 )
                {
                    if(paciente.eliminado != 0)
                    {
                        paciente.eliminado=0;
                        flag=0;

                        fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);
                        fwrite(&paciente,sizeof(stPaciente),1,archivo);
                        system("cls");
                        printf("DADO DE ALTA CORRECTAMENTE \n");
                        muestraUnPaciente(paciente);
                    }
                }
            }

            if(flag && flag1==0)
            {

                printf("\nIngreso un DNI incorrecto.Ingrese un DNI que este inactivo\n");
                printf("Ingrese DNI:\n");

                fflush(stdin);
                gets(dni);

            }
            else
            {
                printf("\nNo hay pacientes inactivos \n");
                flag=0;
            }
        }

        while(flag);



    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
    }

    fclose(archivo);
}

void menuAltasPacientes(char nombreArchivo[]) ///Menu de alta de pacientes nuevos o inactivos
{

    char o=0;

    do
    {

        printf("1)Dar alta un nuevo paciente\n2)Dar alta un paciente inactivo\n");
        fflush(stdin);
        o=getch();
        system("cls");

        switch(o)
        {
        case '1':
            cargaArchivoPacientes(nombreArchivo);
            system("pause");
            system("cls");
            break;

        case '2':

            darAltaInactivoPacientes(nombreArchivo);
            system("pause");
            system("cls");
            break;
        case 27:

            break;
        default:

            printf("Ingreso opcion incorrecta presione cualquier tecla para continuar o ESC para salir a menu de Pacientes\n");
            fflush(stdin);
            o=getch();
        }

    }
    while(o!=ESC);




}

void muestraPacientesInactivos(stPaciente paciente) /// Muestra pacientes inactivos
{

    FILE *archi =fopen("pacientes.dat","r+b");
    if(archi)
    {

        while(fread(&paciente, sizeof(stPaciente), 1, archi) > 0)
        {
            if(paciente.eliminado== -1)
            {

                muestraUnPaciente(paciente);
            }
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARCHIVO \n");
    }
    fclose(archi);


}
void muestraPacientesActivos(stLaboratorios paciente) /// Muestra pacientes activos conteniendo a muestra un laboratorio
{

    FILE *archi =fopen("paciente.dat","r+b");
    if(archi)
    {

        while(fread(&paciente, sizeof(stPaciente), 1, archi) > 0)
        {
            if(paciente.baja== 0)
            {
                printf("\n paciente ACTIVO");
                muestraUnLaboratorio(paciente);
            }
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARCHIVO \n");
    }
    fclose(archi);


}

void modificacion(char nombreArchivo[],stPaciente paciente ) /// FUNCION CONTENEDORA DE MODIFICA UN PACIENTE
{
    stPaciente pacienteV;

    FILE *archivo =fopen(nombreArchivo,"r+b");

    pacienteV=modificaUnPaciente(paciente);
    system("pause");
    system("cls");
    rewind(archivo);
    fseek(archivo,(pacienteV.idPaciente-1)*sizeof(stPaciente),SEEK_SET);
    fwrite(&pacienteV,sizeof(stPaciente),1,archivo);

    fclose(archivo);
    muestraUnPaciente(paciente);
    printf("\n");
    system("pause");
    system("cls");
}

void menuModificacion(char nombreArchivo[])  ///Menu de modificacion para buscar por DNI o por Apellido
{

    char o=0;
    stPaciente paciente;

    printf("1)Buscar por DNI \n");
    printf("2)Buscar por  apellido\n");
    fflush(stdin);
    o=getch();

    switch(o)
    {
    case '1':
        paciente=opcionBuscaPacienteDNI(nombreArchivo);
        if(paciente.idPaciente ==-1)
        {
            printf("El paciente dado de baja no se puede modificar\n");
        }
        else
        {
            modificacion(nombreArchivo,paciente);
        }
        printf("\n");

        break;
    case '2':
        paciente= opcion_busca_paciente_apellido(nombreArchivo);
        if(paciente.idPaciente ==-1)
        {
            printf("El paciente dado de baja no se puede modificar\n");
        }
        else
        {
            modificacion(nombreArchivo,paciente);
        }

        printf("\n");

        break;
    }
}

stPaciente modificaUnPaciente(stPaciente paciente)    ///Modifica un paciente
{

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


    return paciente;
}









