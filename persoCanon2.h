#include "personnage.h"
#include "boulet.h"


#ifndef PERSOCANON2
#define PERSOCANON2

class PersoCanon2:public Personnage
{
	public:
		PersoCanon2(int level=0);
		~PersoCanon2();
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