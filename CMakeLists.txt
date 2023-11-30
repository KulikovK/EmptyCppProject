cmake_minimum_required(VERSION 3.18)
project(Bananan VERSION 0.0.1)

SET(MAX_FILE "2")
option(PVS_CMAKE_ANALYZER "Analyze with PVS-Studio" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

if (PVS_CMAKE_ANALYZER)
   set(PVS_STUDIO_DEBUG On)
endif()

file(GLOB_RECURSE INTERMEDIATE_SRC_FILES ${CMAKE_SOURCE_DIR}/source_*.cpp)
file(GLOB_RECURSE INTERMEDIATE_PVS_FILES ${CMAKE_SOURCE_DIR}/*.PVS-Studio.*)
file(REMOVE ${INTERMEDIATE_SRC_FILES})
#file(REMOVE ${INTERMEDIATE_PVS_FILES})

foreach(IT RANGE 0 ${MAX_FILE})
   file(WRITE "source_${IT}.cpp" "#include <iostream>\n")
   file(APPEND "source_${IT}.cpp" "void GOVNO_${IT}(void * ptr_${IT}_a, size_t size)\n {\n if (*(int*)ptr_${IT}_a / (${IT}-*(int*)ptr_${IT}_a))\n return;\n if (ptr_${IT}_a == 0) delete ptr_${IT}_a;\n }")
   file(WRITE "lib/source_lib_${IT}.cpp" "#include <iostream>\n")
   file(APPEND "lib/source_lib_${IT}.cpp" "void GOVNO_LIB${IT}(void * ptr_${IT}_a, size_t size)\n {\n if (*(int*)ptr_${IT}_a / (${IT}-*(int*)ptr_${IT}_a))\n return;\n if (ptr_${IT}_a == 0);\n }")
   list(APPEND SOURCE "source_${IT}.cpp")
endforeach()

add_library(banana_static STATIC ${SOURCE} "common.h" "common.cpp" "common.cpp")

add_executable(banana banana.cpp "common.cpp" "common.cpp")
target_link_libraries(banana banana_static)

add_subdirectory(lib)


set(BDISTIBUTION_PATH "${CMAKE_SOURCE_DIR}/distribution/${CMAKE_PROJECT_VERSION}/${CMAKE_BUILD_TYPE}" )
set_target_properties( banana banan banana_static
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${BDISTIBUTION_PATH}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${BDISTIBUTION_PATH}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${BDISTIBUTION_PATH}/bin"
)

if (${CMAKE_EXPORT_COMPILE_COMMANDS} AND ${CMAKE_GENERATOR} MATCHES "Ninja" OR ${CMAKE_GENERATOR} MATCHES "Makefile")
add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${BDISTIBUTION_PATH}
    )
endif()

if (PVS_CMAKE_ANALYZER)
  include(FetchContent)
  FetchContent_Declare(
      PVS_CMakeModule
      GIT_REPOSITORY "https://github.com/viva64/pvs-studio-cmake-module.git"
      GIT_TAG        "master"
  )
  FetchContent_MakeAvailable(PVS_CMakeModule)
  #include("${pvs_cmakemodule_SOURCE_DIR}/PVS-Studio.cmake")
  include("D:/GitHub PVS/pvs-studio-cmake-module/PVS-Studio.cmake")
  
  pvs_studio_add_target(TARGET banana.analyze ALL RECURSIVE
                        FORMAT html
                        ANALYZE banana banan banana_static
                        MODE GA:1,2
                        ARGS -R D:/TestSolution/CppTest/testVSPlugin/pvs-studio.pvsconfig
                        #COMPILE_COMMANDS 
                        LOG ${CMAKE_SOURCE_DIR}/StatucAnalysisResult.html
                        )
endif()
