#include <stdio.h>

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
int loadClient(int numClient[], float cagnotte[], int suspendu[], int taille);


/**
* \brief Fonction qui charge le fichier contenant les informations des articles dans des tableaux 
* \param[in,out] id tableau des articles 
* \param[in,out] poids tableau des poids 
* \param[in,out] volume tableau des volumes des articles 
* \param[in,out] prix tableau des prix des articles 
* \author Samuel Pinto
* \return la taille logique des tableau ou erreur si il y a  
*/
int loadArticle(int id[], float poid[], float volume[], float prix[], int tailleMax);

/**
* \brief Fonction qui recherche une valeur dans un tableau donné 
* \param[in] tab tableau dans lequel on recherche 
* \param[in] val valeur à rechercher dans le tableau 
* \param[in] taille contient la taille logique du tableau 
* \param[out] trouve si 0 alors valeur pas trouvé / si 1 alors valeur trouvé  
* \author Enzo Gubbiotti
* \return renvoi l'indice de la valeur dans le tableau si elle est trouvé ou renvoi l'indice de là ou elle doit être inseré si elle n'as pas été trouvé
*/
int frecherche (int tab[], int val , int taille, int *trouve);

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
int AddClient (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax );

/**
* \brief Fonctions qui sert a l'administrateur pour ajouter des clients aux tableaux avec une reference deja defini
* \param[in,out] numClient tableau des clients 
* \param[in,out] cagnotte tableau des cagnottes 
* \param[in,out] suspendue tableau de l'etat de la carte (O/1)
* \param[in,out] taille taille logique des tableaux qui augmente de 1 
* \param[in] tailleMax taille physique des tableaux 
* \param[in] references nouvelle reference a ajouter 
* \author Enzo gubbiotti
* \return 1 si tout c'est bien passé sinon -1 
*/
int AddNouvelleCarte (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax ,int reference);

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
int AddArticle(int ref[],float poids[] ,float volume[] ,float prix[] , int *taille, int tailleMax );

/**
* \brief Fonction qui affiche tout les clients des tableaux 
* \param[in] numClient tableau des clients 
* \param[in] cagnotte tableau des cagnottes 
* \param[in] suspendue tableau des etats de carte 
* \param[in] taille taille logique des tableaux 
* \author Enzo gubbiotti 
*/
void ShowClient (int numClient[], float cagnotte[], int suspendu[], int taille);

/**
* \brief Fonction qui affiche un clients précis 
* \param[in] numClient tableau des clients 
* \param[in] cagnotte tableau des cagnottes 
* \param[in] suspendue tableau des etats de carte 
* \param[in] taille taille logique des tableaux 
* \author Maeva Colle  
*/
void ShowClientPrecis (int numClient[], float cagnotte[], int suspendu[], int taille);

/**
* \brief Affiche tout les articles des tables 
* \param[in] ref tableau des références 
* \param[in] poids tableaux des poids 
* \param[in] volume tableau des volumes 
* \param[in] prix tableau des prix 
* \param[in] taille taille logique des tableaux 
* \author Enzo Gubbiotti 
*/
void ShowArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int taille );

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
int DelClient  (int numClient[], float cagnotte[], int suspendu[], int *taille, int tailleMax );

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
int DelArticle (int ref[],float poids[] ,float volume[] ,float prix[] , int *taille , int tailleMax );

/**
* \brief Fonction qui prend les tableaux des données des clients et ecris ces données dans le fichier csv 
* \param[in] Tclient tableau contenant les référence des clients 
* \param[in] Tcagnotte tableau contenant les cagnottes des clients 
* \param[in] Tsuspendue tableau qui contient l'etat de la carte des clients (0/1)
* \param[in] taille taille logique des tableaux
* \author Samuel Pinto 
*/
void saveClient(int Tclient[], float Tcagnotte[], int Tsuspendue[], int taille);

/**
* \brief Fonction qui prend les tableaux des données des Artciles et écris ces données dans le fichier csv 
* \param[in] Tref tableau des références des artciles 
* \param[in] Tpoids tableau des poids des articles 
* \param[in] Tvolume tableau des volumes des articles 
* \param[in] prix tableau des prix des articles 
* \param[in] taille taille logique des tableaux 
* \author Samuel Pinto 
*/
void saveArticle(int Tref[], float Tpoid[], float Tvolume[], float prix[], int taille);

/**
* \brief Fonction qui affiche le récapitulatif de la commande du client 
* \param[in] pRef tableau des references articles dans le panier du client 
* \param[in] pQuantite tableau des quantités des articles  dans le panier du client 
* \param[in] ptaille des tableaux des paniers 
* \param[in] Tref tableau des references des articles 
* \param[in] Tpoids tableau des poids des articles 
* \param[in] Tprix tableau des prix des articles 
* \param[in] Ttaille Taille des tableaux articles 
* \param[in] cagnotte Cagnotte du client 
* \param[in] volmax volume maximum du client 
* \param[in] poidsmax poids maximum du client  
* \param[in] prixMax prix maximum du client 
* \param[out] prixTT prix de la commande du client 
* \author Samuel Pinto
* \return La cagnotte Mise a jours  a la fonction Client()
*/
float afficheRecap(int pRef[], int pQuantite[], int ptaille, int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int Ttaille, float cagnotte, float volmax, float poidmax, float prixMax, float *prixTT);


/**
* \brief Fonction de l'interface client permet de gerer le cotés client de l'application
* \param[in] Tref tableau des references des articles 
* \param[in] Tpoids tableau des poids des articles 
* \param[in] Tvolume tableau des volumes artciles 
* \param[in] Tprix tableau des prix des articles 
* \param[in] tailleMax taille physique des tableaux 
* \param[in] Ttaille taille logique des tableaux 
* \param[in] cagnotte cagnotte du client 
* \author Samuel Pinto , Maeva Colle 
* \return La cagnotte Mise a jours a l'utilisateur
*/
float Client(int Tref[], float Tpoids[], float Tvolume[], float Tprix[], int tailleMax, int Ttaille, float cagnotte);
/**
* \brief
* \param[in] numClient tableau des numeros des clients 
* \param[in] cagnotte tableau des cagnottes des clients 
* \param[in,out] suspendue tableaux des etats de carte des clients 
* \param[in,out] ref tableau des references des articles 
* \param[in,out] volume tableau des volumes des articles 
* \param[in,out] prix tableau des prix des articles 
* \param[in,out] poids tableau des poids des articles 
* \param[in] tp taille phyisque des tableaux 
* \param[in] tl taille logique des tableaux 
* \author Maeva Colle 
*/

void administrateur(int numClient[], float cagnotte[], int suspendue[], int ref[], float volume[], float prix[], float poids[], int tp, int tl);

/**
* \brief Fonction qui mets ensemble tout les elements du menu 
* \author Maeva Colle 
*/
void Menu(void);


void test(void); 
