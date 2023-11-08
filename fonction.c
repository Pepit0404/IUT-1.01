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

int AddClient (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ){
    int num,j ;
    int trouve;
    if (*taille+1==tailleMax)
        return -1; //Erreur: tableau trop petit
    printf("Quelle sera le numéro du client à ajouter : \n");
    scanf("%d",&num);
    while (num==777){
        printf("Ce numéros est reservé\n");
        printf("Veuillez re saisir une valeur : \n");
        scanf("%d",&num);
    }
    int ind =frecherche(numClient,num,*taille,&trouve);
    while(trouve==1 || num<0) {
        while (num==777){
            printf("Ce numéros est reservé\n");
            printf("Veuillez re saisir une valeur : \n");
            scanf("%d",&num);
        }
        printf("Erreur Saisir un autre numéro client : \n");
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

    return 1 ;
}

int AddArticle(int ref[],float poids[] ,float volume[] ,float prix[] , int *taille, int tailleMax ){
    int  article ,trouve ;
    float vol ;
    float poids1, prix1;
    if (*taille+1==tailleMax)
        return -1; //Erreur: tableau trop petit
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
    printf("Veuillez entrer le poids de l'article ajouté : \n");
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
    int num, dedans;
    printf("Quelle est le numero de client recherché  : \n ");
    scanf("%d",&num);
    int position = frecherche(numClient, num, taille, &dedans);
    if ( dedans==1){
        printf("%d\t%.2f\t%d\n",numClient[position],cagnotte[position],suspendu[position]);

    } else{
        printf("Le numero de client recherché n'existe pas");
    }
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
    int num, dedans;
    printf("Quelle est le numero de l'article recherché  : \n ");
    scanf("%d",&num);
    int position = frecherche(ref, num, taille, &dedans);
    if ( dedans==1){
        printf("%d\t%.2f\t%.2f\t%.2f\t\n",ref[position],poids[position],volume[position],prix[position]);

    } else{
        printf("Le numero d'article recherché n'existe pas");
    }
}

int DelClient  (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ) {

    int num ,i , trouve ;
    if (*taille==0)
        return -1;
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

int DelArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int *taille , int tailleMax )
{
    int ref1 , i ,trouve ;
    if (*taille==0)
        return -1;
    printf("Voicie la liste des articles : \n");
    ShowArticle(ref,poids,volume,prix,*taille);
    printf("Quelle est la ref de l article que vous souhaitez supprimer : \n");
    scanf("%d",&ref1);
    int indice = frecherche(ref,ref1,*taille,&trouve);
    while (trouve==0 || ref <0){
        printf("La reference de l'artcile est inexistante ou negatif veuillez re saisir : \n");
        scanf("%d",&ref1);
        indice =frecherche(ref,ref1,*taille,&trouve);
    }
    for (i=indice;i<*taille;i++){
        ref[i]=ref[i+1];
        poids[i]=poids[i+1];
        volume[i]=volume[i+1];
        prix[i]=prix[i+1];

    }
    *taille-=1;
    printf("Artcile bien supprimé ! ")
    return 1;

}



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

float afficheRecap(int pRef[], int pQuantite[], int ptaille, int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int Ttaille, float cagnotte, float volmax, float poidmax, float prixMax, float *prixTT){
    int place, trouve, quantite;
    float volTT=0, chargeTT=0, cagnotteA=0, prixC=0;
    *prixTT = 0;
    printf("\n\n===========================================================\n");
    printf("Réf\tQté\tPoids\tVol\tPrixU\tPoidsTot\tVolTot\tPrixTT\tCagnotte\n");
    for (int i=0; i<ptaille; i++){
        quantite = pQuantite[i];
        place = frecherche(Tref, pRef[i], Ttaille, &trouve);
        *prixTT = *prixTT + Tprix[place]*quantite;
        cagnotteA = Tprix[place]*quantite/10.0;
        cagnotte += cagnotteA;
        volTT += Tvolume[place]*quantite;
        chargeTT += Tpoids[place]*quantite;
        printf("%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\t%.2f\t%.2f\n", pRef[i], quantite, Tpoids[place], Tvolume[place], Tprix[place], Tpoids[place]*quantite, Tvolume[place]*quantite, Tprix[place]*quantite, cagnotteA);
    }
    printf("%.2f", prixMax);
    printf("\nPrix total à payer:\t%.2f euros\n", *prixTT);
    if (prixMax!=-1) {
        if (prixMax-(*prixTT)<0){
            printf("Attention dépassement de la limite de budget de ");
            printf("%.2f\n", (*prixTT)-prixMax);
        } else printf("Budget restant: %.2f\n", prixMax-(*prixTT));
    }
    printf("Cagnotte totale:\t%.2f euros\n", cagnotte);
    printf("\nVolume utilisé\t: %.2f litres\n", volTT);
    printf("Volume restant\t: ");
    if (volmax-volTT < 0) printf("Attention dépassement du volume autorisée de ");
    printf("%.2f litres\n", volmax-volTT);
    printf("\nCharge Actuelle\t: %.2f kg\n", chargeTT);
    printf("Charge restante\t: ");
    if (poidmax-chargeTT < 0) printf("Attention dépassement de la charge autorisée de ");
    printf("%.2f kg\n", poidmax-chargeTT);

    *prixTT=prixC;
    return cagnotte;
}

//demander caractéristique client (poids, prix, volume)
//demander action client (ajout, supretion, modification, rénitialisation,...)
//utilisation cagnotte entiérement ou partiellement
//mise a jour cagnotte (10%)
//Ajouter liite budget 
float Client(int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int tailleMax, int Ttaille, float cagnotte){
    int pRef[tailleMax], pQuantite[tailleMax], ptaille=0, action=0;
    float volMax, poidMax, cagnotteTT, nCagnotte, prixMax, prixTT=0;
    char choix;
    printf("===========================================================\n");
    printf("||Bienvenue\n");
    printf("===========================================================\n");
    printf("Veuillez définir la charge max de votre véhicule (kg): ");
    scanf("%f", &poidMax);
    printf("Veuillez définir le volume max de votre véhicule (L): ");
    scanf("%f", &volMax);
    printf("Voulez vous définir une limite budgétaire ? (y/n)\n");
    scanf("%*c%c", &choix);
    while (choix!='y' && choix!='Y' && choix!='n' && choix!='N')
    {
        printf("Attention : réponse non conforme\n");
        printf("Voulez vous définir une limite budgétaire ? (y/n)\n");
        scanf("%*c%c", &choix);
    }
    if (choix=='y' || choix=='Y'){
        printf("Veillez définir une limitation: ");
        scanf("%f", &prixMax);
    } else if (choix=='n' || choix=='N') prixMax=-1;
    while (action!=-1)
    {
        printf("\n\n===========================================================\n");
        printf("||Si vous voulez arréter là tapez -1\n||Si vous voulez ajouter au panier tapez 0\n||Si vous voulez payer tapez 1\n||Si vous voulez modifier un article taper 2\n||Si vous voulez suprimer un article tapez 3\n||Si vous voulez rénitialiser le panier tapez 4\n");
        scanf("%d", &action);
        if (action!=-1){
            if (action==0){
                int ref, trouve, place, quantite;
                printf("\n\nReference article: ");
                scanf("%d", &ref);
                place = frecherche(Tref, ref, Ttaille, &trouve);
                while (trouve!=1)
                {
                    printf("L'artile %d n'existe pas\n", ref);
                    printf("Veuillez réessayer: ");
                    scanf("%d", &ref);
                    place = frecherche(Tref, ref, Ttaille, &trouve);
                }
                place = frecherche(pRef, ref, ptaille, &trouve);
                if (trouve == 0){
                    printf("Quantité prise: ");
                    scanf("%d", &quantite);
                    pRef[ptaille] = ref;
                    pQuantite[ptaille] = quantite;
                    ptaille+=1;
                }else printf("L'article %d déjà present dans votre panier \n", ref);
            }
            else if (action==1) {
                if (prixMax<prixTT) {
                    printf("\n\nAttention votre panier dépasse de %.2f €", (prixMax-prixTT)*-1);
                    printf("Continuer quand même tapez 1\n");
                    printf("Prendre depuis la cagnotte tapez 2");
                    printf("Enlever des articles 3");
                }
            }
            else if (action==2) {
                int ref, trouve, place, quantite;
                printf("\n\nReference article: ");
                scanf("%d", &ref);
                place = frecherche(pRef, ref, ptaille, &trouve);
                while (trouve!=1)
                {
                    printf("Vous n'avez pas l'artile %d dans votre panier\n", ref);
                    printf("Veuillez réessayer: ");
                    scanf("%d", &ref);
                    place = frecherche(pRef, ref, ptaille, &trouve);
                }
                printf("Nouvelle quantité voulu: ");
                scanf("%d", &quantite);
                while (quantite<=0)
                {
                    printf("La quantité ne peut pas etre inférieur ou égale à 0\n");
                    printf("Veuillez réessayer: ");
                    scanf("%d", &quantite);
                }
                pQuantite[place] = quantite;
            }
            else if (action == 3) {
                int ref, trouve, place, quantite;
                printf("\n\nReference article: ");
                scanf("%d", &ref);
                place = frecherche(pRef, ref, ptaille, &trouve);
                while (trouve!=1)
                {
                    printf("Vous n'avez pas l'artile %d dans votre panier\n", ref);
                    printf("Veuillez réessayer: ");
                    scanf("%d", &ref);
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
                scanf("%*c%c", &choix);
                if (choix=='y' || choix=='Y') ptaille = 0;
            }
            printf("%.2f\n", prixMax);
            nCagnotte = afficheRecap(pRef, pQuantite, ptaille, Tref, Tpoids, Tvolume, Tprix, Ttaille, cagnotte, volMax, poidMax, prixMax, &prixTT);
        }
    }
    return nCagnotte;
}
void administrateur(int numClient[], float cagnotte[], int suspendue[], int ref[], float volume[], float prix[], float poids[], int tp, int tl)
{
    int choix,choixa, refa, refc, choixc, id, trouve,num, modifa, modifc, nvref,erreur;
    float nvvol,nvpo,nvpr;
    printf("===========================================================\n");
    printf("|| Bienvenue sur l'interface administrative du magasin\n");
    printf("===========================================================\n");

    
    while(choix!=-1)
    {
        printf("===========================================================\n");
        printf("||Voulez vous\n ||modifier un article (tapez 0)\n ||modifier une carte (tapez 1)\n ||si vous voulez afficher un client en particulier tapez 2 ou 3 pour un article\n");
        printf("===========================================================\n");
        scanf("%d",&choix);
        if (choix==0)
        { 
            printf("===========================================================\n");
            printf("||si vous voulez modifier un article tapez 0\n ||si vous voulez supprimer un article tapez 1\n ||si vous voulez en ajouter un faites le 2\n ||si vous voulez modifier la reference faites le 3 \n");
            printf("===========================================================\n");
            scanf("%d",&choixa);
            if (choixa==0)
            {

                printf("Quel article voulez vous modifier ?");
                scanf("%d", &id);
                refa=frecherche (ref,id , tl, &trouve);
                while (trouve==0 || num <0)
                {
                    printf("La reference artcile est inexistante ou incorrect veuillez re saisir la reference :\n");
                    scanf("%d",&num);
                    id = frecherche(ref,num,tl,&trouve);
                }
                printf("voulez vous modifier, le volume (0), le prix (1), le poids(2) ");
                scanf("%d",&modifa);


                if (modifa==0)
                {
                    printf("Donnez le nouveau volume de l'article");
                    scanf("%f",&nvvol);
                    volume[id]==nvvol;
                }
                if (modifa==1)
                {
                    printf("Donnez le nouveau prix de l'article");
                    scanf("%f",&nvpr);
                    prix[id]==nvpr;
                }
                if (modifa==2)
                {
                    printf("Donnez le nouveau poids de l'article");
                    scanf("%f",&nvpo);
                    poids[id]==nvpo;
                }
                if (modifa==3)
                {
                    printf("Donnez la nouvelle référence de l'article l'article");
                    scanf("%d",&nvref);
                    numClient[id]==nvref;
                }
                
                
            }   


        

            
            if (choixa==1)
            {
                erreur=DelArticle (ref,poids ,volume , prix,  &tl, tp);
                if (erreur==-1)printf("vous ne pouvez pas supprimer, le tableau est vide\n");
            }
            if (choixa==2)
            {
                erreur=AddArticle(ref,poids,volume,prix,&tl, tp);
                if (erreur==-1) printf("tableau trop petit\n");
            }
        }
        if (choix == 1)
        {
            printf("si vous voulez modifier le statut d'une carte tapez 0, si vous voulez creer une carte tapez 1, si vous voulez supprimer une carte faites le 2");
            scanf("%d",&choixc);
            if (choixc==0)
            {
                printf("Quel carte voulez vous suspendre");
                scanf("%d",&num);
                id=frecherche(numClient,num,tl,&trouve);
                suspendue[id]=1;
                printf("voulez vous à présent créer une nouvel carte pour se client (si oui tapez 0 si non tapez 1)\n");
                scanf("%d",&choixc);
            }
            if (choixc==1)
            {
                erreur=AddClient(numClient,cagnotte,suspendue,&tl,tp);
                if (erreur=-1)
                    printf("tableau trop petit\n");
            }
            if (choixc==2)
            {
                erreur=DelClient(numClient, cagnotte,suspendue, &tl, tp);
                if (erreur=-1) printf("vous ne pouvez pas supprimer, le tableau est vide\n");
            }
        }
        if (choix == 2)
            ShowClientPrecis(numClient, cagnotte, suspendue,tl);
        if (choix == 3)
            ShowArticlePrecis(ref,poids,volume,prix,tl);


    }



}

//Faire fonction Ajouts article (Enzo)
//Faire Fonction ShowArticle (Enzo)
//Finir le Menu (Maeva) 

//Faire fonction qui avec (s) ecris dans le cvs les nouveaux tableaux , et avec (e) quite et save (Samuel)


void Menu(void)
{
    int admin=777, id, cadmin=0, tp=200, tl;
    int i;
    int numClient[200],  suspendue[200];
    float cagnotte[200];
    int  ref[100] ;
    float volume[100] ;
    float poids[100] , prix[100] ;
    int tl1 ;
    tl1= loadArticle(ref,poids,volume,prix,tp);
    tl = loadClient(numClient, cagnotte, suspendue, tp);
    printf("Bienvenue  sur l'application de BricoConstruction!\nRentrez votre identifiant\n");
    scanf("%d",&id);
    if (id==admin)
    {
        administrateur(numClient, cagnotte, suspendue, ref, volume, prix, poids, tp,  tl);

    }
    
    if (id!=admin)
    {
        for (i=0; i<=tp; i++)
        {
            if (id==numClient[i])
                if (suspendue[i]==0)
                    Client(ref, poids, volume,  prix,tp, *volume, cagnotte[i]);
                else 
                    printf("Cette carte a été suspendue. Veuillez contacter l'assistance.");
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
<<<<<<< HEAD
    //Client();
    tl1= loadArticle(ref,poids,volume,prix,tp);
    DelArticle(ref,poids,volume,prix,&tl1,100);
    ShowArticle(ref,poids,volume,prix,tl1);
    Client(ref, poids, volume, prix, tp, tl1, 42, 0);
        ShowClient(numClient,cagnotte,suspendue,tl);
    ShowArticle(ref,poids,volume,prix,tl1);
    */
=======
    Menu();
    tl1= loadArticle(ref,poids,volume,prix,tp);
    DelArticle(ref,poids,volume,prix,&tl1,100);
    ShowArticle(ref,poids,volume,prix,tl1);
    Client(ref, poids, volume, prix, tp, tl1, 0);
>>>>>>> 8cce7d8e6b86c4fa971c0c5160dafe5262ed676f
}