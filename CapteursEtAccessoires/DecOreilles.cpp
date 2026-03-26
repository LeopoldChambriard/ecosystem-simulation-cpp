#include "DecOreilles.h"
#include "IVisiteur.h"
#include <cmath>

DecOreilles::DecOreilles(IBestiole* c, double deltaO, double gammaO)
    : BestioleDecorator(c), deltaO(deltaO), gammaO(gammaO) {}

IBestiole* DecOreilles::clone() const
{
    return new DecOreilles(composant->clone(), deltaO, gammaO);
}

void DecOreilles::accept(IVisiteur& v)
{
    v.visiter(*this);
    composant->accept(v);
}

void DecOreilles::draw(UImg& support)
{
    composant->draw(support);
    // Cercle d'écoute bleu semi-transparent
    T coul[3] = {80, 160, 230};
    support.draw_circle(getX(), getY(), (int)deltaO, coul, 0.12f);
}

std::vector<IBestiole*> DecOreilles::getBestiolesDetectees(
    const std::vector<IBestiole*>& toutes) const
{
    auto detectees = composant->getBestiolesDetectees(toutes);

    int mx = getX(), my = getY();

    for (auto* b : toutes) {
        if (b->getId() == getId()) continue;
        if (!b->estVivante())      continue;

        double dx   = b->getX() - mx;
        double dy   = b->getY() - my;
        double dist = std::sqrt(dx*dx + dy*dy);

        if (dist <= deltaO && gammaO > b->getCamouflage()) {
            bool doublon = false;
            for (auto* d : detectees)
                if (d->getId() == b->getId()) { doublon = true; break; }
            if (!doublon)
                detectees.push_back(b);
        }
    }
    return detectees;
}
