
// testView.h: интерфейс класса CtestView
//


#pragma once
#include "CMatrix.h"
#include "Resource.h"
#include "CaptureImage.h"
#include "AlterCords.h"
#include "СSunSystem.h"
#include "Lib.h"
#include "LibSurface.h"

#define DROW1 1
#define SURFACE1 2
#define LIGHT 3
#define DIFFUZE 4
#define ZERKALO 5
class CtestView : public CView
{
protected: // создать только из сериализации
	CtestView() noexcept;
	DECLARE_DYNCREATE(CtestView)

// Атрибуты
public:
	CtestDoc* GetDocument() const;
	POINT targetPoint;
	RECT targetArea;
	bool startSelected;
	double r, fi, q; // —ферические координаты точки наблюдени¤ в ћ— 
	//CRectD SRect;	// ќбласть изменеи¤ функции f(x,y) в ћ—  
	//CRect  WRect;	// ќбласть в окне дл¤ рисовани¤
	CRect WRect;
	int Index;	// »ндикатор дл¤ OnPaint
	CPlot3D  Graph1, Graph2, Graph3;	// ќбъ¤вление объектов типа CPlot3D

public:
	// Пирамида
	CMatrix VA, VB, VC, VD;	// Координаты вершин A,B,C,D пирамиды
	CMatrix PView;          // Координаты точки наблюдения
	CRect RS, RW;            // Область в мировых и оконных координатах - int
	int IsData, Rezult, IsRotateX, IsRotateY, IsRotateZ;
	double fx, fy, fz, dfi, dT, f0;      // Для вращения вокруг осей X, Y, Z
// Поверхность
	POINT** MasPOINT;
	int Nx, Ny;
	CRectD RD;
	pfunc2 pF;
	//  Сфера
	double Radius;
	CMatrix PSourceLight;
	double Ks;
	COLORREF Color;
	int TypeModel;
// Lab9
	int N_Bezier;
	CMatrix X, Y;
	CPlot2D Graph;
	CMyPen PenLine, PenAxis;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	afx_msg void OnLab1Multiply();
	afx_msg
		void OnRButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLab2CaptureScreenshot();
	afx_msg void OnLab2LoadBMP();
	afx_msg void OnLab3Sinx();
	//afx_msg void OnLab3X();
	afx_msg void OnLab3XCube();
	afx_msg void OnLab3SqrtXSinX();
	afx_msg void OnLab3XSquare();
	afx_msg void DrawSinX(CRect RW, int mode);
	afx_msg void DrawXCube(CRect RW, int mode);
	afx_msg void DrawSqrtXSinX(CRect RW, int mode);
	afx_msg void DrawXSquare(CRect RW, int mode);
	afx_msg void OnLab3All();
	afx_msg void OnLab4Solarsystem();
	afx_msg void OnLab6Function1();
	afx_msg void OnLab6Function2();
	afx_msg void OnLab6Function3();
	afx_msg void OnLab8Diffusesphere();
	afx_msg void OnLab8Mirrorsphere();
	afx_msg void OnLab9Bezier();
	afx_msg void OnLab9Lagr();
};

#ifndef _DEBUG  // версия отладки в testView.cpp
inline CtestDoc* CtestView::GetDocument() const
   { return reinterpret_cast<CtestDoc*>(m_pDocument); }
#endif

UINT ThreadLab4SolarSystem(LPVOID param);