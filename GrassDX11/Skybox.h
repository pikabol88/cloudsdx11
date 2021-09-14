#pragma once 
#ifndef  __SKYBOX_H__
#define __SKYBOX_H__ 

#include <d3d11.h>
#include <d3dx11effect.h>
#include <SDKmesh.h>
#include "PhysMath.h"



class Skybox {
public:

	
	Skybox(ID3D11Device* a_pD3DDevice, ID3D11DeviceContext* a_pD3DDeviceCtx, ID3DX11Effect* a_pEffect);
	~Skybox();

public:
	void CreateInputLayout(void);

	void Render(float4x4& a_mViewProj);



public:

	ID3D11Device* m_pD3DDevice;
	ID3DX11Effect* m_pEffect;
	ID3D11DeviceContext* m_pD3DDeviceCtx;


	ID3D11InputLayout* m_pSkyVertexLayout = NULL;
	CDXUTSDKMesh                          m_MeshSkybox;
	ID3DX11EffectShaderResourceVariable* m_pSkyBoxESRV = NULL;
	ID3DX11EffectMatrixVariable* m_pSkyViewProjEMV;
	ID3DX11EffectTechnique* m_pSkyboxTechnique = NULL;
	ID3DX11EffectPass* m_pSkyboxPass = NULL;
};


#endif // ! __SKYBOX_H__
