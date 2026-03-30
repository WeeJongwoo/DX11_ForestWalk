#pragma once
#include "modelclass.h"
#include "timerclass.h"

class Raccoon :
    public ModelClass
{

public:
    Raccoon();
    ~Raccoon();

    virtual bool Initialize(ID3D11Device* device, const WCHAR* modelFilename, const WCHAR* textureFilename) override;
    virtual bool InitializeBuffers(ID3D11Device*) override;

private:

    TimerClass* timer;
    float time;
};

