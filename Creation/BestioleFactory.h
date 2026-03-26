#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include "IBestiole.h"
#include "IConfiguration.h"
#include <vector>

/**
 * @brief Fabrique de bestioles — Pattern Singleton + Factory Method.
 * Unique point de création des bestioles, délègue le tirage
 * du comportement à une IConfiguration injectée.
 */
class BestioleFactory
{
    static BestioleFactory *instance; ///< Instance unique du Singleton
    IConfiguration *config = nullptr; ///< Configuration des comportements

    BestioleFactory() {}                                       // Constructeur privé
    BestioleFactory(const BestioleFactory &)            = delete; // Copie interdite
    BestioleFactory &operator=(const BestioleFactory &) = delete; // Affectation interdite

public:
    /** @brief Retourne l'instance unique (création lazy). */
    static BestioleFactory *getInstance();

    /** @brief Injecte la configuration de population. */
    void setConfiguration(IConfiguration *c) { config = c; }

    /** @brief Crée une bestiole positionnée aléatoirement dans le milieu.
     *  L'appelant est responsable du pointeur retourné. */
    IBestiole *creer(int xLim, int yLim) const;

    /** @brief Crée @p nb bestioles en un seul appel. */
    std::vector<IBestiole *> creerPopulation(int nb, int xLim, int yLim) const;
};

#endif