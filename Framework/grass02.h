#pragma once
#include "modelclass.h"
class grass02 :
    public ModelClass
{

public:
    grass02();
    ~grass02();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

