#include "persoPiquant.h"

PersoPiquant::PersoPiquant(int level) :Personnage()
{
	m_persos.resize(1,NULL);
	m_persos[D1] = IMG_Load("images/piquant.png");

	m_nom="PERSOPiQUANT";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;
	m_vitesseS=1;
	m_vitesseV=m_vitesseS+level;

	m_toucheBActif=true;
}
PersoPiquant::~PersoPiquant()
{
}

int PersoPiquant::getPoints()
{
	return m_points;
}

void PersoPiquant::recevoirDegat(int degat)
{
	
}

void PersoPiquant::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void PersoPiquant::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx=0,vy;
	recupererVecteur(&vx,&vy);
	sauter(&vy);
	deplacer(vx,vy,niveau);
}

void PersoPiquant::recupererVecteur(int *vx, int *vy)
{
	if(ancien.y==m_rect.y)
	{
		m_toucheBActif=!m_toucheBActif;
		m_vitesseV=m_vitesseS;
	}
	else if(ancien.y < m_rect.y)
	{
		m_toucheBActif=true;
	}
	else
	{
		m_toucheBActif=false;
	}
	if(m_toucheBActif)
	{
		*vy=m_vitesseV;
	}
	else
	{
		*vy=-m_vitesseV;
	}
	ancien.y=m_rect.y;
}

void PersoPiquant::sauter(int *vy)
{
	if(m_toucheBActif)
	{
		*vy+=5;
	}
	else
	{
		*vy-=2;
	}
}

void PersoPiquant::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	essaieDeplacer(vx,vy,niveau);
}

bool PersoPiquant::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool PersoPiquant::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
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