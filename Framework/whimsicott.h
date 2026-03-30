#pragma once
#include "modelclass.h"
class whimsicott :
    public ModelClass
{

public:
    whimsicott();
    ~whimsicott();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

