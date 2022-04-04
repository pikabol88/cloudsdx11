#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <vector>
#include <string>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <d3dx11effect.h>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "MeshAssimp.h"
#include "TextureLoader.h"


using namespace DirectX;

class ModelLoader
{	
public:
	ModelLoader();
	~ModelLoader();

	bool Load(HWND hwnd, ID3D11Device* dev, ID3D11DeviceContext* devcon, std::string filename);
	void Draw(ID3D11DeviceContext* devcon, ID3DX11EffectPass* pass, ID3DX11EffectShaderResourceVariable* texESRV);

	void Close();
private:
	ID3D11Device           *dev;
	ID3D11DeviceContext    *devcon;
	std::vector<AssModel::MeshAssimp> meshes;
	std::string             directory;
	std::vector<AssModel::Texture>         textures_loaded;
	HWND                    hwnd;

	void                      processNode          (aiNode* node, const aiScene* scene);
	AssModel::MeshAssimp                processMesh          (aiMesh* mesh, const aiScene* scene);
	std::vector<AssModel::Texture>           loadMaterialTextures (aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
   std::string               determineTextureType (const aiScene* scene, aiMaterial* mat);
	int                       getTextureIndex      (aiString* str);
	ID3D11ShaderResourceView* getTextureFromModel  (const aiScene* scene, int textureindex);
};

#endif // !MODEL_LOADER_H

