@echo off

:loop
del test.gba
make -f makefile.txt

if exist test.gba goto run

:miss
pause
cls
goto loop

:run
rem padbin 256 Test.gba
rem copy /b Test.gba+test.gbfs test2.gba
rem gbafix.exe test.gba -tTest -cTest -m00 -r01

test.gba

pause
goto loop

