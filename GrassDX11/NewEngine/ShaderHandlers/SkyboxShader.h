#pragma once

#include "../Engine/Graphics/Shader.h"

class SkyboxShader : public Shader {
public:
	SkyboxShader(Renderer& renderer);
	~SkyboxShader();
};