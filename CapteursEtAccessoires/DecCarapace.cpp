#include "DecCarapace.h"
#include "IVisiteur.h"

DecCarapace::DecCarapace(IBestiole *c, double omega, double eta)
    : BestioleDecorator(c), omega(omega), eta(eta) {}

IBestiole *DecCarapace::clone() const
{
    return new DecCarapace(composant->clone(), omega, eta);
}

void DecCarapace::accept(IVisiteur &v)
{
    // Étape A : Le Double Dispatch
    // Résolution dynamique du type réel de *this ET du visiteur v
    v.visiter(*this);

    // Étape B : La propagation (Synergie avec le Décorateur)
    // On passe le visiteur à la couche interne (ex: la Bestiole de base)
    composant->accept(v);
}

void DecCarapace::draw(UImg &support)
{
    composant->draw(support);
    // Anneau gris symbolisant la carapace
    T coul[3] = {139, 69, 19};
    support.draw_circle(getX(), getY(), 3, coul, 1.0f);
}
