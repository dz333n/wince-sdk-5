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

#include "stdafx.h"

#ifdef AFX_AUX_SEG
#pragma code_seg(AFX_AUX_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTime - absolute time

CTime::CTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
	int nDST)
{
	struct tm atm;
	atm.tm_sec = nSec;
	atm.tm_min = nMin;
	atm.tm_hour = nHour;
	ASSERT(nDay >= 1 && nDay <= 31);
	atm.tm_mday = nDay;
	ASSERT(nMonth >= 1 && nMonth <= 12);
	atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
	ASSERT(nYear >= 1900);
	atm.tm_year = nYear - 1900;     // tm_year is 1900 based
	atm.tm_isdst = nDST;
	m_time = WCE_FCTN(mktime)(&atm);
	ASSERT(m_time != -1);       // indicates an illegal input time
}

CTime::CTime(WORD wDosDate, WORD wDosTime, int nDST)
{
	struct tm atm;
	atm.tm_sec = (wDosTime & ~0xFFE0) << 1;
	atm.tm_min = (wDosTime & ~0xF800) >> 5;
	atm.tm_hour = wDosTime >> 11;

	atm.tm_mday = wDosDate & ~0xFFE0;
	atm.tm_mon = ((wDosDate & ~0xFE00) >> 5) - 1;
	atm.tm_year = (wDosDate >> 9) + 80;
	atm.tm_isdst = nDST;
	m_time = WCE_FCTN(mktime)(&atm);
	ASSERT(m_time != -1);       // indicates an illegal input time
}

CTime::CTime(const SYSTEMTIME& sysTime, int nDST)
{
	if (sysTime.wYear < 1900)
	{
		time_t time0 = 0L;
		CTime timeT(time0);
		*this = timeT;
	}
	else
	{
		CTime timeT(
			(int)sysTime.wYear, (int)sysTime.wMonth, (int)sysTime.wDay,
			(int)sysTime.wHour, (int)sysTime.wMinute, (int)sysTime.wSecond,
			nDST);
		*this = timeT;
	}
}

CTime::CTime(const FILETIME& fileTime, int nDST)
{
	// first convert file time (UTC time) to local time
	FILETIME localTime;
	if (!FileTimeToLocalFileTime(&fileTime, &localTime))
	{
		m_time = 0;
		return;
	}

	// then convert that time to system time
	SYSTEMTIME sysTime;
	if (!FileTimeToSystemTime(&localTime, &sysTime))
	{
		m_time = 0;
		return;
	}

	// then convert the system time to a time_t (C-runtime local time)
	CTime timeT(sysTime, nDST);
	*this = timeT;
}

CTime PASCAL CTime::GetCurrentTime()
// return the current system time
{
	return CTime(::WCE_FCTN(time)(NULL));
}

#if !defined(_WIN32_WCE)
struct tm* CTime::GetGmtTm(struct tm* ptm) const
{
	if (ptm != NULL)
	{
		*ptm = *gmtime(&m_time);
		return ptm;
	}
	else
		return gmtime(&m_time);
}
#endif // _WIN32_WCE

struct tm* CTime::GetLocalTm(struct tm* ptm) const
{
	if (ptm != NULL)
	{
		struct tm* ptmTemp = WCE_FCTN(localtime)(&m_time);
		if (ptmTemp == NULL)
			return NULL;    // indicates the m_time was not initialized!

		*ptm = *ptmTemp;
		return ptm;
	}
	else
		return WCE_FCTN(localtime)(&m_time);
}

BOOL CTime::GetAsSystemTime(SYSTEMTIME& timeDest) const
{
	struct tm* ptm = GetLocalTm(NULL);
	if (ptm == NULL)
		return FALSE;

	timeDest.wYear = (WORD) (1900 + ptm->tm_year);
	timeDest.wMonth = (WORD) (1 + ptm->tm_mon);
	timeDest.wDayOfWeek = (WORD) ptm->tm_wday;
	timeDest.wDay = (WORD) ptm->tm_mday;
	timeDest.wHour = (WORD) ptm->tm_hour;
	timeDest.wMinute = (WORD) ptm->tm_min;
	timeDest.wSecond = (WORD) ptm->tm_sec;
	timeDest.wMilliseconds = 0;

	return TRUE;
}


#ifdef _DEBUG
CDumpContext& AFXAPI operator <<(CDumpContext& dc, CTime time)
{
	char* psz = WCE_FCTN(ctime)(&time.m_time);
	if ((psz == NULL) || (time.m_time == 0))
		return dc << "CTime(invalid #" << time.m_time << ")";

	// format it
	psz[24] = '\0';         // nuke newline
	return dc << "CTime(\"" << psz << "\")";
}
#endif

CArchive& AFXAPI operator <<(CArchive& ar, CTime time)
{
	return ar << (DWORD) time.m_time;
}

CArchive& AFXAPI operator >>(CArchive& ar, CTime& rtime)
{
	return ar >> (DWORD&) rtime.m_time;
}

