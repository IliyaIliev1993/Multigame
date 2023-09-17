#include "MainGame.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
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
    LOG_INFO("Roulette - Transition to Application succeed");
}

void Roulette::OnExit()
{
    
}

void Roulette::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void Roulette::OnTick(unsigned int unID, unsigned int unTimes)
{

 
}