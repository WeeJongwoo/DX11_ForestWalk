#pragma once
#include "modelclass.h"
class birds :
    public ModelClass
{

public:
    birds();
    ~birds();

    //virtual bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
    virtual bool InitializeBuffers(ID3D11Device*) override;
};

