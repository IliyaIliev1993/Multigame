#include "ReelsArea.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

bool ReelsArea::Init()
{

    /*Load textures*/
    m_textureReelsArea = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reels_area_clean.png");

    if(!m_textureReelsArea->Load())
    {
        LOG_ERROR("Reels Area - Unable to load texture reels area !");
        return false;
    }

    LOG_INFO("Reels Area - Initialized ...");
    return true;
}

bool ReelsArea::Deinit()
{
    LOG_INFO("Reels Area - Deinitialized ...");
    return true;
}

bool ReelsArea::HandleEvent()
{
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    return false;
}

void ReelsArea::Draw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    /*Draw Reels Area*/
    rend->DrawPicture(m_textureReelsArea, 25.0f, 0.0f);
}