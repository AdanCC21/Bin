#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "libad.h"

#define _CTR_SECURE_NO_WARNINGS //No more warnings`

#define TRUE 1
#define FALSE 0
#define tpass 50

typedef struct estructura { //Estructura Basica
    char zone[50];
    char pas[tpass];
    char note[50];
    int ind;
}Tdata;

//Prototypes-------------------------
//Funcion de carcar archivo
void charge (int *p,int *band,int *band_actv,char arch[]);

//Funcion para Crear Archivo Binario
void bin_create (int *p,int *band_actv, int *band_char,char arch[]);

//Funcion para Cargar datos al archivo binario
void load (int *p,char arch[]);

//Funcion para Imprimir datos de un archivo externo
void imprint ();

//Funcion para Imprimir datos del archivo binario
void imprint_act (char arch[]);

//Funcion de editar datos del archivo actual
void edit (int *band_actv, char arch[],int *p);
//Funcion de eliminar reg

//Main
int main()
{
    srand(time(NULL));
    int bandchar = FALSE, //bandera de archivos cargados
    band_act = FALSE;//Actividad del archivo
    int op,//Opcion del usuario
        p = 0, //Posiciones usadas
        v; //Variable de verificacion
    char arch[50];//Archivo activo
    do
    {
        system("CLS");
        if(band_act == TRUE)
        {
            printf("Archivo activo : %s\nCon %d registros\n",arch,p);
        }
        else
        {
            printf("Archivo activo : Ninguno\n");
        }
        printf("\n");
        printf("1.-Crear Archivo Nuevo\t\t2.-Llenar Archivo Actual\t3.-Imprimir Actual\t4.-Editar Actual\t5.-Cargar ARchivo\t6.-Imprimir Archivo Externo\t0.-Salir\n");
        op=valid("fuera de rango",0,7);
        switch(op)
        {
            case 1:
                system("CLS");
                bin_create(&p,&band_act,&bandchar,arch);
                break;
            case 2:
                system("CLS");
                if(band_act==TRUE)
                {
                    do
                    {
                        load(&p,arch);
                        printf("Deseas agregar otra password?\n1.-Repetir\t2.-Salir\n");
                        v=valid("Fuera de rango",1,2);
                        system("cls");
                    }
                    while(v==1);
                }
                else
                {
                    printf("Favor de cargar un archivo\n");
                    getch();
                }
                break;
            case 3:
                system("CLS");
                if(band_act==TRUE)
                {
                    imprint_act(arch);
                }
                else
                {
                    printf("Favor de cargar un archivo\n");
                    getch();
                }
                break;
            case 4:
                if(band_act==TRUE)
                {
                    edit(&band_act,arch,&p);
                }
                else
                {
                    system("CLS");
                    printf("Favor de cargar un archivo primero\n");
                    getch();
                }
                break;
                
            /*
            // case 6:
            //     if(bandchar==TRUE)
            //     {
            //         printf("Seguro que quiere reiniciar?\n1.-No, mantener datos\t2.-Si reiniciar\n");
            //         r = valid("Fuera de rango",1,2);
            //         r--;
            //         if(r==FALSE)
            //         {
            //             printf("De acuerdo\n");
            //             getch();
            //         }
            //         else
            //         {
            //             p=0;
            //             bandchar=FALSE;
            //             band_act=FALSE;
            //             printf("Listo\n");
            //             getch();
            //         }
            //     }
            //     else
            //     {
            //         printf("No hay datos para reiniciar\n");
            //         getch();
            //     }
            //     break;
            */
            case 5:
                system("CLS");
                charge(&p,&bandchar,&band_act,arch);
                getch();
                break;
            case 6:
                system("CLS");
                imprint();
                break;
            case 0:
                system("CLS");
                printf("Seguro que quieres salir?\n1.-Salir\t2.-Repetir\n");
                scanf("%d",&op);
                if(op==1)
                {
                    op--;
                }
                else
                {
                    printf("Arre\n");
                    getch();
                }
                break;
        }
    }
    while(op!=0);
}

