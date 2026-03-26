#include "JournalSimulation.h"
#include <iostream>

using namespace std;

JournalSimulation::JournalSimulation()
{
    courant.pas          = 0;
    courant.nbNaissances = 0;
    courant.nbMorts      = 0;
}

void JournalSimulation::notifier(const Evenement& e)
{
    switch (e.type) {
        case TypeEvenement::NAISSANCE:
            courant.nbNaissances++;
            break;
        case TypeEvenement::MORT:
            courant.nbMorts++;
            break;
        case TypeEvenement::PAS_SIMULATION:
            validerPas();
            courant.pas = e.pas + 1;
            courant.nbNaissances = 0;
            courant.nbMorts      = 0;
            courant.bestioles.clear();
            break;
        default:
            break;
    }
}

void JournalSimulation::ajouterSnapshot(const SnapshotBestiole& s)
{
    courant.bestioles.push_back(s);
}

void JournalSimulation::validerPas()
{
    historique.push_back(courant);
}

void JournalSimulation::afficherBilan() const
{
    cout << "=== BILAN SIMULATION ===" << endl;
    cout << "Nombre de pas : " << historique.size() << endl;
    if (!historique.empty()) {
        const auto& dernier = historique.back();
        cout << "Population finale : " << dernier.bestioles.size() << " bestioles" << endl;
        int totalNaissances = 0, totalMorts = 0;
        for (auto& e : historique) {
            totalNaissances += e.nbNaissances;
            totalMorts      += e.nbMorts;
        }
        cout << "Total naissances : " << totalNaissances << endl;
        cout << "Total morts      : " << totalMorts      << endl;
    }
    cout << "========================" << endl;
}
