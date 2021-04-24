
// testView.cpp: реализация класса CtestView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "test.h"
#endif

#include "testDoc.h"
#include "testView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CMatrix.h"
#include "Resource.h"
#include "CaptureImage.h"
#include "AlterCords.h"
#include "СSunSystem.h"
#include "Lib.h"
#include "LibSurface.h"
#include "LibLabs3D.h"
// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LAB1_MULTIPLY, &CtestView::OnLab1Multiply)
	ON_COMMAND(ID_LAB2_CAPTURESCREENSHOT, &CtestView::OnLab2CaptureScreenshot)
	ON_COMMAND(ID_LAB2_LOADBMP, &CtestView::OnLab2LoadBMP)
	ON_COMMAND(ID_LAB3_SINX, &CtestView::OnLab3Sinx)
	ON_COMMAND(ID_LAB3_XCUBE, &CtestView::OnLab3XCube)
	ON_COMMAND(ID_LAB3_SQRTXSINX, &CtestView::OnLab3SqrtXSinX)
	ON_COMMAND(ID_LAB3_XSQUARE, &CtestView::OnLab3XSquare)
	ON_COMMAND(ID_LAB3_ALL, &CtestView::OnLab3All)
	ON_COMMAND(ID_LAB4_SOLARSYSTEM, &CtestView::OnLab4Solarsystem)
	ON_COMMAND(ID_LAB6_FUNCTION1, &CtestView::OnLab6Function1)
	ON_COMMAND(ID_LAB6_FUNCTION2, &CtestView::OnLab6Function2)
	ON_COMMAND(ID_LAB6_FUNCTION3, &CtestView::OnLab6Function3)
	ON_COMMAND(ID_LAB8_DIFFUSESPHERE, &CtestView::OnLab8Diffusesphere)
	ON_COMMAND(ID_LAB8_MIRRORSPHERE, &CtestView::OnLab8Mirrorsphere)
	ON_COMMAND(ID_LAB9_BEZIER, &CtestView::OnLab9Bezier)
	ON_COMMAND(ID_LAB9_LAGR, &CtestView::OnLab9Lagr)
END_MESSAGE_MAP()

// Создание или уничтожение CtestView

CtestView::CtestView() noexcept
{
	// TODO: добавьте код создания
	Index = 0;
	VA.RedimMatrix(4);
	VB.RedimMatrix(4);
	VC.RedimMatrix(4);
	VD.RedimMatrix(4);
	//PView.RedimMatrix(4);
	PView.RedimMatrix(3);
	PSourceLight.RedimMatrix(3);
	//VA(3)=VB(3)=VC(3)=VD(3)=PView(3)=1;
	VA(3) = VB(3) = VC(3) = VD(3) = 1;
	IsData = 0;
	MasPOINT = NULL;

}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CtestView

void CtestView::OnDraw(CDC* /*pf*/)
{

	CDC* dc = GetDC();
	CString ss;
	if (Index == 1)Graph1.Draw(*dc);
	if (Index == 2)Graph2.Draw(*dc);
	if (Index == 3)Graph3.Draw(*dc);
	if (Index == 4)
	{
		dc -> Rectangle(RW);
		DrawLightSphere(*dc, Radius, PView, PSourceLight, RW, Color, TypeModel);
	}
	if (Index == 5)
	{
		// Одна линия		
		PenLine.Set(PS_SOLID, 0, RGB(0, 0, 0));
		Graph.SetPenLine(PenLine);
		Graph.Draw(*dc, true);
		// Вторая линия линия		
		PenLine.Set(PS_SOLID, 2, RGB(255, 0, 0));
		Graph.SetPenLine(PenLine);
		Graph.DrawBezier(*dc, N_Bezier);
	}


	// TODO: добавьте здесь код отрисовки для собственных данных
}

void CtestView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	if ((Index == 1) || (Index == 2) || (Index == 3))
	{
		int dx = 50, dy = 50;
		if ((cx > 3 * dx) && (cy > 3 * dy))
		{
			CRect  WinRect;
			this->GetClientRect(WinRect);
			WinRect.DeflateRect(dx, dy);
			if (Index == 1)Graph1.SetWinRect(WinRect);
			if (Index == 2)Graph2.SetWinRect(WinRect);
			if (Index == 3)Graph3.SetWinRect(WinRect);
		}
	}
}

