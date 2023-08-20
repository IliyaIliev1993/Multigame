#pragma once

class IApp
{
private:

public:

    virtual ~IApp();

    virtual bool Init() = 0;
    virtual bool Deinit();
    virtual void OnEnter();
    virtual bool OnExit();
    virtual void OnDraw();
    virtual bool OnTouch(unsigned int nX, unsigned int nY);
};
