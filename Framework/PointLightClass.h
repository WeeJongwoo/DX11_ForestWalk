#pragma once

//////////////
// INCLUDES //
//////////////
#include <directxmath.h>

using namespace DirectX;

class PointLightClass
{
public:
	PointLightClass();
	PointLightClass(const PointLightClass&);
	~PointLightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetPosition(float, float, float);

	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetDirection();
	XMFLOAT4 GetPosition();

private:
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
	XMFLOAT4 m_position;

};

