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
    if (i==taille && feof(File)==0) return -2; //erreur tableau trop court
    return i;
}

int loadArticle(int id[], float poid[], float volume[], float prix[], int tailleMax)
{
    FILE *File;
    File = fopen("./ressource/articles.csv", "r");

    int i=0;

    if (File==NULL)
    {
        printf("Erreur: fichier vide ou inexistant \n");
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

int frecherche (int tab[], int val , int taille, int *trouve){
    int i=0 ;
    while (i<taille){
        if (tab[i]==val){
            *trouve=1;
            return i;
        }
        if (tab[i]>val){
            *trouve = 0;
            return i ;
        }
        i++;
    }
    *trouve = 0;
    return -1;
}

int AddClient (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax){
    int num, j, erreur;
    int trouve;
    if (*taille+1==tailleMax)
        return -1; //Erreur: tableau trop petit
    printf("Quel sera le numéro du client à ajouter : \n");
    erreur = scanf("%d",&num);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%d", &num);
    }
    while (num==777){
        printf("Ce numéro est reservé\n");
        printf("Veuillez re saisir une valeur : \n");
        erreur = scanf("%d",&num);
        while (erreur==0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veuillez réessayer: ");
            erreur = scanf("%*c%d", &num);
        }
    }
    int ind =frecherche(numClient,num,*taille,&trouve);
    while(trouve==1 || num<0) {
        while (num==777){
            printf("Ce numéros est reservé\n");
            printf("Veuillez re saisir une valeur : \n");
            erreur = scanf("%d",&num);
            while (erreur==0)
            {
                printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                printf("Veuillez réessayer: ");
                erreur = scanf("%*c%d", &num);
            }
        }
        printf("Erreur, veuillez saisir un autre numéro client : \n");
        erreur = scanf("%d", &num);
        while (erreur==0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veuillez réessayer: ");
            erreur = scanf("%*c%d", &num);
        }
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
    printf("Client bien ajouté !\n");
    return 1 ;
}

int AddNouvelleCarte (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ,int reference){
    int j ;
    int trouve;
    if (*taille+1==tailleMax)
        return -1; //Erreur: tableau trop petit
    int ind =frecherche(numClient,reference,*taille,&trouve);
    for (j=*taille;j>ind;j--) {
        numClient[j] = numClient[j -1];
        cagnotte[j] = cagnotte[j - 1];
        suspendu[j] = suspendu[j -1];

    }

    numClient[ind]=reference;
    cagnotte[ind]=0;
    suspendu[ind]=0;
    *taille+=1;
    printf("Client bien ajouté !\n");
    return 1 ;
}

int AddArticle(int ref[],float poids[] ,float volume[] ,float prix[] , int *taille, int tailleMax ){
    int  article, trouve, erreur;
    float vol ;
    float poids1, prix1;
    if (*taille+1==tailleMax)
        return -1; //Erreur: tableau trop petit
    printf("Quelle est la référence de l'article que vous voulez ajouter : \n");
    erreur = scanf("%d" ,&article);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%d", &article);
    }
    int ind = frecherche(ref ,article,*taille,&trouve);
    while(trouve==1 || article <0){
        printf("Erreur, veuillez saisir une autre reference : \n");
        erreur = scanf("%d",&article);
        while (erreur==0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veuillez réessayer: ");
            erreur = scanf("%*c%d", &article);
        }
        ind = frecherche(ref ,article,*taille,&trouve);
    }

    for (int j = *taille; j >ind ; j--) {
        ref[j]=ref[j-1];
        poids[j]=poids[j-1];
        volume[j]=volume[j-1];
        prix[j]=prix[j-1];
    }
    printf("Veuillez entrer le poids de l'article ajouté : \n");
    erreur = scanf("%f",&poids1);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%f", &poids1);
    }
    printf("Veuillez entrer le volume de produit ajouté : \n");
    erreur = scanf("%f",&vol);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%f", &vol);
    }
    printf("Veuillez entrer le prix du produit ajouté : \n");
    erreur = scanf("%f",&prix1);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%f", &prix1);
    }
    ref[ind]=article;
    poids[ind]=poids1;
    volume[ind]=vol;
    prix[ind]=prix1;
    *taille+=1;
    return 1 ;
}

