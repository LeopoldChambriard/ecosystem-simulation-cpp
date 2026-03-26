#ifndef _CONFIGURATIONPOPULATION_H_
#define _CONFIGURATIONPOPULATION_H_

#include "IConfiguration.h"
#include <vector>
#include <string>

struct EntreeConfig {
    std::string nomComportement;
    double      pourcentage;
};

class ConfigurationPopulation : public IConfiguration
{
private:
    std::vector<EntreeConfig> repartition;
    ParamsSimulation          params;
    double _probaYeux, _probaOreilles, _probaCamouflage, _probaCarapace, _probaNageoires;

public:
    ConfigurationPopulation();
    void setProbaYeux(double p) { _probaYeux = p; }
    void setProbaOreilles(double p) { _probaOreilles = p; }
    void setProbaCamouflage(double p) { _probaCamouflage = p; }
    void setProbaCarapace(double p)   { _probaCarapace   = p; }
    void setProbaNageoires(double p) { _probaNageoires = p; }
    void ajouterComportement(const std::string& nom, double pct);
    IComportement* tirerComportement() const override;
    const ParamsSimulation& getParams()         const override { return params; }
    double probaYeux() const override { return _probaYeux; }
    double probaOreilles() const override { return _probaOreilles; }
    double probaCamouflage() const override { return _probaCamouflage; }
    double probaCarapace()   const override { return _probaCarapace;   }
    double probaNageoires() const override { return _probaNageoires; }
};

#endif