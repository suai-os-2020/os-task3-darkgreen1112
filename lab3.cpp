#include <windows.h>
#include <iostream>
#include "lab3.h"
using std::cout;
using std::flush;

#define MAX_SEM_COUNT 9
#define THREADCOUNT 10

HANDLE mutex;
HANDLE hThread[THREADCOUNT];
/*                     0   1   2   3   4   5   6   7   8   9 */
char charTable[10] = {'a','b','c','d','e','f','g','h','i','k'};

DWORD ThreadIDA;
DWORD ThreadIDB;
DWORD ThreadIDC;
DWORD ThreadIDD;
DWORD ThreadIDE;
DWORD ThreadIDF;
DWORD ThreadIDG;
DWORD ThreadIDH;
DWORD ThreadIDI;
DWORD ThreadIDK;

HANDLE ghSemaphoreB;
HANDLE ghSemaphoreD;
HANDLE ghSemaphoreE;
HANDLE ghSemaphoreF;
HANDLE ghSemaphoreG;
HANDLE ghSemaphoreH;
HANDLE ghSemaphoreI;
HANDLE ghSemaphoreK;

HANDLE semaphoreTable[10];


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

DWORD WINAPI thread_unsynchronized(LPVOID lpParam);
DWORD WINAPI thread_sequential(LPVOID lpParam);

