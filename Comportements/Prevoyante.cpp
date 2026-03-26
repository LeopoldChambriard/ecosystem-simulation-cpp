#include "Prevoyante.h"
#include "IBestiole.h"
#include <cmath>
#include <limits>

void Prevoyante::agir(IBestiole &moi,
                      const std::vector<IBestiole*> &voisines,
                      Milieu& /*milieu*/)
{
    if (voisines.empty()) return;

    const double HORIZON = 20.0; // nb de pas anticipés

    double monX = moi.getX();
    double monY = moi.getY();
    double monOri = moi.getOrientation();
    double maVitesse = moi.getVitesse();

    // Position future de moi
    double futX = monX + std::cos(monOri) * maVitesse * HORIZON;
    double futY = monY - std::sin(monOri) * maVitesse * HORIZON;

    bool collision = false;
    for (auto* v : voisines) {
        double vOri = v->getOrientation();
        double vVit = v->getVitesse();

        // Position future de la voisine
        double vFutX = v->getX() + std::cos(vOri) * vVit * HORIZON;
        double vFutY = v->getY() - std::sin(vOri) * vVit * HORIZON;

        double dx = futX - vFutX;
        double dy = futY - vFutY;
        double dist = std::sqrt(dx*dx + dy*dy);

        if (dist < 20.0) { // risque de collision
            collision = true;
            break;
        }
    }

    if (collision)
        moi.setOrientation(monOri + M_PI / 4.); // dévie de 45°
}