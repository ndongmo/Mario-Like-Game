#include <SDL1/SDL.h>
#include <SDL1/SDL_image.h> 
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "constante.h"

using namespace std;

#ifndef FICHIER
#define FICHIER

class Fichier
{
	public:
		Fichier();
		vector<vector<int> > chargerNiveau();
		bool sauvegarderNiveau(const vector<vector<int> >& niveau);
		bool updateNiveau();
		void initialiser();
		bool supprimerNiveau();
		void creerFichier();
		void ajouter(const vector<string>& lignes);
		int nbreNiveaux();
		int getNiveau();
		int getTime();
		int getMusic();
		int getR();
		int getG();
		int getB();
		void setTime(bool b);
		void setMusic(bool b);
		void setR(bool b);
		void setG(bool b);
		void setB(bool b);
		void setNiveau(int niveau);
	private:
		int m_niveauActuel,m_time,m_music;
		vector<int> m_rgb;
};
#endif