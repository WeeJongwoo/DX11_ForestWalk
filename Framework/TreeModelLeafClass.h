#pragma once
#include "modelclass.h"
class TreeModelLeafClass :
    public ModelClass
{

public:
    TreeModelLeafClass();
    ~TreeModelLeafClass();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

