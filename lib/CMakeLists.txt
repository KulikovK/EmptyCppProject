set(BANANA_LIB On)

if (BANANA_LIB)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LIB_SOURCE)
add_library(banan SHARED ${LIB_SOURCE} "../common.cpp" "../common.h")
endif()