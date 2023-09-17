#include "MainGame.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/app_select/AppSelect.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

#include <iostream>

Roulette::Roulette()
{

}

bool Roulette::Init()
{
    LOG_INFO("Roulette - Initialized ...");
    return true;
}

bool Roulette::Deinit()
{
    return true;
}

bool Roulette::HandleEvent()
{
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    return false;
}

const std::string& Roulette::GetAppName()
{
    return m_strAppName;
}

void Roulette::OnEnter()
{
    MainApp::GetInstance().ptrTimer->StartTimer(this, 1, 1000);
}

void Roulette::OnExit()
{
    
}

void Roulette::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;
}

void Roulette::OnTick(unsigned int unID, unsigned int unTimes)
{
    if(unID == 1)
    {
        LOG_INFO("ROULETTE Timer ID \"{0}\"", unID);
        LOG_INFO("ROULETTE Timer TIMES \"{0}\"", unTimes);

        if(unTimes == 5)
        {
            MainApp::GetInstance().ptrTimer->StopTimer(this, 1);
            MainApp::GetInstance().ptrAppSelect->RequestTransition(EApps::eAppSelect);
        }
    }
 
}