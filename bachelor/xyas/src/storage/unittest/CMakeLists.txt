#CMAKE by Harry Wei.
# Time & Place: 2011, 3, 26, @ linux lab in xiyou.
# Just for our XYAS project.

# This *ON* can let cmake procedure output into console.
# _So_that we can debug it.
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
SET(CMAKE_VERBOSE_MAKEFILE ON)
PROJECT(XYAS)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# include these files for building.
SET(WORK_HOME $ENV{PWD}/../../../..)
MESSAGE(STATUS "This is dir" ${WORK_HOME})
MESSAGE(STATUS "This is sqlite lib dir" ${WORK_HOME}/3part/sqlite/lib32)
MESSAGE(STATUS "This is xyas lib dir" ${WORK_HOME}/output/lib32)
MESSAGE(STATUS "This is include file dir" ${WORK_HOME}/src/include)
INCLUDE_DIRECTORIES(
       /usr/include/glib-2.0 
       /usr/lib/glib-2.0/include 
       ${WORK_HOME}/src/include
       ${WORK_HOME}/3part/sqlite/include
	   .)
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
LINK_DIRECTORIES(
    ${WORK_HOME}/output/lib32
    ${WORK_HOME}/3part/sqlite/lib32)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
LINK_DIRECTORIES(
    ${WORK_HOME}/output/lib64
    ${WORK_HOME}/3part/sqlite/lib64)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

SET(LIBS glib-2.0
         xyas
	     sqlite3)

SET(TESTSRC test.c)
ADD_EXECUTABLE(test ${TESTSRC})
TARGET_LINK_LIBRARIES(test ${LIBS})
