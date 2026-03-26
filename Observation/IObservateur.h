#ifndef _IOBSERVATEUR_H_
#define _IOBSERVATEUR_H_

#include <string>

// Types d'événements émis par le Milieu
enum class TypeEvenement
{
    NAISSANCE,
    MORT,
    CLONE,
    COLLISION,
    CHANGEMENT_COMPORTEMENT,
    PAS_SIMULATION
};

struct Evenement
{
    TypeEvenement type;
    int idBestiole;   // bestiole concernée (-1 si global)
    int pas;          // numéro du pas de simulation
    std::string info; // description textuelle optionnelle
};

class IObservateur
{
public:
    virtual ~IObservateur() {}
    virtual void notifier(const Evenement &e) = 0;
};

#endif