/////////////////////////////////////////////////////////////////////////////
// CTimeSpan - relative time

#ifdef _DEBUG
CDumpContext& AFXAPI operator <<(CDumpContext& dc, CTimeSpan timeSpan)
{
	return dc << "CTimeSpan(" << timeSpan.GetDays() << " days, " <<
		 timeSpan.GetHours() << " hours, " <<
		 timeSpan.GetMinutes() << " minutes and " <<
		 timeSpan.GetSeconds() << " seconds)";
}
#endif

CArchive& AFXAPI operator <<(CArchive& ar, CTimeSpan timeSpan)
{
	return ar << (DWORD) timeSpan.m_timeSpan;
}

CArchive& AFXAPI operator >>(CArchive& ar, CTimeSpan& rtimeSpan)
{
	return ar >> (DWORD&) rtimeSpan.m_timeSpan;
}


/////////////////////////////////////////////////////////////////////////////
// String formatting

#define maxTimeBufferSize       128
	// Verifies will fail if the needed buffer size is too large

#ifdef _UNICODE
#endif

CString CTimeSpan::Format(LPCTSTR pFormat) const
// formatting timespans is a little trickier than formatting CTimes
//  * we are only interested in relative time formats, ie. it is illegal
//      to format anything dealing with absolute time (i.e. years, months,
//         day of week, day of year, timezones, ...)
//  * the only valid formats:
//      %D - # of days -- NEW !!!
//      %H - hour in 24 hour format
//      %M - minute (0-59)
//      %S - seconds (0-59)
//      %% - percent sign
{
	TCHAR szBuffer[maxTimeBufferSize];
	TCHAR ch;
	LPTSTR pch = szBuffer;

	while ((ch = *pFormat++) != '\0')
	{
		ASSERT(pch < &szBuffer[maxTimeBufferSize]);
		if (ch == '%')
		{
			switch (ch = *pFormat++)
			{
			default:
				ASSERT(FALSE);      // probably a bad format character
			case '%':
				*pch++ = ch;
				break;
			case 'D':
				pch += wsprintf(pch, _T("%ld"), GetDays());
				break;
			case 'H':
				pch += wsprintf(pch, _T("%02d"), GetHours());
				break;
			case 'M':
				pch += wsprintf(pch, _T("%02d"), GetMinutes());
				break;
			case 'S':
				pch += wsprintf(pch, _T("%02d"), GetSeconds());
				break;
			}
		}
		else
		{
			*pch++ = ch;
			if (_istlead(ch))
			{
				ASSERT(pch < &szBuffer[maxTimeBufferSize]);
				*pch++ = *pFormat++;
			}
		}
	}

	*pch = '\0';
	return szBuffer;
}

CString CTimeSpan::Format(UINT nFormatID) const
{
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);
	return Format(strFormat);
}

#if !defined(_WIN32_WCE)
CString CTime::Format(LPCTSTR pFormat) const
{
	TCHAR szBuffer[maxTimeBufferSize];

	struct tm* ptmTemp = localtime(&m_time);
	if (ptmTemp == NULL ||
		!_tcsftime(szBuffer, _countof(szBuffer), pFormat, ptmTemp))
		szBuffer[0] = '\0';
	return szBuffer;
}

CString CTime::FormatGmt(LPCTSTR pFormat) const
{
	TCHAR szBuffer[maxTimeBufferSize];

	struct tm* ptmTemp = gmtime(&m_time);
	if (ptmTemp == NULL ||
		!_tcsftime(szBuffer, _countof(szBuffer), pFormat, ptmTemp))
		szBuffer[0] = '\0';
	return szBuffer;
}

CString CTime::Format(UINT nFormatID) const
{
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);
	return Format(strFormat);
}

CString CTime::FormatGmt(UINT nFormatID) const
{
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);
	return FormatGmt(strFormat);
}
#endif // _WIN32_WCE

#ifdef _UNICODE
// These functions are provided for compatibility with MFC 3.x
#if !defined(_WIN32_WCE)
CString CTime::Format(LPCSTR pFormat) const
{
	CString strFormat(pFormat);
	return Format((LPCTSTR)strFormat);
}

CString CTime::FormatGmt(LPCSTR pFormat) const
{
	CString strFormat(pFormat);
	return FormatGmt((LPCTSTR)strFormat);
}
#endif // _WIN32_WCE

CString CTimeSpan::Format(LPCSTR pFormat) const
{
	CString strFormat = pFormat;
	return Format((LPCTSTR)strFormat);
}
#endif // _UNICODE

////////////////////////////////////////////////////////////////////////////
// out-of-line inlines for binary compatibility

#ifdef _AFXDLL
#ifndef _DEBUG

CTime::CTime()
	{ }

CTime::CTime(const CTime& timeSrc)
	{ m_time = timeSrc.m_time; }

CTimeSpan::CTimeSpan()
	{ }

#endif
#endif

/////////////////////////////////////////////////////////////////////////////
