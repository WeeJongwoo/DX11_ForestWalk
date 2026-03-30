#pragma once
#include "modelclass.h"
class grassClass :
    public ModelClass
{

public:
    grassClass();
    ~grassClass();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