//Funciones

void charge (int *p,int *band,int *band_actv,char arch[])
{
    Tdata temp;
    int v; //Variable de validacion
    char name[50];//Nombre del archivo
    do
    {
        printf("De que archivo quiere cargar\n");
        gets(name);
        v=validCh(name);
    } while (v==1);
    strcat(name,".dll");

    FILE *doc = fopen(name,"rb");
    if(doc)
    {
        (*p)=0;
        while(fread(&temp,sizeof(Tdata),1,doc))
        {
            (*p)++;
        }
        (*band)=TRUE;
        (*band_actv)=TRUE;
        printf("Listo\nPosiciones cargadas : %d\n",*p);
        strcpy(arch,name);
    }
    else
    {
        printf("Archivo no encontrado\n");
    }
    fclose(doc);
}

void bin_create (int *p,int *band_actv, int *band_char,char arch[])
{
    int v;  //Variable de validacion
    char name[50];//Nombre del archivo
    do
    {
        do
        {
            printf("Con que nombre deseas registrar tu archivo\n");
            gets(name);
            v = validCh(name);
            system("CLS");
        }
        while(v==1); 
        printf("Su archivo se llamara : %s \nEstas seguro?\n\n1.-Cambiar Nombre\t2.-Crear\n",name);
        v=valid("Fuera de rango",1,2);
        v--;
    }
    while(v==0);
    strcat(name,".dll");
    system("CLS");
    
    int band_arch = FALSE;//Archivo encontrado o no
    FILE *docr = fopen(name,"rb");
    FILE *doc = fopen(name,"wb");
    if(docr)
    {
        printf("Archivo ya existe\nSi deseas editarlo carga las posiciones y usa la funcion llenar\n");
        band_arch = TRUE;
    }
    if(doc && band_arch ==FALSE)
    {
        printf("Archivo Creado\n");
        strcpy(arch,name);
        (*p)=0;
        (*band_actv)=TRUE;
        (*band_char)=TRUE;
    }
    
    getch();
    system("CLS");
    fclose(doc);
}

void load (int *p,char arch[])
{
    int v;  //Variable de validacion
    char tzone[50],//Varaible temporal de zona
        tpas[tpass],//Temporal pass
        tnote[50];//temporal note
    Tdata reg;

    FILE *doc = fopen(arch,"ab");
    if(doc)
    {
            do
            {
                printf("Ingrese de que lugar es (google, youtube, gmail, etc.)\n");
                gets(tzone);
                system("CLS");

                printf("Ingrese la password\n");
                gets(tpas);
                system("CLS");

                printf("Alguna nota que desee agregar\nEn caso de que no solo presionar enter\n");
                gets(tnote);
                system("CLS");

                printf("Esto se registrara dentro de su archivo con:\nLugar : %-15s | Pass : %-15s | Note : %s\n\nAsegurate de que tus datos esten correctos\n1.-Editar\t2.-Guardar\n",tzone,tpas,tnote);
                v=valid("Fuera de rango",1,2);
            }
            while(v==1);
            system("CLS");

        strcpy(reg.zone,tzone);
        strcpy(reg.pas,tpas);
        strcpy(reg.note,tnote);
        reg.ind=(*p);

        fwrite(&reg,sizeof(Tdata),1,doc);
        (*p)++;
    }
    else
    {
        printf("Archivo no encontrado\nPorfavor cargue el archivo");
        getch();
    }
    fclose(doc);
}

void imprint ()
{
    char name[50];//Nombre del archivo
    printf("Nombre del archivo que desea imprimir\n");
    fflush(stdin);
    gets(name);
    strcat(name,".dll");

    imprint_act(name);
}

