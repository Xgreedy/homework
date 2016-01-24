# Weiwei Jia <harryxiyou@gmail.com>.
# Time & Place: 2011, 3, 26, @ linux lab in xiyou.

# This *ON* can let cmake procedure output into console.
# _So_that we can debug it.
SET(CMAKE_VERBOSE_MAKEFILE ON)
PROJECT(Babel)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
#CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(WORK_HOME $ENV{PWD}/..)
MESSAGE(STATUS "Current Work Dir :" ${WORK_HOME})

MESSAGE(STATUS "Probe Glib Info")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
if (GLIB_PKG_FOUND)
message(Found glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif(GLIB_PKG_FOUND)

INCLUDE_DIRECTORIES(
        /usr/include/
		${WORK_HOME}/mlcm/include
		.)
# Use SRCS to save all the sources.
# If it has subdirectory, use following commands for adding.

#---------------------- Make all ------------------------------#
ADD_CUSTOM_TARGET(all)

#----------------------- Make tools ---------------------------#
# Multiple Level Cache Management
ADD_CUSTOM_TARGET(mlcm)
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
LINK_DIRECTORIES(
#		/usr/lib/x86_64-linux-gnu
        )
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
LINK_DIRECTORIES(
#		/usr/lib/x86_64-linux-gnu
        )
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

SET(TOOLLIBS glib-2.0)

SET(EXECUTABLE_OUTPUT_PATH output/bin)
SET(TOOLSRCS  
		${WORK_HOME}/mlcm/*.c)
ADD_EXECUTABLE(mlcm ${TOOLSRCS})
TARGET_LINK_LIBRARIES(mlcm ${TOOLLIBS})
SET_TARGET_PROPERTIES(mlcm PROPERTIES COMPILE_FLAGS "-g -Wstrict-prototypes")

ADD_DEPENDENCIES(all mlcm)
#--------------------- Make all end -----------------------------#
