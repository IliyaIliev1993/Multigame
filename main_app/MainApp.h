#pragma once

#include <iostream>
#include <memory>

namespace Debug
{
    class Logger;
}

/*MainApp class, used for control the flow of the app.*/
class MainApp
{

private:

    MainApp();
    ~MainApp() = default;

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

    std::unique_ptr<Debug::Logger> ptrLogger;

    bool Init();
    void Run();
    bool Deinit();

};
