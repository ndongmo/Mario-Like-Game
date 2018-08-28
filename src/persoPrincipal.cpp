#include "persoPrincipal.h"
#include "persoVie.h"
#include "persoChampignon.h"

PersoPrincipal::PersoPrincipal() :Personnage()
{
	m_persos[D1] = SDL_LoadBMP("images/pmarioD1.bmp");
    m_persos[D2] = SDL_LoadBMP("images/pmarioD2.bmp");
    m_persos[D3] = SDL_LoadBMP("images/pmarioD3.bmp");
    m_persos[G1] = SDL_LoadBMP("images/pmarioG1.bmp");
    m_persos[G2] = SDL_LoadBMP("images/pmarioG2.bmp");
	m_persos[G3] = SDL_LoadBMP("images/pmarioG3.bmp");

	m_nom="PERSOPRINCIPAL";
	m_etat=PETIT;
	m_position=true;
	m_vies=5;
	m_interval=0;
	m_persoActuel = m_persos[D1];
	m_rect.x=0;
	m_rect.y=0;
	m_rect.h=m_persoActuel->h;;
	m_rect.w=m_persoActuel->w;
}
PersoPrincipal::~PersoPrincipal()
{
}

void PersoPrincipal::recevoirDegat(int degat)
{
	if(m_etat==PETIT || m_etat==MORT)
	{
		Personnage::recevoirDegat(degat);
		m_etat=MORT;
	}
	else if(m_etat==GRAND || m_etat==GEANT)
		retrecir();
}

void PersoPrincipal::lancer(vector<Personnage*>& persos)
{
	if((SDL_GetTicks() - m_interval) >= 1000)
	{
		persos.push_back(new Pierre(m_position));
		persos.back()->setRect(m_rect);
		m_interval=SDL_GetTicks();
	}
}
void PersoPrincipal::setEtat(int etat)
{
	m_etat=etat;
}
void PersoPrincipal::grandir(SDL_Rect &rect)
{
	if(m_etat==PETIT)
	{
		m_etat=GRAND;
		m_persos[D1] = SDL_LoadBMP("images/marioD1.bmp");
		m_persos[D2] = SDL_LoadBMP("images/marioD2.bmp");
		m_persos[D3] = SDL_LoadBMP("images/marioD3.bmp");
		m_persos[G1] = SDL_LoadBMP("images/marioG1.bmp");
		m_persos[G2] = SDL_LoadBMP("images/marioG2.bmp");
		m_persos[G3] = SDL_LoadBMP("images/marioG3.bmp");
		m_persoActuel = m_persos[D1];
		rect.y=rect.y-(m_persoActuel->h-rect.h);
		m_rect.y=rect.y;
		m_rect.h=m_persoActuel->h;
		m_rect.w=m_persoActuel->w;
	}
	else
	{
		m_etat=GEANT;
		m_persos[D1] = SDL_LoadBMP("images/bmarioD1.bmp");
		m_persos[D2] = SDL_LoadBMP("images/bmarioD2.bmp");
		m_persos[D3] = SDL_LoadBMP("images/bmarioD3.bmp");
		m_persos[G1] = SDL_LoadBMP("images/bmarioG1.bmp");
		m_persos[G2] = SDL_LoadBMP("images/bmarioG2.bmp");
		m_persos[G3] = SDL_LoadBMP("images/bmarioG3.bmp");
		m_persoActuel = m_persos[D1];
		m_rect.h=m_persoActuel->h;
		m_rect.w=m_persoActuel->w;
	}
}
void PersoPrincipal::retrecir()
{
	m_etat=PETIT;
	m_transparent=128;
	m_temps=SDL_GetTicks();
	m_persos[D1] = SDL_LoadBMP("images/pmarioD1.bmp");
    m_persos[D2] = SDL_LoadBMP("images/pmarioD2.bmp");
    m_persos[D3] = SDL_LoadBMP("images/pmarioD3.bmp");
    m_persos[G1] = SDL_LoadBMP("images/pmarioG1.bmp");
    m_persos[G2] = SDL_LoadBMP("images/pmarioG2.bmp");
	m_persos[G3] = SDL_LoadBMP("images/pmarioG3.bmp");
	m_persoActuel = m_persos[D1];
	
	m_rect.h=m_persoActuel->h;
	m_rect.w=m_persoActuel->w;
}
int PersoPrincipal::getEtat()
{
	return m_etat;
}

