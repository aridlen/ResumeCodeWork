#include "stdafx.h"
#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	m_texture = 0;
	m_particleList = 0;
	m_vertices = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ParticleSystem::ParticleSystem(const ParticleSystem &)
{
}


ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::Initialize(ID3D11Device *device, ParticleProperties prop)
{
	
	endofParticles = false;
	runTime = 0.0f;
	m_playEffect = false;
	m_currentAnimation = prop.m_effect;
	if (m_currentAnimation == SPARK)
		fadeOut = 1.0f;
	else
	fadeOut = 0.01f;
	
	 CreateDDSTextureFromFile(device, prop.file, NULL, &m_texture);
	/*if(!hr)
	return false;*/

	InitializeParticle(prop.size,prop.devX,prop.devY,prop.devZ);
	/*if (!hr)
		return false;*/

	InitializeBuffer(device,prop.m_effect);
	/*if (!hr)
		return false;*/

	return true;
}

void ParticleSystem::Shutdown()
{
	ShutdownBuffers();
	ShutdownParticle();
	ReleaseTexture();
	//m_media.Shutdown();

}

bool ParticleSystem::Frame(float data, ID3D11DeviceContext * context,ResourceManager* res)
{


	if (m_playEffect)
	{
		
		KillParticles();
		if (m_currentAnimation == SPARK)
			EmitSparkParticles(data*30.0f);
		else if (m_currentAnimation == BLOOD)
			EmitBloodParticles(data*0.2f);
		else
		{
			//m_media.PlaySFX(WARP);
			EmitParticles(data*2.0f);
		}
		UpdateParticles(data*2.0f,res);
		UpdateBuffers(context);
	}


	return true;
}

void ParticleSystem::Render(ID3D11DeviceContext * context)
{
	if(m_playEffect)
	RenderBuffers(context);
}

ID3D11ShaderResourceView * ParticleSystem::GetTexture()
{
	return m_texture;
}

int ParticleSystem::GetIndexCount()
{
	return m_indexCount;
}



void ParticleSystem::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Release();
		//delete m_texture;
		m_texture = 0;
	}
}

bool ParticleSystem::InitializeParticle(float size, float devX, float devY, float devZ)
{
	////Location during emission
	m_deviationX = devX;//3.0f;
	m_deviationY = devY;//0.5f;
	m_deviationZ = devZ;//3.0f;
	////////////speed////
	m_particleVelocity = 2.0f;
	m_particleVelocityVariation = 0.2f;
	m_particlesPerSecond = 1000.0f;
	m_size = size;//0.5f;
	m_maxParticles = 1000;
	////ParticleList creation
	m_particleList = new ParticleType[m_maxParticles];
//	m_media.Initialize();
	if (!m_particleList)
		return false;
	////////init particle list
	for (size_t i = 0; i < m_maxParticles; i++)
	{
		m_particleList[i].active = false;
	
	}
	//////////
	m_currentCount = 0;
	m_TotalTime = 0.0f;
	return true;
}

void ParticleSystem::ShutdownParticle()
{
	if (m_particleList)
	{
		delete[]m_particleList;
		m_particleList = 0;
	}
}

bool ParticleSystem::InitializeBuffer(ID3D11Device * device,ParticleEffect typeAnimation)
{
	m_currentAnimation = typeAnimation;
	unsigned long* indices;
	int i;
	D3D11_BUFFER_DESC vertexBuffDesc, indexBuffDesc;
	D3D11_SUBRESOURCE_DATA vertData, indexData;

	m_vertexCount = m_maxParticles * 6;
	m_indexCount = m_vertexCount;
	m_vertices = new VertexType[m_vertexCount];
	if (!m_vertices)
		return false;
	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	memset(m_vertices, 0, (sizeof(VertexType)*m_vertexCount));
	for (i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}
	vertexBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBuffDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.CPUAccessFlags =D3D11_CPU_ACCESS_WRITE;
	vertexBuffDesc.MiscFlags = 0;
	vertexBuffDesc.StructureByteStride = 0;

	vertData.pSysMem = m_vertices;
	vertData.SysMemPitch = 0;
	vertData.SysMemSlicePitch = 0;

	HRESULT hr;
	hr = device->CreateBuffer(&vertexBuffDesc, &vertData, &m_vertexBuffer);
	if (FAILED(hr))
		return false;

	indexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBuffDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBuffDesc.CPUAccessFlags = 0;
	indexBuffDesc.MiscFlags = 0;
	indexBuffDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&indexBuffDesc, &indexData, &m_indexBuffer);
	if (FAILED(hr))
		return false;

	delete[] indices;
	indices = 0;
	return true;

}

