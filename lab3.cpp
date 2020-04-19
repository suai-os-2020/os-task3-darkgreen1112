#include <windows.h>
#include <iostream>
#include "lab3.h"
using std::cout;
using std::flush;

#define MAX_SEM_COUNT 1
#define THREADCOUNT 10

HANDLE mutex;
HANDLE hThread[THREADCOUNT];
/*                     0   1   2   3   4   5   6   7   8   9 */
char charTable[10] = {'a','b','c','d','e','f','g','h','i','k'};

DWORD ThreadID;
HANDLE ghSemaphore;

unsigned int lab3_thread_graph_id()
{
    return 16;
}

const char* lab3_unsynchronized_threads()
{
    return "bcef";
}

const char* lab3_sequential_threads()
{
    return "ehi";
}

DWORD WINAPI thread_unsynchronized(LPVOID lpParam)
{
    for(int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        cout << charTable[(int)lpParam] << flush;
        ReleaseMutex(mutex);
        computation();
    }

    ExitThread(0);
}

DWORD WINAPI thread_sequential(LPVOID lpParam)
{
    DWORD dwWaitResult;
    BOOL bContinue=TRUE;
    while(bContinue)
    {
        dwWaitResult = WaitForSingleObject(ghSemaphore,0L);
        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
            for(int i = 0; i < 3; i++)
            {
                WaitForSingleObject(mutex, INFINITE);
                cout << charTable[(int)lpParam] << flush;
                ReleaseMutex(mutex);
                computation();
            }
            bContinue=FALSE;
            if(!ReleaseSemaphore(ghSemaphore, 1,NULL))
            {
                cout << "ReleaseSemaphore error: " << GetLastError();
            }
            break;
            case WAIT_TIMEOUT:
                cout << "Thread %d: wait timed out\n" << GetCurrentThreadId();
            break;
            }
    }

    ExitThread(0);
}


int lab3_init()
{
    mutex = CreateMutex(NULL, FALSE, NULL);

    if(mutex == NULL)
    {
        cout << "CreateMutex error: " << GetLastError();
        return 1;
    }

    ghSemaphore = CreateSemaphore(
        NULL,           // default security attributes // аттрибуты безопасности по умолчанию
        MAX_SEM_COUNT,  // initial count               // начальное значение счетчика
        MAX_SEM_COUNT,  // maximum count               // максимаьлное значение счетчика
        NULL);          // unnamed semaphore           // безымянный семафор

    if (ghSemaphore == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }

    //a
    hThread[0] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, 0,  0, &ThreadID);
    if( hThread[0] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[0], INFINITE);
    CloseHandle(hThread[0]);

    //BCEF
    hThread[1] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)1,  0, &ThreadID);
    if( hThread[1] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[2] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)2,  0, &ThreadID);
    if( hThread[2] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)4,  0, &ThreadID);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[5] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)5,  0, &ThreadID);
    if( hThread[5] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[1], INFINITE);
    CloseHandle(hThread[1]);
    WaitForSingleObject(hThread[2], INFINITE);
    CloseHandle(hThread[2]);
    WaitForSingleObject(hThread[4], INFINITE);
    CloseHandle(hThread[4]);
    WaitForSingleObject(hThread[5], INFINITE);
    CloseHandle(hThread[5]);

    //BDEFG
    hThread[1] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)1,  0, &ThreadID);
    if( hThread[1] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[1], INFINITE);
    CloseHandle(hThread[1]);

    hThread[3] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)3,  0, &ThreadID);
    if( hThread[3] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[3], INFINITE);
    CloseHandle(hThread[3]);

    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)4,  0, &ThreadID);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[4], INFINITE);
    CloseHandle(hThread[4]);

    hThread[5] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)5,  0, &ThreadID);
    if( hThread[5] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[5], INFINITE);
    CloseHandle(hThread[5]);

    hThread[6] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)6,  0, &ThreadID);
    if( hThread[6] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[6], INFINITE);
    CloseHandle(hThread[6]);

    //EFGH
    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)4,  0, &ThreadID);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[4], INFINITE);
    CloseHandle(hThread[4]);

    hThread[5] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)5,  0, &ThreadID);
    if( hThread[5] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[5], INFINITE);
    CloseHandle(hThread[5]);

    hThread[6] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)6,  0, &ThreadID);
    if( hThread[6] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[6], INFINITE);
    CloseHandle(hThread[6]);

    hThread[7] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)7,  0, &ThreadID);
    if( hThread[7] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[7], INFINITE);
    CloseHandle(hThread[7]);

    //EHI
    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)4,  0, &ThreadID);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[4], INFINITE);
    CloseHandle(hThread[4]);

    hThread[7] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)7,  0, &ThreadID);
    if( hThread[7] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[7], INFINITE);
    CloseHandle(hThread[7]);

    hThread[8] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)8,  0, &ThreadID);
    if( hThread[8] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[8], INFINITE);
    CloseHandle(hThread[8]);

    //IK
    hThread[8] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)8,  0, &ThreadID);
    if( hThread[8] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[8], INFINITE);
    CloseHandle(hThread[8]);

    hThread[9] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)9,  0, &ThreadID);
    if( hThread[9] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[9], INFINITE);
    CloseHandle(hThread[9]);

    //close semaphore
    CloseHandle(ghSemaphore);

    CloseHandle(mutex);

    return 0;
}
