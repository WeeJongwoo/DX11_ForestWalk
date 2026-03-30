////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"
#include "InputMappingClass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;

	DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DefaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DefaultPos = XMVectorSet(0.0f, 0.0f, -20.0f, 0.0f);

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camYaw = 0.0f;
	camPitch = 0.0f;

	CamSpeed = 15.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(&m_position);

	// Setup where the camera is looking by default.
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}
 
void CameraClass::GetDefaultViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = XMMatrixLookAtLH(DefaultPos, DefaultForward, DefaultUp);
}


void CameraClass::UpdateCamera()
{
	Timer->Frame();

	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);

	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

	camPosition += moveLeftRight * camRight;
	camPosition += moveBackForward * camForward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;

	m_viewMatrix = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}

void CameraClass::SetInputEvent()
{
	InputMappingClass& InputMapping = InputMappingClass::GetInstance();

	InputMapping.BindKeyEvent(DIK_W, [&]() {
		float deltaTime = (Timer->GetTime()) / 1000;
		moveBackForward += CamSpeed * deltaTime;
		}
	);
	InputMapping.BindKeyEvent(DIK_S, [&]() {
		float deltaTime = (Timer->GetTime()) / 1000;
		moveBackForward -= CamSpeed * deltaTime;
		}
	);
	InputMapping.BindKeyEvent(DIK_A, [&]() {
		float deltaTime = (Timer->GetTime()) / 1000;
		moveLeftRight -= CamSpeed * deltaTime;
		}
	);
	InputMapping.BindKeyEvent(DIK_D, [&]() {
		float deltaTime = (Timer->GetTime())/1000;
		moveLeftRight += CamSpeed * deltaTime;
		}
	);
	InputMapping.BindMouseEvent([&]() {
		camYaw += InputMapping.GetMouseStateX();
		camPitch += InputMapping.GetMouseStateY();
		}
	);

}

bool CameraClass::Initialize()
{
	Timer = new TimerClass;
	if (!Timer)
	{
		return false;
	}

	bool result = Timer->Initialize();
	if(!result)
	{
		return false;
	}

	camPosition = DefaultPos;
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = DefaultUp;

	SetInputEvent();

	return true;
}


