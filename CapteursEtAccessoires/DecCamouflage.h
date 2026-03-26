#ifndef _DECCAMOUFLAGE_H_
#define _DECCAMOUFLAGE_H_

#include "BestioleDecorator.h"

class DecCamouflage : public BestioleDecorator
{
private:
    double psi; // niveau de camouflage [0,1]

public:
    DecCamouflage(IBestiole* c, double psi);

    void       draw(UImg& support)  override;
    void       accept(IVisiteur& v) override;
    IBestiole* clone()        const override;

    // Surcharge : retourne le niveau de camouflage
    double getCamouflage() const override { return psi; }

    double getPsi() const { return psi; }
};

#endif
