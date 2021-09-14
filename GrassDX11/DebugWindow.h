#pragma once

#include "includes.h"

class DebugWindow
{
private:
   struct VertexType
   {
      XMFLOAT3 position;
      XMFLOAT2 texture;
   };

public:
   DebugWindow  (ID3D11Device* device, int screenWidth, int screenHeight, ID3D11ShaderResourceView* pSRV, float scale = 1.0);
   ~DebugWindow (void);

   bool Render     (ID3D11DeviceContext* deviceContext, int positionX, int positionY);

   int  GetIndexCount  (void);
   void SetOrthoMtx    (float4x4& a_mViewProj);
   void SetWorldMtx    (float4x4& a_mWorld);
   void ToggleRender   (void) { m_bNeedRender = ! m_bNeedRender; }
   void ToggleSlice    (void);

private:
   bool InitializeBuffers (ID3D11Device* ctx);
   void ShutdownBuffers   (void);
   bool UpdateBuffers     (ID3D11DeviceContext* deviceContext, int positionX, int positionY);
   void RenderBuffers     (ID3D11DeviceContext* deviceContext);

   void CreateInputLayout (void);

private:
   ID3D11Device                        *m_pDevice;
   ID3D11DeviceContext                 *m_pDeviceCtx;
   ID3DX11EffectMatrixVariable         *m_pOrthoEMV;
   ID3DX11EffectMatrixVariable         *m_pTransformEMV;
   ID3DX11EffectShaderResourceVariable *m_pTexESRV;
   ID3DX11EffectScalarVariable         *m_pArraySlice;
   int                                  m_iCurSlice = 0;

   ID3D11InputLayout        *m_pInputLayout;

   ID3DX11Effect     *m_pEffect;
   ID3DX11EffectPass *m_pPass;
   ID3D11Buffer      *m_vertexBuffer, *m_indexBuffer;
   
   int m_vertexCount, m_indexCount;
   int m_screenWidth, m_screenHeight;
   int m_bitmapWidth, m_bitmapHeight;
   int m_previousPosX, m_previousPosY;

   float m_fScale;
 
   bool m_bNeedRender = false;

   ID3DX11EffectScalarVariable* m_fScaleESV;
};
