#pragma once

#include "../Engine/Graphics/Shader.h"

class TerrainShaderClass : public Shader {
public:
	TerrainShaderClass(Renderer& renderer);
	~TerrainShaderClass();
};