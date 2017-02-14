#include "stdafx.h"
#include "OptionsScreen.h"


OptionsScreen::OptionsScreen()
{
}

OptionsScreen::OptionsScreen(ResourceManager* res)
{
	CreateOptions(res);
}
OptionsScreen::~OptionsScreen()
{
}
void OptionsScreen::CreateOptions(ResourceManager* device)
{


	UITEXT x;
	scroll1 = 0;
	m_currentSelection = 0;
	optionsPrinter.CreateUIPrinter(device);
	options = UIimage(device, options.m_image, L"..\\Resources\\Menu\\OptionsSplash.dds", XMFLOAT2(device->m_DirectView.TopLeftX+200.0f, device->m_DirectView.TopLeftY), DirectX::Colors::White, x);
	sliderButtonSound = UIimage(device, sliderButtonSound.m_image, L"..\\Resources\\Menu\\SliderDotTrans.dds", XMFLOAT2(device->m_DirectView.TopLeftX + 765.0f, device->m_DirectView.TopLeftY+270), DirectX::Colors::White, x);
	sliderButtonBright = UIimage(device, sliderButtonBright.m_image, L"..\\Resources\\Menu\\SliderDotTrans.dds", XMFLOAT2(device->m_DirectView.TopLeftX +765.0f, device->m_DirectView.TopLeftY + 470), DirectX::Colors::White, x);
	m_yes = Button(device, XMFLOAT2(options.m_location.x + 200.0f, options.m_location.y + 570), L"Yes", 80.0f, 80.0f);
	m_no = Button(device, XMFLOAT2(options.m_location.x + 400.0f, options.m_location.y + 570), L"No", 80.0f, 80.0f);


	m_time = 0.0f;
	Yes_No = true;
}
int OptionsScreen::Run(ResourceManager* res,AudioManager* music, int transition)
{
	music->Stop(MUSIC);
	music->SetInMenu(true);
	m_timer.Signal();
	m_time += (float)m_timer.Delta();
	Keyboard::State kb = res->m_keyboard->GetState();
	GamePad::State m_gamePd = res->m_gamepad->GetState(0);
	bst.Update(res->m_gamepad->GetState(0));

		optionsPrinter.DrawUI(res, &options, 2.9f);
		optionsPrinter.DrawUI(res, &sliderButtonSound, 0.5f);
		
		optionsPrinter.DrawUI(res, &sliderButtonBright, 0.5f);
		optionsPrinter.DrawButton(res, &m_yes.m_norm, 2.0f);
		optionsPrinter.DrawButton(res, &m_no.m_norm, 2.0f);
//		
		if (kb.Back || (m_gamePd.IsConnected() && bst.b == GamePad::ButtonStateTracker::PRESSED))
		{
			music->SetInMenu(false);
			music->Play(MUSIC,music->GetCurrentSong());
			return res->m_currentState = transition;
		}
		else
			bst.b= GamePad::ButtonStateTracker::RELEASED;
		if ((kb.IsKeyDown(Keyboard::Keys::Up) && m_time>0.5f)||(m_gamePd.IsConnected()&&bst.leftStickUp ==GamePad::ButtonStateTracker::PRESSED))
		{
			music->Play(SFX,CLICK2);
			m_time = 0.0f;
			m_currentSelection--;
			if (m_currentSelection < 0)
				m_currentSelection = 2;
		}
		else
			bst.leftStickUp = GamePad::ButtonStateTracker::RELEASED;
		if ((kb.IsKeyDown(Keyboard::Keys::Down) && m_time>0.5f)|| (m_gamePd.IsConnected() && bst.leftStickDown == GamePad::ButtonStateTracker::PRESSED))
		{
			music->Play(SFX, CLICK2);
			m_time = 0.0f;
				m_currentSelection++;
				if (m_currentSelection >= NUMUIELEMENTS)
					m_currentSelection = 0;
				
		}
		else
			bst.leftStickDown = GamePad::ButtonStateTracker::RELEASED;
		switch (m_currentSelection)
		{
		case 0:
		{
			sliderButtonSound.m_color = DirectX::Colors::Green;
			sliderButtonBright.m_color = DirectX::Colors::White;
			scroll1 = 0;
			break;
		}
		case 1:
		{
			sliderButtonBright.m_color = DirectX::Colors::Green;
			sliderButtonSound.m_color = DirectX::Colors::White;
			scroll1 = 1;
			break;
		}
		case 2:
		{
			sliderButtonBright.m_color = DirectX::Colors::White;
			sliderButtonSound.m_color = DirectX::Colors::White;
			scroll1 = 2;
			if (Yes_No)
			{
				optionsPrinter.DrawButton(res, &m_yes.m_highlight, 2.0f);
				
			}
			else
			{
				optionsPrinter.DrawButton(res, &m_no.m_highlight, 2.0f);
				
			}
			//Yes_No = true;
			break;
		}
		case 3:
		{

			break;
		}
		case 4:
		{

		}
		}
		if (scroll1==0)
		{
			if (kb.Left || (m_gamePd.IsConnected() && bst.GetLastState().IsLeftThumbStickLeft()))
			{
				
				if (sliderButtonSound.m_location.x > 338.0f)
				{
					music->Play(SFX, CLICK2);
					sliderButtonSound.m_location.x -= 10.0f;
					music->SetMasterVolume(music->GetMasterVolume()-0.025f);
					if(music->GetMasterVolume()<=0.0f)
						music->SetMasterVolume(0.0f);
					music->UpdateVolumes();
					
				}
				
			}
		
			if (kb.Right|| (m_gamePd.IsConnected() && bst.GetLastState().IsLeftThumbStickRight()))
			{
				
				if (sliderButtonSound.m_location.x < 765.0f)
				{
					music->Play(SFX, CLICK2);
					sliderButtonSound.m_location.x += 10.0f;
					music->SetMasterVolume(music->GetMasterVolume() + 0.025f);
					if (music->GetMasterVolume()>=1.0f)
						music->SetMasterVolume(1.0f);
					music->UpdateVolumes();
				}
			
			}
			
		}
		else if (scroll1 == 1)
		{
			
			if (kb.Left || (m_gamePd.IsConnected() && bst.GetLastState().IsLeftThumbStickLeft()))
			{
				
				if (sliderButtonBright.m_location.x >= 338.0f)
				{
					music->Play(SFX, CLICK2);
					sliderButtonBright.m_location.x -= 10.0f;
					res->VRAMPixelShader.gammaRatio -= 0.022f;
					if (res->VRAMPixelShader.gammaRatio < 0.0f)
						res->VRAMPixelShader.gammaRatio = 0.0f;
				}
				
			}
			
			if (kb.Right || (m_gamePd.IsConnected() && bst.GetLastState().IsLeftThumbStickRight()))
			{
				
				if (sliderButtonBright.m_location.x < 765.0f)
				{
					music->Play(SFX, CLICK2);
					sliderButtonBright.m_location.x += 10.0f;
					res->VRAMPixelShader.gammaRatio += 0.022f;
					if (res->VRAMPixelShader.gammaRatio > 1.0f)
						res->VRAMPixelShader.gammaRatio = 1.0f;
				}
				
			}
			
		}
		else if (scroll1 == 2)
		{
			if ((kb.Enter&&m_time > 0.5f)|| (m_gamePd.IsConnected() && bst.a == GamePad::ButtonStateTracker::PRESSED))
			{
				if (Yes_No)
				{
					res->m_fullscreen = true;
				}
				else
					res->m_fullscreen = false;

			}
			else
				bst.a = GamePad::ButtonStateTracker::RELEASED;
			if ((kb.Left&&m_time>0.5f)|| (m_gamePd.IsConnected() && bst.leftStickLeft == GamePad::ButtonStateTracker::PRESSED))
			{

				m_time = 0.0f;
				music->Play(SFX, CLICK2);
				if (Yes_No)
				{
					optionsPrinter.DrawButton(res, &m_yes.m_highlight, 2.0f);
					Yes_No = !Yes_No;
				}
				else
				{
					optionsPrinter.DrawButton(res, &m_no.m_highlight, 2.0f);
					Yes_No = !Yes_No;
				}

			}
			else
				bst.leftStickLeft = GamePad::ButtonStateTracker::RELEASED;
			if ((kb.Right&&m_time>0.5f) ||(m_gamePd.IsConnected() && bst.leftStickRight == GamePad::ButtonStateTracker::PRESSED))
			{
				m_time = 0.0f;
				music->Play(SFX, CLICK2);
				if (Yes_No)
				{
					optionsPrinter.DrawButton(res, &m_yes.m_highlight, 2.0f);
					Yes_No = !Yes_No;
				}
				else
				{
					optionsPrinter.DrawButton(res, &m_no.m_highlight, 2.0f);
					Yes_No = !Yes_No;
				}

			}
			else
				bst.leftStickRight = GamePad::ButtonStateTracker::RELEASED;
		}
		return 0;
}
void OptionsScreen::Shutdown()
{
	optionsPrinter.Shutdown();
	options.Shutdown();
	m_yes.Shutdown();
	m_no.Shutdown();
	//m_apply.Shutdown();
	sliderButtonSound.Shutdown();
	sliderButtonBright.Shutdown();
	

}