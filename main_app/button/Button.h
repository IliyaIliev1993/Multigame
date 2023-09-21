#pragma once

#include <string>
#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>

    struct Button
    {
        float fX = 0.0f;
        float fY = 0.0f;
        float fValue = 0.0f;
        bool bIsClicked = false;
        std::string strText = "";
        std::shared_ptr<Texture>textureButton = nullptr;
        std::shared_ptr<Font>fontButton = nullptr;
        bool IsHovered(const int& nXMouse, const int& nYMouse);
        bool IsPressed(const int& nXMouse, const int& nYMouse);
        bool IsPressAndHold(const int& nXMouse, const int& nYMouse);
        bool IsReleased(const int& nXMouse, const int& nYMouse);
    };