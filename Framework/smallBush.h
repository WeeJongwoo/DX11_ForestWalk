#pragma once
#include "modelclass.h"
class smallBush :
    public ModelClass
{

public:
    smallBush();
    ~smallBush();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

