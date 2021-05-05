PROJECT(ossim-video)

Message("################## Setting up ossim-video library #########################")

INCLUDE(OssimVersion)
INCLUDE(OssimUtilities)
INCLUDE(OssimCommonVariables)

IF(NOT APPLE)
  cmake_minimum_required(VERSION 2.6)
ELSE(NOT APPLE)
  cmake_minimum_required(VERSION 2.8)
ENDIF(NOT APPLE)

INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/include)

# Stores list of libs to link with. Initialized throughout.
set( dependentLibs )

# GEOS - Required:
find_package( GEOS )
if( GEOS_FOUND )
   include_directories( ${GEOS_INCLUDE_DIR} )
   set( dependentLibs ${dependentLibs} ${GEOS_C_LIBRARY} )
else( GEOS_FOUND )
   message( FATAL_ERROR "Could not find required geos package!" )
endif( GEOS_FOUND )

# FFMPEG - Required:
find_package( FFmpeg )
if( FFMPEG_FOUND )
   include_directories( ${FFMPEG_INCLUDE_DIRS} )
   set( dependentLibs ${dependentLibs} ${FFMPEG_LIBRARIES} )
else( FFMPEG_FOUND )
   message( FATAL_ERROR "Could not find required ffmpeg package!" )
endif( FFMPEG_FOUND )

# Ossim - Required:
find_package( ossim )
if( OSSIM_FOUND )
   include_directories( ${OSSIM_INCLUDE_DIR} )
   set( dependentLibs ${dependentLibs} ${OSSIM_LIBRARY} )
else( OSSIM_FOUND )
   message( FATAL_ERROR "Could not find required OSSIM package!" )
endif( OSSIM_FOUND )

MESSAGE( STATUS "OSSIM_INCLUDE_DIR   = ${OSSIM_INCLUDE_DIR}")
MESSAGE( STATUS "OSSIM_LIBRARIES     = ${OSSIM_LIBRARIES}")
MESSAGE( STATUS "FFMPEG_LIBRARIES    = ${FFMPEG_LIBRARIES}")
MESSAGE( STATUS "FFMPEG_INCLUDE_DIRS = ${FFMPEG_INCLUDE_DIRS}")
MESSAGE( STATUS "GEOS_C_LIBRARY      = ${GEOS_C_LIBRARY}" )
MESSAGE( STATUS "GEOS_INCLUDE        = ${GEOS_INCLUDE_DIR}" )
MESSAGE( STATUS "dependent libraries = ${dependentLibraries}" )

################################################## BUILD THE LIBRARY #######################################
SET(LIB_NAME ossim-video)

INCLUDE_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR}/include)
INCLUDE_DIRECTORIES(${FFMPEG_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${OSSIM_INCLUDE_DIR})

FILE(GLOB OSSIMVIDEO_SRCS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
FILE(GLOB OSSIMVIDEO_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/ossimPredator/*.h")
add_definitions("-DOSSIMPREDATOR_LIBRARY")
set(INSTALL_INCLUDE_DIR "include/ossimPredator")
OSSIM_LINK_LIBRARY(${LIB_NAME} COMPONENT_NAME ossim TYPE "${OSSIM_USER_DEFINED_DYNAMIC_OR_STATIC}" HEADERS ${OSSIMVIDEO_HEADERS} SOURCE_FILES ${OSSIMVIDEO_SRCS} 
                   LIBRARIES ${dependentLibs}
                   INSTALL_LIB INSTALL_HEADERS VERSION_SYMLINKS ADDITIONAL_COMPILE_FLAGS "-DOSSIMVIDEO_LIBRARY")
set(INCLUDE_DIR "include")

####################################### SETUP THE UNINSTALL #################################
OSSIM_ADD_COMMON_MAKE_UNINSTALL()

message("################## end of ossim-video library setup #########################")
