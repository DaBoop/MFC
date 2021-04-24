
#include "pch.h"
#include "CMatrix.h"
#include "Windows.h"
#include <cstring>
#include <tchar.h>
#include <string>
#include <vector>
#include "AlterCords.h"

CMatrix CPlot2D::SpaceToWindow(CDoubleRect& rs, CRect& rw)
{
	CMatrix rez = CMatrix(3, 3);
	int spaceWidth = rs.right - rs.left;
	int wndWidth = rw.right - rw.left;
	double spaceHeight = abs(rs.top - rs.bottom);
	double wndHeight = abs(rw.top - rw.bottom);
	double kWidth = wndWidth / spaceWidth;
	double kHeight = wndHeight/ spaceHeight;

	rez(0, 0) = kWidth;
	rez(0, 1) = 0;
	rez(0, 2) = rw.left - kWidth * rs.left;
	rez(1, 0) = 0;
	rez(1, 1) = -kHeight;
	rez(1, 2) = rw.top + kHeight * rs.top;
	rez(2, 0) = 0;
	rez(2, 1) = 0;
	rez(2, 2) = 1;

	K = rez;
	return rez.Transp();
	// Транспонировать???
}

void SetMyMode(CDC& dc, CDoubleRect& rs, CRect& rw, int mode)
{
	int spaceWidth = rs.right - rs.left;
	int wndWidth = rw.right - rw.left;
	int spaceHeight = abs(rs.top - rs.bottom);
	int wndHeight = abs(rw.top - rw.bottom);

	dc.SetMapMode(mode);
	if (mode == MM_ANISOTROPIC)
	{
		dc.SetWindowExt(spaceWidth, spaceHeight); //МСК
		dc.SetWindowOrg(rs.left, rs.top);

		dc.SetViewportExt(wndWidth, -wndHeight); //ОСК
		dc.SetViewportOrg(rw.left, rw.top);
	}

}

void CPlot2D::SetParams(CMatrix& XX, CMatrix& YY, CRect& RWX)
{
	X.RedimMatrix(XX.rows(), XX.cols());
	Y.RedimMatrix(XX.rows(), XX.cols());
	X = XX;
	Y = YY;
	RW = RWX;
}

void CPlot2D::SetWindowRect(CRect& RWX)
{
	RW = RWX;
}

void CPlot2D::GetWindowCords(double xs, double ys, int& xw, int& yw)
{
	CMatrix SpcCord = CMatrix(3);
	SpcCord(0) = xs;
	SpcCord(1) = ys;
	SpcCord(2) = 1;

	CMatrix WndCord = CMatrix(3);

	WndCord = (K * SpcCord);

	xw = WndCord(0);
	yw = WndCord(1);

}

void CPlot2D::SetPenLine(CMyPen& PLine)
{
	PenLine = PLine;
}

void CPlot2D::SetPenAxis(CMyPen& PAxis)
{
	PenAxis = PAxis;
}

void CPlot2D::Draw(CDC& dc, bool DrawAxes)
{
	int XW, YW;
	CPen CPenLine(PenLine.PenStyle, PenLine.PenWidth, PenLine.PenColor);
	dc.SelectObject(CPenLine);

	dc.MoveTo(X(0), Y(0));
	for (int i = 1; i < min(X.rows(), Y.rows()) - 1; i++)
	{
		dc.LineTo(X(i), Y(i));
		dc.MoveTo(X(i), Y(i));
	}

	CPen CPenAxis(PenAxis.PenStyle, PenAxis.PenWidth, PenAxis.PenColor);
	dc.SelectObject(CPenAxis);
	if (DrawAxes)
	{
		XW = RS.left;
		YW = RS.top;
		dc.MoveTo(XW, YW);

		XW = RS.right;
		YW = RS.top;
		dc.LineTo(XW, YW);

		XW = RS.left;
		YW = RS.top;
		dc.MoveTo(XW, YW);

		XW = RS.left;
		YW = RS.bottom;
		dc.LineTo(XW, YW);
	}

	CPenAxis.DeleteObject();
	CPenLine.DeleteObject();
}

void CPlot2D::DrawWnd(CDC& dc, bool DrawAxes)
{
	
	int XW, YW;
	SpaceToWindow(RS, RW);
	//K.PrintMatrix(dc, 200, 200);
	//K.Transp().PrintMatrix(dc, 400, 200);
	GetWindowCords(X(0), Y(0), XW, YW);
	dc.MoveTo(XW, YW);

	//SetDCPenColor(dc,PenLine.PenColor);
	//SetDCPenStyle(dc,PenLine.PenColor);
	//CPen CPenLine = CPen();
	//CPenLine.CreatePen(PenLine.PenStyle, PenLine.PenWidth, PenLine.PenColor);
	CPen CPenLine(PenLine.PenStyle, PenLine.PenWidth, PenLine.PenColor);
	dc.SelectObject(CPenLine);
	for (int i = 1; i < min(X.rows() - 1, Y.rows()) - 1; i++)
	{
		GetWindowCords(X(i), Y(i), XW, YW);
		dc.LineTo(XW, YW);
		dc.MoveTo(XW, YW);
	}

	CPen CPenAxis(PenAxis.PenStyle, PenAxis.PenWidth, PenAxis.PenColor);
	dc.SelectObject(CPenAxis);
	if (DrawAxes)
	{
		XW = RW.left;
		YW = RW.top;
		dc.MoveTo(XW,YW);

		XW = RW.right;
		YW = RW.top;
		dc.LineTo(XW, YW);

		XW = RW.left;
		YW = RW.top;
		dc.MoveTo(XW, YW);

		XW = RW.left;
		YW = RW.bottom;
		dc.LineTo(XW, YW);
	}

	CPenAxis.DeleteObject();
	CPenLine.DeleteObject();
}

void CPlot2D::SetRS(CDoubleRect & RS)
{

	this->RS = RS;
}

void CPlot2D::DrawBezier(CDC& dc, int NT)
// Рисует кривую Безье по набору опорных точек
// Массив опорных точек: [X(0),Y(0)], [X(1),Y(1)],...
// dc - ссылка на класс CDC MFC
// NT - число отрезков по параметру t
{	
	SpaceToWindow(RS, RW);
	double xs, ys;  // мировые  координаты точки
	int xw, yw;     // оконные координаты точки
	CPen MyPen(PenLine.PenStyle, PenLine.PenWidth, PenLine.PenColor);
	CPen* pOldPen = dc.SelectObject(&MyPen);
	double dt = 1.0 / NT;
	int N = X.rows();
	CMatrix RX(N), RY(N);
	xs = X(0);   ys = Y(0);
	GetWindowCords(xs, ys, xw, yw);
	dc.MoveTo(xw, yw);
	for (int k = 1; k <= NT; k++)
	{//***
		double t = k * dt;
		for (int i = 0; i < N; i++)
		{
			RX(i) = X(i);
			RY(i) = Y(i);
		}
		for (int j = N - 1; j > 0; j--)
		{
			for (int i = 0; i < j; i++)
			{
				RX(i) = RX(i) + t * (RX(i + 1) - RX(i));
				RY(i) = RY(i) + t * (RY(i + 1) - RY(i));
			}
		}
		xs = RX(0);   ys = RY(0);
		GetWindowCords(xs, ys, xw, yw);
		dc.LineTo(xw, yw);
	}//***
	dc.SelectObject(pOldPen);
}

