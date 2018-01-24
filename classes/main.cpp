#include <iostream>
#include <string>
#include "Personnage.h"
#include "Magicien.h"
#include "Guerrier.h"
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//Les accents passent pour le moment mal puisque le jeu se fait dans la console mais l'interface Qt est en cours de développement

int main()
{
    vector<Personnage*> listePerso; //Liste contenant l'ensemble des personnages créés
    bool jeu=true;

    //créer un pointeur qui mène sur le personnage actif
    Personnage *persoActif(0);

     srand(time(0)); //random

    //choix du nombre de personnages à créer
    int nbP;
    cout << "Combien voulez-vous créer de personnages ?" << endl;
    cin >> nbP;

    //crée le nombre de pesonnages demandé
    for (int i(0); i<nbP; i++)
    {
        string nom;
        int res;
        cout << "Créez votre personnage !" << endl;
        cout << "Est-ce un guerrier (0) ou un magicien (1)?" << endl;
        cin >> res;
        cout << "Comment voulez-vous l'appeler ?" << endl;
        cin >> nom;
        if (res==0){
            listePerso.push_back(new Guerrier(nom)); //ajoute le nouveau personnage à la liste
        } else {
            listePerso.push_back(new Magicien(nom));
        }
        listePerso[i]->afficherEtat(); //affiche le personnage créé
    }

    do {
        //Prends un nombre random pour choisir qui joue
        int nbRandom;
        nbRandom=rand()%listePerso.size();
        //Si le personnage est gelé, il ne peut pas jouer
        if (listePerso[nbRandom]->getGel()){
            cout << listePerso[nbRandom]->getNom() << " ne peut pas jouer car il était gelé !" << endl;
            //on choisit donc un nouveau nombre random pour jouer
            nbRandom=rand()%listePerso.size();
        }

        //On dégèle tous les personnages (on est gelé que pendant 1 tour)
        cout << "Les personnages gelés sont maintenant dégelés ! " << endl << endl;
        for (int i(0); i<listePerso.size(); i++)
        {
            listePerso[i]->setGel(false);
        }

        //On annonce qui joue
        persoActif=listePerso[nbRandom];
        cout << "C'est au tour de " << persoActif->getNom() << endl;

        if (persoActif->estVivant()) //si le personnage choisi est vivant (à terme, il faudra choisir parmi les personnages vivants)
        {
            //On choisit l'action à effectuer

            //on affiche les possibilités d'actions à effectuer
            persoActif->afficherPossibilites();
            //on récupère la réponse du joueur
            int action;
            cin >> action;

            //on effectue l'action
            persoActif->faireAction(listePerso, action);
        } else {
            //il manque une boucle pour vérifier que tous les persos ne sont pas morts, sinon fin du jeu (en cours de réflexion)
            cout << persoActif->getNom() << " ne peut pas jouer, il est mort ! Quelqu'un doit le ressusciter." << endl;
        }

        //On vérifie que le joueur veut continuer de jouer
        char ans;
        cout << "Voulez-vous continuer à jouer ? (o/n)" << endl;
        cin >> ans;
        if (ans=='n') // s'il répond non, on arrête. S'il répond oui ou autre chose on continue
        {
            jeu=false;
            cout << "A la prochaine !" << endl;
        }
    } while (jeu);

    //Destruction des pointeurs pour l'allocation mémoire
    for (int i(0); i<listePerso.size(); i++)
    {
        persoActif=0;
        delete listePerso[i];
        listePerso[i]=0;
    }


    return 0;
}
