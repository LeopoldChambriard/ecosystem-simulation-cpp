#ifndef _PERSONNALITESMULTIPLES_H_
#define _PERSONNALITESMULTIPLES_H_
#include "IComportement.h"
#include <vector>
class PersonnalitesMultiples : public IComportement {
    std::vector<IComportement*> pool;
    IComportement* courant;
    int compteur, dureeMin, dureeMax;
    void choisirAleatoirement();
public:
    explicit PersonnalitesMultiples(int dMin = 30, int dMax = 100);
    PersonnalitesMultiples(const PersonnalitesMultiples& other);
    ~PersonnalitesMultiples();
    void agir(IBestiole &moi, const std::vector<IBestiole*> &voisines, Milieu &milieu) override;
    IComportement* clone() const override { return new PersonnalitesMultiples(*this); }
    const char* nom() const override { return "PersonnalitesMultiples"; }
};
#endif
