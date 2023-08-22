#include "AppSelect.h"

#include "utils/Utils.h"

AppSelect::AppSelect()
{
    LOGGER("AppSelect - Constructed ...");
}

AppSelect::~AppSelect()
{
    LOGGER("AppSelect - Distructed ...");
}

bool AppSelect::Init()
{

    LOGGER("AppSelect - Initialized ...");
    return true;
}

bool AppSelect::Deinit()
{
    LOGGER("AppSelect - Deinitialzied ...");
    return true;
}

void AppSelect::RegisterClient(IApp *client)
{
    m_vecAppClients.emplace_back(client);

    LOGGER("Registered client: ");
    LOGGER(client);
    LOGGER("AppSelect - Current size of AppClientsContainer: ");
    LOGGER(m_vecAppClients.size());
}

void AppSelect::UnregisterClient(IApp *client)
{
    for(auto it = m_vecAppClients.begin(); it != m_vecAppClients.end(); ++it)
    {
        if(*it == client)
        {
            m_vecAppClients.erase(it);

            LOGGER("Unregistered client: ");
            LOGGER(client);
            break;
        }
    }

    LOGGER("AppSelect - Current size of AppClientsContainer: ");
    LOGGER(m_vecAppClients.size());
}
