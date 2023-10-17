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
//Faire fonction Ajouts article (Enzo)
//Faire Fonction ShowArticle (Enzo)
//Finir le Menu (Maeva)
//Faire fonction qui avec (s) ecris dans le cvs les nouveaux tableaux , et avec (e) quite et save (Samuel)


void test(void)
{
    int taille=100 , result;
    int  ref[taille] ;
    float volume[taille] ;
    float poids[taille] , prix[taille] ;

    int num[taille], suspendu[taille], etat, i=2;
    float cagnotte[taille];
    etat = loadClient(num, cagnotte, suspendu, taille);
    printf("etat :%d \n",etat);
    printf("%d;%.2f;%d \n",num[i], cagnotte[i], suspendu[i]);
    result=AddClient(num ,cagnotte ,suspendu ,etat);
    printf("%d\n" , result);
    printf("----------------\n");
    printf("%d;%.2f;%d \n",num[etat], cagnotte[etat], suspendu[etat]);
    printf("----------------\n");
    ShowClient(num,cagnotte,suspendu,result);
    int taille_artc= loadArticle(ref,poids,volume,prix ,taille);
    int artc = AddArticle(ref,poids,volume ,prix , taille_artc);
    printf("%d\t%.2f\t%.2f\t%.2f\t\n",ref[artc-1],poids[artc-1],volume[artc-1],prix[artc-1]);
}