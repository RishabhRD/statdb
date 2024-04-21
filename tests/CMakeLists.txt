file(GLOB_RECURSE test_list "*_test.cpp")
file(GLOB_RECURSE src_list "../src/statdb/*.cpp")
add_executable(statdb-tests ${src_list} ${test_list} main.cpp)
target_include_directories(statdb-tests SYSTEM PRIVATE ../lib)
target_include_directories(statdb-tests PRIVATE ../include)
target_link_libraries(statdb-tests PRIVATE
  project_options
  project_warnings
  doctest::doctest
)
