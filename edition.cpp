#include "edition.h"

Edition::Edition()
{
	m_carte;
	m_fichier;
	m_niveau.resize(NB_BLOC_LARGEUR_TOTAL,vector<int> (NB_BLOC_HAUTEUR_TOTAL,0));
	m_objets.resize(36,NULL);
	m_objetsJeu.resize(8,NULL);
	m_posObjets.resize(36);
	m_posObjetsJeu.resize(8);
	memset(&m_in,0,sizeof(m_in));
	m_continuer=true;
	m_clickDroitEnCour=false;
	m_clickGaucheEnCour=false;

	m_police=TTF_OpenFont("polices/times.TTF",20);
	m_couleurNoire.b=0;m_couleurNoire.g=0;m_couleurNoire.r=0;
	m_couleurBlanche.b=149;m_couleurBlanche.g=227;m_couleurBlanche.r=244;

	sprintf(m_music, "Music:0%d",0);
	sprintf(m_tempsJeu, "Temps:0%d", m_fichier.getTime());
	sprintf(m_red, "Rouge:00%d", m_fichier.getR());
	sprintf(m_green, "Vert:00%d",  m_fichier.getG());
	sprintf(m_blue, "Bleue:00%d",  m_fichier.getB());
	
	initialiserPosObjets();

	m_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, m_posMenu.w, m_posMenu.h, 32, 0, 0, 0, 0);
	m_objets[0]=NULL;
	m_objets[1]=IMG_Load("images/porte.png");
	m_objets[2]=IMG_Load("images/mur.png");
	m_objets[3]=IMG_Load("images/nuage.png");
	m_objets[4]=IMG_Load("images/marioD1.png");
	m_objets[5]=IMG_Load("images/sol.png");
	m_objets[6]=IMG_Load("images/brique.png");
	m_objets[7]=IMG_Load("images/herbe.png");
	m_objets[8]=IMG_Load("images/bonus.png");
	m_objets[9]=IMG_Load("images/bonusOk.png");
	m_objets[10]=IMG_Load("images/piece.png");
	m_objets[11]=IMG_Load("images/invisible0.png");
	m_objets[12]=IMG_Load("images/bandit1.png");
	m_objets[13]=IMG_Load("images/piquant.png");
	m_objets[14]=IMG_Load("images/suiveur.png");
	m_objets[15]=IMG_Load("images/canon1.png");
	m_objets[16]=IMG_Load("images/canon2.png");
	m_objets[17]=IMG_Load("images/sauteur1.png");
	m_objets[18]=IMG_Load("images/pondeur.png");
	m_objets[19]=IMG_Load("images/fleur.png");
	m_objets[20]=IMG_Load("images/passeur.png");
	m_objets[21]=IMG_Load("images/gazon1.png");
	m_objets[22]=IMG_Load("images/gazon2.png");
	m_objets[23]=IMG_Load("images/gazon3.png");
	m_objets[24]=IMG_Load("images/gazon11.png");
	m_objets[25]=IMG_Load("images/gazon22.png");
	m_objets[26]=IMG_Load("images/gazon33.png");
	m_objets[27]=IMG_Load("images/terre.png");
	m_objets[28]=IMG_Load("images/tortueD.png");
	m_objets[29]=IMG_Load("images/boss1.png");
	m_objets[30]=IMG_Load("images/passeur1.png");
	m_objets[31]=IMG_Load("images/briqueCassable.png");
	m_objets[32]=IMG_Load("images/piquant1.png");
	m_objets[33]=IMG_Load("images/boss2.png");
	m_objets[34]=IMG_Load("images/canard.png");
	m_objets[35]=IMG_Load("images/dinau.png");
	
	m_objetsJeu[0]=IMG_Load("images/precedent2x.png");
	m_objetsJeu[1]=IMG_Load("images/suivant2.png");
	m_objetsJeu[2]=IMG_Load("images/hautX.png");
	m_objetsJeu[3]=IMG_Load("images/bas.png");
	m_objetsJeu[4]=IMG_Load("images/envoyer.png");
	m_objetsJeu[5]=IMG_Load("images/save.png");
	m_objetsJeu[6]=IMG_Load("images/effacer.png");
	m_objetsJeu[7]=IMG_Load("images/quit.png");

	m_objetMusic=TTF_RenderText_Shaded(m_police, m_music, m_couleurNoire, m_couleurBlanche);
	m_objetTemps=TTF_RenderText_Shaded(m_police, m_tempsJeu, m_couleurNoire, m_couleurBlanche);
	m_objetRed=TTF_RenderText_Shaded(m_police, m_red, m_couleurNoire, m_couleurBlanche);
	m_objetGreen=TTF_RenderText_Shaded(m_police, m_green, m_couleurNoire, m_couleurBlanche);
	m_objetBlue=TTF_RenderText_Shaded(m_police, m_blue, m_couleurNoire, m_couleurBlanche);
	m_objetEnCour=m_objets[5];
	m_indexEnCour=SOL;
}

