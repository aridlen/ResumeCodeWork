#include "stdafx.h"
#include "Music.h"


Music::Music()
{
	Initialize();
	Play(SONG1);
}


Music::~Music()
{
	Shutdown();
}

void Music::Initialize()
{
	
	m_Volume = 1.2f;
	m_musicEngine.reset(new AudioEngine(AudioEngine_Default));
	GenerateSongList();

}

void Music::GenerateSongList()
{
	
	m_music[SONG1].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\song1.wav"));
	m_music[SONG2].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\song2.wav"));
	m_music[SONG3].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\song3.wav"));
	m_music[SONG4].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\song4.wav"));
	m_music[SONG5].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\song5.wav"));
	m_music[NWA].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\copyright1.wav"));
	m_music[TRICKY].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\copyright2.wav"));
	m_music[WIN2].reset(new SoundEffect(m_musicEngine.get(), L"..\\Resources\\Sounds\\SoundAssets\\win2.wav"));

}

void Music::Shutdown()
{
	m_musicEngine.reset(nullptr);
	m_musicEngine.release();
	for (size_t i = 0; i < MUSICTOTAL; i++)
	{
		m_music[i].reset(nullptr);
		m_music[i].release();
	}
	m_currentSong.reset(nullptr);
	m_currentSong.release();
}

void Music::Play(int song)
{

	m_currentSong.reset(nullptr);
	m_currentSong.release();
	m_currentSong = m_music[song]->CreateInstance();
	m_currentSong->SetVolume(m_Volume);
	m_currentSong->Play();
}

void Music::Pause()
{
	if (m_currentSong != nullptr)
	{
		m_currentSong->Pause();
	}
}

void Music::Resume()
{
	if (m_currentSong != nullptr)
	{
		m_currentSong->Resume();
	}
}

void Music::Stop()
{
	if (m_currentSong != nullptr)
	{
		m_currentSong->Stop();
	}
}

DirectX::SoundState Music::PlayingState()
{

	return m_currentSong->GetState();
}
