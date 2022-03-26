cmake_minimum_required(VERSION 3.20)

add_executable(win_portal WIN32 win.cpp)
target_link_libraries(win_portal portal)