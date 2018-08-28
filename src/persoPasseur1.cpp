#include "PersoPasseur1.h"

PersoPasseur1::PersoPasseur1(int level) :Personnage()
{
	m_persos.resize(1,NULL);
	m_persos[D1] = IMG_Load("images/passeur1.png");

	m_nom="PERSOPASSEUR1";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;

	m_vitesseV=2+level;
	m_monte=false;
	m_toucheDActif=true;
	m_toucheGActif=false;
}
PersoPasseur1::~PersoPasseur1()
{
}

int PersoPasseur1::getPoints()
{
	return m_points;
}

void PersoPasseur1::recevoirDegat(int degat)
{
	
}

void PersoPasseur1::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void PersoPasseur1::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx=0,vy=0;
	recupererVecteur(&vx,&vy);
	deplacer(vx,vy,niveau,perso);
}

void PersoPasseur1::recupererVecteur(int *vx, int *vy)
{
	if(ancien.y==m_rect.y)
	{
		m_monte=true;
		m_toucheBActif=!m_toucheBActif;
	}
	else if(ancien.y < m_rect.y)
	{
		m_monte=false;
		m_toucheBActif=true;
	}
	else
	{
		m_monte=false;
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

void PersoPasseur1::deplacer(int vx,int vy,const vector<vector<int> > &niveau,Personnage &perso)
{
	essaieDeplacer(vx,vy,niveau,perso);
}

bool PersoPasseur1::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau,Personnage &perso)
{
	SDL_Rect test;
	test=m_rect;
	test.x += vx;
	test.y += vy;
	if(!collision(niveau,test,perso))
	{
		m_rect=test;
		m_monte=false;
		return true;
	}
	m_monte=true;
	return false;
}

bool PersoPasseur1::collision(const vector<vector<int> > &niveau, SDL_Rect &test,Personnage &perso)
{
	int xmin,xmax,ymin,ymax;
	xmin = test.x / TAILLE_BLOC;
	ymin = test.y / TAILLE_BLOC;
	xmax = (test.x + test.w -1) / TAILLE_BLOC;
	ymax = (test.y + test.h -1) / TAILLE_BLOC;
	
	if(ymin < 2)
	{
		return true;
	}
	else if(ymax >= NB_BLOC_HAUTEUR_TOTAL)
	{
		return true;
	}
	else if(xmin <= 0 || xmax >= NB_BLOC_LARGEUR_TOTAL)
		return true;
	else if(!m_toucheBActif && (niveau[xmin][ymin-2]==MUR ||niveau[xmin][ymin-2]==BRIQUE || niveau[xmin][ymin-2]==SOL || niveau[xmin][ymin-2]==BONUS_OK || niveau[xmin][ymin-2]==BONUS || niveau[xmin][ymin-2]==TERRE || niveau[xmin][ymin-2]==GAZON1 || niveau[xmin][ymin-2]==GAZON2 || niveau[xmin][ymin-2]==GAZON3))
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