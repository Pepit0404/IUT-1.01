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

int frecherche (int numClient[],int val ,int taille,int *trouve){
    int i=0 ;
    while (i<taille){
        if (numClient[i]==val){
            *trouve=1;
            return i;
        }
        if (numClient[i]>val){
            *trouve = 0;
            return i ;
        }
        i++;
    }
}
//Cette Fonction est appelé quand l'admin a choisis d'ajouter un CLient
// peut etre a refaire avec fonction inFile()
int AddClient (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ){
    int num,j ;
    int trouve;
        if (*taille+1==tailleMax){
        return -1; //Erreur: tableau trop petit
    }
    printf("Quelle sera la numéros du client a ajouter : \n");
    scanf("%d",&num);

    int indice =inFile(num,numClient,*taille);
        while(indice>0){
            printf("Erreur Saisir un autre numero client : \n");
            scanf("%d",&num);
            indice =inFile(num,numClient,*taille);
        }
    int ind =frecherche(numClient,num,*taille,&trouve);
    printf("%d\n",j);
   for (j=*taille-1;j>ind;j--) {
        printf("%d\n",numClient[j]);
        numClient[j] = numClient[j -1];
        cagnotte[j] = cagnotte[j - 1];
        suspendu[j] = suspendu[j -1];

    }

    numClient[ind]=num;
    cagnotte[ind]=0;
    suspendu[ind]=0;
    *taille+=1;

    return 1 ;
}

int AddArticle(int ref[],float poids[] ,float volume[] ,float prix[] , int *taille, int tailleMax ){
    int i , article ,trouve ;
    float vol ;
    float poids1, prix1;
    if (*taille+1==tailleMax){
        return -1; //Erreur: tableau trop petit
    }
    printf("Quelle est la reference de l'article que vous voulez ajouter : \n");
    scanf("%d" ,&article);
    int indice =inFile(article,ref,*taille);
    while(indice>0){
        printf("Erreur Saisir une autre reference : \n");
        scanf("%d",&article);
        indice =inFile(article,ref,*taille);
    }
    int ind = frecherche(ref ,article,*taille,&trouve);
    for (int j = *taille-1; j >ind ; j--) {
        ref[j]=ref[j-1];
        poids[j]=poids[j-1];
        volume[j]=volume[j-1];
        prix[j]=prix[j-1];
    }
    printf("Veuillez Rentrez le poids de l'artcicle ajouter : \n");
    scanf("%f",&poids1);
    printf("Veuillez entrez le volume de produits ajouté : \n");
    scanf("%fm",&vol);
    printf("Veuillez entrez le prix du produits ajouté : \n");
    scanf("%f",&prix1);

    ref[ind]=article;
    poids[ind]=poids1;
    volume[ind]=vol;
    prix[ind]=prix1;
    *taille+=1;
    return 1 ;

}


void ShowClient (int numClient[], float cagnotte[], int suspendu[], int taille) {
        int i ;
        printf("NumClient\tcagnotte\tsuspendue\t\n");
        for (i=0;i<taille;i++){
            printf("%d\t%.2f\t%d\t\n",numClient[i],cagnotte[i],suspendu[i]);
        }

}

void ShowClientPrecis (int numClient[], float cagnotte[], int suspendu[], int taille){
    int num ;
    printf("Quelle est le numeros de client recherché  : \n");
    scanf("%d",&num);
    int dedans = inFile(num , numClient , taille);
    if ( dedans!=-1){
        printf("%d\t%.2f\t%d\n",numClient[dedans],cagnotte[dedans],suspendu[dedans]);
    } else{
        printf("Le numeros de client rechercher n'existe pas");
    }
}
/*
int DelClient  (int numClient[], float cagnotte[], int suspendu[], int taille) {

    int num ,i;
    i=taille ;
    ShowClient(numClient, cagnotte, suspendu, taille);
    printf("Quelle est la reference du client  que vous souhaitez supprimer : \n ");
    scanf("%d",&num);
    int dedans = inFile(num , numClient , taille);
    if (dedans!=-1){

        while (numClient[i]>num){
            numClient[i]=numClient[i-1];
            cagnotte[i]=cagnotte[i-1];
            suspendu[i]=suspendu[i-1];
            i-=1;
        }
        numClient[i-1]=numClient[i];
    }
    else {
        printf("La valeur choisis n'est pas dans la base \n");
        return -1;
    }



    return 1;
}*/

//Attendre que sam finisse ca fonction LoadArticle
void ShowArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int taille ) {
    int i ;
    printf("Reference\tPoids\tVolume\tPrix\n");
    for (i=0 ;i< taille ; i++){
        printf("%d\t%.2f\t%.2f\t%.2f\n",ref[i],poids[i],volume[i],prix[i]);
    }
}

//permet de rajouter les clients dans le fichier
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

//permet de rajouter les clients dans le fichier
//a tester
void saveArticle(int Tref[], float Tpoid[], int Tvolume[], int prix[], int tailleStart, int tailleEnd){
    FILE *File;
    File = fopen("./ressource/articles.csv", "a");
    
    if (File==NULL){
        printf("Erreur: fichier vide ou non existant \n"); //erreur fichier
    }
    for (int i =tailleStart; i<tailleEnd; i++) {
        fprintf(File, "\n%d;%f;%d;%d", Tref[i], Tpoid[i], Tvolume[i], prix[i]);
    }
}

//Faire fonction Ajouts article (Enzo)
//Faire Fonction ShowArticle (Enzo)
//Finir le Menu (Maeva) 

//Faire fonction qui avec (s) ecris dans le cvs les nouveaux tableaux , et avec (e) quite et save (Samuel)

void Menu(void)
{
    int admin=777, id, cadmin=0, tp=200, tl, erreur;
    int i;
    int numClient[200],  suspendue[200];
    float cagnotte[200];
    tl=loadClient(numClient, cagnotte, suspendue, tp);
    erreur=AddClient(numClient, cagnotte, suspendue, &tl, tp);
    saveClient(numClient,cagnotte,suspendue,tp,tl);
    ShowClient(numClient,cagnotte,suspendue,tl);
    printf("Bienvenue  sur l'application de BricoConstruction!\nRentrez votre identifiant\n");
    scanf("%d",&id);
    if (id==admin)
    {
        printf("Si vous voulez ajouter un adhérant tapez 0\nSi vous voulez suspendre taper 1\nSi vous voulez recréer une carte tapez 3 :\n");
        scanf("%d",&cadmin);
    }
    /*
    if (id!=admin)
    {
        for (i=0, i<=tp, i++)
            if (id==num>Client[i])
                
    }
*/

}

void test(void)
{
    return ;
    /*
    
    int taille=100 , reelTaille, taillebase, menu;
    int  ref[100] ;
    float volume[100] ;
    float poids[100] , prix[100] ;*/

    //int numclient[100], suspendu[100];
    //float cagnotte[100];
    
    /*taillebase = loadClient(numclient,cagnotte,suspendu, taille);
    //reelTaille = AddClient(numclient,cagnotte,suspendu,taillebase);
    saveClient(numclient,cagnotte,suspendu,taillebase,15);
    printf("%d",numclient[0]);
    ShowClient(numclient,cagnotte,suspendu,15);
    ShowClientPrecis(numclient,cagnotte,suspendu,15);*/
    /*ShowArticle(ref ,poids,volume,prix,5);*/
}