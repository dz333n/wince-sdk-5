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
/*++


Module Name:Notify.h

Purpose:Public Header for User Notifications

--*/

#ifndef _NOTIFY_H_
#define _NOTIFY_H_

// @doc NOTIFY

/*
 * Parameters to the CeRunAppAtEvent() API.
 */

#define NOTIFICATION_EVENT_NONE                     0
#define NOTIFICATION_EVENT_TIME_CHANGE              1
#define NOTIFICATION_EVENT_SYNC_END                 2
#define NOTIFICATION_EVENT_ON_AC_POWER              3
#define NOTIFICATION_EVENT_OFF_AC_POWER             4
#define NOTIFICATION_EVENT_NET_CONNECT              5
#define NOTIFICATION_EVENT_NET_DISCONNECT           6
#define NOTIFICATION_EVENT_DEVICE_CHANGE            7
#define NOTIFICATION_EVENT_IR_DISCOVERED            8
#define NOTIFICATION_EVENT_RS232_DETECTED           9
#define NOTIFICATION_EVENT_RESTORE_END             10
#define NOTIFICATION_EVENT_WAKEUP                  11
#define NOTIFICATION_EVENT_TZ_CHANGE               12
#define NOTIFICATION_EVENT_MACHINE_NAME_CHANGE     13
#define NOTIFICATION_EVENT_RNDIS_FN_DETECTED       14
#define NOTIFICATION_EVENT_INTERNET_PROXY_CHANGE   15
#define NOTIFICATION_EVENT_LAST                    NOTIFICATION_EVENT_INTERNET_PROXY_CHANGE

/*
 * String passed on the command line when an app is run as the result
 * of a call to CeRunAppAtTime().
 */

#define APP_RUN_AT_TIME                 TEXT("AppRunAtTime")

/*
 * Prefix of the command line when the user requests to run the application
 * that "owns" a notification.  It is followed by a space, and the
 * stringized version of the notification handle.
 */

#define APP_RUN_TO_HANDLE_NOTIFICATION  TEXT("AppRunToHandleNotification")

/*
 * Strings passed on the command line when an event occurs that the
 * app has requested via CeRunAppAtEvent.  Note that some of these
 * strings will be used as the command line *prefix*, since the rest
 * of the command line will be used as a parameter.
 */

#define APP_RUN_AFTER_TIME_CHANGE           TEXT("AppRunAfterTimeChange")
#define APP_RUN_AFTER_SYNC                  TEXT("AppRunAfterSync")
#define APP_RUN_AT_AC_POWER_ON              TEXT("AppRunAtAcPowerOn")
#define APP_RUN_AT_AC_POWER_OFF             TEXT("AppRunAtAcPowerOff")
#define APP_RUN_AT_NET_CONNECT              TEXT("AppRunAtNetConnect")
#define APP_RUN_AT_NET_DISCONNECT           TEXT("AppRunAtNetDisconnect")
#define APP_RUN_AT_DEVICE_CHANGE            TEXT("AppRunDeviceChange")
#define APP_RUN_AT_IR_DISCOVERY             TEXT("AppRunAtIrDiscovery")
#define APP_RUN_AT_RS232_DETECT             TEXT("AppRunAtRs232Detect")
#define APP_RUN_AFTER_RESTORE               TEXT("AppRunAfterRestore")
#define APP_RUN_AFTER_WAKEUP			    TEXT("AppRunAfterWakeup")
#define APP_RUN_AFTER_TZ_CHANGE			    TEXT("AppRunAfterTzChange")
#define APP_RUN_AFTER_EXTENDED_EVENT	    TEXT("AppRunAfterExtendedEvent")
#define APP_RUN_AFTER_RNDIS_FN_DETECTED     TEXT("AppRunAfterRndisFnDetected")
#define APP_RUN_AFTER_INTERNET_PROXY_CHANGE TEXT("AppRunAfterInternetProxyChange")

/*
 * Strings passed on the end of the command line for the event,
 * NOTIFICATION_EVENT_DEVICE_CHANGE.  The general form will be
 * "/op devicename" for instance "/ADD COM2:"
 */
#define NOTIFY_DEVICE_ADD               TEXT("/ADD")
#define NOTIFY_DEVICE_REMOVE            TEXT("/REMOVE")

/*
 * @struct CE_USER_NOTIFICATION | User Notification Structure
 *
 * @comm  This structure is passed in to <f CeGetUserNotificationPreferences>.
 * Initial settings are used to populate the dialog.  If the function
 * returns TRUE, the returned settings should be saved, and considered when
 * calling <f CeSetUserNotification>.  Settings for hardware not on the
 * current device will be ignored.
 *
 * It is also used when calling <f CeSetUserNotification>, to describe
 * what should happen when the notification time is reached.  
 */

