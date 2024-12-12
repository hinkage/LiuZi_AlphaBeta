cd build
call "D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
cmake.exe --build . --target test
cd ..
"x64/Debug/test.exe"
pause
