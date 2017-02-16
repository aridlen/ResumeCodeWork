#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Larri Nori            //
//      Date:  AUGUST 2016               //
//                                       //
///////////////////////////////////////////
#include<string>
#include <DirectXMath.h>
#include<vector>
#include "..\Common\DeviceResources.h"
#include"Content\DDSTextureLoader.h"
#include "..\Common\DirectXHelper.h"
#include "ShaderStructures.h"
#include "PS_TextureShader.csh"
#include "MeshVertexShader.csh"
#include "SkyBox_PS.csh"
#include "SkyBox_VS.csh"
#include "MyLights.csh"
#include "ShaderPostProcess.csh"
using namespace DirectX;

struct VERTEX
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
	XMFLOAT3 norm;
};
struct MATRIXDATA
{
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

class Model 
{
public:

	Model();
	~Model();
	std::string ModelName, fileNameMesh;
	const wchar_t* TexturePath;
	const wchar_t* TexturePath2;
	std::vector<VERTEX> vertBuffer;
	std::vector<UINT> indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_IndexBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_ShaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_ShaderResourceView2;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inLayout;
	UINT modelSize;
	MATRIXDATA WVP;
	
	bool loadComplete;
	bool SkyboxComplete;
	bool Skytext;
	bool objtext;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBufferLights;
	void LoadModel(std::shared_ptr<DX::DeviceResources> _device);
	void SetModelResource(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state,bool post);
	void UpdateInRender(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state,bool rtt, ID3D11ShaderResourceView* rttTexture);
	void UpdateInRender(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state);
	void LoadSkyBox(std::shared_ptr<DX::DeviceResources> _device);
	void UpdateSkyBoxInRender(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state, ID3D11RasterizerState* ras1, ID3D11RasterizerState* ras2);
	void SetSkyBoxResource(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state, ID3D11RasterizerState* ras1, ID3D11RasterizerState* ras2, bool post);

	
};

