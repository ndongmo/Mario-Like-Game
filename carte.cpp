#include "carte.h"

Carte::Carte()
{
	m_xscroll=0;
	m_yscroll=0;
	m_pasX=5;
	m_pasY=5;
	m_mario = IMG_Load("images/marioD1.png");
	m_bandit1 = IMG_Load("images/bandit1.png");
	m_pieceBlit = IMG_Load("images/piece.png");
	m_etoile = IMG_Load("images/invisible.png");
	m_bonusOk = IMG_Load("images/bonusOk.png");
	m_porte=IMG_Load("images/porte.png");
    m_mur = IMG_Load("images/mur.png");
    m_nuage = IMG_Load("images/nuage.png");
	m_sol = IMG_Load("images/sol.png");
	m_brique = IMG_Load("images/brique.png");
	m_herbe = IMG_Load("images/herbe.png");
	m_bonus = IMG_Load("images/bonus.png");
	m_piquant = IMG_Load("images/piquant.png");
	m_suiveur = IMG_Load("images/suiveur.png");
	m_sauteur = IMG_Load("images/sauteur1.png");
	m_pondeur = IMG_Load("images/pondeur.png");
	m_fleur = IMG_Load("images/fleur.png");
	m_passeur = IMG_Load("images/passeur.png");
	m_gazon1 = IMG_Load("images/gazon1.png");
	m_gazon2 = IMG_Load("images/gazon2.png");
	m_gazon3 = IMG_Load("images/gazon3.png");
	m_gazon11 = IMG_Load("images/gazon11.png");
	m_gazon22 = IMG_Load("images/gazon22.png");
	m_gazon33 = IMG_Load("images/gazon33.png");
	m_terre = IMG_Load("images/terre.png");
	m_tortue = IMG_Load("images/tortueD.png");
	m_boss = IMG_Load("images/boss1.png");
	m_passeur1 = IMG_Load("images/passeur1.png");
	m_cassable = IMG_Load("images/briqueCassable.png");
	m_piquant1 = IMG_Load("images/piquant1.png");
	m_boss2 = IMG_Load("images/boss2.png");
	m_canon1 = IMG_Load("images/canon1.png");
	m_canon2 = IMG_Load("images/canon2.png");
	m_canard = IMG_Load("images/canard.png");
	m_dinau = IMG_Load("images/dinau.png");
}

void Carte::evoluer(Clavier &in,SDL_Rect &rectPerso)
{
	int cxperso,cyperso,xlimmin,xlimmax,ylimmin,ylimmax;
	cxperso = rectPerso.x + rectPerso.w/2;
	cyperso = rectPerso.y + rectPerso.h/2;
	xlimmin = m_xscroll + LIMIT_MIN_X;
	ylimmin = m_yscroll + LIMIT_MIN_Y;
	xlimmax = xlimmin + LIMIT_W;
	ylimmax = ylimmin + LIMIT_H;
	if (cxperso<xlimmin)
		m_xscroll -= (xlimmin-cxperso);
	if (cyperso<ylimmin)
		m_yscroll -= (ylimmin-cyperso);
	if (cxperso>xlimmax)
		m_xscroll += (cxperso-xlimmax);
	if (cyperso>ylimmax)
		m_yscroll += (cyperso-ylimmax);

	deplacer();
}

void Carte::deplacer()
{
	// limitation
	if (m_xscroll < 0)
		m_xscroll=0;
	if (m_yscroll < 0)
		m_yscroll=0;
	if (m_xscroll > (NB_BLOC_LARGEUR_TOTAL *TAILLE_BLOC)-((NB_BLOC_LARGEUR*TAILLE_BLOC)-1))
		m_xscroll = (NB_BLOC_LARGEUR_TOTAL *TAILLE_BLOC)-((NB_BLOC_LARGEUR*TAILLE_BLOC)-1);
	if (m_yscroll > (NB_BLOC_HAUTEUR_TOTAL*TAILLE_BLOC)-((NB_BLOC_HAUTEUR*TAILLE_BLOC)-1))
		m_yscroll = (NB_BLOC_HAUTEUR_TOTAL*TAILLE_BLOC)-((NB_BLOC_HAUTEUR*TAILLE_BLOC)-1);
}

