/// Test de geografie cu 4 variante si cu punctaje
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define LMAX 100
#define intrebari_so_far 6
#define raspuns_corect 5
#define raspuns_gresit -2
#define variante 4
struct intrebare
{
    char *enunt;
    int nr_de_variante;
    char **variante_de_raspuns;
    int *grila;
    struct intrebare *next;
};
typedef struct intrebare intrebare;
struct participant
{
    char *nume;
    int puncte;
    struct participanti *next;
};
typedef struct participant participant;
int citire_nr_participanti(int *nr_participanti)
{
   do{
        printf("Dati numarul de participanti la concurs:");
        scanf("%d",nr_participanti);
        if(*nr_participanti<=0)
         printf("Incercati un numar natural!\n");
    }while(*nr_participanti<=0);
}
int *alocare_grila(int *grila)
{
    grila=(int*)malloc(variante*sizeof(int));
    return grila;
}
char *alocare_text(char *text)
{
    text=(char*)malloc(LMAX);
    return text;
}
char *alocare_matrice_de_variante(char **text)
{
    text=(char**)malloc(variante*sizeof(char*));
    int i;
    for(i=0;i<variante;i++)
     text[i]=alocare_text(text[i]);
    return text;
}
char *citire_nume_participant(char *text)
{
    printf("Dati numele pariticipantului:");
    gets(text);
    return text;
}
char *realocare_text(char *text,int dim)
{
    text=(char*)realloc(text,(dim+1)*sizeof(char));
    return text;
}
participant *creare_participant()
{
    participant *aux=(participant*)malloc(sizeof(participant));
    aux->puncte=0;
    aux->nume=alocare_text(aux->nume);
    aux->nume=citire_nume_participant(aux->nume);
    aux->nume=realocare_text(aux->nume,strlen(aux->nume));
    aux->next=NULL;
    return aux;
}
void adaugare_in_lista(participant **lista)
{
    participant *aux=creare_participant();
    if(*lista==NULL)
    {
        *lista=aux;
        return;
    }
    participant *parcurgere=*lista;
    while(parcurgere->next!=NULL)
     parcurgere=parcurgere->next;
    parcurgere->next=aux;
}
void afisare_participanti(participant *lista)
{
    printf("Lista este urmatoarea:\n");
    while(lista!=NULL)
    {
        printf("%s %d\n",lista->nume,lista->puncte);
        lista=lista->next;
    }
    printf("\n");
}
intrebare *creare_intrebare(char *enunt,char **matrice_cu_variante,int *grila)
{
    intrebare *aux=(intrebare*)malloc(sizeof(intrebare));
    aux->enunt=alocare_text(aux->enunt);
    strcpy(aux->enunt,enunt);
    aux->enunt=realocare_text(aux->enunt,strlen(aux->enunt));
    aux->nr_de_variante=variante;
    aux->variante_de_raspuns=alocare_matrice_de_variante(aux->variante_de_raspuns);
    /*if(aux->variante_de_raspuns==NULL)
    {
        printf("Nu a trecut sefu!\n");
        exit(1);
    }
    else
     printf("A trecut de asta!\n");
     */
    int i;
    for(i=0;i<variante;i++)
    {
        aux->variante_de_raspuns[i]=alocare_text(aux->variante_de_raspuns[i]);
        strcpy(aux->variante_de_raspuns[i],matrice_cu_variante[i]);
        aux->variante_de_raspuns[i]=realocare_text(aux->variante_de_raspuns[i],strlen(aux->variante_de_raspuns[i]));
    }
    ///printf("A trecut si de asta!\n");
    aux->grila=alocare_grila(aux->grila);
    for(i=0;i<variante;i++)
     aux->grila[i]=grila[i];
    ///printf("A trecut si de asta X2!\n");
    aux->next=NULL;
    return aux;
}
void adaugare_intrebare(intrebare **lista,char *enunt,char **matrice_cu_variante,int *grila)
{
    intrebare *aux=creare_intrebare(enunt,matrice_cu_variante,grila);
    if(*lista==NULL)
    {
        *lista=aux;
        return;
    }
    intrebare *parcurgere=*lista;
    while(parcurgere->next!=NULL)
     parcurgere=parcurgere->next;
    parcurgere->next=aux;
}
void afisare_intrebari(intrebare *lista)
{
    while(lista!=NULL)
    {
        printf("%s",lista->enunt);
        int j;
        for(j=0;j<variante;j++)
         printf("%d:%s",j+1,lista->variante_de_raspuns[j]);
       printf("\n");
       lista=lista->next;
    }
}
void afisare_intrebare(intrebare *lista)
{
    printf("%s",lista->enunt);
    int j;
    for(j=0;j<variante;j++)
     printf("%d:%s",j+1,lista->variante_de_raspuns[j]);
    printf("\n");
}
void chestionarul_de_intrebari(intrebare **lista_intrebari)
{
    FILE *f;
    if((f=fopen("intrebari.in","rt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }
    char buffer[LMAX];
    char **matrice_de_intrebari;
    char *enunt;
    int *grila;
    int i;
    for(i=0;i<intrebari_so_far;i++)
    {
        fgets(buffer,LMAX,f);
        ///printf("%s",buffer);
        enunt=alocare_text(enunt);
        strcpy(enunt,buffer);
        enunt=realocare_text(enunt,strlen(enunt));
        matrice_de_intrebari=alocare_matrice_de_variante(matrice_de_intrebari);
        int j;
        for(j=0;j<variante;j++)
        {
            fgets(buffer,LMAX,f);
            ///printf("%s",buffer);
            matrice_de_intrebari[j]=alocare_text(matrice_de_intrebari[j]);
            strcpy(matrice_de_intrebari[j],buffer);
            ///printf("%s",matrice_de_intrebari[j]);
            matrice_de_intrebari[j]=realocare_text(matrice_de_intrebari[j],strlen(matrice_de_intrebari[j]));
            ///printf("%s",matrice_de_intrebari[j]);
        }
        grila=alocare_grila(grila);
        int ind=i+1;
        switch(ind)
        {
        case 1:
            {
                grila[0]=0;
                grila[1]=0;
                grila[2]=0;
                grila[3]=1;
                break;
            }
        case 2:
            {
                grila[0]=1;
                grila[1]=0;
                grila[2]=0;
                grila[3]=0;
                break;
            }
        case 3:
            {
                grila[0]=0;
                grila[1]=1;
                grila[2]=0;
                grila[3]=0;
                break;
            }
        case 4:
            {
                grila[0]=0;
                grila[1]=1;
                grila[2]=0;
                grila[3]=0;
                break;
            }
        case 5:
            {
                grila[0]=1;
                grila[1]=0;
                grila[2]=0;
                grila[3]=0;
                break;
            }
        case 6:
            {
                grila[0]=0;
                grila[1]=0;
                grila[2]=1;
                grila[3]=0;
                break;
            }
        }
        adaugare_intrebare(lista_intrebari,enunt,matrice_de_intrebari,grila);
        free(enunt);
        for(j=0;j<variante;j++)
         free(matrice_de_intrebari[j]);
        free(matrice_de_intrebari);
        free(grila);
    }
}
void concurs(participant **lista_copii, intrebare *lista_intrebari)
{
    participant *aux1=*lista_copii;
    while(aux1!=NULL)
    {
        printf("Bine ai venit la concurs %s\n",aux1->nume);
        printf("Vei avea de rezolvat %d intrebari!\n",intrebari_so_far);
        char ras;
        do{
            printf("Esti gata sa incepem?(d/n)\n");
            scanf("%c",&ras);
            getchar();
            if(ras=='n')
             printf("Mai asteptam sa iti faci curaj =)\n");
        }while(ras=='n');
        printf("\n");
        intrebare *aux2=lista_intrebari;
        while(aux2!=NULL)
        {
            afisare_intrebare(aux2);
            int raspuns;
            do{
                printf("Raspunsul la intrebare este:");
                scanf("%d",&raspuns);
                if(raspuns<=0 || raspuns>variante)
                 printf("Raspunsul trebuie sa fie intre 1 si numarul de variante, in cazul nostru 4!\n");
            }while(raspuns<=0 || raspuns>variante);
            if(aux2->grila[raspuns-1]==1)
             {
                 aux1->puncte+=raspuns_corect;
                 printf("Ai raspuns corect la aceasta intrebare!\n");
             }
            else
             {
                 aux1->puncte+=raspuns_gresit;
                 printf("Ai raspuns gresit la aceasta intrebare!\n");
             }
            printf("\n");
            aux2=aux2->next;
        }
        printf("%s a acumulat %d puncte!\n",aux1->nume,aux1->puncte);
        printf("Apasati orice tasta pentru a trece la urmatorul concurent!");
        getch();
        system("CLS");
        aux1=aux1->next;
    }
}
void afisare_rezultate(participant *lista)
{
    while(lista!=NULL)
    {
        printf("%s:%d\n",lista->nume,lista->puncte);
        lista=lista->next;
    }
}
int main()
{
    participant *lista_copii=NULL;
    intrebare *lista_intrebari=NULL;
    int nr_participanti;
    citire_nr_participanti(&nr_participanti); /// Citirea numarului de participanti
    getchar();
    int i;
    for(i=0;i<nr_participanti;i++) /// Se realizeaza lista de participanti si se initializeaza punctajul cu 0
    {
       adaugare_in_lista(&lista_copii);
       ///afisare_participanti(lista_copii);
    }
    int nr_intrebari=intrebari_so_far; /// Se va actualiza constant, cand am eu chef =)))
    chestionarul_de_intrebari(&lista_intrebari); /// Se realizeaza chestonarul cu intrebari
    printf("Intrebarile de la concurs sunt urmatoarele:\n");
    afisare_intrebari(lista_intrebari); /// Se vor afisa intrebarile de la concurs pentru a-i familiariza pe copii
    puts("Press any key to continue.");
    getch();
    system("CLS");
    concurs(&lista_copii,lista_intrebari); /// Concursul propriu zis la care copii participa
    afisare_rezultate(lista_copii); /// Afisarea rezultatelor
    printf("Cam acesta a fost concursul mai copii! =))))");
    return 0;
}
