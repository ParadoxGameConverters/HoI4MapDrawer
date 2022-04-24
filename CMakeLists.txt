cmake_minimum_required(VERSION 3.16)
#set(CMAKE_VERBOSE_MAKEFILE on)

project(Hoi4MapDrawer)
#set(FRONTER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/Fronter/Fronter/Source)
#set(FRONTER_COMMONS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/Fronter/commonItems)
#set(FRONTER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/Release-Linux)
set(MAP_DRAWER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/Release-Linux)
set(TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/tests/Release-Linux)
set(CMAKE_CXX_STANDARD 20)
set(UNICODE_DEFAULT OFF)


include_directories(.)
include_directories("./external/googletest/googletest")
include_directories("./external/googletest/googletest/include")
include_directories("./external/googletest/googlemock")
include_directories("./external/googletest/googlemock/include")


#### Drawer ####

set(MAP_IMPORTER_SOURCES ${MAP_IMPORTER_SOURCES} "src/map_importer/map_importer.cpp")
add_library(
	MapImporter
	${MAP_IMPORTER_SOURCES}
)

set(MAIN_SOURCE "src/main.cpp")

set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/iconvlite.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/Log.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/OSCommonLayer.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/LinuxUtils.cpp")

add_executable(
	Hoi4MapDrawer
	${MAIN_SOURCE}
	${COMMON_SOURCES}
)
set_target_properties( Hoi4MapDrawer
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAP_DRAWER_OUTPUT_DIRECTORY}
)
target_compile_definitions(Hoi4MapDrawer PRIVATE cimg_display=0)

find_library(RAKALY_LIB librakaly.so PATHS "external/rakaly/" REQUIRED)
target_link_libraries(Hoi4MapDrawer MapImporter ${RAKALY_LIB} pthread)

add_custom_command(TARGET Hoi4MapDrawer POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND git rev-parse HEAD > ${MAP_DRAWER_OUTPUT_DIRECTORY}/../commit_id.txt)


#### Tests ####

set(MAP_IMPORTER_TEST_SOURCES ${MAP_IMPORTER_TEST_SOURCES} "src/map_importer/map_importer_test.cpp")
set(MAP_IMPORTER_TEST_SOURCES ${MAP_IMPORTER_TEST_SOURCES} "src/map_importer/pixel_test.cpp")
#add_library(
#	MapImporterTests
#	${MAP_IMPORTER_TEST_SOURCES}
#)

set(GTEST_SOURCES ${GTEST_SOURCES} "external/googletest/googletest/src/gtest_main.cc")
set(GTEST_SOURCES ${GTEST_SOURCES} "external/googletest/googletest/src/gtest-all.cc")
set(GTEST_SOURCES ${GTEST_SOURCES} "external/googletest/googlemock/src/gmock-all.cc")

add_executable(
	Hoi4MapDrawerTests
	${COMMON_SOURCES}
	${MAP_IMPORTER_TEST_SOURCES}
	${GTEST_SOURCES}
)
set_target_properties( Hoi4MapDrawerTests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY}
)

file(COPY "data/test_data" DESTINATION "${TEST_OUTPUT_DIRECTORY}")

target_link_libraries(Hoi4MapDrawerTests MapImporter pthread)