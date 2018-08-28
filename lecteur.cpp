#include "lecteur.h"

Lecteur::Lecteur()
{
	memset(&m_in,0,sizeof(m_in));
	m_continuer=true;

	m_effet=SDL_CreateRGBSurface(SDL_HWSURFACE, 512, 520, 32, 0, 0, 0, 0);
	m_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_ECRAN,TAILLE_ECRAN_H-520, 32, 0, 0, 0, 0);
	m_touches=IMG_Load("images/images_lecteur/unselected.png");
	m_volume=IMG_Load("images/images_lecteur/volume_05.png");
	m_interval=25;
	m_ratio=m_effet->h/255.0;
	hauteurBarre = 0, tempsActuel = 0, tempsPrecedent = 0;
	spectre=NULL;
	appuyer=false;
}
Lecteur::~Lecteur()
{
	SDL_FreeSurface(m_effet);
	SDL_FreeSurface(m_touches);
	SDL_FreeSurface(m_volume);
}

void Lecteur::afficher(SDL_Surface *ecran,Music & music)
{
	initPosition();
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0, 0, 0));
	gestionVolume(music,5);
	while(m_continuer)
	{
		updateEvents();
		gestionEvent(music);
		SDL_FillRect(m_effet, NULL, SDL_MapRGB(ecran->format,0, 0, 0));
		spectre = FSOUND_DSP_GetSpectrum();
        SDL_LockSurface(m_effet);

        for (int i = 0 ; i < m_effet->w ; i++)
        {
            hauteurBarre = spectre[i] * 10 * m_effet->h;
            if(hauteurBarre > m_effet->h)
                hauteurBarre = m_effet->h;

            for (int j = m_effet->h - hauteurBarre ; j < m_effet->h ; j++)
            {
                setPixel(m_effet, i, j, SDL_MapRGB(ecran->format, 255 - (j / m_ratio), j / m_ratio, 0));
            }
        }

        SDL_UnlockSurface(m_effet);
		blitter(ecran);
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent < m_interval)
		{
			SDL_Delay(m_interval - (tempsActuel - tempsPrecedent));
		}
		tempsPrecedent = SDL_GetTicks();
	}
}

void Lecteur::updateEvents()
{
	m_in.mouseButtons[SDL_BUTTON_WHEELUP] = 0;
	m_in.mouseButtons[SDL_BUTTON_WHEELDOWN] = 0;

	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_KEYDOWN:
		m_in.key[m_event.key.keysym.sym]=1;
		break;
	case SDL_KEYUP:
		m_in.key[m_event.key.keysym.sym]=0;
		break;
	case SDL_MOUSEMOTION:
		m_in.mousex=m_event.motion.x;
		m_in.mousey=m_event.motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_in.mouseButtons[m_event.button.button]=1;
		break;
	case SDL_MOUSEBUTTONUP:
		if (m_event.button.button!=SDL_BUTTON_WHEELUP && m_event.button.button!=SDL_BUTTON_WHEELDOWN)
		{
			m_in.mouseButtons[m_event.button.button]=0;
			appuyer=false;
		}
		break;
	case SDL_QUIT:
		m_in.quit = 1;
		break;
	default:
		break;
	}
}

void Lecteur::initPosition()
{
	m_posEffet.x=0;
	m_posEffet.y=0;
	m_posEffet.h=m_effet->h;
	m_posEffet.w=m_effet->w;
	m_posTouches.x=0;
	m_posTouches.y=m_posEffet.h;
	m_posTouches.h=m_touches->h;
	m_posTouches.w=m_touches->w;
	m_posVolume.x=m_posTouches.w;
	m_posVolume.h=m_volume->h;
	m_posVolume.w=m_volume->w;
	m_posVolume.y=m_posEffet.h;
	m_posMenu.x=0;
	m_posMenu.y=m_posEffet.h;
}

