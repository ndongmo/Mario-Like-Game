#include "fichier.h"

Fichier::Fichier()
{
	m_music=0;
	m_niveauActuel=0;
	m_rgb.resize(3,255);
	m_time=1;
}

void Fichier::initialiser()
{
	m_music=0;
	m_niveauActuel=0;
	m_rgb.clear();
	m_rgb.resize(3,255);
	m_time=1;
}

int Fichier::nbreNiveaux()
{
	 FILE* fichier = NULL;
    char ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 14] = {0};
    int i = 0;

    fichier = fopen("niveaux/niveaux.lvl", "r");
    if (fichier != NULL)
	{
		while(fgets(ligneFichier, NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 13, fichier)!=NULL)
			i++;
		fclose(fichier);
		return i;
	}
	return 0;
}

bool Fichier::supprimerNiveau()
{
	if(m_niveauActuel)
	{
		ifstream file("niveaux/niveaux.lvl");
		vector<string>lignes;
		string ligne;
		int i=1;
		if(!file)
			return false;
		while(getline(file,ligne))
		{
			if(i!=m_niveauActuel)
			{
				lignes.push_back(ligne);
			}
			i++;
		}
		file.close();
		remove("niveaux/niveaux.lvl");
		creerFichier();
		ajouter(lignes);
		return true;
	}
	return false;
}

void Fichier::creerFichier()
{
	FILE* fichier = NULL;
	fichier = fopen("niveaux/niveaux.lvl", "a");
	fclose(fichier);
}

void Fichier::ajouter(const std::vector<string> &lignes)
{
	ofstream file("niveaux/niveaux.lvl",ios_base::app);
	for(int i=0;i<lignes.size();i++)
	{
		file << lignes[i]+"\n";
	}
	file.close();
}

bool Fichier::updateNiveau()
{
	if(m_niveauActuel >= nbreNiveaux())
		return false;
	else
	{
		m_niveauActuel++;
		return true;
	}
}

int Fichier::getNiveau()
{
	return m_niveauActuel;
}

int Fichier::getTime()
{
	return m_time;
}
int Fichier::getMusic()
{
	return m_music;
}
int Fichier::getR()
{
	return m_rgb[0];
}
int Fichier::getG()
{
	return m_rgb[1];
}
int Fichier::getB()
{
	return m_rgb[2];
}

void Fichier::setNiveau(int niveau)
{
	m_niveauActuel=niveau;
}
void Fichier::setMusic(bool b)
{
	if(b)
		m_music=(m_music < NB_MUSIC-1)?m_music+1:m_music;
	else
		m_music=(m_music > 0)?m_music-1:m_music;
}
void Fichier::setTime(bool b)
{
	if(b)
		m_time=(m_time < TEMPS_JEU_MAX-1)?m_time+1:m_time;
	else
		m_time=(m_time > 1)?m_time-1:m_time;
}
void Fichier::setR(bool b)
{
	if(b)
		m_rgb[0]=(m_rgb[0] < 255)?m_rgb[0]+5:m_rgb[0];
	else
		m_rgb[0]=(m_rgb[0] > 0)?m_rgb[0]-5:m_rgb[0];
}
void Fichier::setG(bool b)
{
	if(b)
		m_rgb[1]=(m_rgb[1] < 255)?m_rgb[1]+5:m_rgb[1];
	else
		m_rgb[1]=(m_rgb[1] > 0)?m_rgb[1]-5:m_rgb[1];
}
void Fichier::setB(bool b)
{
	if(b)
		m_rgb[2]=(m_rgb[2] < 255)?m_rgb[2]+5:m_rgb[2];
	else
		m_rgb[2]=(m_rgb[2] > 0)?m_rgb[2]-5:m_rgb[2];
}

