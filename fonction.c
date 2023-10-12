#include "main.h"

int loadFile(int numClient[], float cagnotte[], int suspendu[], int taille)
{
    FILE *File;
    File = fopen("client.csv", "r");
    int i=0;

    if (File==NULL)
    {
        printf("Erreur: fichier vide ou non existant \n");
        return -1; //erreur fichier
    }

    fscanf(File, "numClient;cagnotte;suspendu\n");
    while (feof(File)==0 && i<taille){
        fscanf(File, "%d;%f;%d", &numClient[i], &cagnotte[i], &suspendu[i]);
        i++;
    }
    if (i==taille && feof(File)==0) return -2; //erreur tableau trop cours
    return i;
}

void test(void)
{
    int taille=2;
    int num[taille], suspendu[taille], etat, i=3;
    float cagnotte[taille];
    etat = loadFile(num, cagnotte, suspendu, taille);
    printf("%d \n",etat);
    printf("%d;%.2f;%d \n",num[i], cagnotte[i], suspendu[i]);
}