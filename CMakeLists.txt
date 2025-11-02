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
include_directories("./external/commonItems/ZipLib")
include_directories("./external/googletest/googletest")
include_directories("./external/googletest/googletest/include")
include_directories("./external/googletest/googlemock")
include_directories("./external/googletest/googlemock/include")

#### Drawer ####

set(CONFIGURATION_SOURCES ${CONFIGURATION_SOURCES} "src/configuration/configuration.cpp")
add_library(
	Configuration
	${CONFIGURATION_SOURCES}
)

set(COUNTRY_COLORS_SOURCES ${COUNTRY_COLORS_SOURCES} "src/country_colors/cosmetic_tags_importer.cpp")
set(COUNTRY_COLORS_SOURCES ${COUNTRY_COLORS_SOURCES} "src/country_colors/country_color_importer.cpp")
set(COUNTRY_COLORS_SOURCES ${COUNTRY_COLORS_SOURCES} "src/country_colors/country_definition_reader.cpp")
set(COUNTRY_COLORS_SOURCES ${COUNTRY_COLORS_SOURCES} "src/country_colors/country_tag_file_reader.cpp")
set(COUNTRY_COLORS_SOURCES ${COUNTRY_COLORS_SOURCES} "src/country_colors/country_tags_reader.cpp")
add_library(
	CountryColors
	${COUNTRY_COLORS_SOURCES}
)

set(MAP_DRAWER_SOURCES ${MAP_DRAWER_SOURCES} "src/map_drawer/controller_drawer.cpp")
set(MAP_DRAWER_SOURCES ${MAP_DRAWER_SOURCES} "src/map_drawer/drawer_utils.cpp")
set(MAP_DRAWER_SOURCES ${MAP_DRAWER_SOURCES} "src/map_drawer/faction_controller_drawer.cpp")
set(MAP_DRAWER_SOURCES ${MAP_DRAWER_SOURCES} "src/map_drawer/faction_ownership_drawer.cpp")
set(MAP_DRAWER_SOURCES ${MAP_DRAWER_SOURCES} "src/map_drawer/ownership_drawer.cpp")
add_library(
	MapDrawer
	${MAP_DRAWER_SOURCES}
)

set(MAP_IMPORTER_SOURCES ${MAP_IMPORTER_SOURCES} "src/map_importer/map_importer.cpp")
add_library(
	MapImporter
	${MAP_IMPORTER_SOURCES}
)

set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/countries_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/country_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/faction_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/province_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/provinces_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/save_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/state_importer.cpp")
set(SAVE_READER_SOURCES ${SAVE_READER_SOURCES} "src/save_reader/states_importer.cpp")
add_library(
	SaveReader
	${SAVE_READER_SOURCES}
)

set(STATE_DEFINITIONS_SOURCES ${STATE_DEFINITIONS_SOURCES} "src/state_definitions/state_definition_importer.cpp")
set(STATE_DEFINITIONS_SOURCES ${STATE_DEFINITIONS_SOURCES} "src/state_definitions/state_definitions_importer.cpp")
add_library(
	StateDefintitions
	${STATE_DEFINITIONS_SOURCES}
)

set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/Color.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/CommonFunctions.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/ConvenientParser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/iconvlite.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/LinuxUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/Log.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/OSCommonLayer.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/Parser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/ParserHelpers.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/StringUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/ModLoader/ModFilesystem.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/ModLoader/ModLoader.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "external/commonItems/ModLoader/ModParser.cpp")
add_library(
	CommonItems
	${COMMON_SOURCES}
)

set(MAIN_SOURCE "src/main.cpp")

add_executable(
	Hoi4MapDrawer
	${MAIN_SOURCE}
)
set_target_properties( Hoi4MapDrawer
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAP_DRAWER_OUTPUT_DIRECTORY}
)
target_compile_definitions(Hoi4MapDrawer PRIVATE cimg_display=0)

link_directories("./external/rakaly")

if (PLATFORM STREQUAL "Windows")
	target_compile_options(Hoi4MapDrawer PRIVATE /permissive /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 
        /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928 
        /external:anglebrackets /external:W0 /WX)
	target_link_libraries(Hoi4MapDrawer LINK_PUBLIC Configuration CountryColors MapDrawer MapImporter SaveReader StateDefintitions CommonItems rakaly.dll.lib ZIPLIB pthread)
