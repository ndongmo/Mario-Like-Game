#include <vector>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/SDL_ttf.h>
#include "constante.h"
#include "music.h"
#include "clavier.h"

using namespace std;

#ifndef APROPOS
#define APROPOS

class Apropos
{
	public:
		Apropos();
		~Apropos();
		void updateEvent();
		void gestionTouches();
		bool pointComplet(int x1,int y1,int x2,int y2,int w,int h);
		void afficher(SDL_Surface *ecran,Music &music);
		void quitter();
	private:
		Clavier in;
		SDL_Event event;
		SDL_Surface *s_fond;
		SDL_Rect r_fond;
		bool continuer;
};
#endif