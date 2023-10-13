#pragma once

#include <main_app/texture/Texture.h>

class TableArea
{
private:

    /*Texture Table Bets*/
    std::shared_ptr<Texture> m_textureTableBets;

public:
    bool Init();
    bool Deinit();
    void Draw();
};