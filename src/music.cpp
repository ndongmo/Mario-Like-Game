#include "music.h"

Music::Music()
{
	m_musics.resize(NB_MUSIC+4,NULL);
	m_sons.resize(NB_SON,NULL);
	m_musicEnCour=0;
	m_volume=50;
	stop=false;
	charger();
}

Music::~Music()
{
	for(int i=0;i<m_musics.size();i++)
	{
		FSOUND_Stream_Close(m_musics[i]);
	}
	for(int i=0;i<m_sons.size();i++)
	{
		FSOUND_Sample_Free(m_sons[i]);
	}
}
 
void Music::jouerMusic(int index)
{
	if(index >= NB_MUSIC || index < 0)
		index=0;
	FSOUND_Stream_Stop(m_musics[m_musicEnCour]);
	m_musicEnCour=index;
	FSOUND_Stream_SetLoopCount(m_musics[m_musicEnCour], -1);
    FSOUND_Stream_Play(FSOUND_FREE, m_musics[m_musicEnCour]);
	FSOUND_SetVolume(FSOUND_ALL,m_volume);
}

void Music::jouerSon(int index)
{
	FSOUND_PlaySound(FSOUND_FREE, m_sons[index]);
}

void Music::setVolume(int vol)
{
	if(vol < 255)
	{
		m_volume=vol;
		FSOUND_SetVolume(FSOUND_ALL,m_volume);
	}
}

void Music::setPause()
{
	if(!stop)
	{
		if (FSOUND_GetPaused(1))
			FSOUND_SetPaused(FSOUND_ALL, 0);
		else 
			FSOUND_SetPaused(FSOUND_ALL, 1);
	}
	else
	{
		stop=false;
		FSOUND_Stream_SetLoopCount(m_musics[m_musicEnCour], -1);
		FSOUND_Stream_Play(FSOUND_FREE, m_musics[m_musicEnCour]);
		FSOUND_SetVolume(FSOUND_ALL,m_volume);
	}
}

void Music::setDSP(bool dsp)
{
	if(dsp)
		FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), 1);
	else
	    FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), 0);
}

int Music::getVolume()
{
	return m_volume;
}

int Music::getMusic()
{
	return m_musicEnCour;
}

void Music::stopMusic()
{
	if(!stop)
	{
		stop=true;
		FSOUND_Stream_Stop(m_musics[m_musicEnCour]);
	}
}

void Music::charger()
{
	m_musics[0]=FSOUND_Stream_Open("musics/music_01.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[1]=FSOUND_Stream_Open("musics/music_02.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[2]=FSOUND_Stream_Open("musics/music_03.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[3]=FSOUND_Stream_Open("musics/music_04.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[4]=FSOUND_Stream_Open("musics/music_05.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[5]=FSOUND_Stream_Open("musics/music_06.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[6]=FSOUND_Stream_Open("musics/music_07.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[7]=FSOUND_Stream_Open("musics/music_08.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[8]=FSOUND_Stream_Open("musics/music_09.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[9]=FSOUND_Stream_Open("musics/music_10.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[10]=FSOUND_Stream_Open("musics/music_11.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[11]=FSOUND_Stream_Open("musics/music_12.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[12]=FSOUND_Stream_Open("musics/music_13.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[13]=FSOUND_Stream_Open("musics/music_14.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[14]=FSOUND_Stream_Open("musics/music_15.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[15]=FSOUND_Stream_Open("musics/music_16.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[16]=FSOUND_Stream_Open("musics/music_17.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[17]=FSOUND_Stream_Open("musics/music_18.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[18]=FSOUND_Stream_Open("musics/music_19.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[19]=FSOUND_Stream_Open("musics/music_20.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[20]=FSOUND_Stream_Open("musics/music_21.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[21]=FSOUND_Stream_Open("musics/music_22.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[22]=FSOUND_Stream_Open("musics/music_23.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[23]=FSOUND_Stream_Open("musics/music_24.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[24]=FSOUND_Stream_Open("musics/music_25.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[25]=FSOUND_Stream_Open("musics/music_26.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[26]=FSOUND_Stream_Open("musics/music_27.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[27]=FSOUND_Stream_Open("musics/music_28.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[28]=FSOUND_Stream_Open("musics/music_29.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[29]=FSOUND_Stream_Open("musics/music_30.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[30]=FSOUND_Stream_Open("musics/jouer.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[31]=FSOUND_Stream_Open("musics/mort.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[32]=FSOUND_Stream_Open("musics/fin_niveau.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	m_musics[33]=FSOUND_Stream_Open("musics/boss-victory.mp3", FSOUND_LOOP_NORMAL, 0, 0);
	
	m_sons[0]=FSOUND_Sample_Load(FSOUND_FREE, "musics/select.wav", 0, 0, 0);
	m_sons[1]=FSOUND_Sample_Load(FSOUND_FREE, "musics/smb_coin.wav", 0, 0, 0);
	m_sons[2]=FSOUND_Sample_Load(FSOUND_FREE, "musics/smb_touch.wav", 0, 0, 0);
	m_sons[3]=FSOUND_Sample_Load(FSOUND_FREE, "musics/save.wav", 0, 0, 0);
	m_sons[4]=FSOUND_Sample_Load(FSOUND_FREE, "musics/save_fail.wav", 0, 0, 0);
	m_sons[5]=FSOUND_Sample_Load(FSOUND_FREE, "musics/smb_jump.wav", 0, 0, 0);
	m_sons[6]=FSOUND_Sample_Load(FSOUND_FREE, "musics/coin_4.wav", 0, 0, 0);
	m_sons[7]=FSOUND_Sample_Load(FSOUND_FREE, "musics/smb_sc.wav", 0, 0, 0);
	m_sons[8]=FSOUND_Sample_Load(FSOUND_FREE, "musics/smb_new.wav", 0, 0, 0);
}