// Диагностика CtestView

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CtestView


void CtestView::OnLab1Multiply()
{
	CDC* wnd = GetDC();
	CMatrix A(3, 3);
	CMatrix B(3, 3);
	CMatrix V1(3);
	CMatrix V2(3);

	CMatrix C1(3, 3);
	CMatrix C2(3, 3);


	A(0, 0) = 1;
	A(0, 1) = 1.2;
	A(0, 2) = 1.3;
	A(1, 0) = 1.7;
	A(1, 1) = 2.4;
	A(1, 2) = 1.3;
	A(2, 0) = 5.3;
	A(2, 1) = 3.2;
	A(2, 2) = 7.9;
	
	B(0, 0) = 3.2;
	B(0, 1) = 4.2;
	B(0, 2) = 2.3;
	B(1, 0) = 3.2;
	B(1, 1) = 6.1;
	B(1, 2) = 3.2;
	B(2, 0) = 3;
	B(2, 1) = 3.2;
	B(2, 2) = 3.9;
	

	V1(0) = 1.3;
	V1(1) = 3.4;
	V1(2) = 0.1;

	V2(0) = 3.3;
	V2(1) = 3.7;
	V2(2) = 3.8;

	wnd->TextOutW(60, 10, L"A");
	
	A.PrintMatrix(*wnd, 10, 30);

	wnd->TextOutW(260, 10, L"B");
	B.PrintMatrix(*wnd, 210, 30);

	C1 = A + B;

	wnd->TextOutW(460, 10, L"A+B");
	C1.PrintMatrix(*wnd, 410, 30);

	C2 = A * B;

	wnd->TextOutW(660, 10, L"A*B");
	C2.PrintMatrix(*wnd, 610, 30);

	

	wnd->TextOutW(60, 130, L"V1");
	V1.PrintMatrix(*wnd, 10, 150);

	wnd->TextOutW(260, 130, L"V2");
	V2.PrintMatrix(*wnd, 210, 150);

	CMatrix D = A * V1;
	wnd->TextOutW(460, 130, L"A * V1");
	D.PrintMatrix(*wnd, 410, 150);

	CMatrix q = V1.Transp() * V2;
	CMatrix p = V1.Transp() * A* V2;

	wnd->TextOutW(10, 200, L"V1^T * V2");
	q.PrintMatrix(*wnd, 10, 220);

	wnd->TextOutW(210, 200, L"V1^T * A * V2");
	p.PrintMatrix(*wnd, 210, 220);


	CString buffer;
	buffer.Format(L"%.2lf", V1.ModVec());

	wnd->TextOutW(410, 200, L"|V1|");
	wnd->TextOutW(410, 220, buffer);

	buffer.Format(L"%.2lf", V1.ScalarMult(V2));

	wnd->TextOutW(610, 200, L"V1*V2 (scalar)");
	wnd->TextOutW(610, 220, buffer);

	//buffer.Format(L"%.2lf", V1.VectorMult(V2));

	wnd->TextOutW(30, 300, L"V1xV2 (vector)");
	//wnd->TextOutW(10, 320, buffer);
	V1.VectorMult(V2).PrintMatrix(*wnd, 10, 320);
	// TODO: добавьте свой код обработчика команд

	buffer.Format(L"%.2lf", V1.CosV1V2(V2));

	wnd->TextOutW(210, 300, L"cos(V1,V2)");
	wnd->TextOutW(210, 320, buffer);


	wnd->TextOutW(410, 300, L"V1 spherical to Decart");
	V1.SphereToCart().PrintMatrix(*wnd, 410, 320);
	




}



void CtestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	
	// TODO: Add your message handler code here and/or call default
	if (startSelected)
	{
		targetArea.bottom = point.y;
		targetArea.right = point.x;
		CDC* dc = GetDC();
		dc->SetDCPenColor(0x000000FF);
		dc->MoveTo(targetArea.left, targetArea.top);
		dc->LineTo(targetArea.right, targetArea.top);
		dc->MoveTo(targetArea.right, targetArea.top);
		dc->LineTo(targetArea.right, targetArea.bottom);
		dc->MoveTo(targetArea.right, targetArea.bottom);
		dc->LineTo(targetArea.left, targetArea.bottom);
		dc->MoveTo(targetArea.left, targetArea.bottom);
		dc->LineTo(targetArea.left, targetArea.top);
		ReleaseDC(dc);

		startSelected = false;
	}
	else
	{
		targetArea.top = point.y;
		targetArea.left = point.x;
		startSelected = true;
	}

}


void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	RedrawWindow();
	targetPoint = point;
	CDC* dc = GetDC();
	dc->Rectangle(targetPoint.x - 2, targetPoint.y - 2, targetPoint.x + 2, targetPoint.y + 2);
	ReleaseDC(dc);
}

void CtestView::OnLab2CaptureScreenshot()
{
	CCaptureImage CCapture;
	/*CRect Rect;
	Rect.top =0;
	Rect.bottom = 1000;
	Rect.left = 0;
	Rect.right = 1000;*/

	CCapture.CaptureScreen(targetArea);

	
}


void CtestView::OnLab2LoadBMP()
{
	CCaptureImage CCapture;
	CCapture.LoadImageFromExplorer();
	POINT p;
	//p = AwaitClick();
	CDC* dc = GetDC();
	CCapture.ShowImage(targetPoint.x,targetPoint.y,  dc);
	ReleaseDC(dc);

	
}

//const double pi = 3.14;
CMyPen pen = CMyPen();
CPlot2D plotter = CPlot2D();

void CtestView::DrawSinX(CRect RW, int mode)
{
	pen.Set(PS_SOLID, 1, RGB(255, 0, 0));

	CDC* dc = GetDC();
	int vecLength = 6 * pi / (pi / 36);
	plotter.SetPenLine(pen);

	CMatrix Y = CMatrix(vecLength);
	CMatrix X = CMatrix::RangeVector(-3 * pi, 3 * pi, pi / 36);
	for (int i = 0; i < vecLength - 1; i++)
	{
		Y(i) = sin(X(i)) / X(i);
	}

	CRect WndRect = RW;
	plotter.SetParams(X, Y, WndRect);

	CDoubleRect SpcRect = CDoubleRect(X.MinElement(), Y.MaxElement(), X.MaxElement(), Y.MinElement());
	plotter.SetRS(SpcRect);
	SetMyMode(*dc, SpcRect, WndRect, mode);
	plotter.Draw(*dc, false);

}
void CtestView::DrawXCube(CRect RW, int mode)
{

	pen.Set(PS_SOLID, 1, RGB(0, 255, 0));

	CDC* dc = GetDC();
	int vecLength = 10 / 0.25;
	plotter.SetPenLine(pen);


	pen.Set(PS_SOLID, 2, RGB(0, 0, 255));
	plotter.SetPenAxis(pen);

	CMatrix Y = CMatrix(vecLength);
	CMatrix X = CMatrix::RangeVector(-5, 5, 0.25);
	for (int i = 0; i < vecLength - 1; i++)
	{
		Y(i) = pow(X(i), 3);
	}

	CRect WndRect = RW;
	plotter.SetParams(X, Y, WndRect);

	CDoubleRect SpcRect = CDoubleRect(X.MinElement(), Y.MaxElement(), X.MaxElement(), Y.MinElement());
	plotter.SetRS(SpcRect);
	SetMyMode(*dc, SpcRect, WndRect, mode);
	plotter.Draw(*dc, true);
}
void CtestView::DrawSqrtXSinX(CRect RW, int mode)
{
	pen.Set(PS_SOLID, 3, RGB(255, 0, 0));

	CDC* dc = GetDC();
	int vecLength = 6 * pi / (pi / 36);
	plotter.SetPenLine(pen);

	CMatrix Y = CMatrix(vecLength);
	CMatrix X = CMatrix::RangeVector(0, 6*pi, pi/36);
	for (int i = 0; i < vecLength - 1; i++)
	{
		Y(i) = sqrt(X(i))*sin(X(i));
	}

	CRect WndRect = RW;
	plotter.SetParams(X, Y, WndRect);

	CDoubleRect SpcRect = CDoubleRect(X.MinElement(), Y.MaxElement(), X.MaxElement(), Y.MinElement());
	plotter.SetRS(SpcRect);
	SetMyMode(*dc, SpcRect, WndRect, mode);
	plotter.Draw(*dc, false);
}
void CtestView::DrawXSquare(CRect RW, int mode)
{
	pen.Set(PS_SOLID, 2, RGB(255, 0, 0));

	CDC* dc = GetDC();
	int vecLength = 20/0.25;
	plotter.SetPenLine(pen);
	
	pen.Set(PS_SOLID, 2, RGB(0, 0, 255));
	plotter.SetPenAxis(pen);

	CMatrix Y = CMatrix(vecLength);
	CMatrix X = CMatrix::RangeVector(-10, 10, 0.25);
	for (int i = 0; i < vecLength - 1; i++)
	{
		Y(i) = pow(X(i), 2);
	}

	CRect WndRect = RW;
	plotter.SetParams(X, Y, WndRect);

	CDoubleRect SpcRect = CDoubleRect(X.MinElement(), Y.MaxElement(), X.MaxElement(), Y.MinElement());
	plotter.SetRS(SpcRect);
	SetMyMode(*dc, SpcRect, WndRect, mode);
	plotter.Draw(*dc, true);
}
void CtestView::OnLab3Sinx()
{

	//DrawSinX(CRect(350, 150, 550, 350), MM_TEXT);
	RedrawWindow();
	DrawSinX(CRect(150, 50, 450, 350), MM_TEXT);


	// TODO: добавьте свой код обработчика команд
}


