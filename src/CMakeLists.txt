cmake_minimum_required(VERSION 3.10)

project(CtCI-solutions CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
enable_testing()

set(common_dirs ${CMAKE_CURRENT_SOURCE_DIR}/common)
#set(sanitizer_flags -fsanitize=address -fsanitize=undefined)
set(extra_compile_flags -Wall -Wextra -Werror ${sanitizer_flags})
set(extra_link_flags ${sanitizer_flags})

macro(add_problem chapter problem)
  set(exe_name ${chapter}_${problem})
  add_executable(${exe_name} ${problem}.cpp)
  target_include_directories(${exe_name} PUBLIC ${common_dirs})
  target_compile_options(${exe_name} PUBLIC ${extra_compile_flags})
  target_link_options(${exe_name} PUBLIC ${extra_link_flags})
  add_test(test_${exe_name} ${exe_name})
endmacro()

add_subdirectory(ch1)
add_subdirectory(ch2)
add_subdirectory(ch3)
