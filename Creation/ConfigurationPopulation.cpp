#include "ConfigurationPopulation.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include "PersonnalitesMultiples.h"
#include <cstdlib>

ConfigurationPopulation::ConfigurationPopulation()
    : _probaYeux(0.5), _probaOreilles(0.3), _probaCamouflage(0.2), _probaCarapace(0.25), _probaNageoires(0.3)
{
}

void ConfigurationPopulation::ajouterComportement(const std::string &nom, double pct)
{
    repartition.push_back({nom, pct});
}

IComportement *ConfigurationPopulation::tirerComportement() const
{
    if (repartition.empty())
        return nullptr;

    double r = static_cast<double>(rand()) / RAND_MAX;
    double cumul = 0.;

    for (auto &e : repartition)
    {
        cumul += e.pourcentage;
        if (r <= cumul)
        {
            if (e.nomComportement == "Gregaire")
                return new Gregaire();
            if (e.nomComportement == "Peureuse")
                return new Peureuse();
            if (e.nomComportement == "Kamikaze")
                return new Kamikaze();
            if (e.nomComportement == "Prevoyante")
                return new Prevoyante();
            if (e.nomComportement == "Neutre")
                return nullptr;
            if (e.nomComportement == "PersonnalitesMultiples")
                return new PersonnalitesMultiples();
        }
    }
    return nullptr;
}