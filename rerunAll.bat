#!/bin/bash
echo OFF
echo Starting...

for /f %%f in ('dir /b inputs\') do (
     for /l %%x in (1,1,31) do (
         >>results/%%f (
             ms_sequential.exe inputs/%%f
         )   
     )
     for /l %%x in (1,1,31) do (
         >>results/%%f (
             ms_sequential.exe inputs/%%f
         )   
     )
     for /l %%x in (1,1,31) do (
         >>results/%%f (
             ms_sequential.exe inputs/%%f
         )   
     )
)

echo Done.