#include "Kamikaze.h"
#include "IBestiole.h"
#include <cmath>
#include <limits>

void Kamikaze::agir(IBestiole &moi,
                    const std::vector<IBestiole*> &voisines,
                    Milieu& /*milieu*/)
{
    if (voisines.empty()) return;

    // Trouve la bestiole la plus proche
    IBestiole* cible = nullptr;
    double distMin = std::numeric_limits<double>::max();

    for (auto* v : voisines) {
        double dx = v->getX() - moi.getX();
        double dy = v->getY() - moi.getY();
        double dist = std::sqrt(dx*dx + dy*dy);
        if (dist < distMin) {
            distMin = dist;
            cible = v;
        }
    }

    if (cible) {
        double dx =  cible->getX() - moi.getX();
        double dy = -(cible->getY() - moi.getY()); // axe Y écran inversé
        moi.setOrientation(std::atan2(dy, dx));
    }
}