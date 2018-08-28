#include "personnage.h"



#ifndef PERSOPASSEUR1
#define PERSOPASSEUR1

class PersoPasseur1:public Personnage
{
	public:
		PersoPasseur1(int level=0);
		~PersoPasseur1();
		virtual void evoluer(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy);
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau,Personnage &perso);
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau,Personnage &perso);
		virtual bool collision(const vector<vector<int> >& niveau,SDL_Rect &test,Personnage &perso);
		virtual void recevoirDegat(int degat);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual int getPoints();
	private:
		SDL_Rect ancien;
};
#endif