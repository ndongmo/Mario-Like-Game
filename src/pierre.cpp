#include "pierre.h"
#include "persoVie.h"
#include "persoChampignon.h"

Pierre::Pierre(bool position) :Personnage()
{
	m_persos[D1] = IMG_Load("images/pierre.png");

	m_nom="PIERRE";
	m_vitesseH=10;
	m_vitesseV=5;
	avanceX=position;
	avanceY=true;
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
}
Pierre::~Pierre()
{
}

void Pierre::deplacer(int vx,int vy,const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	essaieDeplacer(vx,vy,niveau,perso,persos,xscroll,yscroll);
}

bool Pierre::essaieDeplacer(int vx,int vy,const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	SDL_Rect test;
	test=m_rect;
	test.x += vx;
	test.y += vy;
	
	if(!collision(niveau,perso,persos,test,xscroll,yscroll))
	{
		m_rect=test;
		return true;
	}
	
	return false;
}

bool Pierre::collision(const vector<vector<int> >& niveau,Personnage &perso,vector<Personnage*>& persos,SDL_Rect &test,int xscroll, int yscroll)
{	
	int xmin,xmax,ymin,ymax;
	xmin = test.x / TAILLE_BLOC;
	ymin = test.y / TAILLE_BLOC;
	xmax = (test.x + test.w -1) / TAILLE_BLOC;
	ymax = (test.y + test.h -1) / TAILLE_BLOC;
	
	if(ymin <= 0)
	{
		mourir();
		return true;
	}
	else if(ymax >= NB_BLOC_HAUTEUR_TOTAL)
	{
		mourir();
		return true;
	}
	else if(xmin < 0 || xmax >= NB_BLOC_LARGEUR_TOTAL)
	{
		mourir();
		return true;
	}

	//Debut gestion collision avec les autres personnages
	Personnage *p=recupererPerso(persos,test.x,test.y,xscroll,yscroll);
	if(p != NULL)
	{
		if(p->getNom()=="PERSOCHAMPIGNON" || p->getNom()=="PERSOVIE")
		{
			return false;
		}
		else if(p->getNom()=="PERSOPASSEUR")
		{
			if(p->getRect().y >=(m_rect.y + m_rect.h) || m_rect.y >=(p->getRect().y + p->getRect().h))
			{
				int retour=Personnage::collision(p,BAS);
				if(retour==PASSEUR)
				{
					avanceY=!avanceY;
				}
			}
			else
			{
				int retour=Personnage::collision(p,HAUT);
				if(retour==PASSEUR)
					avanceX=!avanceX;
			}
			perso.updatePoints(m_points);
			return true;
		}
		else
		{
			int retour=Personnage::collision(p,BAS);
			if(retour==VIE)
			{
				SDL_Rect pos;
				pos=p->getRect();
				persos.push_back(new PersoVie());
				persos.back()->setRect(pos);
			}
			else if(retour==CHAMPIGNON)
			{
				SDL_Rect pos;
				pos=p->getRect();
				persos.push_back(new PersoChampignon());
				persos.back()->setRect(pos);
			}
			mourir();
			perso.updatePoints(m_points);
			return true;
		}
	}
//Fin gestion collision avec les autres personnages

	for(int i=xmin; i <= xmax; i++)
	{
		for(int j=ymin; j <= ymax; j++)
		{
//Debut gestion collision avec le décor
			if (niveau[i][j]==MUR || niveau[i][j]==SOL || niveau[i][j]==BONUS_OK || niveau[i][j]==BRIQUE || niveau[i][j]==PONDEUR || niveau[i][j]==BONUS || niveau[i][j]==TERRE || niveau[i][j]==GAZON1 || niveau[i][j]==GAZON2 || niveau[i][j]==GAZON3)
			{
				if(j*TAILLE_BLOC >=(m_rect.y + m_rect.h) || m_rect.y >=(j*TAILLE_BLOC + TAILLE_BLOC))
				{
					avanceY=!avanceY;
				}
				else
					avanceX=!avanceX;
				return true;
			}
		}
	}
//Fin gestion collision avec le décor

	return false;
}

void Pierre::evoluer(const vector<vector<int> > &niveau,Personnage &perso,vector<Personnage*>& persos,int xscroll, int yscroll)
{
	int vx,vy;
	recupererVecteur(&vx,&vy);
	deplacer(vx,vy,niveau,perso,persos,xscroll,yscroll);
}

void Pierre::recupererVecteur(int *vx,int *vy)
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

void Pierre::afficher(SDL_Surface *ecran,int xscroll, int yscroll)
{
	SDL_Rect posPerso;
	posPerso=m_rect;
	posPerso.x-=xscroll;
	posPerso.y-=yscroll;
	SDL_BlitSurface(m_persoActuel,NULL,ecran,&posPerso);
}