DWORD WINAPI thread_a(LPVOID lpParam)
{
    for(int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        cout << charTable[(int)lpParam] << flush;
        ReleaseMutex(mutex);
        computation();
    }

    //BCEF
    hThread[1] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)1,  0, &ThreadIDB);
    if( hThread[1] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[2] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)2,  0, &ThreadIDC);
    if( hThread[2] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)4,  0, &ThreadIDE);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[5] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_unsynchronized, (LPVOID)5,  0, &ThreadIDF);
    if( hThread[5] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    WaitForSingleObject(hThread[1], INFINITE);
    WaitForSingleObject(hThread[2], INFINITE);
    WaitForSingleObject(hThread[4], INFINITE);
    WaitForSingleObject(hThread[5], INFINITE);
    CloseHandle(hThread[1]);
    CloseHandle(hThread[4]);
    CloseHandle(hThread[5]);

    //BDEFG
    hThread[1] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)13,  0, &ThreadIDB);
    if( hThread[1] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }


    hThread[3] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)34,  0, &ThreadIDD);
    if( hThread[3] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }


    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)45,  0, &ThreadIDE);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }


    hThread[5] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)56,  0, &ThreadIDF);
    if( hThread[5] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }


    hThread[6] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)61,  0, &ThreadIDG);
    if( hThread[6] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    ReleaseSemaphore(semaphoreTable[1], 1,NULL);

    WaitForSingleObject(hThread[1], INFINITE);
    WaitForSingleObject(hThread[3], INFINITE);
    WaitForSingleObject(hThread[4], INFINITE);
    WaitForSingleObject(hThread[5], INFINITE);
    WaitForSingleObject(hThread[6], INFINITE);
    CloseHandle(hThread[4]);
    CloseHandle(hThread[5]);
    CloseHandle(hThread[6]);

    //EFGH
    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)45,  0, &ThreadIDE);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[5] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)56,  0, &ThreadIDF);
    if( hThread[5] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[6] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)67,  0, &ThreadIDG);
    if( hThread[6] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[7] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)74,  0, &ThreadIDH);
    if( hThread[7] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    ReleaseSemaphore(semaphoreTable[4], 1,NULL);

    WaitForSingleObject(hThread[4], INFINITE);
    WaitForSingleObject(hThread[5], INFINITE);
    WaitForSingleObject(hThread[6], INFINITE);
    WaitForSingleObject(hThread[7], INFINITE);
    CloseHandle(hThread[4]);
    CloseHandle(hThread[7]);

    //EHI
    hThread[4] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)47,  0, &ThreadIDE);
    if( hThread[4] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[7] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)78,  0, &ThreadIDH);
    if( hThread[7] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[8] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)84,  0, &ThreadIDI);
    if( hThread[8] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    WaitForSingleObject(hThread[4], INFINITE);
    WaitForSingleObject(hThread[7], INFINITE);
    WaitForSingleObject(hThread[8], INFINITE);
    CloseHandle(hThread[8]);

    //IK
    hThread[8] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)89,  0, &ThreadIDI);
    if( hThread[8] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    hThread[9] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_sequential, (LPVOID)98,  0, &ThreadIDK);
    if( hThread[9] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }

    ReleaseSemaphore(semaphoreTable[8], 1,NULL);

    WaitForSingleObject(hThread[8], INFINITE);
    WaitForSingleObject(hThread[9], INFINITE);

    CloseHandle(hThread[1]);
    CloseHandle(hThread[2]);
    CloseHandle(hThread[3]);
    CloseHandle(hThread[4]);
    CloseHandle(hThread[5]);
    CloseHandle(hThread[6]);
    CloseHandle(hThread[7]);
    CloseHandle(hThread[8]);
    CloseHandle(hThread[9]);

    ExitThread(0);
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
    BOOL bContinue;
    for(int i = 0; i < 3; i++)
    {
        bContinue=TRUE;
        while(bContinue)
        {
            dwWaitResult = WaitForSingleObject(semaphoreTable[(int)lpParam/10],60000L);
            switch (dwWaitResult)
            {
                case WAIT_OBJECT_0:
                    WaitForSingleObject(mutex, INFINITE);
                    cout << charTable[(int)lpParam/10] << flush;
                    ReleaseMutex(mutex);
                    computation();

                    bContinue=FALSE;
                if(!ReleaseSemaphore(semaphoreTable[(int)lpParam%10], 1,NULL))
                {
                    cout << "ReleaseSemaphore error: " << GetLastError();
                }
                break;
                case WAIT_TIMEOUT:
                    cout << "Thread %d: wait timed out\n" << GetCurrentThreadId();
                break;
                }
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

    ghSemaphoreB = CreateSemaphore(NULL,0,6,NULL);
    if (ghSemaphoreB == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreD = CreateSemaphore(NULL,0,3,NULL);
    if (ghSemaphoreD == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreE = CreateSemaphore(NULL,0,12,NULL);
    if (ghSemaphoreE == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreF = CreateSemaphore(NULL,0,9,NULL);
    if (ghSemaphoreF == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreG = CreateSemaphore(NULL,0,6,NULL);
    if (ghSemaphoreG == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreH = CreateSemaphore(NULL,0,6,NULL);
    if (ghSemaphoreH == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreI = CreateSemaphore(NULL,0,6,NULL);
    if (ghSemaphoreI == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }
    ghSemaphoreK = CreateSemaphore(NULL,0,3,NULL);
    if (ghSemaphoreK == NULL)
    {
        cout << "CreateSemaphore error: " <<  GetLastError();
        return 1;
    }

    semaphoreTable[0] = NULL;
    semaphoreTable[1] = ghSemaphoreB;
    semaphoreTable[2] = NULL;
    semaphoreTable[3] = ghSemaphoreD;
    semaphoreTable[4] = ghSemaphoreE;
    semaphoreTable[5] = ghSemaphoreF;
    semaphoreTable[6] = ghSemaphoreG;
    semaphoreTable[7] = ghSemaphoreH;
    semaphoreTable[8] = ghSemaphoreI;
    semaphoreTable[9] = ghSemaphoreK;
    //a
    hThread[0] = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) thread_a, 0,  0, &ThreadIDA);
    if( hThread[0] == NULL )
    {
        cout << "CreateThread error: " << GetLastError();
        return 1;
    }
    WaitForSingleObject(hThread[0], INFINITE);
    CloseHandle(hThread[0]);

    //close semaphore
    for(int i = 0; i < 10; i++)
    {
        if(i != 0 || i != 2)
        CloseHandle(semaphoreTable[i]);
    }

    CloseHandle(mutex);

    return 0;
}