void ParticleSystem::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	if (m_vertices)
	{
		delete[] m_vertices;
		m_vertices = 0;
	}
}

void ParticleSystem::EmitParticles(float time)
{
	
	bool emitParticle, found;
	float x, y, z, v, r, g, b,a;
	int index, i, j;
	m_TotalTime += time;
	emitParticle = false;
	//a = 1.0f;
	if ((m_TotalTime > (1000.0f / m_particlesPerSecond) || runTime < 100.0f))
	{
		m_TotalTime = 0.0f;
		emitParticle = true;
	}
	if (!endofParticles&& emitParticle && (m_currentCount < (m_maxParticles - 1)))
	{
		m_currentCount++;
		x = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationX;

		y = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationY;
		z = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationZ;
		v = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX)*m_particleVelocityVariation;
		r = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		g = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		b = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		a = fadeOut + TRANSPARENCY;
		fadeOut = a;
		index = 0;
		found = false;
		while (!found)
		{
			if ((!m_particleList[index].active) || (m_particleList[index].z < z))
				found = true;
			else
				index++;
		}

		i = m_currentCount;
		j = i - 1;

		while (i != index)
		{
			m_particleList[i].x = m_particleList[j].x;
			m_particleList[i].y = m_particleList[j].y;
			m_particleList[i].z = m_particleList[j].z;
			m_particleList[i].r = m_particleList[j].r;
			m_particleList[i].g = m_particleList[j].g;
			m_particleList[i].b = m_particleList[j].b;
			m_particleList[i].a = m_particleList[j].a;
			m_particleList[i].velocity = m_particleList[j].velocity;
			m_particleList[i].active = m_particleList[j].active;
			i--;
			j--;

		}

		m_particleList[index].x = x;
		m_particleList[index].y = y;
		m_particleList[index].z = z;
		m_particleList[index].r = r;
		m_particleList[index].g = g;
		m_particleList[index].b = b;
		m_particleList[index].a = a;
		m_particleList[index].velocity = v;
		m_particleList[index].active = true;

	}
}

void ParticleSystem::EmitSparkParticles(float time)
{
	
	bool emitParticle, found;
	float x, y, z, v, r, g, b,a;
	int index, i, j;
	m_TotalTime += time;
	a = 1.0f;
	emitParticle = false;
	XMFLOAT3 colorChangeYellow = XMFLOAT3(DirectX::Colors::Yellow.f[0], DirectX::Colors::Yellow.f[1], DirectX::Colors::Yellow.f[2]);
	
	XMFLOAT3 colorChangeWhite = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 colorChangeBlue = XMFLOAT3(0.0f, 0.0f, 1.0f);
	if ((m_TotalTime > (1000.0f / m_particlesPerSecond) || runTime < 100.0f))
	{
		m_TotalTime = 0.0f;
		emitParticle = true;
	}
	if (!endofParticles&& emitParticle && (m_currentCount < (m_maxParticles - 1)))
	{
		m_currentCount++;
		x = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationX;

		y = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationY;
		z = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationZ;
		v = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX)*m_particleVelocityVariation;
		int random = rand() % 3;
		switch (random)
		{
		case 0:
		{
			r = colorChangeYellow.x;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			g = colorChangeYellow.y;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			b = colorChangeYellow.z;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			a = fadeOut - TRANSPARENCY;
			fadeOut = a;
			break;
		}
		case 1:
		{
			r = colorChangeWhite.x;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			g = colorChangeWhite.y;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			b = colorChangeWhite.z;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			a = fadeOut - TRANSPARENCY;
			fadeOut = a;
			break;
		}
		case 2:
		{
			r = colorChangeBlue.x;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			g = colorChangeBlue.y;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			b = colorChangeBlue.z;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			a = fadeOut - TRANSPARENCY;
			fadeOut = a;
			break;
		}
		}
	
		index = 0;
		found = false;
		while (!found)
		{
			if ((!m_particleList[index].active) || (m_particleList[index].z < z))
				found = true;
			else
				index++;
		}

		i = m_currentCount;
		j = i - 1;

		while (i != index)
		{
			m_particleList[i].x = m_particleList[j].x;
			m_particleList[i].y = m_particleList[j].y;
			m_particleList[i].z = m_particleList[j].z;
			m_particleList[i].r = m_particleList[j].r;
			m_particleList[i].g = m_particleList[j].g;
			m_particleList[i].b = m_particleList[j].b;
			m_particleList[i].a = m_particleList[j].a;
			m_particleList[i].velocity = m_particleList[j].velocity;
			m_particleList[i].active = m_particleList[j].active;
			i--;
			j--;

		}

		m_particleList[index].x = x;
		m_particleList[index].y = y;
		m_particleList[index].z = z;
		m_particleList[index].r = r;
		m_particleList[index].g = g;
		m_particleList[index].b = b;
		m_particleList[index].a = a;
		m_particleList[index].velocity = v;
		m_particleList[index].active = true;

	}
}

