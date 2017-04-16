#include "RP1210Core.h"

RP1210Core::RP1210Core(QObject *parent)
	: QObject(parent)
	, pRP1210_ClientConnect(0)
	, pRP1210_ClientDisconnect(0)
	, pRP1210_ReadMessage(0)
	, pRP1210_SendMessage(0)
	, pRP1210_SendCommand(0)
	, pRP1210_ReadVersion(0)
	, pRP1210_ReadDetailedVersion(0)
	, pRP1210_GetHardwareStatus(0)
	, pRP1210_GetErrorMsg(0)
	, pRP1210_GetLastErrorMsg(0)
{
}

RP1210Core* RP1210Core::GetInstance()
{
	if (!theRp1210Instance)
		theRp1210Instance = new RP1210Core(0);

	return theRp1210Instance;
}

RP1210Core::~RP1210Core()
{
	UnLoadRp1210DLL();
}

bool RP1210Core::LoadRp1210DLL(QString DLLPath)
{

#ifdef UNICODE
	hRP1210DLL = LoadLibrary(DLLPath.toStdWString().c_str());
	DWORD dwError = GetLastError();
#else
	hRP1210DLL = LoadLibrary(DLLPath.toStdString().c_str());
#endif

	if(hRP1210DLL == NULL)
	{
		return false;
	}

	// 4/16/2017 : ZH : ��������
	pRP1210_ClientConnect       = (fxRP1210_ClientConnect)GetProcAddress(hRP1210DLL, "RP1210_ClientConnect");
	pRP1210_ClientDisconnect    = (fxRP1210_ClientDisconnect)GetProcAddress(hRP1210DLL, "RP1210_ClientDisconnect");
	pRP1210_ReadMessage         = (fxRP1210_ReadMessage)GetProcAddress(hRP1210DLL, "RP1210_ReadMessage");
	pRP1210_SendMessage         = (fxRP1210_SendMessage)GetProcAddress(hRP1210DLL, "RP1210_SendMessage");
	pRP1210_SendCommand         = (fxRP1210_SendCommand)GetProcAddress(hRP1210DLL, "RP1210_SendCommand");
	pRP1210_ReadVersion         = (fxRP1210_ReadVersion)GetProcAddress(hRP1210DLL, "RP1210_ReadVersion");
	pRP1210_ReadDetailedVersion = (fxRP1210_ReadDetailedVersion)GetProcAddress(hRP1210DLL, "RP1210_ReadDetailedVersion");
	pRP1210_GetHardwareStatus   = (fxRP1210_GetHardwareStatus)GetProcAddress(hRP1210DLL, "RP1210_GetHardwareStatus");
	pRP1210_GetErrorMsg         = (fxRP1210_GetErrorMsg)GetProcAddress(hRP1210DLL, "RP1210_GetErrorMsg");
	pRP1210_GetLastErrorMsg     = (fxRP1210_GetLastErrorMsg)GetProcAddress(hRP1210DLL, "RP1210_GetLastErrorMsg");
	
	if (NULL == pRP1210_ClientConnect)       { fprintf(stderr, "\nError:    Could not find procedure RP1210_ClientConnect       in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_ClientDisconnect)    { fprintf(stderr, "\nError:    Could not find procedure RP1210_ClientDisconnect    in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_ReadMessage)         { fprintf(stderr, "\nError:    Could not find procedure RP1210_ReadMessage         in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_SendMessage)         { fprintf(stderr, "\nError:    Could not find procedure RP1210_SendMessage         in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_SendCommand)         { fprintf(stderr, "\nError:    Could not find procedure RP1210_SendCommand         in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_ReadVersion)         { fprintf(stderr, "\nError:    Could not find procedure RP1210_ReadVersion         in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_GetHardwareStatus)   { fprintf(stderr, "\nError:    Could not find procedure RP1210_GetHardwareStatus   in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_GetErrorMsg)         { fprintf(stderr, "\nError:    Could not find procedure RP1210_GetErrorMsg         in DLL!\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_ReadDetailedVersion) { fprintf(stderr, "\nWarning:  Could not find procedure RP1210_ReadDetailedVersion in DLL.\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }
	if (NULL == pRP1210_GetLastErrorMsg)     { fprintf(stderr, "\nWarning:  Could not find procedure RP1210_GetLastErrorMsg     in DLL.\n"); FreeLibrary(hRP1210DLL);hRP1210DLL = 0 ; return false; }

	return true;	  
} 

void RP1210Core::UnLoadRp1210DLL()
{
	if (hRP1210DLL != INVALID_HANDLE_VALUE)
	{
		pRP1210_ClientConnect = 0;
		pRP1210_ClientDisconnect = 0;
		pRP1210_ReadMessage = 0;
		pRP1210_SendMessage = 0;
		pRP1210_SendCommand = 0;
		pRP1210_ReadVersion = 0;
		pRP1210_ReadDetailedVersion = 0;
		pRP1210_GetHardwareStatus = 0;
		pRP1210_GetErrorMsg = 0;
		pRP1210_GetLastErrorMsg = 0;

		FreeLibrary(hRP1210DLL);
	}
}

RP1210Core* RP1210Core::theRp1210Instance = 0;