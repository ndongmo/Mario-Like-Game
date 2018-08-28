#include "personnage.h"
#include "boulet.h"


#ifndef PERSOCANON1
#define PERSOCANON1

class PersoCanon1:public Personnage
{
	public:
		PersoCanon1(int level=0);
		~PersoCanon1();
		virtual void evoluer(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy,Personnage &perso);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual int getPoints();
		virtual void recevoirDegat(int degat){};
		virtual void lancer(vector<Personnage*>& persos);
		bool hazard();
	private:
		int interval;
};
#endif