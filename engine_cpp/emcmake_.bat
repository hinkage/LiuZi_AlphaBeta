cd embuild
call "D:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Auxiliary/Build/vcvarsall.bat" x64
call "D:/All/WASM/emsdk-3.1.56/emsdk_env.bat"
cmake --version
emcmake.bat cmake.exe --fresh -DCMAKE_GENERATOR="Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cd ..
