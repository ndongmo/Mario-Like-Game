#include "persoDinau.h"

PersoDinau::PersoDinau(int level) :Personnage()
{
	m_persos.resize(6,NULL);
	m_persos[D1] = SDL_LoadBMP("images/dinauD1.bmp");
	m_persos[D2] = SDL_LoadBMP("images/dinauD2.bmp");
	m_persos[D3] = SDL_LoadBMP("images/dinauD3.bmp");
	m_persos[G1] = SDL_LoadBMP("images/dinauG1.bmp");
	m_persos[G2] = SDL_LoadBMP("images/dinauG2.bmp");
	m_persos[G3] = SDL_LoadBMP("images/dinauG3.bmp");

	m_nom="PERSODINAU";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
	ancien=m_rect;

	m_vitesseH=3+level;
	m_toucheDActif=true;
	m_toucheGActif=false;
	m_points=10;
	m_police=TTF_OpenFont("polices/times.TTF",10);
	m_couleurNoire.b=0;m_couleurNoire.g=0;m_couleurNoire.r=0;
	m_couleurBlanche.b=255;m_couleurBlanche.g=255;m_couleurBlanche.r=255;
	sprintf(m_tabPoints, "%d", m_points);
	m_affPoints= TTF_RenderText_Blended(m_police, m_tabPoints, m_couleurNoire);
}
PersoDinau::~PersoDinau()
{
	SDL_FreeSurface(m_affPoints);
	TTF_CloseFont(m_police);
}

int PersoDinau::getPoints()
{
	return m_points;
}

void PersoDinau::recevoirDegat(int degat)
{
	Personnage::recevoirDegat(degat);
	if(!estVivant())
		m_posAffPoints=m_rect;
}

void PersoDinau::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
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

void PersoDinau::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy);
	sauter(&vy);
	deplacer(vx,vy,niveau);
}

void PersoDinau::recupererVecteur(int *vx, int *vy)
{
	if(ancien.x==m_rect.x)
	{
		m_toucheDActif=!m_toucheDActif;
	}
	else if(ancien.x < m_rect.x)
	{
		m_toucheDActif=true;
		if(m_persoActuel==m_persos[D1])
			m_persoActuel=m_persos[D2];
		else if(m_persoActuel==m_persos[D2])
			m_persoActuel=m_persos[D3];
		else
			m_persoActuel=m_persos[D1];
	}
	else
	{
		m_toucheDActif=false;
		if(m_persoActuel==m_persos[G1])
			m_persoActuel=m_persos[G2];
		else if(m_persoActuel==m_persos[G2])
			m_persoActuel=m_persos[G3];
		else
			m_persoActuel=m_persos[G1];
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

void PersoDinau::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool PersoDinau::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool PersoDinau::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
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
	else if((niveau[xmax][ymin+1]==VIDE || niveau[xmin][ymin+1]==VIDE) && !(niveau[xmax][ymin+1]==VIDE && niveau[xmin][ymin+1]==VIDE))
				return true;
	else if((niveau[xmax][ymin+1]==GAZON11 || niveau[xmin][ymin+1]==GAZON11) && !(niveau[xmax][ymin+1]==GAZON11 && niveau[xmin][ymin+1]==GAZON11))
				return true;
	else if((niveau[xmax][ymin+1]==GAZON22 || niveau[xmin][ymin+1]==GAZON22) && !(niveau[xmax][ymin+1]==GAZON22 && niveau[xmin][ymin+1]==GAZON22))
				return true;
	else if((niveau[xmax][ymin+1]==GAZON33 || niveau[xmin][ymin+1]==GAZON33) && !(niveau[xmax][ymin+1]==GAZON33 && niveau[xmin][ymin+1]==GAZON33))
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