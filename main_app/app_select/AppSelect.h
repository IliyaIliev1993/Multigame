#pragma once

#include <main_app/IApp.h>

#include <vector>

class AppSelect
{

private:

    /*Container, holding all the registered IApp objects*/
    std::vector<IApp*>m_vecAppClients;

public:

    bool Init();
    bool Deinit();
    void RegisterClient(IApp* client);
    void UnregisterClient(IApp* client);


};
