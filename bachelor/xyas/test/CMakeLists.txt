#CMAKE by Harry Wei.
# Time & Place: 2011, 3, 26, @ linux lab in xiyou.
# Just for our XYSA project.

# This *ON* can let cmake procedure output into console.
# _So_that we can debug it.
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
SET(CMAKE_VERBOSE_MAKEFILE ON)
PROJECT(XYSA)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# include these files for building.
SET(WORK_HOME $ENV{PWD}/../..)
MESSAGE(STATUS "This is dir" ${WORK_HOME})
INCLUDE_DIRECTORIES(
       /usr/include/glib-2.0 
       /usr/lib/glib-2.0/include 
	   #${WORK_HOME}/src/include
       ${WORK_HOME}/3part/sqlite/include
)
MESSAGE(STATUS "This is include dir" ${WORK_HOME}/3part/sqlite/include)
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
LINK_DIRECTORIES(
	#${WORK_HOME}/output/lib32
    ${WORK_HOME}/3part/sqlite/lib32)
MESSAGE(STATUS "This is lib dir" ${WORK_HOME}/3part/sqlite/lib32)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
LINK_DIRECTORIES(
	#${WORK_HOME}/output/lib64
    ${WORK_HOME}/3part/sqlite/lib64)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

SET(LIBS glib-2.0
         sqlite3)

SET(TESTSRC test.c)
ADD_EXECUTABLE(test ${TESTSRC})
TARGET_LINK_LIBRARIES(test ${LIBS})
SET(TESTSRC1 server.c)
ADD_EXECUTABLE(server ${TESTSRC1})
TARGET_LINK_LIBRARIES(server ${LIBS})
SET(TESTSRC2 client.c)
ADD_EXECUTABLE(client ${TESTSRC2})
TARGET_LINK_LIBRARIES(client ${LIBS})
