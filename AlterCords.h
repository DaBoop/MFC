#pragma once
#include "pch.h"
#include "CMatrix.h"
#include "Windows.h"
#include <cstring>
#include <tchar.h>
#include <string>
#include <vector>



struct CMyPen
{
	int PenStyle;		// Стиль пера
	int PenWidth;		// Толщина пера 
	COLORREF PenColor;	// Цвет пера 
	CMyPen() { PenStyle = PS_SOLID; PenWidth = 1; PenColor = RGB(0, 0, 0); };
	void Set(int PS, int PW, COLORREF PC)
	{
		PenStyle = PS; PenWidth = PW; PenColor = PC;
	};
};

class CDoubleRect
{

public:
	double left;
	double top;
	double right;
	double bottom;
	CDoubleRect(
		_In_ double l,
		_In_ double t,
		_In_ double r,
		_In_ double b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	CDoubleRect() {}
};


void SetMyMode(CDC& dc, CDoubleRect& RS, CRect& RW, int mode);

class CPlot2D
{
	CMatrix X;				// Аргумент
	CMatrix Y;				// Функция
	CMatrix K;				// Матрица пересчета коорднат
	CRect RW;				// Прямоугольник в окне
	CDoubleRect RS;				// Прямоугольник области в МСК
	CMyPen PenLine;                         // Перо для линий
	CMyPen PenAxis;                        // Перо для осей
public:
	CPlot2D() { K.RedimMatrix(3, 3); };          //Конструктор по умолчанию
	void SetParams(CMatrix& XX, CMatrix& YY, CRect& RWX); // Установка
																								 // параметров графика
	void SetWindowRect(CRect& RWX);	//Установка области в окне для отображения 
																			//графика
	void GetWindowCords(double xs, double ys, int& xw, int& yw); //Пересчет
																		   //координаты точки из МСК в оконную СК
	void SetPenLine(CMyPen& PLine);	// Перо для рисования графика
	void SetPenAxis(CMyPen& PAxis);	// Перо для осей координат
	void Draw(CDC& dc, bool drawAxes);	// Рисование с самостоятельным пересчетом
//координат
	void DrawWnd(CDC& dc, bool drawAxes); // Рисование с БЕЗ самостоятельного 
																			 //пересчета координат
	void SetRS(CDoubleRect& RS);
	CMatrix SpaceToWindow(CDoubleRect& rs, CRect& rw);
	void DrawBezier(CDC& dc, int NT);
};
