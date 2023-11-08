#include "main.h"


/**
*\file fonction.c
*\brief Fichier contenant toute les fonctions applications 
*\author Enzo Gubbiotti , Maeva Colle ,Samuel Pinto 
*\date 2023
*Application qui permet de gérer une base de données peu complexe avec une interface client 
*et une interface administrateur. 
*/


/**
* \brief Fonction qui charge le fichier contenant les informations des clients dans des tableaux 
* \param[in,out] numClient tableau des clients 
* \param[in,out] cagnotte tableau des cagnottes 
* \param[in,out] suspendue tableau de l'etat de la carte (O/1)
* \param[in] taille taille physique du tableau qui stock les données
* \author Samuel Pinto
* \return la taille logique de tableau ou erreur si il y a  
*/
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
/**
* \brief Fonction qui charge le fichier contenant les informations des articles dans des tableaux 
* \param[in,out] id tableau des articles 
* \param[in,out] poids tableau des poids 
* \param[in,out] volume tableau des volumes des articles 
* \param[in,out] prix tableau des prix des articles 
* \author Samuel Pinto
* \return la taille logique des tableau ou erreur si il y a  
*/
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

/**
* \brief Fonction qui recherche une valeur dans un tableau donné 
* \param[in] tab tableau dans lequel on recherche 
* \param[in] val valeur à rechercher dans le tableau 
* \param[in] taille contient la taille logique du tableau 
* \param[out] trouve si 0 alors valeur pas trouvé / si 1 alors valeur trouvé  
* \author Enzo Gubbiotti
* \return renvoi l'indice de la valeur dans le tableau si elle est trouvé ou renvoi l'indice de là ou elle doit être inseré si elle n'as pas été trouvé
*/
// recherche si la valeur (numéro client ou reference objet) est déjà dans le fichier
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

