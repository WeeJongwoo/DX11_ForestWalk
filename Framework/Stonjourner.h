#pragma once
#include "modelclass.h"
class Stonjourner :
    public ModelClass
{

public:
    Stonjourner();
    ~Stonjourner();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

