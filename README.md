# Licensing_TK_Examples<br />
**Created Date:** 1/14/2009<br />
**Last Updated:** 11/18/2009<br />
**Description:** Code samples for using Synergy/DE Licensing Toolkit.<br />
**Platforms:** Windows<br />
**Products:** Synergy DBL; UI Toolkit<br />
**Minimum Version:** 9.1.5b<br />
**Author:** John Brunett
<hr>

**Additional Information:** Expected to work with 9.1.5b and above. IF YOU ARE USING REV11 LICENSING, refer to the examples included in the version 11 Licensing Toolkit distribution, available from Synergex Customer Service.

Contents
--------
lmkx.dbl (Synergy interactive interface to License Key Generator)
bldx.bat (Batch file to build lmkx.dbr)
lmkx.wsc (Synergy Windows script file for lmkx.dbr)
lm_auth.dbl (Sample routine LM_AUTHORIZE) - Not necessary as of SDE v9.3
lmtest.dbl (Synergy example program using LM_AUTHORIZE and LM_LOGOUT)
lm.def (Synergy example include file)
lmdltest.c (Example Windows DLL program using win_lm_login and win_lm_logout)
lmstattest.c (Example Windows DLL program using win_lm_stat)
loaddll.h (Windows DLL example include)
readme.txt (This file)

Descriptions
------------

lmkx.dbl (Windows only)
is a Synergy program that can be used to generate configuration
keys. As written, this program enables you to generate up to three
keys per licensee name. We explain below how to use the program as
it's currently written, but you can customize it as desired for your
use. Requires UI Toolkit and the License Key Generator, lmk.exe.

Detailed instructions:
1. Edit the LMKPATH identifier in lmkx to point to the location of
lmk (for example, c:\SynergyDE\dbl\bin\lmk.exe).

2. Run the bldx batch file. This compiles and links the lmkx
program and creates its window library.

3. Run lmkx. Complete the fields as described below. You can enter
data for up to three applications.

Licensee name: Enter the licensee name obtained from the
customer site.

Registration string: Enter the registration string obtained from
the customer site.

Application code: Enter the application code for this product.

Number of users: Enter the number of concurrent users permitted.

Timeout: (optional) Enter the date you want the license to time
out, or press F3 and enter the number of days from the current
date that you want the license to be valid. This field enables
you to create a demo license that will expire after a specified
amount of time.

Extended data: (optional) Enter an extended, developer-defined
data string. This string can contain up to 100 characters. You
can use this option to extend the information that gets configured.
It enables you to include your own string for anything for which
the key program doesn't check.

4. Press ENTER.

The lmkx program generates the configuration keys. The keys are
displayed on screen and written to a Synergy Key file (.skf file)
named with the licensee name.

5. Press F4 to exit when you're done.

6. Send the keys to your customer.

bldx.bat (Windows only)
is a batch file to build lmkx.dbr

lmkx.wsc (Windows only)
is a Windows script file required by bldx.dbr

lm_auth.dbl
is a sample Synergy routine LM_AUTHORIZE using LM_LOGIN and LM_INFO.
As written, this routine performs a login of a specified license and
returns its status. This routine operates equivalent to existing
Synergy licensing which includes a 14-day grace period for new
installations. Also, an example of the .NODEBUG compiler directive
is shown.

lmtest.dbl
is an example Synergy program using LM_AUTHORIZE and LM_LOGOUT.
As written, this program interactively logs up to 10 licenses
in and out. Optionally, the license seat can be set to different
values as well as the choice of logging the license in or just
doing a license check. This program requires lm_auth.dbl (containing
LM_AUTHORIZE); however, it can easily be adapted to use LM_LOGIN
directly.

Build instructions:
dbl lmtest
dbl lm_auth
dblink lmtest lm_auth

lm.def
is a Synergy include file required by lm_auth.dbl and lmtest.dbl.
As written, lm_auth.dbl and lmtest.dbl expect this file to be
located in the DBLDIR: directory. You can change the the .INCLUDE
statement in both to accommodate a different file location.

lmdltest.c (Windows only)
is an example Windows program using win_lm_login and win_lm_logout
to log a license in and out. As written, this program attempts
a login of a well-known license, 999 RUN9; however, it can easily be
modified to use a license of your choosing. Requires syncli_api.dll
from the Licensing Toolkit API.

Build instructions:
cl lmdltest.c

lmstattest.c (Windows only)
is an example Windows program using win_lm_stat to query license
usage of a particular license. As written, this program checks the
status of a well-known license, 999 RUN9; however, it can easily be
modified to use a license of your choosing. Requires syncli_api.dll
from the Licensing Toolkit API.

Build instructions:
cl lmstatest.c

loaddll.h (Windows only)
is a Windows include file required by lmdltest.c and lmstattest.c,
containing the load_lmdll and unload_lmdll routines.
