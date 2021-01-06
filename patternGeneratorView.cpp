// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// patternGeneratorView.cpp : implementation of the CpatternGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "patternGenerator.h"
#endif

#include "patternGeneratorDoc.h"
#include "patternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpatternGeneratorView

IMPLEMENT_DYNCREATE(CpatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CpatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CpatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON2, &CpatternGeneratorView::OnButton2)
	
END_MESSAGE_MAP()

// CpatternGeneratorView construction/destruction

CpatternGeneratorView::CpatternGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;
}

CpatternGeneratorView::~CpatternGeneratorView()
{
}

BOOL CpatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CpatternGeneratorView drawing

void CpatternGeneratorView::OnDraw(CDC* pDC)
{
	CpatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	
	pDC->TextOut(30, 20,_T("Press start For pendulum simulation"));

	for (int i = 0; i < m_PointArray.GetSize() - 2; i++)
	{
		pDC->Rectangle(490, 90, 510, 110);
	   pDC->MoveTo(500,100);
	   pDC->LineTo(m_PointArray[i].x, m_PointArray[i].y);
	   pDC->Ellipse(m_PointArray[i].x-20, m_PointArray[i].y-20, m_PointArray[i].x+20, m_PointArray[i].y+20);
	   Sleep(100);
	   pDC->Rectangle(200, 100, 800, 500);

	}
	// TODO: add draw code for native data here
}


// CpatternGeneratorView printing


void CpatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CpatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CpatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CpatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CpatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CpatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CpatternGeneratorView diagnostics

#ifdef _DEBUG
void CpatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CpatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpatternGeneratorDoc* CpatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpatternGeneratorDoc)));
	return (CpatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CpatternGeneratorView message handlers


void CpatternGeneratorView::OnButton2()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("start"));
	m_pCurrentThread = AfxBeginThread(CpatternGeneratorView::StartThread, this);

}


void CpatternGeneratorView::OnButton3()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("suspend"));
	m_pCurrentThread ->SuspendThread();
}


void CpatternGeneratorView::OnButton4()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("resume"));
	m_pCurrentThread ->ResumeThread();

}


UINT CpatternGeneratorView::StartThread(LPVOID param)
{
	CpatternGeneratorView* pView = (CpatternGeneratorView*)param;
	// TODO: Add your implementation code here.
	CPoint MyPoint(0, 0); int len = 300;
	float angle = 0, aVel = 0, aAcc = 0;
	while (true)
	{
		MyPoint.x =  500+ len * sin(angle);
		MyPoint.y =  100 + len * cos(angle);
		angle += .09;
		aAcc = -.01 * sin(angle);
		angle += aVel;
		aVel += aAcc;
		aVel *= .99;
		(*pView). m_PointArray.Add(MyPoint);
		
		pView->Invalidate();
		
		
		Sleep(100);
	}
	return 0;
}
