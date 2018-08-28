#include "feu.h"

Feu::Feu(bool position,SDL_Rect pos,int level) :Personnage()
{
	m_persos[D1] = IMG_Load("images/feuD.png");
	m_persos[D2] = IMG_Load("images/feu1D.png");
	m_persos[G1] = IMG_Load("images/feuG.png");
	m_persos[G2] = IMG_Load("images/feu1G.png");

	m_nom="FEU";
	m_persoActuel = m_persos[D1];
	m_rect.x=pos.x;
	m_rect.y=pos.y-10+rand_n(30);
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;

	m_vitesseH=4+level;
	m_toucheDActif=position;
}

Feu::Feu(int level) :Personnage()
{
	m_persos[D1] = IMG_Load("images/feuD.png");
	m_persos[D2] = IMG_Load("images/feu1D.png");
	m_persos[G1] = IMG_Load("images/feuG.png");
	m_persos[G2] = IMG_Load("images/feu1G.png");

	m_nom="FEU";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;

	m_vitesseH=4+level;
	m_toucheDActif=true;
}
Feu::~Feu()
{
	
}

void Feu::recevoirDegat(int degat)
{
	
}

void Feu::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;

	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void Feu::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy);
	deplacer(vx,vy,niveau);
}

void Feu::recupererVecteur(int *vx, int *vy)
{
	if(m_toucheDActif)
	{
		*vx=m_vitesseH;
		if(m_persoActuel==m_persos[D1])
			m_persoActuel=m_persos[D2];
		else
			m_persoActuel=m_persos[D1];
	}
	else
	{
		*vx=-m_vitesseH;
		if(m_persoActuel==m_persos[G1])
			m_persoActuel=m_persos[G2];
		else
			m_persoActuel=m_persos[G1];
	}
}

void Feu::deplacer(int vx,int vy,const vector<vector<int> > &niveau)
{
	essaieDeplacer(vx,vy,niveau);
}

bool Feu::essaieDeplacer(int vx,int vy,const vector<vector<int> > &niveau)
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

bool Feu::collision(const vector<vector<int> > &niveau, SDL_Rect &test)
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

int Feu::lotterie()
{
	srand(time(NULL));
	return(rand() % 20);
}