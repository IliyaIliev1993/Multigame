#include "MainApp.h"
#include "app_select/AppSelect.h"
#include "utils/Utils.h"

MainApp::MainApp()
{
    LOGGER("MainApp - Constructed ...");
}

MainApp::~MainApp()
{
    LOGGER("MainApp - Distrucred ...");
}

bool MainApp::Init()
{
    if(!AppSelect::GetInstance().Init())
    {
        LOGGER("MainApp - Failed to init AppSelect");
        return false;
    }

    LOGGER("MainApp - Initialized ...");
    return true;
}

void MainApp::Run()
{

}

bool MainApp::Deinit()
{
    if(!AppSelect::GetInstance().Deinit())
    {
        LOGGER("MainApp - Failed to deinit AppSelect");
        return false;
    }

    LOGGER("MainApp - Deinitialzied ...");
    return true;
}
