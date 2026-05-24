# shtop
My own C++ htop for Linux

## Dependencies

### ncurses
```
sudo apt install libncurses-dev
```

## Start
Create build and init cmake
```
mkdir -p build && cmake -S . -B build/
```

Usefull command to start programm
```
clear && cmake --build build/ -j && ./build/shtop
```
