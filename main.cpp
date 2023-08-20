#include "utils/Utils.h"
#include "main_app/MainApp.h"

int main()
{
    if(!MainApp::GetInstance().Init())
    {
        LOGGER("main - Failed to init MainApp");
        return -1;
    }

    MainApp::GetInstance().Run();
    MainApp::GetInstance().Deinit();

    return 0;
}
