#include "AppSelect.h"

#include <debug/Logger.h>

bool AppSelect::Init()
{

    LOG_INFO("AppSelect - Initialized ...");
    return true;
}

bool AppSelect::Deinit()
{
    LOG_INFO("AppSelect - Deinitialzied ...");
    return true;
}

void AppSelect::RegisterClient(IApp *client)
{
    m_vecAppClients.emplace_back(client);

    LOG_INFO("AppSelect - Registered client : \"{0}\"", client->GetAppName());
    LOG_INFO("AppSelect - Current size of AppClientsContainer: \"{0}\"", m_vecAppClients.size());
}

void AppSelect::UnregisterClient(IApp *client)
{
    for(auto it = m_vecAppClients.begin(); it != m_vecAppClients.end(); ++it)
    {
        if(*it == client)
        {
            LOG_INFO("AppSelect - Unregistered client : \"{0}\"", client->GetAppName());
            m_vecAppClients.erase(it);
            break;
        }
    }

    LOG_INFO("AppSelect - Current size of AppClientsContainer: \"{0}\"", m_vecAppClients.size());
}
