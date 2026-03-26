#include "Gregaire.h"
#include "IBestiole.h"
#include <cmath>

// Ajuste sa direction sur la direction moyenne des voisines détectées
void Gregaire::agir(IBestiole &moi,
                    const std::vector<IBestiole *> &voisines,
                    Milieu & /*milieu*/)
{
    if (voisines.empty())
        return;

    double sumX = 0., sumY = 0.;
    for (auto *v : voisines)
    {
        sumX += std::cos(v->getOrientation());
        sumY += std::sin(v->getOrientation());
    }
    sumX /= voisines.size();
    sumY /= voisines.size();

    if (std::abs(sumX) < 1e-9 && std::abs(sumY) < 1e-9)
        return;

    moi.setOrientation(std::atan2(sumY, sumX));
}