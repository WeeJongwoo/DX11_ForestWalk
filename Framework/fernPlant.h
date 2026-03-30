#pragma once
#include "modelclass.h"
class fernPlant :
    public ModelClass
{

public:
    fernPlant();
    ~fernPlant();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

