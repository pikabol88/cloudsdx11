#pragma once

#include "MeshClass.h"

class MeshInstancer : public MeshCreator
{
private:
public:
	MeshInstancer(Renderer& renderer, MeshData& meshData);
	~MeshInstancer();

	void draw(unsigned int numInstances);
};