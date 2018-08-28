#include <time.h>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 

#include "constante.h"
#include "jeu.h"
#include "music.h"
#include "edition.h"
#include "clavier.h"
#include "carreMenu.h"
#include "lecteur.h"
#include "aide.h"
#include "apropos.h"

#ifndef ACCUEIL
#define ACCUEIL

class Accueil
{
	public:
		Accueil(SDL_Joystick *joystick);
		~Accueil();
		void afficher(SDL_Surface *ecran,Music &music);
		void gestionTouches(SDL_Surface *ecran,Music &music);
		void gestionEvent();
		void blitter(SDL_Surface *ecran);
		bool pointComplet(int x1,int y1,int x2,int y2,int w,int h);
	private:
		vector<Personnage *> carres;
		SDL_Surface *s_menu, *s_fond,*s_facile,*s_normal,*s_difficile,*s_sourie;
		SDL_Rect r_menu, r_fond,r_facile,r_normal,r_difficile,r_sourie;
		bool continuer,joystickDActif,joystickGActif,joystickBActif,joystickHActif;
		SDL_Event event;
		Clavier in;
		int m_level;
		int m_tempsActuel,m_tempsPrecedent,m_intervalTemps;
		SDL_Joystick *m_joystick;
};
#endif