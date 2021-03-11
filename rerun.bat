#!/bin/bash
echo OFF
echo Starting...

set now=%date:~0,2%/%date:~3,2%/%date:~6,4% %time:~0,2%:%time:~3,2%:%time:~6,2%


set /p file=Matrix input file: %=%

>>results_%file% (
    echo ----------------%now%  %file%----------------
)

for /l %%x in (1,1,31) do (
    >>results_%file% (
        ms_sequential.exe %file%
        echo.
    )   
)

echo Done.


