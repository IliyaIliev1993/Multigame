#pragma once

#include <iostream>

/*MainApp class, used for control the flow of the app.*/
class MainApp
{

private:

    MainApp();

public:

    ~MainApp();

    static MainApp& GetInstance()
    {
        static MainApp mainApp;
        return mainApp;
    }

    MainApp(const MainApp& obj) = delete;
    void operator= (const MainApp& obj) = delete;

    bool Init();

    void Run();

    bool Deinit();

};
