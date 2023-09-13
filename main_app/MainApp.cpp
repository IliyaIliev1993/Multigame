#include "MainApp.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <debug/Logger.h>
#include <app_select/AppSelect.h>
#include <renderer/Renderer.h>


MainApp::MainApp() : ptrLogger(new Debug::Logger),
                     ptrRend(new Renderer),
                     ptrAppSelect(new AppSelect)
{

}

MainApp::~MainApp()
{

}

bool MainApp::Init()
{
    if(!ptrLogger->Init("Multigame"))
    {
        std::cout << "MainApp - Failed to initialize Logger !" << std::endl;
        return false;
    }

    if(!ptrRend->InitSystem("Multigame",
                                1920,
                                1080,
                                100))
    {
        LOG_ERROR("MainApp - Failed to initialize Renderer !");
        return false;
    }
    ptrRend->CreateAndFill2DBuffers();
    ptrRend->CreateAndFill3DBuffers();

    InitImgui();

    if(!ptrAppSelect->Init())
    {
        LOG_ERROR("MainApp - Failed to init AppSelect");
        return false;
    }

    LOG_INFO("MainApp - Initialized ...");
    return true;
}

void MainApp::InitImgui()
{
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(ptrRend->GetWindow(), true);
    ImGui::StyleColorsDark();
    ImGui::GetStyle().FrameRounding = 5.0f;
    ImGui::GetStyle().GrabRounding = 5.0f;
}

void MainApp::Run()
{
    while(!glfwWindowShouldClose(ptrRend->GetWindow()))
    {
        /* Debug New frame calculation */
        ImGui_ImplGlfwGL3_NewFrame();

        /* Handle Event TODO*/
        //ptrEventHandler->ProcessInput(ptrRenderer->GetWindow());

        /* Clear Color */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Here ...
        ptrAppSelect->OnDraw();

        //Help IMGUI
        if (m_bShowImguiHelp)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
            ImGui::ShowDemoWindow(&m_bShowImguiHelp);
        }

        /*Draw Imgui*/
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Draw */
        ptrRend->CallEventsAndSwapBuffers();
    }
}

bool MainApp::Deinit()
{
    ImGui::DestroyContext();
    ptrAppSelect->Deinit();
    ptrRend->Deinit();

    LOG_INFO("MainApp - Deinitialzied ...");
    return true;
}
