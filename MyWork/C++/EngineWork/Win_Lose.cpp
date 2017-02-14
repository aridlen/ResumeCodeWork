#include "stdafx.h"
#include "Win_Lose.h"


Win_Lose::Win_Lose()
{

}
Win_Lose::Win_Lose(ResourceManager* res)
{
	m_UI.CreateUIPrinter(res);
	/////////Win///////////
	UITEXT k;
	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\Menu\\StageComplete.dds", NULL, &m_winUI.m_image);
	m_winUI.m_color = DirectX::Colors::Green;
	m_winUI.m_location = XMFLOAT2(res->m_DirectView.Width*0.25f, res->m_DirectView.Height*0.25f);
	m_winUI.m_text = k;
	////////Lose///////////
	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\Menu\\DeadScreen.dds", NULL, &m_loseUI.m_image);
	m_loseUI.m_color = DirectX::Colors::Red;
	m_loseUI.m_location = XMFLOAT2(res->m_DirectView.Width*0.25f + 100.0f, res->m_DirectView.Height*0.25f);
	m_loseUI.m_text = k;
	m_lose = false;
	m_win = false;
	dt = 0;
}

Win_Lose::~Win_Lose()
{
	Shutdown();
}
void Win_Lose::Shutdown()
{
	m_UI.Shutdown();
	m_winUI.Shutdown();
	m_loseUI.Shutdown();
	m_lose = false;
	m_win = false;
	dt = 0.0f;

}
void Win_Lose::Update(ResourceManager* res,Player* player, LevelManager* lvl,float time, AudioManager* media)
{
	
	if (player->GetHealth() <= 0.0f)
	{
		m_lose = true;
		media->Play(DIALOG,WHATTHEHELL);
		
	}
	if (lvl->GetNPCs().size() == 0)
	{
		m_win = true;
		media->Play(SFX,WIN1);
		lvl->GetLevel(lvl->GetCurrentLevel())->GetElevatorLight()->SetTexture(res->GreenTexture);
		
	}
	if (m_win)
	{
		dt += time;
		if (dt < 5.0f)
		{
			m_UI.DrawUI(res, &m_winUI, 2.0f);
		}
	
	}
	if (m_lose)
	{
		dt += time;
		m_UI.DrawUI(res, &m_loseUI, 2.0f);
		if (dt > 5.0f)
		{
			res->m_currentState = RESETGAME;
			dt = 0.0f;
		}

	}
}
void Win_Lose::ResetConditions()
{
	m_lose = false;
	m_win = false;
}