void ShowClient(int numClient[], float cagnotte[], int suspendu[], int taille) {
        int i ;
        printf("Num\tcagnotte\tsuspendue\t\n");
        for (i=0;i<taille;i++){
            printf("%d\t%.2f\t\t%d\t\n",numClient[i],cagnotte[i],suspendu[i]);
        }

}

int ShowClientPrecis(int numClient[], float cagnotte[], int suspendu[], int taille){
    int num, dedans, erreur;
    printf("Quel est le numéro de client recherché  : \n ");
    erreur = scanf("%d",&num);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%d", &num);
    }
    int position = frecherche(numClient, num, taille, &dedans);
    if (dedans==1) printf("%d\t%.2f\t%d\n",numClient[position],cagnotte[position],suspendu[position]);
    else printf("Le numero de client recherché n'existe pas\n");
    if (suspendu[position]==1) return -1;
    return 1;
}

void ShowArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int taille ) {
    int i ;
    printf("Ref\tPoids\tVolume\tPrix\n");
    for (i=0 ;i<taille-1 ; i++){
        printf("%d\t%.2f\t%.2f\t%.2f\n",ref[i],poids[i],volume[i],prix[i]);
    }
}

void ShowArticlePrecis (int ref[],float poids[] ,float volume[] ,float prix[] , int taille )
{
    int num, dedans, erreur;
    printf("Quel est le numero de l'article recherché  : \n ");
    erreur = scanf("%d",&num);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%d", &num);
    }
    int position = frecherche(ref, num, taille, &dedans);
    if ( dedans==1){
        printf("%d\t%.2f\t%.2f\t%.2f\t\n",ref[position],poids[position],volume[position],prix[position]);

    } else{
        printf("Le numero d'article recherché n'existe pas");
    }
}

int DelClient  (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ) {

    int num ,i , trouve, erreur;
    if (*taille==0)
        return -1;
    printf("Voici la liste des clients : \n");
    ShowClient(numClient, cagnotte, suspendu, *taille);
    printf("Quelle est la reference du client  que vous souhaitez supprimer : \n ");
    erreur = scanf("%d",&num);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%d", &num);
    }
    int indice = frecherche(numClient,num,*taille,&trouve);
    while (trouve==0 || num <0){
        printf("La reference client est inexistante ou incorrecte veuillez re saisir la reference :\n");
        erreur = scanf("%d",&num);
        while (erreur==0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veuillez réessayer: ");
            erreur = scanf("%*c%d", &num);
        }
        indice = frecherche(numClient,num,*taille,&trouve);
    }
    indice = frecherche(numClient,num,*taille,&trouve);
    for (i=indice;i<*taille;i++){
        numClient[i]=numClient[i+1];
        cagnotte[i]=cagnotte[i+1];
        suspendu[i]=suspendu[i+1];
    }
    *taille-=1;
    printf("Client bien supprimé ! \n");    
    return 1;
}

int DelArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int *taille , int tailleMax )
{
    int ref1 , i ,trouve, erreur;
    if (*taille==0)
        return -1;
    printf("Voicie la liste des articles : \n");
    ShowArticle(ref,poids,volume,prix,*taille);
    printf("Quelle est la reference de l'article que vous souhaitez supprimer : \n");
    erreur = scanf("%d",&ref1);
    while (erreur==0)
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Veuillez réessayer: ");
        erreur = scanf("%*c%d", &ref1);
    }
    int indice = frecherche(ref,ref1,*taille,&trouve);
    while (trouve==0 || ref <0){
        printf("La reference de l'article est inexistante ou negative veuillez re saisir : \n");
        erreur = scanf("%*c%d",&ref1);
        while (erreur==0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veuillez réessayer: ");
            erreur = scanf("%*c%d", &ref1);
        }
        indice =frecherche(ref,ref1,*taille,&trouve);
    }
    for (i=indice;i<*taille;i++){
        ref[i]=ref[i+1];
        poids[i]=poids[i+1];
        volume[i]=volume[i+1];
        prix[i]=prix[i+1];

    }
    *taille-=1;
    printf("Artcile bien supprimé ! \n");
    return 1;

}