/**
* \brief Fonctions qui sert a l'administrateur pour ajouter des clients aux tableaux 
* \param[in,out] numClient tableau des clients 
* \param[in,out] cagnotte tableau des cagnottes 
* \param[in,out] suspendue tableau de l'etat de la carte (O/1)
* \param[in,out] taille taille logique des tableaux qui augmente de 1 
* \param[in] tailleMax taille physique des tableaux 
* \author Enzo gubbiotti
* \return 1 si tout c'est bien passé sinon -1 
*/
int AddClient (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ){
    int num,j ;h
    int trouve;
    if (*taille+1==tailleMax)
        return -1; //Erreur: tableau trop petit
    printf("Quelle sera le numéro du client à ajouter : \n");
    scanf("%d",&num);

    int ind =frecherche(numClient,num,*taille,&trouve);
    while(trouve==1 || num<0) {
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
/**
* \brief Fonction qui sert a l'administrateur pour ajouter des articles aux tableaux 
* \param[in,out] ref tableau des références 
* \param[in,out] poids tableau des poids 
* \param[in,out] volume tableau des volumes des articles 
* \param[in,out] prix tableau des prix des articles
* \param [out] taille taille logique des tableaux 
* \param[in] tailleMax taille physique des tableaux   
* \author Enzo gubbiotti
* \return 1 si tout c'est bien passé sinon -1 
*/
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
/**
* \brief Fonction qui affiche tout les clients des tableaux 
* \param[in] numClient tableau des clients 
* \param[in] cagnotte tableau des cagnottes 
* \param[in] suspendue tableau des etats de carte 
* \param[in] taille taille logique des tableaux 
* \author Enzo gubbiotti 
*/
void ShowClient (int numClient[], float cagnotte[], int suspendu[], int taille) {
        int i ;
        printf("Num\tcagnotte\tsuspendue\t\n");
        for (i=0;i<taille;i++){
            printf("%d\t%.2f\t\t%d\t\n",numClient[i],cagnotte[i],suspendu[i]);
        }

}
/**
* \brief Fonction qui affiche un clients précis 
* \param[in] numClient tableau des clients 
* \param[in] cagnotte tableau des cagnottes 
* \param[in] suspendue tableau des etats de carte 
* \param[in] taille taille logique des tableaux 
* \author Maeva Colle  
*/
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
/**
* \brief Affiche tout les articles des tables 
* \param[in] ref tableau des références 
* \param[in] poids tableaux des poids 
* \param[in] volume tableau des volumes 
* \param[in] prix tableau des prix 
* \param[in] taille taille logique des tableaux 
* \author Enzo Gubbiotti 
*/
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
/**
* \brief Fonction qui permet a l'administrateur de supprimer un client 
* \param[in,out] numClient tableau des clients 
* \param[in,out] cagnotte tableau des cagnottes 
* \param[in,out] suspendue tableau de l'etat de la carte (O/1)
* \param[in,out] taille taille logique des tableaux qui diminue  de 1
* \param [in] tailleMax taille physique des tableaux 
* \author Enzo Gubbiotti , Samuel Pinto 
* \return renvoi 1 si tout s'est bien passé sinon -1 
*/
>>>>>>> 12c1190842d0f480e2474cd270598c8ae699fff1
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

/**
* \brief Foncion qui permet a l'administrateur de supprimé un article 
* \param[in,out] numClient tableau des clients 
* \param[in,out] cagnotte tableau des cagnottes 
* \param[in,out] suspendue tableau de l'etat de la carte (O/1)
* \param[in,out] taille taille logique des tableaux qui diminue de 1 
* \param[in] tailleMax taille physique des tableaux 
* \author Enzo gubbiotti
* \return 1 si tout c'est bien passé sinon -1 
*/
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
    return 1;

}



/**
* \brief Fonction qui prend les tableaux des données des clients et ecris ces données dans le fichier csv 
* \param[in] Tclient tableau contenant les référence des clients 
* \param[in] Tcagnotte tableau contenant les cagnottes des clients 
* \param[in] Tsuspendue tableau qui contient l'etat de la carte des clients (0/1)
* \param[in] taille taille logique des tableaux
* \author Samuel Pinto 
*/
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

//a ajouter cagnotte (oui c'est la flemme)
float afficheRecap(int pRef[], int pQuantite[], int ptaille, int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int Ttaille, float cagnotte, float volmax, float poidmax){
    int place, trouve, quantite;
    float volTT=0, chargeTT=0, prixTT=0, cagnotteA=0;
    printf("\n\n===========================================================\n");
    printf("Réf\tQté\tPoids\tVol\tPrixU\tPoidsTot\tVolTot\tPrixTT\tCagnotte\n");
    for (int i=0; i<ptaille; i++){
        quantite = pQuantite[i];
        place = frecherche(Tref, pRef[i], Ttaille, &trouve);
        prixTT += Tprix[place]*quantite;
        cagnotteA = Tprix[place]*quantite/10.0;
        cagnotte += cagnotteA;
        volTT += Tvolume[place]*quantite;
        chargeTT += Tpoids[place]*quantite;
        printf("%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\t%.2f\t%.2f\n", pRef[i], quantite, Tpoids[place], Tvolume[place], Tprix[place], Tpoids[place]*quantite, Tvolume[place]*quantite, Tprix[place]*quantite, cagnotteA);
    }
    printf("\nPrix total à payer:\t%.2f euros\n", prixTT);
    printf("Cagnotte totale:\t%.2f euros\n", cagnotte);
    printf("\nVolume utilisé\t: %.2f litres\n", volTT);
    printf("Volume restant\t:");
    if (volmax-volTT < 0) printf("Attention dépassement du volume autorisée de ");
    printf("%.2f litres\n", volmax-volTT);
    printf("\nCharge Actuelle\t: %.2f kg\n", chargeTT);
    printf("Charge restante: ");
    if (poidmax-chargeTT < 0) printf("Attention dépassement de la charge autorisée de ");
    printf("%.2f kg\n", poidmax-chargeTT);

    return cagnotte;
}

//demander caractéristique client (poids, prix, volume)
//demander action client (ajout, supretion, modification, rénitialisation,...)
//utilisation cagnotte entiérement ou partiellement
//mise a jour cagnotte (10%)
//Ajouter liite budget 
float Client(int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int tailleMax, int Ttaille, int id, float cagnotte){
    int pRef[tailleMax], pQuantite[tailleMax], ptaille=0, action;
    float volMax, poidMax, cagnotteTT, nCagnotte;
    printf("===========================================================\n");
    printf("||Bienvenue Monsieur \n");
    printf("===========================================================\n");
    printf("Veuillez définir la charge max de votre véhicule (kg): ");
    scanf("%f", &poidMax);
    printf("Veuillez définir le volume max de votre véhicule (L): ");
    scanf("%f", &volMax);
    while (action!=-1)
    {
        printf("\n\n===========================================================\n");
        printf("||Si vous voulez arréter là tapez -1\n||Si vous voulez ajouter au panier tapez 0\n||Si vous voulez modifier un article taper 1\n||Si vous voulez suprimer un article tapez 2\n||Si vous voulez rénitialiser le panier tapez 3\n");
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
            else if (action == 2) {
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
            else if (action == 3){
                char choix;
                printf("\nEtes vous sur de vouloir remettre à 0 votre panier ? (y/n)\n");
                scanf("%*c%c", &choix);
                if (choix=='y' || choix=='Y') ptaille = 0;
            }
            nCagnotte = afficheRecap(pRef, pQuantite, ptaille, Tref, Tpoids, Tvolume, Tprix, Ttaille, cagnotte, volMax, poidMax);
        }
    }
    return nCagnotte;
}
int administrateur(int numClient[], float cagnotte[], int suspendue[], int ref[], float volume[], float prix[], float poids[], int tp, int tl)
{
    int choix,choixa, refa, refc, choixc, id, trouve,num, modifa, modifc, nvref,erreur;
    float nvvol,nvpo,nvpr;
    printf("===========================================================\n");
    printf("|| Bienvenue sur l'interface administrative du magasin\n");
    printf("===========================================================\n");

    
    while(choix!=-1)
    {
        printf("Voulez vous modifier un article (tapez 0) modifier une carte (tapez 1) si vous voulez afficher un client en particulier tapez 2 ou 3 pour un article");
        scanf("%d",&choix);
        if (choix==0)
        { 
            printf("si vous voulez modifier un article tapez 0 si vous voulez supprimer un article tapez 1 si vous voulez en ajouter un faites le 2 et si vous voulez modifier la reference faites le 3 \n");
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



return -1;



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
    printf("%d\n",tl1);
    tl = loadClient(numClient, cagnotte, suspendue, tp);
    //saveClient(numClient,cagnotte,suspendue,tp,tl); a changer
    ShowClient(numClient,cagnotte,suspendue,tl);
    ShowArticle(ref,poids,volume,prix,tl1);
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
                    Client(ref, poids, volume,  prix,tp, *volume, numClient[i], cagnotte[i]);
                else 
                    printf("Cette carte a été suspendue. Veuillez contacter l'assistance.");
            else
                printf("Cette carte a été suspendue. Veuillez contacter l'assistance.");
        }
                    
                
    }

}

void test(void)
{
    int numClient[200],  suspendue[200], tp=200;
    float cagnotte[200];
    int  ref[100] ;
    float volume[100] ;
    float poids[100] , prix[100] ;
    int tl1 ;
    Menu();
    tl1= loadArticle(ref,poids,volume,prix,tp);
    DelArticle(ref,poids,volume,prix,&tl1,100);
    ShowArticle(ref,poids,volume,prix,tl1);
    Client(ref, poids, volume, prix, tp, tl1, 42, 0);
}