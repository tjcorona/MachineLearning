get_filename_component(BUILD_PARENT_DIR ${CMAKE_BINARY_DIR} PATH)
set(CMAKE_INSTALL_PREFIX "${BUILD_PARENT_DIR}" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)

set (HELLOWORLD_SOURCE
    HelloWorld.cc
    )

add_executable (HelloWorld ${HELLOWORLD_SOURCE})

install (TARGETS HelloWorld DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
