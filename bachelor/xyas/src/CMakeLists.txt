# CMAKE by Harry Wei.
# CMAKE updated by Harry Wei.
# Time & Place: 2011, 3, 26, @ linux lab in xiyou.
# Just for our LHDFS project.

# This *ON* can let cmake procedure output into console.
# _So_that we can debug it.
SET(CMAKE_VERBOSE_MAKEFILE ON)
PROJECT(XYAS)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(WORK_HOME   $ENV{PWD}/..)
MESSAGE(STATUS "This is dir " ${WORK_HOME})
MESSAGE(STATUS "This is sqlite lib dir " ${WORK_HOME}/3part/sqlite)
#SET(WORK_HOME   /home/kanghua/workshop2/trunk/hlfs)
# include these files for building.
SET(SQLITE_HOME ${WORK_HOME}/3part/sqlite)
#MESSAGE(STATUS "This is dir " ${HADOOP_HOME})
#SET(HADOOP_HOME /root/jiawei/hadoop/hadoop-0.20.0)
#SET(JAVA_HOME   /usr/lib/jvm/java-6-sun)
INCLUDE_DIRECTORIES(
       /usr/include/glib-2.0 
       /usr/lib/glib-2.0/include
	   /usr/include/gtk-2.0 
       /usr/lib/gtk-2.0/include  
       ${SQLITE_HOME}/include
	   #${SQLITE_HOME}/include/linux
	   #${HADOOP_HOME}/include
       include
       .)
# Use SRCS present all the sources.
# If it has subdirectory, use following commands for adding.

#AUX_SOURCE_DIRECTORY(utils SRCS)
#AUX_SOURCE_DIRECTORY(api SRCS)
#AUX_SOURCE_DIRECTORY(cleaner SRCS)
#AUX_SOURCE_DIRECTORY(blockcache SRCS)
#AUX_SOURCE_DIRECTORY(flusher SRCS)
#AUX_SOURCE_DIRECTORY(fuse SRCS)

ADD_CUSTOM_TARGET(all)
#---------------------- Make libxyas ------------------------------#
ADD_CUSTOM_TARGET(libxyas)
AUX_SOURCE_DIRECTORY(storage XYASSRCS)

IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
	SET(LIBRARY_OUTPUT_PATH ${WORK_HOME}/output/lib32)
	LINK_DIRECTORIES(
		${SQLITE_HOME}/lib32
		#${JAVA_HOME}/jre/lib/i386/server)
		)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	SET(LIBRARY_OUTPUT_PATH ${WORK_HOME}/output/lib64)
	LINK_DIRECTORIES(
		${SQLITE_HOME}/lib64
		)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
	
SET(XYASLIBS	glib-2.0
				gthread-2.0 
				sqlite3)

ADD_LIBRARY(xyas SHARED ${XYASSRCS})
TARGET_LINK_LIBRARIES(xyas ${XYASLIBS})
SET_TARGET_PROPERTIES(xyas PROPERTIES COMPILE_FLAGS "-g")
ADD_DEPENDENCIES(libxyas xyas)

#---------------------- Make xyasclient ---------------------------#
ADD_CUSTOM_TARGET(xyasclient)
INCLUDE(UsePkgConfig)
 
FIND_PACKAGE(GTK)
 
IF (GTK_FOUND)
     INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIR})
      ADD_DEFINITIONS(-DHAVE_GTK)
     MESSAGE("GTK 1.x found and used as GUI\n")
ELSE (GTK_FOUND)
	PKGCONFIG(gtk+-2.0 GTK2_INCLUDE_DIR GTK2_LINK_DIR GTK2_LINK_FLAGS GTK2_CFLAGS)
	PKGCONFIG(gthread-2.0 GTHREAD_INCLUDE_DIR GTHREAD_LINK_DIR GTHREAD_LINK_FLAGS+- GTHREAD_CFLAGS)
      IF (GTK2_INCLUDE_DIR)
          SET(CMAKE_C_FLAGS "${GTK2_CFLAGS} ${GTHREAD_CFLAGS}")
          STRING(REGEX REPLACE "-l" "" GTK_LIBRARIES "${GTK2_LINK_FLAGS} ${GTHREAD_LINK_FLAGS}")
          SEPARATE_ARGUMENTS(GTK_LIBRARIES)
          ADD_DEFINITIONS(-DHAVE_GTK2)
          MESSAGE("GTK 2.x found and used as GUI\n")
      ELSE (GTK2_INCLUDE_DIR)
          MESSAGE(FATAL_ERROR "GTK or GTK2 is required to build this project.")
      ENDIF (GTK2_INCLUDE_DIR)
ENDIF (GTK_FOUND)

SET(EXECUTABLE_OUTPUT_PATH ../output/bin)
#SET(TOOLSRCS ../test/system_monitor/entry.c)
#SET(TOOLSRCS ../src/gtks/main.c)
SET(TOOLSRCS client/client.c)
#SET(TOOLSRCS ../test/test1.c)
ADD_EXECUTABLE(client ${TOOLSRCS})
TARGET_LINK_LIBRARIES(client ${GTK2_LINK_FLAGS})
SET_TARGET_PROPERTIES(client PROPERTIES COMPILE_FLAGS "-g")
ADD_DEPENDENCIES(xyasclient client)

#---------------------- Make xyasserver ---------------------------#
ADD_CUSTOM_TARGET(xyasserver)
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
LINK_DIRECTORIES(
	${WORK_HOME}/output/lib32
    ${SQLITE_HOME}/lib32)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
LINK_DIRECTORIES(
	${WORK_HOME}/output/lib64
    ${SQLITE_HOME}/lib64)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

SET(LIBS glib-2.0
         sqlite3
		 xyas)

SET(TESTSRC server/server.c)
ADD_EXECUTABLE(server ${TESTSRC})
TARGET_LINK_LIBRARIES(server ${LIBS})
SET_TARGET_PROPERTIES(server PROPERTIES COMPILE_FLAGS "-g")
ADD_DEPENDENCIES(xyasserver server)
ADD_DEPENDENCIES(all xyasclient xyasserver)
