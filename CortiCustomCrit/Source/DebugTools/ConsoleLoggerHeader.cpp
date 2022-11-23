// ConsoleLogger.h: interface for the CConsoleLogger class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSOLELOGGER_H__294FDF9B_F91E_4F6A_A953_700181DD1996__INCLUDED_)
#define AFX_CONSOLELOGGER_H__294FDF9B_F91E_4F6A_A953_700181DD1996__INCLUDED_

#include "windows.h"
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <tlhelp32.h>
//#include "stdlib.h"
//#include "io.h"
//#include "direct.h"

// If no "helper_executable" location was specify - search for the DEFAULT_HELPER_EXE
#define DEFAULT_HELPER_EXE  "DebugConsole.exe"

class CConsoleLogger
{
public:

    // ctor,dtor
    CConsoleLogger();
    ~CConsoleLogger();

    // create a logger: starts a pipe+create the child process
    long Create ( const char *lpszWindowTitle = NULL,
                  int buffer_size_x = -1, int buffer_size_y = -1,
                  const char *logger_name = NULL,
                  const char *helper_executable = NULL );

    // close everything
    long Close ( void );

    // output functions
    int print ( const char *lpszText, int iSize = -1 );
    int printf ( const char *format, ... );

    // play with the CRT output functions
    int SetAsDefaultOutput ( void );
    static int ResetDefaultOutput ( void );

protected:
    char    m_name[64];
    HANDLE  m_hPipe;

    CRITICAL_SECTION    m_cs;
    inline void InitializeCriticalSection ( void )
    {
        ::InitializeCriticalSection ( &m_cs );
    }

    inline void DeleteCriticalSection ( void )
    {
        ::DeleteCriticalSection ( &m_cs );
    }

    // our own LOCK function
    inline void EnterCriticalSection ( void )
    {
        ::EnterCriticalSection ( &m_cs );
    }

    // our own UNLOCK function
    inline void LeaveCriticalSection ( void )
    {
        ::LeaveCriticalSection ( &m_cs );
    }

    // you can extend this class by overriding the function
    virtual long    AddHeaders ( void )
    {
        return 0;
    }

    // the _print() helper function
    virtual int _print ( const char *lpszText, int iSize );

    // SafeWriteFile : write safely to the pipe
    inline BOOL SafeWriteFile (
        /*__in*/ HANDLE hFile,
        /*__in_bcount(nNumberOfBytesToWrite)*/  LPCVOID lpBuffer,
        /*__in        */ DWORD nNumberOfBytesToWrite,
        /*__out_opt   */ LPDWORD lpNumberOfBytesWritten,
        /*__inout_opt */ LPOVERLAPPED lpOverlapped
    )
    {
        EnterCriticalSection();
        BOOL bRet = ::WriteFile ( hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped );
        LeaveCriticalSection();
        return bRet;
    }

    bool IsProcessRunning ( const std::string processName );
};

#endif // AFX_CONSOLELOGGER_H__294FDF9B_F91E_4F6A_A953_700181DD1996__INCLUDED_
