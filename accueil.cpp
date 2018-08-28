#include "accueil.h"

Accueil::Accueil(SDL_Joystick *joystick)
{
	continuer=true;
	memset(&in,0,sizeof(in));
	m_joystick=joystick;

	joystickDActif=false;
	joystickGActif=false; 
	joystickBActif=false;
	joystickHActif=false;

	m_tempsActuel=0;
	m_tempsPrecedent=0;
	m_intervalTemps=50;
	m_level=1;

	s_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_ECRAN, 40, 32, 0, 0, 0, 0);
	s_fond=IMG_Load("images/accueil.png");
	carres.push_back(new CarreMenu("JEU","images/jeu.bmp",10,88,0));
	carres.push_back(new CarreMenu("EDITION","images/edition.bmp",34,21,1));
	carres.push_back(new CarreMenu("MUSIC","images/music.bmp",100,55,2));
	carres.push_back(new CarreMenu("AIDE","images/aide.bmp",24,47,3));
	carres.push_back(new CarreMenu("APROPOS","images/apropos.bmp",177,25,4));
	s_sourie=IMG_Load("images/souris.png");
	s_facile=SDL_LoadBMP("images/facile.bmp");
	s_normal=SDL_LoadBMP("images/normal.bmp");
	s_difficile=SDL_LoadBMP("images/difficile.bmp");
	SDL_SetColorKey(s_facile, SDL_SRCCOLORKEY, SDL_MapRGB(s_facile->format, 0, 0, 0));
	SDL_SetColorKey(s_normal, SDL_SRCCOLORKEY, SDL_MapRGB(s_normal->format, 0, 0, 0));
	SDL_SetAlpha(s_normal, SDL_SRCALPHA, 122);
	SDL_SetColorKey(s_difficile, SDL_SRCCOLORKEY, SDL_MapRGB(s_difficile->format, 0, 0, 0));
	
	r_sourie.x=0;
	r_sourie.y=0;
	r_sourie.h=20;
	r_sourie.w=20;

	r_menu.h=40;
	r_menu.x=0;
	r_menu.y=TAILLE_ECRAN_H-40;

	r_fond.x=0;
    r_fond.y=0;

	r_facile.h=40;
	r_facile.w=100;
	r_facile.x=100;
	r_facile.y=TAILLE_ECRAN_H-40;
	
	r_normal.h=40;
	r_normal.w=100;
	r_normal.x=(LARGEUR_ECRAN-100)/2;
	r_normal.y=TAILLE_ECRAN_H-40;

	r_difficile.h=40;
	r_difficile.w=100;
	r_difficile.x=LARGEUR_ECRAN-200;
	r_difficile.y=TAILLE_ECRAN_H-40;

	SDL_Rect posJeu,posEdition,posMusic,posAide,posApropos;
	posJeu.x=10;
	posJeu.y=10;
	posEdition.x=LARGEUR_ECRAN-150;
	posEdition.y=400;
	posMusic.x=LARGEUR_ECRAN-400;
	posMusic.y=TAILLE_ECRAN_H-150;
	posAide.x=LARGEUR_ECRAN-400;
	posAide.y=TAILLE_ECRAN_H-400;
	posApropos.x=LARGEUR_ECRAN-700;
	posApropos.y=TAILLE_ECRAN_H-200;

	carres[0]->setRect(posJeu);
	carres[1]->setRect(posEdition);
	carres[2]->setRect(posMusic);
	carres[3]->setRect(posAide);
	carres[4]->setRect(posApropos);
}

Accueil::~Accueil()
{
	SDL_FreeSurface(s_sourie);
	SDL_FreeSurface(s_menu);
	SDL_FreeSurface(s_facile);
	SDL_FreeSurface(s_normal);
	SDL_FreeSurface(s_difficile);
	m_joystick=NULL;
}

void Accueil::afficher(SDL_Surface *ecran,Music &music)
{
	SDL_ShowCursor(SDL_DISABLE);
	while(continuer)
	{
		for(int i=0;i<carres.size();i++)
			carres[i]->evoluer(carres,music);
		gestionEvent();
		gestionTouches(ecran,music);
		blitter(ecran);
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

void Accueil::gestionEvent()
{
	in.mouseButtons[SDL_BUTTON_WHEELUP] = 0;
	in.mouseButtons[SDL_BUTTON_WHEELDOWN] = 0;

	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in.key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in.key[event.key.keysym.sym]=0;
			break;
		case SDL_MOUSEMOTION:
			in.mousex=event.motion.x;
			in.mousey=event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			in.mouseButtons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
				in.mouseButtons[event.button.button]=0;
			break;
		case SDL_QUIT:
			in.quit = 1;
			break;
		default:
			break;
		}
	}
}

