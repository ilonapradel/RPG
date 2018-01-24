#include "Guerrier.h"
#include <iostream>


using namespace std;

//Constructeur
Guerrier::Guerrier(string nom) : Personnage(nom){};

//M�thodes
void Guerrier::faireAction(vector<Personnage*> listePerso, int numAction)
{
    switch (numAction)
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
            this->attaquer(*listePerso[cible]); // on effectue l'action
            break;
        case 1:
            //on se soigne
            boirePotionDeVie(10);
            break;
        case 2: //on change d'arme (param�tres pr�vus mais pour le moment non impl�ment�s)
            changerArme("Grosse Hache", 50);
            break;
        default:
            cout << "Ne rien faire" << endl;
    }
}

//getter
string Guerrier::getClasse() const //renvoie la classe
{
    return "Guerrier";
}

//Destructeur
Guerrier::~Guerrier(){}