bool PersoPrincipal::getPosition()
{
	return m_position;
}

void PersoPrincipal::evoluer(Clavier &in,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll)
{
	int vx,vy;
	recupererVecteur(in,&vx,&vy,music,persos);
	sauter(&vy);
	deplacer(vx,vy,niveau,persos,music,xscroll,yscroll);
	if(estTransparent() && (SDL_GetTicks() - m_temps) >= 2000)
		m_transparent=255;
}

void PersoPrincipal::deplacer(int vx,int vy,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll)
{
	if (vx >= TAILLE_BLOC || vy >= TAILLE_BLOC)
	{
		deplacer(vx/2,vy/2,niveau,persos,music,xscroll,yscroll);
		deplacer(vx-vx/2,vy-vy/2,niveau,persos,music,xscroll,yscroll);
		return;
	}
	if (essaieDeplacer(vx,vy,niveau,persos,music,xscroll,yscroll,&vx,&vy))
		return;
// affine
	for(int i=0;i<ABS(vx);i++)
	{
		if (!essaieDeplacer(SGN(vx),0,niveau,persos,music,xscroll,yscroll,&vx,&vy))
			break;
	}
	for(int i=0;i<ABS(vy);i++)
	{
		if (!essaieDeplacer(0,SGN(vy),niveau,persos,music,xscroll,yscroll,&vx,&vy))
			break;			
	}
}

bool PersoPrincipal::essaieDeplacer(int vx,int vy,vector<vector<int> >& niveau,vector<Personnage*>& persos,Music &music,int xscroll, int yscroll,int *x,int *y)
{
	SDL_Rect test;
	test=m_rect;
	test.x += vx;
	test.y += vy;
	if(!collision(niveau,persos,test,music,xscroll,yscroll,x,y))
	{
		setRect(test);
		return true;
	}
	
	return false;
}

bool PersoPrincipal::collision(vector<vector<int> >& niveau,vector<Personnage*>& persos,SDL_Rect &test,Music &music,int xscroll, int yscroll,int *vx,int *vy)
{
	int xmin,xmax,ymin,ymax;
	bool passeur=false;
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
		saut=true;
		m_enSaut=false;
		m_vitesseV=m_vitesseS;
		if(m_etat!=MORT)
		{
			m_etat=MORT;
			recevoirDegat(m_pouvoirTrou);
		}
		return true;
	}
	else if(xmin < 0 || xmax >= NB_BLOC_LARGEUR_TOTAL)
		return true;

//Debut gestion collision avec les autres personnages
	if(!estTransparent())
	{
		Personnage *p=recupererPerso(persos,test.x,test.y,xscroll,yscroll);
		if(p != NULL)
		{
			if(p->getNom()=="PERSOCHAMPIGNON")
			{
				if(m_etat==PETIT)
					grandir(test);
				p->recevoirDegat(m_pouvoirSaut);
			}
			else if(p->getNom()=="PIERRE")
			{
			}
			else if(p->getNom()=="PERSOCANON1" || p->getNom()=="PERSOCANON2")
			{
				if(p->getRect().y >=(m_rect.y + m_rect.h))
				{
					saut=true;
					repeatSaut=true;
					m_enSaut=false;
					m_vitesseV=m_vitesseS;
					return true;
				}
				return true;
			}
			else if(p->getNom()=="PERSOVIE")
			{
				m_vies++;
				p->recevoirDegat(m_pouvoirSaut);
			}
			else if(p->getNom()=="PERSOPiQUANT" || p->getNom()=="PERSOPiQUANT1" || p->getNom()=="FEU")
			{
				recevoirDegat(p->getPouvoir());
			}
			else if(p->getNom()=="PERSOCASSABLE")
			{
				if(p->getRect().y >=(m_rect.y + m_rect.h))
				{
					saut=true;
					repeatSaut=true;
					m_enSaut=false;
					m_vitesseV=m_vitesseS;
					p->setMonte(true);
					return true;
				}
			}
			else if(p->getNom()=="PERSOPASSEUR")
			{
				if(p->getRect().y >=(m_rect.y + m_rect.h))
				{
					saut=true;
					repeatSaut=true;
					m_enSaut=false;
					m_vitesseV=m_vitesseS;
					if(p->getToucheDActif())
						*vx+=p->getVitesseH();
					else
						*vx-=p->getVitesseH();
					passeur=true;
				}
				else if((p->getRect().y+p->getRect().h) <= m_rect.y)
				{
					m_monte=false;
					m_vitesseV=-m_vitesseS/3;
					music.jouerSon(7);
					passeur=true;
				}
			}
			else if(p->getNom()=="PERSOPASSEUR1")
			{
				if(p->getRect().y >=(m_rect.y + m_rect.h))
				{
					saut=true;
					repeatSaut=true;
					m_enSaut=false;
					m_vitesseV=m_vitesseS;
					*vy=0;
					if(!p->getMonte())
					{
					if(p->getToucheBActif())
						*vy+=p->getVitesseV();
					else
						*vy-=p->getVitesseV();
					}
					else
					{
						if(p->getToucheBActif())
						*vy-=p->getVitesseV();
					else
						*vy+=p->getVitesseV();
					}
					passeur=true;
				}
			}
			else 
			{
				if(p->getRect().y >=(m_rect.y + m_rect.h))
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
					else
					{
						saut=false;
						m_enSaut=false;
						m_vitesseV=-m_vitesseS/2;
						music.jouerSon(2);
					}
				}
				else
				{
					Personnage::collision(p,HAUT);
				}
				return true;
			}
		}
	}
