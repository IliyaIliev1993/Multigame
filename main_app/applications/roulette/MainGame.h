#pragma once

#include <string>

#include <main_app/IApp.h>

class Roulette : public IApp
{

private:

    std::string m_strAppName = "Roulette";

public:

    Roulette();

    bool Init() override;
    bool Deinit() override;
    bool OnTouch(unsigned int nX, unsigned int nY) override;
    const std::string& GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
};

