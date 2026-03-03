@echo off

echo Compilando projeto...

gcc Source\main.c Source\inserir_lista.c Source\ler_arquivo.c Source\input.c -IHeaders -o igds.exe

if %errorlevel% neq 0 (
    echo Erro na compilacao.
    pause
    exit /b
)

echo Compilacao concluida!

echo Executando programa...
igds.exe

pause