void Edition::updateEvents(Music &music)
{
	SDL_WaitEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_QUIT:
		m_continuer=false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		gestionClick(music);
		break;
	case SDL_MOUSEBUTTONUP:
		if(m_event.button.button==SDL_BUTTON_RIGHT)
			m_clickDroitEnCour=false;
		else if(m_event.button.button==SDL_BUTTON_LEFT)
			m_clickGaucheEnCour=false;
		break;
	 case SDL_MOUSEMOTION:
		gestionMotion();
		break;
	case SDL_KEYDOWN:
		m_in.key[m_event.key.keysym.sym]=1;
		break;
	case SDL_KEYUP:
		m_in.key[m_event.key.keysym.sym]=0;
		break;
	default:
		break;
	}
}

void Edition::editer(SDL_Surface *ecran, Music &music)
{
	SDL_EnableKeyRepeat(30, 30);
	//music.jouerMusic(1);
	while(m_continuer)
	{
		updateEvents(music);
		gestionTouche(music);
		modifTexte();
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, m_fichier.getR(), m_fichier.getG(), m_fichier.getB()));
		SDL_FillRect(m_menu, NULL, SDL_MapRGB(ecran->format,244,227,149));
		SDL_BlitSurface(m_menu, NULL, ecran, &m_posMenu);
		afficherObjets(ecran);
		m_carte.afficherTous(ecran,m_niveau);
		if(m_affObjetEnCour)
			SDL_BlitSurface(m_objetEnCour, NULL, ecran, &m_posObjetEnCour);
		SDL_Flip(ecran);
	}
}

void Edition::initialiserPosObjets()
{
	m_posMenu.x=0;
	m_posMenu.y=HAUTEUR_ECRAN;
	m_posMenu.h=TAILLE_ECRAN_H - HAUTEUR_ECRAN;
	m_posMenu.w=LARGEUR_ECRAN;

	m_posObjetEnCour.x=0;
	m_posObjetEnCour.y=0;

	m_posTemps.x=0;
	m_posTemps.y=TAILLE_ECRAN_H-TAILLE_BLOC;
	m_posRed.x=150;
	m_posRed.y=TAILLE_ECRAN_H-TAILLE_BLOC;
	m_posGreen.x=300;
	m_posGreen.y=TAILLE_ECRAN_H-TAILLE_BLOC;
	m_posBlue.x=450;
	m_posBlue.y=TAILLE_ECRAN_H-TAILLE_BLOC;
	m_posMusic.x=600;
	m_posMusic.y=TAILLE_ECRAN_H-TAILLE_BLOC;
	m_posTemps.w=m_posRed.x - m_posTemps.x;
	m_posRed.w=m_posGreen.x - m_posRed.x;
	m_posGreen.w=m_posBlue.x - m_posGreen.x;
	m_posBlue.w=m_posMusic.x - m_posBlue.x;
	m_posMusic.w=LARGEUR_ECRAN - m_posMusic.x;
	
	for(int j=m_posMenu.y; j < m_posMenu.y+TAILLE_BLOC; j+=TAILLE_BLOC)
	{
		for(int i=m_posMenu.x; i < m_posObjets.size()*TAILLE_BLOC; i+=TAILLE_BLOC)
		{
			SDL_Rect pos;
			pos.x=i;
			pos.y=j;
			m_posObjets[i/TAILLE_BLOC]=pos;
		}
	}
	for(int j=TAILLE_ECRAN_H-(TAILLE_BLOC*2); j < TAILLE_ECRAN_H-TAILLE_BLOC; j+=TAILLE_BLOC)
	{
		for(int i=m_posMenu.x; i < m_posObjetsJeu.size()*TAILLE_BLOC; i+=TAILLE_BLOC)
		{
			SDL_Rect pos;
			pos.x=i;
			pos.y=j;
			m_posObjetsJeu[i/TAILLE_BLOC]=pos;
		}
	}
}

