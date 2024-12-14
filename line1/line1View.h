
// line1View.h : interface of the Cline1View class
//

#pragma once
#include"banco.h"


class Cline1View : public CView
{
protected: // create from serialization only
	Cline1View() noexcept;
	DECLARE_DYNCREATE(Cline1View)

// Attributes
public:
	Cline1Doc* GetDocument() const;

// Operations
public:
	Banco banco;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Cline1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in line1View.cpp
inline Cline1Doc* Cline1View::GetDocument() const
   { return reinterpret_cast<Cline1Doc*>(m_pDocument); }
#endif

