cmake_minimum_required(VERSION 3.22)

set(PROJECT "SimianViewerPairExpCompPlugin")

PROJECT(${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32 /EHsc /MP")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif(MSVC)

# Check if the directory to the ManiVault installation has been provided
if(NOT DEFINED MV_INSTALL_DIR)
    set(MV_INSTALL_DIR "" CACHE PATH "Directory where ManiVault is installed")
    message(FATAL_ERROR "Please set MV_INSTALL_DIR to the directory where ManiVault is installed")
endif()
file(TO_CMAKE_PATH ${MV_INSTALL_DIR} MV_INSTALL_DIR)

find_package(Qt6 COMPONENTS Widgets WebEngineWidgets REQUIRED)

qt6_add_resources(RESOURCE_FILES res/SimianViewerPairExpComp_viewer_resources.qrc)

set(SOURCES
    src/SimianViewerPairExpCompPlugin.h
    src/SimianViewerPairExpCompPlugin.cpp
    src/SimianViewerPairExpCompPlugin.json
    src/SimianViewerPairExpCompOptionsAction.cpp
    src/SimianViewerPairExpCompOptionsAction.h
    src/SimianViewerPairExpCompWidget.h
    src/SimianViewerPairExpCompWidget.cpp
)

set (RESOURCES
    res/SimianViewerPairExpComp_viewer_resources.qrc
)
set (Web
    res/SimianViewerPairExpComp_viewer/SimianViewerPairExpComp_viewer.html
	res/SimianViewerPairExpComp_viewer/SimianViewerPairExpComp_viewer.js
	res/SimianViewerPairExpComp_viewer/SimianViewerPairExpComp_viewer.css
)

source_group( PluginFiles FILES ${SOURCES})
source_group( ResourceFiles FILES ${RESOURCES})
source_group( ResourceFiles\\generated FILES ${CMAKE_CURRENT_BINARY_DIR}/qrc_SimianViewerPairExpComp_viewer_resources.cpp)
source_group( WebFiles FILES ${Web})


include_directories("${MV_INSTALL_DIR}/$<CONFIGURATION>/include/")
include_directories(${PROJECT_SOURCE_DIR}/src)

set(MV_LINK_PATH "${MV_INSTALL_DIR}/$<CONFIGURATION>/lib")
set(PLUGIN_LINK_PATH "${MV_INSTALL_DIR}/$<CONFIGURATION>/$<IF:$<CXX_COMPILER_ID:MSVC>,lib,Plugins>")
set(MV_LINK_SUFFIX $<IF:$<CXX_COMPILER_ID:MSVC>,${CMAKE_LINK_LIBRARY_SUFFIX},${CMAKE_SHARED_LIBRARY_SUFFIX}>)

add_library(${PROJECT} SHARED ${SOURCES} ${RESOURCES} ${RESOURCE_FILES} ${Data} ${Web} ${Common})

# -----------------------------------------------------------------------------
# Target properties
# -----------------------------------------------------------------------------
target_compile_features(${PROJECT} PRIVATE cxx_std_20)

set_target_properties(${PROJECT}
    PROPERTIES
    FOLDER ViewPlugins
)


if(MSVC)
	set(LIB_SUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")
else()
	set(LIB_SUFFIX "${CMAKE_SHARED_LIBRARY_SUFFIX}")
endif()
target_link_libraries(${PROJECT} Qt6::Widgets)
target_link_libraries(${PROJECT} Qt6::WebEngineWidgets)

set(MV_LINK_LIBRARY "${MV_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}MV_Public${MV_LINK_SUFFIX}")
set(POINTDATA_LINK_LIBRARY "${PLUGIN_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}PointData${MV_LINK_SUFFIX}") 
set(CLUSTERDATA_LINK_LIBRARY "${PLUGIN_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}ClusterData${MV_LINK_SUFFIX}") 

target_link_libraries(${PROJECT} "${MV_LINK_LIBRARY}")
target_link_libraries(${PROJECT} "${POINTDATA_LINK_LIBRARY}")
target_link_libraries(${PROJECT} "${CLUSTERDATA_LINK_LIBRARY}")

install(TARGETS ${PROJECT}
   RUNTIME DESTINATION Plugins COMPONENT SHAREDLIB
   LIBRARY DESTINATION Plugins COMPONENT LINKLIB
   ARCHIVE DESTINATION lib COMPONENT LINKLIB
)

add_custom_command(TARGET ${PROJECT} POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
        --install ${CMAKE_CURRENT_BINARY_DIR}
        --config $<CONFIGURATION>
        --prefix ${MV_INSTALL_DIR}/$<CONFIGURATION>
)

# Automatically set the debug environment (command + working directory) for MSVC in debug and release mode
set_property(TARGET ${PROJECT} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<IF:$<CONFIG:DEBUG>,${MV_INSTALL_DIR}/debug,${MV_INSTALL_DIR}/release>)
set_property(TARGET ${PROJECT} PROPERTY VS_DEBUGGER_COMMAND $<IF:$<CONFIG:DEBUG>,"${MV_INSTALL_DIR}/debug/ManiVault Studio.exe","${MV_INSTALL_DIR}/release/ManiVault Studio.exe">)
