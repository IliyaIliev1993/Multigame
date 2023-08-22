#pragma once

#include "main_app/IApp.h"

#include "utils/Utils.h"

class Roulette : public IApp
{

public:

    Roulette();

    bool Init() override;
    bool Deinit() override;
    bool OnTouch(unsigned int nX, unsigned int nY) override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
};

