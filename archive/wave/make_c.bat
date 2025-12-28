@echo off
if exist %~n1.exe del %~n1.exe
:: gcc -Wall %1 -lopengl32 -lglfw3 -lgdi32 -o %~n1.exe
 gcc -Wall -O %1 -o %~n1.exe
:: tcc %1 -o %~n1.exe
pause
cls
%~n1.exe
pause