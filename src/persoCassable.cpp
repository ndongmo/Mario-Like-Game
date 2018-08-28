#include "persoCassable.h"

PersoCassable::PersoCassable(int level) :Personnage()
{
	m_persos.resize(1,NULL);
	m_persos[D1] = IMG_Load("images/briqueCassable.png");

	m_nom="PERSOCASSABLE";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;
	m_vitesseV=5+level;

	m_toucheBActif=false;
	m_points=10;
	m_police=TTF_OpenFont("polices/times.TTF",10);
	m_affPoints=NULL;
}
PersoCassable::~PersoCassable()
{
	SDL_FreeSurface(m_affPoints);
	TTF_CloseFont(m_police);
}

int PersoCassable::getPoints()
{
	return m_points;
}

void PersoCassable::recevoirDegat(int degat)
{
	
}

void PersoCassable::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void PersoCassable::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	if(m_monte)
	{
		int vx=0,vy=0;
		vy=m_vitesseV;
		essaieDeplacer(vx,vy,niveau);
	}
}

void PersoCassable::recupererVecteur(int *vx, int *vy,Personnage &perso)
{
	if(m_monte)
	{
		*vy=m_vitesseV;
	}
}


void PersoCassable::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	essaieDeplacer(vx,vy,niveau);
}

bool PersoCassable::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	SDL_Rect test;
	test=m_rect;
	test.x += vx;
	test.y += vy;
	if(!collision(niveau,test))
	{
		m_rect=test;
		return true;
	}
	return false;
}

bool PersoCassable::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
{
	int xmin,xmax,ymin,ymax;
	xmin = test.x / TAILLE_BLOC;
	ymin = test.y / TAILLE_BLOC;
	xmax = (test.x + test.w -1) / TAILLE_BLOC;
	ymax = (test.y + test.h -1) / TAILLE_BLOC;
	
	if(ymin < 0 || ymax >= NB_BLOC_HAUTEUR_TOTAL)
	{
		m_transparent=0;
		m_vies=0;
		return true;
	}
	for(int i=xmin; i <= xmax; i++)
	{
		for(int j=ymin; j <= ymax; j++)
		{

//Debut gestion collision avec le décor
			if (niveau[i][j]==MUR || niveau[i][j]==BRIQUE || niveau[i][j]==SOL || niveau[i][j]==BONUS_OK || niveau[i][j]==BONUS || niveau[i][j]==TERRE || niveau[i][j]==GAZON1 || niveau[i][j]==GAZON2 || niveau[i][j]==GAZON3 || niveau[i][j]==PONDEUR)
			{
				m_transparent=0;
				m_vies=0;
				return true;
			}
		}
	}
//Fin gestion collision avec le décor

	return false;
}