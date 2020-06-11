# EEEE2046 Computing Project [![Build Status](https://travis-ci.com/StevenTj/2019_GROUP_35.svg?token=PrzWvXnPocszVMzgAUq5&branch=master)]

## Overview
This repository contains code and other files written by the members of **Group 35** in creating the **Model Viewer** Program.

This project consists of making a program that could load 3D models, visualize them, and perform analysis.

Click [**here**](https://steventj.github.io/2019_GROUP_35/ "Model Viewer Documentation") to see the full documentation on the source codes developed.

## Program Features
- Read MOD/STL Files
- Convert MOD files to STL files
- Render and interact with a 3D Model
- Apply a wide range of filters on the model
- Modify the model using Box Widget
- Change model/background colours
- Change model brightness and opacity
- Change camera perspective
- Show model dimensions
- Change model representation
- Display model statistics
- Capture a screenshot of the model on its current state

## Directory Structure
### Root directory
   Semester 1's Model Reader Project files are stored in the [Semester 1](/Semester%201) directory  
   Model Viewer Project files are stored in the [ModelViewer](/ModelViewer) directory  
   CMakeLists.txt used for building is stored in the [ModelViewer](/ModelViewer) directory  

### ModelViewer Directory
   Model Viewer source and header files are stored in the [ModelViewer](/ModelViewer) directory  
   Example STL files are found in [STL_Model_Files](/ModelViewer/STL_Model_Files) directory  

### Model_Library Directory
   Model Reader source and header files updated to be used with Model Viewer are stored in the [Code](/ModelViewer/Model_Library/Code) directory  
   Model Reader test codes to only be used by travis for testing the model reader are stored in the [Test](/ModelViewer/Model_Library/Test) directory  
   Example MOD files are found in the [Example_Model_Files](/ModelViewer/Model_Library/Example_Model_Files) directory  

## Instructions For Running the Program
*Prerequisites: CMake, Visual Studio, Qt, and VTK are installed*
### Creating a Windows Installer
*Further Prerequisites: Windows OS only and NSIS is installed*
```
> mkdir build && cd build
> cmake -G "Visual Studio 16 2019" ..
> cmake --build . --target package
```
   After building package, the installer can be located inside the build folder  
   After installing, the Model Viewer Program can be located inside the bin folder of the install folder  
### Running the Program directly
```
> mkdir build && cd build
> cmake -G "Visual Studio 16 2019" ..
> "C:\Program Files (x86)\Microsoft Visual Studio\VC\vcvarsall.bat" amd64
> msbuild ModelViewer.sln
> debug\ModelViewer.exe
```

## Possible Solutions to Common Compiling & Running Issues:

### CMake
- Ensure CMake version 3.3 or above is used
- Ensure CMake/bin folder is defined on PATH beforehand

### Microsoft Visual Studio
- Check that the version of Microsoft Visual Studio specified is correct. The compiling instructions above assumes Microsoft Visual 16 2019 version is installed, if that's not the case then change it to the version installed in your computer. Tip: Use ```cmake --help``` to find the list of visual studio versions.
- Check that the file path to vcvarshall.bat is correct. If not, find the vcvarshall.bat path in your computer (e.g. by using file explorer) and then edit the file path inside the speech bubbles to the correct path.
