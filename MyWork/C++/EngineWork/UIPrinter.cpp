#include "stdafx.h"
#include "UIPrinter.h"


void UIPrinter::CreateUIPrinter(ResourceManager* resources)
{
	m_spriteBatch.reset(new SpriteBatch(resources->m_SharedDeviceContext));
	m_textFont.reset(new SpriteFont(resources->m_SharedDevice, L"..\\Resources\\Arial.spritefont"));
	m_flash = false;
	m_count = 3;
	
}


UIPrinter::~UIPrinter()
{
}

void UIPrinter::DrawUI(ResourceManager* res, UIimage* ui,float scale)
{

	m_spriteBatch->Begin();
	m_spriteBatch->SetViewport(res->m_DirectView);
	//ui->m_color=XMVECTORF32();
	XMVECTOR temp = ui->m_color;
	temp.m128_f32[0] *= res->VRAMPixelShader.gammaRatio;
	temp.m128_f32[1] *= res->VRAMPixelShader.gammaRatio;
	temp.m128_f32[2] *= res->VRAMPixelShader.gammaRatio;
	m_spriteBatch->Draw(ui->m_image, ui->m_location, NULL,  temp, 0.0f, XMFLOAT2(0, 0), scale, SpriteEffects::SpriteEffects_None, 0.0f);

	m_spriteBatch->End();
	res->m_SharedDeviceContext->OMSetDepthStencilState(NULL, 0);
}
void UIPrinter::DrawButton(ResourceManager* res, UIimage* ui, float scale)
{
	DrawUI(res, ui, scale);
	DrawString(res, &ui->m_text);
}
void UIPrinter::DrawString(ResourceManager* res, UITEXT* text)
{
	m_spriteBatch->Begin();
	m_spriteBatch->SetViewport(res->m_DirectView);
	XMVECTOR temp = text->m_color;
	temp.m128_f32[0] *= res->VRAMPixelShader.gammaRatio;
	temp.m128_f32[1] *= res->VRAMPixelShader.gammaRatio;
	temp.m128_f32[2] *= res->VRAMPixelShader.gammaRatio;
	m_textFont->DrawString(m_spriteBatch.get(), text->m_characters, text->m_location, temp);
	m_spriteBatch->End();
	res->m_SharedDeviceContext->OMSetDepthStencilState(NULL, 0);
}

void UIPrinter::CreateHealthBar(ResourceManager* res)
{
	UITEXT x;
	
	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\HealthBar\\HealthBarActual1.dds", NULL, &m_barContainer.m_image);
	m_barContainer.m_location = XMFLOAT2(res->m_DirectView.TopLeftX, res->m_DirectView.TopLeftY);
	m_barContainer.m_color = DirectX::Colors::Black;
	m_barContainer.m_text = x;

	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\HealthBar\\HealthSub1.dds", NULL, &m_Health[0].m_image);
	m_Health[0].m_location = XMFLOAT2(res->m_DirectView.TopLeftX+22.0f, res->m_DirectView.TopLeftY + 0.3f);
	m_Health[0].m_color = DirectX::Colors::Green;
	m_Health[0].m_text = x;

	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\HealthBar\\HealthSub2.dds", NULL, &m_Health[1].m_image);
	m_Health[1].m_location = XMFLOAT2(res->m_DirectView.TopLeftX + 128.0f, res->m_DirectView.TopLeftY + 0.3f);
	m_Health[1].m_color = DirectX::Colors::Green;
	m_Health[1].m_text = x;

	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\HealthBar\\HealthSub3.dds", NULL, &m_Health[2].m_image);
	m_Health[2].m_location = XMFLOAT2(res->m_DirectView.TopLeftX + 238.0f, res->m_DirectView.TopLeftY + 0.1f);
	m_Health[2].m_color = DirectX::Colors::Green;
	m_Health[2].m_text = x;

	CreateDDSTextureFromFile(res->m_SharedDevice, L"..\\Resources\\HealthBar\\HealthSub4.dds", NULL, &m_Health[3].m_image);
	m_Health[3].m_location = XMFLOAT2(res->m_DirectView.TopLeftX + 355.0f, res->m_DirectView.TopLeftY+3.5f);
	m_Health[3].m_color = DirectX::Colors::Green;
	m_Health[3].m_text = x;

	


}

void UIPrinter::DrawHealthBar(ResourceManager* res, float health)
{
	if (health < 75.0f&&health > 50.0f)
		m_count = 2;
	else if (health < 50.0f&&health>25.0f)
		m_count = 1;
	else if (health < 25&&health>0.0f)
		m_count = 0;
	else if(health<=0.0f || health>100.0f)
		m_count = -1;
	if (health <= 65.0f&&health > 50.0f)
	{
		m_Health[2].m_color = DirectX::Colors::Yellow;
		m_Health[1].m_color = DirectX::Colors::Yellow;
		m_Health[0].m_color = DirectX::Colors::Yellow;
		m_count = 2;
	}
	else if (health <= 25.0f&&health > 0.0f)
	{
		m_Health[0].m_color = DirectX::Colors::Red;
		
		if (m_flash)
		{
			m_barContainer.m_color = DirectX::Colors::Crimson;
			m_flash = false;
		}
		else if (!m_flash)
		{
			m_barContainer.m_color = DirectX::Colors::Black;
			m_flash = !m_flash;
		}
	}
	if(health<=0.0f)
		m_barContainer.m_color = DirectX::Colors::Black;
	DrawUI(res, &m_barContainer, 1.3f);
	if (m_count > -1)
	{
		for (int i = m_count; i >= 0; i--)
		{
			DrawUI(res, &m_Health[i], 1.3f);
		}
	}
}
void UIPrinter::ResetHealthBar()
{
	m_count = 3;
	m_flash = false;
	for (size_t i = 0; i < 4; i++)
	{
		m_Health[i].m_color = DirectX::Colors::Green;
	}
	m_barContainer.m_color = DirectX::Colors::Black;
}
void UIPrinter::Shutdown()
{
	
	if (m_barContainer.m_image)
		m_barContainer.Shutdown();
	for (size_t i = 0; i < 4; i++)
	{
		if (m_Health[i].m_image)
			m_Health[i].Shutdown();
	}
	m_spriteBatch.reset(nullptr);
	m_spriteBatch.release();
	m_textFont.reset(nullptr);
	m_textFont.release();
}

