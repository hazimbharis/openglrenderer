#include <ZimEngine/Game/OGame.h>
#include <ZimEngine/Window/OWindow.h>   
#include <ZimEngine/Graphics/OGraphicsEngine.h>
#include <windows.h>
#include <ZimEngine/make_unique.h>

OGame::OGame()
{
    m_graphicsEngine = std::make_unique<OGraphicsEngine>();
    m_display = std::make_unique<OWindow>(); // im supposed to make this a unique type pointer but whatever, ill deal with that later

    m_display->makeCurrentContext();
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
}

void OGame::onUpdate()
{
    m_graphicsEngine->clear(OVec4(1,0,0,1));

    m_display->present(false);
}

void OGame::onQuit()
{
}

void OGame::run()
{
    onCreate();

    MSG msg;
    while(m_isRunning)
    {
        msg = {};
        if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_isRunning = false;
                continue;
            }
            else 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        onUpdate();
    }

    onQuit();
}

void OGame::quit()
{
    m_isRunning = false;
}