#include "laboratorios.h"


void darBajaLaboratorios(char nombreArchivo[])

{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    int idLabs;
    stLaboratorios laboratorio;


    if(archivo != NULL)
    {
    printf("Ingrese dni \n");
    fflush(stdin);
    scanf("%d",&idLabs);


     while(fread(&laboratorio,sizeof(stLaboratorios),1,archivo)){
            if(laboratorio.idLab ==idLabs){

           }
       }
                fseek(archivo,(-1)*sizeof(stLaboratorios),SEEK_CUR);

        laboratorio.baja=-1;

  fwrite(&laboratorio,sizeof(stLaboratorios),1,archivo);

    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
    fclose(archivo);
}

void laboratoriosAleatorios(char nombreArchivo[])
{
    int cont;
    FILE *archiLab =fopen(nombreArchivo, "a+b");
    stFecha fecha;
    stLaboratorios laboratorio;
    time_t tiempo_actual;
    /**
     estructura  tm para saber de donde sale
    struct tm {
        int tm_sec;   // segundos [0-60]
        int tm_min;   // minutos [0-59]
        int tm_hour;  // horas [0-23]
        int tm_mday;  // día del mes [1-31]
        int tm_mon;   // mes [0-11]
        int tm_year;  //desde 1900 a año actual
        int tm_wday;  // día de la semana [0-6] (domingo = 0)
        int tm_yday;  // día del año [0-365]
        int tm_isdst; // horario de verano (0 = no, >0 = sí, <0 = desconocido) // eso no lo entendi
    };
    */
//Fin estructura TM

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


            fseek(archiLab,0,SEEK_END);
            cont=ftell(archiLab)/sizeof(laboratorio);

            // idLab ///CAMPO AUTOINCREMENTAL VER

            laboratorio.idPaciente=  rand()%10 +1;

            laboratorio.anio = fecha.anio;
            laboratorio.mes =fecha.mes;
            laboratorio.dia= fecha.dia;
            laboratorio.PracticaRealizada= 1+ rand() % 10;
            laboratorio.baja =0;
            cont++;
            laboratorio.idLab=cont;

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

void muestraLaboratorio (char nombreArchivo[])
{
    stLaboratorios laboratorio;
    FILE *archivo=fopen(nombreArchivo,"r+b");
    if (archivo!=NULL)
{
    while(fread(&laboratorio,sizeof(stLaboratorios),1,archivo)>0)
    {

    if(laboratorio.baja==0)
    {
        printf("LABORATORIO ACTIVO\n");
    }
    else
    {
        printf("LABORATORIO INACTIVO\n");
    }
    printf("ID: %d  \n",laboratorio.idLab);
}

}
else{
printf("ERROR AL ABRIR EL ARCHIVO \n");


}
fclose(archivo);
}
