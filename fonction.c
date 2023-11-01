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

int loadArticle(int id[], float poid[], float volume[], float prix[], int tailleMax)
{
    FILE *File;
    File = fopen("./ressource/articles.csv", "r");

    int i=0;

    if (File==NULL)
    {
        printf("Erreur: fichier vide ou non existant \n");
        return -1; //erreur fichier
    }

    fscanf(File, "reference;poids (kg);volume (l);prix Unitaire\n");
    while (feof(File)==0 && i<tailleMax){
        fscanf(File, "%d;%f;%f;%f", &id[i], &poid[i], &volume[i], &prix[i]);
        i++;
    }
    if (i==tailleMax && feof(File)==0) return -2; //erreur tableau trop court
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

    int ind =frecherche(numClient,num,*taille,&trouve);
    while(trouve==1 || num<0) {
        printf("Erreur Saisir un autre numero client : \n");
        scanf("%d", &num);
        ind =frecherche(numClient,num,*taille,&trouve);
    }
   for (j=*taille;j>ind;j--) {
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
    int  article ,trouve ;
    float vol ;
    float poids1, prix1;
    if (*taille+1==tailleMax){
        return -1; //Erreur: tableau trop petit
    }
    printf("Quelle est la reference de l'article que vous voulez ajouter : \n");
    scanf("%d" ,&article);
    int ind = frecherche(ref ,article,*taille,&trouve);
    while(trouve==1 || article <0){
        printf("Erreur Saisir une autre reference : \n");
        scanf("%d",&article);
        ind = frecherche(ref ,article,*taille,&trouve);
    }

    for (int j = *taille; j >ind ; j--) {
        ref[j]=ref[j-1];
        poids[j]=poids[j-1];
        volume[j]=volume[j-1];
        prix[j]=prix[j-1];
    }
    printf("Veuillez Rentrer le poids de l'article ajouté : \n");
    scanf("%f",&poids1);
    printf("Veuillez entrer le volume de produit ajouté : \n");
    scanf("%fm",&vol);
    printf("Veuillez entrer le prix du produit ajouté : \n");
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
        printf("Num\tcagnotte\tsuspendue\t\n");
        for (i=0;i<taille;i++){
            printf("%d\t%.2f\t\t%d\t\n",numClient[i],cagnotte[i],suspendu[i]);
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

int DelClient  (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ) {

    int num ,i , trouve ;
    if (*taille+1==tailleMax){
        return -1; //Erreur: tableau trop petit
    }
    printf("Voici la liste des clients : \n");
    ShowClient(numClient, cagnotte, suspendu, *taille);
    printf("Quelle est la reference du client  que vous souhaitez supprimer : \n ");
    scanf("%d",&num);
    int indice = frecherche(numClient,num,*taille,&trouve);
    while (trouve==0 || num <0){
        printf("La reference client est inexistante ou incorrect veuillez re saisir la reference :\n");
        scanf("%d",&num);
        indice = frecherche(numClient,num,*taille,&trouve);
    }
    indice = frecherche(numClient,num,*taille,&trouve);
    for (i=indice;i<*taille;i++){
        numClient[i]=numClient[i+1];
        cagnotte[i]=cagnotte[i+1];
        suspendu[i]=suspendu[i+1];
    }
    *taille-=1;
    return 1;
}

//Attendre que sam finisse ca fonction LoadArticle
void ShowArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int taille ) {
    int i ;
    printf("Ref\tPoids\tVolume\tPrix\n");
    for (i=0 ;i<taille-1 ; i++){
        printf("%d\t%.2f\t%.2f\t%.2f\n",ref[i],poids[i],volume[i],prix[i]);
    }
}

//permet de rajouter les clients dans le fichier
void saveClient(int Tclient[], float Tcagnotte[], int Tsuspendue[], int taille){
    FILE *File;
    File = fopen("ressource/client.csv", "w");

    if (File != NULL){
        fprintf(File, "numClient;cagnotte;suspendu");
        for (int i = 0; i<taille; i++){
            fprintf(File, "\n%d;%.2f;%d", Tclient[i], Tcagnotte[i], Tsuspendue[i]);
        }
        fclose(File);
    }
}

//permet de rajouter les clients dans le fichier
//a tester
void saveArticle(int Tref[], float Tpoid[], float Tvolume[], float prix[], int taille){
    FILE *File;
    File = fopen("ressource/articles.csv", "w");
    
    if (File!=NULL){
        fprintf(File, "reference;poids (kg);volume (l);prix Unitaire");
        for (int i = 0; i<taille; i++) {
            fprintf(File, "\n%d;%.3f;%.2f;%.2f", Tref[i], Tpoid[i], Tvolume[i], prix[i]);
        }
        fclose(File);
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
    int  ref[100] ;
    float volume[100] ;
    float poids[100] , prix[100] ;
    int tl1 ;
    tl1= loadArticle(ref,poids,volume,prix,tp);
    printf("%d\n",tl1);
    tl = loadClient(numClient, cagnotte, suspendue, tp);
    erreur= DelClient(numClient, cagnotte, suspendue, &tl, tp);
    //saveClient(numClient,cagnotte,suspendue,tp,tl); a changer
    ShowClient(numClient,cagnotte,suspendue,tl);
    int Error = AddArticle(ref,poids,volume,prix,&tl1,tp);
    ShowArticle(ref,poids,volume,prix,tl1);
    printf("Bienvenue  sur l'application de BricoConstruction!\nRentrez votre identifiant\n");
    scanf("%d",&id);
    if (id==admin)
    {
        printf("===========================================================\n");
        printf("||Bienvenue dans la partie Administration de l application \n");
        printf("||Si vous voulez ajouter un adhérant tapez 0\n||Si vous voulez suspendre taper 1\n||Si vous voulez recréer une carte tapez 3 :\n");
        printf("===========================================================\n");
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
    /*
    int ref[100], tmax = 100, tailleA;
    float poid[100], volume[100], prix[100];
    tailleA = loadArticle(ref, poid, volume, prix, tmax);
    int numClient[100], suspendu[100], tailleC;
    float cagnotte[100];
    tailleC = loadClient(numClient, cagnotte, suspendu, tmax);
    printf("taille Article: %d\ntaille Client: %d\n", tailleA, tailleC);
    */
    int ref[100], tmax = 100, taille, erreur;
    float poid[100], volume[100], prix[100];
    taille = loadArticle(ref, poid, volume, prix, tmax);
    erreur = AddArticle(ref, poid, volume, prix, &taille, tmax);
    saveArticle(ref, poid, volume, prix, taille);
    /*
    int numClient[100], suspendu[100], taille, error, tmax=100, tailleC;
    float cagnotte[100];
    taille = loadClient(numClient, cagnotte, suspendu, tmax);
    error = AddClient(numClient, cagnotte, suspendu, &taille, tmax);
    saveClient(numClient, cagnotte, suspendu, taille);
        */
}