void Edition::afficherObjets(SDL_Surface *ecran)
{
	for(int i=1; i < m_objets.size(); i++)
	{
		SDL_BlitSurface(m_objets[i],NULL,ecran,&m_posObjets[i]);
	}
	for(int i=0; i < m_objetsJeu.size(); i++)
	{
		SDL_BlitSurface(m_objetsJeu[i],NULL,ecran,&m_posObjetsJeu[i]);
	}
	SDL_BlitSurface(m_objetTemps,NULL,ecran,&m_posTemps);
	SDL_BlitSurface(m_objetRed,NULL,ecran,&m_posRed);
	SDL_BlitSurface(m_objetGreen,NULL,ecran,&m_posGreen);
	SDL_BlitSurface(m_objetBlue,NULL,ecran,&m_posBlue);
	SDL_BlitSurface(m_objetMusic,NULL,ecran,&m_posMusic);
}

void Edition::init(Music &music)
{
	m_fichier.initialiser();
	music.jouerMusic(m_fichier.getMusic());
	m_niveau.clear();
	m_niveau.resize(NB_BLOC_LARGEUR_TOTAL,vector<int> (NB_BLOC_HAUTEUR_TOTAL,0));
	m_carte.setXscroll(0);
	m_carte.setYscroll(0);
	m_objetsJeu[0]=IMG_Load("images/precedent2x.png");
	m_objetsJeu[1]=IMG_Load("images/suivant2.png");
	m_objetsJeu[2]=IMG_Load("images/hautX.png");
	m_objetsJeu[3]=IMG_Load("images/bas.png");
}
void Edition::initialiserEdition(Music &music)
{
	if(m_fichier.updateNiveau())
	{
		m_niveau=m_fichier.chargerNiveau();
		m_objetsJeu[0]=IMG_Load("images/precedent2x.png");
		m_objetsJeu[1]=IMG_Load("images/suivant2.png");
		m_objetsJeu[2]=IMG_Load("images/hautX.png");
		m_objetsJeu[3]=IMG_Load("images/bas.png");
		music.jouerMusic(m_fichier.getMusic());
	}
	else
	{
		init(music);
	}
}

void Edition::modifTexte()
{
	if(m_fichier.getMusic() < 10)
		sprintf(m_music, "Music:0%d",m_fichier.getMusic());
	else
		sprintf(m_music, "Music:%d",m_fichier.getMusic());

	if(m_fichier.getTime() < 10)
		sprintf(m_tempsJeu, "Temps:0%d", m_fichier.getTime());
	else
		sprintf(m_tempsJeu, "Temps:%d", m_fichier.getTime());

	if(m_fichier.getR() < 10)
		sprintf(m_red, "Rouge:00%d", m_fichier.getR());
	else if(m_fichier.getR()< 100)
		sprintf(m_red, "Rouge:0%d", m_fichier.getR());
	else
		sprintf(m_red, "Rouge:%d", m_fichier.getR());
	
	if(m_fichier.getG() < 10)
		sprintf(m_green, "Vert:00%d",  m_fichier.getG());
	else if(m_fichier.getG() < 100)
		sprintf(m_green, "Vert:0%d",  m_fichier.getG());
	else
		sprintf(m_green, "Vert:%d",  m_fichier.getG());

	if(m_fichier.getB() < 10)
		sprintf(m_blue, "Bleue:00%d",  m_fichier.getB());
	else if(m_fichier.getB() < 100)
		sprintf(m_blue, "Bleue:0%d",  m_fichier.getB());
	else
		sprintf(m_blue, "Bleue:%d",  m_fichier.getB());
	
	m_objetMusic=TTF_RenderText_Shaded(m_police, m_music, m_couleurNoire, m_couleurBlanche);
	m_objetTemps = TTF_RenderText_Shaded(m_police, m_tempsJeu, m_couleurNoire, m_couleurBlanche);
	m_objetRed = TTF_RenderText_Shaded(m_police, m_red, m_couleurNoire, m_couleurBlanche);
	m_objetGreen = TTF_RenderText_Shaded(m_police, m_green, m_couleurNoire, m_couleurBlanche);
	m_objetBlue = TTF_RenderText_Shaded(m_police, m_blue, m_couleurNoire, m_couleurBlanche);
}

