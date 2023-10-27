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
    /*Reserve 10 textures*/
    m_vecTexturesParticle.reserve(10);

    /*Load Textures and insert into container*/
    auto textureSun = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_sun.png");
    auto textureStar = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_star.png");
    auto textureFlower = Texture::CreateTexture("../src/resources/particle_builder/particles/flower_particle.png");
    auto textureSmoke = Texture::CreateTexture("../src/resources/particle_builder/particles/smoke_particle.png");

    m_vecTexturesParticle.emplace_back(textureSun);
    m_vecTexturesParticle.emplace_back(textureStar);
    m_vecTexturesParticle.emplace_back(textureFlower);
    m_vecTexturesParticle.emplace_back(textureSmoke);

    for (auto &texture : m_vecTexturesParticle)
    {
        if (!texture->Load())
        {
            LOG_ERROR("Particle Builder - Unable to load texture \"{0}\" !", texture->GetPath());
            return false;
        }
    }

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
    MainApp::GetInstance().ptrPanel->HideFields();
    LOG_INFO("Particle_Builder - Transition to Application succeed");
}

void ParticleBuilder::OnExit()
{
    MainApp::GetInstance().ptrPanel->ShowFields();
    LOG_INFO("Particle_Builder - Exit from Application");
}

void ParticleBuilder::DrawMainMenu()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Main menu window flags*/
    ImGuiWindowFlags mainMenuFlags = 0;
    mainMenuFlags |= ImGuiWindowFlags_NoMove;
    mainMenuFlags |= ImGuiWindowFlags_NoResize;
    mainMenuFlags |= ImGuiWindowFlags_MenuBar;

    /*Set position and size*/
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(520, 920), ImGuiCond_FirstUseEver);

    /*Actual window*/
    ImGui::Begin("Particle Builder", &m_bMainMenuFlag, mainMenuFlags);

    /*Actual Menu*/
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Create New ..."))
            {
                if (ImGui::MenuItem("Particle"))
                {
                    m_bCreateNewParticle = true;
                }

                ImGui::EndMenu();
            }

            ImGui::Separator();
            ImGui::MenuItem("Exit");

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    /*Popup create new particle*/
    if (m_bCreateNewParticle)
    {
        ImGui::OpenPopup("Create New Particle");
    }

    if (ImGui::BeginPopupModal("Create New Particle", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static unsigned int unCounterDefaultName = 0;
        std::string strName = "Particle_" + std::to_string(unCounterDefaultName);

        /*Text Buff*/
        static char arrText[64] = "Particle_";
        ImGui::Text("Name:");
        ImGui::InputText(std::to_string(unCounterDefaultName).c_str(), arrText, m_unTextBuff);

        ImGui::Separator();

        ImGui::Text("Textures:");
        ImGui::Separator();

        /*Draw Textures*/
        const unsigned int unTexturesPerRow = 3;
        unsigned int unCounterRow = 0;
        for (auto texture : m_vecTexturesParticle)
        {
            const float fWSize = 75;
            const float fHSize = 75;
            ImTextureID imguiTexture = (void *)(size_t)texture->GetTextureID();
            bool bButtonPressed = ImGui::ImageButton(imguiTexture, ImVec2(fWSize, fHSize));

            /*If pressed, insert object into container*/
            if (bButtonPressed)
            {
                strName = arrText;
                if (strName.empty())
                {
                    strName = "Particle_" + std::to_string(unCounterDefaultName);
                }

                ParticleSystem particleObject;
                particleObject.Init(texture, {rend->SCREEN_WIDTH / 2, rend->SCREEN_HEIGHT / 2});

                m_mapParticles.insert(std::make_pair(strName, particleObject));

                auto itLast = --m_mapParticles.end();
                itLast->second.StartEmitting();

                ++unCounterDefaultName;
                m_bCreateNewParticle = false;
                ImGui::CloseCurrentPopup();
            }
            ++unCounterRow;

            if (unCounterRow < unTexturesPerRow)
            {
                ImGui::SameLine();
            }
            else
            {
                unCounterRow = 0;
            }
        }

        ImGui::Separator();

        if (ImGui::Button("Cancel", ImVec2(130, 0)))
        {
            m_bCreateNewParticle = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

void ParticleBuilder::OnDraw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Particles*/
    for (auto &particle : m_mapParticles)
    {
        particle.second.Draw();
    }

    /*Draw Main Menu*/
    DrawMainMenu();

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void ParticleBuilder::OnTick(unsigned int unID, unsigned int unTimes)
{
}