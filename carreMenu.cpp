#include "carreMenu.h"

CarreMenu::CarreMenu(string nom,char *file,int avX,int avY,int index) :Personnage()
{
	m_persos[D1] = SDL_LoadBMP(file);

	m_nom=nom;
	m_index=index;
	m_vitesseH=10;
	m_vitesseV=10;
	avanceX=hazard(avX);
	avanceY=hazard(avY);
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;
	m_rect.w=m_persoActuel->w;
}
CarreMenu::~CarreMenu()
{
}

void CarreMenu::deplacer(int vx,int vy,vector<Personnage*>& persos,Music &music)
{
	essaieDeplacer(vx,vy,persos,music);
}

bool CarreMenu::essaieDeplacer(int vx,int vy,vector<Personnage*>& persos,Music &music)
{
	SDL_Rect test;
	test=m_rect;
	test.x += vx;
	test.y += vy;
	
	if(!collision(persos,test,music))
	{
		m_rect=test;
		return true;
	}
	
	return false;
}

bool CarreMenu::collision(vector<Personnage*>& persos,SDL_Rect &test,Music &music)
{	
	if(test.y <= 0 || test.y >= TAILLE_ECRAN_H-50-test.h)
	{
		avanceY=!avanceY;
		return true;
	}
	else if(test.x < 0 || test.x >= TAILLE_ECRAN_W-test.w)
	{
		avanceX=!avanceX;
		return true;
	}

	//Debut gestion collision avec les autres Carres

		Personnage *p=recupererPerso(persos,test.x,test.y);
		if(p != NULL)
		{
			if(p->getRect().y >=(m_rect.y + m_rect.h) || m_rect.y >=(p->getRect().y + p->getRect().h))
			{
				avanceY=!avanceY;
				return true;
			}
			else
			{
				avanceX=!avanceX;
				return true;
			}
		}
//Fin gestion collision avec les autres Carres

	return false;
}

void CarreMenu::evoluer(vector<Personnage*>& persos,Music &music)
{
	int vx,vy;
	recupererVecteur(&vx,&vy,music);
	deplacer(vx,vy,persos,music);
}

void CarreMenu::recupererVecteur(int *vx,int *vy,Music &music)
{
	*vx=0; *vy=0;
	if(avanceX)
		*vx+=m_vitesseH;
	else
		*vx-=m_vitesseH;
	if(avanceY)
		*vy+=m_vitesseV;
	else
		*vy-=m_vitesseV;
}

void CarreMenu::afficher(SDL_Surface *ecran)
{
	SDL_SetColorKey(m_persoActuel, SDL_SRCCOLORKEY, SDL_MapRGB(m_persoActuel->format, 255, 255, 0));
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&m_rect);
}

bool CarreMenu::hazard(int tp)
{
	int alea;
	srand(time(NULL));
    alea = (rand() % tp);
	return (alea < tp/2)?true:false;
}

