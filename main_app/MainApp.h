#pragma once
#include <memory>

namespace Debug
{
    class Logger;
}
class AppSelect;
class Renderer;
class TimerMgr;

/*MainApp class, used for control the flow of the app.*/
class MainApp
{

private:

    bool m_bShowImguiHelp = true;

    MainApp();
    ~MainApp();

    void InitImgui();

public:

    static MainApp& GetInstance()
    {
        static MainApp mainApp;
        return mainApp;
    }

    /** Delete copyt-constructor, move-constructor and assignment operators */
    MainApp(MainApp const&) = delete;
    void operator = (MainApp const&) = delete;
    MainApp(MainApp &&) = delete;
    void operator = (MainApp &&) = delete;

    /*Unique pointers global objects to main classes*/
    std::unique_ptr<Debug::Logger> ptrLogger;
    std::unique_ptr<AppSelect> ptrAppSelect;
    std::unique_ptr<Renderer>ptrRend;
    std::unique_ptr<TimerMgr>ptrTimer;

    bool Init();
    void Run();
    bool Deinit();

};