void imprint_act (char arch[])
{
    Tdata temp;

    FILE *doc = fopen(arch,"rb");
    if(doc)
    {
        printf("%-10s %-15s %-15s %s\n","No.","| Pagina","| Pas ","| Note\n------------------------------------------------------------------");
        while(fread(&temp,sizeof(Tdata),1,doc))
        {
            printf("%-10d | %-15s | %-15s | %-15s\n",temp.ind,temp.zone,temp.pas,temp.note);
        }
        getch();
    }
    else
    {
        printf("archivo no encontrado\n");
        getch();
    }
    fclose(doc);
}

void edit (int *band_actv, char arch[],int *p) //Falla
{
    int i=0, //Contador de posiciones pasadas
        op,//Confirmacion de cambiar
        change,//No de registro a cambiar
        band_found = FALSE, //Bandera de registro encontrado
        band_name = FALSE,//Bandera de cambio de nombre
        band_pas = FALSE, //Bandera de cambio de contrase;a
        band_note = FALSE; //Bandera de cambio de nota
    char newpass[tpass],//Nueva contrasena
        newnote[100],//Nueva Nota
        newname[100];//Nuevo nombre
    Tdata reg;//Registro temporal
    FILE *doc = fopen(arch,"rb+"); //Archivo actual

    if(doc)
    {
        if(*band_actv==TRUE)
        {
            system("CLS");
            printf("Ingrese el 'No.' de su registro, desde 0 hasta %d\n",(*p) - 1);
            change=valid("Registro no encontrado",0,*p);

            while (fread(&reg,sizeof(Tdata),1,doc) == 1 && band_found==FALSE)
            {
                if(reg.ind == change)
                {
                    band_found=TRUE;
                    system("CLS");
                    printf("Este es tu registro\n");
                    printf("Zona %-15s | Password %-15s | Nota %-15s\n\n",reg.zone,reg.pas,reg.note);
                    printf("Seguro que quiere cambiarlo?\n1.-Salir\t2.-Editar\n");
                    op=valid("Fuera de rango",1,2);

                    if(op==2)
                    {
                        system("CLS");

                        printf("Cambiar nombre?\n1.-Cambiar\t2.-No\n");
                        band_name=valid("FUERA DE RANGO",1,2);
                        if(band_name==TRUE)
                        {
                            system("CLS");
                            printf("Ingrese su nuevo nombre\n");
                            gets(newname);
                        }

                        printf("Cambiar la pass?\n1.-Cambiar\t2.-No\n");
                        band_pas=valid("FUERA DE RANGO",1,2);
                        if(band_pas==TRUE)
                        {
                            system("CLS");
                            printf("Ingrese su nueva password\n");
                            gets(newpass);
                        }

                        printf("Cambiar Nota?\n1.-Cambiar\t2.-No\n");
                        band_note=valid("FUERA DE RANGO",1,2);
                        if(band_note==TRUE)
                        {
                            system("CLS");
                            printf("Escriba su nueva nota\n");
                            gets(newnote);
                        }

                        system("CLS");
                        printf("Este sera su nuevo registro\n");
                        printf("No. %-10d Zona %-15s | Password %-15s | Nota %-15s\n\n",reg.ind,newname,newpass,newnote);
                        printf("Seguro que quiere cambiarlo?\n1.-Salir\t2.-Guardar\n");
                        op=valid("Fuera de rango",1,2);
                        
                        if(op==2)
                        {
                            strcpy(reg.zone,newname);
                            strcpy(reg.pas,newpass);
                            strcpy(reg.note,newnote);
                            
                            fseek(doc,i * sizeof(Tdata),SEEK_SET);
                            fwrite(&reg,sizeof(Tdata),1,doc);
                            fseek(doc, 0, SEEK_SET); 
                            i = 0; 
                            printf("Cambio realizado con exito\n");
                        }
                        else
                        {
                            printf("Cambio no realizado\n");
                        }
                    }
                    else
                    {
                        printf("Accion cancelada\n");
                    }
                }
                i++;
            }
            if(band_found==FALSE)
            {
                printf("Password no encontrada\n");
            }
        }
    }
    getch();
    fclose(doc);
}


