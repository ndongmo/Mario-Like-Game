#include "personnage.h"

Personnage::Personnage()
{
	m_persos.resize(6,NULL);
	m_vies=1;
	m_pieces=0;
	m_points=0;
	m_piecesMur=pieceBonus();
	m_pouvoirSaut=1;
	m_pouvoirTrou=1;
	m_transparent=255;
	m_vitesseHnormal=4;
	m_vitesseH=m_vitesseHnormal;
	m_vitesseS=14;
	m_vitesseV=m_vitesseS;
	saut=false;
	repeatSaut=false;
	m_enSaut=false;
	m_monte=false;
	m_toucheSautActif=false;
	m_toucheVHActif=false;
	m_gravite=1;
	m_level=NORMAL;
	m_index=0;
	m_mission=false;
	m_temps=0;
}

Personnage::~Personnage()
{	
	for(int i=0; i < m_persos.size(); i++)
	{
		SDL_FreeSurface(m_persos[i]);
	}
	m_persoActuel=NULL;
	SDL_FreeSurface(m_persoActuel);
}

int Personnage::collision(Personnage *perso,int position)
{
	if(position==BAS)
	{
		if(perso->m_nom=="PERSOSUIVEUR")
		{
			perso->recevoirDegat(m_pouvoirSaut);
			if(!perso->estVivant())
			{
				updatePoints(perso->getPoints());
				return lotterie();
			}
		}
		else if(perso->m_nom=="PERSOPASSEUR")
		{
			return PASSEUR;
		}
		else
		{
			perso->recevoirDegat(m_pouvoirSaut);
			if(!perso->estVivant())
				updatePoints(perso->getPoints());
		}
	}
	else
	{
		if(perso->m_nom=="PERSOPASSEUR")
			return PASSEUR;
		else if(perso->m_nom!="PERSOVIE" && perso->m_nom!="PERSOCHAMPIGNON")
			recevoirDegat(perso->m_pouvoirSaut);
	}
	return VIDE;
}

void Personnage::recevoirDegat(int degat)
{
	m_vies-=degat;
	if(!estVivant())
		m_transparent=128;
}

void Personnage::mourir()
{
	m_transparent=0;
	m_vies=0;
}
bool Personnage::estVivant()
{
	if(m_vies > 0)
		return true;
	else
		return false;
}

bool Personnage::estTransparent()
{
	if(m_transparent < 255)
		return true;
	else
		return false;
}
bool Personnage::estSurEcran(int xscroll,int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	if(m_nom!="PERSOPASSEUR1" && m_nom!="PERSOPASSEUR")
	{
		if(posPerso.y > HAUTEUR_ECRAN+TAILLE_BLOC || posPerso.y < 0 ||
			posPerso.x > LARGEUR_ECRAN+TAILLE_BLOC || posPerso.x < 0)
			return false;
	}
	return true;
}
void Personnage::enrichir()
{
	if(m_pieces < 100)
		m_pieces++;
	else
	{
		m_pieces=0;
		m_vies++;
	}
	updatePoints(5);
}
void Personnage::updatePoints(int points)
{
	if(m_points < 100000)
		m_points+=points;
}
int Personnage::pieceBonus()
{
    srand(time(NULL));
    return (rand() % 10);
}

int Personnage::lotterie()
{
	int h;
	srand(time(NULL));
	h=(rand() % 10);
	if(h < 7)
		return CHAMPIGNON;
	else
		return VIE;
}
Personnage* Personnage::recupererPerso(vector<Personnage*>& persos,int x, int y,int xscroll, int yscroll)
{
	for(int i=0;i<persos.size();i++)
	{
		if(persos[i]->estSurEcran(xscroll,yscroll))
		{
			if(!((persos[i]->m_rect.x >= x + m_rect.w) || 
				(persos[i]->m_rect.x + persos[i]->m_rect.w <= x) 
			   || (persos[i]->m_rect.y >= y + m_rect.h)|| 
			   (persos[i]->m_rect.y + persos[i]->m_rect.h <= y)))
			{
				if(persos[i]->estVivant())
				{
					persos[i]->m_index=i;
					return persos[i];
				}
			}
		}
	}
	return NULL;
}

