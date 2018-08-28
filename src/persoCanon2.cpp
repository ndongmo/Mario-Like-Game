#include "persoCanon2.h"

PersoCanon2::PersoCanon2(int level) :Personnage()
{
	m_persos.resize(1,NULL);
	m_persos[D1] = IMG_Load("images/canonCourt.png");

	m_nom="PERSOCANON2";
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;

	m_toucheDActif=false;
	interval=(5-level)*1000;
}
PersoCanon2::~PersoCanon2()
{
	
}

int PersoCanon2::getPoints()
{
	return m_points;
}


bool PersoCanon2::hazard()
{
	int h;
	h=(rand_n(10));
	if(h < 5)
		return false;
	else
		return true;
}

void PersoCanon2::lancer(vector<Personnage*>& persos)
{
	persos.push_back(new Boulet(m_toucheDActif,m_rect,m_level));
	m_temps=SDL_GetTicks();
}

void PersoCanon2::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso,posAff;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;

	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void PersoCanon2::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy=0;
	recupererVecteur(&vx,&vy,perso);
	if((SDL_GetTicks() - m_temps) >= interval && hazard())
		lancer(persos);
}

void PersoCanon2::recupererVecteur(int *vx, int *vy,Personnage &perso)
{
	SDL_Rect pos;
	pos=perso.getRect();
	if(pos.x < m_rect.x)
		m_toucheDActif=false;
	else
		m_toucheDActif=true;
}