#pragma once
#include "ParticleShaderResource.h"
#include "ParticleSystem.h"
class EffectsGenerator
{
	struct Effect
	{
		ParticleShaderResource m_resource;
		ParticleSystem m_system;
		ParticleProperties m_properties;
		XMFLOAT4X4 pos;
		Effect(ResourceManager* res,ParticleProperties prop,XMFLOAT4X4 position)
		{
			m_properties = prop;
			pos = position;
			m_resource.Initialize(res->m_SharedDevice, res->m_window);
			m_system.Initialize(res->m_SharedDevice, m_properties);
		}
		~Effect()
		{
			m_resource.Shutdown();
			m_system.Shutdown();
		}

	};
	vector<Effect*> m_effectList;
public:
	EffectsGenerator();
	~EffectsGenerator();
	void GenerateEffect(ResourceManager* res,  vector<Item*> items,Player* player,vector<Enemy*> enemy,AudioManager* media);
	void RunGenerator(ResourceManager* res, vector<Item*> items, Player* player, vector<Enemy*> enemy,float dt, AudioManager* media);
	void BillBoardEffects(ResourceManager* res, Effect* effect);
	void RemovefromList(Effect* effect);
	void Shutdown();


};

