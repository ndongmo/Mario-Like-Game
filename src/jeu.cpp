#include "jeu.h"

Jeu::Jeu(int level)
{
	m_carte;
	m_fichier;
	m_mario;
	memset(&m_in,0,sizeof(m_in));
	m_niveau.resize(NB_BLOC_LARGEUR_TOTAL,vector<int> (NB_BLOC_HAUTEUR_TOTAL,0));
	m_objets.resize(7,NULL);
	m_posObjets.resize(7);
	
	m_continuer=true;
	m_pause=false;
	m_tempsActuel=0;
	m_tempsPrecedent=0;
	m_intervalTemps=50;
	m_getstickTemps=0;
	m_temps=0;
	m_level=level;

	m_police=TTF_OpenFont("polices/times.TTF",30);
	m_couleurNoire.b=0;m_couleurNoire.g=0;m_couleurNoire.r=0;
	m_couleurBlanche.b=255;m_couleurBlanche.g=255;m_couleurBlanche.r=255;

	initialiserNiveau();

	sprintf(m_tempsJeu, "Temps  00%d", 0);
	sprintf(m_nbrePiece, " X 0%d",0);
	sprintf(m_nbreVie, " X 0%d",  0);
	sprintf(m_point, "Points  0000%d",  0);

	m_objets[0]=SDL_CreateRGBSurface(SDL_HWSURFACE, m_posObjets[0].w,  m_posObjets[0].h, 32, 0, 0, 0, 0);
	m_objets[1]=TTF_RenderText_Shaded(m_police, m_tempsJeu, m_couleurNoire, m_couleurBlanche);
	m_objets[2]=SDL_LoadBMP("images/mario.bmp");
	m_objets[3]=TTF_RenderText_Shaded(m_police, m_nbreVie, m_couleurNoire, m_couleurBlanche);
	m_objets[4]=SDL_LoadBMP("images/piece.bmp");
	m_objets[5]=TTF_RenderText_Shaded(m_police, m_nbrePiece, m_couleurNoire, m_couleurBlanche);
	m_objets[6]=TTF_RenderText_Shaded(m_police, m_point, m_couleurNoire, m_couleurBlanche);
	m_titre=TTF_RenderText_Shaded(m_police, m_tabTitre, m_couleurNoire, m_couleurBlanche);
}

Jeu::~Jeu()
{
	for(int i=0;i<m_bandit1s.size();i++)
	{
		delete m_bandit1s[i];
	}
	for(int i=0;i<m_objets.size();i++)
	{
		SDL_FreeSurface(m_objets[i]);
	}
	SDL_FreeSurface(m_titre);
	TTF_CloseFont(m_police); 
}

void Jeu::initialiserNiveau()
{
	m_posObjets[0].x=0;
	m_posObjets[0].y=HAUTEUR_ECRAN;
	m_posObjets[0].w=LARGEUR_ECRAN;
	m_posObjets[0].h=TAILLE_ECRAN_H-HAUTEUR_ECRAN;
	m_posObjets[1].x= 10;
	m_posObjets[1].y= HAUTEUR_ECRAN+(TAILLE_BLOC*2);
	m_posObjets[2].x=210;
	m_posObjets[2].y=HAUTEUR_ECRAN+(TAILLE_BLOC*2);
	m_posObjets[3].x=240;
	m_posObjets[3].y=HAUTEUR_ECRAN+(TAILLE_BLOC*2);
	m_posObjets[4].x=410;
	m_posObjets[4].y=HAUTEUR_ECRAN+(TAILLE_BLOC*2);
	m_posObjets[5].x=440;
	m_posObjets[5].y=HAUTEUR_ECRAN+(TAILLE_BLOC*2);
	m_posObjets[6].x=600;
	m_posObjets[6].y=HAUTEUR_ECRAN+(TAILLE_BLOC*2);
}

