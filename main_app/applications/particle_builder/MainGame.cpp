#include "MainGame.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <debug/Logger.h>

ParticleBuilder::ParticleBuilder()
{
}

bool ParticleBuilder::Init()
{

    LOG_INFO("Particle Builder - Initialized ...");
    return true;
}

bool ParticleBuilder::Deinit()
{
    LOG_INFO("Roulette - Deinitalized ...");
    return true;
}

bool ParticleBuilder::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    /*Panel Handle Event*/
    if (MainApp::GetInstance().ptrPanel->HandleEvent())
    {
        return true;
    }

    /*If calculator or volume scene active, no handle event for MainGame*/
    if (MainApp::GetInstance().ptrPanel->GetPanelInfoScene() != EPanelInfoScenes::eNoInfoScene)
    {
        return false;
    }

    /*ENTER button*/
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter), false))
    {
        LOG_INFO("Roulette - ENTER Button Pressed");
        return true;
    }

    return false;
}

const std::string &ParticleBuilder::GetAppName()
{
    return m_strAppName;
}

void ParticleBuilder::OnEnter()
{
    MainApp::GetInstance().ptrPanel->LockBetButtons();
    LOG_INFO("Particle_Builder - Transition to Application succeed");
}

void ParticleBuilder::OnExit()
{
    LOG_INFO("Particle_Builder - Exit from Application");
}

void ParticleBuilder::OnDraw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void ParticleBuilder::OnTick(unsigned int unID, unsigned int unTimes)
{

}