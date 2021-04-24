#pragma once
#include "CMatrix.h"
#include "AlterCords.h"
#include "Lib.h"
class СSunSystem
{
	CRect Sun;			 // Прямоугольник Солнца
	CRect Earth;	     // Прямоугольник Земли
	CRect Moon;			 // Прямоугольник Луны
	CRect Mars;			 // Прямоугольник Марса
	CRect EarthOrbit;    // Прямоугольник, описанный вокруг орбиты Земли
	CRect MoonOrbit;     // Прямоугольник, описанный вокруг орбиты Луны
	CRect MarsOrbit;     // Прямоугольник, описанный вокруг орбиты Марса
	double ER;			 // Радиус орбиты Земли
	double MR;			 // Радиус орбиты Луны
	double MarsR;		 // Радиус орбиты Марса
	CMatrix ECoords;     // Текущие координаты Земли в СК Солнца ( x,y,1)
	CMatrix MCoordsEarth;// Текущие координаты Луны в СК Земли ( x,y,1)
	CMatrix MCoordsSun;  // Текущие координаты Луны в СК Солнца ( x,y,1)
	CMatrix MarsCoords;  // Текущие координаты Марса в СК Солнца ( x,y,1)
	CMatrix PM;			 // Матрица поворота для луны
	CMatrix PE;			 // Матрица поворота для Земли
	CMatrix PMars;		 // Матрица поворота для Марса
	CRect RW;			 // Прямоугольник в окне
	CRectD RS;			 // Прямоугольник области в МСК
	double wEarth;	     // Угловая скорость Земли относительно Солнца, град./сек.
	double wMoon;		 // Угловая скорость Луны относительно Земли, град./сек.
	double wMars;		 // Угловая скорость Марса относительно Солнца, град./сек.
	double fiE;			 // Угловое положение Земли в системе кординат Солнца, град
	double dfiE;		 // Угол поворота Земли за время dt.
	double fiM;			 // Угловое положение Луны в системе кординат Земли, град
	double dfiM;		 // Угол поворота Луны за время dt
	double fiMars;		 // Угловое положение Марса в системе кординат Солнца, град
	double dfiMars;		 // Угол поворота Марса за время dt
	double dt;			 // Интервал дискретизации, сек.
public:
	СSunSystem();
	void SetPlanetsSpeed(double EarthSpeed = 2, double MoonSpeed = 3, double MarsSpeed = 1)
	{
		wEarth = EarthSpeed;
		wMoon = MoonSpeed;
		wMars = MarsSpeed;
	}
	void SetDT(double dtx = 1) { dt = dtx; };   // Установка интервала дискретизации
	void SetNewCoords();                     // Вычисляет новые координаты планет
	void GetRS(CRectD& RSX);	   // Возвращает область графика в мировой СК
	CRectD GetRS();	   // Возвращает область графика в мировой СК
	CRect GetRW() { return RW; };	   // Возвращает область графика в окне	
	void Draw(CDC& dc);		    // Рисование без самостоятельного пересчета координат
	void DrawEndless(CDC& dc);

};

void SetMyMode(CDC& dc, CRectD& RS, CRect& RW);