void Edition::gestionMotion()
{
	if(m_event.motion.y < HAUTEUR_ECRAN)
	{
		if (m_clickGaucheEnCour)
		{
			m_niveau[(m_event.button.x +m_carte.getXscroll())/ TAILLE_BLOC][(m_event.button.y+m_carte.getYscroll()) / TAILLE_BLOC] = m_indexEnCour;
		}
		else if (m_clickDroitEnCour)
		{
			m_niveau[(m_event.button.x +m_carte.getXscroll())/ TAILLE_BLOC][(m_event.button.y+m_carte.getYscroll()) / TAILLE_BLOC] = VIDE;
		}
		
		m_posObjetEnCour.x = m_event.motion.x-(TAILLE_BLOC/2); 
		m_posObjetEnCour.y = m_event.motion.y-(TAILLE_BLOC/2);
		//SDL_ShowCursor(SDL_DISABLE);
		m_affObjetEnCour=true;
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
		m_affObjetEnCour=false;
	}
}

void Edition::gestionClick(Music &music)
{
	if(m_event.button.button == SDL_BUTTON_LEFT)
	{
		if(m_event.button.y < HAUTEUR_ECRAN)
		{
			if(m_indexEnCour==MARIO)
			{
				if(!m_carte.rechercher(m_niveau,MARIO))
				{
					m_niveau[(m_event.button.x +m_carte.getXscroll())/ TAILLE_BLOC][(m_event.button.y+m_carte.getYscroll()) / TAILLE_BLOC] = m_indexEnCour;
				}
			}
			else
			{
				m_niveau[(m_event.button.x +m_carte.getXscroll())/ TAILLE_BLOC][(m_event.button.y+m_carte.getYscroll()) / TAILLE_BLOC] = m_indexEnCour;
				m_clickGaucheEnCour = true;
			}
		}
		else if(m_event.button.y > HAUTEUR_ECRAN && m_event.button.y < TAILLE_ECRAN_H-(TAILLE_BLOC*2))
		{
			for(int i=0;i<m_posObjets.size();i++)
			{
				if(point(m_posObjets[i].x,m_posObjets[i].y,m_event.button.x,m_event.button.y))
				{
					m_objetEnCour=m_objets[i];
					m_indexEnCour=i;
					music.jouerSon(0);
				}
			}
		}
		else if(m_event.button.y > TAILLE_ECRAN_H-(TAILLE_BLOC*2) && m_event.button.y < TAILLE_ECRAN_H-TAILLE_BLOC)
		{
			for(int i=0;i<m_posObjetsJeu.size();i++)
			{
				if(point(m_posObjetsJeu[i].x,m_posObjetsJeu[i].y,m_event.button.x,m_event.button.y))
				{
					gestionDivers(i,music);
				}
			}
		}
		else
		{
			if(pointComplet(m_posTemps.x,m_posTemps.y,m_event.button.x,m_event.button.y,m_posTemps.w,TAILLE_BLOC))
			{
				m_fichier.setTime(true);
				//m_clickGaucheEnCour = true;
			}
			else if(pointComplet(m_posRed.x,m_posRed.y,m_event.button.x,m_event.button.y,m_posRed.w,TAILLE_BLOC))
			{
				m_fichier.setR(true);
				//m_clickGaucheEnCour = true;
			}
			else if(pointComplet(m_posGreen.x,m_posGreen.y,m_event.button.x,m_event.button.y,m_posGreen.w,TAILLE_BLOC))
			{
				m_fichier.setG(true);
				//m_clickGaucheEnCour = true;
			}
			else if(pointComplet(m_posBlue.x,m_posBlue.y,m_event.button.x,m_event.button.y,m_posBlue.w,TAILLE_BLOC))
			{
				m_fichier.setB(true);
				//m_clickGaucheEnCour = true;
			}
			else if(pointComplet(m_posMusic.x,m_posMusic.y,m_event.button.x,m_event.button.y,m_posMusic.w,TAILLE_BLOC))
			{
				m_fichier.setMusic(true);
				music.jouerMusic(m_fichier.getMusic());
			}
		}
	}
	else if(m_event.button.button == SDL_BUTTON_RIGHT)
	{
		if(m_event.button.y < HAUTEUR_ECRAN)
		{
			m_niveau[(m_event.button.x +m_carte.getXscroll())/ TAILLE_BLOC][(m_event.button.y+m_carte.getYscroll()) / TAILLE_BLOC] = VIDE;
			m_clickDroitEnCour = true;
		}
		else
		{
			if(pointComplet(m_posTemps.x,m_posTemps.y,m_event.button.x,m_event.button.y,m_posTemps.w,TAILLE_BLOC))
			{
				m_fichier.setTime(false);
				m_clickDroitEnCour = true;
			}
			else if(pointComplet(m_posRed.x,m_posRed.y,m_event.button.x,m_event.button.y,m_posRed.w,TAILLE_BLOC))
			{
				m_fichier.setR(false);
				m_clickDroitEnCour = true;
			}
			else if(pointComplet(m_posGreen.x,m_posGreen.y,m_event.button.x,m_event.button.y,m_posGreen.w,TAILLE_BLOC))
			{
				m_fichier.setG(false);
				m_clickDroitEnCour = true;
			}
			else if(pointComplet(m_posBlue.x,m_posBlue.y,m_event.button.x,m_event.button.y,m_posBlue.w,TAILLE_BLOC))
			{
				m_fichier.setB(false);
				m_clickDroitEnCour = true;
			}
			else if(pointComplet(m_posMusic.x,m_posMusic.y,m_event.button.x,m_event.button.y,m_posMusic.w,TAILLE_BLOC))
			{
				m_fichier.setMusic(false);
				music.jouerMusic(m_fichier.getMusic());
			}
		}
	}
}

