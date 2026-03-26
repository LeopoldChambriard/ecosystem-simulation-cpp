#include "DecCamouflage.h"
#include "IVisiteur.h"

DecCamouflage::DecCamouflage(IBestiole* c, double psi)
    : BestioleDecorator(c), psi(psi) {}

IBestiole* DecCamouflage::clone() const
{
    return new DecCamouflage(composant->clone(), psi);
}

void DecCamouflage::accept(IVisiteur& v)
{
    v.visiter(*this);
    composant->accept(v);
}

void DecCamouflage::draw(UImg& support)
{
    composant->draw(support);
    // Superpose un rectangle blanc semi-transparent pour simuler le camouflage
    // Plus psi est élevé, plus la bestiole est "effacée"
    T blanc[3] = {255, 255, 255};
    float opacite = static_cast<float>(psi * 0.75);
    support.draw_rectangle(getX() - 12, getY() - 12,
                           getX() + 12, getY() + 12,
                           blanc, opacite);
}
