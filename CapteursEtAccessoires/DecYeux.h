#ifndef _DECYEUX_H_
#define _DECYEUX_H_

#include "BestioleDecorator.h"

class DecYeux : public BestioleDecorator
{
private:
    double alpha;  // demi-angle du cône de vision (radians)
    double deltaY; // distance de vision (pixels)
    double gammaY; // capacité de détection [0,1]

public:
    DecYeux(IBestiole* c, double alpha, double deltaY, double gammaY);

    void       draw(UImg& support)  override;
    void       accept(IVisiteur& v) override;
    IBestiole* clone()        const override;

    std::vector<IBestiole*> getBestiolesDetectees(
        const std::vector<IBestiole*>& toutes) const override;

    double getAlpha()  const { return alpha;  }
    double getDeltaY() const { return deltaY; }
    double getGammaY() const { return gammaY; }
};

#endif
