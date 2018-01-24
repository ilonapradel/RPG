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

        if (persoActif->estVivant()) //si le personnage choisit est vivant (� terme, il faudra choisir parmi les personnages vivants)
        {
            //On choisit l'action � effectuer
            int action;
            cout << "Que voulez-vous faire ?" << endl;
            cout << "0 : Attaquer" << endl;
            cout << "1 : Boire une potion de vie" << endl;
            cout << "2 : Changer d'arme" << endl;
            if (persoActif->getClasse()=="Magicien") //si c'est un magicien, on a des fonctionnalit�s suppl�mentaires
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
                //on r�cup�re la cible
                int cible;
                cin >> cible;
                persoActif->attaquer(*listePerso[cible]); // on effectue l'action
                break;
            case 1:
                //on se soigne
                persoActif->boirePotionDeVie(10);
                break;
            case 2: //on change d'arme (param�tres pr�vus mais pour le moment non impl�ment�s)
                persoActif->changerArme("Grosse Hache", 50);
                break;
            case 3: // m�me principe que pour attaquer
                cout << "Qui voulez-vous soigner ?" << endl;
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                cin >> cible;
                persoActif->soigner(*listePerso[cible], 20); //en param�tres : la cible et le nombre de points soign�s (prise de param�tres non impl�ment�s mais pr�vus)
                break;
            case 4: // m�me principe que plus haut
                cout << "Sur qui voulez-vous jeter une boule de feu ?" << endl;
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                cin >> cible;
                persoActif->bouleDeFeu(*listePerso[cible], 20, 20); //en param�tres : la cible, la dur�e du dot et le cout en mana (prise de param�tres non impl�ment�s mais pr�vus)
            case 5: //idem
                cout << "Qui voulez-vous geler ?" << endl;
                for (int i = 0 ; i < listePerso.size() ; i++)
                {
                    cout << i << " : " << listePerso[i]->getNom() << endl;
                }
                cin >> cible;
                persoActif->gel(*listePerso[cible], 20); // en param�tres : cible, cout en mana (m�me remarque)
                break;
            default: //Si on r�pond autre chose que ce qui est propos�, on ne fait rien.
                cout << "Ne rien faire" << endl;
            }
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
