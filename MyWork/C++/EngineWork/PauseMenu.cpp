#include "stdafx.h"
#include "PauseMenu.h"


PauseMenu::PauseMenu()
{
}

PauseMenu::PauseMenu(ResourceManager* res,OptionsScreen* options)
{
	m_Ui.CreateUIPrinter(res);
	UITEXT x;
	m_background = UIimage(res, m_background.m_image, L"..\\Resources\\Textures\\PauseBack.dds", XMFLOAT2(res->m_DirectView.TopLeftX + 250.0f, res->m_DirectView.TopLeftY + 100.0f), DirectX::Colors::White, x);
	m_Continue = Button(res, XMFLOAT2(m_background.m_location.x + 325.0f, m_background.m_location.y), L"Continue", 50.0f, 80.0f);
	m_Retry = Button(res, XMFLOAT2(m_background.m_location.x + 325.0f, m_background.m_location.y + 100.0f), L"Retry", 70.0f, 80.0f);
	m_Options = Button(res, XMFLOAT2(m_background.m_location.x + 325.0f, m_background.m_location.y + 200.0f), L"Options", 60.0f, 80.0f);
	m_Exit = Button(res, XMFLOAT2(m_background.m_location.x + 325.0f, m_background.m_location.y + 300.0f), L"Exit", 80.0f, 80.0f);
	active = false;
	m_currentTime = 0.0f;
	ResetLevel = false;
	ExittoMain = false;
	////////
	m_inGameoptions = options;
	/////////
	m_selected = 0;
}
PauseMenu::~PauseMenu()
{
	Shutdown();
}
void PauseMenu::Run(ResourceManager* res, float dt, AudioManager* media)
{
	Keyboard::State kb = res->m_keyboard->GetState();
	GamePad::State gamePad = res->m_gamepad->GetState(0);
	gbt.Update(res->m_gamepad->GetState(0));

	m_currentTime += dt;
	if ((gamePad.IsConnected() && gbt.start == GamePad::ButtonStateTracker::PRESSED) || (kb.Escape) && m_currentTime > 0.5f)
	{
		media->Pause(MUSIC);
		m_currentTime = 0.0f;
		active = true;
	}
	else
		gbt.start = GamePad::ButtonStateTracker::RELEASED;
	if (inOptions)
		m_inGameoptions->Run(res, media,GAMESTATE);
	if (active&&inOptions == false)
	{

		m_Ui.DrawUI(res, &m_background, 3.0f);
		m_Ui.DrawButton(res, &m_Continue.m_norm, 2.0f);
		m_Ui.DrawButton(res, &m_Retry.m_norm, 2.0f);
		m_Ui.DrawButton(res, &m_Options.m_norm, 2.0f);
		m_Ui.DrawButton(res, &m_Exit.m_norm, 2.0f);

		switch (m_selected)
		{
		case 0:
		{
			m_Ui.DrawButton(res, &m_Continue.m_highlight, 2.0f);
			break;
		}
		case 1:
		{
			m_Ui.DrawButton(res, &m_Retry.m_highlight, 2.0f);
			break;
		}
		case 2:
		{
			m_Ui.DrawButton(res, &m_Options.m_highlight, 2.0f);
			break;
		}
		case 3:
		{
			m_Ui.DrawButton(res, &m_Exit.m_highlight, 2.0f);
			break;
		}
		}


		if ((gamePad.IsConnected() && gbt.leftStickUp == GamePad::ButtonStateTracker::PRESSED) || kb.Up&&m_currentTime > 0.5f)
		{
			media->Play(SFX,CLICK1);
			m_currentTime = 0.0f;
			if (m_selected == 0)
				m_selected = 3;
			else
				m_selected--;
		}
		else
			gbt.leftStickUp = GamePad::ButtonStateTracker::RELEASED;

		if ((gamePad.IsConnected() && gbt.leftStickDown == GamePad::ButtonStateTracker::PRESSED) || kb.Down&&m_currentTime > 0.5f)
		{
			media->Play(SFX, CLICK1);
			m_currentTime = 0.0f;
			if (m_selected == 3)
				m_selected = 0;
			else
				m_selected++;
		}
		else
			gbt.leftStickDown = GamePad::ButtonStateTracker::RELEASED;

		if ((gamePad.IsConnected() && gbt.a == GamePad::ButtonStateTracker::PRESSED) || kb.Enter&&m_currentTime > 0.5f)
		{
			media->Play(SFX, CLICK2);
			m_currentTime = 0.0f;
			switch (m_selected)
			{
			case 0:
			{
				m_Ui.DrawButton(res, &m_Continue.m_enter, 2.0f);
				m_selected = 0;
				media->Resume(MUSIC);
				active = false;
				break;
			}
			case 1:
			{
				m_Ui.DrawButton(res, &m_Retry.m_enter, 2.0f);
				active = false;
				media->Resume(MUSIC);
				ResetLevel = true;
				break;
			}
			case 2:
			{
				m_Ui.DrawButton(res, &m_Options.m_enter, 2.0f);
				inOptions = true;

				break;
			}
			case 3:
			{
				m_Ui.DrawButton(res, &m_Exit.m_enter, 2.0f);
				media->Resume(MUSIC);
				active = false;
				ExittoMain = true;

				res->m_wait = true;
				break;
			}
			}
		}
		else
			gbt.a = GamePad::ButtonStateTracker::RELEASED;
		
		if ((gamePad.IsConnected() && gbt.b == GamePad::ButtonStateTracker::PRESSED) || kb.Back&&m_currentTime > 0.5f)
		{
			m_Ui.DrawButton(res, &m_Continue.m_enter, 2.0f);
			m_selected = 0;
			media->Resume(MUSIC);
			active = false;
		}
		else
			gbt.b = GamePad::ButtonStateTracker::RELEASED;
	}
	if (inOptions)
	{
		if ((gamePad.IsConnected() && gbt.b == GamePad::ButtonStateTracker::PRESSED) || kb.Back&&m_currentTime > 0.5f)
		{
			inOptions = false;

		}
		else
			gbt.b = GamePad::ButtonStateTracker::RELEASED;
	}
}
void PauseMenu::Shutdown()
{
	
	m_background.Shutdown();
	m_Continue.Shutdown();
	m_Retry.Shutdown();
	m_Options.Shutdown();
	m_Exit.Shutdown();
}