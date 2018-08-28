#include "persoBoss.h"

PersoBoss::PersoBoss(int level) :Personnage()
{
	m_persos.resize(2,NULL);
	m_persos[D1] = SDL_LoadBMP("images/boss1G.bmp");
	m_persos[D2] = SDL_LoadBMP("images/boss1D.bmp");

	m_nom="PERSOBOSS";
	m_vies=8+level;
	m_vitesseH=1+level;
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;

	m_toucheDActif=false;
	m_toucheGActif=false;
	m_pouvoirSaut=2;
	m_vitesseV=m_vitesseS-4;
	m_points=200;
	m_police=TTF_OpenFont("polices/castelar.TTF",30);
	m_couleurNoire.b=0;m_couleurNoire.g=0;m_couleurNoire.r=0;
	m_couleurBlanche.b=255;m_couleurBlanche.g=255;m_couleurBlanche.r=255;
	sprintf(m_tabPoints, "%d", m_points);
	m_affPoints= TTF_RenderText_Blended(m_police, m_tabPoints, m_couleurNoire);
}
PersoBoss::~PersoBoss()
{
	SDL_FreeSurface(m_affPoints);
	TTF_CloseFont(m_police);
}

int PersoBoss::getPoints()
{
	return m_points;
}

void PersoBoss::recevoirDegat(int degat)
{
	m_vies-=degat;
	if(!estVivant())
	{
		m_transparent=128;
		m_posAffPoints=m_rect;
	}
}

bool PersoBoss::hazard()
{
	int h;
	h=(rand_n(10));
	if(h < 5)
		return false;
	else
		return true;
}

void PersoBoss::lancer(vector<Personnage*>& persos)
{
	persos.push_back(new Feu(m_toucheDActif,m_rect,m_level));
	m_temps=SDL_GetTicks();
}

void PersoBoss::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso,posAff;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	posAff=m_posAffPoints;
	posAff.x-=xscroll;
	posAff.y-=yscroll;

	SDL_SetColorKey(m_persoActuel, SDL_SRCCOLORKEY, SDL_MapRGB(m_persoActuel->format, 255, 255, 0));
	SDL_SetAlpha(m_persoActuel, SDL_SRCALPHA, m_transparent);
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
	if(!estVivant())
		SDL_BlitSurface(m_affPoints,NULL,ecran,&posAff);
}

void PersoBoss::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy,perso);
	sauter(&vy);
	deplacer(vx,vy,niveau);
	
	if((SDL_GetTicks() - m_temps) >= 2000 && hazard())
		lancer(persos);
}

void PersoBoss::recupererVecteur(int *vx, int *vy,Personnage &perso)
{
	SDL_Rect pos;
	pos=perso.getRect();
	if(pos.y+pos.h == m_rect.y+m_rect.h)
	{
		if(pos.x==m_rect.x)
		{
			*vx=0;
			return;
		}
		else if(pos.x < m_rect.x)
		{
			m_toucheDActif=false;
			m_persoActuel = m_persos[D1];
		}
		else
		{
			m_toucheDActif=true;
			m_persoActuel = m_persos[D2];
		}
		if(m_toucheDActif)
		{
			*vx=m_vitesseH;
		}
		else
		{
			*vx=-m_vitesseH;
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
			m_persoActuel = m_persos[D2];
		}
		else
		{
			m_toucheDActif=false;
			m_persoActuel = m_persos[D1];
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
	if(saut)
	{
		m_enSaut=true;
		m_monte=true;
		repeatSaut=false;
	}
}

void PersoBoss::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	if (vx >= TAILLE_BLOC || vy >= TAILLE_BLOC)
	{
		deplacer(vx/2,vy/2,niveau);
		deplacer(vx-vx/2,vy-vy/2,niveau);
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

bool PersoBoss::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool PersoBoss::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
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
		m_vies=0;
		return false;
	}
	else if(xmin <= 0 || xmax >= NB_BLOC_LARGEUR_TOTAL)
		return true;
	else if(!saut && (niveau[xmax][ymin+1]==VIDE || niveau[xmin][ymin+1]==VIDE) && m_vies > 2)
				return true;
	for(int i=xmin; i <= xmax; i++)
	{
		for(int j=ymin; j <= ymax; j++)
		{

//Debut gestion collision avec le décor
			if (niveau[i][j]==MUR || niveau[i][j]==PONDEUR || niveau[i][j]==BONUS || niveau[i][j]==BRIQUE || niveau[i][j]==SOL || niveau[i][j]==BONUS_OK || niveau[i][j]==TERRE || niveau[i][j]==GAZON1 || niveau[i][j]==GAZON2 || niveau[i][j]==GAZON3 || niveau[i][j]==PONDEUR)
			{
				if(j==ymax && (m_rect.x < i*TAILLE_BLOC+TAILLE_BLOC && m_rect.x+m_rect.w > i*TAILLE_BLOC))
				{
					saut=true;
					repeatSaut=true;
					m_enSaut=false;
					m_vitesseV=m_vitesseS;

				}
				else if(j==ymin && (m_rect.x < i*TAILLE_BLOC+TAILLE_BLOC && m_rect.x+m_rect.w > i*TAILLE_BLOC))
				{
					m_monte=false;
					m_vitesseV=-m_vitesseS/3;
				}
				return true;
			}
		}
	}
//Fin gestion collision avec le décor

	return false;
}