#pragma once
#include "modelclass.h"
class Cat :
    public ModelClass
{

public:
    Cat();
    ~Cat();

    //virtual bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
    virtual bool InitializeBuffers(ID3D11Device*) override;
};

