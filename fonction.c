#include "main.h"

int loadFile(int numClient[], float cagnotte[], int suspendu[], int taille)
{
    FILE *File;
    File = fopen("ressource/client.csv", "r");
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

//Cette Fonction est appelé quand l'admin a choisis d'ajouter un CLient 
int AddClient (int numClient[], float cagnotte[], int suspendu[], int taille  ){
    int num,i ;
    printf("Quelle sera la nnuméros du client a ajouter : \n");
    scanf("%d",&num);
    for (i=0 ; i<taille ; i++){
        while(numClient[i]== num){
            printf("Erreur Saisir un autre numero client : \n");
            scanf("%d",&num);
        }
        
    }
    
    numClient[taille]=num;    
    cagnotte[taille]=0;
    suspendu[taille]=0;

    return taille+1 ;
}
void ShowClient (int Tclient[] ,float Tcagnotte[] , int Tsuspendue[] , int taille  ) {
    int i ;
    printf("NumClient\tcagnotte\tsuspendue\t\n");
    for (i=0;i<taille;i++){
        printf("%d\t%.2f\t%d\t\n",Tclient[i],Tcagnotte[i],Tsuspendue[i]);
    }

}

//Faire fonction qui avec (s) ecris dans le cvs les nouveaux tableaux , et avec (e) quite et save 


void test(void)
{
    int taille=100 , result; 
    int num[taille], suspendu[taille], etat, i=2;
    float cagnotte[taille];
    etat = loadFile(num, cagnotte, suspendu, taille);
    printf("etat :%d \n",etat);
    printf("%d;%.2f;%d \n",num[i], cagnotte[i], suspendu[i]);
    result=AddClient(num ,cagnotte ,suspendu ,etat);
    printf("%d\n" , result);
    printf("----------------\n");
    printf("%d;%.2f;%d \n",num[etat], cagnotte[etat], suspendu[etat]);
    printf("----------------\n");
    ShowClient(num,cagnotte,suspendu,result);

}