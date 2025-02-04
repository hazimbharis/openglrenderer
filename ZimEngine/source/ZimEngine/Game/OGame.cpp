#include <ZimEngine/Game/OGame.h>
#include <ZimEngine/Window/OWindow.h>
#include <windows.h>

OGame::OGame()
{
    m_display = new OWindow();
}

OGame::~OGame()
{
    delete m_display;
}

void OGame::run()
{
    MSG msg;
    while(m_isRunning && !m_display->IsClosed())
    {
        if(PeekMessage(&msg, NULL,NULL,NULL,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Sleep(1);
    }
}

void OGame::quit()
{
    m_isRunning = false;
}