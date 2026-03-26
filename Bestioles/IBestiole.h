#ifndef _IBESTIOLE_H_
#define _IBESTIOLE_H_

#include "UImg.h"
#include <vector>

class Milieu;
class IVisiteur;
class IComportement;

class IBestiole
{
public:
    virtual ~IBestiole() {}

    virtual void action(Milieu &monMilieu) = 0;
    virtual void draw(UImg &support) = 0;
    virtual IBestiole *clone() const = 0;
    virtual void accept(IVisiteur &v) = 0;
    virtual void setVitesse(double v) = 0;

    virtual void setCoords(int px, int py) = 0;
    virtual int getId() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual double getOrientation() const = 0;
    virtual double getVitesse() const = 0;
    virtual double getCamouflage() const = 0;
    virtual int getAge() const = 0;
    virtual int getAgeLimite() const = 0;
    virtual bool estVivante() const = 0;

    virtual std::vector<IBestiole *> getBestiolesDetectees(
        const std::vector<IBestiole *> &toutes) const = 0;

    virtual void initCoords(int xLim, int yLim) = 0;
    virtual void setComportement(IComportement *c) = 0;
    virtual void setOrientation(double o) = 0;
    virtual void tuer() = 0;
    virtual double getResistanceCollision() const = 0;
    virtual void agirAvecVoisines(const std::vector<IBestiole*>& voisines, Milieu& m) = 0;
};

#endif