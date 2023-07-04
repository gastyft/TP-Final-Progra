#include "laboratorios.h"

void darBajaLaboratorios(char nombreArchivo[]) ///DAR BAJA LABORATORIOS
{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    int idLabs;
    stLaboratorios laboratorio;
    int flag=1;
    if(archivo != NULL)
    {
        printf("Ingrese ID de laboratorio a dar de baja \n");
        fflush(stdin);
        scanf("%d",&idLabs);
        system("cls");
        while(flag && fread(&laboratorio,sizeof(stLaboratorios),1,archivo))
        {
            if(laboratorio.idLab ==idLabs)
            {
                if(laboratorio.baja == -1)
                {
                    printf("Ya esta dado de baja el Laboratorio %d \n",laboratorio.idLab);

                    flag=0;
                }
                else
                {
                    fseek(archivo,(-1)*sizeof(stLaboratorios),SEEK_CUR);
                    laboratorio.baja=-1;
                    fwrite(&laboratorio,sizeof(stLaboratorios),1,archivo);
                    flag=0;
                    printf("Baja exitosa \n");
                    system("pause");
                    system("cls");
                }
            }
        }
        if(flag)
        {
            printf("No se encontro el laboratorio con el ID %d. Intente nuevamente \n",idLabs);
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("ERROR EN EL ARCHIVO \n");
    }
    fclose(archivo);
}

void laboratoriosAleatorios(char nombreArchivo[]) /// LABORATORIOS ALEATORIOS
{
    int cont;
    FILE *archiLab =fopen(nombreArchivo, "a+b");
    stFecha fecha;
    stLaboratorios laboratorio;
    stPaciente paciente;
    stPracticas practica;
    FILE *archivo =fopen("pacientes.dat","r+b");
    int contadorTotalPacientes=0;
    FILE *archivoPrac =fopen("practicas.dat","r+b");
    int contadorTotalPrac=0;
    time_t tiempo_actual;  ///Estructura para extraer fecha actual
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

    /// Obtenemos el tiempo actual
    tiempo_actual = time(NULL);

    /// Convertimos el tiempo a una estructura de tm
    info_tiempo = localtime(&tiempo_actual);

    /// Obtenemos el día del mes como cadena
    strftime(dia, sizeof(dia), "%d", info_tiempo);
    strftime(mes, sizeof(mes),"%m",info_tiempo);
    strftime(anio, sizeof(anio),"%Y",info_tiempo);

    /// Convertimos la cadena a entero
    diaActual = atoi(dia);
    mesActual = atoi(mes);
    anioActual =atoi(anio);

    if(archiLab!= NULL)
    {
//srand(time(NULL));
        do
        {
            fecha.anio=rand()%(anioActual-2020 +1)+2020;
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

            if(archivo)
            {
                while(fread(&paciente,sizeof(stPaciente),1,archivo)>0)
                {
                    contadorTotalPacientes++;
                }
            }
            else
            {
                printf("ERROR AL ABRIR EL ARCHIVO\n");
            }
            if(archivoPrac)
            {
                while(fread(&practica,sizeof(stPracticas),1,archivoPrac)>0)
                {
                    contadorTotalPrac++;
                }
            }
            else
            {
                printf("ERROR AL ABRIR EL ARCHIVO\n");
            }
            laboratorio.idPaciente=  rand()%contadorTotalPacientes +1; ///FUNCION ACTIVA O INACTIVA PARA CONTAR CCON contador para activos Y HACER UN RAND CON EL TOTAL
            laboratorio.anio = fecha.anio;
            laboratorio.mes =fecha.mes;
            laboratorio.dia= fecha.dia;
            laboratorio.PracticaRealizada= rand() % contadorTotalPrac +1;  /// FUNCION ACTIVA O INACTIVA
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

void muestraUnLaboratorio(stLaboratorios laboratorio) /// Muestreo de un laboratorio
{
    FILE *archivo =fopen("pacientes.dat","r+b");
    FILE *archivoPrac =fopen("practicas.dat","r+b");
    int flag=1,flagP=1;
    stPracticas practicas;
    stPaciente paciente;
    if(archivo!=NULL && archivoPrac!=NULL)
    {
        printf("\n Laboratorio: %d", laboratorio.idLab);
        while(flag && fread(&paciente,sizeof(stPaciente),1,archivo)>0)
        {
            if(laboratorio.idPaciente == paciente.idPaciente)
            {
                fseek(archivo,(-1)*sizeof(stPaciente),SEEK_CUR);
                printf("\n %s %s",paciente.nombre,paciente.apellido);
                flag=0;
            }
        }
        while(flagP && fread(&practicas,sizeof(stPracticas),1,archivoPrac)>0)
        {
            if(laboratorio.PracticaRealizada == practicas.idPractica)
            {
                fseek(archivoPrac,(-1)*sizeof(stPracticas),SEEK_CUR);
                printf("\n %s",practicas.nombre);
                flagP=0;
            }
        }
        printf("\n fecha %d/%d/%d", laboratorio.dia,laboratorio.mes,laboratorio.anio);

        printf("\n____________________________ ");
    }
    fclose(archivo);
    fclose(archivoPrac);
}

void muestraArchivoLaboratorios(char nombreArchivo[]) ///MUESTRA ARCHIVO LABORATORIOS
{
    stLaboratorios laboratorios;
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&laboratorios, sizeof(stLaboratorios), 1, archi) > 0)
        {
            if(laboratorios.baja== -1)
            {
                printf("\n LABORATORIO INACTIVO");
            }
            else
            {
                printf("\n LABORATORIO ACTIVO");
            }
            muestraUnLaboratorio(laboratorios);
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO \n");
    }
}

stLaboratorios cargaUnLaboratorio() ///FUNCION CARGA UN LABORATORIO con las validaciones correspondientes
{
    stLaboratorios laboratorio;

    laboratorio.idPaciente= validacionId();

    laboratorio=validacionFecha(laboratorio);

    laboratorio=validacionPractica(laboratorio);

    return laboratorio;
}

void cargaArchivoLaboratorios(char nombreArchivo[]) ///FUNCION CARGA UN ARCHIVO DE LABORATORIOS
{
    stLaboratorios laboratorios;
    char opcion=0;
    int cant=0;
    FILE *archi = fopen(nombreArchivo, "ab");
    if(archi)
    {

        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(stLaboratorios);
        do
        {
            cant++;
            laboratorios = cargaUnLaboratorio();
            laboratorios.idLab=cant;
            system("cls");
            fwrite(&laboratorios, sizeof(stLaboratorios), 1, archi);
            borrar_logicamente(laboratorios,nombreArchivo);
            printf("\nESC para salir o cualquier tecla para continuar");
            opcion = getch();
        }
        while(opcion != ESC);
        fclose(archi);
    }
}

stLaboratorios busquedaLaboratorio(char nombreArchivo[]) ///FUNCION BUSQUEDA PRACTICA POR NOMBRE
{
    int flag=0;
    int idBuscar;
    stLaboratorios laboratorios;
    FILE*  archivo=fopen(nombreArchivo,"r+b");
    if(archivo)
    {
        printf("Ingrese el id del laboratorio a buscar \n");
        scanf("%d",&idBuscar);

        system("cls");
        while( !flag &&fread(&laboratorios,sizeof(stLaboratorios),1,archivo)>0)
        {
            if (laboratorios.idLab == idBuscar )
            {
                if(laboratorios.baja ==-1)
                {
                    printf("LABORATORIO INACTIVO\n");

                }
                else
                {
                    printf("LABORATORIO ACTIVO \n");
                }
                fseek(archivo,(-1)*sizeof(stLaboratorios),SEEK_CUR);
                muestraUnLaboratorio(laboratorios);
                flag=1;
            }
        }
        if(!flag)
        {
            printf("No existe el laboratorio buscado\n");
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARCHIVO\n");
    }
    fclose(archivo);
    return laboratorios;
}

int validacionId() /// VALIDACION DE UN ID DE PACIENTE PARA QUE NO SEA INEXISTENTE
{


    stPaciente paciente;
    int flag=1,id;
    FILE *archivo= fopen("pacientes.dat","r+b");
    if(archivo != NULL)
    {
        do
        {
            printf("\nId Paciente: ");
            scanf("%d", &id);
            rewind(archivo);
            while(flag && fread(&paciente,sizeof(stPaciente),1,archivo)>0 )
            {
                if(id == paciente.idPaciente)
                {
                    flag=0;
                }
            }
            if(flag)
            {
                printf("Ingreso un ID de paciente %d no existe en la base de datos. Ingrese uno nuevo.\n",id);
            }

        }
        while(flag);


    }
    else
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO\n");
    }
    return id;
}

stLaboratorios validacionFecha(stLaboratorios laboratorio) ///VALIDACION DE UNA FECHA MENOR A LA ACTUAL
{

    stFecha fecha;
    FILE *archiLab=fopen("laboratorios.dat","r+b");
    time_t tiempo_actual;

//Fin estructura TM
    struct tm *info_tiempo;
    char dia[3];
    char mes[3];
    char anio[5];
    int diaActual,mesActual,anioActual,diasMaximos=0;

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

        do
        {
            printf("Ingrese anio\n");
            scanf("%d",&fecha.anio);

        }
        while(fecha.anio<2020 || anioActual<fecha.anio);      ///PIDE AÑO MENOR O IGUAL A 2023



        if(fecha.anio == anioActual)  /// SI ES AÑO ACTUAL ENTONCES PIDE MES MENOR O IGUAL AL ACTUAL
        {
            do
            {
                printf("Ingrese mes\n");
                scanf("%d",&fecha.mes);
            }
            while(fecha.mes<1 || mesActual<fecha.mes);

            if(fecha.mes == mesActual) /// SI EL MES ES ACTUAL ENTONCES VALIDA QUE MES ES PARA ASIGNARLE LE MAXIMO DE DIAS DE ESE MES
            {

                do    /// si es menor al dia actual no habria porque validar en el switch
                {
                    printf("Ingrese dia\n");   /// PIDE UN DIA MENOR O IGUAL AL ACTUAL
                    scanf("%d",&fecha.dia);
                }
                while(fecha.dia<1 || diaActual<fecha.dia );

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
                do
                {
                    printf("Ingrese dia\n");
                    scanf("%d",&fecha.dia);
                }
                while(fecha.dia > diasMaximos);
            }
        }
        else /// si no es anio actual
        {
            do
            {
                printf("Ingrese mes\n");
                scanf("%d",&fecha.mes);
            }
            while(fecha.mes>12 || fecha.mes<1 );

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
            do
            {
                printf("Ingrese dia \n");
                scanf("%d",&fecha.dia);
            }
            while( fecha.dia<1   || fecha.dia >diasMaximos);

        }
    }

    else
    {
        printf("ERROR AL ABRIR O CREAR EL ARCHIVO \n");
    }
    laboratorio.dia=fecha.dia;
    laboratorio.anio=fecha.anio;
    laboratorio.mes=fecha.mes;
    fclose(archiLab);
    return laboratorio;
}

stLaboratorios validacionPractica(stLaboratorios laboratorio)  /// VALIDACION DE UNA PRACTICA EXISTENTE
{
    int flag=1,id;
    stPracticas practica;

    FILE *archivo= fopen("practicas.dat","r+b");

    if(archivo != NULL)
    {
        printf("\n LISTA DE PRACTICAS ACTIVAS");
        do
        {
            while(fread(&practica,sizeof(stPracticas),1,archivo)>0)
            {
                muestraPracticasActivas(practica);
            }
            printf("\n Ingrese ID practica realizada: ");
            scanf("%d", &id);

            rewind(archivo);
            while(flag && fread(&practica,sizeof(stPracticas),1,archivo)>0 )
            {
                if(id == practica.idPractica)
                {
                    if(practica.baja==0)
                    {
                        flag=0;

                    }
                }
            }
            if(flag)
            {
                printf("Ingreso el ID %d de una practica que no existe en la base de datos o esta inactiva. Ingrese uno nuevo.\n",id);

            }
        }
        while(flag);
    }
    else
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO\n");
    }
    fclose(archivo);
    laboratorio.PracticaRealizada=id;
    return laboratorio;
}

