#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


///estrctura

typedef struct
{
   int id;
   char nombre[30];
   char apellido[30];
   int dni;
   int nota;

}stAlumno;

///prototipados

int buscaDni(int dni);
void guardaAlumnoArchivo(stAlumno a);
stAlumno cargaUnAlumno();
int validoId();
void cargaAlumnos();
void muestraUnAlumno(stAlumno a);
void muestraArch(char archivo[]);
int ArchivoAArrglo(stAlumno arreglo[], int dim);
void muestraArreglo(int v, stAlumno a[]);
int cuentaAlumnos(char archivo[]);
void archAprobadosDesaprobados(int v, stAlumno a[], int aprobacion);
float porcentajeDeAprobados();
float porcentajeDeDesaprobados();

///constante

const char ESC=27;
const char DIM = 30;
const char *AR_ALUMNOS = "archivoAlumnos.dat";
const char *AR_APROBADOS = "archivoAprobados.dat";
const char *AR_DESAPROBADOS = "archivoDesaprobados.dat";

int main()
{
    stAlumno alumnos[DIM];///arreglo de alumnos
    int valumnos = 0;///validos
    int cantAlumnos = 0;///alumnos totales cargados en el archivo
    int aprobacion = 0;///nota de aprobacion
    float porcentajeAprobado = 0;///porcentaje de alumnos aprobados
    float porcentajeDesaprobados = 0;///porcentaje de alumnos desaprobados
    char opcion;

    printf("ingrese 1 si desea cargar el archivo: \n\n");
    opcion = getch();

    ///ejercicio 1 y 2
    if(opcion == 49)
    {
        cargaAlumnos();///esta funcion carga el archivo de alumnos
        system("pause");
        system("cls");
    }

    ///ejercicio 3
    printf("\nEsta es la planilla de alumnos:\n\n");
    muestraArch(AR_ALUMNOS);
    printf("\n\n");
    system("pause");
    system("cls");

    ///ejercicio 4 pasa de archivo a arreglo y lo muestra
    valumnos = ArchivoAArrglo(alumnos, DIM);
    printf("\nEste es el arreglo: \n");
    muestraArreglo(valumnos, alumnos);
    printf("\n\n");
    system("pause");
    system("cls");

    ///ejercicio 5
    cantAlumnos = cuentaAlumnos(AR_ALUMNOS);
    printf("Hay %d alummnos cargados\n\n", cantAlumnos);
    system("pause");
    system("cls");

    ///ejercicio 6

    printf("Ingrese la nota de aprobacion: ");
    scanf("%d", &aprobacion);
    archAprobadosDesaprobados(valumnos, alumnos, aprobacion);

    ///muestro archivo aprobados
    printf("\n\nEstos son los alumnos aprobados:\n\n");
    muestraArch(AR_APROBADOS);
    printf("\n\n");
    system("pause");
    system("cls");

    ///muestro archivo desaprobados
    printf("Estos son los alumnos desaprobados:\n\n");
    muestraArch(AR_DESAPROBADOS);
    printf("\n\n");
    system("pause");
    system("cls");

    ///ejercicio 7
    ///aprobados
    porcentajeAprobado = porcentajeDeAprobados();
    printf("Hay un %.2f porciento de aprobados\n\n", porcentajeAprobado);
    system("pause");
    system("cls");

    ///desaprobados
    porcentajeDesaprobados = porcentajeDeDesaprobados();
    printf("Hay un %.2f porciento de desaprobados\n\n", porcentajeDesaprobados);
    system("pause");
    system("cls");



    return 0;
}


///funciones

///ejercicio 1////////////////////////////////////////////////////////////////////////////////
///verifico si existe un dato en un archivo buscando por dni

int buscaDni(int dni)
{
    stAlumno a;
    int flag = 0;

    FILE *pArchAlumno = fopen(AR_ALUMNOS, "rb");

    if(pArchAlumno)
    {
        while(flag == 0 && fread(&a, sizeof(stAlumno), 1, pArchAlumno) > 0)
        {
            if(a.dni == dni)
            {
                flag = 1;
            }
        }
        fclose(pArchAlumno);
    }

    return flag;///si retorna 0 no existe ningun dni si retorna 1 es que existe
}
///.///////////////////////////////////////////////////////////////////////////////////////////

///ejercicio 2////////////////////////////////////////////////////////////////////////////////
///carga UN alumno

stAlumno cargaUnAlumno()
{
    stAlumno a;
    int flagDni = 0;

    do
    {
        printf("Ingrese su DNI............: ");
        scanf("%d", &a.dni);
        flagDni = buscaDni(a.dni);
    }
    while(flagDni == 1);

    printf("Ingrese su nombre.........: ");
    fflush(stdin);
    gets(a.nombre);

    printf("Ingrese su apellido.......: ");
    fflush(stdin);
    gets(a.apellido);



    do
    {
        printf("Ingrese sus nota..........: ");
        scanf("%d", &a.nota);
    }
    while(a.nota <= 1 || a.nota > 10);

    return a;
}

///valido id

