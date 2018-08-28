#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/SDL_ttf.h>
#include "constante.h"
#include "clavier.h"
#include "music.h"

using namespace std;

#ifndef PERSONNAGE
#define PERSONNAGE
#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

class Personnage
{
	public:
		Personnage();
		virtual ~Personnage();
		virtual void evoluer(Clavier &in,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll){};
		virtual void deplacer(int vx,int vy,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll){};
		virtual bool essaieDeplacer(int vx,int vy,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll){return true;};
		virtual void recupererVecteur(Clavier &in,int *vx,int *vy,Music &music){};
		virtual bool collision(vector<vector<int> >& niveau,vector<Personnage*>& persos,SDL_Rect &test,Music &music,int xscroll, int yscroll){return true;};
//Start:Définition des méthodes propres aux ennemies
		virtual void evoluer(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll ){};
		virtual void recupererVecteur(int *vx,int *vy){};
		virtual void recupererVecteur(int *vx,int *vy,Personnage &perso){};
		virtual void deplacer(int vx,int vy,const vector<vector<int> >& niveau){};
		virtual bool essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau){return true;};
		virtual bool collision(const vector<vector<int> >& niveau,SDL_Rect &test){return true;};
//End:Définition des méthodes propres aux ennemies
//Start:Définition des méthodes propres aux Carres
		virtual void evoluer(vector<Personnage*>& carre,Music &music){};
		virtual void deplacer(int vx,int vy,vector<Personnage*>& carre,Music &music){};
		virtual bool essaieDeplacer(int vx,int vy,vector<Personnage*>& carre,Music &music){return true;};
		virtual void recupererVecteur(int *vx,int *vy,Music &music){};
		virtual bool collision(vector<Personnage*>& carre,SDL_Rect &test,Music &music){return true;};
		virtual void afficher(SDL_Surface *ecran){};
		virtual Personnage* recupererPerso(vector<Personnage *>& persos,int x,int y);
//End:Définition des méthodes propres aux Carres
		int collision(Personnage *perso,int position);
		Personnage* recupererPerso(vector<Personnage *>& persos,int x,int y,int xscroll, int yscroll);
		Personnage* recupererPerso(vector<Personnage *>& persos,Personnage *moi,int x,int y,int xscroll, int yscroll);
		virtual void recevoirDegat(int degat);
		virtual void lanser(){};
		virtual void mourir();
		void enrichir();
		void updatePoints(int points);
		int pieceBonus();
		virtual int lotterie();
		bool estVivant();
		bool estTransparent();
		int rand_n(int n);
		bool estSurEcran(int xscroll,int yscroll);
		virtual void afficher(SDL_Surface *ecran,int xscroll, int yscroll);
		virtual void sauter(int *vy);
		int getPieces();
		int getVies();
		int getIndex();
		virtual int getPoints();
		int getTransparent();
		string getNom();
		void updateMission(bool mission);
		bool getMission();
		void setTransparent(int valeur);
		void setRect(SDL_Rect &rect);
		void setPosAffPoints(int x,int y);
		void setVitesse(int vv,int vh);
		void setIndex(int index);
		SDL_Rect getRect();
		int getVitesseV();
		int getVitesseH();
		int getPouvoir();
		bool getMonte();
		bool getToucheDActif();
		bool getToucheBActif();
		void setToucheDActif();
		void setMonte(bool monte);
	protected:
		SDL_Rect m_rect,m_posAffPoints;
		int m_vitesseV,m_vitesseH,m_vitesseHnormal,m_vitesseS,m_gravite,m_pouvoirSaut,m_pouvoirTrou;
		int m_transparent,m_piecesMur,m_pieces,m_points,m_vies,m_level,m_index,m_temps;
		bool m_enSaut,m_monte,m_toucheSautActif,m_toucheVHActif,saut,repeatSaut,
			m_mission,m_toucheGActif,m_toucheDActif,m_toucheBActif;
		vector<SDL_Surface *>m_persos;
		SDL_Surface *m_persoActuel,*m_affPoints;
		string m_nom;
};
#endif