void Edition::gestionMenu(Music &music)
{
	if(m_clickGaucheEnCour)
	{
		if(m_event.motion.y > TAILLE_ECRAN_H-(TAILLE_BLOC*2) && m_event.motion.y < TAILLE_ECRAN_H-TAILLE_BLOC)
		{
			for(int i=0;i<m_posObjetsJeu.size();i++)
			{
				if(point(m_posObjetsJeu[i].x,m_posObjetsJeu[i].y,m_event.motion.x,m_event.motion.y))
				{
					gestionDivers(i,music);
				}
			}
		}
		else
		{
			if(point(m_posTemps.x,m_posTemps.y,m_event.motion.x,m_event.motion.y))
			{
				m_fichier.setTime(true);
			}
			else if(point(m_posRed.x,m_posRed.y,m_event.motion.x,m_event.motion.y))
			{
				m_fichier.setR(true);
			}
			else if(point(m_posGreen.x,m_posGreen.y,m_event.motion.x,m_event.motion.y))
			{
				m_fichier.setG(true);
			}
			else if(point(m_posBlue.x,m_posBlue.y,m_event.motion.x,m_event.motion.y))
			{
				m_fichier.setB(true);
			}
			else if(point(m_posMusic.x,m_posMusic.y,m_event.motion.x,m_event.motion.y))
			{
				//m_fichier.setB(true);
			}
		}
	}
	else if(m_clickDroitEnCour)
	{
		if(point(m_posTemps.x,m_posTemps.y,m_event.motion.x,m_event.motion.y))
		{
			m_fichier.setTime(false);
		}
		else if(point(m_posRed.x,m_posRed.y,m_event.motion.x,m_event.motion.y))
		{
			m_fichier.setR(false);
		}
		else if(point(m_posGreen.x,m_posGreen.y,m_event.motion.x,m_event.motion.y))
		{
			m_fichier.setG(false);
		}
		else if(point(m_posBlue.x,m_posBlue.y,m_event.motion.x,m_event.motion.y))
		{
			m_fichier.setB(false);
		}
		else if(point(m_posMusic.x,m_posMusic.y,m_event.motion.x,m_event.motion.y))
		{
			//m_fichier.setB(false);
		}
	}
}

