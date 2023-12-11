# Clogger-pp
A Logger for C++ <br>

## Install
### Step 1: install ncurses <br>
On Arch-Based System <br>

```bash
$ sudo pacman -S ncurses
```

On Fedora, RHEL, CentOS, AlmaLinux, Rocky Linux: <br>

```bash
$ sudo yum install ncurses-devel
```

Or, <br>

```bash
$ sudo dnf install ncurses-devel
```

On Debian, Ubuntu, Linux Mint, Pop OS: <br>

```bash
$ sudo apt install libncurses5-dev libncursesw5-dev
```

### Step 2: Link with cmake
#### use Fetch Content
Check out example/CMakeLists.txt for a complete example <br>
<br>
Replace: <br>
  {EXE_NAME} with your executable name (e.g. main) <br>
  {SOURCE_FILES} with your source files (e.g. src/main.cpp) <br>
```cmake
include(FetchContent)

FetchContent_Declare(
    Clogger_pp 
    GIT_REPOSITORY https://github.com/CPP-AI-Programmer/Clogger-pp.git
    GIT_TAG master) 
FetchContent_MakeAvailable(Clogger_pp)

add_executable({EXE_NAME} {SOURCE_FILES})

target_link_libraries({EXE_NAME} PUBLIC Cloggerpp::Cloggerpp)
```

#### or find_package
Install with <br>
```bash
git clone https://github.com/CPP-AI-Programmer/Clogger-pp.git
cd Clogger-pp && mkdir build && cd build
cmake ..
cmake --build . 
sudo cmake --install .
```
Replace: <br>
  {EXE_NAME} with your executable name (e.g. main) <br>
  {SOURCE_FILES} with your source files (e.g. src/main.cpp) <br>
```cmake
find_package(Cloggerpp)
add_executable({EXE_NAME} {SOURCE_FILES})

target_link_libraries({EXE_NAME} PUBLIC Cloggerpp)
```

If you get an error similar to the program not being able to find libCloggerpp.so.1, use this command <br>
```bash
sudo ldconfig
```
Be careful installing to much as oldver version .so files stay (you should always delete them if not needed to remove bloat) <br>


## Documentation - Comming Soon...

## KNOWN ISSUES
##### legacy cloggerpp and current cloggerpp on same machine
if you have done this and its resulted in errors like symbol not found or the build is saying something like ... not_found in clogger.hpp <br>
then you will most likely have to clean you /usr/local/* of any Cloggerpp files like /usr/local/libCloggerpp*
as well as -rf /usr/local/include/Cloggerpp.
if this dosen't work then please crate an issue and i or someone else who is knowledgeable in this package will try and help you (you can also use stackoverflow if you want)