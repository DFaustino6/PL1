#!/bin/bash
echo OFF
echo Starting...

set /p file=Matrix size input: %=%

    for /l %%x in (1,1,31) do (
            >>results/p%f%.txt (
                ms_sequential.exe inputs/p%f%.txt
            )   
        )

    for /l %%x in (1,1,31) do (
            >>results/i%f%.txt (
                ms_sequential.exe inputs/i%f%.txt
            )   
    )

    for /l %%x in (1,1,31) do (
            >>results/r%f%.txt (
                ms_sequential.exe inputs/r%f%.txt
            )   
    )
echo Done.


