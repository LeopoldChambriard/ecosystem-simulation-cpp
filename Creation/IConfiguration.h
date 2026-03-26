#ifndef _ICONFIGURATION_H_
#define _ICONFIGURATION_H_

class IComportement;
struct ParamsSimulation
{
    // Yeux
    double alphaMin = 0.3, alphaMax = 1.0;
    double deltaYMin = 100., deltaYMax = 200.; 
    double gammaYMin = 0.3, gammaYMax = 1.0;

    // Oreilles
    double deltaOMin = 30.,  deltaOMax = 80.;
    double gammaOMin = 0.3, gammaOMax = 1.0;

    // Paramètres de la simulation, à compléter au besoin (taux de naissance, clonage, collision, etc..)
    // Accessoires
    double psiMin = 0.2, psiMax = 0.9;

    double omegaMin = 1.5, omegaMax = 3.0;
    double etaMin   = 1.2, etaMax   = 2.0;
    double nuMin = 1.2, nuMax = 2.5; // Pour les nageoires
};

/**
 * @class IConfiguration
 * @brief Interface abstraite pour la gestion des configurations de comportement.
 * 
 * Cette classe définit un contrat pour les implémentations concrètes qui fournissent
 * des comportements configurables. Elle utilise le pattern Strategy pour permettre
 * l'extraction dynamique de comportements.
 * 
 * @note Cette classe est abstraite et ne peut pas être instanciée directement.
 *       Les classes dérivées doivent implémenter la méthode tirerComportement().
 */
class IConfiguration
{
public:
    virtual ~IConfiguration() {}

    virtual IComportement *tirerComportement() const = 0;
    virtual const ParamsSimulation &getParams() const = 0;

    virtual double probaYeux() const = 0;
    virtual double probaOreilles() const = 0;
    virtual double probaCamouflage() const = 0;
    virtual double probaCarapace()   const = 0;
    virtual double probaNageoires() const = 0;
};

#endif