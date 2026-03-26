#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_
#include "IComportement.h"
class Gregaire : public IComportement {
public:
    void agir(IBestiole &moi, const std::vector<IBestiole*> &voisines, Milieu &milieu) override;
    IComportement* clone() const override { return new Gregaire(*this); }
    const char* nom() const override { return "Gregaire"; }
};
#endif
