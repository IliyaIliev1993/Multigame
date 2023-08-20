#include "MainApp.h"
#include "utils/Utils.h"

MainApp::MainApp()
{
    LOGGER("MainApp - constructed ...");
}

MainApp::~MainApp()
{
    LOGGER("MainApp - distrucred ...");
}

bool MainApp::Init()
{

    LOGGER("MainApp - Initialized");
    return true;
}

void MainApp::Run()
{

}

bool MainApp::Deinit()
{

    LOGGER("MainApp - Deinitialzied ...");
    return true;
}