void saveClient(int Tclient[], float Tcagnotte[], int Tsuspendue[], int taille){
    FILE *File;
    File = fopen("ressource/client.csv", "w");

    if (File != NULL){
        fprintf(File, "numClient;cagnotte;suspendu");
        for (int i = 0; i<=taille; i++){
            fprintf(File, "\n%d;%.2f;%d", Tclient[i], Tcagnotte[i], Tsuspendue[i]);
        }  
    }
    fclose(File);
}

void saveArticle(int Tref[], float Tpoid[], float Tvolume[], float prix[], int taille){
    FILE *File;
    File = fopen("ressource/articles.csv", "w");
    
    if (File!=NULL){
        fprintf(File, "reference;poids (kg);volume (l);prix Unitaire");
        for (int i = 0; i<=taille; i++) {
            fprintf(File, "\n%d;%.3f;%.2f;%.2f", Tref[i], Tpoid[i], Tvolume[i], prix[i]);
        }
    }
    fclose(File);
}

float afficheRecap(int pRef[], int pQuantite[], int ptaille, int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int Ttaille, float cagnotte, float volmax, float poidmax, float prixMax, float *prixTT, float *chargeTT, float *volTT){
    int place, trouve, quantite;
    float cagnotteA=0;
    *prixTT = 0;
    *volTT = 0;
    *chargeTT = 0;
    printf("\033[0;32m");
    printf("\n\n===========================================================\n");
    printf("Réf\tQté\tPoids\tVol\tPrixU\tPoidsTot\tVolTot\tPrixTT\tCagnotte\n");
    for (int i=0; i<ptaille; i++){
        quantite = pQuantite[i];
        place = frecherche(Tref, pRef[i], Ttaille, &trouve);
        *prixTT = *prixTT + Tprix[place]*quantite;
        cagnotteA = Tprix[place]*quantite/10.0;
        cagnotte += cagnotteA;
        *volTT += Tvolume[place]*quantite;
        *chargeTT += Tpoids[place]*quantite;
        printf("%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\t%.2f\t%.2f\n", pRef[i], quantite, Tpoids[place], Tvolume[place], Tprix[place], Tpoids[place]*quantite, Tvolume[place]*quantite, Tprix[place]*quantite, cagnotteA);
    }
    printf("\nPrix total à payer:\t%.2f euros\n", *prixTT);
    if (prixMax!=-1) {
        if (prixMax-(*prixTT)<0){
            printf("\033[0;31mAttention dépassement de la limite de budget de ");
            printf("%.2f\n", (*prixTT)-prixMax);
            printf("\033[0;32m");
        } else printf("Budget restant: %.2f\n", prixMax-(*prixTT));
    }
    printf("Cagnotte totale:\t%.2f euros\n", cagnotte);
    printf("\nVolume utilisé\t: %.2f litres\n", *volTT);
    printf("Volume restant\t: ");
    if (volmax-(*volTT) < 0) printf("\033[0;31mAttention dépassement du volume autorisé de %.2f litres\n\033[0;32m", *(volTT)-volmax);
    else printf("%.2f litres\n", volmax-(*volTT));
    printf("\nCharge Actuelle\t: %.2f kg\n", *chargeTT);
    printf("Charge restante\t: ");
    if (poidmax-(*chargeTT) < 0) printf("\033[0;31mAttention dépassement de la charge autorisée de %.2f kg\n\033[0;32m", (*chargeTT)-poidmax);
    else printf("%.2f kg\n", poidmax-(*chargeTT));
    printf("===========================================================\n");
    printf("\033[0;36m");

    return cagnotte;
}

