cmake_minimum_required(VERSION 3.16)
project(DA_PROJ1_FEUP)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_PROJ1_FEUP
        main.cpp
        include/App.h
        include/AppStarter.h
        include/Courier.h
        include/FileReader.h
        include/Menu.h
        include/Package.h
        src/App.cpp
        src/AppStarter.cpp
        src/Courier.cpp
        src/FileReader.cpp
        src/Menu.cpp
        src/Package.cpp
        src/Shipping.cpp include/Shipping.h)

target_link_libraries(DA_PROJ1_FEUP)
