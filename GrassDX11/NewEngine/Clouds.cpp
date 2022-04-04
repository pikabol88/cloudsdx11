#include "pch.h"
#include "Clouds.h"
#include "SettingsController.h"
#include "..\StateManager.h"


Clouds::Clouds(Renderer& renderer): skybox(nullptr), meshData(DefaultMesh::SKY_PLANE, 100, 100, false), mesh(renderer, this->meshData),
shader(renderer), constantBuffer(renderer, sizeof(CloudsBuffer)),renderer(renderer),
perturbTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R16G16B16A16_UNORM, TextureEdgeSampling::REPEAT),
cloudTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R8G8B8A8_UNORM, TextureEdgeSampling::REPEAT) {
	
	//Load dds clouds textures
	this->cloudTexture.createFromFile("Resources/Textures/cloud001.dds");
	this->perturbTexture.createFromFile("Resources/Textures/perturb001.dds");

	this->constantBuffer.setPS();

	cb.brightness = 0.5f;
	cb.scale = 0.3f;
	cb.padding = 0.0f;
	cb.translation = 0.0f;
}

Clouds::~Clouds(){}

void Clouds::draw() {

	if (GetGlobalStateManager().UseWireframe()) {
		GetGlobalStateManager().SetRasterizerState("EnableMSAA_Wire");
	}
	else {
		GetGlobalStateManager().SetRasterizerState("EnableMSAA");
	}

	this->constantBuffer.setPS();

	cb.translation += SettingsController::translationSpeed/10000;

	if (cb.translation > 1.0f)
	{
		cb.translation -= 1.0f;
	}

	cb.brightness = SettingsController::brightness;
	cb.scale = SettingsController::scale;

	this->constantBuffer.update(&this->cb);
	this->cloudTexture.setPS(0);
	this->perturbTexture.setPS(1);

	XMMATRIX newMatrix = this->skybox->getWorldMatrix();
	

	this->shader.update(renderer, this->mesh.getWorldMatrix(), true);
	this->shader.set();
	this->mesh.draw();
}

void Clouds::setSkybox(SkyboxClass& skybox) {
	this->skybox = &skybox;
}
