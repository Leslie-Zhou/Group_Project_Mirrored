# CMAKELISTS to install Model Viewer Program

cmake_minimum_required( VERSION 3.3 FATAL_ERROR )

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

PROJECT( ModelViewer )

# Set CMake build type to debug
set( CMAKE_BUILD_TYPE Debug )

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )

set( UIS mainwindow.ui )
qt5_wrap_ui( UI_Srcs ${UIS} )

set( ICONS Icons/icons.qrc )
qt5_add_resources( QRC_Srcs ${ICONS} )

# Also link to VTK
find_package( VTK )
include( ${VTK_USE_FILE} )

# Include the header/source and test folders of the model library.
include_directories ( Model_Library/Test )
include_directories ( Model_Library/Code )

# Add Model Library
add_library( modellib Model_Library/Code/model.cpp Model_Library/Code/Material.cpp
		      Model_Library/Code/Cell.cpp Model_Library/Code/vectorClass.cpp
               	      Model_Library/Code/model.h Model_Library/Code/Material.h
		      Model_Library/Code/Cell.h Model_Library/Code/vectorClass.h )

# Add Project Library
add_library( projectlib  mainwindow.cpp mainwindow.h mainwindow.ui
			 filters.cpp filters.h
			 readMod.cpp readMod.h
			 vtkBoxCallback.h vtkBoxCallback.cpp )
target_link_libraries( projectlib Qt5::Widgets )


# Define the executable output and its sources
add_executable( ModelViewer MACOSX_BUNDLE WIN32
			    main.cpp
			    ${UI_Srcs}
			    ${QRC_Srcs} )

# Link project and model library to the executable files
target_link_libraries( ModelViewer modellib )
target_link_libraries( ModelViewer projectlib )

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( ModelViewer Qt5::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( ModelViewer ${VTK_LIBRARIES} )

# Installing
# For Windows only
if ( WIN32 )

# Installer Info
set(CPACK_GENERATOR "NSIS")
set(CPACK_BUILD_CONFIG DEBUG)
set(CPACK_PACKAGE_VENDOR "Group 35")
set(CPACK_PACKAGE_NAME "Model Viewer")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "Model Viewer")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license.txt")

set(CPACK_NSIS_MENU_LINKS
    "https://steventj.github.io/2019_GROUP_35/html/" "Model Viewer Help")
set(CPACK_NSIS_HELP_LINK "https://steventj.github.io/2019_GROUP_35/html/")
set(CPACK_NSIS_URL_INFO_ABOUT "https://steventj.github.io/2019_GROUP_35/html/")
set(CPACK_NSIS_PACKAGE_NAME "Model Viewer")
set(CPACK_NSIS_DISPLAY_NAME "Model Viewer")
set(CPACK_NSIS_MUI_FINISHPAGE_RUN "ModelViewer.exe")
set(CPACK_NSIS_CREATE_ICONS_EXTRA
    "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Model Viewer.lnk' '$INSTDIR\\\\bin\\\\ModelViewer.exe' '-foo -bar'")
set(CPACK_NSIS_DELETE_ICONS_EXTRA
    "Delete '$SMPROGRAMS\\\\$START_MENU\\\\Model Viewer.lnk'")


INSTALL(TARGETS ModelViewer modellib projectlib
 	RUNTIME DESTINATION bin
 	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static )

# Find the folder where QT DLLs live
get_target_property(QT_CORE_LIB Qt5::Core LOCATION)
get_filename_component(QT_RUNTIME_DIR "${QT_CORE_LIB}" DIRECTORY)

list( APPEND QT_DLLS "${QT_RUNTIME_DIR}/Qt5Cored.dll" )
list( APPEND QT_DLLS "${QT_RUNTIME_DIR}/Qt5Guid.dll" )
list( APPEND QT_DLLS "${QT_RUNTIME_DIR}/Qt5Widgetsd.dll" )

# QT Libraries
#file( GLOB QT_DLLS ${QT_RUNTIME_DIR}/*.dll )
install ( FILES ${QT_DLLS} DESTINATION bin COMPONENT Runtime )
install ( FILES "$<TARGET_FILE:Qt5::QWindowsIntegrationPlugin>" DESTINATION bin/platforms COMPONENT Runtime )

# VTK Libraries
file( GLOB VTK_DLLS ${VTK_RUNTIME_LIBRARY_DIRS}/*.dll )
install( FILES ${VTK_DLLS} DESTINATION bin COMPONENT Runtime )

# Microsoft Redistributable
set( CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION bin )
set( CMAKE_INSTALL_DEBUG_LIBRARIES TRUE )  # Install debug libs as VTK is running in debug mode
set( CMAKE_INSTALL_UCRT_LIBRARIES TRUE )   # For ucrtbased.dll
include ( InstallRequiredSystemLibraries ) # Install debug/release system libs

# In some versions of VS, this DLL is required
if(EXISTS "${MSVC_CRT_DIR}/vcruntime${v}_1d.dll")
   install( FILES "${MSVC_CRT_DIR}/vcruntime${v}_1d.dll" DESTINATION bin COMPONENT Runtime )
endif()

# Import Sample Model Files (.mod/.stl)
file( GLOB MOD_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Model_Library/Example_Model_Files/*.mod )
file( GLOB STL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/STL_Model_Files/*.stl )
install( FILES ${MOD_FILES} ${STL_FILES} DESTINATION Models COMPONENT Models )

include(CPack)

endif (WIN32)
