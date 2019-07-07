//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// Inlines for AFXDLGS.H

#ifdef _AFXDLGS_INLINE

// CCommonDialog
_AFXDLGS_INLINE CCommonDialog::CCommonDialog(CWnd* pParentWnd)
	: CDialog((UINT)0, pParentWnd) { }

// CFileDialog
_AFXDLGS_INLINE BOOL CFileDialog::GetReadOnlyPref() const
	{ return m_ofn.Flags & OFN_READONLY ? TRUE : FALSE; }
_AFXDLGS_INLINE void CFileDialog::SetTemplate(UINT nWin3ID, UINT nWin4ID)
	{ SetTemplate(MAKEINTRESOURCE(nWin3ID), MAKEINTRESOURCE(nWin4ID)); }
_AFXDLGS_INLINE POSITION CFileDialog::GetStartPosition() const
	{ return (POSITION)m_ofn.lpstrFile; }

#if !defined(_WIN32_WCE)
// CFontDialog
_AFXDLGS_INLINE CString CFontDialog::GetFaceName() const
	{ return (LPCTSTR)m_cf.lpLogFont->lfFaceName; }
_AFXDLGS_INLINE CString CFontDialog::GetStyleName() const
	{ return m_cf.lpszStyle; }
_AFXDLGS_INLINE int CFontDialog::GetSize() const
	{ return m_cf.iPointSize; }
_AFXDLGS_INLINE int CFontDialog::GetWeight() const
	{ return (int)m_cf.lpLogFont->lfWeight; }
