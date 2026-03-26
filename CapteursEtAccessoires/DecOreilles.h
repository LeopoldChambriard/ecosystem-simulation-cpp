#ifndef _DECOREILLES_H_
#define _DECOREILLES_H_

#include "BestioleDecorator.h"

class DecOreilles : public BestioleDecorator
{
private:
    double deltaO; // rayon d'écoute (pixels)
    double gammaO; // capacité de détection [0,1]

public:
    DecOreilles(IBestiole* c, double deltaO, double gammaO);

    void       draw(UImg& support)  override;
    void       accept(IVisiteur& v) override;
    IBestiole* clone()        const override;

    std::vector<IBestiole*> getBestiolesDetectees(
        const std::vector<IBestiole*>& toutes) const override;

    double getDeltaO() const { return deltaO; }
    double getGammaO() const { return gammaO; }
};

#endif
