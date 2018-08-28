#include "personnage.h"

#ifndef PIERRE
#define PIERRE

class Pierre:public Personnage
{
	public:
		Pierre(bool position);
		~Pierre();
		virtual void evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll);
		virtual void recupererVecteur(int *vx,int *vy);
		virtual bool collision(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,SDL_Rect &test,int xscroll, int yscroll);
		virtual void afficher(SDL_Surface *ecran,int xscroll,int yscroll);
		virtual void recevoirDegat(int degat){};
		
	private:
		bool avanceX,avanceY;
};
#endif