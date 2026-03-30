////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
protected:
	struct VertexType
	{
		XMFLOAT3 position;
	    XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	virtual bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext*);

	virtual int GetIndexCount();
	virtual ID3D11ShaderResourceView* GetTexture();

	virtual bool LoadModel(const WCHAR*);
	virtual void ReleaseModel();

	virtual int GetInstanceCount();

protected:
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext*);

	virtual bool LoadTexture(ID3D11Device*, const WCHAR*);
	virtual void ReleaseTexture();

	virtual bool ReadFileCounts(const WCHAR*);
	virtual bool LoadDataStructures(const WCHAR*, int, int, int, int);

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount, m_textureCount, m_normalCount, m_faceCount;
	TextureClass* m_Texture;

	ModelType* m_model;

	int m_instanceCount;
	ID3D11Buffer* m_instanceBuffer;
};

#endif