#ifndef MAGICIEN_H_INCLUDED
#define MAGICIEN_H_INCLUDED

#include <iostream>
#include <string>
#include "Personnage.h"

class Magicien : public Personnage
{
public:
    //Constructeurs
    Magicien(std::string nom);

    //M�thodes
    void bouleDeFeu(Personnage &cible, int duree, int coutMana); //lance une boule de feu sur une autre cible, en param�tres la dur�e et le co�t, � impl�menter
    void gel(Personnage &cible, int coutMana); //g�le la cible, en param�tre le co�t en mana
    void ressusciter(Personnage &cible); //si la cible est morte, la ressuscite
    void soigner(Personnage &cible, int points); //soigne une cible

    //getter
    std::string getClasse() const;

    //Destructeur
    virtual ~Magicien();

protected:
    //Attributs
    int m_mana;

};


#endif // MAGICIEN_H_INCLUDED
