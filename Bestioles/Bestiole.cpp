#include "Bestiole.h"
#include "Milieu.h"
#include <cstdlib>
#include <cmath>
#include <IVisiteur.h>

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_VITESSE = 10.;
const double Bestiole::LIMITE_VUE = 30.;

int Bestiole::next = 0;

static const T COULEURS[][3] = {
    {200, 200, 200}, // 0 default (gris)
    {100, 200, 100}, // 1 Gregaire (vert)
    {200, 100, 100}, // 2 Peureuse (rouge)
    {200, 100, 200}, // 3 Kamikaze (violet)
    {100, 180, 220}, // 4 Prevoyante (bleu clair)
    {255, 165,   0},  // 5 PersonnalitesMultiples (orange)
};
Bestiole::Bestiole(void)
{
    identite = ++next;
    cout << "const Bestiole (" << identite << ") par defaut" << endl;
    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
    vitesse = static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE;
    vivante = true;
    age = 0;
    ageLimite = 500 + rand() % 1000; // entre 500 et 1500 pas
    couleur = new T[3];
    couleur[0] = COULEURS[0][0];
    couleur[1] = COULEURS[0][1];
    couleur[2] = COULEURS[0][2];
    comportement = nullptr;
}

Bestiole::Bestiole(const Bestiole &b)
{
    identite = ++next;
    cout << "const Bestiole (" << identite << ") par copie" << endl;
    x = b.x;
    y = b.y;
    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    couleur = new T[3];
    memcpy(couleur, b.couleur, 3 * sizeof(T));
    comportement = b.comportement ? b.comportement->clone() : nullptr;
}

Bestiole::~Bestiole(void)
{
    delete[] couleur;
    delete comportement;
    cout << "dest Bestiole" << endl;
}

void Bestiole::setComportement(IComportement *c)
{
    delete comportement;
    comportement = c;

    int idx = 0;
    if (c)
    {
        string n = c->nom();
        if (n == "Gregaire")
            idx = 1;
        else if (n == "Peureuse")
            idx = 2;
        else if (n == "Kamikaze")
            idx = 3;
        else if (n == "Prevoyante")
            idx = 4;
        else if (n == "PersonnalitesMultiples")
            idx = 5;
    }
    couleur[0] = COULEURS[idx][0];
    couleur[1] = COULEURS[idx][1];
    couleur[2] = COULEURS[idx][2];
}

void Bestiole::initCoords(int xLim, int yLim)
{
    x = rand() % xLim;
    y = rand() % yLim;
}

void Bestiole::bouge(int xLim, int yLim)
{
    double vitesse = getVitesse();
    double nx, ny;
    double dx = cos(orientation) * vitesse;
    double dy = -sin(orientation) * vitesse;
    int cx, cy;

    cx = static_cast<int>(cumulX);
    cumulX -= cx;
    cy = static_cast<int>(cumulY);
    cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ((nx < 0) || (nx > xLim - 1))
    {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else
    {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 0) || (ny > yLim - 1))
    {
        orientation = -orientation;
        cumulY = 0.;
    }
    else
    {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}

// ptite correction
//  sert à faire vieillir la bestiole, et à lui faire appliquer son comportement (si elle en a un) en fonction de ses voisines
void Bestiole::action(Milieu &monMilieu)
{
    auto voisines = getBestiolesDetectees(monMilieu.getBestioles());
    agirAvecVoisines(voisines, monMilieu);
}

void Bestiole::draw(UImg &support)
{
    double xt = x + cos(orientation) * AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * AFF_SIZE / 2.1;

    support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5., -orientation / M_PI * 180., couleur);
    support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);
}

void Bestiole::accept(IVisiteur &v)
{
    v.visiter(*this);
}

bool operator==(const Bestiole &b1, const Bestiole &b2)
{
    return (b1.identite == b2.identite);
}

void Bestiole::agirAvecVoisines(const std::vector<IBestiole *> &voisines, Milieu &m)
{
    age++;
    if (age >= ageLimite)
    {
        vivante = false;
        return;
    }
    if (comportement)
        comportement->agir(*this, voisines, m);
    bouge(m.getWidth(), m.getHeight());
}

bool Bestiole::jeTeVois(const Bestiole &b) const
{
    double dist = std::sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    return (dist <= LIMITE_VUE);
}

std::vector<IBestiole *> Bestiole::getBestiolesDetectees(
    const std::vector<IBestiole *> &toutes) const
{
    return {}; // sans capteur, on ne détecte rien
}