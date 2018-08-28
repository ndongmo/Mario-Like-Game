#include "aide.h"

Aide::Aide()
{
	continuer=true;
	memset(&in,0,sizeof(in));
	s_fond.push_back(IMG_Load("images/aideAccueil.png"));
	s_fond.push_back(IMG_Load("images/aideJeu.png"));
	s_fond.push_back(IMG_Load("images/aideEdition.png"));
	s_fond.push_back(IMG_Load("images/aideMusic.png"));
	s_fond.push_back(IMG_Load("images/aideAide.png"));
	s_fond.push_back(IMG_Load("images/aideApropos.png"));
	s_fondEncours=s_fond.at(0);
	
	r_fond.x=0;
    r_fond.y=0;
}

Aide::~Aide()
{
	for(int i=0; i<s_fond.size();i++)
		SDL_FreeSurface(s_fond[i]);
}

void Aide::updateEvent()
{
	in.mouseButtons[SDL_BUTTON_WHEELUP] = 0;
	in.mouseButtons[SDL_BUTTON_WHEELDOWN] = 0;

	SDL_WaitEvent(&event);
	
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

void Aide::gestionTouches()
{
	if(in.key[SDLK_ESCAPE] || in.quit)
	{
		continuer=false;
	}
	if(in.mouseButtons[SDL_BUTTON_LEFT])
	{
		if(pointComplet(823,562,event.button.x,event.button.y,48,48))
		{
			continuer=false;
		}
		if(pointComplet(100,552,event.button.x,event.button.y,100,100))
		{
			s_fondEncours=s_fond.at(1);
		}
		if(pointComplet(250,552,event.button.x,event.button.y,100,100))
		{
			s_fondEncours=s_fond.at(2);
		}
		if(pointComplet(400,552,event.button.x,event.button.y,100,100))
		{
			s_fondEncours=s_fond.at(3);
		}
		if(pointComplet(550,552,event.button.x,event.button.y,100,100))
		{
			s_fondEncours=s_fond.at(4);
		}
		if(pointComplet(700,552,event.button.x,event.button.y,100,100))
		{
			s_fondEncours=s_fond.at(5);
		}
		in.mouseButtons[SDL_BUTTON_LEFT]=0;
	}
}
void Aide::afficher(SDL_Surface *ecran,Music &music)
{
	music.jouerMusic(12);
	while(continuer)
	{
		updateEvent();
		gestionTouches();
		SDL_BlitSurface(s_fondEncours, NULL, ecran, &r_fond);
		SDL_Flip(ecran);
	}
}

bool Aide::pointComplet(int x1, int y1,int x2,int y2,int w,int h)
{
	if(x2 < x1 || x2 > x1+w)
		return false;
	if(y2 < y1 || y2 > y1+h)
		return false;
	return true;
}