void ParticleSystem::EmitBloodParticles(float time)
{
	bool emitParticle, found;
	float x, y, z, v, r, g, b,a;
	int index, i, j;
	m_TotalTime += time;
	emitParticle = false;

	if ((m_TotalTime > (1000.0f / m_particlesPerSecond) || runTime < 100.0f))
	{
		m_TotalTime = 0.0f;
		emitParticle = true;
	}
	if (!endofParticles&& emitParticle && (m_currentCount < (m_maxParticles - 1)))
	{
		m_currentCount++;
		x = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationX;

		y = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationY;
		z = (((float)rand() - (float)rand()) / RAND_MAX)*m_deviationZ;
		v = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX)*m_particleVelocityVariation;
		r = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		g = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		b = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		a = fadeOut + TRANSPARENCY;
		fadeOut = a;
		index = 0;
		found = false;
		while (!found)
		{
			if ((!m_particleList[index].active) || (m_particleList[index].z < z))
				found = true;
			else
				index++;
		}

		i = m_currentCount;
		j = i - 1;

		while (i != index)
		{
			m_particleList[i].x = m_particleList[j].x;
			m_particleList[i].y = m_particleList[j].y;
			m_particleList[i].z = m_particleList[j].z;
			m_particleList[i].r = m_particleList[j].r;
			m_particleList[i].g = m_particleList[j].g;
			m_particleList[i].b = m_particleList[j].b;
			m_particleList[i].a = m_particleList[j].a;
			m_particleList[i].velocity = m_particleList[j].velocity;
			m_particleList[i].active = m_particleList[j].active;
			i--;
			j--;

		}

		m_particleList[index].x = x;
		m_particleList[index].y = y;
		m_particleList[index].z = z;
		m_particleList[index].r = r;
		m_particleList[index].g = g;
		m_particleList[index].b = b;
		m_particleList[index].a = a;
		m_particleList[index].velocity = v;
		m_particleList[index].active = true;

	}
}

void ParticleSystem::UpdateParticles(float time, ResourceManager* res)
{
	runTime += time;
	for (size_t i = 0; i < m_currentCount; i++)
	{
		m_particleList[i].y = m_particleList[i].y - (m_particleList[i].velocity*time*0.001f);
		
	}
	switch (m_currentAnimation)
	{
	case 0:
	{
		
		break;
	}
	case 1:
	{
		//////////Rising Up
		for (size_t i = 0; i < m_maxParticles; i++)
		{
			if (m_particleList[i].active)
			{
				m_particleList[i].y += time;
			}
		}
		break;
	}
	case 2:
	{
		///////Falling down
		for (size_t i = 0; i < m_maxParticles; i++)
		{
			if (m_particleList[i].active)
			{
				m_particleList[i].y-= time;
			}
		}
		break;
	}
	case 3:
	{
		///////Explosive
		for (size_t i = 0; i < m_maxParticles; i++)
		{
			if (m_particleList[i].active)
			{
				if (change)
					m_particleList[i].x += time;
				else if (!change)
					m_particleList[i].z += time;
				m_particleList[i].y += time;
				change = !change;
			}
		}
		break;
	}
	}
	if (runTime >= 4.0f)
	{
		//m_media.PlaySFX(EXPLODE);
		m_playEffect = false;
		endofParticles = true;
	}
}