void CtestView::OnLab3XCube()
{
	RedrawWindow();
	//DrawXCube(CRect(350, 150, 550, 350), MM_ANISOTROPIC);
	DrawXCube(CRect(150, 50, 450, 350), MM_ANISOTROPIC);
	// TODO: добавьте свой код обработчика команд
}


void CtestView::OnLab3SqrtXSinX()
{
	RedrawWindow();
	DrawSqrtXSinX(CRect(150, 50, 450, 350), MM_TEXT);
	// TODO: добавьте свой код обработчика команд
}


void CtestView::OnLab3XSquare()
{
	RedrawWindow();
	//DrawXCube(CRect(350, 150, 550, 350), MM_ANISOTROPIC);
	DrawXSquare(CRect(150, 50, 450, 350), MM_TEXT);
	// TODO: добавьте свой код обработчика команд
}


void CtestView::OnLab3All()
{
	RedrawWindow();
	DrawSinX      (CRect(50, 5, 150, 105), MM_ANISOTROPIC);
	DrawXCube     (CRect(160, 50, 260, 155), MM_ANISOTROPIC);
	DrawSqrtXSinX (CRect(50, 70, 150, 170), MM_ANISOTROPIC);
	DrawXSquare	  (CRect(160, 120, 260, 220), MM_ANISOTROPIC);

	// TODO: добавьте свой код обработчика команд
}


void CtestView::OnLab4Solarsystem()
{	
	CDC* dc = GetDC();
	CWnd* wnd = this;
	//СSunSystem ss;

	//ss.DrawEndless(*dc);
	AfxBeginThread(ThreadLab4SolarSystem, (LPVOID)  wnd);

}

UINT ThreadLab4SolarSystem(LPVOID param)
{
	CWnd *wnd = (CWnd*)param;
	CDC *dc = wnd->GetDC();
	СSunSystem ss;
	ss.DrawEndless(*dc);

	return 0;
}


void CtestView::OnLab6Function1()
{
	// TODO: добавьте свой код обработчика команд
	double dx = 0.25, dy = 0.25;
	//double 
	r = 50, fi = 30, q = 45;
	CRectD SpaceRect(-5, 5, 5, -5);
	CRect  WinRect;
	this->GetClientRect(WinRect);
	WinRect.SetRect(WinRect.left + 50, WinRect.top + 50, WinRect.right - 50, WinRect.bottom - 50);
	Graph1.SetFunction(Function1, SpaceRect, dx, dy);	// Function1 	
	Graph1.SetViewPoint(r, fi, q);
	Graph1.SetWinRect(WinRect);
	Index = 1;
	this->Invalidate();
}


