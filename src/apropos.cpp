#include "apropos.h"

Apropos::Apropos()
{
	memset(&in,0,sizeof(in));
	s_fond=IMG_Load("images/menuApropos.png");
	continuer=true;
	r_fond.x=0;
    r_fond.y=0;
}

Apropos::~Apropos()
{
	SDL_FreeSurface(s_fond);
}

void Apropos::updateEvent()
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

void Apropos::gestionTouches()
{
	if(in.key[SDLK_ESCAPE] || in.quit)
	{
		continuer=false;
	}
	if(in.mouseButtons[SDL_BUTTON_LEFT])
	{
		if(pointComplet(857,557,event.button.x,event.button.y,60,60))
		{
			continuer=false;
		}
		
		in.mouseButtons[SDL_BUTTON_LEFT]=0;
	}
}
void Apropos::afficher(SDL_Surface *ecran,Music &music)
{
	music.jouerMusic(12);
	while(continuer)
	{
		updateEvent();
		gestionTouches();
		SDL_BlitSurface(s_fond, NULL, ecran, &r_fond);
		SDL_Flip(ecran);
	}
}

bool Apropos::pointComplet(int x1, int y1,int x2,int y2,int w,int h)
{
	if(x2 < x1 || x2 > x1+w)
		return false;
	if(y2 < y1 || y2 > y1+h)
		return false;
	return true;
}