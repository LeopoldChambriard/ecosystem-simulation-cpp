#ifndef _ICOMPORTEMENT_H_
#define _ICOMPORTEMENT_H_

#include <vector>

class IBestiole;
class Milieu;

class IComportement
{
public:
    virtual ~IComportement() {}

    // Calcule le delta d'orientation à appliquer à la bestiole
    virtual void agir(IBestiole &moi, const std::vector<IBestiole *> &voisines, Milieu &milieu) = 0;

    // Pour le Prototype / clonage de la bestiole
    virtual IComportement *clone() const = 0;

    // Nom pour affichage/debug
    virtual const char *nom() const = 0;
};

#endif