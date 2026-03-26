#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_
#include "IComportement.h"

class Kamikaze : public IComportement {
public:
    void agir(IBestiole &moi, const std::vector<IBestiole*> &voisines, Milieu &milieu) override;
    IComportement* clone() const override { return new Kamikaze(*this); }
    const char* nom() const override { return "Kamikaze"; }
};
#endif