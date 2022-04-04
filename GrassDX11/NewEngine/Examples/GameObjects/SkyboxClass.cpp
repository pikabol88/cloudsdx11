#include "SkyboxClass.h"
#include "../../Engine/Application/Time.h"
#include "..\..\SettingsController.h"
#include "..\..\..\StateManager.h"

SkyboxClass::SkyboxClass(Renderer& renderer) : meshData(DefaultMesh::CUBE, 0, 0, true), mesh(renderer, this->meshData),
	shader(renderer), constantBuffer(renderer, sizeof(SkyboxBuffer)),
	renderer(renderer), skyCubeMap(renderer), 
	preethamCreatorShader(renderer, "CompiledShaders/PreethamSkyCreator_Comp.cso", CUBE_FACE_WIDTH / 16, CUBE_FACE_HEIGHT / 16, 6 / 2){
	
	// Make the mesh big enough to not clip into another mesh
	this->mesh.setWorldMatrix(XMMatrixScaling(1000.0f, 1000.0f, 1000.0f));
	// Create cube map as render texture
	this->skyCubeMap.createAsRenderTexture(CUBE_FACE_WIDTH, CUBE_FACE_HEIGHT);
	// Preetham creator shader
	this->preethamCreatorShader.addRenderTexture(this->skyCubeMap);
	this->preethamCreatorShader.addConstantBuffer(this->constantBuffer);

	// Set constants in shader buffer struct
	this->sb.faceWidth = CUBE_FACE_WIDTH;
	this->sb.faceHeight = CUBE_FACE_HEIGHT;

}

SkyboxClass::~SkyboxClass() {}

void SkyboxClass::draw() {

	if (GetGlobalStateManager().UseWireframe()) {
		GetGlobalStateManager().SetRasterizerState("EnableMSAA_Wire");
	}
	else {
		GetGlobalStateManager().SetRasterizerState("EnableMSAA");
	}

	this->sunDir = XMFLOAT3(0.0f, cos(SettingsController::time), sin(SettingsController::time));

	// Update and set shader buffer
	this->sb.sunDir = this->sunDir;
	this->sb.turbidity = SettingsController::turbidity;
	this->constantBuffer.update(&this->sb);

	this->preethamCreatorShader.run();

	//// Set sky box to use in pixel shader
	this->skyCubeMap.setPS();

	//// Update shader
	this->shader.update(renderer, this->mesh.getWorldMatrix());

	//// Set shader to render mesh with
	this->shader.set();

	//// Render mesh
	this->mesh.draw();
}

CubeMap& SkyboxClass::getCubeMap()
{
	return this->skyCubeMap;
}

const XMMATRIX& SkyboxClass::getWorldMatrix()const {
	return this->mesh.getWorldMatrix();
}

const XMFLOAT3& SkyboxClass::getSunDir() const
{
	return this->sunDir;
}



