////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "PointLightClass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "timerclass.h"

#include <vector>

#include "Cat.h"
#include "fernPlant.h"
#include "floawers.h"
#include "grass02.h"
#include "grassClass.h"
#include "Raccoon.h"
#include "smallBush.h"
#include "smoliv.h"
#include "Stonjourner.h"
#include "TreeModelClass.h"
#include "TreeModelLeafClass.h"
#include "whimsicott.h"
#include "birds.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

enum class LightMode {
	OFF = 0,
	ON
};


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int fps, int cpu);

	void SetInputMapping();

	void ChangeAmbientLightMode();
	void ChangeDeffuseLightMode();
	void ChangeSpecularLightMode();

	void ChangeColorPointLightRed();
	void ChangeColorPointLightGreen();
	void ChangeColorPointLightBlue();

	void ReduceIntensity();
	void IncreaseIntensity();

	bool SetModel(HWND hwnd);
	bool SetPointLight();

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;

	ModelClass* m_Ground;

	Cat* m_Cat;
	fernPlant* m_FernPlat;
	floawers* m_floawers;
	grass02* m_grass02;
	grassClass* m_grassClass;
	Raccoon* m_Raccoon;
	smallBush* m_smallBush;
	smoliv* m_smoliv;
	Stonjourner* m_Stonjourner;
	TreeModelClass* m_TreeModelClass;
	TreeModelLeafClass* m_TreeModelLeafClass;
	whimsicott* m_whimsicott;
	birds* m_birds;

	std::vector<ModelClass*> m_Models;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	LightMode AmbientMode, DeffuseMode, SpecularMode;

	PointLightClass* m_PointLight1, *m_PointLight2, *m_PointLight3;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	TextClass* m_Text;
	TimerClass* m_Timer;
};

#endif