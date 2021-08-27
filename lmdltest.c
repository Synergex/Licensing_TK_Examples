/* 
 * This program illustrates win_lm_login and win_lm_logout usage
 */

#include <windows.h>
#include <stdio.h>
#include "loaddll.h"

static void login(unsigned int *, int);
static void logout(unsigned int , int);
void thread(void *);
int tcount = 0;
CRITICAL_SECTION ThreadCount;

#define PROD "999   "
#define APP  "RUN9  "

/*
	The critical section is used below to keep the process alive
	until all threads have finished and logged out, at which time
	the DLL can be safely unloaded.
*/

int
main()
{
    char buf[100];
    unsigned int token;
    int i;
    int done = 0;

    load_lmdll();				/* Load licensing DLL	*/

    printf("Main thread:\n");
    login(&token, 99);				/* Login a seat 	*/
    printf("Press enter\n");
    gets(buf);

    InitializeCriticalSection(&ThreadCount);

    for (i = 1; i < 10; i++)	/* Start some licensing threads		*/
    {
        _beginthread(thread, 0, (void*)i);
    }
    if (token)
	logout(token, 99);			/* Logout a seat 	*/

    do 				/* Wait until all threads have finished	*/
    {
	SleepEx(1000, 1);
	EnterCriticalSection(&ThreadCount);
	if (tcount == 0)
	    done = 1;
	LeaveCriticalSection(&ThreadCount);
    } while (!done);

    unload_lmdll();				/* Unload licensing DLL	*/
    exit(0);
}

/*
 * Login APP user license
 *
 * Seat identifies license usage allocation
 * Token is returned.
 *
 * NOTE: fnLogin is assigned in loaddll.h after loading the license DLL 
 *
 */
void
login(unsigned int *token, int seat)
{
    int syserr;
    int sts = (*fnLogin)(PROD, APP, 0, seat, token, &syserr);

    if (!sts)
	printf("Seat %d logged in\n", seat);
    else
	printf("Login error = %d System error = %d\n", sts, syserr);
}

/*
 * Logout APP user license
 *
 * Seat and token identify license to logout
 *
 * NOTE: fnLogout is assigned in loaddll.h after loading the license DLL 
 */
void
logout(unsigned int token, int seat)
{
    int syserr;
    int sts = (*fnLogout)(PROD, APP, seat, token, &syserr);

    if (!sts)
	printf("Seat %d logged out\n", seat);
    else
    	printf("Logout error = %d System error = %d\n", sts, syserr);
}

/*
 * Example of threaded logins and logouts
 */
void
thread(void *thread)
{
    unsigned int token;
    int seat = (int)thread;

    EnterCriticalSection(&ThreadCount);
    tcount++;
    LeaveCriticalSection(&ThreadCount);

    printf("Thread %d started:\n", seat);
    login(&token, seat);		/* Login license for thread	*/
    SleepEx(10000, FALSE);
    if (token)
	logout(token, seat);		/* Logout license for thread	*/

    EnterCriticalSection(&ThreadCount);
    tcount--;
    LeaveCriticalSection(&ThreadCount);

    _endthread();
}
