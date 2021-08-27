@echo off
start/wait dbl lmkx
if ERRORLEVEL 1 goto comperr

start/wait dblink lmkx WND:tklib.elb
if ERRORLEVEL 1 goto lnkerr

start/wait dbr WND:script -c lmkx -i lmkx
if ERRORLEVEL 1 goto wscerr
goto end

:comperr
echo "Compile errors..."
goto end

:lnkerr
echo "Linker errors..."
goto end

:wscerr
echo "Script errors..."
goto end

:end
