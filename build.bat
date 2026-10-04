@echo off
if not exist bin mkdir bin
nasm -f win64 -I ./ src\main.asm -o bin\c_compiler.obj
if %errorlevel% neq 0 (
    echo [!] Assembly failed.
    exit /b %errorlevel%
)
gcc bin\c_compiler.obj -o bin\c_compiler.exe
if %errorlevel% neq 0 (
    echo [!] GCC linking failed.
    exit /b %errorlevel%
)
echo [+] Successfully built bin\c_compiler.exe
