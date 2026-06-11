////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "InputMappingClass.h"
#include "ModelBuilder.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_Timer = new TimerClass;
	result = m_Timer->Initialize();
	if (!result)
	{
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	result = m_Camera->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Camera.", L"Error", MB_OK);
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
	//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair


		// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	//m_Ground = new ModelClass;
	//if (!m_Ground)
	//{
	//	return false;
	//}
	//result = m_Ground->Initialize(m_D3D->GetDevice(), L"./data/ground.obj", L"./data/ground.dds");
	//// Initialize the model object.
	////result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/cube.obj", L"./data/seafloor.dds");
	////result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/Stonjourner.obj", L"./data/Stonjourner.dds");
	////	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	//m_Cat = new Cat;
	//result = m_Cat->Initialize(m_D3D->GetDevice(), L"./data/Cat.obj", L"./data/Cat.dds");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	result = SetModel(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	/*m_Models.push_back(m_Ground);
	m_Models.push_back(m_Cat);*/

	//// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light->SetDirection(0.0f, -2.0f, -1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	AmbientMode = LightMode::ON;
	DeffuseMode = LightMode::ON;
	SpecularMode = LightMode::ON;

	SetInputMapping();

	result = SetPointLight();
	if (!result)
	{
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/background.dds", 1600, 900);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	XMMATRIX baseViewMatrix;
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	//m_Camera->Render();
	m_Camera->UpdateCamera();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}



	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release all models (owned by m_Models, built via ModelBuilder).
	// Frees every model in one loop (the old per-pointer code leaked a few).
	for (ModelClass* model : m_Models)
	{
		if (model)
		{
			model->Shutdown();
			delete model;
		}
	}
	m_Models.clear();

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool GraphicsClass::Frame(int fps, int cpu)
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	int NumOfObj = 0;
	int PolyNum = 0;
	for (auto Model : m_Models)
	{
		NumOfObj += Model->GetInstanceCount();
		PolyNum += (Model->GetIndexCount()) / 3;
	}

	result = m_Text->SetNumberOfObject(NumOfObj, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetNumberOfPolygon(PolyNum, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreenResoiution(1600, 900, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::SetInputMapping()
{
	InputMappingClass& InputMapping = InputMappingClass::GetInstance();

	InputMapping.BindKeyDownEvent(DIK_6, [&]() {
		this->ChangeAmbientLightMode();
		});

	InputMapping.BindKeyDownEvent(DIK_7, [&]() {
		this->ChangeDeffuseLightMode();
		});

	InputMapping.BindKeyDownEvent(DIK_8, [&]() {
		this->ChangeSpecularLightMode();
		});

	InputMapping.BindKeyDownEvent(DIK_R, [&]() {
		this->ChangeColorPointLightRed();
		});

	InputMapping.BindKeyDownEvent(DIK_G, [&]() {
		this->ChangeColorPointLightGreen();
		});

	InputMapping.BindKeyDownEvent(DIK_B, [&]() {
		this->ChangeColorPointLightBlue();
		});

	InputMapping.BindKeyDownEvent(DIK_MINUS, [&]() {
		this->ReduceIntensity();
		});

	InputMapping.BindKeyEvent(DIK_EQUALS, [&]() {
		this->IncreaseIntensity();
		});
}

void GraphicsClass::ChangeAmbientLightMode()
{
	switch (AmbientMode)
	{
	case LightMode::OFF: {
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		AmbientMode = LightMode::ON;
		break;
	}
	case LightMode::ON: {
		m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
		AmbientMode = LightMode::OFF;
		break;
	}
	default:
		break;
	}
}

void GraphicsClass::ChangeDeffuseLightMode()
{
	switch (DeffuseMode)
	{
	case LightMode::OFF: {
		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		DeffuseMode = LightMode::ON;
		break;
	}
	case LightMode::ON: {
		m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
		DeffuseMode = LightMode::OFF;
		break;
	}
	default:
		break;
	}
}

void GraphicsClass::ChangeSpecularLightMode()
{
	switch (SpecularMode)
	{
	case LightMode::OFF: {
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		SpecularMode = LightMode::ON;
		break;
	}
	case LightMode::ON: {
		m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 1.0f);
		SpecularMode = LightMode::OFF;
		break;
	}
	default:
		break;
	}
}

void GraphicsClass::ChangeColorPointLightRed()
{
	m_PointLight1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void GraphicsClass::ChangeColorPointLightGreen()
{
	m_PointLight1->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void GraphicsClass::ChangeColorPointLightBlue()
{
	m_PointLight1->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void GraphicsClass::ReduceIntensity()
{
	float newX = m_Light->GetDiffuseColor().x - 0.1f;
	float newY = m_Light->GetDiffuseColor().y - 0.1f;
	float newZ = m_Light->GetDiffuseColor().z - 0.1f;

	m_Light->SetDiffuseColor(newX, newY, newZ, 1.0f);

	newX = m_PointLight1->GetDiffuseColor().x - 0.1f;
	newY = m_PointLight1->GetDiffuseColor().y - 0.1f;
	newZ = m_PointLight1->GetDiffuseColor().z - 0.1f;

	m_PointLight1->SetDiffuseColor(newX, newY, newZ, 1.0f);
}

void GraphicsClass::IncreaseIntensity()
{
	float newX = m_Light->GetDiffuseColor().x + 0.1f;
	float newY = m_Light->GetDiffuseColor().y + 0.1f;
	float newZ = m_Light->GetDiffuseColor().z + 0.1f;

	m_Light->SetDiffuseColor(newX, newY, newZ, 1.0f);

	newX = m_PointLight1->GetDiffuseColor().x + 0.1f;
	newY = m_PointLight1->GetDiffuseColor().y + 0.1f;
	newZ = m_PointLight1->GetDiffuseColor().z + 0.1f;

	m_PointLight1->SetDiffuseColor(newX, newY, newZ, 1.0f);
}

bool GraphicsClass::SetModel(HWND hwnd)
{
	// The builder encapsulates the repeated "new T -> Initialize -> error check
	// -> push into m_Models" procedure.
	// Add order == m_Models index order. Render() branches on this index,
	// so the order must NOT change.
	ModelBuilder builder(m_D3D->GetDevice());

	builder.Add<ModelClass>(L"./data/ground.obj",              L"./data/ground.dds")                   // 0
	       .Add<Cat>(L"./data/Cat.obj",                        L"./data/Cat.dds")                      // 1
	       .Add<fernPlant>(L"./data/fernPlant.obj",            L"./data/fernPlant.dds")                // 2
	       .Add<floawers>(L"./data/flowers.obj",               L"./data/flowers.dds")                  // 3
	       .Add<grass02>(L"./data/grass02.obj",                L"./data/grass02.dds")                  // 4
	       .Add<grassClass>(L"./data/grass.obj",               L"./data/grass.dds")                    // 5
	       .Add<Raccoon>(L"./data/Raccoon.obj",                L"./data/Raccoon.dds")                  // 6
	       .Add<smallBush>(L"./data/small_bush.obj",           L"./data/small_bush.dds")               // 7
	       .Add<smoliv>(L"./data/smoliv.obj",                  L"./data/smoliv.dds")                   // 8
	       .Add<Stonjourner>(L"./data/Stonjourner.obj",        L"./data/Stonjourner.dds")              // 9
	       .Add<TreeModelClass>(L"./data/tree01.obj",          L"./data/tree01.dds")                   // 10
	       .Add<TreeModelLeafClass>(L"./data/tree01_leaf.obj", L"./data/tree01_leaf.dds")              // 11
	       .Add<whimsicott>(L"./data/whimsicott.obj",          L"./data/whimsicott_mat_Base_Color.dds")// 12
	       .Add<birds>(L"./data/birds.obj",                    L"./data/birds.dds");                   // 13

	if (!builder.BuildInto(m_Models))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::SetPointLight()
{
	m_PointLight1 = new PointLightClass;
	if (!m_PointLight1)
	{
		return false;
	}
	// Initialize the first light object.
	m_PointLight1->SetDiffuseColor(0.86f, 0.76f, 0.6f, 1.0f);
	m_PointLight1->SetPosition(-97.0f, 5.0f, -30.0f);

	m_PointLight2 = new PointLightClass;
	if (!m_PointLight1)
	{
		return false;
	}
	// Initialize the first light object.
	m_PointLight2->SetDiffuseColor(0.63f, 0.78f, 0.5f, 1.0f);
	m_PointLight2->SetPosition(0.0f, 2.0f, -58.0f);

	m_PointLight3 = new PointLightClass;
	if (!m_PointLight1)
	{
		return false;
	}
	// Initialize the first light object.
	m_PointLight3->SetDiffuseColor(1.0f, 0.5f, 0.0f, 1.0f);
	m_PointLight3->SetPosition(50.0f, 2.0f, 5.0f);

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;

	m_Timer->Frame();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	//m_Camera->Render();
	m_Camera->UpdateCamera();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetDefaultViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn on the alpha blending before rendering the text.
	m_Camera->GetViewMatrix(viewMatrix);

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Ground->Render(m_D3D->GetDeviceContext());

	/////*for (ModelClass* model : m_Models)
	////{
	////	model->Render(m_D3D->GetDeviceContext());
	////}*/

	////worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//worldMatrix *= XMMatrixScaling(100.0f, 1.0f, 100.0f);

	//XMFLOAT4 diffuseColor[1];
	//XMFLOAT4 lightPosition[1];

	//diffuseColor[0] = m_PointLight->GetDiffuseColor();
	//lightPosition[0] = m_PointLight->GetPosition();

	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(), m_Ground->GetInstanceCount(),
	//	worldMatrix, viewMatrix, projectionMatrix,
	//	m_Ground->GetTexture(),
	//	m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
	//	m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
	//	diffuseColor, lightPosition);

	int count = 0;

	/*
	m_Models.push_back(m_Ground);					0
	m_Models.push_back(m_Cat);						1
	m_Models.push_back(m_FernPlat);					2
	m_Models.push_back(m_floawers);					3
	m_Models.push_back(m_grass02);					4
	m_Models.push_back(m_grassClass);				5
	m_Models.push_back(m_Raccoon);					6
	m_Models.push_back(m_smallBush);				7
	m_Models.push_back(m_smoliv);					8
	m_Models.push_back(m_Stonjourner);				9
	m_Models.push_back(m_TreeModelClass);			10
	m_Models.push_back(m_TreeModelLeafClass);		11
	m_Models.push_back(m_whimsicott);				12
	m_Models.push_back(m_birds);					13
	*/
	static float time = 0.0f;
	static bool olivUp = true;
	static bool stonUp = true;
	static bool whimUp = true;
	float deltaTime = (m_Timer->GetTime()) / 1000;

	if (olivUp)
	{
		time += deltaTime;
	}
	else
	{
		time -= deltaTime;
	}

	if (time >= 2.0f)
	{
		olivUp = false;
		stonUp = false;
		whimUp = false;
	}
	else if (time <= 0.0f)
	{
		olivUp = true;
		stonUp = true;
		whimUp = true;
	}

	for (ModelClass* model : m_Models)
	{

		model->Render(m_D3D->GetDeviceContext());

		XMMATRIX worldMatrix2 = worldMatrix;
		bool IsRotate = false;
		switch (count)
		{

		case 0:
		{
			//worldMatrix2 = XMMatrixTranslation(0/)
			worldMatrix2 *= XMMatrixScaling(1000.0f, 1.0f, 1000.0f);
			break;
		}
		case 1:
		{
			worldMatrix2 *= XMMatrixScaling(0.1f, 0.1f, 0.1f);
			worldMatrix2 *= XMMatrixRotationY(rotation * 3);
			worldMatrix2 *= XMMatrixTranslation(0.0f, -8.0f, -5.0f);
			IsRotate = true;
			break;
		}
		case 2:
		{
			worldMatrix2 *= XMMatrixScaling(0.1f, 0.1f, 0.1f);
			break;
		}
		case 3:
		{
			worldMatrix2 *= XMMatrixScaling(1.5f, 1.5f, 1.5f);
			break;
		}
		case 4:
		{
			worldMatrix2 *= XMMatrixScaling(0.3f, 0.3f, 0.3f);
			break;
		}
		case 6:
		{
			worldMatrix2 = XMMatrixRotationY(rotation);
			worldMatrix2 *= XMMatrixScaling(15.0f, 15.0f, 15.0f);
			worldMatrix2 *= XMMatrixTranslation(7.0f, -8.0f, -3.0f);
			IsRotate = true;
			break;
		}
		case 7:
		{
			worldMatrix2 *= XMMatrixScaling(15.0f, 20.0f, 15.0f);
			worldMatrix2 *= XMMatrixTranslation(0.0f, -8.0f, 0.0f);
			IsRotate = true;
			break;
		}
		case 8:
		{

			worldMatrix2 = XMMatrixRotationY(rotation);
			worldMatrix2 *= XMMatrixScaling(0.1f, 0.1f, 0.1f);

			worldMatrix2 *= XMMatrixTranslation(0.0f, time, -68.0f);

			//worldMatrix2 *= XMMatrixTranslation(0.0f, 3.0f, -70.0f);
			IsRotate = true;
			break;
		}
		case 9:
		{
			worldMatrix2 *= XMMatrixRotationY(rotation * 2);
			worldMatrix2 *= XMMatrixScaling(0.5f, 0.5f, 0.5f);

			worldMatrix2 *= XMMatrixTranslation(50.0f, time - 5.0f, 10.0f);

			//worldMatrix2 *= XMMatrixTranslation(50.0f, -5.0f, 10.0f);
			IsRotate = true;
			break;
		}
		case 10:
		case 11:
		{
			worldMatrix2 *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
			break;
		}
		case 12:
		{
			worldMatrix2 *= XMMatrixRotationY(rotation);
			worldMatrix2 *= XMMatrixScaling(10.0f, 10.0f, 10.0f);

			worldMatrix2 *= XMMatrixTranslation(-100.0f, time - 4.0f, -40.0f);
			IsRotate = true;

			break;
		}
		case 13:
		{
			worldMatrix2 = XMMatrixRotationY(-rotation);
			worldMatrix2 *= XMMatrixScaling(10.0f, 10.0f, 10.0f);
			break;
		}
		default:
		{
			worldMatrix2 *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
			break;
		}
		}

		XMFLOAT4 diffuseColor[3];
		XMFLOAT4 lightPosition[3];

		diffuseColor[0] = m_PointLight1->GetDiffuseColor();
		lightPosition[0] = m_PointLight1->GetPosition();

		diffuseColor[1] = m_PointLight2->GetDiffuseColor();
		lightPosition[1] = m_PointLight2->GetPosition();

		diffuseColor[2] = m_PointLight3->GetDiffuseColor();
		lightPosition[2] = m_PointLight3->GetPosition();

		//// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), model->GetInstanceCount(),
			worldMatrix2, viewMatrix, projectionMatrix,
			model->GetTexture(),
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
			diffuseColor, lightPosition, IsRotate);

		count++;
	}

	m_D3D->TurnOnAlphaBlending();
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}