void ParticleSystem::KillParticles()
{
	for (size_t i = 0; i < m_maxParticles; i++)
	{
		if (m_particleList[i].active && ((m_particleList[i].y < -1.0f) || (m_particleList[i].y > 4.0f)))
		{
			m_particleList[i].active = false;
			m_currentCount--;
			for (size_t j = i; j < m_maxParticles - 1; j++)
			{
				m_particleList[j].x = m_particleList[j + 1].x;
				m_particleList[j].y = m_particleList[j + 1].y;
				m_particleList[j].z = m_particleList[j + 1].z;
				m_particleList[j].r = m_particleList[j + 1].r;
				m_particleList[j].g = m_particleList[j + 1].g;
				m_particleList[j].b = m_particleList[j + 1].b;
				m_particleList[j].a = m_particleList[j+1].a;
				m_particleList[j].velocity = m_particleList[j + 1].velocity;
				m_particleList[j].active = m_particleList[j + 1].active;
			}
		}
	}
}

bool ParticleSystem::UpdateBuffers(ID3D11DeviceContext * context)
{
	D3D11_MAPPED_SUBRESOURCE map;
	VertexType* vertices;
	memset(m_vertices, 0, (sizeof(VertexType)*m_vertexCount));
	int index = 0;
	for (size_t i = 0; i < m_currentCount; i++)
	{
		////Lower left
		m_vertices[index].position = XMFLOAT3(m_particleList[i].x - m_size, m_particleList[i].y - m_size, m_particleList[i].z);
		m_vertices[index].texture = XMFLOAT2(0.0f, 1.0f);
		m_vertices[index].color = XMFLOAT4(m_particleList[i].r, m_particleList[i].g, m_particleList[i].b, m_particleList[i].a);
		
		index++;
		////Upper left
		m_vertices[index].position = XMFLOAT3(m_particleList[i].x - m_size, m_particleList[i].y + m_size, m_particleList[i].z);
		m_vertices[index].texture = XMFLOAT2(0.0f, 0.0f);
		m_vertices[index].color = XMFLOAT4(m_particleList[i].r, m_particleList[i].g, m_particleList[i].b, m_particleList[i].a);
		
		index++;
		////Lower right
		m_vertices[index].position = XMFLOAT3(m_particleList[i].x + m_size, m_particleList[i].y - m_size, m_particleList[i].z);
		m_vertices[index].texture = XMFLOAT2(1.0f, 1.0f);
		m_vertices[index].color = XMFLOAT4(m_particleList[i].r, m_particleList[i].g, m_particleList[i].b, m_particleList[i].a);
	
		index++;
		////Lower right
		m_vertices[index].position = XMFLOAT3(m_particleList[i].x + m_size, m_particleList[i].y - m_size, m_particleList[i].z);
		m_vertices[index].texture = XMFLOAT2(1.0f, 1.0f);
		m_vertices[index].color = XMFLOAT4(m_particleList[i].r, m_particleList[i].g, m_particleList[i].b, m_particleList[i].a);
		
		index++;
		////Upper left
		m_vertices[index].position = XMFLOAT3(m_particleList[i].x - m_size, m_particleList[i].y + m_size, m_particleList[i].z);
		m_vertices[index].texture = XMFLOAT2(0.0f, 0.0f);
		m_vertices[index].color = XMFLOAT4(m_particleList[i].r, m_particleList[i].g, m_particleList[i].b, m_particleList[i].a);
	
		index++;
		////Upper right
		m_vertices[index].position = XMFLOAT3(m_particleList[i].x + m_size, m_particleList[i].y + m_size, m_particleList[i].z);
		m_vertices[index].texture = XMFLOAT2(1.0f, 0.0f);
		m_vertices[index].color = XMFLOAT4(m_particleList[i].r, m_particleList[i].g, m_particleList[i].b, m_particleList[i].a);
		
		index++;
	}
	HRESULT hr;
	hr = context->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	if (FAILED(hr))
		return false;

	vertices = (VertexType*)map.pData;
	memcpy(vertices, (void*)m_vertices, (sizeof(VertexType)*m_vertexCount));

	context->Unmap(m_vertexBuffer, 0);
	return true;


}

void ParticleSystem::RenderBuffers(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}
