#include "persoVie.h"

PersoVie::PersoVie() :Personnage()
{
	m_persos.resize(1,NULL);
	m_persos[D1] = SDL_LoadBMP("images/vie.bmp");

	m_nom="PERSOVIE";
	m_vies=1;
	m_vitesseH=6;
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;

	m_toucheDActif=true;
	m_toucheGActif=false;
}
PersoVie::~PersoVie()
{
}

int PersoVie::getPoints()
{
	return m_points;
}

void PersoVie::recevoirDegat(int degat)
{
	m_vies-=degat;
	m_transparent=0;
}

void PersoVie::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;

	SDL_SetColorKey(m_persoActuel, SDL_SRCCOLORKEY, SDL_MapRGB(m_persoActuel->format, 255, 255, 0));
	SDL_SetAlpha(m_persoActuel, SDL_SRCALPHA, m_transparent);
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void PersoVie::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy,perso);
	sauter(&vy);
	deplacer(vx,vy,niveau);
}

void PersoVie::recupererVecteur(int *vx, int *vy,Personnage &perso)
{
	SDL_Rect pos;
	pos=perso.getRect();
	if(m_level == DIFFICILE)
	{
		if(pos.x==m_rect.x)
		{
			m_toucheDActif=!m_toucheDActif;
		}
		else if(pos.x < m_rect.x)
		{
			m_toucheDActif=true;
		}
		else
		{
			m_toucheDActif=false;
		}
		if(m_toucheDActif)
		{
			*vx=m_vitesseH+2;
		}
		else
		{
			*vx=-m_vitesseH-2;
		}
	}
	else
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
}

void PersoVie::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	if (vx >= TAILLE_BLOC || vy >= TAILLE_BLOC)
	{
		deplacer(vx/2,vy/2,niveau);
		//deplacer(vx-vx/2,vy-vy/2,niveau);
		return;
	}
	if (essaieDeplacer(vx,vy,niveau))
		return;
// affine
	for(int i=0;i<ABS(vx);i++)
	{
		if (!essaieDeplacer(SGN(vx),0,niveau))
			break;
	}
	for(int i=0;i<ABS(vy);i++)
	{
		if (!essaieDeplacer(0,SGN(vy),niveau))
			break;			
	}
}

bool PersoVie::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool PersoVie::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
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
		m_transparent=0;
		return false;
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
				m_vitesseV=m_vitesseS;
				return true;
			}
		}
	}
//Fin gestion collision avec le décor

	return false;
}