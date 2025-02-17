#pragma once
#include <memory>
#include <ZimEngine/OPrerequisites.h>

class OGraphicsEngine;
class OWindow;
class OGame
{
public:
    OGame();
    ~OGame();

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onQuit();

    void run();
    void quit();
protected:
    bool m_isRunning = true;
    std::unique_ptr<OWindow> m_display;
    std::unique_ptr<OGraphicsEngine> m_graphicsEngine;

    OVertexArrayObjectPtr m_triangleVAO;
};