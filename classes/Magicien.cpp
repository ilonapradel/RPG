#include "Magicien.h"
#include <iostream>


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

//getter
string Magicien::getClasse() const //renvoie la classe
{
    return "Magicien";
}

//Destructeur
Magicien::~Magicien(){}
