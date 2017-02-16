#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//      Date:  01/02/2017                //
//                                       //
///////////////////////////////////////////
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include"DDSTextureLoader.h"


struct UITEXT
{
	 wchar_t* m_characters;
	XMFLOAT2 m_location;
	 XMVECTORF32 m_color;
	 UITEXT()
	 {
		 m_characters = L"BLANK";
		 m_location = XMFLOAT2(0, 0);
		 m_color = XMVECTORF32();
	 }
	UITEXT(wchar_t* words,XMFLOAT2 pos,XMVECTORF32 color)
	{
		m_characters = words;
		m_location = pos;
		m_color = color;
	}
	
};

struct UIimage
{
	
	ID3D11ShaderResourceView* m_image;
	XMFLOAT2 m_location;
	XMVECTORF32 m_color;
	UITEXT m_text;
	UIimage()
	{
		m_image = NULL;
		m_location = XMFLOAT2(0, 0);
		m_color = XMVECTORF32();

	}

	UIimage(ResourceManager* device, ID3D11ShaderResourceView* texture,wchar_t* ddsFile, XMFLOAT2 pos,XMVECTORF32 color,UITEXT text)
	{
		m_image = texture;
		m_location = pos;
		m_color = color;
		m_text.m_characters = text.m_characters;
		m_text.m_color = text.m_color;
		m_text.m_location = text.m_location;
		CreateDDSTextureFromFile(device->m_SharedDevice, ddsFile, NULL, &m_image);

	}

	void Shutdown()
	{
		if (m_image)
		{
			m_image->Release();
			m_image = nullptr;

		}
	}
};
struct Button
{
	UIimage m_norm, m_highlight, m_enter;
	XMFLOAT2 loc;
	Button()
	{

	}
	Button(ResourceManager* res,XMFLOAT2 pos,wchar_t* words,float textPosX,float textPosY)
	{
		UITEXT x;
		x.m_characters = words;
		x.m_color = DirectX::Colors::White;
		x.m_location = XMFLOAT2(pos.x+ textPosX,pos.y+ textPosY);
		m_norm = UIimage(res, m_norm.m_image, L"..\\Resources\\HealthBar\\HealthSub2.dds", pos, DirectX::Colors::Blue, x);
		m_highlight = UIimage(res, m_highlight.m_image, L"..\\Resources\\HealthBar\\HealthSub2.dds", pos, DirectX::Colors::Green, x);
		m_enter = UIimage(res, m_enter.m_image, L"..\\Resources\\HealthBar\\HealthSub2.dds", pos, DirectX::Colors::Red, x);


	}
	void Shutdown()
	{
		m_norm.Shutdown();
		m_highlight.Shutdown();
		m_enter.Shutdown();
		
	}
};
class UIPrinter
{
	unique_ptr<SpriteBatch>m_spriteBatch;
	unique_ptr<SpriteFont> m_textFont;
	
	UIimage m_barContainer;
	UIimage m_Health[4];
	int m_count;
	bool m_flash;
public:
	void CreateUIPrinter(ResourceManager* resources);
	~UIPrinter();
	void DrawUI(ResourceManager* res, UIimage* ui, float scale);
	void DrawButton(ResourceManager* res, UIimage* ui, float scale);
	void DrawString(ResourceManager* res, UITEXT* text);
	void CreateHealthBar(ResourceManager* res);
	void DrawHealthBar(ResourceManager* res, float health);
	void Shutdown();
	void ResetHealthBar();
	//ACCESSORS

	//Mutators
};

