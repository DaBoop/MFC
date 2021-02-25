#pragma once
#define NO_STRETCH -1

class CCaptureImage
{
private:
    HWND wnd = GetActiveWindow();
    HDC wnddc = GetDC(wnd);
    //RECT RcScreen;
    HBITMAP BMP;

public:

    CCaptureImage();
    bool CLoadImage(CString filename);
    bool LoadImageFromExplorer();
    //bool SaveImageFromExplorer();
    bool ShowImage(int X, int Y, CDC* dc, int Width = NO_STRETCH, int Height = NO_STRETCH);
    bool CaptureScreen(RECT& area);

    //bool CaptureRect(const CRect& rcCapture);
    
};
