#include <stdlib.h>
#include <stdio.h>
#include <SDL1/SDL.h>
#include <SDL1/SDL_getenv.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/SDL_ttf.h>
#include <SDL1/fmod.h>

#include "accueil.h"
#include "music.h"

int main(int argc, char *argv[])
{
	SDL_Surface *ecran=NULL;
	SDL_Joystick *joystick;
	
	FSOUND_Init(44100, 32, 0);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
	TTF_Init();
	putenv("SDL_VIDEO_WINDOW_POS=center");
	SDL_WM_SetIcon(IMG_Load("images/mario_ico.png"),NULL);
	ecran=SDL_SetVideoMode(TAILLE_ECRAN_W,TAILLE_ECRAN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Mario Bros by NDONGMO S F M",NULL);
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	Accueil accueil(joystick);
	Music music;

	music.jouerMusic(0);
	accueil.afficher(ecran,music);

	music.~Music();
	TTF_Quit();
	FSOUND_Close();
	SDL_JoystickClose(joystick);
	SDL_Quit();
    return EXIT_SUCCESS;
}