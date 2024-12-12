cd embuild
call "D:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Auxiliary/Build/vcvarsall.bat" x64
call "D:/All/WASM/emsdk-3.1.56/emsdk_env.bat"
cmake.exe --build . --target liuzi

cd ..
copy /y x64\Release\*.* ..\ui_web\public\
pause
