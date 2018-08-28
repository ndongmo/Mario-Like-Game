#include "personnage.h"

#ifndef PERSOTORTUE
#define PERSOTORTUE

class PersoTortue:public Personnage
{
	public:
		PersoTortue(int level=0);
		~PersoTortue();
		virtual void evoluer(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy);
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool collision(const vector<vector<int> >& niveau,SDL_Rect &test);
		virtual void recevoirDegat(int degat);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual int getPoints();
	private:
		SDL_Rect ancien;
		TTF_Font *m_police;
		SDL_Color m_couleurNoire,m_couleurBlanche;
		char m_tabPoints[10];
};
#endif