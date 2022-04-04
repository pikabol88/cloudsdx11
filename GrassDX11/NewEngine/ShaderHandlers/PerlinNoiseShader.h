#pragma once

#include "../Engine/Graphics/Shader.h"

class PerlinNoiseShader : public Shader {
public:
	PerlinNoiseShader(Renderer& renderer);
	~PerlinNoiseShader();
};