#include "main.h"

int loadClient(int numClient[], float cagnotte[], int suspendu[], int taille)
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

int loadArticle(int id[], float poid[], float volume[], float prix[], int taille)
{
    FILE *File;
    File = fopen("./ressource/articles.csv", "r");

    int i=0;

    if (File==NULL)
    {
        printf("Erreur: fichier vide ou non existant \n");
        return -1; //erreur fichier
    }

    fscanf(File, "numClient;cagnotte;suspendu\n");
    while (feof(File)==0 && i<taille){
        fscanf(File, "%d;%f;%f;%f", &id[i], &poid[i], &volume[i], &prix[i]);
        i++;
    }
    if (i==taille && feof(File)==0) return -2; //erreur tableau trop court
    return i;
}

// recherche si la valeur (numéro client ou reference objet) est déjà dans le fichier
int inFile(int val, int tab[], int taille){
    for (int i=0 ; i<taille ; i++){
        if (tab[i] == val) return i;
    }
    return -1;
}

//Cette Fonction est appelé quand l'admin a choisis d'ajouter un CLient
// peut etre a refaire avec fonction inFile()
int AddClient (int numClient[], float cagnotte[], int suspendu[], int taille  ){
    int num,i ;
    printf("Quelle sera la numéros du client a ajouter : \n");
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

int AddArticle(int ref[],float poids[] ,float volume[] ,float prix[] , int taille ){
    int i , article  ;
    float vol ;
    float poids1, prix1;
    int new_taille = loadArticle(ref,poids,volume,prix,taille) ;
    printf("Quelle est la reference de l'article que vous voulez ajouter : \n");
    scanf("%d" ,&article);
    for (i=0;i<new_taille;i++){
        while (ref[i]==article) {
            printf("L'article souhaité est déja existant sous un reference existante veuillez saisir une autre référence : \n");
            scanf("%d", &article);
        }
    }
    printf("Veuillez Rentrez le poids de l'artcicle ajouter : \n");
    scanf("%f",&poids1);
    printf("Veuillez entrez le volume de produits ajouté : \n");
    scanf("%fm",&vol);
    printf("Veuillez entrez le prix du produits ajouté : \n");
    scanf("%f",&prix1);

    ref[taille]=article;
    poids[taille]=poids1;
    volume[taille]=vol;
    prix[taille]=prix1;
    return taille + 1 ;

}

void ShowClient (int Tclient[] ,float Tcagnotte[] , int Tsuspendue[] , int taille  ) {
    int i ;
    printf("NumClient\tcagnotte\tsuspendue\t\n");
    for (i=0;i<taille;i++){
        printf("%d\t%.2f\t%d\t\n",Tclient[i],Tcagnotte[i],Tsuspendue[i]);
    }

}

//permet de rajouter les clients dans le fichier
//ATTENTION MARCHE PAS
void saveClient(int Tclient[], float Tcagnotte[], int Tsuspendue[], int tailleStart, int tailleEnd){
    FILE *File;
    File = fopen("./ressource/client.csv", "a");
    
    if (File==NULL){
        printf("Erreur: fichier vide ou non existant \n"); //erreur fichier
    }
    for (int i =tailleStart; i<tailleEnd; i++) {
        fprintf(File, "\n%d;%f;%d", Tclient[i], Tcagnotte[i], Tsuspendue[i]);
    }
}

//Faire fonction Ajouts article (Enzo)
//Faire Fonction ShowArticle (Enzo)
//Finir le Menu (Maeva)
//Faire fonction qui avec (s) ecris dans le cvs les nouveaux tableaux , et avec (e) quite et save (Samuel)


void test(void)
{
    
    int taille=100 , reelTaille, taillebase;/*
    int  ref[taille] ;
    float volume[taille] ;
    float poids[taille] , prix[taille] ;*/

    int numclient[100], suspendu[100];
    float cagnotte[100];
    taillebase = loadClient(numclient,cagnotte,suspendu, taille);
    reelTaille = AddClient(numclient,cagnotte,suspendu,taille);
    saveClient(numclient,cagnotte,suspendu,taillebase,reelTaille);
}