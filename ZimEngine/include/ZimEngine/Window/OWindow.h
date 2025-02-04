#pragma once

class OWindow
{
public:
    OWindow();
    ~OWindow();

    void OnDestroy();
    bool IsClosed();
private:
    void* m_handle = nullptr;
};