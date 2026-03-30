#include "TreeModelClass.h"

TreeModelClass::TreeModelClass()
{
}

TreeModelClass::~TreeModelClass()
{
}

bool TreeModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	// 인스턴스 배열을 만듭니다.
	//m_instanceCount = 10;
	m_instanceCount = 51;

	// 인스턴스 배열을 만듭니다.
	InstanceType* instances = new InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	// 데이터로 인스턴스 배열을 로드합니다.
	instances[0].position = XMFLOAT3(0.0f, -8.0f, 0.0f);
	instances[1].position = XMFLOAT3(-10.0f, -8.0f, 3.0f);
	instances[2].position = XMFLOAT3(-20.0f, -8.0f, 0.0f);
	instances[3].position = XMFLOAT3(-31.0f, -8.0f, 3.0f);

	instances[4].position = XMFLOAT3(-44.0f, -8.0f, 0.0f);
	instances[5].position = XMFLOAT3(-58.0f, -8.0f, 3.0f);
	instances[6].position = XMFLOAT3(-71.0f, -8.0f, 0.0f);
	instances[7].position = XMFLOAT3(-86.0f, -8.0f, 3.0f);

	instances[8].position = XMFLOAT3(-10.0f, -8.0f, -25.0f);
	instances[9].position = XMFLOAT3(-10.0f, -8.0f, -22.0f);
	instances[10].position = XMFLOAT3(-20.0f, -8.0f, -25.0f);
	instances[11].position = XMFLOAT3(-31.0f, -8.0f, -22.0f);

	instances[12].position = XMFLOAT3(-44.0f, -8.0f, -25.0f);
	instances[13].position = XMFLOAT3(-58.0f, -8.0f, -22.0f);
	instances[14].position = XMFLOAT3(-71.0f, -8.0f, -25.0f);
	instances[15].position = XMFLOAT3(-86.0f, -8.0f, -22.0f);

	instances[16].position = XMFLOAT3(-101.0f, -8.0f, 0.0f);

	instances[17].position = XMFLOAT3(-110.0f, -8.0f, -3.0f);
	instances[18].position = XMFLOAT3(-112.0f, -8.0f, -14.0f);
	instances[19].position = XMFLOAT3(-110.0f, -8.0f, -26.0f);
	instances[20].position = XMFLOAT3(-109.0f, -8.0f, -39.0f);

	instances[21].position = XMFLOAT3(-106.0f, -8.0f, -50.0f);
	instances[22].position = XMFLOAT3(-90.0f, -8.0f, -49.0f);


	instances[23].position = XMFLOAT3(-89.0f, -8.0f, -34.0f);

	instances[24].position = XMFLOAT3(3.0f, -8.0f, -3.0f);
	instances[25].position = XMFLOAT3(14.0f, -8.0f, -0.0f);
	instances[26].position = XMFLOAT3(24.0f, -8.0f, -3.0f);
	instances[27].position = XMFLOAT3(34.0f, -8.0f, -3.0f);

	instances[28].position = XMFLOAT3(10.0f, -8.0f, -30.0f);
	instances[29].position = XMFLOAT3(14.0f, -8.0f, -25.0f);
	instances[30].position = XMFLOAT3(24.0f, -8.0f, -28.0f);
	instances[31].position = XMFLOAT3(35.0f, -8.0f, -25.0f);
	instances[32].position = XMFLOAT3(48.0f, -8.0f, -25.0f);
	instances[33].position = XMFLOAT3(60.0f, -8.0f, -25.0f);

	instances[34].position = XMFLOAT3(63.0f, -8.0f, -12.0f);
	instances[35].position = XMFLOAT3(63.0f, -8.0f, 2.0f);

	instances[36].position = XMFLOAT3(61.0f, -8.0f, 13.0f);
	instances[37].position = XMFLOAT3(58.0f, -8.0f, 28.0f);

	instances[38].position = XMFLOAT3(48.0f, -8.0f, 28.0f);

	instances[39].position = XMFLOAT3(40.0f, -8.0f, 24.0f);
	instances[40].position = XMFLOAT3(40.0f, -8.0f, 11.0f);

	instances[41].position = XMFLOAT3(10.0f, -8.0f, -40.0f);
	instances[42].position = XMFLOAT3(10.0f, -8.0f, -53.0f);
	instances[43].position = XMFLOAT3(10.0f, -8.0f, -65.0f);
	instances[44].position = XMFLOAT3(10.0f, -8.0f, -80.0f);

	instances[45].position = XMFLOAT3(-9.0f, -8.0f, -49.0f);
	instances[46].position = XMFLOAT3(-9.0f, -8.0f, -60.0f);
	instances[47].position = XMFLOAT3(-9.0f, -8.0f, -75.0f);

	instances[48].position = XMFLOAT3(-2.0f, -8.0f, -76.0f);
	instances[49].position = XMFLOAT3(8.0f, -8.0f, -80.0f);
	
	instances[50].position = XMFLOAT3(-10.0f, -8.0f, -35.0f);

	// 인스턴스 버퍼의 설명을 설정합니다.
	D3D11_BUFFER_DESC instanceBufferDesc;
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// 하위 리소스 구조에 인스턴스 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA instanceData;
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// 인스턴스 버퍼를 만듭니다.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 인스턴스 버퍼가 생성되고로드되었으므로 인스턴스 배열을 해제합니다.
	delete[] instances;
	instances = 0;

	return true;
}
