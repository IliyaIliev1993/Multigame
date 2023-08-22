#include "IApp.h"

#include "utils/Utils.h"

bool IApp::Init()
{
    LOGGER("IApp - Init() ...");
    return true;
}

bool IApp::Deinit()
{
    LOGGER("IApp - Deinit() ...");
    return true;
}

bool IApp::OnTouch(unsigned int nX, unsigned int nY)
{
    LOGGER("IApp - OnTouch() ...");
    return false;
}

void IApp::OnEnter()
{
    LOGGER("IApp - OnEnter() ...");
}

void IApp::OnExit()
{
    LOGGER("IApp - OnExit() ...");
}

void IApp::OnDraw()
{
    LOGGER("IApp - OnDraw() ...");
}
