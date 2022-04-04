#include "MeshClass.h"
#include "../Dev/Helpers.h"

bool MeshCreator::createBuffers(MeshData& meshData) {
	HRESULT result;

	// Make sure there are vertices to create buffers from
	if (meshData.getVertices().empty())	{
		Log::error("MeshData contained no vertices.");
		return false;
	}

	// Create vertex buffer desc
	CD3D11_BUFFER_DESC vertexBufferDesc = CD3D11_BUFFER_DESC(
		sizeof(meshData.getVertices()[0]) * this->vertexCount, D3D11_BIND_VERTEX_BUFFER
	);

	// Create sub resource data containing pointer to vertex data
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &meshData.getVertices()[0];
	vertexData.SysMemPitch = 0;			// Distance in bytes from one line to the next one (2D/3D textures)
	vertexData.SysMemSlicePitch = 0;	// Distance in bytes from one depth level to the next one (3D textures)

	// Create vertex buffer
	result = renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &this->vertexBuffer);

	if (FAILED(result))	{
		Log::error("Could not create vertex buffer.");

		return false;
	}

	// Create index buffer desc
	CD3D11_BUFFER_DESC indexBufferDesc = CD3D11_BUFFER_DESC(sizeof(meshData.getIndices()[0]) * this->indexCount, D3D11_BIND_INDEX_BUFFER);

	// Create sub resource data containing pointer to index data
	D3D11_SUBRESOURCE_DATA indexData = { 0 };
	indexData.pSysMem = &meshData.getIndices()[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer
	result = renderer.getDevice()->CreateBuffer(&indexBufferDesc, &indexData, &this->indexBuffer);
	if (FAILED(result))	{
		Log::error("Could not create index buffer.");

		return false;
	}

	return true;
}

void MeshCreator::prepareToDraw(ID3D11DeviceContext*& deviceContext) {
	// Set topology
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set vertex buffer
	deviceContext->IASetVertexBuffers(
		0, 1,
		&this->vertexBuffer,
		&this->vertexStride,
		&this->vertexOffset
	);

	// Set index buffer
	deviceContext->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

}

const Renderer& MeshCreator::getRenderer() const {
	return this->renderer;
}

ID3D11Buffer*& MeshCreator::getVertexBuffer() {
	return this->vertexBuffer;
}

ID3D11Buffer*& MeshCreator::getIndexBuffer() {
	return this->indexBuffer;
}

const unsigned int& MeshCreator::getVertexCount() const {
	return this->vertexCount;
}

const unsigned int& MeshCreator::getIndexCount() const {
	return this->indexCount;
}

const UINT& MeshCreator::getVertexStride() const {
	return this->vertexStride;
}

const UINT& MeshCreator::getVertexOffset() const {
	return this->vertexOffset;
}

MeshCreator::MeshCreator(Renderer& renderer, MeshData& meshData): renderer(renderer), vertexBuffer(nullptr), vertexCount(meshData.getVertices().size()), 
	indexCount(meshData.getIndices().size()) {
	// Create vertex buffers and index buffers
	this->createBuffers(meshData);
	
	// Initialize world matrix to identity matrix
	this->setWorldMatrix(XMMatrixIdentity());
}

MeshCreator::~MeshCreator() {
	S_RELEASE(this->indexBuffer);
	S_RELEASE(this->vertexBuffer);
}

void MeshCreator::setWorldMatrix(XMMATRIX newWorldMatrix) {
	this->worldMatrix = newWorldMatrix;
}

void MeshCreator::draw() {
	ID3D11DeviceContext* deviceContext = renderer.getDeviceContext();

	// Set buffers
	this->prepareToDraw(deviceContext);

	// Draw
	deviceContext->DrawIndexed(this->indexCount, 0, 0);
}

const XMMATRIX& MeshCreator::getWorldMatrix() const {
	return this->worldMatrix;
}
