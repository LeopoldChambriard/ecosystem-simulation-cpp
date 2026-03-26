#include <iostream>
#include <cmath>
#include <vector>
#include "Bestiole.h"
#include "DecYeux.h"
#include "DecOreilles.h"
#include "DecCamouflage.h"
#include "DecCarapace.h"

using namespace std;

int passed = 0, failed = 0;

void check(bool ok, const string& msg)
{
    cout << (ok ? "[OK]  " : "[FAIL]") << " " << msg << endl;
    ok ? passed++ : failed++;
}

int main()
{
    cout << "=== TESTS BESTIOLES ===" << endl << endl;

    // ─────────────────────────────────────────
    // TESTS DecCamouflage
    // ─────────────────────────────────────────
    cout << "-- DecCamouflage --" << endl;

    {
        IBestiole* b = new DecCamouflage(new Bestiole(), 0.7);
        check(b->getCamouflage() == 0.7, "getCamouflage() retourne psi=0.7");
        delete b;
    }
    {
        IBestiole* b = new DecCamouflage(new Bestiole(), 0.0);
        check(b->getCamouflage() == 0.0, "getCamouflage() retourne psi=0.0");
        delete b;
    }

    // ─────────────────────────────────────────
    // TESTS DecCarapace
    // ─────────────────────────────────────────
    cout << "\n-- DecCarapace --" << endl;

    {
        Bestiole* base = new Bestiole();
        double vitesseBase = base->getVitesse();
        IBestiole* b = new DecCarapace(base, 2.0, 2.0);
        check(b->getVitesse() == vitesseBase / 2.0, "carapace divise la vitesse par eta");
        delete b;
    }
    {
        IBestiole* b = new DecCarapace(new Bestiole(), 3.0, 1.5);
        check(b->getResistanceCollision() == 3.0, "getResistanceCollision() retourne omega=3.0");
        delete b;
    }
    {
        IBestiole* b = new Bestiole();
        check(b->getResistanceCollision() == 1.0, "Bestiole sans carapace : resistance=1.0");
        delete b;
    }

    // ─────────────────────────────────────────
    // TESTS tuer()
    // ─────────────────────────────────────────
    cout << "\n-- tuer() --" << endl;

    {
        IBestiole* b = new Bestiole();
        check(b->estVivante(), "bestiole vivante à la création");
        b->tuer();
        check(!b->estVivante(), "tuer() -> estVivante() == false");
        delete b;
    }
    {
        // tuer() à travers un décorateur
        IBestiole* b = new DecCarapace(new Bestiole(), 2.0, 1.0);
        b->tuer();
        check(!b->estVivante(), "tuer() propagé à travers DecCarapace");
        delete b;
    }

    // ─────────────────────────────────────────
    // TESTS DecYeux
    // ─────────────────────────────────────────
    cout << "\n-- DecYeux --" << endl;

    {
        // Cible dans le cône
        Bestiole* base = new Bestiole();
        base->setCoords(100, 100);
        base->setOrientation(0.0); // regarde à droite
        IBestiole* bYeux = new DecYeux(base, M_PI / 2., 200., 1.0);

        Bestiole* cible = new Bestiole();
        cible->setCoords(150, 100); // à droite, dist=50, dans le cône

        vector<IBestiole*> toutes = {bYeux, cible};
        auto detectees = bYeux->getBestiolesDetectees(toutes);
        check(detectees.size() == 1 && detectees[0]->getId() == cible->getId(),
              "DecYeux détecte une cible dans le cône");
        delete bYeux;
        delete cible;
    }
    {
        // Cible hors du cône (derrière)
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        base->setOrientation(0.0);
        IBestiole* bYeux = new DecYeux(base, M_PI / 6., 200., 1.0); // cône étroit

        Bestiole* cible = new Bestiole();
        cible->initCoords(50, 100); // à gauche, hors du cône

        vector<IBestiole*> toutes = {bYeux, cible};
        auto detectees = bYeux->getBestiolesDetectees(toutes);
        check(detectees.empty(), "DecYeux ne détecte pas une cible hors du cône");
        delete bYeux;
        delete cible;
    }
    {
        // Cible trop loin
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        base->setOrientation(0.0);
        IBestiole* bYeux = new DecYeux(base, M_PI / 2., 30., 1.0); // portée 30

        Bestiole* cible = new Bestiole();
        cible->initCoords(200, 100); // dist=100, hors portée

        vector<IBestiole*> toutes = {bYeux, cible};
        auto detectees = bYeux->getBestiolesDetectees(toutes);
        check(detectees.empty(), "DecYeux ne détecte pas une cible trop loin");
        delete bYeux;
        delete cible;
    }
    {
        // Cible camouflée (psi > gammaY)
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        base->setOrientation(0.0);
        IBestiole* bYeux = new DecYeux(base, M_PI / 2., 200., 0.3);

        Bestiole* baseCible = new Bestiole();
        baseCible->initCoords(150, 100);
        IBestiole* cible = new DecCamouflage(baseCible, 0.8); // psi=0.8 > gammaY=0.3

        vector<IBestiole*> toutes = {bYeux, cible};
        auto detectees = bYeux->getBestiolesDetectees(toutes);
        check(detectees.empty(), "DecYeux ne détecte pas une cible trop camouflée");
        delete bYeux;
        delete cible;
    }

    // ─────────────────────────────────────────
    // TESTS DecOreilles
    // ─────────────────────────────────────────
    cout << "\n-- DecOreilles --" << endl;

    {
        // Cible dans le rayon
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        IBestiole* bO = new DecOreilles(base, 80., 1.0);

        Bestiole* cible = new Bestiole();
        cible->initCoords(150, 100); // dist=50, dans rayon=80

        vector<IBestiole*> toutes = {bO, cible};
        auto detectees = bO->getBestiolesDetectees(toutes);
        check(detectees.size() == 1 && detectees[0]->getId() == cible->getId(),
              "DecOreilles détecte une cible dans le rayon");
        delete bO;
        delete cible;
    }
    {
        // Cible hors du rayon
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        IBestiole* bO = new DecOreilles(base, 30., 1.0);

        Bestiole* cible = new Bestiole();
        cible->initCoords(200, 100); // dist=100, hors rayon=30

        vector<IBestiole*> toutes = {bO, cible};
        auto detectees = bO->getBestiolesDetectees(toutes);
        check(detectees.empty(), "DecOreilles ne détecte pas une cible hors du rayon");
        delete bO;
        delete cible;
    }
    {
        // Cible camouflée (psi > gammaO)
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        IBestiole* bO = new DecOreilles(base, 80., 0.3);

        Bestiole* baseCible = new Bestiole();
        baseCible->initCoords(150, 100);
        IBestiole* cible = new DecCamouflage(baseCible, 0.8); // psi=0.8 > gammaO=0.3

        vector<IBestiole*> toutes = {bO, cible};
        auto detectees = bO->getBestiolesDetectees(toutes);
        check(detectees.empty(), "DecOreilles ne détecte pas une cible trop camouflée");
        delete bO;
        delete cible;
    }
    {
        // Yeux + Oreilles combinés : pas de doublon
        Bestiole* base = new Bestiole();
        base->initCoords(100, 100);
        base->setOrientation(0.0);
        IBestiole* bYeux    = new DecYeux(base, M_PI / 2., 200., 1.0);
        IBestiole* bYeuxO   = new DecOreilles(bYeux, 200., 1.0);

        Bestiole* cible = new Bestiole();
        cible->initCoords(150, 100);

        vector<IBestiole*> toutes = {bYeuxO, cible};
        auto detectees = bYeuxO->getBestiolesDetectees(toutes);
        check(detectees.size() == 1, "Yeux + Oreilles : pas de doublon pour la même cible");
        delete bYeuxO;
        delete cible;
    }

    // ─────────────────────────────────────────
    // BILAN
    // ─────────────────────────────────────────
    cout << "\n=======================" << endl;
    cout << passed << "/" << (passed + failed) << " tests passés" << endl;
    if (failed == 0)
        cout << "Tous les tests sont OK !" << endl;
    else
        cout << failed << " test(s) en échec." << endl;

    return failed == 0 ? 0 : 1;
}
