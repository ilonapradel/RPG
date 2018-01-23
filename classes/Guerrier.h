#ifndef GUERRIER_H_INCLUDED
#define GUERRIER_H_INCLUDED

#include <iostream>
#include <string>
#include "Personnage.h"

class Guerrier : public Personnage
{
public:
    //Constructeurs
    Guerrier(std::string nom);

    //Méthodes de magicien, virtuelles ici
    virtual void soigner(Personnage &cible, int points);
    virtual void bouleDeFeu(Personnage &cible, int duree, int coutMana);
    virtual void gel(Personnage &cible, int coutMana);

    //getter
    std::string getClasse() const; //renvoie le classe

    //Destructeur
    virtual ~Guerrier();
};


#endif // GUERRIER_H_INCLUDED
