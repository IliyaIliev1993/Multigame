#include "MainGame.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
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
    MainApp::GetInstance().ptrTimer->StartTimer(this, 1, 1000);
}

void KidsFantasy::OnExit()
{

}

void KidsFantasy::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    /*Draw Background*/
    rend->DrawPicture(m_textureBackground, 0.0f, 0.0f);
}

void KidsFantasy::OnTick(unsigned int unID, unsigned int unTimes)
{
    if(unID == 1)
    {
        LOG_INFO("Timer ID \"{0}\"", unID);
        LOG_INFO("Timer TIMES \"{0}\"", unTimes);

        if(unTimes == 3)
        {
            MainApp::GetInstance().ptrTimer->StopTimer(this, 1);
        }
    }
 
}