#include "stdafx.h"
#include "MenuState.h"

#define BUTTONLOCX BACKBUFFER_WIDTH * 0.25f
#define BUTTONLOCY BACKBUFFER_HEIGHT * 0.16f

MenuState::MenuState()
{
	
}

MenuState::MenuState(ResourceManager* res)
{
#if !WINDOWED
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	float width = 0;
	width = (float)desktop.right;
	float hieght = 0;
	hieght = (float)desktop.bottom;
#endif

	//m_music.Initialize();
	m_menu.CreateUIPrinter(res);

	CreateButton(res, XMFLOAT2(BUTTONLOCX, BUTTONLOCY));//XMFLOAT2(res->m_DirectView.Width*0.5f, res->m_DirectView.Height*0.5f));
	back = true;
	m_currentSong = 0;
	m_currentState = -1;
	m_currentSelection = 0;
    m_optionsSplash.CreateOptions(res);
	
}


MenuState::~MenuState()
{
	Shutdown();
}
void MenuState::Start(ResourceManager* res)
{
	m_menu.CreateUIPrinter(res);
	CreateButton(res, XMFLOAT2(300, 100));//XMFLOAT2(res->m_DirectView.Width*0.5f, res->m_DirectView.Height*0.5f));
	m_currentState = 0;
	slowEnter = true;
	time = 0.0f;
}
void MenuState::Run(ResourceManager* res,HWND win, AudioManager* media)
{
	
	m_time.Signal();
	time +=(float) m_time.Delta();
	/*if (timer > 150)
	{
		timer = 0;
		buffer = false;
	}*/
	Keyboard::State m_keybrd = res->m_keyboard->GetState();
	Mouse::State m_mos = res->m_mouse->GetState();
	GamePad::State m_gamePd = res->m_gamepad->GetState(0);
	Keyboard::KeyboardStateTracker tracker;
	
	auto state = res->m_keyboard->GetState();
	tracker.Update(state);
	bst.Update(res->m_gamepad->GetState(0));

	POINT cur;
	GetCursorPos(&cur);
	ScreenToClient(win, &cur);
	/////BACK
	
	/*if (back)
	{
		
	media->PlaySong(SONG1);
	}*/
		//m_music.PlaySong(SONG1);
	back=false;
	
	////OptionsSplash
	
	////BACKGROUND
	m_menu.DrawUI(res, &background, 1.9f);
	/////////START
	
	
	m_menu.DrawUI(res, &m_start.m_norm, 1.0f);

	/////////////HIGHSCORES
	
	m_menu.DrawUI(res, &m_highscores.m_norm, 1.0f);
	
	//////////////OPTIONS
	
	m_menu.DrawUI(res, &m_options.m_norm, 1.0f);
	
	//////////////EXIT
	
	m_menu.DrawUI(res, &m_exit.m_norm, 1.0f);
	

	/////exit
	
	//if (kb.Escape)
		//PostQuitMessage(0);
	if ((m_gamePd.IsConnected() && bst.back == GamePad::ButtonStateTracker::PRESSED) || m_keybrd.Escape && m_keybrd.LeftAlt)
		PostQuitMessage(0);
	else
		bst.back = GamePad::ButtonStateTracker::RELEASED;

	/////DRAW BASIC IMAGE/////////
	switch (m_currentSelection)
	{
	case 0:
	{
		m_menu.DrawUI(res, &m_start.m_highlight, 1.0f);
		
		break;
	}
	case 1:
	{
		m_menu.DrawUI(res, &m_highscores.m_highlight, 1.0f);
		
		break;
	}
	case 2:
	{
		m_menu.DrawUI(res, &m_options.m_highlight, 1.0f);
		
		break;
	}
	case 3:
	{
		m_menu.DrawUI(res, &m_exit.m_highlight, 1.0f);
		
		break;
	}
	
	}
	
	/////ARROW INPUT
	if ((m_gamePd.IsConnected() && bst.leftStickUp == GamePad::ButtonStateTracker::PRESSED) || m_keybrd.IsKeyDown(Keyboard::Keys::Up) && time > 0.5f)
	{
		media->Play(SFX,CLICK2);
		m_currentSelection--;
		if (m_currentSelection < 0)
			m_currentSelection = 3;
		time = 0.0f;

	}
	else
		bst.leftStickUp = GamePad::ButtonStateTracker::RELEASED;
	
	if ((m_gamePd.IsConnected() && bst.leftStickDown == GamePad::ButtonStateTracker::PRESSED) || m_keybrd.IsKeyDown(Keyboard::Keys::Down) && time>0.5f)
	{
		media->Play(SFX, CLICK2);
			m_currentSelection++;
			if (m_currentSelection > 3)
				m_currentSelection = 0;
			time = 0.0f;
	}
	else
		bst.leftStickDown = GamePad::ButtonStateTracker::RELEASED;
	
	////ENTER SELECTION
	if ((m_gamePd.IsConnected() && bst.a == GamePad::ButtonStateTracker::PRESSED) || m_keybrd.Enter&&time > 0.5f&&!res->m_wait)
	{
		time = 0.0f;
		media->Play(SFX, CLICK1);
		slowEnter = false;
		switch (m_currentSelection)
		{
		case 0:
		{

			m_menu.DrawUI(res, &m_start.m_highlight, 1.0f);
			res->m_currentState = GAMESTATE;

			break;
		}
		case 1:
		{

			m_menu.DrawUI(res, &m_highscores.m_highlight, 1.0f);
			res->m_currentState = HIGHSCORES;
			break;
		}
		case 2:
		{

			m_menu.DrawUI(res, &m_options.m_highlight, 1.0f);
			res->m_currentState = OPTIONS;
			break;
		}
		case 3:
		{

			m_menu.DrawUI(res, &m_exit.m_highlight, 1.0f);
			res->m_currentState = EXIT;
			break;
		}
		}


		//media->Stop(SONG1);
	}
	else
		bst.a = GamePad::ButtonStateTracker::RELEASED;
	/////


}
void MenuState::Shutdown()
{
	
	m_menu.Shutdown();
	m_start.Shutdown();
	m_highscores.Shutdown();
	m_options.Shutdown();
	m_exit.Shutdown();
	background.Shutdown();
	//m_music.Shutdown();
	m_optionsSplash.Shutdown();
	/*x->Release();
	x1->Release();
	x2->Release();
	x3->Release();*/
}
void MenuState::CreateButton(ResourceManager* device, XMFLOAT2 pos)
{
	UITEXT x;
	background = UIimage(device, background.m_image, L"..\\Resources\\Menu\\GettingEvenLogo.dds", XMFLOAT2(device->m_DirectView.TopLeftX, device->m_DirectView.TopLeftY), DirectX::Colors::White, x);
	m_start.loc = pos;
	m_start.m_norm = UIimage(device, m_start.m_norm.m_image, L"..\\Resources\\Menu\\StartBlue.dds", pos, DirectX::Colors::White, x);
	m_start.m_highlight = UIimage(device, m_start.m_highlight.m_image, L"..\\Resources\\Menu\\StartGreen.dds", pos, DirectX::Colors::White, x);
	m_start.m_enter = UIimage(device, m_start.m_enter.m_image, L"..\\Resources\\Menu\\StartRed.dds", pos, DirectX::Colors::White, x);
	//////////////////////////
	pos.y += 100;
	m_highscores.loc = pos;
	m_highscores.m_norm = UIimage(device, m_highscores.m_norm.m_image, L"..\\Resources\\Menu\\HighscoresBlue.dds", pos, DirectX::Colors::White, x);
	m_highscores.m_highlight = UIimage(device, m_highscores.m_highlight.m_image, L"..\\Resources\\Menu\\HighscoresGreen.dds", pos, DirectX::Colors::White, x);
	m_highscores.m_enter = UIimage(device, m_highscores.m_enter.m_image, L"..\\Resources\\Menu\\HighscoresRed.dds", pos, DirectX::Colors::White, x);
	///////////////////////////
	pos.y += 100;
	m_options.loc = pos;
	m_options.m_norm = UIimage(device, m_options.m_norm.m_image, L"..\\Resources\\Menu\\OptionsBlue.dds", pos, DirectX::Colors::White, x);
	m_options.m_highlight = UIimage(device, m_options.m_highlight.m_image, L"..\\Resources\\Menu\\OptionsGreen.dds", pos, DirectX::Colors::White, x);
	m_options.m_enter = UIimage(device, m_options.m_enter.m_image, L"..\\Resources\\Menu\\OptionsRed.dds", pos, DirectX::Colors::White, x);
	//////////////////////////
	pos.y += 100;
	m_exit.loc = pos;
	m_exit.m_norm = UIimage(device, m_exit.m_norm.m_image, L"..\\Resources\\Menu\\ExitBlue.dds", pos, DirectX::Colors::White, x);
	m_exit.m_highlight = UIimage(device, m_exit.m_highlight.m_image, L"..\\Resources\\Menu\\ExitGreen.dds", pos, DirectX::Colors::White, x);
	m_exit.m_enter = UIimage(device, m_exit.m_enter.m_image, L"..\\Resources\\Menu\\ExitRed.dds", pos, DirectX::Colors::White, x);


}
