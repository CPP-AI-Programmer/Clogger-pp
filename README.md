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


## Documentation - Comming Soon...

