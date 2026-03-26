#include "Peureuse.h"
#include "IBestiole.h"
#include <cmath>

void Peureuse::agir(IBestiole &moi,
                    const std::vector<IBestiole*> &voisines,
                    Milieu& /*milieu*/)
{
    if (vitesseNormale < 0.)
        vitesseNormale = moi.getVitesse(); // mémorise la vitesse initiale au 1er appel

    if ((int)voisines.size() >= seuilPeur) {
        // Fuite : direction opposée + boost de vitesse
        if (!enFuite) {
            moi.setOrientation(moi.getOrientation() + M_PI);
            moi.setVitesse(vitesseNormale * 2.5); // boost x2.5
            enFuite = true;
        }
    } else {
        // Reprend sa vitesse normale
        if (enFuite) {
            moi.setVitesse(vitesseNormale);
            enFuite = false;
        }
    }
}