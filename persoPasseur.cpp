#include "persoPasseur.h"

PersoPasseur::PersoPasseur(int level) :Personnage()
{
	m_persos.resize(1,NULL);
	m_persos[D1] = IMG_Load("images/passeur.png");

	m_nom="PERSOPASSEUR";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;

	m_vitesseHnormal=2;
	m_vitesseH=m_vitesseHnormal+level;
	m_monte=false;
	m_toucheDActif=true;
	m_toucheGActif=false;
}
PersoPasseur::~PersoPasseur()
{
}

int PersoPasseur::getPoints()
{
	return m_points;
}

void PersoPasseur::recevoirDegat(int degat)
{
	
}

void PersoPasseur::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void PersoPasseur::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy);
	deplacer(vx,vy,niveau);
}

void PersoPasseur::recupererVecteur(int *vx, int *vy)
{
	if(ancien.x==m_rect.x)
	{
		m_toucheDActif=!m_toucheDActif;
	}
	else if(ancien.x < m_rect.x)
	{
		m_toucheDActif=true;
	}
	else
	{
		m_toucheDActif=false;
	}
	if(m_toucheDActif)
	{
		*vx=m_vitesseH;
	}
	else
	{
		*vx=-m_vitesseH;
	}
	ancien.x=m_rect.x;
}

void PersoPasseur::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	essaieDeplacer(vx,vy,niveau);
}

bool PersoPasseur::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool PersoPasseur::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
{
	int xmin,xmax,ymin,ymax;
	xmin = test.x / TAILLE_BLOC;
	ymin = test.y / TAILLE_BLOC;
	xmax = (test.x + test.w -1) / TAILLE_BLOC;
	ymax = (test.y + test.h -1) / TAILLE_BLOC;
	
	if(ymin < 0)
	{
		m_monte=false;
		m_vitesseV=-m_vitesseS/3;
		return true;
	}
	else if(ymax >= NB_BLOC_HAUTEUR_TOTAL)
	{
		saut=true;
		m_enSaut=false;
		m_vitesseV=m_vitesseS;
		return true;
	}
	else if(xmin <= 0 || xmax >= NB_BLOC_LARGEUR_TOTAL)
		return true;
	
	for(int i=xmin; i <= xmax; i++)
	{
		for(int j=ymin; j <= ymax; j++)
		{

//Debut gestion collision avec le décor
			if (niveau[i][j]==MUR || niveau[i][j]==BRIQUE || niveau[i][j]==SOL || niveau[i][j]==BONUS_OK || niveau[i][j]==BONUS || niveau[i][j]==TERRE || niveau[i][j]==GAZON1 || niveau[i][j]==GAZON2 || niveau[i][j]==GAZON3 || niveau[i][j]==PONDEUR)
			{
				return true;
			}
		}
	}
//Fin gestion collision avec le décor

	return false;
}