void Carte::afficher(SDL_Surface *ecran,const vector<vector<int> >& niveau)
{
	int j,i;
	SDL_Rect position;
	int minX,maxX,minY,maxY;
	minX=m_xscroll/TAILLE_BLOC;
	minY=m_yscroll/TAILLE_BLOC;
	maxX=(m_xscroll + (NB_BLOC_LARGEUR*TAILLE_BLOC))/TAILLE_BLOC;
	maxY=(m_yscroll + (NB_BLOC_HAUTEUR*TAILLE_BLOC))/TAILLE_BLOC;

	for (i = minX ; i < maxX ; i++)
	{
		for (j = minY ; j < maxY ; j++)
		{
			position.x = i * TAILLE_BLOC - m_xscroll;
			position.y = j * TAILLE_BLOC - m_yscroll;

			switch(niveau[i][j])
			{
			case BONUS_OK:
				SDL_BlitSurface(m_bonusOk, NULL, ecran, &position);
				break;
			case ETOILE:
				SDL_BlitSurface(m_etoile, NULL, ecran, &position);
				break;
			case PIECE:
				SDL_BlitSurface(m_pieceBlit, NULL, ecran, &position);
				break;
			case MUR:
				SDL_BlitSurface(m_mur, NULL, ecran, &position);
				break;
			case PORTE:
				SDL_BlitSurface(m_porte, NULL, ecran, &position);
				break;
			case NUAGE:
				SDL_BlitSurface(m_nuage, NULL, ecran, &position);
				break;
			case SOL:
				SDL_BlitSurface(m_sol, NULL, ecran, &position);
				break;
			case BRIQUE:
				SDL_BlitSurface(m_brique, NULL, ecran, &position);
				break;
			case HERBE:
				SDL_BlitSurface(m_herbe, NULL, ecran, &position);
				break;
			case BONUS:
				SDL_BlitSurface(m_bonus, NULL, ecran, &position);
				break;
			case PONDEUR:
				SDL_BlitSurface(m_pondeur, NULL, ecran, &position);
				break;
			case FLEUR:
				SDL_BlitSurface(m_fleur, NULL, ecran, &position);
				break;
			case GAZON1:
				SDL_BlitSurface(m_gazon1, NULL, ecran, &position);
				break;
			case GAZON2:
				SDL_BlitSurface(m_gazon2, NULL, ecran, &position);
				break;
			case GAZON3:
				SDL_BlitSurface(m_gazon3, NULL, ecran, &position);
				break;
			case GAZON11:
				SDL_BlitSurface(m_gazon11, NULL, ecran, &position);
				break;
			case GAZON22:
				SDL_BlitSurface(m_gazon22, NULL, ecran, &position);
				break;
			case GAZON33:
				SDL_BlitSurface(m_gazon33, NULL, ecran, &position);
				break;
			case TERRE:
				SDL_BlitSurface(m_terre, NULL, ecran, &position);
				break;
			}
		}
	}
}

void Carte::afficherTous(SDL_Surface *ecran,const vector<vector<int> >& niveau)
{
	int j,i;
	SDL_Rect position;
	int minX,maxX,minY,maxY;
	minX=m_xscroll/TAILLE_BLOC;
	minY=m_yscroll/TAILLE_BLOC;
	maxX=(m_xscroll + (NB_BLOC_LARGEUR*TAILLE_BLOC))/TAILLE_BLOC;
	maxY=(m_yscroll + (NB_BLOC_HAUTEUR*TAILLE_BLOC))/TAILLE_BLOC;

	for (i = minX ; i < maxX ; i++)
	{
		for (j = minY ; j < maxY ; j++)
		{
			position.x = i * TAILLE_BLOC - m_xscroll;
			position.y = j * TAILLE_BLOC - m_yscroll;

			switch(niveau[i][j])
			{
			case BONUS_OK:
				SDL_BlitSurface(m_bonusOk, NULL, ecran, &position);
				break;
			case ETOILE:
				m_etoile = IMG_Load("images/invisible0.png");
				SDL_BlitSurface(m_etoile, NULL, ecran, &position);
				break;
			case PIECE:
				SDL_BlitSurface(m_pieceBlit, NULL, ecran, &position);
				break;
			case MUR:
				SDL_BlitSurface(m_mur, NULL, ecran, &position);
				break;
			case PORTE:
				SDL_BlitSurface(m_porte, NULL, ecran, &position);
				break;
			case NUAGE:
				SDL_BlitSurface(m_nuage, NULL, ecran, &position);
				break;
			case SOL:
				SDL_BlitSurface(m_sol, NULL, ecran, &position);
				break;
			case BRIQUE:
				SDL_BlitSurface(m_brique, NULL, ecran, &position);
				break;
			case HERBE:
				SDL_BlitSurface(m_herbe, NULL, ecran, &position);
				break;
			case BONUS:
				SDL_BlitSurface(m_bonus, NULL, ecran, &position);
				break;
			case PONDEUR:
				SDL_BlitSurface(m_pondeur, NULL, ecran, &position);
				break;
			case FLEUR:
				SDL_BlitSurface(m_fleur, NULL, ecran, &position);
				break;
			case MARIO:
				SDL_BlitSurface(m_mario, NULL, ecran, &position);
				break;
			case BANDIT_1:
				SDL_BlitSurface(m_bandit1, NULL, ecran, &position);
				break;
			case PIQUANT:
				SDL_BlitSurface(m_piquant, NULL, ecran, &position);
				break;
			case SUIVEUR:
				SDL_BlitSurface(m_suiveur, NULL, ecran, &position);
				break;
			case SAUTEUR:
				SDL_BlitSurface(m_sauteur, NULL, ecran, &position);
				break;
			case PASSEUR:
				SDL_BlitSurface(m_passeur, NULL, ecran, &position);
				break;
			case GAZON1:
				SDL_BlitSurface(m_gazon1, NULL, ecran, &position);
				break;
			case GAZON2:
				SDL_BlitSurface(m_gazon2, NULL, ecran, &position);
				break;
			case GAZON3:
				SDL_BlitSurface(m_gazon3, NULL, ecran, &position);
				break;
			case GAZON11:
				SDL_BlitSurface(m_gazon11, NULL, ecran, &position);
				break;
			case GAZON22:
				SDL_BlitSurface(m_gazon22, NULL, ecran, &position);
				break;
			case GAZON33:
				SDL_BlitSurface(m_gazon33, NULL, ecran, &position);
				break;
			case TERRE:
				SDL_BlitSurface(m_terre, NULL, ecran, &position);
				break;
			case TORTUE:
				SDL_BlitSurface(m_tortue, NULL, ecran, &position);
				break;
			case BOSS1:
				SDL_BlitSurface(m_boss, NULL, ecran, &position);
				break;
			case PASSEUR1:
				SDL_BlitSurface(m_passeur1, NULL, ecran, &position);
				break;
			case CASSABLE:
				SDL_BlitSurface(m_cassable, NULL, ecran, &position);
				break;
			case PIQUANT1:
				SDL_BlitSurface(m_piquant1, NULL, ecran, &position);
				break;
			case BOSS2:
				SDL_BlitSurface(m_boss2, NULL, ecran, &position);
				break;
			case CANON1:
				SDL_BlitSurface(m_canon1, NULL, ecran, &position);
				break;
			case CANON2:
				SDL_BlitSurface(m_canon2, NULL, ecran, &position);
				break;
			case CANARD:
				SDL_BlitSurface(m_canard, NULL, ecran, &position);
				break;
			case DINAU:
				SDL_BlitSurface(m_dinau, NULL, ecran, &position);
				break;
			}
		}
	}
}

