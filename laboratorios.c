#include "laboratorios.h"


void darBajaLaboratorios(char nombreArchivo[]) ///DAR BAJA LABORATORIOS
{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    int idLabs;
    stLaboratorios laboratorio;
    int flag=1;
    if(archivo != NULL)
    {
        printf("Ingrese id de laboratorio a dar de baja \n");
        fflush(stdin);
        scanf("%d",&idLabs);
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
                }
            }
        }
        if(flag)
        {
            printf("No se encontro el laboratorio con ese nombre. Intente nuevamente \n");
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
/// VER VALIDACION DE FECHAS CUANDO NOS JUNTEMOS
/// Validar que no se pueda dar de alta un Laboratorio para
/// un paciente y practica inexistentes.
/// Validar que si al dar de alta un laboratorio, se
///repitan, paciente, fecha y practica; se deberá
///eliminar (lógicamente) el laboratorio anterior e
///insertar el nuevo.

void validacionesLabs(char nombreArchivo[]) ///VALIDACIONES DE LABORATORIOS FECHAS ver si ID tambien
{
    /*
        stLaboratorios labValido;

        FILE *archivo=fopen(nombreArchivo,"r+b");
        rewind(archivo);

        while(  fread(&labValido,sizeof(stLaboratorios),1,archivo)>0 ) /// VALIDACION DE ID LAB
        {

            if(lab.idLab == labValido.idLab)
            {

                printf("El laboratorio ya existe, ingrese otro laboratorio \n");
                printf("Ingrese laboratorio nuevo \n");
                scanf("%d",&lab.idLab);

                rewind(archivo);
            }
        }
        rewind(archivo);
        while(  fread(&labValido,sizeof(stLaboratorios),1,archivo)>0 ) ///VALIDACION DE ID PACIENTE
        {
            if(lab.idPaciente == labValido.idPaciente)
            {

                printf("El id del paciente ya existe, ingrese otro id de paciente \n");
                printf("Ingrese id paciente nuevo \n");
                scanf("%d",&lab.idPaciente);

                rewind(archivo);
            }
        }
        rewind(archivo);
        }



        fclose(archivo);


    }
    */
}

void muestraUnLaboratorio(stLaboratorios laboratorio)
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
}

stLaboratorios cargaUnLaboratorio() ///FUNCION CARGA UN LABORATORIO
{
    stLaboratorios laboratorio;

    printf("\n Id Paciente: ");
    scanf("%d", &laboratorio.idPaciente);

    printf("\n Anio: ");
    scanf("%d", &laboratorio.anio);

    printf("\n Mes: ");
    scanf("%d", &laboratorio.mes);

    printf("\n Dia: ");
    scanf("%d", &laboratorio.dia);

    printf("\n Id practica realizada: ");
    scanf("%d", &laboratorio.PracticaRealizada);

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
        printf("LISTA DE PRACTICAS");
        muestraArchivoPracticas("practicas.dat");
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(stLaboratorios);
        do
        {
            cant++;
            laboratorios = cargaUnLaboratorio();
            laboratorios.idLab=cant;
            fwrite(&laboratorios, sizeof(stLaboratorios), 1, archi);
            printf("\nESC para salir o cualquier tecla para continuar");
            opcion = getch();
        }
        while(opcion != ESC);
        fclose(archi);
    }
}

void busquedaLaboratorio (char nombreArchivo[]) ///FUNCION BUSQUEDA PRACTICA POR NOMBRE
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
}
