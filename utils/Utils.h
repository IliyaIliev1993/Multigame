#pragma once

#include <iostream>

/*LOGGER Method*/
static bool g_bEnableLogging = true;

template<typename T>
void LOGGER(T valueToBeLogged)
{
    if(!g_bEnableLogging)
    {
        return;
    }

    std::cout << valueToBeLogged << std::endl;
}
