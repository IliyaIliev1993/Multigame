#include "MainGame.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/kids_fantasy/math_logic/MathLogic.h>
#include <debug/Logger.h>


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

    /*MathLogic Init*/
    if(!MathLogic::GetInstance().Init())
    {
        LOG_ERROR("Kids Fantasy - Unable to Init Math Logic !");
        return false;
    }

    /*Reels Area Init*/
    if(!m_reelsArea.Init())
    {
        LOG_ERROR("Kids Fantasy - Unable to Init Reels Area !");
        return false;
    }

    LOG_INFO("Kids Fantasy - Initialized ...");
    return true;
}

bool KidsFantasy::Deinit()
{
    /*Reels Area Deinit*/
    m_reelsArea.Deinit();

    /*Math Logic Deinit*/
    MathLogic::GetInstance().Deinit();

    LOG_INFO("Kids Fantasy - Deinitialized ...");
    return true;
}

bool KidsFantasy::HandleEvent()
{
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    /*Reels Area Handle Event*/
    m_reelsArea.HandleEvent();

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

    /*Draw ReelsArea*/
    m_reelsArea.Draw();

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void KidsFantasy::OnTick(unsigned int unID, unsigned int unTimes)
{
 
}