float Client(int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int tailleMax, int Ttaille, float cagnotte){
    int pRef[tailleMax], pQuantite[tailleMax], ptaille=0, action=0, erreur;
    float volMax, poidMax, nCagnotte=cagnotte, prixMax, prixTT=0, poidTT=0, volumeTT=0;
    char choix;
    printf("\033[0;36m");
    printf("===========================================================\n");
    printf("\033[0;35m");
    printf("|Bienvenue\n");
    printf("\033[0;36m");
    printf("===========================================================\n");
    printf("Veuillez définir la charge max de votre véhicule (kg): ");
    erreur = scanf("%f", &poidMax);
    while (erreur==0 || poidMax<0)
    {
        printf("\033[0;31mValeurs impossibles\n\033[0;36mVeuillez définir la charge max de votre véhicule (kg): ");
        erreur = scanf("%*c%f", &poidMax);
    }
    printf("Veuillez définir le volume max de votre véhicule (L): ");
    erreur = scanf("%f", &volMax);
    while (erreur==0 || volMax<0)
    {
        printf("\033[0;31mValeurs impossibles\033[0;36m\nVeuillez définir le volume max de votre véhicule (L): ");
        erreur = scanf("%*c%f", &volMax);
    }
    printf("Voulez vous définir une limite budgétaire ? (y/n)\n");
    erreur = scanf("%*c%c", &choix);
    while (erreur==0 || (choix!='y' && choix!='Y' && choix!='n' && choix!='N') )
    {
        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        printf("Voulez vous définir une limite budgétaire ? (y/n)\n");
        erreur = scanf("%*c%c", &choix);
    }
    if (choix=='y' || choix=='Y'){
        printf("Veillez définir une limitation: ");
        erreur = scanf("%f", &prixMax);
        while (erreur==0 || prixMax<0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veillez définir une limitation: ");
            erreur = scanf("%*c%f", &prixMax);
        }
        
    } else if (choix=='n' || choix=='N') prixMax=-1;
    while (action!=-1)
    {
        
        printf("\n\n===========================================================\n");
        printf("||Si vous voulez arréter là tapez -1\n||Si vous voulez ajouter au panier tapez 0\n||Si vous voulez payer tapez 1\n||Si vous voulez modifier un article taper 2\n||Si vous voulez suprimer un article tapez 3\n||Si vous voulez rénitialiser le panier tapez 4\n||Si vous voulez voir les articles tapez 5\n");
        erreur = scanf("%*c%d", &action);
        if (erreur==0) {
            action=999;
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
        }
        if (action!=-1){
            if (action==0){
                int ref, trouve, quantite;
                printf("\n\nReference article: ");
                erreur = scanf("%*c%d", &ref);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("\n\nReference article: ");
                    erreur = scanf("%d", &ref);
                }
                frecherche(Tref, ref, Ttaille, &trouve);
                while (trouve!=1)
                {
                    printf("L'article %d n'existe pas\n", ref);
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &ref);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("\n\nReference article: ");
                        erreur = scanf("%*c%d", &ref);
                    }
                    frecherche(Tref, ref, Ttaille, &trouve);
                }
                frecherche(pRef, ref, ptaille, &trouve);
                if (trouve == 0){
                    printf("Quantité prise: ");
                    erreur = scanf("%*c%d", &quantite);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Quantité prise: ");
                        erreur = scanf("%*c%d", &quantite);
                    }
                    pRef[ptaille] = ref;
                    pQuantite[ptaille] = quantite;
                    ptaille+=1;
                }else printf("L'article %d déjà present dans votre panier \n", ref);
            }
            else if (action==1) {
                int modif=0;
                if (prixMax<prixTT && prixMax!=-1) {
                    int reponse;
                    printf("\n\nAttention votre panier dépasse de %.2f euros\n", prixTT-prixMax);
                    printf("Continuer quand même tapez 1\n");
                    printf("Prendre depuis la cagnotte tapez 2\n");
                    printf("Enlever des articles 3\n");
                    erreur = scanf("%*c%d", &reponse);
                    while (erreur==0 && reponse!=1 && reponse!=2 && reponse!=3)
                    {
                        printf("Reponse invalide veuillez réessayer: ");
                        erreur = scanf("%*c%d", &reponse);
                    }
                    if (reponse==1) modif=0;
                    else if (reponse==2) {
                        if (nCagnotte>prixMax-prixTT) {
                            nCagnotte += prixMax-prixTT;
                            modif=0;
                        }
                        else {
                            printf("Désolé mais votre cagnotte ne peut pas compenser la différence\n");
                            modif=1;
                        }
                    } else modif=1;
                }
                if (poidMax<poidTT && modif!=1) {
                    int reponse;
                    printf("\n\nAttention votre panier dépasse de %.2f kilos\n", poidTT-poidMax);
                    printf("Continuer quand même tapez 1\n");
                    printf("Enlever des articles tapez 2\n");
                    erreur = scanf("%d", &reponse);
                    while (erreur==0 && reponse!=1 && reponse!=2 && reponse!=3)
                    {
                        printf("Reponse invalide veuillez réessayer: ");
                        erreur = scanf("%*c%d", &reponse);
                    }
                    if (reponse==1) modif=0;
                    else modif=1;
                }
                if (volMax<volumeTT && modif!=1) {
                    int reponse;
                    printf("\n\nAttention votre panier dépasse de %.2f L\n", volumeTT-volMax);
                    printf("Continuer quand même tapez 1\n");
                    printf("Enlever des articles 2\n");
                    erreur = scanf("%d", &reponse);
                    while (erreur==0 && reponse!=1 && reponse!=2 && reponse!=3)
                    {
                        printf("Reponse invalide veuillez réessayer: ");
                        erreur = scanf("%*c%d", &reponse);
                    }
                    if (reponse==1) modif=0;
                    else modif=1;
                }
                if (modif==0) {
                    printf("Achat de %.2f euros\nCagnotte de %.2f euros\n\nAu revoir\n", prixTT, nCagnotte);
                    return nCagnotte;
                }
            }
            else if (action==2) {
                int ref, trouve, place, quantite;
                printf("\n\nReference article: ");
                erreur = scanf("%d", &ref);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention réponse invalide\n\033[0;36m");
                    erreur = scanf("%*c%d", &ref);
                }
                
                place = frecherche(pRef, ref, ptaille, &trouve);
                while (trouve!=1)
                {
                    printf("Vous n'avez pas l'artile %d dans votre panier\n", ref);
                    erreur = scanf("%d", &ref);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention réponse invalide\n\033[0;36m");
                        erreur = scanf("%*c%d", &ref);
                    }
                    place = frecherche(pRef, ref, ptaille, &trouve);
                }
                printf("Nouvelle quantité voulue: ");
                erreur = scanf("%d", &quantite);
                while (quantite<=0 || erreur==0)
                {
                    if (quantite<=0) printf("La quantité ne peut pas etre inférieure ou égale à 0\n");
                    printf("\033[0;31mAttention réponse invalide\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    scanf("%*c%d", &quantite);
                }
                pQuantite[place] = quantite;
            }
            else if (action == 3) {
                int ref, trouve, place;
                printf("\n\nReference article: ");
                erreur = scanf("%d", &ref);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention réponse invalide\n\033[0;36m");
                    printf("Veilliez réessayer: ");
                    erreur = scanf("%*c%d", &ref);
                }
                
                place = frecherche(pRef, ref, ptaille, &trouve);
                while (trouve!=1)
                {
                    printf("Vous n'avez pas l'article %d dans votre panier\n", ref);
                    printf("Veuillez réessayer: \n");
                    erreur = scanf("%d", &ref);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention réponse invalide\n\033[0;36m");
                        printf("Veilliez réessayer: ");
                        erreur = scanf("%*c%d", &ref);
                    }
                    
                    place = frecherche(pRef, ref, ptaille, &trouve);
                }
                for (int i=place; i<ptaille; i++) {
                    pRef[i]=pRef[i+1];
                    pQuantite[i]=pQuantite[i+1];
                }
                ptaille--;
                printf("Article %d supprimé\n", ref);
            }
            else if (action == 4){
                char choix;
                printf("\nEtes vous sur de vouloir remettre à 0 votre panier ? (y/n)\n");
                erreur = scanf("%*c%c", &choix);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention réponse invalide\n\033[0;36m");
                    printf("Veilliez réessayer: ");
                    erreur = scanf("%*c%c", &choix);
                }
                
                if (choix=='y' || choix=='Y') ptaille = 0;
            }
            if (action == 5) {
                printf("\n\n");
                ShowArticle(Tref, Tpoids, Tvolume, Tprix, Ttaille);
            }
            else nCagnotte = afficheRecap(pRef, pQuantite, ptaille, Tref, Tpoids, Tvolume, Tprix, Ttaille, cagnotte, volMax, poidMax, prixMax, &prixTT, &poidTT, &volumeTT);
        }
    }
    printf("\033[0;33m");
    printf("============================================\n");
    printf("Au revoir cher(e) client(e) \n");
    return nCagnotte;
}

