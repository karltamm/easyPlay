cmake_minimum_required(VERSION 3.26)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJ_LIB easyplay-installer-lib)

set(SRC_FILES
    src/manifestHandler.cpp
    src/clientHandler.cpp)

set(INCLUDE_FILES
    include/manifestHandler.h
    include/clientHandler.h)

set(RESOURCE_FILES resources/resources.qrc)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(DEBUG_BUILD)
endif()

project(easyplay-installer LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent)

include_directories(include)

add_library(${PROJ_LIB} STATIC ${SRC_FILES} ${INCLUDE_FILES}) 
add_executable(${PROJECT_NAME} src/main.cpp ${RESOURCE_FILES})

target_link_libraries(${PROJ_LIB} Qt6::Core Qt6::Concurrent)
target_link_libraries(${PROJECT_NAME} ${PROJ_LIB})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# TESTING
enable_testing()

set(TEST_EXE easyplay-installer-tests)
set(TEST_SRC_FILES
    tests/manifestHandlerTest.cpp
    tests/clientHandlerTest.cpp)

add_subdirectory(tests/googletest)

add_executable(${TEST_EXE} ${TEST_SRC_FILES} ${RESOURCE_FILES})
target_link_libraries(${TEST_EXE} gtest_main ${PROJ_LIB})

add_test(NAME ${TEST_EXE} COMMAND ${TEST_EXE})