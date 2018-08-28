#include "personnage.h"
#include "feu.h"


#ifndef PERSOBOSS2
#define PERSOBOSS2

class PersoBoss2:public Personnage
{
	public:
		PersoBoss2(int level=0);
		~PersoBoss2();
		virtual void evoluer(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy,Personnage &perso);
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool collision(const vector<vector<int> >& niveau,SDL_Rect &test);
		virtual void recevoirDegat(int degat);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual int getPoints();
		virtual void lancer(vector<Personnage*>& persos);
		bool hazard();
	private:
		SDL_Rect ancien;
		TTF_Font *m_police;
		SDL_Color m_couleurNoire,m_couleurBlanche;
		char m_tabPoints[10];
};
#endif