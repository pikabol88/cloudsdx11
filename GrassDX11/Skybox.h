#ifndef SKYBOX_H
#define SKYBOX_H

#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTsettingsdlg.h"
#include "DXUTcamera.h"
#include "SDKmisc.h"
#include "SDKmesh.h"
#include "DXUTRes.h"

#include <d3dx11effect.h>
#include "PhysMath.h"

///* sky */
//ID3D11InputLayout* g_pSkyVertexLayout = NULL;
//CDXUTSDKMesh                          g_MeshSkybox;
//ID3DX11EffectShaderResourceVariable* g_pSkyBoxESRV = NULL;
//ID3DX11EffectMatrixVariable* g_pSkyViewProjEMV;
//ID3DX11EffectTechnique* g_pSkyboxTechnique = NULL;
//ID3DX11EffectPass* g_pSkyboxPass = NULL;

class Skybox {
public:


	Skybox(ID3D11Device* a_pD3DDevice, ID3D11DeviceContext* a_pD3DDeviceCtx, ID3DX11Effect* a_pEffect);
	~Skybox();

public:
	void CreateLayout(void);

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

#endif // !SKYBOX_H