_AFXDLGS_INLINE BOOL CFontDialog::IsItalic() const
	{ return m_cf.lpLogFont->lfItalic ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFontDialog::IsStrikeOut() const
	{ return m_cf.lpLogFont->lfStrikeOut ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFontDialog::IsBold() const
	{ return m_cf.lpLogFont->lfWeight == FW_BOLD ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFontDialog::IsUnderline() const
	{ return m_cf.lpLogFont->lfUnderline ? TRUE : FALSE; }
_AFXDLGS_INLINE COLORREF CFontDialog::GetColor() const
	{ return m_cf.rgbColors; }
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE_NO_COLORDLG)
// CColorDialog
_AFXDLGS_INLINE COLORREF CColorDialog::GetColor() const
	{ return m_cc.rgbResult; }
#endif // _WIN32_WCE_NO_COLORDLG

// CPrintDialog
#if defined(_WIN32_WCE)
#if !defined(_WIN32_WCE_NO_PRINTING)
_AFXDLGS_INLINE BOOL CPrintDialog::PrintSelection() const
	{ return m_pd.dwFlags & PD_SELECTSELECTION ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CPrintDialog::PrintAll() const
	{ return !PrintSelection() ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CPrintDialog::PrintDraft() const
	{ return m_pd.dwFlags & PD_SELECTDRAFTMODE ? TRUE : FALSE; }
_AFXDLGS_INLINE HDC CPrintDialog::GetPrinterDC() const
	{ ASSERT_VALID(this);
		return m_pd.hdc; }
#endif // _WIN32_WCE_NO_PRINTING
#else // _WIN32_WCE
_AFXDLGS_INLINE BOOL CPrintDialog::PrintSelection() const
	{ return m_pd.Flags & PD_SELECTION ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CPrintDialog::PrintRange() const
	{ return m_pd.Flags & PD_PAGENUMS ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CPrintDialog::PrintAll() const
	{ return !PrintRange() && !PrintSelection() ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CPrintDialog::PrintCollate() const
	{ return m_pd.Flags & PD_COLLATE ? TRUE : FALSE; }
_AFXDLGS_INLINE int CPrintDialog::GetFromPage() const
	{ return (PrintRange() ? m_pd.nFromPage :-1); }
_AFXDLGS_INLINE int CPrintDialog::GetToPage() const
	{ return (PrintRange() ? m_pd.nToPage :-1); }
_AFXDLGS_INLINE HDC CPrintDialog::GetPrinterDC() const
	{ ASSERT_VALID(this);
		ASSERT(m_pd.Flags & PD_RETURNDC);
		return m_pd.hDC; }
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE_NO_FINDREPLACE)
// CFindReplaceDialog
_AFXDLGS_INLINE BOOL CFindReplaceDialog::IsTerminating() const
	{ return m_fr.Flags & FR_DIALOGTERM ? TRUE : FALSE ; }
_AFXDLGS_INLINE CString CFindReplaceDialog::GetReplaceString() const
	{ return m_fr.lpstrReplaceWith; }
_AFXDLGS_INLINE CString CFindReplaceDialog::GetFindString() const
	{ return m_fr.lpstrFindWhat; }
_AFXDLGS_INLINE BOOL CFindReplaceDialog::SearchDown() const
	{ return m_fr.Flags & FR_DOWN ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFindReplaceDialog::FindNext() const
	{ return m_fr.Flags & FR_FINDNEXT ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFindReplaceDialog::MatchCase() const
	{ return m_fr.Flags & FR_MATCHCASE ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFindReplaceDialog::MatchWholeWord() const
	{ return m_fr.Flags & FR_WHOLEWORD ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFindReplaceDialog::ReplaceCurrent() const
	{ return m_fr. Flags & FR_REPLACE ? TRUE : FALSE; }
_AFXDLGS_INLINE BOOL CFindReplaceDialog::ReplaceAll() const
	{ return m_fr.Flags & FR_REPLACEALL ? TRUE : FALSE; }
#endif // _WIN32_WCE_NO_FINDREPLACE

// CPropertySheet
_AFXDLGS_INLINE CPropertyPage* CPropertySheet::GetPage(int nPage) const
	{ return STATIC_DOWNCAST(CPropertyPage, (CObject*)m_pages[nPage]); }
#if !defined(_WIN32_WCE)
_AFXDLGS_INLINE void CPropertySheet::SetWizardMode()
	{ m_psh.dwFlags |= PSH_WIZARD; }
_AFXDLGS_INLINE void CPropertySheet::SetFinishText(LPCTSTR lpszText)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, PSM_SETFINISHTEXT, 0, (LPARAM)lpszText); }
_AFXDLGS_INLINE void CPropertySheet::SetWizardButtons(DWORD dwFlags)
	{ ASSERT(::IsWindow(m_hWnd)); ::PostMessage(m_hWnd, PSM_SETWIZBUTTONS, 0, dwFlags); }
#endif // _WIN32_WCE
_AFXDLGS_INLINE CTabCtrl* CPropertySheet::GetTabControl() const
	{ ASSERT(::IsWindow(m_hWnd)); return (CTabCtrl*)CWnd::FromHandle(
		(HWND)::SendMessage(m_hWnd, PSM_GETTABCONTROL, 0, 0)); }
_AFXDLGS_INLINE BOOL CPropertySheet::PressButton(int nButton)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, PSM_PRESSBUTTON, nButton, 0); }
#if defined(_WIN32_WCE)
_AFXDLGS_INLINE BOOL CPropertySheet::IsWizard() const
        { return FALSE; }
#else // _WIN32_WCE
_AFXDLGS_INLINE BOOL CPropertySheet::IsWizard() const
        { return ((((CPropertySheet*)this)->GetPropSheetHeader()->dwFlags & (PSH_WIZARD | PSH_WIZARD97)) != 0); }
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE)
// CPropertySheetEx
_AFXDLGS_INLINE void CPropertySheetEx::SetWizardMode()
	{ m_psh.dwFlags |= PSH_WIZARD; }

// CPageSetupDialog
_AFXDLGS_INLINE CSize CPageSetupDialog::GetPaperSize() const
	{ return CSize(m_psd.ptPaperSize.x, m_psd.ptPaperSize.y); }
#endif // _WIN32_WCE

/////////////////////////////////////////////////////////////////////////////

#endif //_AFXDLGS_INLINE
