#include "MainGame.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

#include <iostream>

KidsFantasy::KidsFantasy()
{

}

bool KidsFantasy::Init()
{

    /*Load textures*/
    m_textureBackground = Texture::CreateTexture("../src/resources/kids_fantasy/kids_fantasy_background.png");

    if(!m_textureBackground->Load())
    {
        LOG_ERROR("KidsFantasy - Unable to load texture background !");
        return false;
    }

    LOG_INFO("Kids Fantasy - Initialized ...");
    return true;
}

bool KidsFantasy::Deinit()
{
    return true;
}

bool KidsFantasy::HandleEvent()
{
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    return false;
}

const std::string& KidsFantasy::GetAppName()
{
    return m_strAppName;
}

void KidsFantasy::OnEnter()
{
    LOG_INFO("Kids Fantasy - Transition to Application succeed");
}

void KidsFantasy::OnExit()
{
    LOG_INFO("Kids Fantasy - Exit from Application");
}

void KidsFantasy::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    /*Draw Background*/
    rend->DrawPicture(m_textureBackground, 0.0f, 0.0f);

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void KidsFantasy::OnTick(unsigned int unID, unsigned int unTimes)
{
 
}