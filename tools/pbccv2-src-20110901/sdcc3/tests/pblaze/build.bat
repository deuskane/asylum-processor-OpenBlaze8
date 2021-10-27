@REM Compile-only (no assembling and linking)
..\..\bin\sdcc.exe %1 -mpblaze -S -I"..\..\device\include\pblaze"

@REM Compile and assemble only (no linking)
@REM ..\..\bin\sdcc.exe %1 -mpblaze -c -I"..\..\device\include\pblaze"

@REM Compile, assemble and link
@REM ..\..\bin\sdcc.exe %1 -mpblaze -I"..\..\device\include\pblaze"