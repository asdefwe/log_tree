mkdir build

cd .\build\

cmake .. -G "MinGW Makefiles"

mingw32-make



ECHO ""
ECHO "============ log_tree running ============"
ECHO ""
.\log_tree.exe

cd ..