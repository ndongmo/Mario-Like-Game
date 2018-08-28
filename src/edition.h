#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/SDL_ttf.h>
#include <SDL1/fmod.h>

using namespace std;

#include "constante.h"
#include "clavier.h"
#include "fichier.h"
#include "carte.h"
#include "music.h"

#ifndef EDITION
#define EDITION

class Edition
{
	public:
		Edition();
		~Edition();
		void editer(SDL_Surface *ecran, Music &music);
		void updateEvents(Music &music);
		void init(Music &music);
		void initialiserEdition(Music &music);
		void initialiserPosObjets();
		void modifTexte();
		void gestionTouche(Music &music);
		void gestionMotion();
		void gestionClick(Music &music);
		void gestionMenu(Music &music);
		void gestionDivers(int i,Music &music);
		bool point(int x1,int y1,int x2,int y2);
		bool pointComplet(int x1,int y1,int x2,int y2,int w,int h);
		void afficherObjets(SDL_Surface *ecran);
	private:
		Carte m_carte;
		Fichier m_fichier;
		vector<vector <int> >m_niveau;
		vector<SDL_Surface *> m_objets,m_objetsJeu;
		vector<SDL_Rect>m_posObjets,m_posObjetsJeu;
		SDL_Surface *m_menu,*m_objetTemps,*m_objetRed,*m_objetGreen,*m_objetBlue,
			*m_objetEnCour,*m_objetMusic;
		Clavier m_in;
		SDL_Event m_event;
		bool m_continuer,m_clickDroitEnCour,m_clickGaucheEnCour;
		bool m_affObjetEnCour;
		SDL_Rect m_posMenu,m_posTemps,m_posRed,m_posGreen,m_posBlue,m_posMusic,m_posObjetEnCour;
		TTF_Font *m_police;
		SDL_Color m_couleurNoire,m_couleurBlanche;
		char m_tempsJeu[10],m_red[10],m_green[10],m_blue[10],m_music[50];
		int m_indexEnCour;
		
};
#endif