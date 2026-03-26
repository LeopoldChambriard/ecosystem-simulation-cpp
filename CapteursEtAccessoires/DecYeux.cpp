#include "DecYeux.h"
#include "IVisiteur.h"
#include <cmath>

DecYeux::DecYeux(IBestiole* c, double alpha, double deltaY, double gammaY)
    : BestioleDecorator(c), alpha(alpha), deltaY(deltaY), gammaY(gammaY) {}

IBestiole* DecYeux::clone() const
{
    return new DecYeux(composant->clone(), alpha, deltaY, gammaY);
}

void DecYeux::accept(IVisiteur& v)
{
    v.visiter(*this);
    composant->accept(v); // propage aux couches internes
}

void DecYeux::draw(UImg& support)
{
    composant->draw(support);

    // Dessine le cône de vision en jaune semi-transparent
    T coul[3] = {200, 200, 50};
    double ori = getOrientation();
    int x0 = getX(), y0 = getY();

    int x1 = x0 + (int)(deltaY * std::cos(ori + alpha));
    int y1 = y0 - (int)(deltaY * std::sin(ori + alpha));
    int x2 = x0 + (int)(deltaY * std::cos(ori - alpha));
    int y2 = y0 - (int)(deltaY * std::sin(ori - alpha));

    support.draw_line(x0, y0, x1, y1, coul, 0.5f);
    support.draw_line(x0, y0, x2, y2, coul, 0.5f);
}

std::vector<IBestiole*> DecYeux::getBestiolesDetectees(
    const std::vector<IBestiole*>& toutes) const
{
    // Récupère ce que les couches internes détectent déjà
    auto detectees = composant->getBestiolesDetectees(toutes);

    double ori = getOrientation();
    int mx = getX(), my = getY();

    for (auto* b : toutes) {
        if (b->getId() == getId()) continue;
        if (!b->estVivante())      continue;

        double dx   =  b->getX() - mx;
        double dy   = -(b->getY() - my); // axe Y écran inversé
        double dist = std::sqrt(dx*dx + dy*dy);
        if (dist > deltaY) continue;

        // Vérifie que b est dans le cône
        double angleCible = std::atan2(dy, dx);
        double diff = angleCible - ori;
        while (diff >  M_PI) diff -= 2. * M_PI;
        while (diff < -M_PI) diff += 2. * M_PI;

        if (std::abs(diff) <= alpha && gammaY > b->getCamouflage()) {
            bool doublon = false;
            for (auto* d : detectees)
                if (d->getId() == b->getId()) { doublon = true; break; }
            if (!doublon)
                detectees.push_back(b);
        }
    }
    return detectees;
}
