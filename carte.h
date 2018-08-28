#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <vector>
#include "constante.h"
#include "clavier.h"

using namespace std;

#ifndef CARTE
#define CARTE

class Carte
{
	public:
		Carte();
		~Carte();
		void deplacer();
		void evoluer(Clavier &in,SDL_Rect &rectPerso);
		void afficher(SDL_Surface *ecran,const vector<vector<int> >& niveaux);
		void afficherTous(SDL_Surface *ecran,const vector<vector<int> >& niveaux);
		bool rechercher(const vector<vector<int> >& niveau,int index);
		int getXscroll();
		int getYscroll();
		void setXscroll(int xscroll);
		void setYscroll(int yscroll);
		void inXscroll();
		void deXscroll();
		void inYscroll();
		void deYscroll();
	private:
		int m_xscroll,m_yscroll;
		int m_pasX,m_pasY;
		SDL_Surface *m_mur, *m_nuage, *m_sol, *m_brique, *m_herbe, *m_bonus, *m_porte,
			*m_pieceBlit, *m_etoile, *m_bonusOk, *m_mario, *m_bandit1, *m_piquant, *m_suiveur,
			*m_sauteur, *m_pondeur, *m_fleur, *m_passeur, *m_gazon1,*m_gazon2, *m_gazon3, 
			*m_gazon11, *m_gazon22, *m_gazon33, *m_terre, *m_boss, *m_tortue, *m_passeur1,
			*m_cassable, *m_piquant1, *m_boss2, *m_canon1, *m_canon2, *m_canard, *m_dinau;
};
#endif