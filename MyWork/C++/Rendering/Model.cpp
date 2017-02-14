#include "pch.h"
#include "Model.h"


Model::Model()
{
	loadComplete = false;
	SkyboxComplete = false;
}
Model::~Model()
{

	delete[] TexturePath;
	delete[] TexturePath2;
	m_constantBuffer.Reset();
	m_constantBufferLights.Reset();
	m_IndexBuffer.Reset();
	m_inLayout.Reset();
	m_pixelShader.Reset();
	m_ShaderResourceView.Reset();
	m_ShaderResourceView2.Reset();
	m_VertexBuffer.Reset();
	m_vShader.Reset();
}
void Model::LoadModel(std::shared_ptr<DX::DeviceResources> _device)
{
	if (TexturePath == NULL)
	{
		TexturePath= L"PyramidTexture.dds";

	}
	if (TexturePath2 == NULL)
	{
		TexturePath2 = TexturePath;
	}
	
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_device->GetD3DDevice(),
			TexturePath,
			NULL,
			m_ShaderResourceView.GetAddressOf()
		));
	
	
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_device->GetD3DDevice(),
			TexturePath2,
			NULL,
			m_ShaderResourceView2.GetAddressOf()
		));

	
	
		std::vector<XMFLOAT3> _verts;
		std::vector<XMFLOAT2> _uv;
		std::vector<XMFLOAT3> _norm;
		std::vector<UINT> _vertind;
		std::vector<UINT> _uvind;
		std::vector<UINT> _normind;
		std::FILE *file;

		//wchar_t dir[_MAX_DIR];
		//GetCurrentDirectory(_MAX_DIR, dir);
		errno_t  err = fopen_s(&file, fileNameMesh.c_str(), "r");
		if (file == NULL)
		{

			printf_s("Impossible to open the file !\n");
			return;
		}
		for (;;)
		{

			char lineHeader[128];
			INT res = fscanf_s(file, "%s", lineHeader, 128);
			if (res == EOF)
				break;
			else
			{
				if (strcmp(lineHeader, "v") == 0)
				{
					XMFLOAT3 temp_V;
					fscanf_s(file, "%f %f %f/n", &temp_V.x, &temp_V.y, &temp_V.z);
					_verts.push_back(temp_V);
				}
				else if (strcmp(lineHeader, "vt") == 0)
				{
					XMFLOAT2 temp_uv;
					fscanf_s(file, "%f %f/n", &temp_uv.x, &temp_uv.y);
					temp_uv.y = 1 - temp_uv.y;
					_uv.push_back(temp_uv);
				}
				else if (strcmp(lineHeader, "vn") == 0)
				{
					XMFLOAT3 temp_norm;
					fscanf_s(file, "%f %f %f/n", &temp_norm.x, &temp_norm.y, &temp_norm.z);
					_norm.push_back(temp_norm);
				}
				else if (strcmp(lineHeader, "f") == 0)
				{
					std::string v1, v2, v3;
					UINT vI[3], uvI[3], nI[3];
					INT match = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vI[0], &uvI[0], &nI[0],
						&vI[1], &uvI[1], &nI[1],
						&vI[2], &uvI[2], &nI[2]
					);
					if (match != 9)
					{

						printf_s("File can't be read!");
						return;
					}
					_vertind.push_back(vI[0]);
					_vertind.push_back(vI[1]);
					_vertind.push_back(vI[2]);

					_uvind.push_back(uvI[0]);
					_uvind.push_back(uvI[1]);
					_uvind.push_back(uvI[2]);

					_normind.push_back(nI[0]);
					_normind.push_back(nI[1]);
					_normind.push_back(nI[2]);



				}
			}
		}

		modelSize = (UINT)_vertind.size();
		for (UINT i = 0; i < _vertind.size(); ++i)
		{
			VERTEX temp;

			temp.pos = _verts[_vertind[i] - 1];
			temp.uv = _uv[_uvind[i] - 1];
			temp.norm = _norm[_normind[i] - 1];
			temp.pos.z = (-temp.pos.z);
			vertBuffer.push_back(temp);
			indexBuffer.push_back(i);

		}

	


}
void Model::SetModelResource(DX::DeviceResources* _device, ID3D11SamplerState*	m_state,bool post)
{
	
	
	auto loadPSTask = DX::ReadDataAsync(L"MyLights.cso");
	auto loadPSTask2 = DX::ReadDataAsync(L"ShaderPostProcess.cso");
	auto loadVSTask = DX::ReadDataAsync(L"MeshVertexShader.cso");
	auto createVSTask = loadVSTask.then([this, _device](const std::vector<byte>& fileData)
	{
		DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(), NULL, m_vShader.GetAddressOf()
			)
		);

		static const D3D11_INPUT_ELEMENT_DESC MeshDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },

		};

		DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateInputLayout(
				MeshDesc,
				ARRAYSIZE(MeshDesc),
				&fileData[0],
				fileData.size() ,
				m_inLayout.GetAddressOf()
			)
		);
	});
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(XMFLOAT4X4) * 3, D3D11_BIND_CONSTANT_BUFFER);
	
	
		auto createPSTask2 = loadPSTask2.then([this, _device, constantBufferDesc,post](const std::vector<byte>& fileData)
		{
			if (post)
			{
				DX::ThrowIfFailed(
					_device->GetD3DDevice()->CreatePixelShader(
						&fileData[0],
						fileData.size(),
						NULL,
						m_pixelShader.GetAddressOf()
					));
			}
			DX::ThrowIfFailed(
				_device->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					m_constantBuffer.GetAddressOf()

				));
		});
		
	
	
		auto createPSTask = loadPSTask.then([this, _device, constantBufferDesc,post](const std::vector<byte>& fileData)
		{
			if (post == false)
			{
				DX::ThrowIfFailed(
					_device->GetD3DDevice()->CreatePixelShader(
						&fileData[0],
						fileData.size(),
						NULL,
						m_pixelShader.GetAddressOf()
					));
			}
			DX::ThrowIfFailed(
				_device->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					m_constantBuffer.GetAddressOf()

				));
		});
	
		auto createObjectTask = (createVSTask && createPSTask && createPSTask2).then([this,_device,&m_state]() {
			//CREATE VERTEX BUFFER
			D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
			vertexBufferData.pSysMem = vertBuffer.data();
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;

			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VERTEX)*(UINT)vertBuffer.size(), D3D11_BIND_VERTEX_BUFFER);
			DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_VertexBuffer.GetAddressOf()));

			//CREATE INDEX BUFFER
			D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
			indexBufferData.pSysMem = indexBuffer.data();
			indexBufferData.SysMemPitch = 0;

			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(UINT)*(UINT)indexBuffer.size(), D3D11_BIND_INDEX_BUFFER);
			DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, m_IndexBuffer.GetAddressOf()));

			// After the pixel shader file is loaded, create the shader and constant buffer.


				/*_device->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					m_constantBuffer.GetAddressOf()

				);*/


			D3D11_SAMPLER_DESC state;
			ZeroMemory(&state, sizeof(D3D11_SAMPLER_DESC));
			state.Filter = D3D11_FILTER_ANISOTROPIC;
			state.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			state.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			state.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			state.MaxAnisotropy = 1;
			DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateSamplerState(&state, &m_state));



		});
	//MY VERTEX 
		createObjectTask.then([this]() {
			loadComplete = true;
			

		});
	
	// After the vertex shader file is loaded, create the shader and input layout.
	
}
void Model::UpdateInRender(DX::DeviceResources* _device, ID3D11SamplerState* m_state, bool rtt, ID3D11ShaderResourceView* rttTexture)
{

	
	if (m_IndexBuffer == NULL || m_VertexBuffer == NULL || loadComplete==false )
	{
		return;
	}

	auto context = _device->GetD3DDeviceContext();
	
	
	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&WVP,
		0,
		0,
		0
	);



	context->IASetIndexBuffer(
		m_IndexBuffer.Get(),
		DXGI_FORMAT_R32_UINT, // Each index is one 16-bit unsigned integer (short).
		0
	);
	UINT stride2 = sizeof(VERTEX);
	UINT offset2 = 0;
	context->IASetVertexBuffers(
		0,
		1,
		m_VertexBuffer.GetAddressOf(),
		&stride2,
		&offset2
	);

	
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//MY LAYOUT
	context->IASetInputLayout(m_inLayout.Get());


	// Attach our vertex shader.
	context->VSSetShader(
		m_vShader.Get(),
		nullptr,
		0
	);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
	);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
	);


	// rasterizer state
	// front face = counterclockwise
	context->PSSetSamplers(0, 1, &m_state);
	if (rtt==false)
	{
		context->PSSetShaderResources(0, 1, m_ShaderResourceView.GetAddressOf());
		context->PSSetShaderResources(1, 1, m_ShaderResourceView2.GetAddressOf());
	}
	else if (rtt)
	{
		//context->GenerateMips(rttTexture);
		context->PSSetShaderResources(0, 1, &rttTexture);
		context->PSSetShaderResources(1, 1, &rttTexture);

	}
	// Draw the objects.
	context->DrawIndexed(
		modelSize,
		0,
		0
	);


}
void Model::UpdateInRender(DX::DeviceResources* _device, ID3D11SamplerState* m_state)
{


	if (m_IndexBuffer == NULL || m_VertexBuffer == NULL || loadComplete == false)
	{
		return;
	}

	auto context = _device->GetD3DDeviceContext();


	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&WVP,
		0,
		0,
		0
	);



	context->IASetIndexBuffer(
		m_IndexBuffer.Get(),
		DXGI_FORMAT_R32_UINT, // Each index is one 16-bit unsigned integer (short).
		0
	);
	UINT stride2 = sizeof(VERTEX);
	UINT offset2 = 0;
	context->IASetVertexBuffers(
		0,
		1,
		m_VertexBuffer.GetAddressOf(),
		&stride2,
		&offset2
	);


	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//MY LAYOUT
	context->IASetInputLayout(m_inLayout.Get());


	// Attach our vertex shader.
	context->VSSetShader(
		m_vShader.Get(),
		nullptr,
		0
	);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
	);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
	);


	// rasterizer state
	// front face = counterclockwise
	context->PSSetSamplers(0, 1, &m_state);
	
		context->PSSetShaderResources(0, 1, m_ShaderResourceView.GetAddressOf());
		context->PSSetShaderResources(1, 1, m_ShaderResourceView2.GetAddressOf());
	

	// Draw the objects.
	context->DrawIndexed(
		modelSize,
		0,
		0
	);


}
void Model::LoadSkyBox(std::shared_ptr<DX::DeviceResources> _device)
{
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_device->GetD3DDevice(),
			TexturePath,
			NULL,
			m_ShaderResourceView.GetAddressOf()
		));
	
	
		std::vector<XMFLOAT3> _verts;
		std::vector<XMFLOAT2> _uv;
		std::vector<XMFLOAT3> _norm;
		std::vector<UINT> _vertind;
		std::vector<UINT> _uvind;
		std::vector<UINT> _normind;
		std::FILE *file;

		//wchar_t dir[_MAX_DIR];
		//GetCurrentDirectory(_MAX_DIR, dir);
		errno_t  err = fopen_s(&file, fileNameMesh.c_str(), "r");
		if (file == NULL)
		{

			printf_s("Impossible to open the file !\n");
			return;
		}
		for (;;)
		{

			char lineHeader[128];
			INT res = fscanf_s(file, "%s", lineHeader, 128);
			if (res == EOF)
				break;
			else
			{
				if (strcmp(lineHeader, "v") == 0)
				{
					XMFLOAT3 temp_V;
					fscanf_s(file, "%f %f %f/n", &temp_V.x, &temp_V.y, &temp_V.z);
					_verts.push_back(temp_V);
				}
				else if (strcmp(lineHeader, "vt") == 0)
				{
					XMFLOAT2 temp_uv;
					fscanf_s(file, "%f %f/n", &temp_uv.x, &temp_uv.y);
					temp_uv.y = 1 - temp_uv.y;
					_uv.push_back(temp_uv);
				}
				else if (strcmp(lineHeader, "vn") == 0)
				{
					XMFLOAT3 temp_norm;
					fscanf_s(file, "%f %f %f/n", &temp_norm.x, &temp_norm.y, &temp_norm.z);
					_norm.push_back(temp_norm);
				}
				else if (strcmp(lineHeader, "f") == 0)
				{
					std::string v1, v2, v3;
					UINT vI[3], uvI[3], nI[3];
					INT match = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vI[0], &uvI[0], &nI[0],
						&vI[1], &uvI[1], &nI[1],
						&vI[2], &uvI[2], &nI[2]
					);
					if (match != 9)
					{

						printf_s("File can't be read!");
						return;
					}
					_vertind.push_back(vI[0]);
					_vertind.push_back(vI[1]);
					_vertind.push_back(vI[2]);

					_uvind.push_back(uvI[0]);
					_uvind.push_back(uvI[1]);
					_uvind.push_back(uvI[2]);

					_normind.push_back(nI[0]);
					_normind.push_back(nI[1]);
					_normind.push_back(nI[2]);



				}
			}
		}

		modelSize = (UINT)_vertind.size();
		for (UINT i = 0; i < _vertind.size(); ++i)
		{
			VERTEX temp;

			temp.pos = _verts[_vertind[i] - 1];
			temp.uv = _uv[_uvind[i] - 1];
			temp.norm = _norm[_normind[i] - 1];
			temp.pos.z = temp.pos.z;
			vertBuffer.push_back(temp);
			indexBuffer.push_back(i);

		}


	

}
void Model::UpdateSkyBoxInRender(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state, ID3D11RasterizerState* ras1, ID3D11RasterizerState* ras2)
{

	if (m_IndexBuffer == NULL || m_VertexBuffer == NULL || SkyboxComplete==false)
	{
		return;
	}

	auto context = _device->GetD3DDeviceContext();

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&WVP,
		0,
		0,
		0
	);



	context->IASetIndexBuffer(
		m_IndexBuffer.Get(),
		DXGI_FORMAT_R32_UINT, // Each index is one 16-bit unsigned integer (short).
		0
	);
	UINT stride2 = sizeof(VERTEX);
	UINT offset2 = 0;
	context->IASetVertexBuffers(
		0,
		1,
		m_VertexBuffer.GetAddressOf(),
		&stride2,
		&offset2
	);


	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//MY LAYOUT
	context->IASetInputLayout(m_inLayout.Get());


	// Attach our vertex shader.
	context->VSSetShader(
		m_vShader.Get(),
		nullptr,
		0
	);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
	);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
	);


	// rasterizer state
	// front face = counterclockwise
	context->PSSetSamplers(0, 1, &m_state);
	context->PSSetShaderResources(0, 1, m_ShaderResourceView.GetAddressOf());
	context->RSSetState(ras1);
	// Draw the objects.
	context->DrawIndexed(
		modelSize,
		0,
		0
	);
	context->RSSetState(ras2);

	context->ClearDepthStencilView(_device->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);


}
void Model::SetSkyBoxResource(DX::DeviceResources*  _device, ID3D11SamplerState*	m_state, ID3D11RasterizerState* ras1, ID3D11RasterizerState* ras2, bool post)
{
	auto loadVSTask = DX::ReadDataAsync(L"SkyBox_VS.cso");
	auto loadPSTask = DX::ReadDataAsync(L"SkyBox_PS.cso");
	auto loadPSTask2 = DX::ReadDataAsync(L"SkyBoxPost_PS.cso");
	auto createVSTask = loadVSTask.then([this, _device](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(), NULL, m_vShader.GetAddressOf()
			));

		static const D3D11_INPUT_ELEMENT_DESC MeshDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DX::ThrowIfFailed(
		_device->GetD3DDevice()->CreateInputLayout(
			MeshDesc,
			ARRAYSIZE(MeshDesc),
			&fileData[0],
			fileData.size(),
			m_inLayout.GetAddressOf()
		));

	});

	auto createPSTask = loadPSTask.then([this,_device,post](const std::vector<byte>& fileData) {
		if (post == false)
		{
			DX::ThrowIfFailed(
				_device->GetD3DDevice()->CreatePixelShader(
					&fileData[0],
					fileData.size(),
					NULL,
					m_pixelShader.GetAddressOf()
				)
			);
		}
			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(XMFLOAT4X4) * 3, D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				_device->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					m_constantBuffer.GetAddressOf()
				)
			);
		
	});
	auto createPSTask2 = loadPSTask2.then([this, _device, post](const std::vector<byte>& fileData) {
		if (post)
		{
			DX::ThrowIfFailed(
				_device->GetD3DDevice()->CreatePixelShader(
					&fileData[0],
					fileData.size(),
					NULL,
					m_pixelShader.GetAddressOf()
				)
			);
			
		}
			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(XMFLOAT4X4) * 3, D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				_device->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					m_constantBuffer.GetAddressOf()
				)
			);
		
	});
	auto createSkyTask = (createPSTask && createVSTask && createPSTask2).then([this,_device,&ras1,&ras2,&m_state]() {
		//CREATE VERTEX BUFFER
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertBuffer.data();
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VERTEX)*(UINT)vertBuffer.size(), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
		_device->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_VertexBuffer.GetAddressOf())
		);
		//CREATE INDEX BUFFER
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indexBuffer.data();
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(UINT)*(UINT)indexBuffer.size(), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			_device->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, m_IndexBuffer.GetAddressOf())
		);

		// After the pixel shader file is loaded, create the shader and constant buffer.




		D3D11_SAMPLER_DESC state;
		ZeroMemory(&state, sizeof(D3D11_SAMPLER_DESC));
		state.Filter = D3D11_FILTER_ANISOTROPIC;
		state.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		state.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		state.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		state.MaxAnisotropy = 1;
		DX::ThrowIfFailed(
		_device->GetD3DDevice()->CreateSamplerState(&state, &m_state)

		);


		//MY VERTEX 


		// After the vertex shader file is loaded, create the shader and input layout.




		//CW
		CD3D11_RASTERIZER_DESC ras_desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
		ras_desc.FrontCounterClockwise = FALSE;
		//CCW
		CD3D11_RASTERIZER_DESC ras_desc2 = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
		ras_desc2.FrontCounterClockwise = TRUE;

		DX::ThrowIfFailed(
		_device->GetD3DDevice()->CreateRasterizerState(&ras_desc, &ras1));
		DX::ThrowIfFailed(
		_device->GetD3DDevice()->CreateRasterizerState(&ras_desc2, &ras2));
	});
	createSkyTask.then([this]() {
		SkyboxComplete = true;
	});


}
