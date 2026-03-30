#pragma once
#include "modelclass.h"
class smoliv :
    public ModelClass
{

public:
    smoliv();
    ~smoliv();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

