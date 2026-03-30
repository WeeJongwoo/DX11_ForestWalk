#pragma once
#include "modelclass.h"


class TreeModelClass :public ModelClass
{

public:
    TreeModelClass();
    ~TreeModelClass();

    virtual bool InitializeBuffers(ID3D11Device*) override;
};

