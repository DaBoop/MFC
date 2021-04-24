#include "pch.h"
#include "СSunSystem.h"
#include "Lib.h"

СSunSystem::СSunSystem()
{
	SetPlanetsSpeed();
	SetDT();
	
	fiE = 0;
	fiM = 0;
	fiMars = 0;
	
	double rS = 30, rE = 20, rM = 10, rMars = 25;       // Радиус Солнца, Земли, Луны
	double RE = 10 * rS, RM = 5 * rE, RMars = 18*rMars;		  // Радиус орбиты Земли и Луны

	Sun = CRect(-rS, rS, rS, -rS);
	Earth = CRect(-rE, rE, rE, -rE);
	Moon = CRect(-rM, rM, rM, -rM);
	Mars = CRect(-rMars, rMars, rMars, -rMars);

	double d = RE + RM + MarsR;

	RW = CRect(100, 50, 450, 400);
	RS = CRectD(-d, -d, d, d);
	EarthOrbit = CRect(-RE, RE, RE, -RE);
	MoonOrbit = CRect(-RM, RM, RM, -RM);
	MarsOrbit = CRect(-RMars, RMars, RMars, -RMars);
	
	ECoords.RedimMatrix(3);
	double ff = (fiE / 180.0) * pi;	  
	ECoords(0) = RE * cos(ff);
	ECoords(1) = RE * sin(ff);
	ECoords(2) = 1;

	ff = (fiM / 180.0) * pi;
	MCoordsEarth.RedimMatrix(3);
	MCoordsEarth(0) = RM * cos(ff);
	MCoordsEarth(1) = RM * sin(ff);
	MCoordsEarth(2) = 1;



	MCoordsSun.RedimMatrix(3);
	MCoordsSun(0) = ECoords(0) + MoonOrbit.left;
	MCoordsSun(1) = ECoords(1) + MoonOrbit.left;
	MCoordsSun(2) = 1;

	MarsCoords.RedimMatrix(3);
	ff = (fiMars / 180.0) * pi;
	MarsCoords(0) = RMars * cos(ff);
	MarsCoords(1) = RMars * sin(ff);
	MarsCoords(2) = 1;

	dfiE = wEarth * dt;
	dfiM = wMoon * dt;
	dfiMars = wMars * dt;

	PE.RedimMatrix(3, 3);
	PM.RedimMatrix(3, 3);
	PMars.RedimMatrix(3, 3);
	PE = CreateRotate2D(dfiE);	// Матрица поворота против часовой стрелки Луны и Земли
	PM = CreateRotate2D(dfiM);	// Матрица поворота против часовой стрелки Луны
	PMars = CreateRotate2D(-dfiMars);	// Матрица поворота против часовой стрелки Луны

}

void СSunSystem::SetNewCoords()
{
	double x1 = MCoordsEarth(0);
	double y1 = MCoordsEarth(1);
	MCoordsEarth = PM * MCoordsEarth;
	x1 = MCoordsEarth(0);
	y1 = MCoordsEarth(1);

	double x = ECoords(0);  double y = ECoords(1);
	CMatrix P = CreateTranslate2D(x, y);   
	MCoordsSun = P * MCoordsEarth;	
	
	//Для дебага
	x1 = MCoordsEarth(0); 
	y1 = MCoordsEarth(1);
	double x2 = MCoordsSun(0);
	double y2 = MCoordsSun(1);
	// ===


	MCoordsSun = PE * MCoordsSun;	  
	ECoords = PE * ECoords;		  
	MarsCoords = PMars * MarsCoords;		  
}


CRectD СSunSystem::GetRS()
{
	return CRectD();
}


void СSunSystem::Draw(CDC& dc)
{
	//SetMyMode(dc, CRect(0, 0, 500, 500), CRect(0,0,500,500), MM_ANISOTROPIC);
	CBrush SBrush, EBrush, MBrush, MarsBrush, * pOldBrush;
	CRect R;
	
	dc.SelectStockObject(BLACK_PEN);

	SBrush.CreateSolidBrush(RGB(255, 0, 0));
	EBrush.CreateSolidBrush(RGB(0, 0, 255));
	MBrush.CreateSolidBrush(RGB(0, 255, 0));
	MarsBrush.CreateSolidBrush(RGB(255, 0, 255));
	

	// Рисуем орбиты
	dc.SelectStockObject(NULL_BRUSH); // Белая кисть - не надо соэдавать
	dc.Ellipse(EarthOrbit); // Орбита Земли

	int d = MoonOrbit.right;	// Радиус орбиты Луны
	R.SetRect(ECoords(0) - d, ECoords(1) + d, ECoords(0) + d, ECoords(1) - d);
	dc.Ellipse(R); // Орбита Луны
	dc.Ellipse(MarsOrbit);


	
	pOldBrush = dc.SelectObject(&SBrush);	// Цвет Солнца
	dc.Ellipse(Sun);  // Солнце

	// Рисуем Землю
	d = Earth.right;   // Радиус Земли
	R.SetRect(ECoords(0) - d, ECoords(1) + d, ECoords(0) + d, ECoords(1) - d);
	dc.SelectObject(&EBrush);	// Цвет Земли
	dc.Ellipse(R);	// Земля

	// Рисуем Луну
	d = Moon.right;   // Радиус Луны
	R.SetRect(MCoordsSun(0) - d, MCoordsSun(1) + d, MCoordsSun(0) + d, MCoordsSun(1) - d);
	dc.SelectObject(&MBrush);	// Цвет Луны
	dc.Ellipse(R);	// Луна

	dc.SelectObject(MarsBrush);
	d = Mars.right;
	R.SetRect(MarsCoords(0) - d, MarsCoords(1) + d, MarsCoords(0) + d, MarsCoords(1) - d);
	dc.Ellipse(R);
	dc.SelectObject(pOldBrush);	  //Восстанавливаем контекст по pOldBrush 

}


void СSunSystem::DrawEndless(CDC& dc)
{
	SetMyMode(dc, RS, RW);
	while (true)
	{
		dc.SelectStockObject(WHITE_PEN);
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Rectangle(-1000,-1000,1000,1000);
		SetNewCoords();
		Draw(dc);
		
		if (fiE > 360) fiE -= 360;
		if (fiM > 360) fiM -= 360;
		if (fiMars > 360) fiMars -= 360;
		Sleep(dt);
		
	}
}

void SetMyMode(CDC& dc, CRectD& RS, CRect& RW)  //MFC
// Устанавливает режим отображения MM_ANISOTROPIC и его параметры
// dc - ссылка на класс CDC MFC
// RS -  область в мировых координатах - int
// RW -	 Область в оконных координатах - int  
{
	double dsx = RS.right - RS.left;
	double dsy = RS.top - RS.bottom;
	double xsL = RS.left;
	double ysL = RS.bottom;

	int dwx = RW.right - RW.left;
	int dwy = RW.bottom - RW.top;
	int xwL = RW.left;
	int ywH = RW.bottom;

	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt((int)dsx, (int)dsy);
	dc.SetViewportExt(dwx, -dwy);
	dc.SetWindowOrg((int)xsL, (int)ysL);
	dc.SetViewportOrg(xwL, ywH);
}