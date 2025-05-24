add_executable(main main.cpp)
target_link_libraries(main PUBLIC open_addr_map)
target_link_libraries(main PRIVATE gtest gtest_main)