//Fin gestion collision avec les autres personnages

//Debut gestion collision avec le décor
	for(int i=xmin; i <= xmax; i++)
	{
		for(int j=ymin; j <= ymax; j++)
		{
			if (niveau[i][j]==MUR || niveau[i][j]==SOL || niveau[i][j]==BONUS_OK || niveau[i][j]==TERRE || niveau[i][j]==GAZON1 || niveau[i][j]==GAZON2 || niveau[i][j]==GAZON3)
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
					music.jouerSon(7);
				}
				return true;
			}
			else if(niveau[i][j]==BRIQUE)
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
					if(m_etat > PETIT)
						niveau[i][j]=VIDE;
					m_monte=false;
					m_vitesseV=-m_vitesseS/3;
					music.jouerSon(7);
				}
				return true;
			}
			else if(niveau[i][j]==ETOILE)
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
					SDL_Rect pos;
					pos.x=i*TAILLE_BLOC;
					pos.y=(j-1)*TAILLE_BLOC;
					PersoVie * p=new PersoVie();
					p->setRect(pos);
					persos.push_back(p);

					niveau[i][j]=MUR;
					m_monte=false;
					m_vitesseV=-m_vitesseS/3;
					music.jouerSon(7);
				}
				return true;
			}
			else if(niveau[i][j]==PONDEUR)
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
					if(m_etat > PETIT)
						niveau[i][j-1]=FLEUR;
					else
					{
						if(lotterie()==CHAMPIGNON)
						{
							SDL_Rect pos;
							pos.x=i*TAILLE_BLOC;
							pos.y=(j-1)*TAILLE_BLOC;
							PersoChampignon * p=new PersoChampignon();
							p->setRect(pos);
							persos.push_back(p);
						}
						else
						{
							SDL_Rect pos;
							pos.x=i*TAILLE_BLOC;
							pos.y=(j-1)*TAILLE_BLOC;
							PersoVie * p=new PersoVie();
							p->setRect(pos);
							persos.push_back(p);
						}
					}
					niveau[i][j]=MUR;
					m_monte=false;
					m_vitesseV=-m_vitesseS/3;
					music.jouerSon(7);
				}
				return true;
			}
			else if(niveau[i][j]==PIECE)
			{
				niveau[i][j]=VIDE;
				enrichir();
				music.jouerSon(1);
			}
			else if(niveau[i][j]==FLEUR)
			{
				niveau[i][j]=VIDE;
				grandir(test);
				music.jouerSon(8);
			}
			else if(niveau[i][j]==PORTE)
			{
				updateMission(true);
			}
			else if(niveau[i][j]==BONUS)
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
					if(m_piecesMur > 0)
					{
						enrichir();
						m_piecesMur--;
					}
					else
					{
						niveau[i][j]=BONUS_OK;
						m_piecesMur=this->pieceBonus();
					}
					m_monte=false;
					m_vitesseV=-m_vitesseS/3;
					music.jouerSon(1);
				}
				return true;
			}
		}
	}
