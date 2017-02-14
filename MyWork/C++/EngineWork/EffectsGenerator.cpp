#include "stdafx.h"
#include "EffectsGenerator.h"


EffectsGenerator::EffectsGenerator()
{
	m_effectList.clear();

}


EffectsGenerator::~EffectsGenerator()
{
	for (size_t i = 0; i < m_effectList.size(); i++)
	{
		delete m_effectList[i];
	}
	m_effectList.clear();
}

void EffectsGenerator::GenerateEffect(ResourceManager * res, vector<Item*> items, Player * player, vector<Enemy*> enemy, AudioManager* media)
{

	for (size_t i = 0; i < items.size(); i++)
	{
		
		if (items[i]->GetMarkedForDeath())
		{
			items[i]->SetMarkedForDeath(false);
			if (items[i]->Tag() == "Desk")
			{
				if (media->PlayingState(SFX)==PLAYING)
				{
					media->Stop(SFX);
				}
				media->Play(SFX, WARP);
				ParticleProperties tempProp(0.5f, 3.0f, 0.5f, 3.0f, L"..\\Resources\\Textures\\Cloud.dds", EXPLOSIVE);
				Effect* temp = new Effect(res, tempProp, items[i]->getTransform().Translate);
				m_effectList.push_back(temp);

			}
			else if (items[i]->Tag() == "Comp_Monitor")
			{
				if (items[i]->isPlayerHeld() || items[i]->isEnemyHeld())
				{
					if (media->PlayingState(SFX) == PLAYING)
					{
						media->Stop(SFX);
					}
					media->Play(SFX, SPARKY);
					ParticleProperties tempProp(0.5f, 1.0f, 0.5f, 1.0f, L"..\\Resources\\Textures\\Spark.dds", SPARK);
					Effect* temp = new Effect(res, tempProp, items[i]->getTransform().Translate);
					m_effectList.push_back(temp);
				}
			}
		}

	}

}



void EffectsGenerator::RunGenerator(ResourceManager * res, vector<Item*> items, Player * player, vector<Enemy*> enemy, float dt, AudioManager* media)
{

	for (size_t i = 0; i < m_effectList.size(); i++)
	{
		
		if (m_effectList[i]->m_system.GetPlay() == false && !m_effectList[i]->m_system.GetParticleRunTime())
		{
			m_effectList[i]->m_system.TogglePlayEffect();
			
		}
		else if(m_effectList[i]->m_system.GetPlay() == false && m_effectList[i]->m_system.GetParticleRunTime())
		{

			RemovefromList(m_effectList[i]);
			continue;
		}
		m_effectList[i]->m_system.Frame(dt, res->m_SharedDeviceContext, res);
		m_effectList[i]->m_system.Render(res->m_SharedDeviceContext);
		BillBoardEffects(res, m_effectList[i]);
		//delete m_effectList[i];
	}



	//m_effectList.clear();
}

void EffectsGenerator::BillBoardEffects(ResourceManager * res, Effect* effect)
{
	XMFLOAT4 pos;
	pos.x = effect->pos._41;
	pos.y = effect->pos._42;
	pos.z = effect->pos._43;
	pos.w = 1.0f;
	XMFLOAT4 Ppos;
	Ppos.x = res->m_Camera.Getpostion().x;
	Ppos.y = 0.0f;
	Ppos.z = res->m_Camera.Getpostion().z;
	Ppos.w = 1.0f;
	XMVECTOR upVec = XMVectorZero();
	upVec.m128_f32[1] = 1.0f;
	upVec.m128_f32[3] = 1.0f;
	XMFLOAT4X4 RotateTemp;
	XMStoreFloat4x4(&RotateTemp, XMMatrixInverse(nullptr, XMMatrixLookAtRH(XMLoadFloat4(&pos), XMLoadFloat4(&Ppos), upVec)));

	effect->m_resource.Render(res, res->m_SharedDeviceContext, effect->m_system.GetIndexCount(), RotateTemp, res->m_Camera.GetViewMatrix(), res->m_Camera.GetProjectionMatrix(), effect->m_system.GetTexture(), &effect->m_system);

}

void EffectsGenerator::RemovefromList(Effect* effect)
{
	Effect* temp = effect;
	m_effectList.erase(remove(m_effectList.begin(), m_effectList.end(), temp), m_effectList.end());
	delete temp;
}

void EffectsGenerator::Shutdown()
{
}
