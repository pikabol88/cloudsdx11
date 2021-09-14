#pragma once 
#include <d3d11.h>
#include <d3dx11effect.h>
#include <SDKmesh.h>

//test

/* sky */
ID3D11InputLayout* g_pSkyVertexLayout = NULL;
CDXUTSDKMesh                          g_MeshSkybox;
ID3DX11EffectShaderResourceVariable* g_pSkyBoxESRV = NULL;
ID3DX11EffectMatrixVariable* g_pSkyViewProjEMV;
ID3DX11EffectTechnique* g_pSkyboxTechnique = NULL;
ID3DX11EffectPass* g_pSkyboxPass = NULL;
