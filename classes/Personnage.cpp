#include "Personnage.h"
#include <iostream>
#include <vector>

using namespace std;
//Constructeurs         //on initialise m_gel � false pour que le personnage puisse jouer au premier tour
Personnage::Personnage(string nom) : m_vie(100), m_nom(nom), m_gel(false){
    m_arme = new Arme();
}

Personnage::Personnage(string nomArme, int degatsArme, string nom) : m_vie(100), m_arme(0), m_nom(nom),m_gel(false) {
    m_arme = new Arme(nomArme, degatsArme);
}
 //Constructeur de copie
 Personnage::Personnage(Personnage const& personnageACopier):m_vie(personnageACopier.m_vie),m_arme(0), m_gel(false) {
    m_arme = new Arme(*(personnageACopier.m_arme));
 }

//Destructeur
Personnage::~Personnage(){
    delete m_arme;
}

//M�thodes

void Personnage::afficherEtat() const //affiche les caract�ristiques actuelles du personnage
{
    cout << "Vous �tes un " << getClasse() << endl;
    cout << "Vous vous appelez " << m_nom << endl;
    cout << "Vous avez " << m_vie << " points de vie. " << endl;
    cout << "Vous �tes �quip�s de " ;
    m_arme->afficher();
    cout << endl;
}

void Personnage::recevoirDegats(int nbDegats) //pour recevoir les d�g�ts inflig�s
{
    m_vie-=nbDegats; //on change le nombre de points de vie
    if (m_vie<=0){ //on ne peut pas avoir une barre de vie n�gative
        m_vie=0; //on la met donc � 0 = on est mort
        cout << getNom() << " est mort :( " << endl;
    }
}

void Personnage::attaquer(Personnage &cible) //on attaque une autre cible
{
    cible.recevoirDegats(m_arme->getDegats()); //on inflige des degats en fonction de notre arme
    //on affiche qu'on a attaqu� le cible et le nombre de d�g�ts subis
    cout << getNom() << " attaque " << cible.getNom() << " avec " << m_arme->getNom() << " et inflige " << m_arme->getDegats() << " degats" << endl;;
}

void Personnage::boirePotionDeVie(int nbPdV) //en param�tres le nombre de points de vie de la potion (� impl�menter plus tard)
{
    if (m_vie == 0){ //si la vie est �gale � 0, on est mort donc on ne peut pas boire de potion
        cout << getNom() <<" est mort ! Quelqu'un doit le ressusciter !" << endl;
    } else {
        m_vie+=nbPdV; // on se soigne
        if (m_vie >= 100) //on ne peut pas avoir plus de 100 pdv
        {
            m_vie=100;
        }
        cout << "Vous avez bu une potion qui vous a fait gagner " << nbPdV << " points de vie." << endl;
        cout << "Vous avez maintenant " << m_vie << " points de vie" << endl;
    }
}

void Personnage::changerArme(string nomNouvelleArme, int degatsNouvelleArme) //on change d'arme
{
    m_arme->changer(nomNouvelleArme, degatsNouvelleArme); //on appelle la m�thode dans arme
    cout << "Vous avez chang� d'arme et �tes maintenant �quip�s de : "; // on affiche la nouvelle arme
    m_arme->afficher();
    cout << endl;
}

bool Personnage::estVivant() const //on renvoie si on est vivant ou non
{
    return m_vie>0;
}

void Personnage::afficherPossibilites() const
{
    cout << "Que voulez-vous faire ?" << endl;
    cout << "0 : Attaquer" << endl;
    cout << "1 : Boire une potion de vie" << endl;
    cout << "2 : Changer d'arme" << endl;
}

void Personnage::faireAction(vector<Personnage*> listePerso, int numAction)
{
    //virtuelle ici
}

//getters
int Personnage::getVie() const //renvoie et affiche le nombre de points de vie actuels
{
    cout << "Points de vie : " << m_vie << endl;
    return m_vie;
}

string Personnage::getNom() const //renvoie le nom du perso
{
    return m_nom;
}

string Personnage::getClasse() const{} //m�thode virtuelle d�velopp�e dans guerrier et magicien

bool Personnage::getGel() const //renvoie la valeur du bool�en (si true, on ne peut pas jouer)
{
    return m_gel;
}

//setters
void Personnage::setVie(int points) //change le nombre de points de vie (en ajoute par d�faut)
{
    m_vie+=points;
}

void Personnage::setGel(bool a) //change la valeur du bool�en, si true on est gel�.
{
    m_gel=a;
}

//Operateurs
Personnage& Personnage::operator=(Personnage const& persoACopier)
{
    if (this != &persoACopier) //si l'objet est diff�rent
    {
        m_vie=persoACopier.m_vie;
        m_nom=persoACopier.m_nom;
        delete m_arme;
        m_arme = new Arme(*(persoACopier.m_arme));
    }
    return *this; //on renvoie l'objet
}

//Destructeur
Personnage::~Personnage();