void Edition::gestionTouche(Music &music)
{
	if(m_in.key[SDLK_ESCAPE] || m_in.quit)
	{
		m_continuer=false;
	}
	if(m_in.key[SDLK_LEFT])
	{
		gestionDivers(0,music);
	}
	if(m_in.key[SDLK_RIGHT])
	{
		gestionDivers(1,music);
	}
	if(m_in.key[SDLK_UP])
	{
		gestionDivers(2,music);
	}
	if(m_in.key[SDLK_DOWN])
	{
		gestionDivers(3,music);
	}
}

bool Edition::point(int x1, int y1,int x2,int y2)
{
	if(x2 < x1 || x2 > x1+TAILLE_BLOC)
		return false;
	if(y2 < y1 || y2 > y1+TAILLE_BLOC)
		return false;
	return true;
}

bool Edition::pointComplet(int x1, int y1,int x2,int y2,int w,int h)
{
	if(x2 < x1 || x2 > x1+w)
		return false;
	if(y2 < y1 || y2 > y1+h)
		return false;
	return true;
}

void Edition::gestionDivers(int i,Music &music)
{
	switch(i)
	{
	case 0:
		if(m_carte.getXscroll() > 0)
		{
			m_carte.setXscroll(m_carte.getXscroll()-TAILLE_BLOC);
			m_objetsJeu[0]=IMG_Load("images/precedent2.png");
			m_objetsJeu[1]=IMG_Load("images/suivant2.png");
		}
		else
			m_objetsJeu[0]=IMG_Load("images/precedent2X.png");
		//m_clickGaucheEnCour = true;
		break;
	case 1:
		if(m_carte.getXscroll() < (NB_BLOC_LARGEUR_TOTAL-NB_BLOC_LARGEUR)*TAILLE_BLOC)
		{
			m_carte.setXscroll(m_carte.getXscroll()+TAILLE_BLOC);
			m_objetsJeu[0]=IMG_Load("images/precedent2.png");
			m_objetsJeu[1]=IMG_Load("images/suivant2.png");
		}
		else
			m_objetsJeu[1]=IMG_Load("images/suivant2X.png");
		//m_clickGaucheEnCour = true;
		break;
	case 2:
		if(m_carte.getYscroll() > 0)
		{
			m_carte.setYscroll(m_carte.getYscroll()-TAILLE_BLOC);
			m_objetsJeu[2]=IMG_Load("images/haut.png");
			m_objetsJeu[3]=IMG_Load("images/bas.png");
		}
		else
			m_objetsJeu[2]=IMG_Load("images/hautX.png");
		//m_clickGaucheEnCour = true;
		break;
	case 3:
		if(m_carte.getYscroll() < (NB_BLOC_HAUTEUR_TOTAL-NB_BLOC_HAUTEUR)*TAILLE_BLOC)
		{
			m_carte.setYscroll(m_carte.getYscroll()+TAILLE_BLOC);
			m_objetsJeu[2]=IMG_Load("images/haut.png");
			m_objetsJeu[3]=IMG_Load("images/bas.png");
		}
		else
			m_objetsJeu[3]=IMG_Load("images/basX.png");
		//m_clickGaucheEnCour = true;
		break;
		case 4:
			initialiserEdition(music);
		break;
		case 5:
			if(m_carte.rechercher(m_niveau,MARIO) && m_fichier.sauvegarderNiveau(m_niveau))
			{
				init(music);
				music.jouerSon(3);
			}
			else
				music.jouerSon(4);
		break;
		case 6:
			if(m_fichier.supprimerNiveau())
			{
				init(music);
				music.jouerSon(3);
			}
			else
				music.jouerSon(4);
		break;
		case 7:
			m_continuer=false;
		break;
	}
}
Edition::~Edition()
{
	for(int i=0;i<m_objets.size();i++)
	{
		SDL_FreeSurface(m_objets[i]);
	}
	for(int i=0;i<m_objetsJeu.size();i++)
	{
		SDL_FreeSurface(m_objetsJeu[i]);
	}
	m_objetEnCour=NULL;
	SDL_FreeSurface(m_objetMusic);
	SDL_FreeSurface(m_objetTemps);
	SDL_FreeSurface(m_objetRed);
	SDL_FreeSurface(m_objetGreen);
	SDL_FreeSurface(m_objetBlue);
	SDL_FreeSurface(m_objetEnCour);
	SDL_FreeSurface(m_menu);
	TTF_CloseFont(m_police); 
}