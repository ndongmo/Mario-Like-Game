#include "personnage.h"
#include "pierre.h"


#ifndef PERSOPRINCIPAL
#define PERSOPRINCIPAL

class PersoPrincipal:public Personnage
{
	public:
		PersoPrincipal();
		~PersoPrincipal();
		virtual void evoluer(Clavier &in,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll);
		virtual void deplacer(int vx,int vy,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll);
		virtual bool essaieDeplacer(int vx,int vy,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll,int *x,int *y);
		virtual void recupererVecteur(Clavier &in,int *vx,int *vy,Music &music,vector<Personnage*>& persos);
		virtual bool collision(vector<vector<int> >& niveau,vector<Personnage*>& persos,SDL_Rect &test,Music &music,int xscroll, int yscroll,int *vx,int *vy);
		virtual void recevoirDegat(int degat);
		virtual void lancer(vector<Personnage*>& persos);
		void setEtat(int etat);
		void grandir(SDL_Rect &rect);
		void retrecir();
		int getEtat();
		bool getPosition();
	private:
		int m_etat,m_interval;
		bool m_position;
};
#endif