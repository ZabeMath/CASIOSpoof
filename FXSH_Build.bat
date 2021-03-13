@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist SPOOF.G1A  del SPOOF.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"D:\casio sdk\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"D:\casio sdk\Tools\MakeAddinHeader363.exe" "C:\Users\Alec\Documents\CASIO\fx-9860G SDK\CASIOSpoof"
if not exist SPOOF.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

