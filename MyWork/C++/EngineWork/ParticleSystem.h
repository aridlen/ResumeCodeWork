#pragma once
#define TRANSPARENCY 0.02F

enum ParticleEffect
{
	INPLACE,RISING,FALLING,EXPLOSIVE,BLOOD,SPARK
};
struct ParticleProperties
{
	float size;
	float devX,devY,devZ;
	WCHAR* file;
	ParticleEffect m_effect;
	ParticleProperties()
	{

	}
	ParticleProperties(float Newsize,float x, float y, float z, WCHAR* png, ParticleEffect effect)
	{
		size = Newsize;
		devX = x;
		devY = y;
		devZ = z;
		file = png;
		m_effect = effect;
	}
};
class ParticleSystem
{
	struct ParticleType
	{
		float x, y, z;
		float r, g, b,a;
		
		float velocity;
		bool active;
	};
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT4 color;
	
	};
	//Sounds m_media;
public:
	ParticleSystem();
	ParticleSystem(const ParticleSystem&);
	~ParticleSystem();
	bool Initialize(ID3D11Device* device, ParticleProperties prop);
	void Shutdown();
	bool Frame(float data, ID3D11DeviceContext* context, ResourceManager* res);
	void Render(ID3D11DeviceContext* context);
	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();
	void TogglePlayEffect() { m_playEffect = !m_playEffect; }
	bool GetPlay() { return m_playEffect; }
	ParticleEffect GetCurrentEffect() { return m_currentAnimation; }
	bool GetParticleRunTime() { return endofParticles; }
private:
	///////////////
	bool change = false;
	float m_deviationX, m_deviationY, m_deviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_size, m_particlesPerSecond;
	int m_maxParticles;
	int m_currentCount;
	float m_TotalTime;
	bool endofParticles;
	float runTime;
	bool m_playEffect;
	float fadeOut;
	
	//////////
	ParticleEffect m_currentAnimation;

	//////////
	ID3D11ShaderResourceView* m_texture;
	ParticleType* m_particleList;
	int m_vertexCount, m_indexCount;
	VertexType* m_vertices;
	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer;
	///////////////

	void ReleaseTexture();
	bool InitializeParticle(float size,float devX,float devY,float devZ);
	void ShutdownParticle();
	bool InitializeBuffer(ID3D11Device* device, ParticleEffect typeAnimation);
	void ShutdownBuffers();

	void EmitParticles(float time);
	void EmitSparkParticles(float time);
	void EmitBloodParticles(float time);
	void UpdateParticles(float time, ResourceManager* res);
	void KillParticles();
	bool UpdateBuffers(ID3D11DeviceContext* context);
	void RenderBuffers(ID3D11DeviceContext* context);


};

