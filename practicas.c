#include "practicas.h"
///FUNCION CARGA UNA PRACTICA
stPracticas cargaUnaPractica()
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



///FUNCION CARGA UN ARCHIVO DE PRACTICAS
void cargaArchivoPracticas(char nombreArchivo[])
{
    stPracticas practicas;
    char opcion=0;
    int cant=0;
    FILE *archi = fopen(nombreArchivo, "a+b");
    if(archi!= NULL)
    {
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(practicas);
        do
        {
            cant+=1;
            practicas = cargaUnaPractica();
            practicas.idPractica=cant;
            fwrite(&practicas, sizeof(stPracticas), 1, archi);
            printf("\nESC para salir o cualquier tecla para continuar");
            opcion = getch();
        }
        while(opcion != ESC);
        fclose(archi);
    }
    else{
        printf("ERROR EN EL ARCHIVO \n");
    }
}

///FUNCION MUESTRA UNA PRACTICA:
void muestraUnaPractica(stPracticas practica)
{
    printf("\n ID: %d", practica.idPractica);
    printf("\n Nombre: %s", practica.nombre);
    printf("\n Costo %d", practica.costo);
    if(practica.baja ==0){
        printf("\nPRACTICA ACTIVA\n");
    }
    else{
        printf("\nPRACTICA INACTIVA\n");
    }
    printf("\n =====================================\n");
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


stPracticas busquedaPractica (char nombreArchivo[])
{
    int flag=0;
    char nombreAuxiliar[30];
    stPracticas practicas;
   FILE*  archivo=fopen(nombreArchivo,"r+b");
   if(archivo){
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
                printf("NOMBRE: %s \n",practicas.nombre);
                printf("COSTO  %d \n",practicas.costo);
                flag=1;

            }
        }
        if(!flag){
            printf("No existe la practica buscada\n");
        }
   }
   else{
    printf("ERROR AL ABRIR ARCHIVO\n");
   }

    fclose(archivo);
    return practicas;
}



void darBajaPracticas(char nombreArchivo[])

{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    stPracticas practicas;

    char nombre[30];
    if(archivo != NULL)
    {
    printf("Ingrese dni \n");
    fflush(stdin);
    gets(nombre);


     while(fread(&practicas,sizeof(stPracticas),1,archivo)){
            if(strcmpi(practicas.nombre, nombre)==0){

           }
       }
                fseek(archivo,(-1)*sizeof(stPracticas),SEEK_CUR);

        practicas.baja=-1;




        fwrite(&practicas,sizeof(stPracticas),1,archivo);

    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
    fclose(archivo);
}


