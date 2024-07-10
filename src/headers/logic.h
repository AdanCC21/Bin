#include <iostream>
#include <string.h>
#include <cstring>

#define PASMAX 50

using std::cout;
using std::endl;
using std::string;
using std::cin;

typedef struct estructura {
    char place[50]; // Lugar de la contraseña
    char pas[PASMAX]; // Constraseña
    char note[50]; // Nota que quiera agregar
    int ind; // Indice
}Tdata;

bool charge(string arch_name, int *p){
    char name[30];
    strcpy(name, arch_name.c_str());
    cout<<name<<endl;
    
    Tdata temp;

    FILE *doc = fopen(name,"rb");
    if(doc)
    {
        (*p)=0;
        while(fread(&temp,sizeof(Tdata),1,doc))
        {
            (*p)++;
        }
        cout<<"Posiciones cargadas "<< *p<<endl;
        return true;
    }
    else
    {
        cout<<"archivo no encontrado"<<endl;
    }
    fclose(doc);
    return false;
}

void priArch (string arch_name)
{
    Tdata temp;
    const char *arch = arch_name.c_str();

    int indice = 0;
    char place[50];
    char pass[50];
    char note[50];

    FILE *doc = fopen(arch,"rb");
    if(doc)
    {
        printf("%-10s %-15s %-15s %s\n","No.","| Pagina","| Pas ","| Note\n------------------------------------------------------------------");
        while(fread(&temp,sizeof(Tdata),1,doc))
        {
            indice = temp.ind;
            strcpy(place,temp.place);
            strcpy(pass,temp.pas);
            strcpy(note,temp.note);
            // printf("%-10d | %-15s | %-15s | %-15s\n",temp.ind,temp.place,temp.pas,temp.note);
            printf("%-10d | %-15s | %-15s | %-15s\n",indice,place,pass,note);
        }
    }
    else
    {
        printf("archivo no encontrado\n");
    }
    fclose(doc);
}
