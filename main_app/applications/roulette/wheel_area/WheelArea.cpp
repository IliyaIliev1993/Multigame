#include "WheelArea.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerLifeRoulette = 1;

bool WheelArea::Init()
{
    if (!m_Ball.Init())
    {
        LOG_ERROR("Wheel Area - Failed to initialize Ball");
        return false;
    }

    if (!m_Wheel.Init())
    {
        LOG_ERROR("Wheel Area - Failed to initialize Wheel");
        return false;
    }

    std::function<void()> afterSpinningStoppedCallabck = [this]()
    {
        AfterSpinningStopped();
    };

    m_Ball.SetAfterSpinningStoppedCallback(afterSpinningStoppedCallabck);

    LOG_INFO("Wheel Area - Initialized ...");
    return true;
}

bool WheelArea::Deinit()
{
    /*Deinit Ball*/
    m_Ball.Deinit();

    /*Deinit Wheel*/
    m_Wheel.Deinit();

    LOG_WARN("Wheel Area - Deinitialized ...");
    return true;
}

bool WheelArea::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    return false;
}

void WheelArea::Draw()
{
    /*Draw Wheel*/
    m_Wheel.Draw();

    /*Draw Ball*/
    m_Ball.Draw();
}

void WheelArea::StartNewSpin()
{
    m_Ball.StartSpinning(RouletteMathLogic::GetInstance().GetWinningSector());
    m_Wheel.StartFastRotation();
}

void WheelArea::StartSlowRotation()
{
    m_Wheel.StartSlowRotation();
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerLifeRoulette, 1);
}

void WheelArea::StopSlowRotation()
{
    m_Wheel.StopSlowRotation();
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerLifeRoulette);
}

void WheelArea::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerLifeRoulette)
    {
        /*Set every frame communication between objects*/
        m_Ball.SetDegreesRoulette(m_Wheel.GetDegrees());
        m_Ball.SetSpeedRoulette(m_Wheel.GetSpeed());
    }
}

void WheelArea::AfterSpinningStopped()
{
    m_Wheel.DecrementToSlowRotation();
}