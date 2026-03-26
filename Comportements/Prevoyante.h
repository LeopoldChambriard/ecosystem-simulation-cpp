#ifndef _PREVOYANTE_H_
#define _PREVOYANTE_H_
#include "IComportement.h"

class Prevoyante : public IComportement {
public:
    void agir(IBestiole &moi, const std::vector<IBestiole*> &voisines, Milieu &milieu) override;
    IComportement* clone() const override { return new Prevoyante(*this); }
    const char* nom() const override { return "Prevoyante"; }
};
#endif