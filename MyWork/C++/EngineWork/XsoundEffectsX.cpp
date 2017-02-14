#include "stdafx.h"
#include "XsoundEffectsX.h"


XsoundEffectsX::XsoundEffectsX()
{
	Initialize();
}


XsoundEffectsX::~XsoundEffectsX()
{
	Shutdown();
}

void XsoundEffectsX::Initialize()
{
	m_Volume = 1.2f;
	m_soundEffectEngine.reset(new AudioEngine(AudioEngine_Default));
	GenerateSFXList();
}

void XsoundEffectsX::GenerateSFXList()
{
	m_soundEffect[0].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\break1.wav"));
	m_soundEffect[1].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\click1.wav"));
	m_soundEffect[2].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\click2.wav"));
	m_soundEffect[3].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\dead1.wav"));
	m_soundEffect[4].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\grunt1.wav"));
	m_soundEffect[5].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\grunt2.wav"));
	m_soundEffect[6].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\grunt3.wav"));
	m_soundEffect[7].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\grunt4.wav"));
	m_soundEffect[8].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\grunt5.wav"));
	m_soundEffect[9].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\pickup1.wav"));
	m_soundEffect[10].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\pickupMetal.wav"));
	m_soundEffect[11].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\punch1.wav"));
	m_soundEffect[12].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\punch2.wav"));
	m_soundEffect[13].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\punch3.wav"));
	m_soundEffect[14].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\punch4.wav"));
	m_soundEffect[15].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\punch5.wav"));
	m_soundEffect[16].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\punch6.wav"));
	m_soundEffect[17].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\weaponHit.wav"));
	m_soundEffect[18].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\walk1.wav"));
	m_soundEffect[19].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\win1.wav"));
	m_soundEffect[20].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\warp.wav"));
	m_soundEffect[21].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\explode.wav"));
	m_soundEffect[22].reset(new SoundEffect(m_soundEffectEngine.get(),L"..\\Resources\\Sounds\\SoundAssets\\spark.wav"));
}

void XsoundEffectsX::Shutdown()
{
	m_soundEffectEngine.reset(nullptr);
	m_soundEffectEngine.release();
	for (size_t i = 0; i < SFXTOTAL; i++)
	{
		m_soundEffect[i].reset(nullptr);
		m_soundEffect[i].release();
	}
	m_currentSFX.reset(nullptr);
	m_currentSFX.release();
}

void XsoundEffectsX::Play(int sfx)
{
	//m_currentSFX.reset(nullptr);
	//m_currentSFX.release();
	m_currentSFX = m_soundEffect[sfx]->CreateInstance();
	m_currentSFX->SetVolume(m_Volume);
	m_currentSFX->Play();
}

void XsoundEffectsX::Pause()
{
	if (m_currentSFX != nullptr)
	{
		m_currentSFX->Pause();
	}
}

void XsoundEffectsX::Resume()
{
	if (m_currentSFX != nullptr)
	{
		m_currentSFX->Resume();
	}
}

void XsoundEffectsX::Stop()
{
	if (m_currentSFX != nullptr)
	{
		m_currentSFX->Stop();
	}
}

DirectX::SoundState XsoundEffectsX::PlayingState()
{
	return m_currentSFX->GetState();
}
