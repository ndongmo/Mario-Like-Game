#include <vector>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/SDL_ttf.h>

using namespace std;

#include "constante.h"
#include "music.h"
#include "clavier.h"

#ifndef LECTEUR
#define LECTEUR

class Lecteur
{
	public:
		Lecteur();
		~Lecteur();
		void initPosition();
		void gestionEvent(Music & music);
		void gestionVolume(Music & music,int vol);
		void blitter(SDL_Surface *ecran);
		void afficher(SDL_Surface *ecran,Music & music);
		void updateEvents();
		void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		bool pointComplet(int x1,int y1,int x2,int y2,int w,int h);
	private:
		SDL_Surface *m_effet,*m_touches,*m_volume,*m_menu;
		SDL_Rect m_posEffet,m_posTouches,m_posVolume,m_posMenu;
		vector<SDL_Surface *>m_sons;
		vector<SDL_Rect *>m_posSons;
		SDL_Event m_event;
		Clavier m_in;
		float m_ratio,*spectre;
		int m_interval,hauteurBarre, tempsActuel, tempsPrecedent;
		bool m_continuer,appuyer;
};
#endif