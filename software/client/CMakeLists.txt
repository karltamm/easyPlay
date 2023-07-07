cmake_minimum_required(VERSION 3.26)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJ_LIB easyplay-device-client-lib)

set(SRC_FILES
    src/deviceHandler.cpp
    src/logger.cpp
    src/browserHandler.cpp)

set(INCLUDE_FILES
    include/deviceHandler.h
    include/logger.h
    include/browserHandler.h)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(DEBUG_BUILD)
endif()

project(easyplay-device-client LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core SerialPort) 

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${PROJ_LIB} STATIC ${SRC_FILES} ${INCLUDE_FILES})
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJ_LIB} Qt6::Core Qt6::SerialPort)
target_link_libraries(${PROJECT_NAME} ${PROJ_LIB})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# TESTING
enable_testing()

set(TESTS_EXE easyplay-device-client-tests)
set(TEST_SRC_FILES tests/browserHandlerTest.cpp)

add_subdirectory(tests/googletest)

add_executable(${TESTS_EXE} ${TEST_SRC_FILES})
target_link_libraries(${TESTS_EXE} PRIVATE gtest_main ${PROJ_LIB})

add_test(NAME ${TESTS_EXE} COMMAND ${TESTS_EXE})