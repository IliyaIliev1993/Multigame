#include "MainApp.h"

#include <app_select/AppSelect.h>
#include <debug/Logger.h>

MainApp::MainApp() : ptrLogger(new Debug::Logger)
{

}

bool MainApp::Init()
{
    if(!ptrLogger->Init("Multigame"))
    {
        std::cout << "MainApp - Failed to initialize Logger !" << std::endl;
        return false;
    }

    if(!AppSelect::GetInstance().Init())
    {
        LOG_ERROR("MainApp - Failed to init AppSelect");
        return false;
    }

    LOG_INFO("MainApp - Initialized ...");
    return true;
}

void MainApp::Run()
{

}

bool MainApp::Deinit()
{
    if(!AppSelect::GetInstance().Deinit())
    {
        LOG_ERROR("MainApp - Failed to deinit AppSelect");
        return false;
    }

    LOG_INFO("MainApp - Deinitialzied ...");
    return true;
}
