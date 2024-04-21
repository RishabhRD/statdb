file(GLOB_RECURSE src_list "*.cpp")
add_executable(statdb ${src_list} ${src_list} main.cpp)
target_include_directories(statdb SYSTEM PRIVATE ../lib)
target_include_directories(statdb PRIVATE ../include)
target_link_libraries(statdb PRIVATE
  project_options
  project_warnings
)