void Lecteur::gestionEvent(Music & music)
{
	if(m_in.key[SDLK_ESCAPE] || m_in.quit)
	{
		m_continuer=false;
	}
	if(m_in.mouseButtons[SDL_BUTTON_LEFT]&& !appuyer)
	{
		if(m_event.button.x < m_posVolume.x-12)
		{
			if(pointComplet(45,m_posTouches.y+10,m_event.button.x,m_event.button.y,30,20))
			{
				m_touches=IMG_Load("images/images_lecteur/play_pause.png");
				music.setPause();
			}
			if(pointComplet(87,m_posTouches.y+10,m_event.button.x,m_event.button.y,25,20))
			{
				m_touches=IMG_Load("images/images_lecteur/stop.png");
				music.stopMusic();
			}
			if(pointComplet(167,m_posTouches.y+10,m_event.button.x,m_event.button.y,25,20))
			{
				m_touches=IMG_Load("images/images_lecteur/previous.png");
				music.jouerMusic(music.getMusic()-1);
			}
			if(pointComplet(287,m_posTouches.y+10,m_event.button.x,m_event.button.y,25,20))
			{
				m_touches=IMG_Load("images/images_lecteur/next.png");
				music.jouerMusic(music.getMusic()+1);
			}
			if(pointComplet(367,m_posTouches.y+10,m_event.button.x,m_event.button.y,25,20))
			{
				m_touches=IMG_Load("images/images_lecteur/esc.png");
				m_continuer=false;
			}
		}
		else
		{
			for(int i=0,y=0; i < 11; i++,y+=16)
			{
				if(pointComplet((m_posVolume.x-12)+y,m_posVolume.y+14,m_event.button.x,m_event.button.y,10,10))
				{
					gestionVolume(music,i);
				}
			}
		}
		appuyer=true;
	}
	else
		m_touches=IMG_Load("images/images_lecteur/unselected.png");
}

void Lecteur::blitter(SDL_Surface *ecran)
{
	SDL_FillRect(m_menu, NULL, SDL_MapRGB(ecran->format,216, 219, 224));
	SDL_BlitSurface(m_menu,NULL,ecran,&m_posMenu);
	SDL_BlitSurface(m_effet,NULL,ecran,&m_posEffet);
	SDL_BlitSurface(m_touches,NULL,ecran,&m_posTouches);
	SDL_BlitSurface(m_volume,NULL,ecran,&m_posVolume);
	SDL_Flip(ecran);
}

void Lecteur::setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

bool Lecteur::pointComplet(int x1, int y1,int x2,int y2,int w,int h)
{
	if(x2 < x1 || x2 > x1+w)
		return false;
	if(y2 < y1 || y2 > y1+h)
		return false;
	return true;
}

void Lecteur::gestionVolume(Music & music,int vol)
{
	switch(vol)
	{
	case 0:
		music.setVolume(0);
		m_volume=IMG_Load("images/images_lecteur/volume_00.png");
		break;
	case 1:
		music.setVolume(25);
		m_volume=IMG_Load("images/images_lecteur/volume_01.png");
		break;
	case 2:
		music.setVolume(50);
		m_volume=IMG_Load("images/images_lecteur/volume_02.png");
		break;
	case 3:
		music.setVolume(75);
		m_volume=IMG_Load("images/images_lecteur/volume_03.png");
		break;
	case 4:
		music.setVolume(100);
		m_volume=IMG_Load("images/images_lecteur/volume_04.png");
		break;
	case 5:
		music.setVolume(125);
		m_volume=IMG_Load("images/images_lecteur/volume_05.png");
		break;
	case 6:
		music.setVolume(150);
		m_volume=IMG_Load("images/images_lecteur/volume_06.png");
		break;
	case 7:
		music.setVolume(175);
		m_volume=IMG_Load("images/images_lecteur/volume_07.png");
		break;
	case 8:
		music.setVolume(200);
		m_volume=IMG_Load("images/images_lecteur/volume_08.png");
		break;
	case 9:
		music.setVolume(225);
		m_volume=IMG_Load("images/images_lecteur/volume_09.png");
		break;
	case 10:
		music.setVolume(250);
		m_volume=IMG_Load("images/images_lecteur/volume_10.png");
		break;
	}
}