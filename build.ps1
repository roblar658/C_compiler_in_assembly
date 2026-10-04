if (!(Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin" | Out-Null
}
nasm -f win64 -I ./ src\main.asm -o bin\c_compiler.obj
if ($LASTEXITCODE -ne 0) {
    Write-Error "[!] Assembly failed."
    exit $LASTEXITCODE
}
gcc bin\c_compiler.obj -o bin\c_compiler.exe
if ($LASTEXITCODE -ne 0) {
    Write-Error "[!] GCC linking failed."
    exit $LASTEXITCODE
}
Write-Host "[+] Successfully built bin\c_compiler.exe" -ForegroundColor Green
