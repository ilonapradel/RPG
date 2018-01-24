#include "Magicien.h"
#include <iostream>
#include <vector>

using namespace std;
//Constructeurs
Magicien::Magicien(string nom) : Personnage(nom), m_mana(100){}

//Méthodes
void Magicien::bouleDeFeu(Personnage &cible, int duree, int coutMana) //lance une boule de feu sur la cible
{
    m_mana-=coutMana; //diminue le coût en mana
    if (m_mana<0) //on ne peut pas avoir une barre de mana négative
    {
        m_mana=0; //on remet la valeur à 0 et on affiche
        cout << "Vous n'avez pas assez de mana pour faire cette action !" << endl;
    } else { //si on a assez de mana on effectue l'action
        cout << getNom() << " lance une boule de feu sur " << cible.getNom() << endl;
        cout << cible.getNom() << " brûle !" << endl;
        for (int i(0); i<duree; i++) //On fait des dégâts sur la durée
        {
            cible.recevoirDegats(1);
        }
    }
}

void Magicien::gel(Personnage &cible, int coutMana) //on gèle la cible
{
    m_mana-=coutMana;
    if (m_mana<0) //on ne peut pas avoir une barre de mana négative
    {
        m_mana=0; //on remet la valeur à 0 et on affiche
        cout << "Vous n'avez pas assez de mana pour faire cette action !" << endl;
    } else { //sinon on effectue l'action
        cout << getNom() << " gèle " << cible.getNom() << endl;
        cible.setGel(true); //on incapacite la cible
    }
}

void Magicien::ressusciter(Personnage &cible){ //on ressuscite la cible
    if (cible.getVie()==0)//si la cible est morte
    {
        cible.setVie(100); //on remet la barre de vie au maximum
        cout << getNom() << " a ressuscité " << cible.getNom() << endl;
        cout << "Votre bonté vous perdra." << endl;
    } else { //sinon on ne peut pas la ressusciter
        cout << cible.getNom() << " n'est pas mort !" << endl;
    }
}

void Magicien::soigner(Personnage &cible, int points) //soigne un autre personnage
{
    if (cible.getVie()==0) //si le personnage est mort, on ne peut pas le soigner
    {
        cout << "Vous ne pouvez pas soigner " << cible.getNom() << " il est mort !" << endl;
        cout << "Voulez-vous le ressusciter ? (o/n)" << endl; //on propose de le ressusciter
        char res;
        cin >> res;
        if (res='o'){
            ressusciter(cible); //si on répond oui, on le ressuscite
        } else {
            cout << "Vous n'êtes pas très gentils :(" << endl;
        }
    } else if (m_vie >= 100) { // si le personnage a déjà 100 points de vie, on ne peut pas le soigner
        cout << "Vous ne pouvez pas soigner " << cible.getNom() << " il est full life !" << endl;
    }else { //sinon on le soigne
        cible.setVie(points);
        if (m_vie >=100)
        {
            m_vie=100; //on ne peut pas avoir plus de 100 points de vie
        }
        cout << cible.getNom() << "a récupéré " << points << "points de vie." << endl;
        cout << "Il a maintenant " << cible.getVie() << " points de vie." << endl;
    }
}

void Magicien::afficherPossibilites() const
{
    Personnage::afficherPossibilites(); //on rappelle la méthode initiale de personnage pour les actions communes à tout le monde
    cout << "3 : Soigner" << endl;
    cout << "4 : Lancer une boule de feu" << endl;
    cout << "5 : Geler l'adversaire"<< endl;
}

void Magicien::faireAction(vector<Personnage*> listePerso, int numAction)
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
            //on récupère la cible
            int cible;
            cin >> cible;
            this->attaquer(*listePerso[cible]); // on effectue l'action
            break;
        case 1:
            //on se soigne
            boirePotionDeVie(10);
            break;
        case 2: //on change d'arme (paramètres prévus mais pour le moment non implémentés)
            changerArme("Grosse Hache", 50);
            break;
        case 3: // même principe que pour attaquer
            cout << "Qui voulez-vous soigner ?" << endl;
            for (int i = 0 ; i < listePerso.size() ; i++)
            {
                cout << i << " : " << listePerso[i]->getNom() << endl;
            }
            cin >> cible;
            soigner(*listePerso[cible], 20); //en paramètres : la cible et le nombre de points soignés (prise de paramètres non implémentés mais prévus)
            break;
        case 4: // même principe que plus haut
            cout << "Sur qui voulez-vous jeter une boule de feu ?" << endl;
            for (int i = 0 ; i < listePerso.size() ; i++)
            {
                cout << i << " : " << listePerso[i]->getNom() << endl;
            }
            cin >> cible;
            bouleDeFeu(*listePerso[cible], 20, 20); //en paramètres : la cible, la durée du dot et le cout en mana (prise de paramètres non implémentés mais prévus)
        case 5: //idem
            cout << "Qui voulez-vous geler ?" << endl;
            for (int i = 0 ; i < listePerso.size() ; i++)
            {
                cout << i << " : " << listePerso[i]->getNom() << endl;
            }
            cin >> cible;
            gel(*listePerso[cible], 20); // en paramètres : cible, cout en mana (même remarque)
            break;
        default: //Si on répond autre chose que ce qui est proposé, on ne fait rien.
            cout << "Ne rien faire" << endl;
    }
}

//getter
string Magicien::getClasse() const //renvoie la classe
{
    return "Magicien";
}

//Destructeur
Magicien::~Magicien(){}
