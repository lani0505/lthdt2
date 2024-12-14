
// line1View.cpp : implementation of the Cline1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "line1.h"
#endif

#include "line1Doc.h"
#include "line1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cline1View

IMPLEMENT_DYNCREATE(Cline1View, CView)

BEGIN_MESSAGE_MAP(Cline1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Cline1View construction/destruction

Cline1View::Cline1View() noexcept
{
	// TODO: add construction code here
	banco = Banco();

}

Cline1View::~Cline1View()
{
}

BOOL Cline1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cline1View drawing

void Cline1View::OnDraw(CDC* /*pDC*/)
{
	Cline1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CClientDC pdc(this);
	//banco.batdau();
	banco.vehinh(&pdc);
}

void Cline1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cline1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cline1View diagnostics

#ifdef _DEBUG
void Cline1View::AssertValid() const
{
	CView::AssertValid();
}

void Cline1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cline1Doc* Cline1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cline1Doc)));
	return (Cline1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cline1View message handlers


void Cline1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 32)
	{
		banco.batdau();
		CClientDC pdc(this);
		banco.vehinh(&pdc);

	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void Cline1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC pdc(this);

	banco.bamchuot(&pdc, point);
	CView::OnLButtonUp(nFlags, point);

}
