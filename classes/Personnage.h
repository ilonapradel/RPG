#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include <string>
#include "Personnage.h"
#include "Arme.h"
#include <iostream>
#include <vector>

class Personnage{
public:
    //constructeurs
    Personnage(std::string nom);
    Personnage(std::string nomArme, int degatsArme, std::string nomP);
    Personnage(Personnage const& personnageACopier); //si on veut le m�me personnage qu'un qui existe d�j�

    //m�thodes
    virtual void afficherEtat() const; //pour afficher les caract�ristiques du personnage
    void recevoirDegats(int nbDegats); //pour subir des d�g�ts
    void attaquer(Personnage &cible); //pour attaquer un autre personnage
    void boirePotionDeVie(int nbPdV); //pour se soigner
    void changerArme(std::string nomNouvelleArme, int degatsNouvelleArme); //pour changer d'arme
    bool estVivant() const; //pour v�rifier que le perso est vivant
    virtual void afficherPossibilites() const; //affiche les possibilit�s de jeu du joueur
    virtual void faireAction(std::vector<Personnage*> listePerso, int numAction); //effectue l'action demand�e

    //getters
    int getVie() const; //renvoie le nombre de points de vie actuels
    virtual std::string getClasse() const; // renvoie la classe du perso (magicien ou guerrier pour le moment)
    std::string getNom() const; //renvoie le nom du perso
    bool getGel() const; //renvoie si le perso est incapacit� ou non

    //setters
    void setVie(int points); //change le nombre de points de vie
    void setGel(bool a); //g�le le perso (ne peut pas jouer au prochain tour si true)

    //Operateurs
    Personnage& operator=(Personnage const& persoACopier);

    //Destructeur
    virtual ~Personnage();

protected:
    //Attributs
    int m_vie;
    Arme *m_arme;
    std::string m_nom;
    bool m_gel;
};

#endif // PERSONNAGE_H_INCLUDED
