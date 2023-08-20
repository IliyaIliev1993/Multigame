#include "main_app/MainApp.h"

int main()
{
    MainApp::GetInstance().Init();
    MainApp::GetInstance().Run();
    MainApp::GetInstance().Deinit();

    return 0;
}
