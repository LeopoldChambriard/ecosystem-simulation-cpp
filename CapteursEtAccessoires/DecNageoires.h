#ifndef _DECNAGEOIRES_H_
#define _DECNAGEOIRES_H_

#include "BestioleDecorator.h"

class DecNageoires : public BestioleDecorator
{
private:
    double nu; // coefficient multiplicateur de vitesse >= 1

public:
    DecNageoires(IBestiole* c, double nu);

    void       draw(UImg& support)  override;
    void       accept(IVisiteur& v) override;
    IBestiole* clone()        const override;

    // Surcharge : vitesse × nu
    double getVitesse() const override { return composant->getVitesse() * nu; }

    double getNu() const { return nu; }
};

#endif
