#pragma once

class IApp
{
private:

public:

    virtual ~IApp() {}

    virtual bool Init() = 0;
    virtual bool Deinit();
    virtual bool OnTouch(unsigned int nX, unsigned int nY);
    virtual void OnEnter();
    virtual void OnExit();
    virtual void OnDraw();
};
