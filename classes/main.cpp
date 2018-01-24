#include <iostream>
#include <string>
#include "Personnage.h"
#include "Magicien.h"
#include "Guerrier.h"
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//Les accents passent pour le moment mal puisque le jeu se fait dans la console mais l'interface Qt est en cours de d�veloppement

int main()
{
    vector<Personnage*> listePerso; //Liste contenant l'ensemble des personnages cr��s
    bool jeu=true;

    //cr�er un pointeur qui m�ne sur le personnage actif
    Personnage *persoActif(0);

     srand(time(0)); //random

    //choix du nombre de personnages � cr�er
    int nbP;
    cout << "Combien voulez-vous cr�er de personnages ?" << endl;
    cin >> nbP;

    //cr�e le nombre de pesonnages demand�
    for (int i(0); i<nbP; i++)
    {
        string nom;
        int res;
        cout << "Cr�ez votre personnage !" << endl;
        cout << "Est-ce un guerrier (0) ou un magicien (1)?" << endl;
        cin >> res;
        cout << "Comment voulez-vous l'appeler ?" << endl;
        cin >> nom;
        if (res==0){
            listePerso.push_back(new Guerrier(nom)); //ajoute le nouveau personnage � la liste
        } else {
            listePerso.push_back(new Magicien(nom));
        }
        listePerso[i]->afficherEtat(); //affiche le personnage cr��
    }

    do {
        //Prends un nombre random pour choisir qui joue
        int nbRandom;
        nbRandom=rand()%listePerso.size();
        //Si le personnage est gel�, il ne peut pas jouer
        if (listePerso[nbRandom]->getGel()){
            cout << listePerso[nbRandom]->getNom() << " ne peut pas jouer car il �tait gel� !" << endl;
            //on choisit donc un nouveau nombre random pour jouer
            nbRandom=rand()%listePerso.size();
        }

        //On d�g�le tous les personnages (on est gel� que pendant 1 tour)
        cout << "Les personnages gel�s sont maintenant d�gel�s ! " << endl << endl;
        for (int i(0); i<listePerso.size(); i++)
        {
            listePerso[i]->setGel(false);
        }

        //On annonce qui joue
        persoActif=listePerso[nbRandom];
        cout << "C'est au tour de " << persoActif->getNom() << endl;

        if (persoActif->estVivant()) //si le personnage choisi est vivant (� terme, il faudra choisir parmi les personnages vivants)
        {
            //On choisit l'action � effectuer

            //on affiche les possibilit�s d'actions � effectuer
            persoActif->afficherPossibilites();
            //on r�cup�re la r�ponse du joueur
            int action;
            cin >> action;

            //on effectue l'action
            persoActif->faireAction(listePerso, action);
        } else {
            //il manque une boucle pour v�rifier que tous les persos ne sont pas morts, sinon fin du jeu (en cours de r�flexion)
            cout << persoActif->getNom() << " ne peut pas jouer, il est mort ! Quelqu'un doit le ressusciter." << endl;
        }

        //On v�rifie que le joueur veut continuer de jouer
        char ans;
        cout << "Voulez-vous continuer � jouer ? (o/n)" << endl;
        cin >> ans;
        if (ans=='n') // s'il r�pond non, on arr�te. S'il r�pond oui ou autre chose on continue
        {
            jeu=false;
            cout << "A la prochaine !" << endl;
        }
    } while (jeu);

    //Destruction des pointeurs pour l'allocation m�moire
    for (int i(0); i<listePerso.size(); i++)
    {
        persoActif=0;
        delete listePerso[i];
        listePerso[i]=0;
    }


    return 0;
}
