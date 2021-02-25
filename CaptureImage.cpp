#include "pch.h"
#include "Windows.h"
#include <cstring>
#include <tchar.h>
#include <string>
#include <vector>
#include "CaptureImage.h"



CCaptureImage::CCaptureImage()
{

}

bool CCaptureImage::CLoadImage(CString filename)
{
    //LPCWSTR str = filename.GetBuffer();
    BMP = (HBITMAP)LoadImage(NULL, filename,
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    // HBITMAP bmp = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //BMP = LoadBitmap(NULL, filename.GetBuffer());
    //BMP = LoadBitmap(GetModuleHandle(NULL), L"C:\\4sem\\CGG\\Labs\\Lab1MFC\\vappfp.bmp");
    if (BMP)
        return true;
    else false;
}
bool CCaptureImage::LoadImageFromExplorer()
{
    std::string fileName;
    CFileDialog dlgFile(TRUE, NULL, TEXT("*.bmp"), 6UL, TEXT("*.bmp"));
    int result = dlgFile.DoModal();
    if (result == IDOK)	
    {
       // CString str = dlgFile.GetPathName();
       // HBITMAP bmp = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (CLoadImage(dlgFile.GetPathName()))
            return true;
        else 
            return false;
    }
    else
    {
        return false;
    }
}
bool CCaptureImage::ShowImage(int X, int Y, CDC* dc, int Width, int Height)
{
    BITMAP bm;
    GetObject(BMP, sizeof(bm), &bm);
    int bmWidth = bm.bmWidth;
    int bmHeight = bm.bmHeight;

    HDC hdcTemp = CreateCompatibleDC(wnddc);
    SelectObject(hdcTemp, BMP);
    
    if ((Width == NO_STRETCH && Height == NO_STRETCH) || true ) // можно добавить StretchBlt, || true - забивка
    {
        BitBlt(wnddc, X+1, Y+1, bmWidth, bmHeight, hdcTemp, 0, 0, SRCCOPY);
		
		dc->SetDCPenColor(0x000000FF);
		dc->MoveTo(X, Y);
		dc->LineTo(X + bmWidth, Y);
		dc->MoveTo(X + bmWidth, Y);
		dc->LineTo(X + bmWidth, Y + bmHeight);
		dc->MoveTo(X + bmWidth, Y + bmHeight);
		dc->LineTo(X, Y + bmHeight);
		dc->MoveTo(X, Y + bmHeight);
		dc->LineTo(X, Y);
		

    }
    DeleteDC(hdcTemp);


    return true;
}

bool CCaptureImage::CaptureScreen(RECT& area)
{
    HDC dcDisplay = GetDC(wnd);
    HDC dcMemory = CreateCompatibleDC(dcDisplay);
	HBITMAP hBmp = CreateCompatibleBitmap(dcDisplay, //создание точечного рисунка
		abs(area.right - area.left),//модуль ширины рисунка
		abs(area.bottom - area.top));
	HBITMAP hOldBmp = (HBITMAP)SelectObject(dcMemory, hBmp); // Выбираем изображение bitmap в контекст памяти
	BitBlt(//рисуем изображение
		dcMemory, 0, 0, //в окне и в каких координатах в целевом рисунке
		abs(area.right - area.left), abs(area.bottom - area.top), //размеры изображения
		dcDisplay,
		area.left, area.top, //в окне и в каких координатах в исходном рисунке
		SRCCOPY);//копируем исходник(код растровой операции)


	hBmp = (HBITMAP)SelectObject(dcMemory, hOldBmp);// Восстанавливаем контекст памяти

	BITMAP bmp;
	BITMAPINFOHEADER bmpInfoHeader;//передаст структуру с инфой о изображении
	BITMAPFILEHEADER bmpFileHeader; //сюда запишем сам файл
	int colorDepth = 32; //глубина цвета

	GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp);// получаем объект

	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);//колличество байт необходимое структуре
	bmpInfoHeader.biWidth = bmp.bmWidth;//ширина
	bmpInfoHeader.biHeight = bmp.bmHeight;//высота
	bmpInfoHeader.biPlanes = 1;//колличество слоев для целевого устройства
	bmpInfoHeader.biBitCount = colorDepth; //колво битов на пиксел - глубина цвета
	bmpInfoHeader.biCompression = BI_RGB; //тип сжатия(смена формата, например на png или jpeg), тут без сжатия
	bmpInfoHeader.biSizeImage = 0; //размер изображения, для BI_RGB 0, тк без сжатия, если другой формат, то оно сожмет до заданного значения
	bmpInfoHeader.biXPelsPerMeter = 0; //разрешение в пикселях на метр целевого устройства для растрового изображения
	bmpInfoHeader.biYPelsPerMeter = 0;
	bmpInfoHeader.biClrUsed = 0; //Количество цветовых индексов в таблице цветов используемое. Если равно нулю, то юзает макс колво
	bmpInfoHeader.biClrImportant = 0; //Количество цветовых индексов, необходимых для отображения растрового изображения. Если  нуль, все цвета.

	DWORD dwBitSize = ((bmp.bmWidth * colorDepth + 31) / 32) *
		4 * bmp.bmHeight; //битовый размер
	DWORD dwDibSize = sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		dwBitSize;

	bmpFileHeader.bfType = ('M' << 8) | 'B'; //тип файла
	bmpFileHeader.bfSize = dwDibSize; //размер в байтах файла растрового изображения.
	bmpFileHeader.bfReserved1 = 0; //Зарезервированный
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		(DWORD)sizeof(BITMAPINFOHEADER); //Смещение в байтах от начала структуры к битам битовой карты.

	HANDLE hDib = GlobalAlloc(//выделяет глобальный блок памяти
		GHND, //Во все байты блока записываются нулевые значения и Заказывается перемещаемый блок памяти. Логический адрес перемещаемого блока памяти может изменяться
		dwBitSize + sizeof(BITMAPINFOHEADER));//выделяемый размер
	LPBITMAPINFOHEADER lpBmpInfoHeader = (LPBITMAPINFOHEADER)GlobalLock(hDib); //выделяем память под Структуру BITMAPINFOHEADER содержит информацию о размерах и цветовом формате DIB(BMP).
	*lpBmpInfoHeader = bmpInfoHeader;

	GetDIBits(//извлекает биты заданного совместимого точечного рисунка и копирует их в буфер как DIB
		dcMemory,
		hBmp,  // дескриптор рисунка
		0, // первая устанавливаемая строка развертки
		(UINT)bmp.bmHeight,  // число копируемых строк развертки
		(LPSTR)lpBmpInfoHeader + sizeof(BITMAPINFOHEADER), // массив для битов рисунка
		(BITMAPINFO*)lpBmpInfoHeader, // буфер данных рисунка
		DIB_RGB_COLORS);// индексы RGB или палитры




	CString fileName;
	CFileDialog dlgFile(FALSE, NULL, NULL, 6UL, TEXT("*.bmp"));
	int result = dlgFile.DoModal();
	if (result == IDOK)
	{
		// CString str = dlgFile.GetPathName();
		// HBITMAP bmp = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		fileName = dlgFile.GetPathName();
	}


	HANDLE hFile = CreateFile((LPCWSTR)fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось создать файл", L"Ошибка", MB_ICONSTOP);
		return 0;
	}

	DWORD dwWritten;

	WriteFile(hFile, // дескриптор файла
		(LPSTR)&bmpFileHeader, // буфер данных
		sizeof(BITMAPFILEHEADER),// число байтов для записи
		&dwWritten, // число записанных байтов
		NULL);// асинхронный буфер
	WriteFile(hFile, (LPSTR)lpBmpInfoHeader, dwDibSize,
		&dwWritten, NULL);

	GlobalUnlock(hDib);//Далее освобождение памяти
	GlobalFree(hDib);
	CloseHandle(hFile);

	ReleaseDC(wnd, dcDisplay);
	DeleteDC(dcMemory);

	if (dwWritten == 0)
	{
		MessageBox(NULL, L"Не удалось записать файл", L"Ошибка", MB_ICONSTOP);
		return 0;
	}
    return false;
}









/*
bool CCaptureImage::CaptureRect(const CRect& rcCapture)
{
    // destroy the currently contained bitmap to create a new one
    //Destroy();

    // create bitmap and attach it to this object 
    BMP = CreateCompatibleBitmap(wnddc, rcCapture.right - rcCapture.left, rcCapture.bottom - rcCapture.top);

    //Create(rcCapture.Width(), rcCapture.Height(), 32, 0);

    // create virtual screen DC
    CDC dcScreen;
    dcScreen.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

    GetObject(wnddc, sizeof(BITMAP), &BMP);

    // copy the contents from the virtual screen DC 
    BOOL bRet = ::BitBlt(wnddc, 0, 0, rcCapture.Width(), rcCapture.Height(),
        dcScreen.m_hDC, rcCapture.left, rcCapture.top,
        SRCCOPY | CAPTUREBLT);

    // do cleanup and return
    dcScreen.DeleteDC();
    ReleaseDC(wnd, wnddc);

    return bRet;
}
*/