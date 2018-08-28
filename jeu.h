#include <vector>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/SDL_ttf.h>
#include "constante.h"
#include "carte.h"
#include "fichier.h"
#include "persoPrincipal.h"
#include "persoBandit.h"
#include "persoTortue.h"
#include "persoPiquant.h"
#include "persoPiquant1.h"
#include "persoSuiveur.h"
#include "persoPasseur.h"
#include "persoPasseur1.h"
#include "persoSauteur.h"
#include "persoCassable.h"
#include "persoBoss.h"
#include "persoBoss2.h"
#include "persoDinau.h"
#include "persoCanard.h"
#include "persoCanon1.h"
#include "persoCanon2.h"
#include "music.h"
#include "clavier.h"

using namespace std;

#ifndef JEU
#define JEU

class Jeu
{
	public:
		Jeu(int level);
		~Jeu();
		void jouer(SDL_Surface *ecran,Music &music);
		void updateEvents();
		void updateMenu();
		void controlEtat(SDL_Surface *ecran,Music &music);
		void initialiserNiveau();
		void gestionBandits();
		void gestionMario(SDL_Surface *ecran,Music &music);
		void updateJeu(SDL_Surface *ecran,int type,Music &music);
		void afficherBandits(SDL_Surface *ecran);
		void afficherMenu(SDL_Surface *ecran);
		void afficherScene(SDL_Surface *ecran,int type,Music &music);
		void pause();
		void quitter();
	private:
		Carte m_carte;
		Fichier m_fichier;
		Clavier m_in;
		PersoPrincipal m_mario;
		vector<Personnage *> m_bandit1s;
		SDL_Event m_event;
		SDL_Surface *m_titre;
		bool m_continuer;
		bool m_pause;
		vector<vector<int> > m_niveau;
		vector<SDL_Rect> m_posObjets;
		vector<SDL_Surface *> m_objets;
		TTF_Font *m_police;
		SDL_Color m_couleurNoire,m_couleurBlanche;
		char m_tempsJeu[20],m_nbreVie[10],m_nbrePiece[10],m_point[20],m_tabTitre[50];
		int m_tempsActuel,m_tempsPrecedent,m_intervalTemps,m_temps,m_getstickTemps,m_level;
		
};
#endif