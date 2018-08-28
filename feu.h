#include "personnage.h"

#ifndef FEU
#define FEU

class Feu:public Personnage
{
	public:
		Feu(int level=0);
		Feu(bool position,SDL_Rect pos,int level=0);
		~Feu();
		virtual void evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy);
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau);
		virtual bool collision(const vector<vector<int> >& niveau,SDL_Rect &test);
		virtual void recevoirDegat(int degat);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual int lotterie();
	private:
};
#endif