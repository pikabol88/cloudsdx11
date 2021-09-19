#pragma once
//#pragma warning(disable:1563)

#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTsettingsdlg.h"
#include "DXUTcamera.h"
#include "SDKmisc.h"
#include "SDKmesh.h"
#include "DXUTRes.h"

#include <d3dx11effect.h>

#include "mesh.h"
#include "plane.h"
#include "Terrain.h"
#include "GrassFieldManager.h"
#include "AxesFanFlow.h"
#include "DebugWindow.h"
#include "ParticleShader.h"
#include "SnowParticleSystem.h"
#include "Skybox.h"

#ifdef DEBUG
#pragma comment(lib, "Effects11d.lib")
#else
#pragma comment(lib, "Effects11.lib")
#endif
#pragma comment(lib, "DirectXTex.lib")

#define MAX_NUM_MESHES 1

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
int g_windowWidth = 1920;
int g_windowHeight = 1080;
//int g_windowWidth = 1600;
//int g_windowHeight = 900;


//
struct RototCamFixController {
   bool isFixed = false;
   XMVECTOR delta;
};

RototCamFixController g_RotCamController;
//


// Effect handles
ID3DX11EffectScalarVariable         *g_pTerrTile = NULL;

ID3DX11EffectScalarVariable         *g_pGrassDiffuse = NULL;
GrassFieldState                      g_GrassInitState;
GrassFieldManager                   *g_pGrassField;
Mesh                                *g_pMeshes[MAX_NUM_MESHES];

// Output textures to screen
DebugWindow                         *g_dbgWin;

// Snow Particle System
int g_totalParticles = 250000;
ParticleShader* g_ParticleShader = nullptr;
SnowParticleSystem* g_ParticleSystem = nullptr;
Skybox* g_pSkybox;


XMFLOAT3                            g_MeshVels[MAX_NUM_MESHES];

/* Grass global variables */
float                               g_fGrassLodBias = 0.0f;//0.02f;//0.35f;//0.1f;
float                               g_fGrassSubScatterGamma = 0.95f;
float                               g_fGrassAmbient = 0.15f;//0.23f;//0.05f
float                               g_fGrassDiffuse = 10.0f;

//phys
float                               g_fMass = 1.0;//0.2450f; //0.230f;
float                               g_fHardness = 1.0f;
float                               g_fWindStrength = 0.35f;//0.1616f;
float                               g_fWindStrengthDefault = 1.0f;
float                               g_fWindBias = 0.4370f;
float                               g_fWindScale = 4.96f;

float                               g_fMaxFlowStrength = 0.0562;
float                               g_fFanRadius = 20;
float                               g_fDeltaSlices = 0.005;
float                               g_fAngleSpeed = 100;
float                               g_fShift = 0.005;
XMFLOAT3                            g_vDir = XMFLOAT3(0.0f, -1.0f, 0.0f);
//phys


float                               g_fWindTexSpeed = 2.5f;//3.78f;
float                               g_fWindTexTile = 4.f;//4.f;//5.2f;
float                               g_fCameraSpeed = 30.0f;
float                               g_fTime = 0.0f;
float                               g_fHeightScale = 40;//120;//0;//40.0f;
float                               g_fQuality = 1.0f;
XMFLOAT4                            g_vFogColor = XMFLOAT4(0.2f, 0.3f, 0.25f, 1.0f);
XMFLOAT3                            g_vTerrRGB = XMFLOAT3(0.5f, 0.5f, 0.0f);
XMFLOAT4                            g_vGrassSpecular = XMFLOAT4(0.04f, 0.27f, 0.00f, 1.0f);

float                               g_fTerrTile = 45.0f;


float                               g_fCameraMeshDist = 13.0f;
float                               g_fCameraMeshDistMin;
float                               g_fCameraMeshDistMax;
float                               g_fCameraHeight = 5.0f;
float                               g_fCameraHeightMax;
float                               g_fCameraHeightMin;
XMFLOAT3                            g_vCameraEyeStart(69.79, 20.20, -75.06);
XMFLOAT3                            g_vCameraAtStart(70.33, 19.97, -75.87);


ID3D11Texture2D*                    g_pRenderTarget = NULL;
ID3D11RenderTargetView*             g_pRTRV = NULL;
ID3D11Texture2D*                    g_pDSTarget = NULL;
ID3D11DepthStencilView*             g_pDSRV = NULL;
ID3D11BlendState* g_alphaDisableBlendingState;
ID3D11BlendState* g_alphaEnableBlendingState;



UINT                                g_MSAASampleCount = 4;
UINT                                g_BackBufferWidth;
UINT                                g_BackBufferHeight;

//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
enum IDC_HUD
{
   IDC_STATIC = -1,

   IDC_CHANGEDEVICE,

   IDC_GRASS_WIND_LABEL,
   IDC_GRASS_WIND_FORCE_SLYDER,
   
   IDC_GRASS_MAX_FLOW_STRENGTH_LABEL,
   IDC_GRASS_MAX_FLOW_STRENGTH_SLYDER,
   
   IDC_FAN_RADIUS_LABEL,
   IDC_FAN_RADIUS_SLYDER,

   IDC_DELTA_SLICES_LABEL,
   IDC_DELTA_SLICES_SLYDER,

   IDC_CAM_SPEED_SCALE_LABEL,
   IDC_CAM_SPEED_SCALE_SLYDER,

   IDC_FIX_CAMERA,

   IDC_GRASS_SHIFT_LABEL,
   IDC_GRASS_SHIFT_SLYDER,

   IDC_TERR_RGB_LABEL,
   IDC_TERR_R_SLYDER,
   IDC_TERR_G_SLYDER,
   IDC_TERR_B_SLYDER,

   IDC_FLOW_DIR_LABEL,
   IDC_FLOW_DIR_X_SLYDER,
   IDC_FLOW_DIR_Y_SLYDER,
   IDC_FLOW_DIR_Z_SLYDER,

   IDC_FAN_ANGLE_SPEED_LABEL,
   IDC_FAN_ANGLE_SPEED_SLYDER,

   IDC_TOGGLE_WIREFRAME,
   IDC_TOGGLE_RENDERING_GRASS,
   IDC_TOGGLE_RENDERING_DBG_WIN,
   IDC_TOGGLE_DBG_WIN_SLICE,

   IDC_SAMPLE_COUNT
};
                      
//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc     (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
void CALLBACK    OnKeyboard  (UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
void CALLBACK    OnGUIEvent  (UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext);
void CALLBACK    OnFrameMove (double fTime, float fElapsedTime, void* pUserContext);

bool CALLBACK ModifyDeviceSettings     (DXUTDeviceSettings* pDeviceSettings, void* pUserContext);

bool CALLBACK IsD3D11DeviceAcceptable (const CD3D11EnumAdapterInfo* AdapterInfo, UINT Output,
                                       const CD3D11EnumDeviceInfo* DeviceInfo,
                                       DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext);

HRESULT CALLBACK OnD3D11CreateDevice (ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
HRESULT CALLBACK OnD3D11ResizedSwapChain (ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
                                const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

void CALLBACK OnD3D11ReleasingSwapChain (void* pUserContext);
void CALLBACK OnD3D11DestroyDevice      (void* pUserContext);
void CALLBACK OnD3D11FrameRender        (ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
                                         float fElapsedTime, void* pUserContext );

void TurnOnAlphaBlending();
void TurnOffAlphaBlending();

void InitApp    (void);
void RenderText (void);