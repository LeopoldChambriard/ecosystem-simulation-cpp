#include "DecNageoires.h"
#include "IVisiteur.h"
#include <cmath>

DecNageoires::DecNageoires(IBestiole* c, double nu)
    : BestioleDecorator(c), nu(nu) {}

IBestiole* DecNageoires::clone() const
{
    return new DecNageoires(composant->clone(), nu);
}

void DecNageoires::accept(IVisiteur& v)
{
    v.visiter(*this);
    composant->accept(v);
}

void DecNageoires::draw(UImg& support)
{
    composant->draw(support);
    // Deux traits latéraux orange symbolisant les nageoires
    T coul[3] = {255, 140, 0};
    double ori = getOrientation();
    int x0 = getX(), y0 = getY();

    int x1 = x0 + (int)(7 * std::cos(ori + M_PI / 2.));
    int y1 = y0 - (int)(7 * std::sin(ori + M_PI / 2.));
    int x2 = x0 + (int)(7 * std::cos(ori - M_PI / 2.));
    int y2 = y0 - (int)(7 * std::sin(ori - M_PI / 2.));

    support.draw_line(x0, y0, x1, y1, coul);
    support.draw_line(x0, y0, x2, y2, coul);
}
