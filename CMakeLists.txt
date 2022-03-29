cmake_minimum_required(VERSION 3.16)
project(DA_PROJ1_FEUP)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_PROJ1_FEUP
        include/AppStarter.h main.cpp src/AppStarter.cpp include/App.h src/App.cpp include/Menu.h src/Menu.cpp)

target_link_libraries(DA_PROJ1_FEUP)
