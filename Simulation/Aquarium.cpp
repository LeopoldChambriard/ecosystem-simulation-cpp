#include "Aquarium.h"
#include "Milieu.h"
#include "Kamikaze.h"
#include "Gregaire.h"


Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl; // Sert à vérifier que le constructeur est appelé (affiche dans la console)

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" ); // Sert à afficher le milieu dans la fenêtre (affiche dans la console)

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::run( void )
{

   cout << "running Aquarium" << endl;

   while ( ! is_closed() )
   {

      // cout << "iteration de la simulation" << endl;

      if ( is_key() ) {
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if (is_keyESC()) close();

// Touche 'K' → transforme une bestiole aléatoire en Kamikaze
if (is_keyK()) {
    auto& bestioles = flotte->getBestioles();
    if (!bestioles.empty()) {
        int idx = rand() % bestioles.size();
        flotte->changerComportement(
            bestioles[idx]->getId(),
            new Kamikaze()
        );
    }
}

// Touche 'G' → transforme une bestiole aléatoire en Grégaire
if (is_keyG()) {
    auto& bestioles = flotte->getBestioles();
    if (!bestioles.empty()) {
        int idx = rand() % bestioles.size();
        flotte->changerComportement(
            bestioles[idx]->getId(),
            new Gregaire()
        );
    }
}
      }

      flotte->step(); // Sert à faire avancer la simulation (affiche dans la console)
      display( *flotte );

      wait( delay );

   } // while

}