void Jeu::updateJeu(SDL_Surface *ecran,int type,Music &music)
{
	memset(&m_in,0,sizeof(m_in));
	m_mario.setTransparent(255);
	if(m_mario.getEtat()==MORT)
	{
		m_mario.retrecir();
		m_niveau=m_fichier.chargerNiveau();
		m_temps=m_fichier.getTime()*60;
		afficherScene(ecran,type,music);
		m_bandit1s.clear();
		music.jouerMusic(m_fichier.getMusic());

		for(int i=0; i < m_niveau.size(); i++)
		{
			for(int j=0; j < m_niveau[i].size(); j++)
			{
				if(m_niveau[i][j]==MARIO)
				{
					SDL_Rect posMario;
					posMario.x=i*TAILLE_BLOC;
					posMario.y=j*TAILLE_BLOC;
					m_mario.setRect(posMario);
				}
				else if(m_niveau[i][j]==BANDIT_1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoBandit(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==DINAU)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoDinau(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==TORTUE)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoTortue(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PIQUANT)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPiquant(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PIQUANT1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPiquant1(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==SUIVEUR)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoSuiveur(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PASSEUR)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPasseur(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PASSEUR1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPasseur1(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CASSABLE)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCassable(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==SAUTEUR)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoSauteur(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CANARD)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCanard(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CANON1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=(j*TAILLE_BLOC)-TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCanon1(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CANON2)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCanon2(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==BOSS1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoBoss(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==BOSS2)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoBoss2(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
			}
		}
	}
	else if(m_fichier.updateNiveau())
	{
		m_mario.retrecir();
		m_niveau=m_fichier.chargerNiveau();
		m_temps=m_fichier.getTime()*60;
		afficherScene(ecran,type,music);
		m_bandit1s.clear();
		music.jouerMusic(m_fichier.getMusic());

		if(m_fichier.getNiveau() < 10 && m_fichier.getNiveau() % 3==0)
			m_level++;

		for(int i=0; i < m_niveau.size(); i++)
		{
			for(int j=0; j < m_niveau[i].size(); j++)
			{
				if(m_niveau[i][j]==MARIO)
				{
					SDL_Rect posMario;
					posMario.x=i*TAILLE_BLOC;
					posMario.y=j*TAILLE_BLOC;
					m_mario.setRect(posMario);
				}
				else if(m_niveau[i][j]==BANDIT_1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoBandit(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==DINAU)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoDinau(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==TORTUE)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoTortue(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PIQUANT1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPiquant1(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PIQUANT)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPiquant(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==SUIVEUR)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoSuiveur(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PASSEUR)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPasseur(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==PASSEUR1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoPasseur1(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CASSABLE)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCassable(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==SAUTEUR)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoSauteur(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CANARD)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCanard(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CANON1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=(j*TAILLE_BLOC)-TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCanon1(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==CANON2)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoCanon2(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==BOSS1)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoBoss(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
				else if(m_niveau[i][j]==BOSS2)
				{
					SDL_Rect posPerso;
					posPerso.x=i*TAILLE_BLOC;
					posPerso.y=j*TAILLE_BLOC;
					m_bandit1s.push_back(new PersoBoss2(m_level));
					m_bandit1s.back()->setRect(posPerso);
				}
			}
		}
	}
	else
	{
		afficherScene(ecran,3,music);
		m_continuer=false;
	}
}
void Jeu::updateEvents()
{
	while(SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			m_continuer=false;
			break;
		case SDL_KEYDOWN:
			m_in.key[m_event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			m_in.key[m_event.key.keysym.sym]=0;
			break;
		case SDL_JOYBUTTONDOWN:
			m_in.joystickButtons[m_event.jbutton.button]=1;
			break;
		case SDL_JOYBUTTONUP:
			m_in.joystickButtons[m_event.jbutton.button]=0;
			break;
		case SDL_JOYAXISMOTION:
			if (m_event.jaxis.axis == 0 && m_event.jaxis.value == -32768)
				m_in.mouseG=true;
			else
				m_in.mouseG=false;
			if (m_event.jaxis.axis == 0 && m_event.jaxis.value == 32767)
				m_in.mouseD=true;
			else
				m_in.mouseD=false;
			if (m_event.jaxis.axis == 1 && m_event.jaxis.value == -32768)
				m_in.mouseH=true;
			else
				m_in.mouseH=false;
			if (m_event.jaxis.axis == 1 && m_event.jaxis.value == 32767)
				m_in.mouseB=true;
			else
				m_in.mouseB=false;
			break;
		default:
			break;
		}
	}
}

void Jeu::afficherMenu(SDL_Surface *ecran)
{
	SDL_FillRect(m_objets[0], NULL, SDL_MapRGB(ecran->format,255,255,255));
	for(int i=0;i<m_objets.size();i++)
	{
		SDL_BlitSurface(m_objets[i], NULL, ecran, &m_posObjets[i]);
	}
}
void Jeu::pause()
{
	if(m_in.key[SDLK_p])
	{
		m_pause=true;
	}
	else
	{
		while(m_pause && m_continuer && SDL_WaitEvent(&m_event))
		{
			switch(m_event.type)
			{
				case SDL_QUIT:
					m_continuer = false;
				break;
				case SDL_KEYDOWN:
				switch(m_event.key.keysym.sym)
				{
					case SDLK_p:
					m_pause = false;
					break;
					case SDLK_ESCAPE:
					m_continuer = false;
					break;
				}
				break;
			}
		}
	}
}

void Jeu::quitter()
{
	if(m_in.key[SDLK_ESCAPE] || m_in.key[SDL_QUIT])
		m_continuer=false;
}

void Jeu::updateMenu()
{
	if (SDL_GetTicks() - m_getstickTemps >= 1000)
		{
			m_getstickTemps = SDL_GetTicks();
			m_temps-=1;
			if(m_temps==0)
			{
				m_mario.recevoirDegat(1);
				m_mario.setEtat(MORT);
			}
		}

	if(m_temps < 10)
		sprintf(m_tempsJeu, "Temps  00%d", m_temps);
	else if(m_temps < 100)
		sprintf(m_tempsJeu, "Temps  0%d", m_temps);
	else
		sprintf(m_tempsJeu, "Temps  %d", m_temps);

	if(m_mario.getVies() < 10)
		sprintf(m_nbreVie, "X  0%d", m_mario.getVies());
	else
		sprintf(m_nbreVie, "X  %d", m_mario.getVies());
	
	if(m_mario.getPieces() < 10)
		sprintf(m_nbrePiece, "X 0%d",  m_mario.getPieces());
	else
		sprintf(m_nbrePiece, "X %d",  m_mario.getPieces());

	if(m_mario.getPoints() < 10)
		sprintf(m_point, "Points  0000%d",  m_mario.getPoints());
	else if(m_mario.getPoints() < 100)
		sprintf(m_point, "Points  000%d",  m_mario.getPoints());
	else if(m_mario.getPoints() < 1000)
		sprintf(m_point, "Points  000%d",  m_mario.getPoints());
	else if(m_mario.getPoints() < 10000)
		sprintf(m_point, "Points  0%d",  m_mario.getPoints());
	else
		sprintf(m_point, "Points  %d",  m_mario.getPoints());
	
	SDL_FreeSurface(m_objets[1]);
	SDL_FreeSurface(m_objets[3]);
	SDL_FreeSurface(m_objets[5]);
	SDL_FreeSurface(m_objets[6]);

	m_objets[1]=TTF_RenderText_Shaded(m_police, m_tempsJeu, m_couleurNoire, m_couleurBlanche);
	m_objets[3]=TTF_RenderText_Shaded(m_police, m_nbreVie, m_couleurNoire, m_couleurBlanche);
	m_objets[5]=TTF_RenderText_Shaded(m_police, m_nbrePiece, m_couleurNoire, m_couleurBlanche);
	m_objets[6]=TTF_RenderText_Shaded(m_police, m_point, m_couleurNoire, m_couleurBlanche);
}

void Jeu::controlEtat(SDL_Surface *ecran,Music &music)
{
	if(m_mario.getEtat()==MORT)
	{
		updateJeu(ecran,1,music);
	}
}

void Jeu::gestionBandits()
{
	for(int i=0;i<m_bandit1s.size();i++)
	{
		if(m_bandit1s[i]->estSurEcran(m_carte.getXscroll(),m_carte.getYscroll()))
		{
			if(m_bandit1s[i]->estTransparent())
			{
				if(m_bandit1s[i]->getTransparent() > 0)
				{
					m_bandit1s[i]->setTransparent(m_bandit1s[i]->getTransparent()-2);
					m_bandit1s[i]->setPosAffPoints(0,-2);
				}
				else
				{
					if(m_bandit1s[i]->getNom()=="PERSOBOSS" || m_bandit1s[i]->getNom()=="PERSOBOSS2")
					{
						m_niveau[m_bandit1s[i]->getRect().x/TAILLE_BLOC][m_bandit1s[i]->getRect().y/TAILLE_BLOC]=PORTE;
					}
					for(int j=i;j<m_bandit1s.size()-1;j++)
						m_bandit1s[j]=m_bandit1s[j+1];
					m_bandit1s.pop_back();
				}
			}
			else
			{
				m_bandit1s[i]->evoluer(m_niveau,m_mario,m_bandit1s,m_carte.getXscroll(),m_carte.getYscroll());
			}
		}
		else if(m_bandit1s[i]->getNom()=="FEU" || m_bandit1s[i]->getNom()=="PIERRE")
			m_bandit1s[i]->mourir();
	}
}

void Jeu::gestionMario(SDL_Surface *ecran,Music &music)
{
	if(m_mario.getMission())
	{
		updateJeu(ecran,2,music);
		m_mario.updateMission(false);
	}
	else if(m_mario.estVivant())
	{
		updateMenu();
		controlEtat(ecran,music);
	}
	else
	{
		updateJeu(ecran,3,music);
		m_continuer=false;
	}
	m_mario.evoluer(m_in,m_niveau,m_bandit1s,music,m_carte.getXscroll(),m_carte.getYscroll());
}

void Jeu::afficherBandits(SDL_Surface *ecran)
{
	for(int i=0;i<m_bandit1s.size();i++)
	{
		if(m_bandit1s[i]->estSurEcran(m_carte.getXscroll(),m_carte.getYscroll()))
		{
			m_bandit1s[i]->afficher(ecran,m_carte.getXscroll(),m_carte.getYscroll());
		}
	}
}
void Jeu::jouer(SDL_Surface *ecran,Music &music)
{	
	int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0,m=0,n=0,v=0;
	v= SDL_GetTicks();
	updateJeu(ecran,0,music);
	while(m_continuer)
	{
		a= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		updateEvents();

		b= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		gestionMario(ecran,music);

		d= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		gestionBandits();

		e= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		m_carte.evoluer(m_in,m_mario.getRect());

		f= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, m_fichier.getR(), m_fichier.getG(), m_fichier.getB()));
		
		g= SDL_GetTicks()-v;
		v=SDL_GetTicks();
		
		afficherMenu(ecran);

		h= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		m_carte.afficher(ecran,m_niveau);

		i= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		afficherBandits(ecran);

		j= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		m_mario.afficher(ecran,m_carte.getXscroll(),m_carte.getYscroll());

		k= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		SDL_Flip(ecran);

		l= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		pause();
		quitter();

		m= SDL_GetTicks()-v;
		v=SDL_GetTicks();

		m_tempsActuel = SDL_GetTicks();
		if (m_tempsActuel - m_tempsPrecedent > m_intervalTemps)
		{
			m_tempsPrecedent = m_tempsActuel;
		}
		else
		{
			SDL_Delay(m_intervalTemps - (m_tempsActuel - m_tempsPrecedent));
		}
	}
}

void Jeu::afficherScene(SDL_Surface *ecran,int type,Music &music)
{
	SDL_Rect posTitre,posTemps,posMario,posVie,posPiece,posNbrePiece,posPoint;
	int tempsActuel=0,tempsPrecedent=0,tempsScene=0;
	bool continuer=true;

	posTitre.w=200;
	posTitre.x=(LARGEUR_ECRAN-posTitre.w)/2;
	posTitre.y=TAILLE_BLOC*2 ;
	posTemps.w=200;
	posTemps.x= (LARGEUR_ECRAN-posTemps.w)/2;
	posTemps.y= TAILLE_BLOC * 8;
	posMario.w=m_objets[2]->w;
	posVie.w=150;
	posMario.x=(LARGEUR_ECRAN-posMario.w-posVie.w)/2;
	posVie.x=((LARGEUR_ECRAN-posMario.w-posVie.w)/2)+posMario.w+10;
	posMario.y=TAILLE_BLOC * 14;
	posVie.y=TAILLE_BLOC * 14;
	posPiece.w=m_objets[4]->w;
	posNbrePiece.w=150;
	posPiece.x=(LARGEUR_ECRAN-posPiece.w-posNbrePiece.w)/2;
	posNbrePiece.x=((LARGEUR_ECRAN-posPiece.w-posNbrePiece.w)/2)+posPiece.w+10;
	posPiece.y=TAILLE_BLOC * 20;
	posNbrePiece.y=TAILLE_BLOC * 20;
	posPoint.w=200;
	posPoint.x=(LARGEUR_ECRAN-posPoint.w)/2;
	posPoint.y=TAILLE_BLOC * 26;

	if(type==0)
	{
		music.jouerMusic(30);
		sprintf(m_tabTitre,"NIVEAU %d",m_fichier.getNiveau());
		tempsScene=15;
	}
	else if(type==1)
	{
		music.jouerMusic(31);
		sprintf(m_tabTitre,"VOUS ETES MORT !",m_fichier.getNiveau());
		tempsScene=10;
		posTitre.w=300;
		posTitre.x=(LARGEUR_ECRAN-posTitre.w)/2;
	}
	else if(type==2)
	{
		music.jouerMusic(32);
		sprintf(m_tabTitre,"NIVEAU %d",m_fichier.getNiveau());
		tempsScene=20;
	}
	else if(type==3)
	{
		music.jouerMusic(34);
		sprintf(m_tabTitre,"GAME OVER",m_fichier.getNiveau());
		tempsScene=15;
		posTitre.y=HAUTEUR_ECRAN/2;
	}
	else
	{
	}
	
	if(m_temps < 10)
		sprintf(m_tempsJeu, "Temps  00%d", m_temps);
	else if(m_temps < 100)
		sprintf(m_tempsJeu, "Temps  0%d", m_temps);
	else
		sprintf(m_tempsJeu, "Temps  %d", m_temps);

	if(m_mario.getVies() < 10)
		sprintf(m_nbreVie, "X  0%d", m_mario.getVies());
	else
		sprintf(m_nbreVie, "X  %d", m_mario.getVies());
	
	if(m_mario.getPieces() < 10)
		sprintf(m_nbrePiece, "X 0%d",  m_mario.getPieces());
	else
		sprintf(m_nbrePiece, "X %d",  m_mario.getPieces());

	if(m_mario.getPoints() < 10)
		sprintf(m_point, "Points  0000%d",  m_mario.getPoints());
	else if(m_mario.getPoints() < 100)
		sprintf(m_point, "Points  000%d",  m_mario.getPoints());
	else if(m_mario.getPoints() < 1000)
		sprintf(m_point, "Points  000%d",  m_mario.getPoints());
	else if(m_mario.getPoints() < 10000)
		sprintf(m_point, "Points  0%d",  m_mario.getPoints());
	else
		sprintf(m_point, "Points  %d",  m_mario.getPoints());
	
	SDL_FreeSurface(m_objets[1]);
	SDL_FreeSurface(m_objets[3]);
	SDL_FreeSurface(m_objets[5]);
	SDL_FreeSurface(m_objets[6]);
	SDL_FreeSurface(m_titre);

	m_objets[1]=TTF_RenderText_Shaded(m_police, m_tempsJeu, m_couleurBlanche, m_couleurNoire);
	m_objets[3]=TTF_RenderText_Shaded(m_police, m_nbreVie, m_couleurBlanche, m_couleurNoire);
	m_objets[5]=TTF_RenderText_Shaded(m_police, m_nbrePiece, m_couleurBlanche, m_couleurNoire);
	m_objets[6]=TTF_RenderText_Shaded(m_police, m_point, m_couleurBlanche, m_couleurNoire);
	m_titre=TTF_RenderText_Shaded(m_police, m_tabTitre, m_couleurBlanche, m_couleurNoire);

	tempsScene=tempsScene*1000;

	while(continuer)
	{
		SDL_PollEvent(&m_event);
		
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 100)
		{
			if(tempsScene <= 0)
				continuer=0;
			else
				tempsScene-=100;
		}
		else /* Si ça fait moins de 30ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
		{
			SDL_Delay(100 - (tempsActuel - tempsPrecedent));
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		if(type!=3)
		{
			SDL_BlitSurface(m_objets[1], NULL, ecran, &posTemps);
			SDL_SetColorKey(m_objets[2], SDL_SRCCOLORKEY, SDL_MapRGB(m_objets[2]->format, 255, 255, 0));
			SDL_BlitSurface(m_objets[2], NULL, ecran, &posMario);
			SDL_BlitSurface(m_objets[3], NULL, ecran, &posVie);
			SDL_SetColorKey(m_objets[4], SDL_SRCCOLORKEY, SDL_MapRGB(m_objets[4]->format, 255, 255, 0));
			SDL_BlitSurface(m_objets[4], NULL, ecran, &posPiece);
			SDL_BlitSurface(m_objets[5], NULL, ecran, &posNbrePiece);
			SDL_BlitSurface(m_objets[6], NULL, ecran, &posPoint);
		}
		SDL_BlitSurface(m_titre, NULL, ecran, &posTitre);

		SDL_Flip(ecran);
	}
}