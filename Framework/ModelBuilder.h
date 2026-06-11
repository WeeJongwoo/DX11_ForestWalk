#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <vector>

#include "modelclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelBuilder
//
// Fluent builder for scene models.
// Encapsulates the repeated procedure:
//   new T -> Initialize(device, obj, dds) -> error handling -> store in collection
//
// Usage:
//   ModelBuilder builder(device);
//   builder.Add<Cat>(L"./data/Cat.obj", L"./data/Cat.dds")
//          .Add<Raccoon>(L"./data/Raccoon.obj", L"./data/Raccoon.dds");
//   if (!builder.BuildInto(m_Models)) { /* handle failure */ }
////////////////////////////////////////////////////////////////////////////////
class ModelBuilder
{
public:
	explicit ModelBuilder(ID3D11Device* device)
		: m_device(device), m_failed(false)
	{
	}

	// Add a single model. T must derive from ModelClass.
	// Once any Add fails, later Add calls are short-circuited (skipped).
	template <class T>
	ModelBuilder& Add(const WCHAR* objFile, const WCHAR* textureFile)
	{
		if (m_failed)
		{
			return *this;
		}

		T* model = new T;
		if (!model->Initialize(m_device, objFile, textureFile))
		{
			model->Shutdown();
			delete model;
			m_failed = true;
			return *this;
		}

		// Stored as ModelClass* (virtual Initialize/Render are used).
		m_models.push_back(model);
		return *this;
	}

	// Final step. Move all built models into 'out'.
	// - All succeeded: append to 'out' and return true.
	// - Any failure: clean up the temporary models and return false.
	bool BuildInto(std::vector<ModelClass*>& out)
	{
		if (m_failed)
		{
			for (ModelClass* model : m_models)
			{
				if (model)
				{
					model->Shutdown();
					delete model;
				}
			}
			m_models.clear();
			return false;
		}

		for (ModelClass* model : m_models)
		{
			out.push_back(model);
		}
		m_models.clear();
		return true;
	}

private:
	ID3D11Device*            m_device;
	bool                     m_failed;
	std::vector<ModelClass*> m_models;	// temporary staging area
};
