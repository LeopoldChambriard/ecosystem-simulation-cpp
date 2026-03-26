#ifndef _ETATSIMULATION_H_
#define _ETATSIMULATION_H_
#include "IObservateur.h"
#include <vector>
#include <string>
#include <iostream>
struct SnapshotBestiole {
    int id, x, y, age;
    double vitesse, orientation, camouflage;
    std::string comportement;
};
struct EtatSimulation {
    int pas, nbNaissances, nbMorts;
    std::vector<SnapshotBestiole> bestioles;
};
class JournalSimulation : public IObservateur {
    std::vector<EtatSimulation> historique;
    EtatSimulation courant;
public:
    JournalSimulation();
    void notifier(const Evenement& e) override;
    void ajouterSnapshot(const SnapshotBestiole& s);
    void validerPas();
    const std::vector<EtatSimulation>& getHistorique() const { return historique; }
    void afficherBilan() const;
};
#endif

