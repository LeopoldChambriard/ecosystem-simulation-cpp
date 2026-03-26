#ifndef _PEUREUSE_H_
#define _PEUREUSE_H_
#include "IComportement.h"

class Peureuse : public IComportement {
private:
    int seuilPeur;
    double vitesseNormale;  // mémorise la vitesse de croisière
    bool enFuite;

public:
    Peureuse(int seuil = 3) : seuilPeur(seuil), vitesseNormale(-1.), enFuite(false) {}
    void agir(IBestiole &moi, const std::vector<IBestiole*> &voisines, Milieu &milieu) override;
    IComportement* clone() const override { return new Peureuse(*this); }
    const char* nom() const override { return "Peureuse"; }
};
#endif