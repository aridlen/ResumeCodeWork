#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//      Date:  01/02/2017                //
//                                       //
///////////////////////////////////////////
#include "Audio.h"
///SONG INDEXS
enum SFXList {
	BREAK, CLICK1, CLICK2, DEAD, GRUNT1, GRUNT2, GRUNT3, GRUNT4, GRUNT5, PICKUP1, PICKUPMETAL, PUNCH1, PUNCH2, PUNCH3,
	PUNCH4, PUNCH5, PUNCH6, WEAPONHIT, WALK1, WIN1, WARP, EXPLODE, SPARKY, SFXTOTAL
};
class XsoundEffectsX
{
	unique_ptr<AudioEngine> m_soundEffectEngine;
	unique_ptr<SoundEffect> m_soundEffect[SFXTOTAL];
	unique_ptr<SoundEffectInstance> m_currentSFX;

	float m_Volume;
public:
	XsoundEffectsX();
	~XsoundEffectsX();

	void Initialize();
	void GenerateSFXList();
	void Shutdown();
	void Play(int sfx);

	void Pause();
	void Resume();
	void Stop();
	////Helpers///
	void SetMasterVolume(float volume) { m_Volume = volume; }
	float GetMasterVolume() { return m_Volume; }

	DirectX::SoundState PlayingState();
};

