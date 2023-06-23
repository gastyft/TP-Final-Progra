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
    int cant=0,cantInac;
    FILE *archi = fopen(nombreArchivo, "a+b");
    if(archi!= NULL)
    {
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(practicas);
        do
        {
            cant+=1;
            rewind(archi);
            while(fread(&practicas,sizeof(stPracticas),1,archi))
            {
                if(practicas.baja!=0)
                {
                    cantInac++;
                }

            }
            if(cantInac>10)
            {
                printf("No se pueden agregar mas practicas \n");
                printf("Debe dar de baja alguna \n");


            }
            else
            {
                practicas = cargaUnaPractica();
                practicas.idPractica=cant;
                practicas= validacionesPractica(nombreArchivo,practicas);
                fwrite(&practicas, sizeof(stPracticas), 1, archi);
            }
            printf("\nESC para salir o cualquier tecla para continuar\n");
            opcion = getch();
        }
        while(opcion != ESC);
        fclose(archi);
    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
}

void muestraUnaPractica(stPracticas practica) ///FUNCION MUESTRA UNA PRACTICA:
{
    printf("\n ID: %d", practica.idPractica);
    printf("\n Nombre: %s", practica.nombre);
    printf("\n Costo %d", practica.costo);
    if(practica.baja ==0)
    {
        printf("\n PRACTICA ACTIVA\n");
    }
    else
    {
        printf("\n PRACTICA INACTIVA\n");
    }
    printf(" ==========================\n");
}

///MUESTRA ARCHIVO PRACTICAS:
void muestraArchivoPracticas(char nombreArchivo[])
{
    stPracticas practicas;
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&practicas, sizeof(stPracticas), 1, archi) > 0)
        {
            muestraUnaPractica(practicas);
        }
        fclose(archi);
    }
}

stPracticas busquedaPractica (char nombreArchivo[]) ///FUNCION BUSQUEDA PRACTICA POR NOMBRE
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
    return practicas;
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


        while(flag && fread(&practicas,sizeof(stPracticas),1,archivo))
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
/*
void validacionesPracticaId(char nombreArchivo[])
{

stPracticas practica;
   FILE * archivo= fopen(nombreArchivo, "r+b");
    int cant=0,cantInac;
   if(archivo!= NULL){

    fseek(archivo,0,SEEK_END);

   }
   else{
    printf("ERROR AL ABRIR ARCHIVO \n");
   }


fclose(archivo);

}
*/






