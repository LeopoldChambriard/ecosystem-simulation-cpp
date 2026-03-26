#include "Milieu.h"
#include "BestioleFactory.h"
#include <cstdlib>
#include <ctime>

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3),
                                          width(_width), height(_height)
{
    cout << "const Milieu" << endl;
    std::srand(time(NULL));
}

Milieu::~Milieu(void)
{
    cout << "dest Milieu" << endl;
}   

void Milieu::addMember(IBestiole *b)
{
    ptrBestioles.push_back(b);
    notifier({TypeEvenement::NAISSANCE, b->getId(), pas, "ajout"});
}

void Milieu::notifier(const Evenement &e)
{
    for (auto *o : observateurs)
        o->notifier(e);
}

void Milieu::supprimerMortes()
{
    auto it = ptrBestioles.begin();
    while (it != ptrBestioles.end())
    {
        if (!(*it)->estVivante())
        {
            notifier({TypeEvenement::MORT, (*it)->getId(), pas, "mort"});
            delete *it;
            it = ptrBestioles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Milieu::gererCollisions()
{
    const double RAYON_COLLISION = 12.0;
    const double PROBA_MORT = 0.3;

    for (size_t i = 0; i < ptrBestioles.size(); ++i)
    {
        for (size_t j = i + 1; j < ptrBestioles.size(); ++j)
        {
            IBestiole *a = ptrBestioles[i];
            IBestiole *b = ptrBestioles[j];
            if (!a->estVivante() || !b->estVivante())
                continue;

            double dx = a->getX() - b->getX();
            double dy = a->getY() - b->getY();
            double dist = std::sqrt(dx * dx + dy * dy);

            if (dist < RAYON_COLLISION)
            {
                notifier({TypeEvenement::COLLISION, a->getId(), pas, "collision"});
                // Proba de mort réduite par omega (carapace) : PROBA_MORT / omega
                double probaA = PROBA_MORT / a->getResistanceCollision();
                double probaB = PROBA_MORT / b->getResistanceCollision();

                if (static_cast<double>(std::rand()) / RAND_MAX < probaA)
                    a->tuer();
                else
                    a->setOrientation(a->getOrientation() + M_PI);

                if (static_cast<double>(std::rand()) / RAND_MAX < probaB)
                    b->tuer();
                else
                    b->setOrientation(b->getOrientation() + M_PI);
            }
        }
    }
}

void Milieu::gererClonage()
{
    const double PROBA_CLONE = 0.001;
    std::vector<IBestiole*> clones;

    for (auto* b : ptrBestioles)
    {
        if (!b->estVivante()) continue;
        if (static_cast<double>(std::rand()) / RAND_MAX < PROBA_CLONE)
        {
            IBestiole* clone = b->clone();
            clone->initCoords(width, height); // position aléatoire
            clones.push_back(clone);
            notifier({TypeEvenement::CLONE, b->getId(), pas, "clonage"});
        }
    }
    for (auto* c : clones)
        addMember(c);
}

void Milieu::gererNaissancesSpontanees()
{
    const double TAUX_NAISSANCE = 0.005;
    if (static_cast<double>(std::rand()) / RAND_MAX < TAUX_NAISSANCE)
    {
        IBestiole *b = BestioleFactory::getInstance()->creer(width, height);
        addMember(b);
    }
}


void Milieu::step()
{
    // Efface le fond
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

    // Snapshot journal avant action
    for (auto *b : ptrBestioles)
    {
        if (b->estVivante())
        {
            SnapshotBestiole s;
            s.id = b->getId();
            s.x = b->getX();
            s.y = b->getY();
            s.vitesse = b->getVitesse();
            s.orientation = b->getOrientation();
            journal.ajouterSnapshot(s);
        }
    }

    // Action + dessin de chaque bestiole
    for (auto *b : ptrBestioles)
    {
        if (b->estVivante())
        {
            auto voisines = b->getBestiolesDetectees(ptrBestioles);
            b->agirAvecVoisines(voisines, *this);
            b->draw(*this);
        }
    }

    gererNaissancesSpontanees();
    gererCollisions();
    gererClonage();
    supprimerMortes();

    notifier({TypeEvenement::PAS_SIMULATION, -1, pas, ""});
    ++pas;
}

int Milieu::nbVoisins(const IBestiole& b)
{
    return b.getBestiolesDetectees(ptrBestioles).size();
}

void Milieu::fairenaitre()
{
    IBestiole *b = BestioleFactory::getInstance()->creer(width, height);
    addMember(b);
}