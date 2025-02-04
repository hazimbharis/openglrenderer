#include <ZimEngine/Window/OWindow.h> 
#include <Windows.h>
#include <tchar.h>
#include <assert.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_DESTROY:
    {
        OWindow* window = (OWindow*) GetWindowLongPtr(hwnd,GWLP_USERDATA);
        window->OnDestroy();
        break;
    }
    default:
        return DefWindowProc(hwnd,msg,wParam,lParam);
    }

    return NULL;
}

OWindow::OWindow()
{
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = _T("ZimEngineWindow");
    wc.lpfnWndProc = DefWindowProc;

    RegisterClassEx(&wc);

    RECT rc = {0, 0, 1024, 768};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

    m_handle = CreateWindowEx(
        NULL, 
        _T("ZimEngineWindow"), 
        _T("ZimEngine"), 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        rc.right - rc.left, 
        rc.bottom - rc.top,
        NULL,
        NULL,
        NULL,
        NULL
        );

    assert(m_handle);

    SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow((HWND) m_handle, SW_SHOW);
    UpdateWindow((HWND) m_handle);
}

OWindow::~OWindow()
{
    DestroyWindow((HWND) m_handle);
}

void OWindow::OnDestroy()
{
    m_handle = nullptr;
}

bool OWindow::IsClosed()
{
    return !m_handle;
}