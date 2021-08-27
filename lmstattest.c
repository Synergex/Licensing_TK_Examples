/*
 * This program illustrates win_lm_stat usage
 *
 * The win_lm_stat routine is dynamically loaded by load_dll() located
 * in loaddll.h
 *
 */

#include <windows.h>
#include <stdio.h>
#include "loaddll.h"

main()
{
    char prod[7] = "999   ";
    char app[7] = "RUN9  ";
    int syserr = 0;
    int sts;
    int inuse;

    load_lmdll();

		/* Display usage of selected license */
    while (1)
    {
	inuse = syserr = 0;
	/* fnLogin is assigned after loading the license DLL in load_dll() */
	sts = (*fnStatus)(prod, app, &inuse, &syserr);
	if (sts)
	    printf("Status error = %d, System error = %d\n", sts, syserr);
	else
	    printf("%s - Current usage: %d \n", app, inuse);
	SleepEx(2000,1);
    }
}
