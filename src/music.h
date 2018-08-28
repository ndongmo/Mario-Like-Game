#include <vector>
#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <SDL1/fmod.h>

using namespace std;

#include "constante.h"
#include "clavier.h"

#ifndef MUSIC
#define MUSIC

class Music
{
	public:
		Music();
		~Music();
		void charger();
		void jouerMusic(int index);
		void jouerSon(int index);
		void setVolume(int vol);
		void setPause();
		void setDSP(bool dsp);
		void stopMusic();
		int getVolume();
		int getMusic();
	private:
		vector<FSOUND_STREAM *>m_musics;
		vector<FSOUND_SAMPLE *>m_sons;
		int m_musicEnCour;
		int m_volume;
		bool stop;
};
#endif