
// testView.h: интерфейс класса CtestView
//

#pragma once


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
	afx_msg void OnLab1Multiply();
	afx_msg
		void OnRButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLab2CaptureScreenshot();
	afx_msg void OnLab2LoadBMP();
};

#ifndef _DEBUG  // версия отладки в testView.cpp
inline CtestDoc* CtestView::GetDocument() const
   { return reinterpret_cast<CtestDoc*>(m_pDocument); }
#endif

