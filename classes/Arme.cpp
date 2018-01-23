#include "Arme.h"

using namespace std;

//Constructeurs
Arme::Arme():m_nom("Vieille Épée"), m_degats(10){}
Arme::Arme(string nom, int degats) : m_nom(nom), m_degats(degats){}

//Méthodes

//Changer d'arme
void Arme::changer(string nom, int degats){
    m_nom = nom;
    m_degats = degats;
}

//Afficher l'arme actuelle
void Arme::afficher() const {
    cout << "Arme : " << m_nom << " (Dégâts : " << m_degats << ")" << endl;
}

//Renvoie le nombre de dégâts actuels
int Arme::getDegats() const{
    return m_degats;
}

//Renvoie le nom de l'arme actuelle
string Arme::getNom() const{
    return m_nom;
}