vector<vector<int> > Fichier::chargerNiveau()
{
    FILE* fichier = NULL;
	vector<vector<int> > niveaux(NB_BLOC_LARGEUR_TOTAL, vector<int> (NB_BLOC_HAUTEUR_TOTAL,0));
    char ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 14] = {0};
	char r[10];
	char g[10];
	char b[10];
	char *conv=NULL;
    int i = 0, j = 0, t=0;
	
    fichier = fopen("niveaux/niveaux.lvl", "r");
    if (fichier == NULL)
        exit(-1);

	for(t=1;t <= m_niveauActuel;t++)
	{
		fgets(ligneFichier, NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 13, fichier);

		for (i = 0 ; i < NB_BLOC_LARGEUR_TOTAL ; i++)
		{
			for (j = 0 ; j < NB_BLOC_HAUTEUR_TOTAL ; j++)
			{
				switch (ligneFichier[(i * NB_BLOC_HAUTEUR_TOTAL) + j])
				{
					case '0':
						niveaux[i][j] = 0;
						break;
					case '1':
						niveaux[i][j] = 1;
						break;
					case '2':
						niveaux[i][j] = 2;
						break;
					case '3':
						niveaux[i][j] = 3;
						break;
					case '4':
						niveaux[i][j] = 4;
						break;
					case '5':
						niveaux[i][j] = 5;
						break;
					case '6':
						niveaux[i][j] = 6;
						break;
					case '7':
						niveaux[i][j] = 7;
						break;
					case '8':
						niveaux[i][j] = 8;
						break;
					case '9':
						niveaux[i][j] = 9;
						break;
					case 'a':
						niveaux[i][j] = 10;
						break;
					case 'b':
						niveaux[i][j] = 11;
						break;
					case 'c':
						niveaux[i][j] = 12;
						break;
					case 'd':
						niveaux[i][j] = 13;
						break;
					case 'e':
						niveaux[i][j] = 14;
						break;
					case 'f':
						niveaux[i][j] = 15;
						break;
					case 'g':
						niveaux[i][j] = 16;
						break;
					case 'h':
						niveaux[i][j] = 17;
						break;
					case 'i':
						niveaux[i][j] = 18;
						break;
					case 'j':
						niveaux[i][j] = 19;
						break;
					case 'k':
						niveaux[i][j] = 20;
						break;
					case 'l':
						niveaux[i][j] = 21;
						break;
					case 'n':
						niveaux[i][j] = 22;
						break;
					case 'm':
						niveaux[i][j] = 23;
						break;
					case 'o':
						niveaux[i][j] = 24;
						break;
					case 'p':
						niveaux[i][j] = 25;
						break;
					case 'q':
						niveaux[i][j] = 26;
						break;
					case 'r':
						niveaux[i][j] = 27;
						break;
					case 's':
						niveaux[i][j] = 28;
						break;
					case 't':
						niveaux[i][j] = 29;
						break;
					case 'u':
						niveaux[i][j] = 30;
						break;
					case 'v':
						niveaux[i][j] = 31;
						break;
					case 'w':
						niveaux[i][j] = 32;
						break;
					case 'y':
						niveaux[i][j] = 33;
						break;
					case 'z':
						niveaux[i][j] = 34;
						break;
					case '$':
						niveaux[i][j] = 35;
						break;
					case '#':
						niveaux[i][j] = 36;
						break;
					case ':':
						niveaux[i][j] = 37;
						break;
					case '<':
						niveaux[i][j] = 38;
						break;
					case '>':
						niveaux[i][j] = 39;
						break;
				}
			}
		}
		m_time=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL]-'0';
		switch(ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 1])
		{
			case 'a':
				m_music=10;
				break;
			case 'b':
				m_music=11;
				break;
			case 'c':
				m_music=12;
				break;
			case 'd':
				m_music=13;
				break;
			case 'e':
				m_music=14;
				break;
			case 'f':
				m_music=15;
				break;
			case 'g':
				m_music=16;
				break;
			case 'h':
				m_music=17;
				break;
			case 'i':
				m_music=18;
				break;
			case 'j':
				m_music=19;
				break;
			case 'k':
				m_music=20;
				break;
			case 'l':
				m_music=21;
				break;
			case 'm':
				m_music=22;
				break;
			case 'n':
				m_music=23;
				break;
			case 'o':
				m_music=24;
				break;
			case 'p':
				m_music=25;
				break;
			case 'q':
				m_music=26;
				break;
			case 'r':
				m_music=27;
				break;
			case 's':
				m_music=28;
				break;
			case 't':
				m_music=29;
				break;
			case 'u':
				m_music=30;
				break;
			default:
				m_music=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 1]-'0';
		}

		r[0]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 2];
		r[1]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 3];
		r[2]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 4];
		g[0]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 5];
		g[1]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 6];
		g[2]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 7];
		b[0]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 8];
		b[1]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 9];
		b[2]=ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 10];

		m_rgb[0]=(int)strtol(r,&conv,10);
		m_rgb[1]=(int)strtol(g,&conv,10);
		m_rgb[2]=(int)strtol(b,&conv,10);
	}

    fclose(fichier);
    return niveaux;
}

