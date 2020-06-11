# EEEE2046 Computing Project

## Overview
This repository contains code and other files written by the members of **Group 35**.

The Project involves creating a program that can read/write model files and perform basic computational functions on them (i.e. Volume, weight, dimensions, centre, dimensions calculations).

This was achieved by creating separate classes including *vector & matrix, cell, model, and material classes* that all work together to create the final program.

## Directory Structure
Header and Source Files are stored within the **Code** folder.

Test Codes for each class and the main program's code is stored within the **Test** folder.

Example mod files are stored within the **Example_Model_Files** folder.

CMakeLists.txt used for building is stored on the parent directory.

## Instructions For Compiling
### MingW
```
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" ..
> mingw32-make
```
### Microsoft Visual Studio
```
> mkdir build
> cd build
> cmake -G "Visual Studio 16 2019" ..
> "C:\Program Files (x86)\Microsoft Visual Studio\VC\vcvarsall.bat" amd64
> msbuild model.sln
```

## Running the Program
### MingW
```
> model.exe
```
### Microsoft Visual Studio
```
> debug\model.exe
```

The program should now run and perform the following tasks:
- Importing all 3 example mod files provided within the *Example_Model_Files* folder to their respective model classes
- Displaying information and properties regarding each of the 3 models (i.e. volume, weight, centre, dimensions)
- Saving all 3 of the models to different mod files into the build directory (named testModel)

## Possible Solutions to Common Compiling Issues:

### CMake
- Ensure CMake version 2.8.0 or above is used
- Ensure CMake/bin folder is defined on PATH beforehand

### MingW
- Ensure MingW/bin folder is defined on PATH beforehand

### Microsoft Visual Studio
- Check that the version of Microsoft Visual Studio specified is correct. The compiling instructions above assumes microsoft visual 16 2019 version is installed, if that's not the case then change it to the version installed in your computer. Tip: Use ```cmake --help``` to find the list of visual studio versions.
- Check that the file path to vcvarshall.bat is correct. If not, find the vcvarshall.bat path in your computer (e.g. by using file explorer) and then edit the file path inside the speech bubbles to the correct path.
