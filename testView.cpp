
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
// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LAB1_MULTIPLY, &CtestView::OnLab1Multiply)
	ON_COMMAND(ID_LAB2_CAPTURESCREENSHOT, &CtestView::OnLab2CaptureScreenshot)
	ON_COMMAND(ID_LAB2_LOADBMP, &CtestView::OnLab2LoadBMP)
END_MESSAGE_MAP()

// Создание или уничтожение CtestView

CtestView::CtestView() noexcept
{
	// TODO: добавьте код создания

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

void CtestView::OnDraw(CDC* /*pDC*/)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
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
