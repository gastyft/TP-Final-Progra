#include "practicas.h"

stPracticas cargaUnaPractica() ///FUNCION CARGA UNA PRACTICA
{
    stPracticas practica;
    printf("\nIngreso de practicas:\n");
    printf("\n Nombre: ");
    fflush(stdin);
    gets(practica.nombre);
    printf("\n Costo: ");
    scanf("%d",&practica.costo);
    practica.baja = 0;
    return practica;
}

void cargaArchivoPracticas(char nombreArchivo[]) ///FUNCION CARGA UN ARCHIVO DE PRACTICAS
{
    stPracticas practicas;
    char opcion=0;
    int cant=0,cantActivo=0;
    FILE *archi = fopen(nombreArchivo, "a+b");
    if(archi!= NULL)
    {
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(practicas);
        do
        {
            cant+=1;
            rewind(archi);
            cantActivo=0;
            while(fread(&practicas,sizeof(stPracticas),1,archi)>0)
            {
                if(practicas.baja==0)
                {
                    cantActivo+=1;
                }
            }
            if(10>cantActivo)
            {
                system("cls");
                practicas = cargaUnaPractica();
                practicas.idPractica=cant;
                practicas= validacionesPractica(nombreArchivo,practicas);
                practicas= validacionCosto(practicas);
                fwrite(&practicas, sizeof(stPracticas), 1, archi);
                printf("\nESC para volver al menu de practicas o cualquier tecla para continuar cargando\n");
            }
            else
            {
                printf("No se pueden agregar mas practicas \n");
                printf("Debe dar de baja alguna \n");
                printf("\nESC para volver al menu de practicas\n");
            }

            fflush(stdin);
            opcion = getch();
            system("cls");
        }
        while(opcion != ESC);
        fclose(archi);
    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
}


void muestraTodasLasPracticas(stPracticas practica)
{

    if(practica.baja ==0)
    {
        printf("\n PRACTICA ACTIVA");
    }
    else
    {
        printf("\n PRACTICA INACTIVA");
    }
    printf("\n ID: %d", practica.idPractica);
    printf("\n Nombre: %s", practica.nombre);
    printf("\n Costo %d", practica.costo);
    printf("\n ==========================");
}

void muestraPracticasActivas(stPracticas practica)
{
    if(practica.baja ==0)
    {
        printf("\n PRACTICA ACTIVA");
        printf("\n ID: %d", practica.idPractica);
        printf("\n Nombre: %s", practica.nombre);
        printf("\n Costo %d", practica.costo);
        printf("\n ==========================");
    }

}

void muestraPracticasInactivas(stPracticas practica)
{

    if(practica.baja ==-1)
    {
        printf("\n PRACTICA INACTIVA");
        printf("\n ID: %d", practica.idPractica);
        printf("\n Nombre: %s", practica.nombre);
        printf("\n Costo %d", practica.costo);
        printf("\n ==========================");
    }
}



///MUESTRA ARCHIVO PRACTICAS:
void muestraArchivoPracticas(char nombreArchivo[])
{
    stPracticas practicas;
    FILE *archi = fopen(nombreArchivo, "rb");
    char o=0;
    if(archi)
    {


        while(o !=ESC)
        {
            printf("\n 1)Mostrar todas las practicas\n 2)Mostrar practicas activas\n 3)Mostrar practicas inactivas\n");
            printf(" \nPresione ESC para volver al menu de practicas\n");
            fflush(stdin);
            o=getch();
            rewind(archi);
            system("cls");
            switch(o)
            {
            case '1':
                while(fread(&practicas, sizeof(stPracticas), 1, archi) > 0)
                {
                    muestraTodasLasPracticas(practicas);
                }
                printf("\n");
                system("pause");
                system("cls");
                break;
            case '2':
                while(fread(&practicas, sizeof(stPracticas), 1, archi) > 0)
                {
                    muestraPracticasActivas(practicas);
                }
                printf("\n");
                system("pause");
                system("cls");
                break;
            case '3':
                while(fread(&practicas, sizeof(stPracticas), 1, archi) > 0)
                {
                    muestraPracticasInactivas(practicas);
                }
                printf("\n");
                system("pause");
                system("cls");
                break;
            case 27:
                break;
            default:
                printf("Ingreso una opcion no valida.Presione una tecla cualquiera para continuar o ESC para volver al menu de practicas \n");
                fflush(stdin);
                o=getch();
                system("cls");
            }
        }


    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO \n");
    }
    fclose(archi);

}


void busquedaPractica (char nombreArchivo[]) ///FUNCION BUSQUEDA PRACTICA POR NOMBRE
{
    int flag=0;
    char nombreAuxiliar[30];
    stPracticas practicas;
    FILE*  archivo=fopen(nombreArchivo,"r+b");
    if(archivo)
    {
        printf("Ingrese nombre de practica a buscar \n");
        fflush(stdin);
        gets(nombreAuxiliar);

        system("cls");
        while(fread(&practicas,sizeof(stPracticas),1,archivo)>0)
        {
            if (strcmpi(practicas.nombre,nombreAuxiliar)==0)
            {
                if(practicas.baja ==0)
                {
                    printf("PRACTICA ACTIVA\n");
                }
                else
                {
                    printf("PRACTICA INACTIVA \n");
                }
                fseek(archivo,(-1)*sizeof(stPracticas),SEEK_CUR);
                fread(&practicas,sizeof(stPracticas),1,archivo);
                printf("ID Practica: %d \n",practicas.idPractica);
                printf("NOMBRE: %s \n",practicas.nombre);
                printf("COSTO  %d \n",practicas.costo);
                flag=1;
            }
        }
        if(!flag)
        {
            printf("No existe la practica buscada\n");
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARCHIVO\n");
    }
    fclose(archivo);
}

void darBajaPracticas(char nombreArchivo[])   ///FUNCION DAR BAJA PRACTICAS
{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    stPracticas practicas;
    int flag=1;
    char nombre[30];
    if(archivo != NULL)
    {
        printf("Ingrese Practica \n");
        fflush(stdin);
        gets(nombre);
        while(flag && fread(&practicas,sizeof(stPracticas),1,archivo)>0)
        {
            if(strcmpi(practicas.nombre, nombre)==0)
            {
                if(practicas.baja == -1)
                {
                    printf("Ya esta dada de baja la practica %s \n",practicas.nombre);
                    flag=0;
                }
                else
                {
                    fseek(archivo,(-1)*sizeof(stPracticas),SEEK_CUR);
                    practicas.baja=-1;
                    fwrite(&practicas,sizeof(stPracticas),1,archivo);
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

stPracticas validacionesPractica(char nombreArchivo[],stPracticas practica) ///VALIDACIONES PRACTICA PARA QUE NO SE REPITAN DATOS
{
    stPracticas practicaValido;
    FILE *archivo=fopen(nombreArchivo,"r+b");
    rewind(archivo);
    while( fread(&practicaValido,sizeof(stPracticas),1,archivo)>0 )
    {
        if(strcmpi(practica.nombre,practicaValido.nombre)==0)
        {
            printf("La practica ya existe, ingrese una nueva practica\n");
            printf("Ingrese nombre de practica nueva \n");
            fflush(stdin);
            gets(practica.nombre);
            rewind(archivo);
        }
    }
    fclose(archivo);
    return practica;
}

stPracticas validacionCosto( stPracticas valPracticas)
{
    int flag=1;
    while(flag)
    {
        if( valPracticas.costo >= 1000 && valPracticas.costo <= 10000)
        {
            flag = 0;
        }
        else
        {
            printf("Ingreso un costo no valido, ingrese un nuevo costo entre 1000 y 10000\n");
            scanf("%d",&valPracticas.costo);
            system("cls");
        }
    }
    return valPracticas;
}
void darAltaInactivo(char nombreArchivo[])
{
    FILE*archivo= fopen(nombreArchivo,"r+b");
    int flag=1;
    int flag1=1;
    char nombre[30];
    stPracticas practica;
    if(archivo)
    {
        while(fread(&practica,sizeof(stPracticas),1,archivo)>0){

       muestraPracticasInactivas(practica);
       if(practica.baja==-1){
        flag1=0;
       }

        }
            if(!flag1){
            printf("\nIngrese nombre de practica a dar de alta\n");
            fflush(archivo);
            gets(nombre);

            }
        do
        {
            rewind(archivo);
            while( flag && fread(&practica,sizeof(stPracticas),1,archivo)>0)
            {
                if(strcmpi(practica.nombre,nombre)==0)
                {
                    if(practica.baja != 0)
                    {
                        practica.baja=0;
                        flag=0;

                        fseek(archivo,(-1)*sizeof(stPracticas),SEEK_CUR);
                        fwrite(&practica,sizeof(stPracticas),1,archivo);
                        system("cls");
                        printf("DADO DE ALTA CORRECTAMENTE \n");
                        muestraPracticasActivas(practica);
                    }
                }
            }

            if(flag && flag1==0)
            {

                printf("\nIngreso un nombre incorrecto. ingrese un nombre que este inactivo\n");
                fflush(stdin);
                gets(nombre);
            }
            else{
                printf("No hay practicas inactivas \n");
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

void menuAltasPracticas(char nombreArchivo[])
{

    char o=0;


    do
    {

        printf("1)Dar alta una nueva practica\n 2)Dar alta una practica inactiva\n");
        fflush(stdin);
        o=getch();
        system("cls");

        switch(o)
        {
        case '1':
            cargaArchivoPracticas(nombreArchivo);
            printf("\n");
            system("pause");
            system("cls");
            break;

        case '2':
            darAltaInactivo(nombreArchivo);
             printf("\n");
            system("pause");
            system("cls");
            break;
        case 27:

            break;
        default:

            printf("Ingreso opcion correcta presione cualquier tecla para continuar o ESC para salir a menu de Practicas\n");
            fflush(stdin);
            o=getch();
        }

    }
    while(o!=ESC);




}