bool Fichier::sauvegarderNiveau(const std::vector<vector<int> > &niveau)
{
	if(m_niveauActuel)
	{
		FILE* fichier = NULL;
		char ligneFichier[NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 14] = {0};
		int i = 0, j = 0, t = 0;

		fichier = fopen("niveaux/niveaux.lvl", "r+");
		if (fichier == NULL)
			return false;

		fseek(fichier,(NB_BLOC_LARGEUR_TOTAL * NB_BLOC_HAUTEUR_TOTAL + 13)*(m_niveauActuel-1),0);
		for (i = 0 ; i < NB_BLOC_LARGEUR_TOTAL ; i++)
		{
			for (j = 0 ; j < NB_BLOC_HAUTEUR_TOTAL ; j++)
			{
				if( niveau[i][j] < 10)
					fprintf(fichier, "%d", niveau[i][j]);
				else if( niveau[i][j]==10)
					fprintf(fichier, "a");
				else if( niveau[i][j]==11)
					fprintf(fichier, "b");
				else if( niveau[i][j]==12)
					fprintf(fichier, "c");
				else if( niveau[i][j]==13)
					fprintf(fichier, "d");
				else if( niveau[i][j]==14)
					fprintf(fichier, "e");
				else if( niveau[i][j]==15)
					fprintf(fichier, "f");
				else if( niveau[i][j]==16)
					fprintf(fichier, "g");
				else if( niveau[i][j]==17)
					fprintf(fichier, "h");
				else if( niveau[i][j]==18)
					fprintf(fichier, "i");
				else if( niveau[i][j]==19)
					fprintf(fichier, "j");
				else if( niveau[i][j]==20)
					fprintf(fichier, "k");
				else if( niveau[i][j]==21)
					fprintf(fichier, "l");
				else if( niveau[i][j]==22)
					fprintf(fichier, "n");
				else if( niveau[i][j]==23)
					fprintf(fichier, "m");
				else if( niveau[i][j]==24)
					fprintf(fichier, "o");
				else if( niveau[i][j]==25)
					fprintf(fichier, "p");
				else if( niveau[i][j]==26)
					fprintf(fichier, "q");
				else if( niveau[i][j]==27)
					fprintf(fichier, "r");
				else if( niveau[i][j]==28)
					fprintf(fichier, "s");
				else if( niveau[i][j]==29)
					fprintf(fichier, "t");
				else if( niveau[i][j]==30)
					fprintf(fichier, "u");
				else if( niveau[i][j]==31)
					fprintf(fichier, "v");
				else if( niveau[i][j]==32)
					fprintf(fichier, "w");
				else if( niveau[i][j]==33)
					fprintf(fichier, "y");
				else if( niveau[i][j]==34)
					fprintf(fichier, "z");
				else if( niveau[i][j]==35)
					fprintf(fichier, "$");
				else if( niveau[i][j]==36)
					fprintf(fichier, "#");
				else if( niveau[i][j]==37)
					fprintf(fichier, ":");
				else if( niveau[i][j]==38)
					fprintf(fichier, "<");
				else if( niveau[i][j]==39)
					fprintf(fichier, ">");
			}
		}
				
				fprintf(fichier,"%d",m_time);
				if(m_music > 9)
				{
					if(m_music==10)
						fprintf(fichier, "a");
					else if(m_music==11)
						fprintf(fichier, "b");
					else if(m_music==12)
						fprintf(fichier, "c");
					else if(m_music==13)
						fprintf(fichier, "d");
					else if(m_music==14)
						fprintf(fichier, "e");
					else if(m_music==15)
						fprintf(fichier, "f");
					else if(m_music==16)
						fprintf(fichier, "g");
					else if(m_music==17)
						fprintf(fichier, "h");
					else if(m_music==18)
						fprintf(fichier, "i");
					else if(m_music==19)
						fprintf(fichier, "j");
					else if(m_music==20)
						fprintf(fichier, "k");
					else if(m_music==21)
						fprintf(fichier, "l");
					else if(m_music==22)
						fprintf(fichier, "m");
					else if(m_music==23)
						fprintf(fichier, "n");
					else if(m_music==24)
						fprintf(fichier, "o");
					else if(m_music==25)
						fprintf(fichier, "p");
					else if(m_music==26)
						fprintf(fichier, "q");
					else if(m_music==27)
						fprintf(fichier, "r");
					else if(m_music==28)
						fprintf(fichier, "s");
					else if(m_music==29)
						fprintf(fichier, "t");
					else if(m_music==30)
						fprintf(fichier, "u");
				}
				else
					fprintf(fichier,"%d",m_music);

				for(i=0;i<3;i++)
				{
					if(m_rgb[i] > 99)
						fprintf(fichier,"%d",m_rgb[i]);
					else if(m_rgb[i] > 9)
						fprintf(fichier,"0%d",m_rgb[i]);
					else 
						fprintf(fichier,"00%d",m_rgb[i]);
				}
				fputs("\n",fichier);

		fclose(fichier);
	}
	else
	{
		FILE* fichier = NULL;
		int i = 0, j = 0;

		fichier = fopen("niveaux/niveaux.lvl", "a");
		if (fichier == NULL)
			return false;

		for (i = 0 ; i < NB_BLOC_LARGEUR_TOTAL ; i++)
		{
			for (j = 0 ; j < NB_BLOC_HAUTEUR_TOTAL ; j++)
			{
				
				if( niveau[i][j] < 10)
					fprintf(fichier, "%d", niveau[i][j]);
				else if( niveau[i][j]==10)
					fprintf(fichier, "a");
				else if( niveau[i][j]==11)
					fprintf(fichier, "b");
				else if( niveau[i][j]==12)
					fprintf(fichier, "c");
				else if( niveau[i][j]==13)
					fprintf(fichier, "d");
				else if( niveau[i][j]==14)
					fprintf(fichier, "e");
				else if( niveau[i][j]==15)
					fprintf(fichier, "f");
				else if( niveau[i][j]==16)
					fprintf(fichier, "g");
				else if( niveau[i][j]==17)
					fprintf(fichier, "h");
				else if( niveau[i][j]==18)
					fprintf(fichier, "i");
				else if( niveau[i][j]==19)
					fprintf(fichier, "j");
				else if( niveau[i][j]==20)
					fprintf(fichier, "k");
				else if( niveau[i][j]==21)
					fprintf(fichier, "l");
				else if( niveau[i][j]==22)
					fprintf(fichier, "n");
				else if( niveau[i][j]==23)
					fprintf(fichier, "m");
				else if( niveau[i][j]==24)
					fprintf(fichier, "o");
				else if( niveau[i][j]==25)
					fprintf(fichier, "p");
				else if( niveau[i][j]==26)
					fprintf(fichier, "q");
				else if( niveau[i][j]==27)
					fprintf(fichier, "r");
				else if( niveau[i][j]==28)
					fprintf(fichier, "s");
				else if( niveau[i][j]==29)
					fprintf(fichier, "t");
				else if( niveau[i][j]==30)
					fprintf(fichier, "u");
				else if( niveau[i][j]==31)
					fprintf(fichier, "v");
				else if( niveau[i][j]==32)
					fprintf(fichier, "w");
				else if( niveau[i][j]==33)
					fprintf(fichier, "y");
				else if( niveau[i][j]==34)
					fprintf(fichier, "z");
				else if( niveau[i][j]==35)
					fprintf(fichier, "$");
				else if( niveau[i][j]==36)
					fprintf(fichier, "#");
				else if( niveau[i][j]==37)
					fprintf(fichier, ":");
				else if( niveau[i][j]==38)
					fprintf(fichier, "<");
				else if( niveau[i][j]==39)
					fprintf(fichier, ">");
			}
		}
		
		fprintf(fichier,"%d",m_time);
				if(m_music > 9)
				{
					if(m_music==10)
						fprintf(fichier, "a");
					else if(m_music==11)
						fprintf(fichier, "b");
					else if(m_music==12)
						fprintf(fichier, "c");
					else if(m_music==13)
						fprintf(fichier, "d");
					else if(m_music==14)
						fprintf(fichier, "e");
					else if(m_music==15)
						fprintf(fichier, "f");
					else if(m_music==16)
						fprintf(fichier, "g");
					else if(m_music==17)
						fprintf(fichier, "h");
					else if(m_music==18)
						fprintf(fichier, "i");
					else if(m_music==19)
						fprintf(fichier, "j");
					else if(m_music==20)
						fprintf(fichier, "k");
					else if(m_music==21)
						fprintf(fichier, "l");
					else if(m_music==22)
						fprintf(fichier, "m");
					else if(m_music==23)
						fprintf(fichier, "n");
					else if(m_music==24)
						fprintf(fichier, "o");
					else if(m_music==25)
						fprintf(fichier, "p");
					else if(m_music==26)
						fprintf(fichier, "q");
					else if(m_music==27)
						fprintf(fichier, "r");
					else if(m_music==28)
						fprintf(fichier, "s");
					else if(m_music==29)
						fprintf(fichier, "t");
					else if(m_music==30)
						fprintf(fichier, "u");
				}
				else
					fprintf(fichier,"%d",m_music);
		for(i=0;i<3;i++)
		{
			if(m_rgb[i] > 99)
				fprintf(fichier,"%d",m_rgb[i]);
			else if(m_rgb[i] > 9)
				fprintf(fichier,"0%d",m_rgb[i]);
			else 
				fprintf(fichier,"00%d",m_rgb[i]);
		}

		fputs("\n",fichier);

		fclose(fichier);
	}
    return true;
}

