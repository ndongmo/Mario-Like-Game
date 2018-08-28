#include "boulet.h"

Boulet::Boulet(bool position,SDL_Rect pos,int level) :Personnage()
{
	m_persos.resize(2,NULL);
	m_persos[D1] = IMG_Load("images/bouletD.bmp");
	m_persos[D2] = IMG_Load("images/bouletG.bmp");

	m_nom="BOULET";
	m_persoActuel = m_persos[D1];
	m_rect.x=pos.x;
	m_rect.y=pos.y;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;

	m_vitesseH=4+level;
	m_toucheDActif=position;
	m_points=5;
	m_police=TTF_OpenFont("polices/times.TTF",10);
	m_couleurNoire.b=0;m_couleurNoire.g=0;m_couleurNoire.r=0;
	m_couleurBlanche.b=255;m_couleurBlanche.g=255;m_couleurBlanche.r=255;
	sprintf(m_tabPoints, "%d", m_points);
	m_affPoints= TTF_RenderText_Blended(m_police, m_tabPoints, m_couleurNoire);
}

Boulet::~Boulet()
{
	SDL_FreeSurface(m_affPoints);
	TTF_CloseFont(m_police);
}

void Boulet::recevoirDegat(int degat)
{
	Personnage::recevoirDegat(degat);
	if(!estVivant())
		m_posAffPoints=m_rect;
}

void Boulet::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
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

void Boulet::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy);
}

void Boulet::recupererVecteur(int *vx, int *vy)
{
	if(m_toucheDActif)
	{
		m_rect.x+=m_vitesseH;
		m_persoActuel=m_persos[D1];
	}
	else
	{
		m_rect.x+=-m_vitesseH;
		m_persoActuel=m_persos[D2];
	}
}

void Boulet::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	essaieDeplacer(vx,vy,niveau);
}

bool Boulet::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool Boulet::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
{
	int xmin,xmax,ymin,ymax;
	xmin = test.x / TAILLE_BLOC;
	ymin = test.y / TAILLE_BLOC;
	xmax = (test.x + test.w -1) / TAILLE_BLOC;
	ymax = (test.y + test.h -1) / TAILLE_BLOC;
	
	if(ymin < 0)
	{
		m_transparent=0;
		m_vies=0;
		return false;
	}
	else if(ymax >= NB_BLOC_HAUTEUR_TOTAL)
	{
		m_transparent=0;
		m_vies=0;
		return false;
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
				return false;
			}
		}
	}
//Fin gestion collision avec le décor

	return false;
}

int Boulet::lotterie()
{
	srand(time(NULL));
	return(rand() % 20);
}