#include "PersonnalitesMultiples.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include <cstdlib>

PersonnalitesMultiples::PersonnalitesMultiples(int dMin, int dMax)
    : courant(nullptr), compteur(0), dureeMin(dMin), dureeMax(dMax)
{
    pool.push_back(new Gregaire());
    pool.push_back(new Peureuse());
    pool.push_back(new Kamikaze());
    pool.push_back(new Prevoyante());
    choisirAleatoirement();
}

PersonnalitesMultiples::PersonnalitesMultiples(const PersonnalitesMultiples &other)
    : courant(nullptr), compteur(other.compteur),
      dureeMin(other.dureeMin), dureeMax(other.dureeMax)
{
    for (auto *c : other.pool)
        pool.push_back(c->clone());
    choisirAleatoirement();
}

PersonnalitesMultiples::~PersonnalitesMultiples()
{
    for (auto *c : pool)
        delete c;
}

void PersonnalitesMultiples::choisirAleatoirement()
{
    courant = pool[rand() % pool.size()];
    compteur = dureeMin + rand() % (dureeMax - dureeMin + 1);
}

void PersonnalitesMultiples::agir(IBestiole &moi,
                                  const std::vector<IBestiole *> &voisines,
                                  Milieu &milieu)
{
    if (--compteur <= 0)
        choisirAleatoirement();

    if (courant)
        courant->agir(moi, voisines, milieu);
}