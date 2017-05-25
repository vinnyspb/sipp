enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_path(GTEST_SRC_DIRECTORY "3rdparty/googletest" PATHS "${PROJECT_SOURCE_DIR}")

set(BUILD_GTEST ON CACHE BOOL "Build googletest library" FORCE)
set(GTEST_SRC_DIRECTORY "${GTEST_SRC_DIRECTORY}/3rdparty/googletest")
add_subdirectory(${GTEST_SRC_DIRECTORY} "gtest" EXCLUDE_FROM_ALL)

include_directories(SYSTEM "${GTEST_SRC_DIRECTORY}/googletest/include")

set(TEST_SOURCE_FILES
        test_distance.cpp
        test_speed.cpp)
add_executable(sipp_tests ${TEST_SOURCE_FILES})

target_link_libraries(sipp_tests
        gtest
        gtest_main)

