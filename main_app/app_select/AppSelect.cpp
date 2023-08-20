#include "AppSelect.h"

#include "utils/Utils.h"

AppSelect::AppSelect()
{
    LOGGER("AppSelect - Constructed ...");
}

AppSelect::~AppSelect()
{
    LOGGER("AppSelect - Distructed");
}

bool AppSelect::Init()
{

    LOGGER("AppSelect - Initialized");
    return true;
}

bool AppSelect::Deinit()
{
    LOGGER("AppSelect - Deinitialzied ...");
    return true;
}
