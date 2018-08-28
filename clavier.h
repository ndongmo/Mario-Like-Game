#include <SDL1/SDL.h>

#ifndef CLAVIER
#define CLAVIER

class Clavier
{
	public:
		Clavier()
		{
			 mouseG=false;
			 mouseD=false;
			 mouseB=false;
			 mouseH=false;
		};

		char key[SDLK_LAST];
		bool mouseG,mouseD,mouseH,mouseB;
		char mouseButtons[8];
        char quit;
		int mousex,mousey;
		char joystickButtons[10];
};
#endif