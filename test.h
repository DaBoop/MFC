
// test.h: основной файл заголовка для приложения test
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CtestApp:
// Сведения о реализации этого класса: test.cpp
//

class CtestApp : public CWinApp
{
public:
	CtestApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtestApp theApp;
