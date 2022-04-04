#include "Skybox.h"
#include "StateManager.h"

Skybox::Skybox(ID3D11Device* a_pD3DDevice, ID3D11DeviceContext* a_pD3DDeviceCtx, ID3DX11Effect* a_pEffect) {
	m_pD3DDevice = a_pD3DDevice;
	m_pD3DDeviceCtx = a_pD3DDeviceCtx;
	m_pEffect = a_pEffect;


	m_pSkyBoxESRV = a_pEffect->GetVariableByName("g_txSkyBox")->AsShaderResource();
	m_pSkyboxTechnique = a_pEffect->GetTechniqueByName("RenderSkyBox");
	m_pSkyViewProjEMV = a_pEffect->GetVariableByName("g_mViewProj")->AsMatrix();
}


Skybox::~Skybox() {
	SAFE_RELEASE(m_pSkyVertexLayout);
	m_MeshSkybox.Destroy();
}

#include <iostream>
void Skybox::CreateLayout(void) {
	const D3D11_INPUT_ELEMENT_DESC SkyBoxLayout[] =
	{
	   { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	   { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	   { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	int iNumElements = sizeof(SkyBoxLayout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	D3DX11_PASS_DESC PassDesc;
	ID3DX11EffectPass* pPass;
	m_pSkyboxPass = m_pSkyboxTechnique->GetPassByIndex(0);
	m_pSkyboxPass->GetDesc(&PassDesc);
	m_pD3DDevice->CreateInputLayout(SkyBoxLayout, iNumElements, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &m_pSkyVertexLayout);


	m_MeshSkybox.Create(m_pD3DDevice, L"resources\\skysphere.sdkmesh");
	m_pSkyBoxESRV->SetResource(nullptr);

};

void Skybox::Render(float4x4& a_mViewProj) {
	m_pD3DDeviceCtx->IASetInputLayout(m_pSkyVertexLayout);
	m_pSkyViewProjEMV->SetMatrix((float*)&a_mViewProj);

	if (GetGlobalStateManager().UseWireframe()) {
		GetGlobalStateManager().SetRasterizerState("EnableMSAACulling_Wire");
	}
	else {
		GetGlobalStateManager().SetRasterizerState("EnableMSAACulling");
	}


	m_pD3DDeviceCtx->IASetInputLayout(m_pSkyVertexLayout);
	m_pSkyboxPass->Apply(0, m_pD3DDeviceCtx);
	m_MeshSkybox.Render(m_pD3DDeviceCtx, 0);
	m_pSkyBoxESRV->SetResource(m_MeshSkybox.GetMaterial(0)->pDiffuseRV11);
};