void Accueil::gestionTouches(SDL_Surface *ecran,Music &music)
{
	if(SDL_MOUSEMOTION)
	{
		r_sourie.x=in.mousex-(r_sourie.w/2);
		r_sourie.y=in.mousey-(r_sourie.h/2);
	}
	if(in.key[SDLK_ESCAPE] || in.quit)
	{
		continuer=false;
	}
	if(in.key[SDLK_e])
	{
		Edition edit;
		edit.editer(ecran,music);
		in.key[SDLK_e]=0;
		music.jouerMusic(0);
	}
	if(in.key[SDLK_j])
	{
		Jeu jeu(m_level);
		jeu.jouer(ecran,music);
		in.key[SDLK_j]=0;
		music.jouerMusic(0);
	}
	if(in.key[SDLK_m])
	{
		SDL_ShowCursor(SDL_ENABLE);
		music.setDSP(true);
		Lecteur lecteur;
		lecteur.afficher(ecran,music);
		music.setDSP(false);
		in.key[SDLK_m]=0;
		music.jouerMusic(0);
		SDL_ShowCursor(SDL_DISABLE);
	}
	if(in.key[SDLK_a])
	{
		SDL_ShowCursor(SDL_ENABLE);
		Aide aide;
		aide.afficher(ecran,music);
		in.key[SDLK_a]=0;
		music.jouerMusic(0);
		SDL_ShowCursor(SDL_DISABLE);
	}
	if(in.key[SDLK_p])
	{
		SDL_ShowCursor(SDL_ENABLE);
		Apropos propos;
		propos.afficher(ecran,music);
		in.key[SDLK_p]=0;
		music.jouerMusic(0);
		SDL_ShowCursor(SDL_DISABLE);
	}
	if(in.mouseButtons[SDL_BUTTON_LEFT])
	{
		for(int i=0;i<carres.size();i++)
		{
			if(pointComplet(carres[i]->getRect().x,carres[i]->getRect().y,event.button.x,event.button.y,carres[i]->getRect().w,carres[i]->getRect().h))
			{
				if(carres[i]->getNom()=="JEU")
				{
					Jeu jeu(m_level);
					jeu.jouer(ecran,music);
					music.jouerMusic(0);
				}
				else if(carres[i]->getNom()=="EDITION")
				{
					Edition edit;
					edit.editer(ecran,music);
					music.jouerMusic(0);
				}
				else if(carres[i]->getNom()=="MUSIC")
				{
					SDL_ShowCursor(SDL_ENABLE);
					music.setDSP(true);
					Lecteur lecteur;
					lecteur.afficher(ecran,music);
					music.setDSP(false);
					music.jouerMusic(0);
					SDL_ShowCursor(SDL_DISABLE);
				}
				else if(carres[i]->getNom()=="AIDE")
				{
					SDL_ShowCursor(SDL_ENABLE);
					Aide aide;
					aide.afficher(ecran,music);
					music.jouerMusic(0);
					SDL_ShowCursor(SDL_DISABLE);
				}
				else if(carres[i]->getNom()=="APROPOS")
				{
					SDL_ShowCursor(SDL_ENABLE);
					Apropos propos;
					propos.afficher(ecran,music);
					music.jouerMusic(0);
					SDL_ShowCursor(SDL_DISABLE);
				}
			}
		}
		if(pointComplet(r_facile.x,r_facile.y,event.button.x,event.button.y,r_facile.w,r_facile.h))
		{
			SDL_SetAlpha(s_facile, SDL_SRCALPHA, 122);
			SDL_SetAlpha(s_normal, SDL_SRCALPHA, 255);
			SDL_SetAlpha(s_difficile, SDL_SRCALPHA, 255);
			for(int i=0;i<carres.size();i++)
				carres[i]->setVitesse(6,6);
			m_level=0;
		}
		else if(pointComplet(r_normal.x,r_normal.y,event.button.x,event.button.y,r_normal.w,r_normal.h))
		{
			SDL_SetAlpha(s_facile, SDL_SRCALPHA, 255);
			SDL_SetAlpha(s_normal, SDL_SRCALPHA, 122);
			SDL_SetAlpha(s_difficile, SDL_SRCALPHA, 255);
			for(int i=0;i<carres.size();i++)
				carres[i]->setVitesse(8,8);
			m_level=1;
		}
		else if(pointComplet(r_difficile.x,r_difficile.y,event.button.x,event.button.y,r_difficile.w,r_difficile.h))
		{
			SDL_SetAlpha(s_facile, SDL_SRCALPHA, 255);
			SDL_SetAlpha(s_normal, SDL_SRCALPHA, 255);
			SDL_SetAlpha(s_difficile, SDL_SRCALPHA, 122);
			for(int i=0;i<carres.size();i++)
				carres[i]->setVitesse(10,10);
			m_level=2;
		}
		in.mouseButtons[SDL_BUTTON_LEFT]=0;
	}
}

void Accueil::blitter(SDL_Surface *ecran)
{
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 150, 249));
	SDL_BlitSurface(s_fond,NULL,ecran,&r_fond);
	SDL_FillRect(s_menu, NULL, SDL_MapRGB(ecran->format,1,121,255));
	SDL_BlitSurface(s_menu,NULL,ecran,&r_menu);
	SDL_BlitSurface(s_facile,NULL,ecran,&r_facile);
	SDL_BlitSurface(s_normal,NULL,ecran,&r_normal);
	SDL_BlitSurface(s_difficile,NULL,ecran,&r_difficile);
	for(int i=0;i<carres.size();i++)
		carres[i]->afficher(ecran);
	SDL_SetColorKey(s_sourie, SDL_SRCCOLORKEY, SDL_MapRGB(s_sourie->format, 255, 255, 0));
	SDL_BlitSurface(s_sourie,NULL,ecran,&r_sourie);
	SDL_Flip(ecran);
}

bool Accueil::pointComplet(int x1, int y1,int x2,int y2,int w,int h)
{
	if(x2 < x1 || x2 > x1+w)
		return false;
	if(y2 < y1 || y2 > y1+h)
		return false;
	return true;
}