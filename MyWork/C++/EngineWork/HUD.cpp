#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
	
}
HUD::HUD(ResourceManager* res)
{
	
	UITEXT x;
	m_UI.CreateUIPrinter(res);
	m_score = UIimage(res, m_score.m_image, L"..\\Resources\\Textures\\ScoreUI.dds", XMFLOAT2(res->m_DirectView.TopLeftX +1000.0f, res->m_DirectView.TopLeftY+80.0f), DirectX::Colors::Yellow, x);
	m_playerScore = 0;
	m_scoreNum = UITEXT(L"0", m_score.m_location, DirectX::Colors::Yellow);
	m_scoreNum.m_location.x += 150.0f;
	///////////
	m_comboBack = UIimage(res, m_comboBack.m_image, L"..\\Resources\\Textures\\ComboUI.dds", XMFLOAT2(res->m_DirectView.TopLeftX + 1000.0f, res->m_DirectView.TopLeftY + 30.0f), DirectX::Colors::Yellow, x);
	m_comboCount = UITEXT(L"0", m_comboBack.m_location, DirectX::Colors::Yellow);
	m_comboCount.m_location.x += 120.0f;
	m_comboCount.m_location.y += 12.0f;
	combo = 0;
	///////////
	setCheck = 5;
	prevScore = 0;
	multiplier = 1;
	adder = 100;
}

HUD::~HUD()
{
	Shutdown();
}
void HUD::Run(ResourceManager* res)
{
	wstring number = to_wstring((int)m_playerScore);
	wstring comboString = to_wstring((int)combo);
	m_comboCount.m_characters = (wchar_t*)comboString.c_str();
	m_scoreNum.m_characters = (wchar_t*)number.c_str();
	m_UI.DrawUI(res, &m_comboBack, 1.0f);
	m_UI.DrawString(res, &m_comboCount);
	m_UI.DrawUI(res, &m_score, 1.0f);
	m_UI.DrawString(res, &m_scoreNum);
}
void HUD::SetScoreString(int combo)
{
	//prevScore = setCheck;

		/*if (combo == setCheck)
			setCheck *= 2;*/
	if (combo == 0)
	{
		prevScore = 0;
		setCheck = 5;
		multiplier = 1;
	}
		if (combo >= prevScore && combo <= setCheck)
		{
			m_playerScore += (adder*multiplier);
			return;
		}
		else
		{
			multiplier++;
			prevScore = setCheck;
			setCheck *= 2;
			SetScoreString(combo);
		}
		

}
void HUD::Shutdown()
{
	m_UI.Shutdown();
	m_score.Shutdown();
	m_comboBack.Shutdown();
}