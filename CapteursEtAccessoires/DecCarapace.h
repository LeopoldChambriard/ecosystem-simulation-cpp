#ifndef _DECCARAPACE_H_
#define _DECCARAPACE_H_

#include "BestioleDecorator.h"

class DecCarapace : public BestioleDecorator
{
private:
    double omega; // divise la proba de mort en collision
    double eta;   // divise la vitesse

public:
    DecCarapace(IBestiole *c, double omega, double eta);

    void draw(UImg &support) override;
    void accept(IVisiteur &v) override;
    IBestiole *clone() const override;

    // Surcharge : vitesse réduite par eta
    double getVitesse() const override { return composant->getVitesse() / eta; }

    double getResistanceCollision() const override { return omega; }
    double getOmega() const { return omega; }
    double getEta() const { return eta; }
};

#endif