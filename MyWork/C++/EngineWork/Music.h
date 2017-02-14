#pragma once
#include "Audio.h"
enum SongList { SONG1, SONG2, SONG3, SONG4, SONG5, NWA, TRICKY, WIN2, MUSICTOTAL };
class Music
{
	unique_ptr<AudioEngine> m_musicEngine;
	unique_ptr<SoundEffect> m_music[MUSICTOTAL];
	unique_ptr<SoundEffectInstance> m_currentSong;
	
	float m_Volume;
	bool active;
public:
	Music();
	~Music();
	void Initialize();
	void GenerateSongList();
	void Shutdown();
	void Play(int song);
	
	void Pause();
	void Resume();
	void Stop();
	////Helpers///
	void SetMasterVolume(float volume) { m_Volume = volume; }
	float GetMasterVolume() { return m_Volume; }

	DirectX::SoundState PlayingState();
};