int validoId()
{
    int id = 0;
    stAlumno a;

    FILE *pArchAlumno = fopen(AR_ALUMNOS, "rb");
    if(pArchAlumno)
    {
        fseek(pArchAlumno, sizeof(stAlumno)*(-1), SEEK_END);
        if(fread(&a, sizeof(stAlumno), 1, pArchAlumno) > 0)
        {
            id = a.id;
        }
       fclose(pArchAlumno);
    }

    return id;
}

///guardo alumno en archivi

void guardaAlumnoArchivo(stAlumno a)
{
    FILE *pArchAlumno = fopen(AR_ALUMNOS, "ab");
    if(pArchAlumno)
    {
        fwrite(&a, sizeof(stAlumno), 1, pArchAlumno);
        fclose(pArchAlumno);
    }
}

///carga lista de alumnos

void cargaAlumnos()
{
    char opcion;
    stAlumno a;

    while(opcion != ESC)
    {
        printf("Cargando alumnos...\n\n");

        a = cargaUnAlumno();
        a.id = validoId()+1;
        guardaAlumnoArchivo(a);

        printf("ESC si desea salir...");
        opcion = getch();
        system("cls");
    }
}

///.///////////////////////////////////////////////////////////////////////////////////////

///ejercicio 3/////////////////////////////////////////////////////////////////////////////
///muestra un alumno

void muestraUnAlumno(stAlumno a)
{
    printf("\nNombre.............: %s \n", a.nombre);
    printf("Apellido...........: %s \n", a.apellido);
    printf("DNI................: %d \n", a.dni);
    printf("Nota...............: %d \n", a.nota);
    printf("-------------------------------------");
}

///muestra plantiila de  alumnos

void muestraArch(char archivo[])
{
    stAlumno a;
    FILE *pArchAlumno = fopen(archivo, "rb");
    if(pArchAlumno)
    {
        while(fread(&a, sizeof(stAlumno), 1, pArchAlumno) > 0)
        {
            muestraUnAlumno(a);
        }
        fclose(pArchAlumno);
    }
}

///.////////////////////////////////////////////////////////////////////////////////////////////

///ejercicio 4//////////////////////////////////////////////////////////////////////////////////
///archivo a arreglo

int ArchivoAArrglo(stAlumno arreglo[], int dim)
{
    stAlumno a;
    int v = 0;

    FILE *pArchAlumnos = fopen(AR_ALUMNOS, "rb");
    if(pArchAlumnos)
    {
        while(v<dim && fread(&a, sizeof(stAlumno), 1 , pArchAlumnos) > 0)
        {
            arreglo[v] = a;
            v++;
        }
        fclose(pArchAlumnos);
    }

    return v;
}
 ///muestra arreglo de alumnos

 void muestraArreglo(int v, stAlumno a[])
 {
     int i;

     for(i = 0; i<v; i++)
     {
         muestraUnAlumno(a[i]);
     }
 }

 ///.//////////////////////////////////////////////////////////////////////////////////////////

///ejercicio 5/////////////////////////////////////////////////////////////////////////////////
///cuenta los alumnos cargados en un archivo

int cuentaAlumnos(char archivo[])
{
    int cont = 0;
    stAlumno a;
    FILE *pArchAlumno = fopen(archivo, "rb");
    if(pArchAlumno)
    {
        fseek(pArchAlumno, 0, SEEK_END);
        cont = ftell(pArchAlumno)/sizeof(stAlumno);
        fclose(pArchAlumno);
    }
    return cont;
}

///.///////////////////////////////////////////////////////////////////////////////////////////

///ejercicio 6////////////////////////////////////////////////////////////////////////////////
///pasa los aprobados al archivo de aprobados  y los desaprobados al archivo de desaprobados

void archAprobadosDesaprobados(int v, stAlumno a[], int aprobacion)
{
    FILE *pArchAprobados = fopen(AR_APROBADOS, "wb");
    FILE *pArchDesaprobados = fopen(AR_DESAPROBADOS, "wb");

    if(pArchAprobados && pArchDesaprobados)
    {
        for(int i = 0; i<v; i++)
        {
            if(a[i].nota >= aprobacion)
            {
                fwrite(&a[i], sizeof(stAlumno), 1, pArchAprobados);
            }
            else
            {
                fwrite(&a[i], sizeof(stAlumno), 1, pArchDesaprobados);
            }
        }
        fclose(pArchAprobados);
        fclose(pArchDesaprobados);
    }

}

///.////////////////////////////////////////////////////////////////////////////////////////////

///ejercicio 7//////////////////////////////////////////////////////////////////////////////////
///calcula el porcentaje de alummnos aprobados

float porcentajeDeAprobados()
{
    float porcentaje = 0;
    int cantAlumnos = cuentaAlumnos(AR_ALUMNOS);
    int cantAprobados = cuentaAlumnos(AR_APROBADOS);

    porcentaje = (float) (cantAprobados*100)/cantAlumnos;

    return porcentaje;
}


///calcula el porcentaje de alummnos desaprobados

float porcentajeDeDesaprobados()
{
    float porcentaje = 0;
    int cantAlumnos = cuentaAlumnos(AR_ALUMNOS);
    int cantDesaprobados = cuentaAlumnos(AR_DESAPROBADOS);

    porcentaje = (float) (cantDesaprobados*100)/cantAlumnos;

    return porcentaje;
}

///.///////////////////////////////////////////////////////////////////////////////////////