void darAltaInactivoLaboratorio(char nombreArchivo[])  /// dar alta un inactivo
{
    FILE*archivo= fopen(nombreArchivo,"r+b");
    int flag=1;
    int flag1 =1;
    int id=0;
    stLaboratorios laboratorios;
    if(archivo)
    {
        while(fread(&laboratorios,sizeof(stLaboratorios),1,archivo)>0)
        {
            if(laboratorios.baja ==-1)
            {
            muestraLaboratoriosInactivos(laboratorios);
                flag1=0;
            }
        }
        if(!flag1)
        {
            printf("\nIngrese ID de laboratorios a dar de alta\n");
           scanf("%d",&id);
        }
        do
        {
            rewind(archivo);
            while( flag && fread(&laboratorios,sizeof(stLaboratorios),1,archivo)>0)
            {
                if(id == laboratorios.idLab )
                {
                    if(laboratorios.baja == -1)
                    {
                        laboratorios.baja=0;
                        flag=0;
                        fseek(archivo,(-1)*sizeof(stLaboratorios),SEEK_CUR);
                        fwrite(&laboratorios,sizeof(stLaboratorios),1,archivo);
                        system("cls");
                        printf("DADO DE ALTA CORRECTAMENTE \n");
                        muestraUnLaboratorio(laboratorios);
                    }
                }
            }
            if(flag && flag1==0)
            {
                printf("\nIngreso un ID incorrecto.Ingrese un ID que este inactivo\n");
                printf("Ingrese ID:\n");
                scanf("%d",&id);
            }
            else
            {
                printf("\nNo hay laboratorios inactivos \n");
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

void menuAltasLaboratorios(char nombreArchivo[])  /// Menu de altas de laboratorios nuevos o inactivos
{
    char o=0;
    do
    {

        printf("1)Dar alta un nuevo laboratorio\n2)Dar alta un laboratorio inactivo\n");
        fflush(stdin);
        o=getch();
        system("cls");

        switch(o)
        {
        case '1':
            cargaArchivoLaboratorios(nombreArchivo);

            system("cls");
            break;

        case '2':

            darAltaInactivoLaboratorio(nombreArchivo);
            system("pause");

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

void muestraLaboratoriosInactivos(stLaboratorios laboratorio) /// Funcion contenedora nuestra laboratorios inactivos
{

    FILE *archi =fopen("laboratorios.dat","r+b");
    if(archi)
    {
        while(fread(&laboratorio, sizeof(stLaboratorios), 1, archi) > 0)
        {
            if(laboratorio.baja== -1)
            {
                printf("\n LABORATORIO INACTIVO");
                muestraUnLaboratorio(laboratorio);
            }
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARACHIVO \n");
    }
    fclose(archi);


}

void muestraLaboratoriosActivos(stLaboratorios laboratorio) ///  Funcion contenedora muestra laboratorios activos
{
    FILE *archi =fopen("laboratorios.dat","r+b");
    if(archi)
    {
        while(fread(&laboratorio, sizeof(stLaboratorios), 1, archi) > 0)
        {
            if(laboratorio.baja== 0)
            {
                printf("\n LABORATORIO ACTIVO");
                muestraUnLaboratorio(laboratorio);
            }
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARACHIVO \n");
    }
    fclose(archi);
}

void modificacionLaboratorio(char nombreArchivo[])/// Contenedora de modificacion de laboratorio
{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    stLaboratorios laboratorio;
    stLaboratorios laboratorioV;
    if(archivo)
    {
        laboratorio=busquedaLaboratorio(nombreArchivo);
        printf("\nID paciente actual %d",laboratorio.idPaciente);
        laboratorioV = modificaUnLaboratorio(laboratorio);

        rewind(archivo);
        fseek(archivo,(laboratorioV.idLab-1)*sizeof(stLaboratorios),SEEK_SET);
        fwrite(&laboratorioV,sizeof(stLaboratorios),1,archivo);
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO \n");
    }
system("pause");
system("cls");
    fclose(archivo);
}

stLaboratorios modificaUnLaboratorio(stLaboratorios laboratorio) /// modifica un laboratorio utilizando las validaciones pertinentes
{

    laboratorio.idPaciente= validacionId();

    laboratorio=validacionFecha(laboratorio);

    laboratorio=validacionPractica(laboratorio);

    return laboratorio;
}


void borrar_logicamente(stLaboratorios laboratorio, char nombreArchivo[]) ///Borra logicamente un registro que recien se ingresa
{                                                                         ///y que en el archivo se repite

    FILE *archivo=fopen(nombreArchivo,"r+b");
    FILE *archivoPac =fopen("pacientes.dat","r+b");
    FILE *archivoPrac =fopen("practicas.dat","r+b");
    stPaciente paciente;
    stPracticas practica;
    stLaboratorios laboratorioValido;
    int flag1=1,flag2=1,flag3=1;
    int flag5=1;
    if(archivo && archivoPac && archivoPrac)
    {


        while(fread(&practica,sizeof(stPracticas),1,archivoPrac)>0) /// Se busca un registro que contenga los mismos campos
        {
            if(practica.idPractica == laboratorio.PracticaRealizada)
            {
                flag2=0;


                while(fread(&paciente,sizeof(stPaciente),1,archivoPac)>0)
                {
                    if (paciente.idPaciente ==laboratorio.idPaciente)
                    {
                        flag1=0;
                        while( flag3 && fread(&laboratorioValido,sizeof(stLaboratorios),1,archivo)>0)
                        {
                            if(laboratorio.anio ==laboratorioValido.anio)
                            {
                                if(laboratorio.mes == laboratorioValido.mes)
                                {
                                    if(laboratorio.dia == laboratorioValido.dia)
                                    {
                                        flag3=0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if(flag1==0 && flag2==0 && flag3==0)
        {
            rewind(archivo);

            while(  flag5 &&fread(&laboratorio,sizeof(stLaboratorios),1,archivo)>0)
            {



                if(laboratorio.idLab == laboratorioValido.idLab)   /// Se da de baja
                {


                    fseek(archivo,(-1)*sizeof(stLaboratorios),SEEK_CUR);
                    laboratorio.baja=-1;
                    fwrite(&laboratorio,sizeof(stLaboratorios),1,archivo);

                    flag5=0;

                }

            }


        }



    }

    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO \n");
    }


    fclose(archivo);
    fclose(archivoPac);
    fclose(archivoPrac);


}






