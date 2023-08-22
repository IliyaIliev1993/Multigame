#pragma once

#include "main_app/IApp.h"
#include <vector>

class AppSelect
{

private:

    AppSelect();

    /*Container, holding all the registered IApp objects*/
    std::vector<IApp*>m_vecAppClients;

public:

    ~AppSelect();

    static AppSelect& GetInstance()
    {
        static AppSelect appSelect;
        return appSelect;
    }

    AppSelect(const AppSelect& obj) = delete;
    void operator= (const AppSelect& obj) = delete;

    bool Init();
    bool Deinit();
    void RegisterClient(IApp* client);
    void UnregisterClient(IApp* client);


};
