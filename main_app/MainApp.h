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

    MainApp(const MainApp& copyObj) = delete;

    void operator=(const MainApp& copyObj) = delete;

    bool Init();

    void Run();

    bool Deinit();

};
