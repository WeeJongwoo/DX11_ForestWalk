#include "grass02.h"

grass02::grass02()
{
}

grass02::~grass02()
{
}

bool grass02::InitializeBuffers(ID3D11Device* device)
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
	m_instanceCount = 46;

	// 인스턴스 배열을 만듭니다.
	InstanceType* instances = new InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	// 데이터로 인스턴스 배열을 로드합니다.
	instances[0].position = XMFLOAT3(-0.0f, -23.3f, 16.5f);
	instances[1].position = XMFLOAT3(-33.3f, -23.3f, 16.5f);
	instances[2].position = XMFLOAT3(-80.6f, -23.3f, 16.5f);
	instances[3].position = XMFLOAT3(-120.0f, -23.3f, 16.5f);
	instances[4].position = XMFLOAT3(-140.3f, -23.3f, 16.5f);
	instances[5].position = XMFLOAT3(-190.6f, -23.3f, 16.5f);
	instances[6].position = XMFLOAT3(-225.0f, -23.3f, 16.5f);
	instances[7].position = XMFLOAT3(-270.3f, -23.3f, 16.5f);
	instances[8].position = XMFLOAT3(-300.0f, -23.3f, 16.5f);
	instances[9].position = XMFLOAT3(-333.3f, -23.3f, 16.5f);

	instances[10].position = XMFLOAT3(-33.3f, -23.3f, -76.5f);
	instances[11].position = XMFLOAT3(-33.3f, -23.3f, -100.5f);
	instances[12].position = XMFLOAT3(-70.6f, -23.3f, -76.5f);
	instances[13].position = XMFLOAT3(-120.0f, -23.3f, -76.5f);
	instances[14].position = XMFLOAT3(-160.3f, -23.3f, -76.5f);
	instances[15].position = XMFLOAT3(-200.6f, -23.3f, -76.5f);
	instances[16].position = XMFLOAT3(-250.0f, -23.3f, -76.5f);
	instances[17].position = XMFLOAT3(-280.3f, -23.3f, -110.5f);
	instances[18].position = XMFLOAT3(-283.3f, -23.3f, -160.5f);

	instances[19].position = XMFLOAT3(-33.3f, -23.3f, -145.5f);
	instances[20].position = XMFLOAT3(-33.3f, -23.3f, -200.5f);
	instances[21].position = XMFLOAT3(-33.3f, -23.3f, -240.5f);

	instances[22].position = XMFLOAT3(-300.3f, -23.3f, -160.5f);
	instances[23].position = XMFLOAT3(-333.3f, -23.3f, -140.5f);
	instances[24].position = XMFLOAT3(-333.3f, -23.3f, -100.5f);
	instances[25].position = XMFLOAT3(-333.3f, -23.3f, -50.5f);
	instances[26].position = XMFLOAT3(-333.3f, -23.3f, -10.5f);

	instances[27].position = XMFLOAT3(33.3f, -23.3f, 16.5f);
	instances[28].position = XMFLOAT3(80.3f, -23.3f, 24.5f);
	instances[29].position = XMFLOAT3(130.3f, -23.3f, 18.5f);
	instances[30].position = XMFLOAT3(130.3f, -23.3f, 70.5f);
	instances[31].position = XMFLOAT3(180.3f, -23.3f, 120.5f);
	instances[32].position = XMFLOAT3(155.3f, -23.3f, 120.5f);
	instances[33].position = XMFLOAT3(210.3f, -23.3f, 120.5f);

	instances[34].position = XMFLOAT3(230.3f, -23.3f, 70.5f);
	instances[35].position = XMFLOAT3(210.3f, -23.3f, 10.5f);
	instances[36].position = XMFLOAT3(220.3f, -23.3f, -30.5f);
	instances[37].position = XMFLOAT3(220.3f, -23.3f, -76.5f);

	instances[38].position = XMFLOAT3(80.3f, -23.3f, -76.5f);
	instances[39].position = XMFLOAT3(130.3f, -23.3f, -76.5f);
	instances[40].position = XMFLOAT3(180.3f, -23.3f, -76.5f);
	instances[41].position = XMFLOAT3(50.3f, -23.3f, -100.5f);
	instances[42].position = XMFLOAT3(60.3f, -23.3f, -160.5f);
	instances[43].position = XMFLOAT3(50.3f, -23.3f, -210.5f);
	instances[44].position = XMFLOAT3(50.3f, -23.3f, -240.5f);
	instances[45].position = XMFLOAT3(0.3f, -23.3f, -240.5f);



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
