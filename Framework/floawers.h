#pragma once
#include "modelclass.h"
class floawers :
    public ModelClass
{

public:
    floawers();
    ~floawers();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