//Fin gestion collision avec le décor

	return passeur;
}

void PersoPrincipal::recupererVecteur(Clavier &in,int *vx,int *vy,Music &music,vector<Personnage*>& persos)
{
	*vx=0; *vy=0;
//Debut: Touche haut du clavier appuyée
	if (in.key[SDLK_UP])
	{
		if(repeatSaut)
		{
			music.jouerSon(5);
		}
		if(saut)
		{
			m_enSaut=true;
			m_toucheSautActif=true;
			m_monte=true;
			repeatSaut=false;
		}
	}
	else
	{
		m_toucheSautActif=false;
	}
//Fin
//Debut: Touche Gauche du clavier appuyée
	if (in.key[SDLK_LEFT])
	{
		m_position=false;
		if(m_persoActuel==m_persos[G1])
			m_persoActuel=m_persos[G2];
		else if(m_persoActuel==m_persos[G2])
			m_persoActuel=m_persos[G3];
		else
			m_persoActuel=m_persos[G1];

		*vx=-m_vitesseH;
	}
//Fin
//Debut: Touche Droite du clavier appuyée
	else if (in.key[SDLK_RIGHT])
	{
		m_position=true;
		if(m_persoActuel==m_persos[D1])
			m_persoActuel=m_persos[D2];
		else if(m_persoActuel==m_persos[D2])
			m_persoActuel=m_persos[D3];
		else
			m_persoActuel=m_persos[D1];

		*vx=m_vitesseH;
	}
//Fin
//Debut: Touche Gauche de la Manette appuyée
	else if (in.mouseG)
	{
		m_position=false;
		if(m_persoActuel==m_persos[G1])
			m_persoActuel=m_persos[G2];
		else if(m_persoActuel==m_persos[G2])
			m_persoActuel=m_persos[G3];
		else
			m_persoActuel=m_persos[G1];

		*vx=-m_vitesseH;
	}
//Fin
//Debut: Touche Droite de la Manette appuyée
	else if (in.mouseD)
	{
		m_position=true;
		if(m_persoActuel==m_persos[D1])
			m_persoActuel=m_persos[D2];
		else if(m_persoActuel==m_persos[D2])
			m_persoActuel=m_persos[D3];
		else
			m_persoActuel=m_persos[D1];

		*vx=m_vitesseH;
	}
//Fin
//Debut: Touche y du clavier appuyée
	if (in.key[SDLK_c] && m_etat==GEANT)
	{
		lancer(persos);
	}
//Fin
//Debut: Touche B de la manette appuyée
	if (in.joystickButtons[1] && m_etat==GEANT)
	{
		lancer(persos);
	}
//Fin
//Debut: Touches X,Gauche ou Droite du clavier appuyée
	if (in.key[SDLK_x] && (in.key[SDLK_RIGHT] || in.key[SDLK_LEFT]))
	{
		if((!m_toucheVHActif || m_vitesseH < m_vitesseHnormal+6) && repeatSaut)
		{
			m_vitesseH+=1;
			m_toucheVHActif=true;
		}
	}
	else if (!(in.joystickButtons[5] && (in.mouseG || in.mouseD)))
	{
		m_vitesseH=m_vitesseHnormal;
		m_toucheVHActif=false;
	}
//Fin
//Debut: Touche A de la Manette appuyée
	if(in.joystickButtons[0])
	{
		if(repeatSaut)
		{
			music.jouerSon(5);
		}
		if(saut)
		{
			m_enSaut=true;
			m_toucheSautActif=true;
			m_monte=true;
			repeatSaut=false;
		}
	}
	else if(!in.key[SDLK_UP])
	{
		m_toucheSautActif=false;
	}
//Fin
//Debut: Touches A,Gauche ou Droite de la Manette appuyée
	if (in.joystickButtons[5] && (in.mouseG || in.mouseD))
	{
		if((!m_toucheVHActif || m_vitesseH < m_vitesseHnormal+6) && repeatSaut)
		{
			m_vitesseH+=1;
			m_toucheVHActif=true;
		}
	}
	else if (!(in.key[SDLK_x] && (in.key[SDLK_RIGHT] || in.key[SDLK_LEFT])))
	{
		m_vitesseH=m_vitesseHnormal;
		m_toucheVHActif=false;
	}
//Fin
}