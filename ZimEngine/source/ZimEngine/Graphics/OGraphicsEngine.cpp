#include <ZimEngine/Graphics/OGraphicsEngine.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <tchar.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
    //dummy window
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = _T("ZimEngineDummyWindow");
    wc.lpfnWndProc = DefWindowProc;

    auto classId = RegisterClassEx(&wc);
    assert(classId);

    RECT rc = {0, 0, 1024, 768};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

    auto dummyWindow = CreateWindowEx(  
        NULL, 
        MAKEINTATOM(classId), 
        _T(""), 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        NULL,
        NULL,
        NULL,
        NULL
        );

    assert(dummyWindow);

    auto dummyDC = GetDC(dummyWindow); //get device context

    PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
    pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDesc.nVersion = 1;
    pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDesc.cColorBits = 32;
    pixelFormatDesc.cAlphaBits = 8;
    pixelFormatDesc.cDepthBits = 24;
    pixelFormatDesc.cStencilBits = 8;
    pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

    auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
    SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

    auto dummyContext = wglCreateContext(dummyDC);
    assert(dummyContext);

    wglMakeCurrent(dummyDC, dummyContext);

    if (!gladLoadWGL(dummyDC))
        throw std::runtime_error("OGraphicsEngine - Error - gladLoadWGL failed");

    if (!gladLoadGL())
        throw std::runtime_error("OGraphicsEngine - Error - gladLoadGL failed");

    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummyWindow, dummyDC);
    DestroyWindow(dummyWindow);


    
}

OGraphicsEngine::~OGraphicsEngine()
{
    
}

void OGraphicsEngine::clear(const OVec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);   
    glClear(GL_COLOR_BUFFER_BIT);
}

void OGraphicsEngine::setViewport(const ORect &size)
{
    glViewport(size.left, size.top, size.width, size.height);
}

OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferData& data)
{
    return std::make_shared<OVertexArrayObject>(data);
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}

void OGraphicsEngine::drawTriangles(ui32 vertexCount, ui32 offset)
{
    glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}