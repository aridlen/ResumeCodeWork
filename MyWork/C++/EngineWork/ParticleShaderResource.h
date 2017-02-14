#pragma once
#include<d3dcompiler.h>
#include<d3d11shader.h>
#include<fstream>
#include "ParticleSystem.h"
class ParticleShaderResource
{
	struct MatrixBufferType
	{
		XMFLOAT4X4 world;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
	};
	bool InitializeShader(ID3D11Device* device, HWND win, WCHAR* file, WCHAR* file2);
	void ShutdownShader();
	
	bool SetShaderParameters(ResourceManager* res,ID3D11DeviceContext* context, XMFLOAT4X4 m1, XMFLOAT4X4 m2, XMFLOAT4X4 m3, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext*context, int x);
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
public:
	ParticleShaderResource();
	ParticleShaderResource(const ParticleShaderResource& obj);
	~ParticleShaderResource();
	bool Initialize(ID3D11Device* device, HWND win);
	void Shutdown();
	bool Render(ResourceManager* res,ID3D11DeviceContext* context, int x, XMFLOAT4X4 m1, XMFLOAT4X4 m2, XMFLOAT4X4 m3, ID3D11ShaderResourceView* texture,ParticleSystem* sys);
};