typedef struct UserNotificationType {
    DWORD ActionFlags;      //@field Action Flags.  Any combination of the
                            // PUN_* flags.  Flags not valid on a given
                            // hardware platform will be ignored.
#define PUN_LED     1       //@flag PUN_LED | LED flag.  Set if the LED should be 
                            // flashed when the notification occurs.
#define PUN_VIBRATE 2       //@flag PUN_VIBRATE | Vibrate flag.  Set if the device should
                            // be vibrated.
#define PUN_DIALOG  4       //@flag PUN_DIALOG | Dialog flag.  Set if a dialog should be
                            // displayed (the app must provide title and text
                            // when calling <f CeSetUserNotification>).
#define PUN_SOUND   8       //@flag PUN_SOUND | Sound flag.  Set if the sound specified
                            // in pwszSound should be played.
#define PUN_REPEAT  16      //@flag PUN_REPEAT | Sound repeat flag.  Set if the sound
                            // specified in pwszSound should be repeated progressively.
#define PUN_PRIVATE 32      //@flag PUN_PRIVATE | Dialog box z-order flag.  Set if the
                            // notification dialog box should come up behind the password.
    TCHAR *pwszDialogTitle; //@field Dialog Title.  Required if PUN_DIALOG is set, ignored
                            // otherwise. Ignored by CeGetUserNotificationPreferences().
    TCHAR *pwszDialogText;  //@field Dialog Text.  Required if PUN_DIALOG is set, ignored
                            // otherwise. Ignored by CeGetUserNotificationPreferences().
    TCHAR *pwszSound;       //@field Sound string as supplied to sndPlaySound.
                            // CeSetUserNotification() ignores it if PUN_SOUND is not set.
    DWORD nMaxSound;        //@field Max Sound string length.  Specifies the
                            // maximum length of the string that can be copied
                            // into the pwszSound buffer by
                            // CeGetUserNotificationPreferences().
							// Should be at least MAX_PATH * sizeof(TCHAR).
                            // Ignored by CeSetUserNotification().
	union {
        DWORD dwReserved;   //@field Reserved.  Must be NULL or a pointer to
                            // platform-defined expansion structure.
                            // The first dword of the structure
                            // indicates the size of the structure.
	    void *pExpansion;
	};
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

typedef struct UserNotificationTrigger {
	DWORD		dwSize;
	DWORD		dwType;				//@field dwType Notification type
#define CNT_EVENT		1			//@flag CNT_EVENT  | System event notification
#define CNT_TIME		2			//@flag CNT_TIME   | Time-based notification
#define CNT_PERIOD		3			//@flag CNT_PERIOD | Time-based notification is active for
									// time period between stStart and stEnd
#define CNT_CLASSICTIME	4			//@flag CNT_CLASSICTIME | equivalent to using (obsolete)
									// CeSetUserNotification function - standard command line is
									// supplied. lpszArguments must be NULL
	DWORD		dwEvent;			//@field dwEvent - type of event if dwType == CNT_EVENT
	TCHAR		*lpszApplication;	//@field lpszApplication - name of application to execute
	TCHAR		*lpszArguments;		//@field lpszArguments   - command line (sans app name)
	SYSTEMTIME	stStartTime;		//@field stStartTime - begin of notification period
	SYSTEMTIME	stEndTime;			//@field stEndTime   - end of notification period
} CE_NOTIFICATION_TRIGGER, *PCE_NOTIFICATION_TRIGGER;

//
//	Application name can be prefixed with the following strings to specify different
//	named objects rather than an application. The action varies depending on the prefix.
//  In case of named event, the event gets signaled.
//
#define NAMED_EVENT_PREFIX_TEXT TEXT("\\\\.\\Notifications\\NamedEvents\\")
#define NAMED_EVENT_PREFIX_LEN (sizeof(NAMED_EVENT_PREFIX_TEXT)/sizeof(TCHAR) - 1)

typedef struct UserNotificationInfoHeader {
	HANDLE					hNotification;
#define CNS_SIGNALLED	1

	DWORD					dwStatus;
	CE_NOTIFICATION_TRIGGER	*pcent;
	CE_USER_NOTIFICATION	*pceun;
} CE_NOTIFICATION_INFO_HEADER, *PCE_NOTIFICATION_INFO_HEADER;

/* Declarations of User Notification APIs. */

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

BOOL   CeGetUserNotificationPreferences (HWND hWndParent, PCE_USER_NOTIFICATION lpNotification);

HANDLE CeSetUserNotificationEx		(HANDLE hNotification, CE_NOTIFICATION_TRIGGER *pcnt, CE_USER_NOTIFICATION *pceun);
BOOL   CeClearUserNotification		(HANDLE hNotification);
BOOL   CeGetUserNotification		(HANDLE hNotification, DWORD cBufferSize, LPDWORD pcBytesNeeded, LPBYTE pBuffer);
BOOL   CeGetUserNotificationHandles (HANDLE *rghNotifications, DWORD cHandles, LPDWORD pcHandlesNeeded);

//
//	Obsolete; provided to maintain compatibility only
//
HANDLE CeSetUserNotification (HANDLE hNotification, TCHAR *pwszAppName, SYSTEMTIME *lpTime, PCE_USER_NOTIFICATION lpUserNotification);
BOOL   CeRunAppAtTime (TCHAR *pwszAppName, SYSTEMTIME *lpTime);
BOOL   CeRunAppAtEvent(TCHAR *pwszAppName, LONG lWhichEvent);
BOOL   CeHandleAppNotifications (TCHAR *pwszAppName);

//
//	API set ready event - wait for it before using notifications
//
#define NOTIFICATION_EVENTNAME_API_SET_READY	L"system/events/notify/APIReady"

#ifdef __cplusplus
}
#endif  //__cplusplus

#ifdef WINCEOEM
#include <pnotify.h>
#endif

#endif /* _NOTIFY_H_ */

