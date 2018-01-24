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

        if (persoActif->estVivant()) //si le personnage choisit est vivant (à terme, il faudra choisir parmi les personnages vivants)
        {
            //On choisit l'action à effectuer
            int action;
            cout << "Que voulez-vous faire ?" << endl;
            cout << "0 : Attaquer" << endl;
            cout << "1 : Boire une potion de vie" << endl;
            cout << "2 : Changer d'arme" << endl;
            if (persoActif->getClasse()=="Magicien") //si c'est un magicien, on a des fonctionnalités supplémentaires
            {
                cout << "3 : Soigner" << endl;
                cout << "4 : Lancer une boule de feu" << endl;
                cout << "5 : Geler l'adversaire" << endl;
            }
            cin >> action;

            switch (action)
            {
            case 0: //Si on veut attaquer
                cout << "Qui voulez-vous attaquer ?" << endl;
                //On affiche la liste des persos qu'on peut attaquer
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                //on récupère la cible
                int cible;
                cin >> cible;
                persoActif->attaquer(*listePerso[cible]); // on effectue l'action
                break;
            case 1:
                //on se soigne
                persoActif->boirePotionDeVie(10);
                break;
            case 2: //on change d'arme (paramètres prévus mais pour le moment non implémentés)
                persoActif->changerArme("Grosse Hache", 50);
                break;
            case 3: // même principe que pour attaquer
                cout << "Qui voulez-vous soigner ?" << endl;
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                cin >> cible;
                persoActif->soigner(*listePerso[cible], 20); //en paramètres : la cible et le nombre de points soignés (prise de paramètres non implémentés mais prévus)
                break;
            case 4: // même principe que plus haut
                cout << "Sur qui voulez-vous jeter une boule de feu ?" << endl;
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                cin >> cible;
                persoActif->bouleDeFeu(*listePerso[cible], 20, 20); //en paramètres : la cible, la durée du dot et le cout en mana (prise de paramètres non implémentés mais prévus)
            case 5: //idem
                cout << "Qui voulez-vous geler ?" << endl;
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                cin >> cible;
                persoActif->gel(*listePerso[cible], 20); // en paramètres : cible, cout en mana (même remarque)
                break;
            default: //Si on répond autre chose que ce qui est proposé, on ne fait rien.
                cout << "Ne rien faire" << endl;
            }
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
