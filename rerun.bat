#!/bin/bash
echo OFF
echo Starting...

set /p file=Matrix size input: %=%

for /l %%x in (1,1,31) do (
    >>results/results_p%file%.txt (
        ms_sequential.exe inputs/p%file%.txt
        echo.
    )   
)

for /l %%x in (1,1,31) do (
    >>results/results_i%file%.txt (
        ms_sequential.exe inputs/i%file%.txt
        echo.
    )   
)

for /l %%x in (1,1,31) do (
    >>results/results_r%file%.txt (
        ms_sequential.exe inputs/r%file%.txt
        echo.
    )   
)


echo Done.


