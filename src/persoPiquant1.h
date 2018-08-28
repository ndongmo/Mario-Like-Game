#include "personnage.h"



#ifndef PERSOPIQUANT1
#define PERSOPIQUANT1

class PersoPiquant1:public Personnage
{
	public:
		PersoPiquant1(int level=0);
		~PersoPiquant1();
		virtual void evoluer(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy,Personnage &perso);
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool collision(const vector<vector<int> >& niveau,SDL_Rect &test);
		virtual void recevoirDegat(int degat);
		virtual void sauter(int *vy);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual int getPoints();
	private:
		SDL_Rect ancien;
};
#endif