#ifndef MAGICIEN_H_INCLUDED
#define MAGICIEN_H_INCLUDED

#include <iostream>
#include <string>
#include "Personnage.h"
#include <vector>

class Magicien : public Personnage
{
public:
    //Constructeurs
    Magicien(std::string nom);

    //Méthodes
    void bouleDeFeu(Personnage &cible, int duree, int coutMana); //lance une boule de feu sur une autre cible, en paramètres la durée et le coût, à implémenter
    void gel(Personnage &cible, int coutMana); //gèle la cible, en paramètre le coût en mana
    void ressusciter(Personnage &cible); //si la cible est morte, la ressuscite
    void soigner(Personnage &cible, int points); //soigne une cible
    void afficherPossibilites() const; //affiche les possibilités de jeu du MAGICIEN.
    void faireAction(std::vector<Personnage*> listePerso, int numAction); //effectue l'action demandée en fonction du numéro

    //getter
    std::string getClasse() const;

    //Destructeur
    virtual ~Magicien();

protected:
    //Attributs
    int m_mana;

};


#endif // MAGICIEN_H_INCLUDED
