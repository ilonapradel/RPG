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

    //M�thodes
    void faireAction(std::vector<Personnage*> listePerso, int numAction); //effectue l'action demand�e en fonction du num�ro

    //getter
    std::string getClasse() const; //renvoie la classe

    //Destructeur
    virtual ~Guerrier();
};


#endif // GUERRIER_H_INCLUDED
