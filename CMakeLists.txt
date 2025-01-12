cmake_minimum_required(VERSION 3.5)

project(BullsAndCow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BullsAndCow main.cpp bullandcow.cpp bullandcow.h)

install(TARGETS BullsAndCow
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)