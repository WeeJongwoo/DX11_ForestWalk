////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>

#include "AlignedAllocationPolicy.h"
#include "timerclass.h"

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass : public AlignedAllocationPolicy<16>
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);
	void GetDefaultViewMatrix(XMMATRIX&);

	void UpdateCamera();

	void SetInputEvent();
	bool Initialize();

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;

	//------------------------new-------------------------

	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	XMVECTOR DefaultForward;
	XMVECTOR DefaultRight;
	XMVECTOR DefaultUp;
	XMVECTOR DefaultPos;
	XMVECTOR camForward;
	XMVECTOR camRight;

	XMMATRIX camRotationMatrix;
	XMMATRIX groundWorld;

	float moveLeftRight;
	float moveBackForward;

	float camYaw;
	float camPitch;

	float CamSpeed;

	TimerClass* Timer;
};

#endif