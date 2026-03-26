#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "UImg.h"
#include "Bestiole.h"
#include "IBestiole.h"
#include "IObservateur.h"
#include "JournalSimulation.h"

#include <iostream>
#include <vector>
#include <algorithm> // pour std::remove

using namespace std;

class Milieu : public UImg
{
private:
    static const T white[];

    int width, height;
    std::vector<IBestiole *> ptrBestioles;
    std::vector<IObservateur *> observateurs;
    int pas = 0;
    JournalSimulation journal;

    void gererCollisions();
    void gererNaissancesSpontanees();
    void notifier(const Evenement &e);
    void supprimerMortes();
    void gererClonage();

public:
    Milieu(int _width, int _height);
    ~Milieu(void);

    int getWidth(void) const { return width; }
    int getHeight(void) const { return height; }

    void step(void);

    void addMember(IBestiole *b);

    // Fait naître une bestiole (événement extérieur)
    void fairenaitre();

    const std::vector<IBestiole *> &getBestioles() const { return ptrBestioles; }

    int nbVoisins(const IBestiole &b);

    void ajouterObservateur(IObservateur *o)
    {
        observateurs.push_back(o);
    }

    void retirerObservateur(IObservateur *o)
    {
        observateurs.erase(
            std::remove(observateurs.begin(), observateurs.end(), o),
            observateurs.end());
    }

    void changerComportement(int id, IComportement* c)
{
    for (auto* b : ptrBestioles)
    {
        if (b->getId() == id && b->estVivante())
        {
            b->setComportement(c);
            notifier({TypeEvenement::CHANGEMENT_COMPORTEMENT, id, pas, c ? c->nom() : "Neutre"});
            return;
        }
    }
}
};

#endif