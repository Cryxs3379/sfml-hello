@echo off
echo ========================================
echo    LAUNCHER AUTOMATICO PARA SFML
echo ========================================
echo.

REM Configurar el PATH para incluir las DLLs de MSYS2 UCRT64
echo Configurando PATH para SFML...
set "PATH=C:\msys64\ucrt64\bin;%PATH%"

REM Verificar que las DLLs existen
echo Verificando DLLs de SFML...
if exist "C:\msys64\ucrt64\bin\libsfml-system-2.dll" (
    echo ✓ libsfml-system-2.dll encontrada
) else (
    echo ✗ libsfml-system-2.dll NO encontrada
    pause
    exit /b 1
)

if exist "C:\msys64\ucrt64\bin\libsfml-graphics-2.dll" (
    echo ✓ libsfml-graphics-2.dll encontrada
) else (
    echo ✗ libsfml-graphics-2.dll NO encontrada
    pause
    exit /b 1
)

if exist "C:\msys64\ucrt64\bin\libsfml-window-2.dll" (
    echo ✓ libsfml-window-2.dll encontrada
) else (
    echo ✗ libsfml-window-2.dll NO encontrada
    pause
    exit /b 1
)

echo.
echo PATH configurado correctamente.
echo Ejecutando SFML Hello...
echo.

REM Ejecutar el programa
sfml_hello.exe

REM Pausar para ver mensajes de error (si los hay)
echo.
echo Programa terminado.
pause
