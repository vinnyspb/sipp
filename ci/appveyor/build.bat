mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=%CONFIGURATION% 
cmake --build . --config %CONFIGURATION%