void administrateur(int numClient[], float cagnotte[], int suspendue[], int ref[], float volume[], float prix[], float poids[], int tp, int tla, int tlc)
{
    int choix,choixa,ref2, choixc, id, id1,id2, trouve,num, modifa, nvref,nvcarte,reference, susp, erreur;
    float nvvol,nvpo,nvpr;
    printf("\033[0;35m");
    printf("===========================================================\n");
    printf("|| Bienvenue sur l'interface administrative du magasin\n");
    printf("===========================================================\n");
    
    while(choix!=-1)
    {
        
        printf(" ====Voulez vous====\n ||Gérer les articles tapez 0\n ||Gérer les cartes tapez 1\n ||Si vous voulez afficher un client en particulier tapez 2\n ||Si vous voulez afficher un article particulier taper 3\n ||Si vous voulez vous déconnecter taper 4\n");
        printf("===========================================================\n");
        erreur = scanf("%d",&choix);
        while (erreur==0)
        {
            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
            printf("Veuillez réessayer: ");
            erreur = scanf("%*c%d", &choix);
        }
        while (choix!=0 && choix!=1 && choix!=2 && choix!=3 && choix!=4)
        {
        printf(" ====Voulez vous====\n ||Gérer les articles tapez 0\n ||Gérer les cartes tapez 1\n ||Si vous voulez afficher un client en particulier tapez 2\n ||Si vous voulez afficher un article particulier taper 3\n ||Si vous voulez vous déconnecter taper 4\n");
        printf("===========================================================\n");
        scanf("%*c%d", &choix);
        }
        if (choix==0)
        { 
            printf("===========================================================\n");
            printf(" ||Si vous voulez modifier un article tapez 0\n ||Si vous voulez supprimer un article tapez 1\n ||Si vous voulez en ajouter un faites le 2\n ||Si vous voulez modifier la reference faites le 3 \n ");
            printf("===========================================================\n");
            erreur = scanf("%d",&choixa);
            while (erreur==0 && choixa!=0 && choixa!=1 && choixa!=2 && choixa!=3 )
            {
                while (erreur==0)
                printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                printf("Veuillez réessayer: ");
                erreur = scanf("%*c%d",&choixa);
            }
            if (choixa==0)
            {

                printf("Quel article voulez vous modifier ?\n");
                erreur = scanf("%d", &id);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &id);
                }
                frecherche (ref, id, tla, &trouve);
                while (trouve==0 || num <0)
                {
                    printf("La reference article est inexistante ou incorrect veuillez re saisir la reference :\n");
                    erreur = scanf("%*c%d",&num);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%d", &num);
                    }
                    id = frecherche(ref,num,tla,&trouve);
                }
                printf("Voulez vous modifier, le volume (0), le prix (1), le poids(2) , la reference (3)\n");
                erreur = scanf("%d",&modifa);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &modifa);
                }
                if (modifa==0)
                {
                    printf("Donnez le nouveau volume de l'article\n");
                    erreur = scanf("%f",&nvvol);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%f", &nvvol);
                    }
                    volume[id]=nvvol;
                }
                if (modifa==1)
                {
                    printf("Donnez le nouveau prix de l'article\n");
                    erreur = scanf("%f",&nvpr);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%f", &nvpr);
                    }
                    prix[id]=nvpr;
                }
                if (modifa==2)
                {
                    printf("Donnez le nouveau poids de l'article\n");
                    erreur = scanf("%f",&nvpo);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%f", &nvpo);
                    }
                    poids[id]=nvpo;
                }
                if (modifa==3)
                {
                    printf("Donnez la nouvelle référence de l'article l'article\n");
                    erreur = scanf("%d",&nvref);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%d", &nvref);
                    }
                    numClient[id]=nvref;
                }
                
                
            }   
            if (choixa==1)
            {
                erreur=DelArticle (ref,poids ,volume , prix,  &tla, tp);
                if (erreur==-1)printf("vous ne pouvez pas supprimer, le tableau est vide\n");
            }
            if (choixa==2)
            {
                erreur=AddArticle(ref,poids,volume,prix,&tla, tp);
                if (erreur==-1) printf("tableau trop petit\n");
            }
            if (choixa==3)
            {
                int new_ref ,poubelle;
                printf("Quelle est la rérérence que vous souhaitez modifier \n");
                erreur = scanf("%d",&ref2);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &ref2);
                }
                int ind2=frecherche(ref,ref2,tla,&poubelle);
                printf("Quelle sera la nouvelle référence : \n");
                erreur = scanf("%d",&new_ref);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &new_ref);
                }
                ref[ind2]=new_ref;
                printf("Référence modifiée \n");
            }
        }
        if (choix == 1)
        
        {
            printf("===========================================================\n");
            printf(" ||si vous voulez modifier le statut d'une carte tapez 0\n ||Si vous voulez creer une carte tapez 1\n ||Si vous voulez supprimer une carte tapez le 2\n");
            printf("===========================================================\n");
            erreur = scanf("%d",&choixc);
            while (erreur==0 && choixc!=0 && choixc!=1 && choixc!=2  )
            {
                printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                printf("Veuillez réessayer: ");
                erreur = scanf("%*c%d",&choixc);
            }

            if (choixc==0)
            {
                printf("Quel carte voulez vous suspendre\n");
                erreur = scanf("%d",&num);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &num);
                }
                id1=frecherche(numClient,num,tlc,&trouve);
                suspendue[id1]=1;
                printf("voulez vous à présent créer une nouvel carte pour ce client (si oui tapez 0 si non tapez 1)\n");
                erreur = scanf("%d",&nvcarte);
                while (erreur==0)
                {
                    printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                    printf("Veuillez réessayer: ");
                    erreur = scanf("%*c%d", &nvcarte);
                }
                if (nvcarte==0)
                {
                    printf("Quel sera le numéro de cette nouvelle carte ?\n");
                    erreur = scanf("%d",&reference);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%d", &reference);
                    }
                    AddNouvelleCarte(numClient, cagnotte, suspendue, &tlc,tp,reference);
                    id2=frecherche(numClient,num,tlc,&trouve);
                    cagnotte[id2]=cagnotte[id2];
                }
            }
            if (choixc==1)
            {
                erreur=AddClient(numClient,cagnotte,suspendue,&tlc,tp);
                printf("%d", tlc);
                if (erreur==-1)
                    printf("tableau trop petit\n");
            }
            if (choixc==2)
            {
                erreur=DelClient(numClient, cagnotte,suspendue, &tlc, tp);
                if (erreur==-1) printf("vous ne pouvez pas supprimer, le tableau est vide\n");
            }
        }
        if (choix == 2){
            susp=ShowClientPrecis(numClient, cagnotte, suspendue,tlc);
            if (susp==-1)
                {
                    printf("Cette carte a été suspendue, voulez vous en refaire une autre ?\n");
                    erreur = scanf("%d",&nvcarte);
                    while (erreur==0)
                    {
                        printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                        printf("Veuillez réessayer: ");
                        erreur = scanf("%*c%d", &nvcarte);
                    }
                    if (nvcarte==0)
                    {
                        printf("Quel sera le numéro de cette nouvelle carte ?\n");
                        erreur = scanf("%d", &reference);
                        while (erreur==0)
                        {
                            printf("\033[0;31mAttention : réponse non conforme\n\033[0;36m");
                            printf("Veuillez réessayer: ");
                            erreur = scanf("%*c%d", &reference);
                        }
                        AddNouvelleCarte (numClient, cagnotte, suspendue, &tlc,tp ,reference);
                        id2=frecherche(numClient,num,tlc,&trouve);
                        cagnotte[id2]=cagnotte[id2];
                    }
                }
        }
        if (choix == 3)
            ShowArticlePrecis(ref,poids,volume,prix,tlc);
        if (choix == 4){
            printf("===========================================================\n");
            printf(" || Au revoir l administrateur(e)\n");
            printf("===========================================================\n");
            return ;
        }


    }



}

