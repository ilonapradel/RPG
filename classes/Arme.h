#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED

#include <iostream>
#include <string>

class Arme {

public:
    // Constructeurs
    Arme();
    Arme(std::string nom, int degats);

    //M�thodes
    void changer(std::string nom, int degats); //pour changer d'arme
    void afficher() const; //pour afficher quel arme on poss�de
    //Getters
    int getDegats() const; //renvoie le nombre de d�g�ts
    std::string getNom() const; //renvoie le nom de l'arme

private:
    //Attributs
    std::string m_nom;
    int m_degats;

};

#endif // ARME_H_INCLUDED
