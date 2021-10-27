@REM Compile-only (no assembling and linking)
@REM copy %1 ..\..\bin
@REM cd ..\..\bin
..\..\bin\sdcc.exe %1 -mjson -S -I"..\..\device\include\json"
@REM copy %1.json ..\tests\json
@REM cd ..\tests\json
@REM -I..\..\device\include\json

@REM Compile and assemble only (no linking)
@REM ..\..\bin\sdcc.exe %1 -mjson -c -I"..\..\device\include\json"

@REM Compile, assemble and link
@REM ..\..\bin\sdcc.exe %1 -mjson -I"..\..\device\include\json"