elseif (PLATFORM STREQUAL "Linux")
	target_link_libraries(Hoi4MapDrawer LINK_PUBLIC Configuration CountryColors MapDrawer MapImporter SaveReader StateDefintitions CommonItems rakaly ZIPLIB pthread)
endif (PLATFORM  STREQUAL "Windows")

if (PLATFORM STREQUAL "Windows")
	configure_file("external/rakaly/rakaly.dll" "${FRONTER_OUTPUT_DIRECTORY}/Vic3toHoi4/rakaly.dll" COPYONLY)
endif (PLATFORM STREQUAL "Windows")
add_custom_command(TARGET Hoi4MapDrawer POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND git rev-parse HEAD > ${MAP_DRAWER_OUTPUT_DIRECTORY}/../commit_id.txt)


#### Tests ####

set(CONFIGURATION_TEST_SOURCES ${CONFIGURATION_TEST_SOURCES} "src/configuration/configuration_test.cpp")

set(COUNTRY_COLORS_TEST_SOURCES ${COUNTRY_COLORS_TEST_SOURCES} "src/country_colors/cosmetic_tags_importer_test.cpp")
set(COUNTRY_COLORS_TEST_SOURCES ${COUNTRY_COLORS_TEST_SOURCES} "src/country_colors/country_color_importer_test.cpp")
set(COUNTRY_COLORS_TEST_SOURCES ${COUNTRY_COLORS_TEST_SOURCES} "src/country_colors/country_definition_reader_test.cpp")
set(COUNTRY_COLORS_TEST_SOURCES ${COUNTRY_COLORS_TEST_SOURCES} "src/country_colors/country_tag_file_reader_test.cpp")
set(COUNTRY_COLORS_TEST_SOURCES ${COUNTRY_COLORS_TEST_SOURCES} "src/country_colors/country_tags_reader_test.cpp")

set(MAP_IMPORTER_TEST_SOURCES ${MAP_IMPORTER_TEST_SOURCES} "src/map_importer/map_importer_test.cpp")
set(MAP_IMPORTER_TEST_SOURCES ${MAP_IMPORTER_TEST_SOURCES} "src/map_importer/pixel_test.cpp")

set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/countries_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/country_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/faction_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/province_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/provinces_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/save_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/state_importer_test.cpp")
set(SAVE_READER_TEST_SOURCES ${SAVE_READER_TEST_SOURCES} "src/save_reader/states_importer_test.cpp")

set(STATE_DEFINITIONS_TEST_SOURCES ${STATE_DEFINITIONS_TEST_SOURCES} "src/state_definitions/state_definition_importer_test.cpp")
set(STATE_DEFINITIONS_TEST_SOURCES ${STATE_DEFINITIONS_TEST_SOURCES} "src/state_definitions/state_definitions_importer_test.cpp")

set(GTEST_SOURCES ${GTEST_SOURCES} "external/googletest/googletest/src/gtest_main.cc")
set(GTEST_SOURCES ${GTEST_SOURCES} "external/googletest/googletest/src/gtest-all.cc")
set(GTEST_SOURCES ${GTEST_SOURCES} "external/googletest/googlemock/src/gmock-all.cc")

add_executable(
	Hoi4MapDrawerTests
	${CONFIGURATION_TEST_SOURCES}
	${COUNTRY_COLORS_TEST_SOURCES}
	${MAP_IMPORTER_TEST_SOURCES}
	${SAVE_READER_TEST_SOURCES}
	${STATE_DEFINITIONS_TEST_SOURCES}
	${GTEST_SOURCES}
)
set_target_properties( Hoi4MapDrawerTests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY}
)

file(COPY "data/test_data" DESTINATION "${TEST_OUTPUT_DIRECTORY}")

target_link_libraries(Hoi4MapDrawerTests Configuration CountryColors MapDrawer MapImporter SaveReader StateDefintitions CommonItems ${RAKALY_LIB} ZIPLIB pthread)
