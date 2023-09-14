#pragma once

#include <string>

#include <main_app/IApp.h>
#include <main_app/texture/Texture.h>

class KidsFantasy : public IApp
{

private:

    std::string m_strAppName = "Kids Fantasy";

    /*Texture main background*/
    std::shared_ptr<Texture>m_textureBackground;

public:

    KidsFantasy();

    bool Init() override;
    bool Deinit() override;
    bool HandleEvent() override;
    const std::string& GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
};