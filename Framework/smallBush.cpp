#include "smallBush.h"

smallBush::smallBush()
{
}

smallBush::~smallBush()
{
}

bool smallBush::InitializeBuffers(ID3D11Device* device)
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
	m_instanceCount = 131;

	// 인스턴스 배열을 만듭니다.
	InstanceType* instances = new InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	// 데이터로 인스턴스 배열을 로드합니다.
	instances[0].position = XMFLOAT3(0.0f, 0.0f, 6.0f);
	instances[1].position = XMFLOAT3(-5.0f, 0.0f, 6.0f);
	instances[2].position = XMFLOAT3(-10.0f, 0.0f, 6.0f);
	instances[3].position = XMFLOAT3(-15.0f, 0.0f, 6.0f);
	instances[4].position = XMFLOAT3(-20.0f, 0.0f, 6.0f);
	instances[5].position = XMFLOAT3(-25.0f, 0.0f, 6.0f);
	instances[6].position = XMFLOAT3(-30.0f, 0.0f, 6.0f);
	instances[7].position = XMFLOAT3(-35.0f, 0.0f, 6.0f);
	instances[8].position = XMFLOAT3(-40.0f, 0.0f, 6.0f);
	instances[9].position = XMFLOAT3(-45.0f, 0.0f, 6.0f);

	instances[10].position = XMFLOAT3(-50.0f, 0.0f, 6.0f);
	instances[11].position = XMFLOAT3(-55.0f, 0.0f, 6.0f);
	instances[12].position = XMFLOAT3(-60.0f, 0.0f, 6.0f);
	instances[13].position = XMFLOAT3(-65.0f, 0.0f, 6.0f);
	instances[14].position = XMFLOAT3(-70.0f, 0.0f, 6.0f);
	instances[15].position = XMFLOAT3(-75.0f, 0.0f, 6.0f);
	instances[16].position = XMFLOAT3(-80.0f, 0.0f, 6.0f);
	instances[17].position = XMFLOAT3(-85.0f, 0.0f, 6.0f);
	instances[18].position = XMFLOAT3(-90.0f, 0.0f, 6.0f);
	instances[19].position = XMFLOAT3(-95.0f, 0.0f, 6.0f);
	instances[20].position = XMFLOAT3(-100.0f, 0.0f, 6.0f);
	instances[21].position = XMFLOAT3(-105.0f, 0.0f, 6.0f);
	instances[22].position = XMFLOAT3(-110.0f, 0.0f, 6.0f);

	instances[23].position = XMFLOAT3(-110.0f, 0.0f, 1.0f);
	instances[24].position = XMFLOAT3(-110.0f, 0.0f, -4.0f);
	instances[25].position = XMFLOAT3(-110.0f, 0.0f, -9.0f);
	instances[26].position = XMFLOAT3(-110.0f, 0.0f, -14.0f);
	instances[27].position = XMFLOAT3(-110.0f, 0.0f, -19.0f);
	instances[28].position = XMFLOAT3(-110.0f, 0.0f, -24.0f);
	instances[29].position = XMFLOAT3(-110.0f, 0.0f, -29.0f);
	instances[30].position = XMFLOAT3(-110.0f, 0.0f, -34.0f);
	instances[31].position = XMFLOAT3(-110.0f, 0.0f, -39.0f);
	instances[32].position = XMFLOAT3(-110.0f, 0.0f, -44.0f);
	instances[33].position = XMFLOAT3(-110.0f, 0.0f, -49.0f);
	instances[34].position = XMFLOAT3(-110.0f, 0.0f, -54.0f);
	instances[35].position = XMFLOAT3(-110.0f, 0.0f, -59.0f);

	instances[36].position = XMFLOAT3(-105.0f, 0.0f, -59.0f);
	instances[37].position = XMFLOAT3(-100.0f, 0.0f, -59.0f);
	instances[38].position = XMFLOAT3(-95.0f, 0.0f, -59.0f);
	instances[39].position = XMFLOAT3(-90.0f, 0.0f, -59.0f);
	instances[40].position = XMFLOAT3(-85.0f, 0.0f, -59.0f);
	instances[41].position = XMFLOAT3(-80.0f, 0.0f, -59.0f);

	instances[42].position = XMFLOAT3(-80.0f, 0.0f, -54.0f);
	instances[43].position = XMFLOAT3(-80.0f, 0.0f, -49.0f);
	instances[44].position = XMFLOAT3(-80.0f, 0.0f, -44.0f);
	instances[45].position = XMFLOAT3(-80.0f, 0.0f, -39.0f);
	instances[46].position = XMFLOAT3(-80.0f, 0.0f, -34.0f);

	instances[47].position = XMFLOAT3(-75.0f, 0.0f, -34.0f);
	instances[48].position = XMFLOAT3(-70.0f, 0.0f, -34.0f);
	instances[49].position = XMFLOAT3(-65.0f, 0.0f, -34.0f);
	instances[50].position = XMFLOAT3(-60.0f, 0.0f, -34.0f);
	instances[51].position = XMFLOAT3(-55.0f, 0.0f, -34.0f);
	instances[52].position = XMFLOAT3(-50.0f, 0.0f, -34.0f);
	instances[53].position = XMFLOAT3(-45.0f, 0.0f, -34.0f);
	instances[54].position = XMFLOAT3(-40.0f, 0.0f, -34.0f);
	instances[55].position = XMFLOAT3(-35.0f, 0.0f, -34.0f);
	instances[56].position = XMFLOAT3(-30.0f, 0.0f, -34.0f);
	instances[57].position = XMFLOAT3(-25.0f, 0.0f, -34.0f);
	instances[58].position = XMFLOAT3(-20.0f, 0.0f, -34.0f);

	instances[59].position = XMFLOAT3(-20.0f, 0.0f, -39.0f);
	instances[60].position = XMFLOAT3(-20.0f, 0.0f, -44.0f);
	instances[61].position = XMFLOAT3(-20.0f, 0.0f, -49.0f);
	instances[62].position = XMFLOAT3(-20.0f, 0.0f, -54.0f);
	instances[63].position = XMFLOAT3(-20.0f, 0.0f, -59.0f);
	instances[64].position = XMFLOAT3(-20.0f, 0.0f, -64.0f);
	instances[65].position = XMFLOAT3(-20.0f, 0.0f, -69.0f);
	instances[66].position = XMFLOAT3(-20.0f, 0.0f, -74.0f);
	instances[67].position = XMFLOAT3(-20.0f, 0.0f, -79.0f);
	instances[68].position = XMFLOAT3(-20.0f, 0.0f, -84.0f);

	instances[69].position = XMFLOAT3(-15.0f, 0.0f, -84.0f);
	instances[70].position = XMFLOAT3(-10.0f, 0.0f, -84.0f);
	instances[71].position = XMFLOAT3(-5.0f, 0.0f, -84.0f);
	instances[72].position = XMFLOAT3(0.0f, 0.0f, -84.0f);
	instances[73].position = XMFLOAT3(5.0f, 0.0f, -84.0f);
	instances[74].position = XMFLOAT3(10.0f, 0.0f, -84.0f);
	instances[75].position = XMFLOAT3(15.0f, 0.0f, -84.0f);
	instances[76].position = XMFLOAT3(20.0f, 0.0f, -84.0f);

	instances[77].position = XMFLOAT3(20.0f, 0.0f, -79.0f);
	instances[78].position = XMFLOAT3(20.0f, 0.0f, -74.0f);
	instances[79].position = XMFLOAT3(20.0f, 0.0f, -69.0f);
	instances[80].position = XMFLOAT3(20.0f, 0.0f, -64.0f);
	instances[81].position = XMFLOAT3(20.0f, 0.0f, -59.0f);
	instances[82].position = XMFLOAT3(20.0f, 0.0f, -54.0f);
	instances[83].position = XMFLOAT3(20.0f, 0.0f, -49.0f);
	instances[84].position = XMFLOAT3(20.0f, 0.0f, -44.0f);
	instances[85].position = XMFLOAT3(20.0f, 0.0f, -39.0f);
	instances[86].position = XMFLOAT3(20.0f, 0.0f, -34.0f);

	instances[86].position = XMFLOAT3(25.0f, 0.0f, -34.0f);
	instances[87].position = XMFLOAT3(30.0f, 0.0f, -34.0f);
	instances[88].position = XMFLOAT3(35.0f, 0.0f, -34.0f);
	instances[89].position = XMFLOAT3(40.0f, 0.0f, -34.0f);
	instances[90].position = XMFLOAT3(45.0f, 0.0f, -34.0f);
	instances[91].position = XMFLOAT3(50.0f, 0.0f, -34.0f);
	instances[92].position = XMFLOAT3(55.0f, 0.0f, -34.0f);
	instances[93].position = XMFLOAT3(60.0f, 0.0f, -34.0f);
	instances[94].position = XMFLOAT3(65.0f, 0.0f, -34.0f);
	instances[95].position = XMFLOAT3(70.0f, 0.0f, -34.0f);

	instances[96].position = XMFLOAT3(70.0f, 0.0f, -29.0f);
	instances[97].position = XMFLOAT3(70.0f, 0.0f, -24.0f);
	instances[98].position = XMFLOAT3(70.0f, 0.0f, -19.0f);
	instances[99].position = XMFLOAT3(70.0f, 0.0f, -14.0f);
	instances[100].position = XMFLOAT3(70.0f, 0.0f, -9.0f);
	instances[101].position = XMFLOAT3(70.0f, 0.0f, -4.0f);
	instances[102].position = XMFLOAT3(70.0f, 0.0f, 1.0f);
	instances[103].position = XMFLOAT3(70.0f, 0.0f, 6.0f);
	instances[104].position = XMFLOAT3(70.0f, 0.0f, 11.0f);
	instances[105].position = XMFLOAT3(70.0f, 0.0f, 16.0f);
	instances[106].position = XMFLOAT3(70.0f, 0.0f, 21.0f);
	instances[107].position = XMFLOAT3(70.0f, 0.0f, 26.0f);
	instances[108].position = XMFLOAT3(70.0f, 0.0f, 31.0f);
	instances[109].position = XMFLOAT3(70.0f, 0.0f, 36.0f);
	instances[110].position = XMFLOAT3(70.0f, 0.0f, 41.0f);

	instances[111].position = XMFLOAT3(65.0f, 0.0f, 41.0f);
	instances[112].position = XMFLOAT3(60.0f, 0.0f, 41.0f);
	instances[113].position = XMFLOAT3(55.0f, 0.0f, 41.0f);
	instances[114].position = XMFLOAT3(50.0f, 0.0f, 41.0f);
	instances[115].position = XMFLOAT3(45.0f, 0.0f, 41.0f);
	instances[116].position = XMFLOAT3(40.0f, 0.0f, 41.0f);
	instances[117].position = XMFLOAT3(35.0f, 0.0f, 41.0f);

	instances[118].position = XMFLOAT3(35.0f, 0.0f, 36.0f);
	instances[119].position = XMFLOAT3(35.0f, 0.0f, 31.0f);
	instances[120].position = XMFLOAT3(35.0f, 0.0f, 26.0f);
	instances[121].position = XMFLOAT3(35.0f, 0.0f, 21.0f);
	instances[122].position = XMFLOAT3(35.0f, 0.0f, 16.0f);
	instances[123].position = XMFLOAT3(35.0f, 0.0f, 11.0f);
	instances[124].position = XMFLOAT3(35.0f, 0.0f, 6.0f);

	instances[125].position = XMFLOAT3(30.0f, 0.0f, 6.0f);
	instances[126].position = XMFLOAT3(25.0f, 0.0f, 6.0f);
	instances[127].position = XMFLOAT3(20.0f, 0.0f, 6.0f);
	instances[128].position = XMFLOAT3(15.0f, 0.0f, 6.0f);
	instances[129].position = XMFLOAT3(10.0f, 0.0f, 6.0f);
	instances[130].position = XMFLOAT3(5.0f, 0.0f, 6.0f);

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
