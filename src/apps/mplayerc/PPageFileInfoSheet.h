/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2024 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <HighDPI.h>
#include "PPageFileInfoClip.h"
#include "PPageFileInfoDetails.h"
#include "PPageFileInfoRes.h"
#include "PPageFileMediaInfo.h"


class CMainFrame;

class CMPCPropertySheet: public CPropertySheet
{
	DECLARE_DYNAMIC(CMPCPropertySheet)

public:
	CMPCPropertySheet(LPCWSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);

	template <class T>
	void AddPage(T* pPage) {
		CPropertySheet::AddPage(pPage);
		m_IdMap[GetPageIndex(pPage)] = T::IDD;
	}

	void RemovePage(CPropertyPage* pPage) {
		m_IdMap.erase(GetPageIndex(pPage));
		CPropertySheet::RemovePage(pPage);
	}
	void RemovePage(int nPage) {
		m_IdMap.erase(nPage);
		CPropertySheet::RemovePage(nPage);
	}

	DWORD GetResourceId(int nPage) {
		return m_IdMap[nPage];
	}

protected:
	std::map<int, DWORD> m_IdMap;
};

// CPPageFileInfoSheet

class CPPageFileInfoSheet : public CMPCPropertySheet, public CDPI
{
	DECLARE_DYNAMIC(CPPageFileInfoSheet)

private:
	CPPageFileInfoDetails m_details;
	CPPageFileInfoClip    m_clip;
	CPPageFileInfoRes     m_res;
	CPPageFileMediaInfo   m_mi;

	CButton m_Button_MI_SaveAs;
	CButton m_Button_MI_Clipboard;

	BOOL    m_bNeedInit = TRUE;
	CRect   m_rCrt;
	CRect   m_rWnd;
	int     m_nMinCX = 0;
	int     m_nMinCY = 0;

public:
	CPPageFileInfoSheet(const std::list<CString>& files, CMainFrame* pMainFrame, CWnd* pParentWnd, const bool bOnlyMI = false);
	virtual ~CPPageFileInfoSheet();

	afx_msg void OnSaveAs();
	afx_msg void OnCopyToClipboard();
	INT_PTR DoModal();

protected:
	virtual BOOL OnInitDialog();
	static int CALLBACK XmnPropSheetCallback(HWND hWnd, UINT message, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDestroy();
	LRESULT OnDpiChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
