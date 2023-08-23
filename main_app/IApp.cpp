#include "IApp.h"

#include <debug/Logger.h>

bool IApp::Init()
{
    LOG_INFO("IApp - Init() ...");
    return true;
}

bool IApp::Deinit()
{
    LOG_INFO("IApp - Deinit() ...");
    return true;
}

bool IApp::OnTouch(unsigned int nX, unsigned int nY)
{
    LOG_INFO("IApp - OnTouch() ...");
    return false;
}

const std::string& IApp::GetAppName()
{
    return m_strAppName;
}

void IApp::OnEnter()
{
    LOG_INFO("IApp - OnEnter() ...");
}

void IApp::OnExit()
{
    LOG_INFO("IApp - OnExit() ...");
}

void IApp::OnDraw()
{
    LOG_INFO("IApp - OnDraw() ...");
}