void Menu(void)
{
    int admin=777, id, tp=200, tl, run=1, place, trouve;
    int numClient[tp],  suspendue[tp];
    float cagnotte[tp];
    int  ref[tp] ;
    float volume[tp] ;
    float poids[tp] , prix[tp] ;
    int tl1 ;
    tl1= loadArticle(ref,poids,volume,prix,tp);
    tl = loadClient(numClient, cagnotte, suspendue, tp);

    while (run){
        int erreur;
        printf("\033[0;33m");
        printf("===========================================================\n");
        printf(" ||Bienvenue  sur l'application de BricoConstruction!\n===========================================================\nRentrez votre identifiant/Ou tapez -1 pour Arreter \n");
        erreur = scanf("%d",&id);
        while (erreur==0)
        {
            printf("Reponse invalide\nRentrez votre identifiant/Ou tapez -1 pour Arreté\n");
            erreur = scanf("%*c%d",&id);
        }
        printf("===========================================================\n");
        
        if (id==admin)
        {
            administrateur(numClient, cagnotte, suspendue, ref, volume, prix, poids, tp,  tl1, tl);

        }
        else if (id==-1)
        {
            run=0;
            saveClient(numClient, cagnotte, suspendue, tl);
            saveArticle(ref, poids, volume, prix, tl1);
        }
        else if (id!=admin)
        {
            place = frecherche(numClient, id, tl, &trouve);
            if (trouve>0){
                if (suspendue[place]==0)
                    cagnotte[place] = Client(ref, poids, volume,  prix, tp, tl, cagnotte[place]);
                else 
                    printf("Cette carte a été suspendue. Veuillez contacter l'assistance.\n\n\n");
            }
            else printf("Identifiant inconnu\n\n");
        }
    }
}

void test(void)
{
    Menu();
    /*
    int numClient[200],  suspendue[200], tp=200;
    float cagnotte[200];
    int  ref[100] ;
    float volume[100] ;
    float poids[100] , prix[100] ;
    int tl1 ;
    //Client();
    tl1= loadArticle(ref,poids,volume,prix,tp);
    DelArticle(ref,poids,volume,prix,&tl1,100);
    ShowArticle(ref,poids,volume,prix,tl1);
    Client(ref, poids, volume, prix, tp, tl1, 42, 0);
        ShowClient(numClient,cagnotte,suspendue,tl);
    ShowArticle(ref,poids,volume,prix,tl1);
    */
}