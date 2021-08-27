/* 
 * Routines to load and unload licensing DLL
 */

HMODULE syncli;
int (WINAPI *fnLogin)(char *, char *, int, int, unsigned int *, int *);
int (WINAPI *fnLogout)(char *, char *, unsigned int, int, int *);
int (WINAPI *fnStatus)(char *, char *, int *, int *);

extern int WINAPI win_lm_stat(char *, char *, int *, int *);
extern int WINAPI win_lm_login(char *, char *, int, int, unsigned int*, int*);
extern int WINAPI win_lm_logout(char *, char *, unsigned int, int, int *);

extern void load_lmdll();
extern void unload_lmdll();

/*
 * Load the licensing DLL
 */
void
load_lmdll()
{
    syncli = LoadLibrary("syncli_api");
    if (!syncli)
    {
	printf("Cannot find syncli_api.dll");
	exit(-1);
    }
    fnLogin = (int (WINAPI *)(char *, char *, int, int, unsigned int *, int *))GetProcAddress(syncli, "win_lm_login");
    fnLogout = (int (WINAPI *)(char *, char *, unsigned int, int, int *))GetProcAddress(syncli, "win_lm_logout");
    fnStatus = (int (WINAPI *)(char *, char *, int *, int *))GetProcAddress(syncli, "win_lm_stat");
}

/*
 * Unload the licensing DLL
 */
void
unload_lmdll()
{
    FreeLibrary(syncli);
}
