#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED

#include <iostream>
#include <string>

class Arme {

public:
    // Constructeurs
    Arme();
    Arme(std::string nom, int degats);

    //Méthodes
    void changer(std::string nom, int degats); //pour changer d'arme
    void afficher() const; //pour afficher quel arme on possède
    //Getters
    int getDegats() const; //renvoie le nombre de dégâts
    std::string getNom() const; //renvoie le nom de l'arme

private:
    //Attributs
    std::string m_nom;
    int m_degats;

};

#endif // ARME_H_INCLUDED