void CtestView::OnLab6Function2()
{
	// TODO: добавьте свой код обработчика команд
	double dx = 0.25, dy = 0.25;
	//double r=50, fi=0, q=45;
	r = 50, fi = 30, q = 45;
	CRectD SpaceRect(-5, 5, 5, -5);
	CRect  WinRect;
	this->GetClientRect(WinRect);
	WinRect.SetRect(WinRect.left + 50, WinRect.top + 50, WinRect.right - 50, WinRect.bottom - 50);
	Graph2.SetFunction(Function2, SpaceRect, dx, dy);  // Function2 	
	Graph2.SetViewPoint(r, fi, q);
	Graph2.SetWinRect(WinRect);
	Index = 2;
	this->Invalidate();
}


void CtestView::OnLab6Function3()
{
	// TODO: добавьте свой код обработчика команд
	double dx = 0.25, dy = 0.25;
	//double r=50, fi=0, q=45;
	r = 50, fi = 30, q = 45;
	CRectD SpaceRect(-10, 10, 10, -10);
	CRect  WinRect;
	this->GetClientRect(WinRect);
	WinRect.SetRect(WinRect.left + 50, WinRect.top + 50, WinRect.right - 50, WinRect.bottom - 50);

	Graph3.SetFunction(Function3, SpaceRect, dx, dy);	// Function3 
	Graph3.SetViewPoint(r, fi, q);
	Graph3.SetWinRect(WinRect);
	Index = 3;
	this->Invalidate();
}


void CtestView::OnLab8Diffusesphere()
{
	// TODO: добавьте свой код обработчика команд
	RW.SetRect(100, 50, 300, 250);					// Область в окне
	Radius = 20;
	PView(0) = 100;	PView(1) = 0;  PView(2) = 60;
	PSourceLight(0) = 100;  PSourceLight(1) = 0; PSourceLight(2) = 0;
	Color = RGB(255, 0, 0);
	Ks = 1.0;
	Index = 4;
	TypeModel = 0;
	InvalidateRect(NULL);
}


void CtestView::OnLab8Mirrorsphere()
{
	// TODO: добавьте свой код обработчика команд
	RW.SetRect(100, 50, 300, 250);					// Область в окне
	Radius = 20;
	PView(0) = 100;	PView(1) = 0;  PView(2) = 60;
	PSourceLight(0) = 100;  PSourceLight(1) = 0; PSourceLight(2) = 0;
	Color = RGB(255, 255, 0);
	Ks = 1.0;
	Index = 4;
	TypeModel = 1;
	InvalidateRect(NULL);
}


void CtestView::OnLab9Bezier()
{
	// TODO: добавьте свой код обработчика команд
	double dt = pi / 4;
	int N = 9;
	X.RedimMatrix(N);
	Y.RedimMatrix(N);
	//*
	for (int i = 0; i < N; i++)
	{
		X(i) = i * dt;
		Y(i) = sin(i * dt);
	}
	//*/


	/*
	X(0)=0;		X(1)=1;		X(2)=2;		X(3)=3;
	Y(0)=0;		Y(1)=1;		Y(2)=1;		Y(3)=0;

	X(4)=4;		X(5)=5;		X(6)=6;
	Y(4)=-1;	Y(5)=-1;	Y(6)=0;
*/
	CDoubleRect SpcRect = CDoubleRect(X.MinElement(), Y.MaxElement(), X.MaxElement(), Y.MinElement());
	Graph.SetRS(SpcRect);

	N_Bezier = 50;
	RW.SetRect(100, 50, 500, 350);
	Graph.SetParams(X, Y, RW);
	Index = 5;
	this->Invalidate();
}


void CtestView::OnLab9Lagr()
{
	// TODO: добавьте свой код обработчика команд
}
