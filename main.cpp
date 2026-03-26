#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "ConfigurationPopulation.h"

#include <iostream>
using namespace std;

int main()
{
    ConfigurationPopulation config;
    config.ajouterComportement("Gregaire", 0.20);
    config.ajouterComportement("Peureuse", 0.20);
    config.ajouterComportement("Kamikaze", 0.20);
    config.ajouterComportement("Prevoyante", 0.20);
    config.ajouterComportement("Neutre", 0.10);
    config.ajouterComportement("PersonnalitesMultiples", 0.10);

    config.setProbaYeux(0.6);
    config.setProbaOreilles(0.6);
    config.setProbaCamouflage(0.2);
    config.setProbaCarapace(0.2);
    config.setProbaNageoires(0.4);

    BestioleFactory::getInstance()->setConfiguration(&config);

    Aquarium ecosysteme(1280, 720, 30);
    JournalSimulation journal;
    ecosysteme.getMilieu().ajouterObservateur(&journal);

    auto population = BestioleFactory::getInstance()->creerPopulation(20, 1280, 720);
    for (auto *b : population)
        ecosysteme.getMilieu().addMember(b);

    ecosysteme.run();
    return 0;
}