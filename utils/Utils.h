#pragma once

#include <iostream>

template<typename T>
void LOGGER(T valueToBeLogged)
{
    std::cout << valueToBeLogged << std::endl;
}