Personnage* Personnage::recupererPerso(vector<Personnage*>& persos,Personnage*moi,int x, int y,int xscroll, int yscroll)
{
	for(int i=0;i<persos.size();i++)
	{
		if(persos[i]!=moi && persos[i]->estSurEcran(xscroll,yscroll))
		{
			if(!((persos[i]->m_rect.x >= x + m_rect.w) || 
				(persos[i]->m_rect.x + persos[i]->m_rect.w <= x) 
			   || (persos[i]->m_rect.y >= y + m_rect.h)|| 
			   (persos[i]->m_rect.y + persos[i]->m_rect.h <= y)))
			{
				if(persos[i]->estVivant())
				{
					persos[i]->m_index=i;
					return persos[i];
				}
			}
		}
	}
	return NULL;
}

Personnage* Personnage::recupererPerso(vector<Personnage*>& persos,int x, int y)
{
	for(int i=0;i<persos.size();i++)
	{
		if(i!=m_index)
		{
			if(!((persos[i]->m_rect.x >= x + m_rect.w) || 
				(persos[i]->m_rect.x + persos[i]->m_rect.w <= x) 
				|| (persos[i]->m_rect.y >= y + m_rect.h)|| 
				(persos[i]->m_rect.y + persos[i]->m_rect.h <= y)))
			{
				return persos[i];
			}
		}
	}
	return NULL;
}

void Personnage::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	SDL_SetColorKey(m_persoActuel, SDL_SRCCOLORKEY, SDL_MapRGB(m_persoActuel->format, 255, 255, 0));
	SDL_SetAlpha(m_persoActuel, SDL_SRCALPHA, m_transparent);
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}

void Personnage::sauter(int *vy)
{
	if(m_enSaut)
	{
		if(m_monte )
		{
			if(m_toucheSautActif)
			{
				m_vitesseV-=m_gravite;
			}
			else
			{
				m_vitesseV-=m_gravite*2;
			}
		}
		else
		{
			m_vitesseV-=m_gravite;
		}
		*vy=-m_vitesseV;
	}
	else
	{
		saut=false;
		repeatSaut=false;
		m_vitesseV+=m_gravite;
		*vy+=m_vitesseV;
	}
}

SDL_Rect Personnage::getRect()
{
	return m_rect;
}
void Personnage::setRect(SDL_Rect &rect)
{
	m_rect.x=rect.x;
	m_rect.y=rect.y;
}
void Personnage::setPosAffPoints(int x,int y)
{
	m_posAffPoints.x+=x;
	m_posAffPoints.y+=y;
}
void Personnage::setTransparent(int valeur)
{
	m_transparent=valeur;
}
void Personnage::updateMission(bool mission)
{
	m_mission=mission;
}
bool Personnage::getMission()
{
	return m_mission;
}
int Personnage::getTransparent()
{
	return m_transparent;
}
int Personnage::getPieces()
{
	return m_pieces;
}
int Personnage::getPoints()
{
	return m_points;
}
int Personnage::getPouvoir()
{
	return m_pouvoirSaut;
}
int Personnage::getVies()
{
	return m_vies;
}
string Personnage::getNom()
{
	return m_nom;
}
int Personnage::getIndex()
{
	return m_index;
}
int Personnage::getVitesseH()
{
	return m_vitesseH;
}
int Personnage::getVitesseV()
{
	return m_vitesseV;
}
bool Personnage::getMonte()
{
	return m_monte;
}
void Personnage::setVitesse(int vv, int vh)
{
	m_vitesseV=vv;
	m_vitesseH=vh;
}
bool Personnage::getToucheDActif()
{
	return m_toucheDActif;
}
bool Personnage::getToucheBActif()
{
	return m_toucheBActif;
}
void Personnage::setIndex(int index)
{
	m_index=index;
}
void Personnage::setToucheDActif()
{
	m_toucheDActif=!m_toucheDActif;
}
void Personnage::setMonte(bool monte)
{
	m_monte=monte;
}

int Personnage::rand_n(int n)
{
	int partSize= 1 + (n == RAND_MAX ? 0 : (RAND_MAX - n) / (n + 1));
	int maxUsefull = partSize * n + (partSize - 1);
	int draw;

	do{
		draw = rand();
	}while(draw > maxUsefull);
	return draw / partSize;
}