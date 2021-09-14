#pragma once
#include "DXUT.h"
#include <thread>
#include "SnowParticleTypes.h"
#include "AxesFanFlow.h"
#include "FlowManager.h"

using namespace DirectX;

class ParticleShader;

class SnowParticleSystem
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT4 color;
	};

public:
	SnowParticleSystem(float fGrassRadius);
	SnowParticleSystem(const SnowParticleSystem&);
	~SnowParticleSystem();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const WCHAR*, int);
	void SetParticleShader(ParticleShader* ps) { m_pParticleShader = ps; }
	//void SetFlowManager(FlowManager* manager) { m_pFlowManager = manager; }
	bool Frame(float, ID3D11DeviceContext*);
	void Render(ID3D11DeviceContext*);

	void FillConstantDataBuffer(ID3D11DeviceContext* deviceContext, ID3D11Buffer* inputBuffer);
	void UpdatePosition(InstanceType* dataView);

	//ID3D11UnorderedAccessView* GetUAV() { return m_uav; }
	ID3D11ShaderResourceView* GetTexture() { return m_TextureView; }
	int GetIndexCount() { return m_indexCount; }
	int GetVertexCount() { return m_vertexCount; }
	int GetInstaceCount() { return m_instanceCount; }
	int GetCurrentParticleCount() { return m_currentParticleCount; }
	int GetParticlesPerSecond() { return m_particlePerSecond; }
	float** GetSnowCover() { return m_snowCover; }
	void SetParticlesPerSecond(int value) { m_particlePerSecond = value; }
	void ToggleSnowCover() { isSnowCoverActive = !isSnowCoverActive; }
	void ToggleCloudMovement() { isCloudMovementActive = !isCloudMovementActive; }
	void SaveState() { 
		memcpy(m_particleListSaved, m_particleList, m_maxParticles * sizeof(ParticleType)); 
		memcpy(m_instanceSaved, m_instance, m_maxParticles * sizeof(InstanceType));
		m_currentParticleCountSaved = m_currentParticleCount;
	};
	void RestoreState() { 
		memcpy(m_particleList, m_particleListSaved, m_maxParticles * sizeof(ParticleType));
		memcpy(m_instance, m_instanceSaved, m_maxParticles * sizeof(InstanceType));
		m_currentParticleCount = m_currentParticleCountSaved;
	}

	/*TORNADO*/
	XMFLOAT3 GetTornadoPos() { return m_tornadoPos; }
	void ToggleTornado() { _tornadoActive = !_tornadoActive; }
	bool IsTornadoActive() { return _tornadoActive; }
	void MoveTornadoForward() { m_tornadoPos.z += 0.3f; m_deltaTorandoPos.z += 0.3f; _manualTornadoContral = true; }
	void MoveTornadoBack() { m_tornadoPos.z -= 0.3f; m_deltaTorandoPos.z -= 0.3f; _manualTornadoContral = true;}
	void MoveTornadoLeft() { m_tornadoPos.x -= 0.3f; m_deltaTorandoPos.x -= 0.3f; _manualTornadoContral = true;}
	void MoveTornadoRight() { m_tornadoPos.x += 0.3f; m_deltaTorandoPos.x += 0.3f; _manualTornadoContral = true;}
private:
	// Initialize
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const WCHAR*);
	bool InitializeParticleSystem(int);
	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext*);
	void CalculateInstancePositions(int, int);
	void UpdateCloudPosition();
	XMUINT2 GetIntCoord(XMFLOAT2 pos);
	void SnowNeighbors(int x, int y, int num, float addMax, float thres);

	// Particle methods
	void EmitParticles(float);
	void UpdateParticles(float);
	void SpawnParticle();

	// Render & Update
	bool UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);
private:
	ParticleShader* m_pParticleShader;
	//FlowManager* m_pFlowManager;
	XMFLOAT3 m_cloudPos{ 0.f, 80.f, 0.f };
	XMFLOAT3 m_tornadoPos{ 0.f, 0.f, 0.f };
	XMFLOAT3 m_deltaTorandoPos{ 0.f, 0.f, 0.f };;
	bool _tornadoActive = false;
	bool _manualTornadoContral = false;
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVeclocity, m_particleVelocityVariation;
	float m_particleSize, m_particlePerSecond;
	int m_maxParticles;

	int m_currentParticleCount;
	int m_currentParticleCountSaved;
	float m_accumulatedTime;

	ID3D11UnorderedAccessView* m_uav;
	ID3D11Texture2D* m_uavTex;

	ID3D11Resource* m_Texture;
	ID3D11ShaderResourceView* m_TextureView;

	ParticleType* m_particleList;
	ParticleType* m_particleListSaved;

	int m_vertexCount, m_indexCount, m_instanceCount;
	InstanceType* m_instance;
	InstanceType* m_instanceSaved;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer, * m_instanceBuffer;
	long _reachGround = 1;
	float _fTerrRadius = 0.f;
	float** m_snowCover = nullptr;
	int _snowCoverTextureSize = 1024;
	bool isSnowCoverActive = false;
	bool isCloudMovementActive = false;
	long m_frame = 0;

	std::vector<std::thread> m_threads;
};