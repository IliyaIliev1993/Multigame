#pragma once

#include <main_app/texture/Texture.h>

    struct Button
    {
        float fX = 0.0f;
        float fY = 0.0f;
        std::shared_ptr<Texture>textureButton = nullptr;
        bool IsHovered(const int& nXMouse, const int& nYMouse);
        bool IsPressed(const int& nXMouse, const int& nYMouse);
        bool IsPressAndHold(const int& nXMouse, const int& nYMouse);
        bool IsReleased(const int& nXMouse, const int& nYMouse);
    };