#include "personnage.h"

#ifndef CARREMENU
#define CARREMENU

class CarreMenu:public Personnage
{
	public:
		CarreMenu(string nom,char *file,int avX,int avY,int index);
		~CarreMenu();
		virtual void evoluer(vector<Personnage*>& carre,Music &music);
		virtual void deplacer(int vx,int vy,vector<Personnage*>& carre,Music &music);
		virtual bool essaieDeplacer(int vx,int vy,vector<Personnage*>& carre,Music &music);
		virtual void recupererVecteur(int *vx,int *vy,Music &music);
		virtual bool collision(vector<Personnage*>& carre,SDL_Rect &test,Music &music);
		virtual void afficher(SDL_Surface *ecran);
		bool hazard(int tp);
	private:
		bool avanceX,avanceY;
};
#endif