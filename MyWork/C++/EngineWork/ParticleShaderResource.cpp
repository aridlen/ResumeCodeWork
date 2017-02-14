#include "stdafx.h"
#include "ParticleShaderResource.h"
#include"..\Shaders\ParticlePS.csh"
#include"..\Shaders\ParticleVS.csh"

bool ParticleShaderResource::InitializeShader(ID3D11Device * device, HWND win, WCHAR * file, WCHAR * file2)
{
	HRESULT hr;
	
	D3D11_INPUT_ELEMENT_DESC polyLayout[3];
	unsigned int num;
	D3D11_BUFFER_DESC matrixBuffDesc;
	D3D11_SAMPLER_DESC sampleDesc;
	
	hr = device->CreateVertexShader(ParticleVS, sizeof(ParticleVS), NULL, &m_vertexShader);
	
	hr = device->CreatePixelShader(ParticlePS, sizeof(ParticlePS), NULL, &m_pixelShader);
	

	polyLayout[0].SemanticName = "POSITION";
	polyLayout[0].SemanticIndex = 0;
	polyLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polyLayout[0].InputSlot = 0;
	polyLayout[0].AlignedByteOffset = 0;
	polyLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polyLayout[0].InstanceDataStepRate = 0;

	polyLayout[1].SemanticName = "TEXCOORD";
	polyLayout[1].SemanticIndex = 0;
	polyLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polyLayout[1].InputSlot = 0;
	polyLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polyLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polyLayout[1].InstanceDataStepRate = 0;

	polyLayout[2].SemanticName = "COLOR";
	polyLayout[2].SemanticIndex = 0;
	polyLayout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polyLayout[2].InputSlot = 0;
	polyLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polyLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polyLayout[2].InstanceDataStepRate = 0;


	num = sizeof(polyLayout) / sizeof(polyLayout[0]);
	//_device->CreateInputLayout(Layout, 5, Trivial_VS, sizeof(Trivial_VS), &m_RegLayout);
	hr = device->CreateInputLayout(polyLayout, num, ParticleVS, sizeof(ParticleVS), &m_layout);
	

	matrixBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBuffDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBuffDesc.MiscFlags = 0;
	matrixBuffDesc.StructureByteStride = 0;
	hr = device->CreateBuffer(&matrixBuffDesc, NULL, &m_matrixBuffer);
	if (FAILED(hr))
		return false;
	
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.MipLODBias = 0.0f;
	sampleDesc.MaxAnisotropy = 1;
	sampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampleDesc.BorderColor[0] = 0;
	sampleDesc.BorderColor[1] = 0;
	sampleDesc.BorderColor[2] = 0;
	sampleDesc.BorderColor[3] = 0;
	sampleDesc.MinLOD = 0;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&sampleDesc, &m_sampleState);
	if (FAILED(hr))
		return false;
	return true;

}

void ParticleShaderResource::ShutdownShader()
{
	
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}


	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}


	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}


bool ParticleShaderResource::SetShaderParameters(ResourceManager* res,ID3D11DeviceContext * context, XMFLOAT4X4 m1, XMFLOAT4X4 m2, XMFLOAT4X4 m3, ID3D11ShaderResourceView * texture)
{
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE map;
	MatrixBufferType* data;
	unsigned int buffNum;
	
	XMMATRIX w = XMMatrixTranspose(XMLoadFloat4x4(&m1));
	XMMATRIX v = XMMatrixTranspose(XMLoadFloat4x4(&m2));
	XMMATRIX p = XMMatrixTranspose(XMLoadFloat4x4(&m3));

	hr = context->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	if (FAILED(hr))
		return false;
	data = (MatrixBufferType*)map.pData;
	XMStoreFloat4x4(&data->world, w);
	XMStoreFloat4x4(&data->view, v);
	XMStoreFloat4x4(&data->projection, p);

	context->Unmap(m_matrixBuffer, 0);
	buffNum = 0;
	context->VSSetConstantBuffers(buffNum, 1, &m_matrixBuffer);
	context->PSSetConstantBuffers(0, 0, &res->m_constantPixelBuffer);
	context->PSSetShaderResources(0, 1, &texture);

	return true;
}

void ParticleShaderResource::RenderShader(ID3D11DeviceContext * context, int x)
{
	context->IASetInputLayout(m_layout);
	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->PSSetSamplers(0, 1, &m_sampleState);
	//context->DrawIndexed(x,0,0);
	context->Draw(x, 0);

}

ParticleShaderResource::ParticleShaderResource()
{
}

ParticleShaderResource::ParticleShaderResource(const ParticleShaderResource & obj)
{
}


ParticleShaderResource::~ParticleShaderResource()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
}

bool ParticleShaderResource::Initialize(ID3D11Device * device, HWND win)
{
	bool hr = InitializeShader(device, win, L"..//RENDERER//ParticleVS.hlsl", L"..//RENDERER//ParticlePS.hlsl");
	if(!hr)
	return false;

	return true;
}

void ParticleShaderResource::Shutdown()
{
	ShutdownShader();
}

bool ParticleShaderResource::Render(ResourceManager* res,ID3D11DeviceContext * context, int x, XMFLOAT4X4 m1, XMFLOAT4X4 m2, XMFLOAT4X4 m3, ID3D11ShaderResourceView * texture, ParticleSystem* sys)
{
	if (sys->GetPlay())
	{
		bool hr = SetShaderParameters(res,context, m1, m2, m3, texture);
		if (!hr)
			return false;
		RenderShader(context, x);
		return true;
	}
	return false;
}