bool Carte::rechercher(const vector<vector<int> >& niveau,int index)
{
	for (int i = 0 ; i < NB_BLOC_LARGEUR_TOTAL ; i++)
	{
		for (int j = 0 ; j < NB_BLOC_HAUTEUR_TOTAL ; j++)
		{
			if(niveau[i][j]==index)
				return true;
		}
	}
	return false;
}

int Carte::getXscroll()
{
	return m_xscroll;
}
int Carte::getYscroll()
{
	return m_yscroll;
}
void Carte::setXscroll(int xscroll)
{
	m_xscroll=xscroll;
}
void Carte::setYscroll(int yscroll)
{
	m_yscroll=yscroll;
}
void Carte::inXscroll()
{
	m_xscroll+=m_pasX;
}
void Carte::deXscroll()
{
	m_xscroll-=m_pasX;
}
void Carte::inYscroll()
{
	m_yscroll+=m_pasY;
}
void Carte::deYscroll()
{
	m_yscroll-=m_pasY;
}

Carte::~Carte()
{
	SDL_FreeSurface(m_mur);
    SDL_FreeSurface(m_nuage);
    SDL_FreeSurface(m_sol);
    SDL_FreeSurface(m_brique);
	SDL_FreeSurface(m_herbe);
	SDL_FreeSurface(m_bonus);
	SDL_FreeSurface(m_pieceBlit);
	SDL_FreeSurface(m_etoile);
	SDL_FreeSurface(m_bonusOk);
	SDL_FreeSurface(m_bandit1);
	SDL_FreeSurface(m_piquant);
	SDL_FreeSurface(m_suiveur);
	SDL_FreeSurface(m_mario);
	SDL_FreeSurface(m_sauteur);
	SDL_FreeSurface(m_pondeur);
	SDL_FreeSurface(m_fleur);
	SDL_FreeSurface(m_passeur);
	SDL_FreeSurface(m_gazon1);
	SDL_FreeSurface(m_gazon2);
	SDL_FreeSurface(m_gazon3);
	SDL_FreeSurface(m_gazon11);
	SDL_FreeSurface(m_gazon22);
	SDL_FreeSurface(m_gazon33);
	SDL_FreeSurface(m_terre);
	SDL_FreeSurface(m_tortue);
	SDL_FreeSurface(m_boss);
	SDL_FreeSurface(m_passeur1);
	SDL_FreeSurface(m_cassable);
	SDL_FreeSurface(m_piquant1);
	SDL_FreeSurface(m_boss2);
	SDL_FreeSurface(m_canon1);
	SDL_FreeSurface(m_canon2);
	SDL_FreeSurface(m_canard);
	SDL_FreeSurface(m_dinau);
}