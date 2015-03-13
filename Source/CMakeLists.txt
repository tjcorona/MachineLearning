get_filename_component(BUILD_PARENT_DIR ${CMAKE_BINARY_DIR} PATH)
set(CMAKE_INSTALL_PREFIX "${BUILD_PARENT_DIR}" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake )

set (HELLOWORLD_SOURCE
    HelloWorld.cc
    )

add_executable (HelloWorld ${HELLOWORLD_SOURCE})

set (TESTDATAPOINT_SOURCE
    TestDataPoint.cc
    )

add_executable (TestDataPoint ${TESTDATAPOINT_SOURCE})

set (TESTLINEARALGEBRA_SOURCE
    TestLinearAlgebra.cc
    )

add_executable (TestLinearAlgebra ${TESTLINEARALGEBRA_SOURCE})

find_package( Octave REQUIRED )
include_directories(${OCTAVE_INCLUDE_DIR})

set (TESTOCTAVE_SOURCE
    TestOctave.cc
    )

add_executable (TestOctave ${TESTOCTAVE_SOURCE})
target_link_libraries( TestOctave ${OCTAVE_LIBRARIES} )

set (TESTOCTAVEEMBEDDED_SOURCE
    TestOctaveEmbedded.cc
    )

add_executable (TestOctaveEmbedded ${TESTOCTAVEEMBEDDED_SOURCE})
target_link_libraries( TestOctaveEmbedded ${OCTAVE_LIBRARIES} )

install (TARGETS
	HelloWorld
	TestDataPoint
	TestLinearAlgebra
	TestOctave
	TestOctaveEmbedded
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
