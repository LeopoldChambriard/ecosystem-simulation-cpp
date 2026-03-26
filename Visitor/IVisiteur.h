#ifndef _IVISITEUR_H_
#define _IVISITEUR_H_

// Déclarations anticipées de tous les types visités
class Bestiole;
class DecCamouflage;
class DecCarapace;
class DecOreilles;
class DecYeux;
class DecNageoires;

class IVisiteur
{
public:
    virtual ~IVisiteur() {}

    virtual void visiter(Bestiole &) = 0;
    virtual void visiter(DecCamouflage &) = 0;
    virtual void visiter(DecCarapace &) = 0;
    virtual void visiter(DecYeux &) = 0;
    virtual void visiter(DecOreilles &) = 0;
    virtual void visiter(DecNageoires &) = 0;
};

#endif